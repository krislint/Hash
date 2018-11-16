// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <windows.h>
#include <iomanip>
using namespace std;

typedef unsigned int uint;
/*
void FileTest(string address)
{
	ifstream in(address,);
	string str;
	while (!in.eof())
	{
		getline(in, str);
		cout << str << endl;
	}
	in.close();
}
*/
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
	double rate = 0.6233;
	uint M; //开放地址的数量
	uint P; //离M最近的素数

	int NextPrime();
	bool Isprime(int n);
public:
	Hash(int Amount, double rate);
	Hash();
	uint HashCode(string str);
	bool Find(string e, int &times);
	void CreatBaseFile(string address);
	void FileTest(void);
	void KeyBoardTest();
	int test();
};

int main(void)
{
	Hash hash;
	hash.CreatBaseFile("input.txt");
	//cout << hash.test() << endl;
	while (true)
	{
		PrintInf();
		int n;
		cin >> n;
		cin.get();
		switch (n)
		{
		case 1: hash.FileTest();
			break;
		case 2: hash.KeyBoardTest();
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
		
		if (e == base[n])
		{
			flag = true;
			break;
		}
		n = (n + 1) % M;
		times++;
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

	//ifstream in(address);
	freopen(address.c_str(),"r",stdin);
	string str;
	uint cnt = 0;
	while (getline(cin, str)&&!cin.eof())
	{
		if (str == "0")
			break;
		uint location = HashCode(str);
		int time = 0;
		Find(str, time);
		cnt += time;
		base[location + time - 1] = str;
	}
	//in.close();
	freopen("con","r",stdin);
	cout << "哈希表构造完毕!" << endl << endl;;
	cout << "平均成功查找长度 " << 1.0*cnt / Amount << endl << endl;
}


void Hash::FileTest(void)
{
	string address;
	cout << endl<<"请输入要测试文件的地址 非绝对路径请用\\\\代替\\,并且确保地址无误"<<endl;
	cin >> address;
	cout << "正在处理中请稍等" << endl;
	//ifstream in(address);
	freopen(address.c_str(),"r",stdin);
	//ofstream out("out.txt");
	freopen("out.txt","w",stdout);
	string name;
	uint amount = 0, cnt = 0;
	while (true&&!cin.eof())
	{	
		getline(cin, name);
		if (name == "0") break;
		cnt++;
		cout << cnt << ": ";
		int times;
		if (Find(name, times))
		{
			cout << "Pos " << HashCode(name) + times;
		}
		else
		{
			cout << ": Sorry! ";
		}
		amount += times;
		cout << " ; cur: " << times << ", Avg: ";
		cout << fixed << setprecision(6) << 1.0*amount / cnt << endl;
		
	}
	
	freopen("con","w",stdout);
	freopen("con","r",stdin);
	cout << "平均查找长度为"<<fixed << setprecision(6) << 1.0*amount / cnt << endl;
	
	//in.close();
	//out.close();
}

void Hash::KeyBoardTest()
{
	string name;
	uint amount = 0, cnt = 0;
	while (true)
	{
		getline(cin, name);
		if (name == "0") break;
		cnt++;
		cout << cnt << ": ";
		int times;
		if (Find(name, times))
		{
			cout << "Pos " << HashCode(name) + times;
		}
		else
		{
			cout << ": Sorry! ";
		}
		amount += times;
		cout << " ; cur: " << times << ", Avg: ";
		cout << fixed << setprecision(6) << 1.0*amount / cnt << endl;

	}
	cout << "平均查找长度为" << fixed << setprecision(6) << 1.0*amount / cnt << endl;
}

int Hash::test()
{
	int cnt = 0;
	for (int i = 0; i < this->M; ++i)
	{
		if (this->base[i] != "")
			cnt++;
	}
	return cnt;
}
