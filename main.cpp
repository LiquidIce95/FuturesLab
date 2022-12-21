#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <clocale>
#include <locale>
#include <vector>
#include <experimental/filesystem>

#include "Modules.h"
using namespace std;

void Modules::SubroutineMainMenu()
{
    //Start of programm 
	cout << "***************************************************************" << endl;
    cout << "*********************Welcome to FuturesLab*********************" << endl;
	cout << "***************************************************************" << endl;
    cout << "What do you want to do? 1=Formatter; 2= FuturesConstructor; 3=SpreadsConstructor ; 4= Spreadsorter; 5=Spreadtuner ; 0=Exit" << endl;

    short A;
    cin >> A;

    switch (A)
    {
    case 1:
        Modules::SubroutineFormatter();
        break;
    case 2:
        Modules::SubroutineFuturesConstructor();
        break;
	case 3:
		Modules::SubroutineSpreadsConstructor();
		break;
	case 4:
		Modules::SubroutineSpreadsorter();
		break;
	case 5:
		Modules::SubroutineSpreadTuner();
    case 0:
        cout << "Thank you for using FuturesLab!" << endl;
		exit(EXIT_SUCCESS);
		

    default:
        break;
    }
}

//works just as an entry point 
int main()
{
    Modules::SubroutineMainMenu();

	return 0;
}
