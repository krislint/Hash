#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <iomanip>
#include <time.h>
#include <fstream>
using namespace std;

typedef unsigned int uint;

void RandCreat()
{
	
	string str;
	cout<<"������Ҫ�������ļ���"<<endl;
	getline(cin,str);
	string comd="RandCreat.exe ";
	time_t at = clock();
	cout << "���ڴ����У����Ե�\n";
	system(comd.append(str).c_str());
	cout<<"�����ɹ�"<<endl;
	cout << endl << fixed << setprecision(0)<< "��ʱ" << (double)(clock() - at) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
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
	double rate = 0.6233;
	uint M; //���ŵ�ַ������
	uint P; //��M���������

	int NextPrime();
	bool Isprime(int n);
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
	cin.get();
	if (rate>0.99)  // �����������
	{
		cout<<"�������̫�󣬳����˳�"<<endl;
		return 0;
	}
	Hash hash(rate);
	time_t at = clock();
	hash.CreatBaseFile("input.txt");
	cout << endl << "��ʱ" << (int)((double)(clock() - at)*1000/CLOCKS_PER_SEC )<<"ms"<< endl;
	
	while (true)
	{
		cin.clear();
		PrintInf();
		string cmd;
		getline(cin,cmd);
		char n=cmd[0];
		switch (n)
		{
		case '1': hash.FileTest();
			break;
		case '2': hash.KeyBoardTest();
			break;
		case '3':	RandCreat();
			break;	
		case '4': return 0;
			break;
		default: cout << "����Ƿ�����������" << endl;
			break;
		}
		
		//system("cls");
		cout << endl;
	}
	return 0;
}
//���캯�� ��ʼ������
Hash::Hash(double rate)
{
	this->rate = rate;
	M = (int)(Amount / rate);//���㿪�ŵ�ַ������
	base = new string[M];//�����Լ���ʼ���ڴ�
	P = NextPrime();
}

Hash::Hash()
{
	M = (int)(Amount / rate);
	base = new string[M];
	P = NextPrime();
}
//��ϣ���ҹؼ�����
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
//Ѱ�������һ������
int Hash::NextPrime()
{
	for (int i = M; i >= 1; i--)
	{
		if (Isprime(i))
			return i;
	}
	return 1;
}
//�����ַ����Ĺ�ϣֵ������λ��
uint Hash::HashCode(string str)
{
	uint seed = 131; // 31 131 1313 13131 131313 etc..
	uint hash = 0;

	for (uint i = 0; i < str.size(); i++)
	{
		hash = hash * seed + str[i];
	}
	return (hash & 0x7FFFFFFF)%P;
}

// �Ƚϸ�Ч�ʵ��ж�������Ƿ�������
bool Hash::Isprime(int num)
{    
     if(num ==2|| num==3 )
        return true ;
        
     if(num %6!= 1&&num %6!= 5)
        return false ;
        
     int tmp =(int)sqrt( num);
     for(int i= 5;i <=tmp; i+=6 )
        if(num %i== 0||num %(i+ 2)==0 )
            return false ;
    
     return true ;
}

void Hash::CreatBaseFile(string address)
{
	cout << "���ڹ����ϣ�����Ե�......" << endl << endl;
	cout << "�������Ϊ " << this->rate << endl << endl;

	ifstream input(address.c_str()); // ������cin�Կ���̨�Ĳ���
	if (!input)
	{
		cout << "�ļ������ڣ�����" << endl;
		system("RandCreat input.txt");
		return;
	}
	string str;
	uint cnt = 0; //���ڼ�¼�ܹ��ĳɹ����Ҵ���
	while (!input.eof()&&getline(input, str))
	{
		
		if (str == "0")
			break;
		uint location = HashCode(str);
		int time = 0;
		Find(str, time);
		cnt += time;
		base[(location + time - 1)%M] = str; //����ȡ������������±�Խ�絼�³������
	}
	input.close();
	cout << "��ϣ�������!" << endl << endl;;
	cout << "ƽ���ɹ����ҳ��� " << 1.0*cnt / Amount << endl << endl;
}


void Hash::FileTest(void)
{
	
	string address;
	cout << endl<<"������Ҫ�����ļ��ĵ�ַ "<<endl;
	getline(cin, address);
	ifstream input(address.c_str());
	if (!input)
	{
		cout << "�ļ������ڣ���������" << endl;
		return ;
	}
	cout << "���ڴ��������Ե�" << endl;	
	//ͨ��freopen�ķ������Լ��ٴ����� ��ֱ��������freopen Ȼ�����keyboardtest �Ϳ���
	/*
	freopen(address.c_str(),"r",stdin);
	freopen("out.txt","w",stdout);
	this->KeyBoardTest();	
	freopen("con","w",stdout);
	freopen("con","r",stdin);
	*/
	time_t at = clock();
	ofstream out("out.txt");
	string name;
	uint amount = 0, cnt = 0;
	while (!input.eof() && getline(input, name))
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
	cout << "ƽ�����ҳ���Ϊ" << fixed << setprecision(6) << 1.0*amount / cnt << endl;

	input.close();
	out.close();
	cout << endl << fixed << setprecision(0)<< "��ʱ" << (double)(clock() - at) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
}

void Hash::KeyBoardTest()
{
	string name;
	uint amount = 0, cnt = 0;
	while (!cin.eof()&&getline(cin, name))
	{
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

