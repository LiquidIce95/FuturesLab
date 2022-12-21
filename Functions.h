#pragma once
#include <string>
#include <iostream>
using namespace std;

class Functions
{
	public:
		static int SymbolFormatter(string symbol);
		static int DateFormatter(string date);
		static bool sortcol(const vector<double>& v1, const vector<double>& v2);
};