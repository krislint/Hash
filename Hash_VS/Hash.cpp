// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <windows.h>
#include <iomanip>
using namespace std;

typedef unsigned int uint;


void RadnCreat()
{
	string str;
	cout<<"������Ҫ�������ļ���"<<endl;
	getline(cin, str);
	string comd = "RandCreat.exe ";
	cout << "���ڴ����У����Ե�\n";
	system((comd.append(str)).c_str());
	cout << "�����ɹ�" << endl ;
}

void PrintInf()
{
	cout << "*************************" << endl;
	cout << "��ѡ�����ģʽ" << endl;
	cout << "*************************" << endl;
	cout << "1:\tͨ���ļ�" << endl;
	cout << "2:\t��������" << endl;
	cout << "3:\t�����������" << endl;
	cout << "4:\t�˳�����" << endl;
	cout << "*************************" << endl;
}

class Hash
{
private:
	string * base;
	int Amount = 100000;
	double rate = 0.6333;
	uint M; //���ŵ�ַ������
	uint P; //��M���������

	int NextPrime();
	bool Isprime(int num);
public:
	Hash(double rate);
	Hash();
	uint HashCode(string str);
	bool Find(string e, int &times);
	void CreatBaseFile(string address);
	void FileTest(void);
	void KeyBoardTest();
};

int main(void)
{
	double rate;
	cout << "�������������:";
	cin >> rate;
	Hash hash(rate);
	hash.CreatBaseFile("input.txt");
	
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
		case 3:RadnCreat();
			break;
		case 4: return 0;
			break;
		default: cout << "����Ƿ�����������" << endl;
			break;
		}

		//system("cls");
		cout << endl;
	}
	return 0;
}

Hash::Hash(double rate)
{
	this->rate = rate;
	M = (int)(Amount / rate);
	base = new string[M];
	P = NextPrime();
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
	for (int i = M; i >= 1; i--)
	{
		if (Isprime(i))
			return i;
	}
	return 1;
}

uint Hash::HashCode(string str)
{

	uint h = 0;
	for (uint i = 0; i < str.size(); i++) {
		h = (h << 4) + str[i];
		uint g = h & 0Xf0000000L;
		if (g)  h ^= g >> 24;
		h &= ~g;
	}
	return h % P;

}

bool Hash::Isprime(int num)
{
	if (num == 2 || num == 3)
		return true;

	if (num % 6 != 1 && num % 6 != 5)
		return false;

	int tmp = (int)sqrt(num);
	for (int i = 5; i <= tmp; i += 6)
	if (num %i == 0 || num % (i + 2) == 0)
		return false;

	return true;
}

void Hash::CreatBaseFile(string address)
{
	cout << "���ڹ����ϣ�����Ե�......" << endl << endl;
	cout << "�������Ϊ " << this->rate << endl << endl;

	ifstream in(address);
	string str;
	uint cnt = 0;
	while (!in.eof() && getline(in, str))
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

	cout << "��ϣ�������!" << endl << endl;;
	cout << "ƽ���ɹ����ҳ��� " << 1.0*cnt / Amount << endl << endl;
}


void Hash::FileTest(void)
{
	string address;
	cout << endl<<"������Ҫ�����ļ��ĵ�ַ �Ǿ���·������\\\\����\\,����ȷ����ַ����"<<endl;
	cin >> address;
	cout << "���ڴ��������Ե�" << endl;
	ifstream in(address);
	ofstream out("out.txt");
	string name;
	uint amount = 0, cnt = 0;
	while (!in.eof() && getline(in, name))
	{
		
		if (name == "0") break;
		cnt++;
		out << cnt << ": ";
		int times;
		if (Find(name, times))
		{
			out << "Pos " << HashCode(name) + times;
		}
		else
		{
			out << "Sorry! ";
		}
		amount += times;
		out << " ; cur: " << times << ", Avg: ";
		out << fixed << setprecision(6) << 1.0*amount / cnt << endl;
		
	}
	cout << "ƽ�����ҳ���Ϊ"<<fixed << setprecision(6) << 1.0*amount / cnt << endl;

	in.close();
	out.close();
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
			cout << "Sorry! ";
		}
		amount += times;
		cout << " ; cur: " << times << ", Avg: ";
		cout << fixed << setprecision(6) << 1.0*amount / cnt << endl;
	}

	cout << "ƽ�����ҳ���Ϊ" << fixed << setprecision(6) << 1.0*amount / cnt << endl;
}
