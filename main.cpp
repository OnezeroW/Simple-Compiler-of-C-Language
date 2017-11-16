#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include "LexicalAnalyzer.h"
#include "ParseAnalyzer.h"
using namespace std;

int main()
{
	ifstream fin;
	Lexical L;
	parse p;
	int i = 0,j = 0;
	int inputchoice;
	cout <<"Compile test.cpp?" <<"   1.yes" <<"   0.no" <<endl;
	cin >>inputchoice;
	cout <<endl;
	if(inputchoice==0)
    {
        cout <<"End!" <<endl;
        return 0;
    }
	fin.open("test.cpp", ios_base::in);
	if (!fin.is_open())
	{
		cout << "Open Faild" <<endl;
	}
	else
	{
	    cout <<"Result after compiling:" <<endl <<endl;
		string str;
		while (getline(fin, str))
		{
			j++;
			L.analyze(str,j);
		}
		for (i = 0; i < L.svector.size(); i++)
		{
			cout <<"\t"<< L.svector[i].words << "\t";
			cout << L.svector[i].label;
			cout << endl;
		}
		fin.close();

	}
    p.parse_analyze(L);
    p.display();
	return 0;
}
