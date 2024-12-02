#include"interpolation.h"
#include"methods.h"
#include<iostream>
#include<sstream>
using namespace std;

int ui_mode();
int api_mode(string, bool, const vector<pair<long double, long double> >&);

enum ERRORCODE {
	UNKOWN_METHOD = 100,
	NUMBER_TOO_LARGE,
	UNEMPLEMENTED_FEATURE,
	UNEXPECTED
};

int main(int argc, char* argv[])
{
	if (argc == 1)
		return ui_mode();

	string method = argv[1];
	if (ZK::methods::interpolation::methods.find(method)==ZK::methods::interpolation::methods.end())
	{
		cerr << "Error: interpolation method unknown!\n";
		for (auto itr : ZK::methods::interpolation::methods)
			cerr << ' ' << itr.first << '\n';
		return ERRORCODE::UNKOWN_METHOD;
	}
	bool human = string(argv[2]) == "-h";
	vector<pair<long double, long double> > points;
	points.reserve((argc >> 1) - 1);
	for (long long i = 2 + human; i < argc; i += 2)
	{
		if (i + 1 == argc)
		{
			cerr << "Error: invalid arguments!\n interpolate <method> [-h] [<x0> <y0>] ... [<xn> <yn>]\n";
			return 1;
		}
		try {
			points.emplace_back(stold(argv[i]), stold(argv[i + 1]));
		}
		catch (const invalid_argument& e) {
			cerr << "Error: invalid numeric value '" << argv[i] << "' or '" << argv[i + 1] << "'\n";
			return 1;
		}
		catch (const out_of_range& e) {
			cerr << "Error: value out of range '" << argv[i] << "' or '" << argv[i + 1] << "'\n";
			return ERRORCODE::NUMBER_TOO_LARGE;
		}
	}

	return api_mode(method, human, points);
}

int ui_mode()
{
	const map<string, ZK::polynomial(*)(const std::vector<std::pair<long double, long double> >&)>& methods = ZK::methods::interpolation::methods;
	vector<pair<string, string> > commands = {
		{"set <x> <y>", "add or edit a point"},
		{"remove <x>", "remove a point"},
		{"clear", "removes all points"},
		{"points", "print all registered points"},
		{"<method> [<x>]", "interpolate using the given method {if given an x value directly evaluates y}"},
		{"quit", "closes the program"}
	};
	map<long double, long double> points;
	pair<long double, long double> point;
	string line;

	cout << "\n\n\033[2J\033[H\n\n";
	while (true)
	{
		for (auto l : commands)
			cout << l.first << "\n\t" << l.second << '\n';
		cout << "\nmethods: ";
		for (auto itr = methods.begin(); itr != methods.end();)
			cout << itr->first << (++itr != methods.end() ? ", " : "\n");

		getline(cin, line);
		cout << "\n\n\033[2J\033[H\n\n";

		istringstream iss(line);
		vector<string> tokens;
		string token;
		while (iss >> token)
			tokens.push_back(token);

		if (tokens[0] == "set")
		{
			if (tokens.size() < 3)
			{
				cout << "Error: missing arguments\n";
				continue;
			}
			try {
				point.first = stold(tokens[1]);
				point.second = stold(tokens[2]);
			}
			catch (...) {
				cout << "Error: could not read x and y values\n";
				continue;
			}
			points[point.first] = point.second;
			cout << "point (" << point.first << ", " << point.second << ") set!\n";
		}
		else if (tokens[0] == "remove")
		{
			if (tokens.size() < 2)
			{
				cout << "Error: missing arguments\n";
				continue;
			}
			try {
				point.first = stold(tokens[1]);
			}
			catch (...) {
				cout << "Error: could not read x value\n";
				continue;
			}
			points.erase(point.first);
			cout << "point removed!\n";
		}
		else if (tokens[0] == "clear")
		{
			points.clear();
			cout << "data cleared!\n";
		}
		else if (tokens[0] == "points")
		{
			if (!points.size())
				cout << "no points saved...\n";
			for (auto p : points)
				cout << p.first << ", " << p.second << '\n';
		}
		else if (tokens[0] == "quit")
		{
			cout << "bye!\n";
			return 0;
		}
		else if (methods.find(tokens[0]) != methods.end())
		{
			ZK::interpolation F(methods.find(tokens[0])->second);
			try {
				F.set(points);
			}
			catch (const std::invalid_argument& e) { // Catch unequal intervals or similar issues
				cout << "Error: " << e.what() << '\n';
				continue;
			}
			catch (const std::exception& e) { // Catch division by zero or other exceptions
				cout << "Unexpected error during interpolation: " << e.what() << '\n';
				continue;
			}
			if (tokens.size() < 2)
				cout << F(ZK::polynomial({ 0,1 })) << '\n';
			else try {
				point.first = stold(tokens[1]);
				cout << "F(" << point.first << ") = " << F(point.first) << '\n';
			}
			catch (...) {
				cout << "Error: could not read x value\n";
			}
		}
		else
			cout << "Error: command unrecognized...\n";
	}
	return ERRORCODE::UNEXPECTED;
}


int api_mode(string method, bool human, const vector<pair<long double, long double> >& points)
{
	ZK::interpolation F(ZK::methods::interpolation::methods.find(method)->second, map<long double, long double>(points.begin(), points.end()));
	ZK::polynomial result = { 0,1 };
	result = F(result);
	if (human)
	{
		cout << result << '\n';
		return 0;
	}
	for (long long i = 0; i < result.size(); ++i)
		cout << result[i] << ' ';
	return 0;
}