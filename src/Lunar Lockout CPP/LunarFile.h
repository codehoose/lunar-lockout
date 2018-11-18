#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class CLunarFile
{
public:

	CLunarFile(void);
	~CLunarFile(void);

	void WriteLunar(char * filename, string * lines);
	void ReadLunar(char * filename, string * lines);
	void ReadLunar(int boardID, string * lines);
	void DoWriting(char * filename);
protected:

	void GetLine(int num, string & line);

};