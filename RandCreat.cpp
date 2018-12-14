
//#include "stdafx.h"
#include <iostream>
#include <set>
#include <stdlib.h>
#include <ctime>
using namespace std;

const int Amount = 100000;
//const double rate =0.666;

void RandCreat(const char *address)
{
	srand((unsigned)time(NULL));
	set<string> names;
	//FILE *fp = NULL;
	//errno_t err = fopen_s(&fp, address, "w");
	//if ( err!= 0) return;
	FILE *fp=fopen(address,"w");
	if (fp==NULL) return ;
	int nowsize = 0;
	while (nowsize<Amount)
	{
		int len = 5 + rand() % 5;
		string name = "";
		for (int i = 0; i<len; ++i)
		{
			if (rand() % 2)	name += rand() % 26 + 'a';
			else name += rand() % 26 + 'A';
		}

		if (names.find(name) == names.end())
		{
			names.insert(name);
			fprintf(fp, "%s\n", name.c_str());
			nowsize++;
		}

	}

	fprintf(fp, "0");
	fclose(fp);
}


int main(int argc, char *argv[])
{
	//RandCreat("input.txt");

	for (int i = 1; i < argc; ++i)
	{
		RandCreat(argv[i]);
	}

	return 0;

}

