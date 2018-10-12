#include<streambuf>
#include<sstream>
#include<fstream>
#include<iostream>
#include"log_server.h"
#include"cJSON.h"
using namespace std;

void readFileContent(string fileName, string &_content)
{
	ifstream fp;
	fp.open("E:\\tests\\test1.json");
	stringstream buff;
	buff << fp.rdbuf();

	_content = buff.str();

}

int main()
{
	string content = "test";
	int tmp = 10;
	LOG_RECORD(LOG_INFO, "content = %s tmp = %d\n", content.c_str(),tmp);

	return 0;
}