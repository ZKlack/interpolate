#include"interpolation.h"
#include"methods.h"
using namespace std;

int ui_mode();
int api_mode(string, bool, const vector<pair<long double, long double> >&);

int main(int argc, char* argv[])
{
	if (argc == 1)
		return ui_mode();
	//parse params
	return api_mode(/*pass good params*/);
}

int ui_mode()
{

}

int api_mode(string method, bool human, const vector<pair<long double, long double> >& points)
{

}