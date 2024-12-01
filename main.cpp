#include"interpolation.h"
#include"methods.h"
#include <iostream>
using namespace std;

int ui_mode();
int api_mode(string, bool, const vector<pair<long double, long double> >&);

enum ERRORCODE {
	UNKOWN_METHOD = 100,
	NUMBER_TOO_LARGE,
	UNEMPLEMENTED_FEATURE
};

int main(int argc, char* argv[])
{
	if (argc == 1)
		return ui_mode();

	string method = argv[1];
	if (!ZK::methods::interpolation::methods.contains(method))
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
		catch (const invalid_argument& e) { // Catch invalid number conversion
			cerr << "Error: invalid numeric value '" << argv[i] << "' or '" << argv[i + 1] << "'\n";
			return 1;
		}
		catch (const out_of_range& e) { // Catch numbers that are too large
			cerr << "Error: value out of range '" << argv[i] << "' or '" << argv[i + 1] << "'\n";
			return ERRORCODE::NUMBER_TOO_LARGE;
		}
	}

	return api_mode(method, human, points);
}

int ui_mode()
{
	return ERRORCODE::UNEMPLEMENTED_FEATURE;
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