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
	cout<<"请输入要创建的文件名"<<endl;
	getline(cin,str);
	string comd="RandCreat.exe ";
	time_t at = clock();
	cout << "正在创建中，请稍等\n";
	system(comd.append(str).c_str());
	cout<<"创建成功"<<endl;
	cout << endl << fixed << setprecision(0)<< "耗时" << (double)(clock() - at) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
}
void PrintInf()
{
	cout << "*************************" << endl;
	cout << "请选择测试模式" << endl;
	cout << "*************************" << endl;
	cout << "1:\t通过文件" << endl;
	cout << "2:\t键盘输入" << endl;
	cout << "3:\t随机创建数据" << endl;
	cout << "4:\t退出程序" << endl;
	cout << "*************************" << endl;
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
	cout << "请输入填充因子:";
	cin >> rate;
	cin.get();
	if (rate>0.99)  // 避免错误输入
	{
		cout<<"填充因子太大，程序将退出"<<endl;
		return 0;
	}
	Hash hash(rate);
	time_t at = clock();
	hash.CreatBaseFile("input.txt");
	cout << endl << "耗时" << (int)((double)(clock() - at)*1000/CLOCKS_PER_SEC )<<"ms"<< endl;
	
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
		default: cout << "输入非法请重新输入" << endl;
			break;
		}
		
		//system("cls");
		cout << endl;
	}
	return 0;
}
//构造函数 初始化变量
Hash::Hash(double rate)
{
	this->rate = rate;
	M = (int)(Amount / rate);//计算开放地址的数量
	base = new string[M];//创建以及初始化内存
	P = NextPrime();
}

Hash::Hash()
{
	M = (int)(Amount / rate);
	base = new string[M];
	P = NextPrime();
}
//哈希查找关键函数
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
//寻找最近的一个素数
int Hash::NextPrime()
{
	for (int i = M; i >= 1; i--)
	{
		if (Isprime(i))
			return i;
	}
	return 1;
}
//计算字符串的哈希值并返回位置
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

// 比较高效率的判断这个数是否是素数
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
	cout << "正在构造哈希表，请稍等......" << endl << endl;
	cout << "填充因子为 " << this->rate << endl << endl;

	ifstream input(address.c_str()); // 类似于cin对控制台的操纵
	if (!input)
	{
		cout << "文件不存在，请检查" << endl;
		system("RandCreat input.txt");
		return;
	}
	string str;
	uint cnt = 0; //用于记录总共的成功查找次数
	while (!input.eof()&&getline(input, str))
	{
		
		if (str == "0")
			break;
		uint location = HashCode(str);
		int time = 0;
		Find(str, time);
		cnt += time;
		base[(location + time - 1)%M] = str; //加上取余操作，避免下标越界导致程序崩溃
	}
	input.close();
	cout << "哈希表构造完毕!" << endl << endl;;
	cout << "平均成功查找长度 " << 1.0*cnt / Amount << endl << endl;
}


void Hash::FileTest(void)
{
	
	string address;
	cout << endl<<"请输入要测试文件的地址 "<<endl;
	getline(cin, address);
	ifstream input(address.c_str());
	if (!input)
	{
		cout << "文件不存在，请检查输入" << endl;
		return ;
	}
	cout << "正在处理中请稍等" << endl;	
	//通过freopen的方法可以减少代码量 ，直接先两个freopen 然后调用keyboardtest 就可以
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
	cout << "平均查找长度为" << fixed << setprecision(6) << 1.0*amount / cnt << endl;

	input.close();
	out.close();
	cout << endl << fixed << setprecision(0)<< "耗时" << (double)(clock() - at) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
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
	
	cout << "平均查找长度为" << fixed << setprecision(6) << 1.0*amount / cnt << endl;
}

