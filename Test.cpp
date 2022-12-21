#include <iostream>
using namespace std;

int main()
{
	
	string A = "125356466221565";
	
	cout<<A<<endl;
	
	long B = stol(A);
	
	double C = (double)B;
	
	long T = (long)C;
	
	cout<<B<<endl;
	cout<<C<<endl;
	cout<<T<<endl;
	
	return 0;
}