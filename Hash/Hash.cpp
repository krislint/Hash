// Hash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void test(void)
{
	ifstream in("input.txt");
	string str;
	while (!in.eof())
	{
		getline(in, str);
		cout << str << endl;
	}
	in.close();
}

class HashTable
{
private:
	string *base;
	const int Amount = 10000;
	const double rate = 0.666;
	unsigned int M;

public:
	HashTable()
	{
		M = (int)(Amount / rate);
		base = new string[M];
		fill(base, base + M, "");
	}

	bool Find(string e, int &times)
	{
		bool flag = false;
		unsigned int n = HashCode(e);
		times = 0;
		while (base[n] != "")
		{
			times++;
			if (e == base[n])
			{
				flag = true;
				break;
			}
			n = (n + 1) % M;
		}

		return flag;
	}
	unsigned int HashCode(string str)
	{

		unsigned int h = 0;
		for (int i = 0; i < str.size(); i++) {
			h = (h << 4) + str[i];
			unsigned int g = h & 0Xf0000000L;
			if (g)  h ^= g >> 24;
			h &= ~g;
		}
		return h % M;

	}

	int GetM()
	{
		return M;
	}
};

int main(void)
{
	HashTable s;
	cout << s.GetM() << endl;
	int time=0;
	cout << s.Find("sdasd", time) << "  " << time << endl;
	return 0;
}
