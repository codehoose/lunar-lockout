#include ".\lunarfile.h"

CLunarFile::CLunarFile(void){}
CLunarFile::~CLunarFile(void){}

void CLunarFile::DoWriting(char * filename)
{
	string s[5];
	for(int i=0; i < 5; i++)
	{
		GetLine((i+1), s[i]);
	}
	WriteLunar(filename, s);
}

void CLunarFile::ReadLunar(char * filename, string * lines)
{
	using namespace std;
	ifstream myFile;
	myFile.open(filename, ios::in);
	for(int i=0; i<5; i++)
	{
		getline(myFile, lines[i]);
	}
	myFile.close();
}

void CLunarFile::ReadLunar(int boardid, string * lines)
{
	char buffer[8];
	string filename(".txt");
	itoa(boardid, buffer, 10);
	string prefix(buffer);
	filename = prefix + filename;
	ReadLunar((char*)filename.c_str(), lines);
}

void CLunarFile::GetLine(int num, string & line)
{
	using namespace std;
	cout << "Line " << num << " ";
	cin >> line;
}

void CLunarFile::WriteLunar(char * filename, string * lines)
{
	using namespace std;
	ofstream myFile;
	myFile.open(filename, ios::out);

	for(int i=0; i < 5; i++)
		myFile << lines[i] << std::endl;

	myFile.close();
}