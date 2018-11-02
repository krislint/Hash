// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <windows.h>
using namespace std;

typedef unsigned int uint;

void FileTest(string address)
{
	ifstream in(address);
	string str;
	while (!in.eof())
	{
		getline(in, str);
		cout << str << endl;
	}
	in.close();
}

void PrintInf()
{
	cout << "*************************" << endl;
	cout << "请选择测试模式" << endl;
	cout << "*************************" << endl;
	cout << "1:\t通过文件" << endl;
	cout << "2:\t键盘输入" << endl;
	cout << "3:\t退出程序" << endl;
}

class Hash
{
private:
	string * base;
	int Amount = 100000;
	double rate = 0.666;
	uint M;
	uint P;

	int NextPrime();
	bool Isprime(int n);
public:
	Hash(int Amount, double rate);
	Hash();
	uint HashCode(string str);
	bool Find(string e, int &times);
	void CreatBaseFile(string address);
	void FileTest(string address);
	void KeyBoardTest();
};

int main(void)
{
	Hash hash;
	hash.CreatBaseFile("test.txt");

	while (true)
	{
		PrintInf();
		int n;
		cin >> n;
		switch (n)
		{
		case 1:
			break;
		case 2:
			break;
		case 3: return 0;
			break;
		default: cout << "输入非法请重新输入" << endl;
			break;
		}

		//system("cls");
		cout << endl;
	}
	return 0;
}

Hash::Hash(int Amount, double rate)
{
	this->Amount = Amount;
	this->rate = rate;
	Hash();
}

Hash::Hash()
{
	M = (int)(Amount / rate);
	base = new string[M];
	P = NextPrime();
}

bool Hash::Find(string e, int &times)
{
	bool flag = false;
	uint n = HashCode(e);
	times = 1;
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


int Hash::NextPrime()
{
	for (int i = M; i >= 0; i--)
	{
		if (Isprime(i))
			return i;
	}
}

uint Hash::HashCode(string str)
{

	uint h = 0;
	for (int i = 0; i < str.size(); i++) {
		h = (h << 4) + str[i];
		uint g = h & 0Xf0000000L;
		if (g)  h ^= g >> 24;
		h &= ~g;
	}
	return h % P;

}

bool Hash::Isprime(int n)
{
	for (int i = 2; i<sqrt(n); ++i)
	{
		if (n%i == 0)
			return false;
	}
	return true;
}

void Hash::CreatBaseFile(string address)
{
	cout << "正在构造哈希表，请稍等......" << endl << endl;
	cout << "填充因子为 " << this->rate << endl << endl;

	ifstream in(address);
	string str;
	uint cnt = 0;
	while (getline(in, str))
	{
		if (str == "0")
			break;
		uint location = HashCode(str);
		int time = 0;
		Find(str, time);
		cnt += time;
		base[location + time - 1] = str;
	}
	in.close();

	cout << "哈希表构造完毕!" << endl << endl;;
	cout << "平均成功查找长度 " << 1.0*cnt / Amount << endl << endl;
}
