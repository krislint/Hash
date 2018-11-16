// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout << "��ѡ�����ģʽ" << endl;
	cout << "*************************" << endl;
	cout << "1:\tͨ���ļ�" << endl;
	cout << "2:\t��������" << endl;
	cout << "3:\t�˳�����" << endl;
}

class Hash
{
private:
	string * base;
	int Amount = 100000;
	double rate = 0.6233;
	uint M; //���ŵ�ַ������
	uint P; //��M���������

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
		default: cout << "����Ƿ�����������" << endl;
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
	cout << "���ڹ����ϣ�����Ե�......" << endl << endl;
	cout << "�������Ϊ " << this->rate << endl << endl;

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
	cout << "��ϣ�������!" << endl << endl;;
	cout << "ƽ���ɹ����ҳ��� " << 1.0*cnt / Amount << endl << endl;
}


void Hash::FileTest(void)
{
	string address;
	cout << endl<<"������Ҫ�����ļ��ĵ�ַ �Ǿ���·������\\\\����\\,����ȷ����ַ����"<<endl;
	cin >> address;
	cout << "���ڴ��������Ե�" << endl;
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
	cout << "ƽ�����ҳ���Ϊ"<<fixed << setprecision(6) << 1.0*amount / cnt << endl;
	
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
	cout << "ƽ�����ҳ���Ϊ" << fixed << setprecision(6) << 1.0*amount / cnt << endl;
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
