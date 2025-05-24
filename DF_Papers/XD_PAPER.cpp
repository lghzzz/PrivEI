#include "HMAC_256.h"
#include "SHA_256.h"
#include<integer.h>
#include<iostream>
#include<osrng.h>
#include<nbtheory.h>
#include<dh.h>
#include<hrtimer.h>
#include<math.h>
#include<cmath>
#include<fstream>
#include<secblock.h>
#include<files.h>
#include<string>
#include<sstream>
#include<vector>
#include<stack>
#include <algorithm>
#include <ctime>	
#include<iostream>


//DM表示中国剩余定理中用户数据的维度
#define MAX 1000
#define DM 6



using namespace std;
using namespace CryptoPP;


//文件流对象
ofstream outfile;


//pr、pu是以Integer类型保存解码之后的私钥、公钥，con存储解码后的协商值
//p1、p2是以地址的形式（SecByteBlock）保存私钥和公钥，目的在于方便使用库中的agree协商函数
int n;
Integer pr[MAX];
Integer pu[MAX];
Integer con[MAX][MAX];

SecByteBlock p1[MAX];
SecByteBlock p2[MAX];

//space存储加密空间,它的含义是第I个用户的第J列的哈希值，即H
Integer space[MAX][MAX];

//定义三个基本数p,q,g
AutoSeededRandomPool rng;
Integer p, q, g;
Integer K = 1;

//这些数组都是完成签名工作需要的中间量，其中M2是签名认证之后存储的值
Integer gamma[MAX][MAX], beta[MAX][MAX];
string L[MAX], R[MAX];
Integer C[MAX][MAX], S[MAX][MAX];
Integer M1[MAX], M2[MAX][MAX];
Integer Sig_r;
vector<int> V;

//声明字符串转Integer函数tran1
Integer tran1(string s);

//序列号
vector<int> SN;

//中国剩余定理被除数和除数（模数）
typedef long long llong;
Integer b[MAX][DM];


//中国剩余定理W赋值
// 16维
//Integer w[DM] = { 131,137 ,139 ,149 ,151 ,157 ,163 ,167 ,173 ,179 ,181 ,191 ,193 ,197 ,199 ,211 };
//Integer w[DM] = {32771,32779,32783 ,32789, 32797, 32801, 32803, 32831, 32833, 32839, 32843, 32869, 32887, 32909, 32911,32917};
//Integer w[DM] = {tran1("2332913579"),tran1("3537815783"),tran1("3901918367"),tran1("3521966627"),tran1("4041359759"),tran1("2560834439"),tran1("3927551339"),tran1("3252618827"),tran1("4068467087"),tran1("2777096207"),tran1("2846247707"),tran1("4060407383"),tran1("2844487307"),tran1("2201980343"),tran1("2499728207"),tran1("3358379183") };
//Integer w[DM] = {tran1("14799980878431137483"),tran1("11375890615488983567"),tran1("17946625525685077583"),tran1("11072502421788333047"),tran1("14391117850104244559"),tran1("14507098390601505203"),tran1("11691624821837589599"),tran1("14908258777734559379"),tran1("11144752929418587539"),tran1("10787199373909830083"),tran1("13286396365882500647"),tran1("17178023310558063599"),tran1("13627461406213581503"),tran1("13012120592205740207"),tran1("16201609614510235667"),tran1("17962597866526172243") };

//8维
//Integer w[DM] = { 131,137 ,139 ,149 ,151 ,157 ,163 ,167};
Integer w[DM] = {32771,32779,32783 ,32789, 32797, 32801};
//Integer w[DM] = {tran1("2332913579"),tran1("3537815783"),tran1("3901918367"),tran1("3521966627"),tran1("4041359759"),tran1("2560834439")};
//Integer w[DM] = {tran1("14799980878431137483"),tran1("11375890615488983567"),tran1("17946625525685077583"),tran1("11072502421788333047"),tran1("14391117850104244559"),tran1("14507098390601505203"),tran1("11691624821837589599"),tran1("14908258777734559379") };

//4维
//Integer w[DM] = {131,137 ,139 ,149};
//Integer w[DM] = {32771,32779,32783 ,32789};
//Integer w[DM] = {tran1("2332913579"),tran1("3537815783"),tran1("3901918367"),tran1("3521966627")};
//Integer w[DM] = { tran1("14799980878431137483"),tran1("11375890615488983567"),tran1("17946625525685077583"),tran1("11072502421788333047")};



//EV向量，crt_1是mbi,crt_2是还原后的每个用户每个维度的数据mil,agg是最终聚合函数
Integer EV[MAX][MAX];
Integer crt_1[MAX];
Integer crt_2[MAX][16];
Integer AG[MAX];

//安全参数 128位
string secur = "340282366920938463463374607431768211456";
Integer M = tran1(secur);


//定义加密空间数值转换的中间变量
string con_temp[MAX][MAX];
string j_temp[MAX];
Integer num_temp[MAX][MAX];

//签名算法数制转换中间变量
Integer temp_s1;
string temp_R1;
string temp_pr[MAX];
Integer temp_g;
string temp_j;
Integer temp_z;
Integer temp_value1;
Integer temp_value2;
int temp_num;
string temp_s;
Integer temp_L[MAX];
string temp_C[MAX][MAX];
Integer temp_part1;
Integer temp_part2;
Integer temp_part3;
string temp_Sig_r;


//Integer型转字符串
string its(Integer n)
{
	ostringstream stream;
	stream << n;  //n为int类型
	string ans = stream.str();
	int l = ans.length();
	ans.erase(l - 1, 1);
	return ans;
}

//整型转字符串
string its(int n)

{
	ostringstream stream;

	stream << n;  //n为int类型

	return stream.str();

}

//字符串转Integer型（十六进制）
Integer trans(string s)
{
	Integer c = s.length();
	Integer n = 0;
	for (int i = 0; i < c; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			Integer m = s[i] - '0';
			n = n + m;
		}
		else
		{
			Integer m = s[i] - 'a' + 10;
			n = n + m;
		}
		if (i < c - 1)
			n = n * 16;
	}
	return n;
}

//字符串转整型
int tran(string s)
{

	if (s[0] != '-')
	{
		int c = s.length();
		int n = 0;
		for (int i = 0; i < c; i++)
		{
			int m = s[i] - '0';
			n = n + m;

			if (i < c - 1)
				n = n * 10;
		}
		return n;
	}
	else
	{
		int c = s.length();
		int n = 0;
		for (int i = 1; i < c; i++)
		{
			int m = s[i] - '0';
			n = n + m;

			if (i < c - 1)
				n = n * 10;
		}
		n = -n;
		return n;
	}

}

//字符串转Integer型(10进制）
Integer tran1(string s)
{

	if (s[0] != '-')
	{
		int c = s.length();
		Integer n = 0;
		for (int i = 0; i < c; i++)
		{
			int m = s[i] - '0';
			n = n + m;

			if (i < c - 1)
				n = n * 10;
		}
		return n;
	}
	else
	{
		int c = s.length();
		Integer n = 0;
		for (int i = 1; i < c; i++)
		{
			int m = s[i] - '0';
			n = n + m;

			if (i < c - 1)
				n = n * 10;
		}
		n = -n;
		return n;
	}

}



//字符串转vector函数（V是全局变量，使用时自动完成清空）
void stv(string s)
{
	V.clear();
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		V.push_back(s[i] - '0');
	}

}

//取位函数（因为数较大，不能用一般的log）
string DecToBinary(const string &dec)
{
	int i, len, sta;
	stack<int> s;

	len = dec.length();
	int *num = new int[len + 1];

	for (i = 0; i < len; ++i)
	{
		num[i] = dec[i] - '0';
	}

	while (true)
	{
		sta = len;
		for (i = 0; i < len; ++i)
		{
			if (num[i] != 0)
			{
				sta = i;
				break;
			}

		}

		if (sta == len) break;

		int remain = 0;
		for (i = sta; i < len; ++i)
		{
			remain = remain * 10 + num[i];
			num[i] = remain / 2;
			remain = remain % 2;
		}
		s.push(remain);
	}

	string ans;
	while (!s.empty())
	{
		ans += s.top() + '0';
		s.pop();
	}
	if (ans.length() == 0)
		ans = "0";

	delete[] num;
	//cout << endl << "长度为：" << ans.length();
	return ans;

}

//字符串切割函数,start是起始位置，n为长度
string cut(string s1, int start, int n)
{
	string ans;
	for (int i = start; n > 0; n--, i++)
	{
		ans = ans + s1[i];
	}
	return ans;
}

//大数幂模运算取余（下方函数调用该函数）

Integer mypow(Integer a, Integer k)
{
	a %= tran(its(p));
	Integer res = 1;

	for (int i = 0; i < k; i++)
	{
		res = res * a;
		res %= tran(its(p));
	}

	return res;
}


//大数幂模运算
Integer superPow(Integer a, vector<int>& b)
{
	if (b.empty())
		return 1;
	int last = b.back();
	b.pop_back();

	Integer part1 = mypow(a, last);
	Integer part2 = mypow(superPow(a, b), 10);

	return (part1 * part2) % tran1(its(p));
}


//初始化函数，随机生成p，g，q
void Init()
{
	PrimeAndGenerator pg;
	pg.Generate(1, rng, 512, 511);
	p = pg.Prime();
	q = pg.SubPrime();
	g = pg.Generator();

}

//生成序列号
void sec()
{
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		SN.push_back(i);
	}
	// 产生[vec.begin(), vec.end())之间的随机序列，前闭后开
	random_shuffle(SN.begin(), SN.end());
}

//二进制转十进制
Integer BTD(string s)
{
	int len = s.length();
	Integer m = 0xffffffffffffffff;
	Integer n = 0;
	for (int i = 0; i < len; ++i)
	{

		if (s[i] == '1')
			n += ModularExponentiation(2, len - 1 - i, m);
	}
	return n;
}

//生成私钥和公钥的函数
void Key_gen()
{
	for (int i = 0; i < n; i++)
	{
		DH d(p, q, g);
		SecByteBlock Pri(d.PrivateKeyLength());
		SecByteBlock Pub(d.PublicKeyLength());
		d.GenerateKeyPair(rng, Pri, Pub);
		p1[i] = Pri;
		p2[i] = Pub;
	}
}

//签名初始化步骤数制转换
void temp_SigKeyGen(int i)
{
	string s1 = (hmac<SHA__256>(its(pr[i]) + its(1), "0"));
	Integer R1 = ModularExponentiation(tran1(its(g)), tran1(s1), p);

	temp_j = its(1);
	temp_s1 = tran1(s1);
	temp_R1 = its(R1);
	temp_pr[i] = its(pr[i]);
	temp_g = tran1(its(g));
	temp_value1 = tran1(hmac<SHA__256>(temp_R1, "0"));
	temp_value2 = tran1(hmac<SHA__256>(temp_R1, "1"));
	temp_z = tran1(hmac<SHA__256>(temp_pr[i] + temp_j, "1"));
}

//签名过程一：签名初始化步骤
void SigKeyGen(int i)
{
	for (int j = 0; j < K; j++)
	{
		string s1 = (hmac<SHA__256>(temp_pr[i] + temp_j, "0"));
		Integer R1 = ModularExponentiation(temp_g, temp_s1, p);
		string z = hmac<SHA__256>(temp_pr[i] + temp_j, "1");
		string value1 = hmac<SHA__256>(temp_R1, "0");
		string value2 = hmac<SHA__256>(temp_R1, "1");
		gamma[i][j] = temp_z ^ temp_value1;
		beta[i][j] = temp_value2;
	}
}


////签名过程一：签名初始化步骤
//void SigKeyGen(int i)
//{
//
//	for (int j = 0; j < K; j++)
//	{
//		string s1 = (hmac<SHA__256>(its(pr[i]) + its(j), "0"));
//		Integer R1 = ModularExponentiation(tran1(its(g)), tran1(s1), p);
//		Integer z = tran1(hmac<SHA__256>(its(pr[i]) + its(j), "1"));
//		gamma[i][j] = z ^ tran1(hmac<SHA__256>(its(R1), "0"));
//		beta[i][j] = tran1(hmac<SHA__256>(its(R1), "1"));
//	}
//}



//签名计算步骤数制转换
void temp_Sig_Com(int i, int j)
{
	for (int t = 0; t < n; t++)
	{
		//s = s + DecToBinary(its(space[i][t]));
		temp_s = temp_s + its(space[i][t]);
	}
	temp_num = DecToBinary(its(q)).length();
	temp_L[i] = tran1(L[i]);
	temp_pr[i] = its(pr[i]);
	temp_j = its(j);
	temp_part1 = tran1(hmac<SHA__256>(its(pr[i]) + its(j), "1"));
	temp_C[i][j] = its(C[i][j]);
	temp_part2 = tran1(hmac<SHA__256>(its(C[i][j]) + R[i], "0"));
	Integer b = tran1(hmac<SHA__256>(its(C[i][j]) + R[i], "0"));
	temp_part3 = tran1(hmac<SHA__256>(its(pr[i]) + its(j), "0"));
}


//签名步骤二：签名计算步骤(剔除数制转换)
void Sig_Com(int i, int j)
{

	string s = temp_s;
	int num = temp_num;
	int rlen = s.length() - num;
	L[i] = cut(s, 0, num);
	R[i] = cut(s, num, rlen);
	hmac<SHA__256>(temp_pr[i] + temp_j, "1");
	C[i][j] = temp_L[i] ^ temp_part1;
	hmac<SHA__256>(temp_C[i][j] + R[i], "0");
	Integer b = temp_part2;
	hmac<SHA__256>(temp_pr[i] + temp_j, "0");
	S[i][j] = temp_part3 - (b % q) * (pr[i] % q);

}



////签名步骤二：签名计算步骤
//void Sig_Com(int i, int j)
//{
//
//	string s;
//
//	for (int t = 0; t < n; t++)
//	{
//		//s = s + DecToBinary(its(space[i][t]));
//		s = s + its(space[i][t]);
//	}
//
//	int num = DecToBinary(its(q)).length();
//
//	int rlen = s.length() - num;
//	L[i] = cut(s, 0, num);
//	R[i] = cut(s, num, rlen);
//
//	C[i][j] = tran1(L[i]) ^ tran1(hmac<SHA__256>(its(pr[i]) + its(j), "1"));
//	Integer b = tran1(hmac<SHA__256>(its(C[i][j]) + R[i], "0"));
//	S[i][j] = tran1(hmac<SHA__256>(its(pr[i]) + its(j), "0")) - (b % q) * (pr[i] % q);
//	
//}


//签名认证数制转换
bool temp_Sig_ver(int i, int j)
{
	temp_pr[i] = its(pr[i]);
	temp_j = its(j);
	string s1 = hmac<SHA__256>(its(pr[i]) + its(j), "0");

	temp_s1 = tran1(s1);
	Integer r1 = ModularExponentiation(pu[i], tran1(s1), p);
	Integer r2 = ModularExponentiation(g, tran1(s1), p);
	Sig_r = ModularMultiplication(r1, r2, p);
	temp_Sig_r = its(Sig_r);
}


//签名步骤三，签名认证步骤(剔除数制转换)
bool Sig_ver(int i, int j)
{
	string s1 = hmac<SHA__256>(temp_pr[i] + temp_j, "0");
	Integer r1 = ModularExponentiation(pu[i], temp_s1, p);
	Integer r2 = ModularExponentiation(g, temp_s1, p);
	Sig_r = ModularMultiplication(r1, r2, p);
	if (beta[i][j] != tran1(hmac<SHA__256>(temp_Sig_r, "1")))
	{
		return false;
	}
	else
	{
		return true;
	}
}

////签名步骤三，签名认证步骤
//bool Sig_ver(int i, int j)
//{
//	string s1 = hmac<SHA__256>(its(pr[i]) + its(j), "0");
//
//	Integer r1 = ModularExponentiation(tran1(its(pu[i])), tran1(s1), p);
//
//	Integer r2 = ModularExponentiation(tran1(its(g)), tran1(s1), p);
//
//	Sig_r = ModularMultiplication(r1, r2, p);
//
//	if (beta[i][j] != tran1(hmac<SHA__256>(its(Sig_r), "1")))
//	{
//		return false;
//	}
//	else
//	{
//		return true;
//	}
//}




//签名还原步骤
void Sig_rec(int i, int j)
{
	
	if (C[i][j] < 0)
		M1[i] = -(gamma[i][j] ^ trans(hmac<SHA__256>(DecToBinary(its(Sig_r)), "0")) ^ C[i][j]);
	else
		M1[i] = gamma[i][j] ^ trans(hmac<SHA__256>(DecToBinary(its(Sig_r)), "0")) ^ C[i][j];
	string m = its(M1[i]) + R[i];

	Integer temp = 0;
	for (int t = 0; t < n; t++)
	{
		Integer len = its(space[i][t]).length();
		M2[i][t] = tran1(cut(m, tran(its(temp)), tran(its(len))));
		temp = temp + len;
	}
	
}


//生成协商值的函数
void Con_gen()
{

	DH d(p, q, g);
	SecByteBlock t1(d.AgreedValueLength()), t2(d.AgreedValueLength());
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			d.Agree(t1, p1[i], p2[j]);
			Integer A;
			A.Decode(t1.BytePtr(), t1.size());
			con[i][j] = A;
		}
	}
}

//解码函数，将之前保存的私钥公钥地址中存储的内容解码，保存到Integer型的两个数组中
void Decode()
{

	Integer A, B;
	for (int i = 0; i < n; i++)
	{
		A.Decode(p1[i].BytePtr(), p1[i].size());
		B.Decode(p2[i].BytePtr(), p2[i].size());
		pr[i] = A;
		pu[i] = B;
	}
}

//这一部分是将计算加密空间向量中的数值转换步骤提出来，减少时间
void temp_tran(int i)
{
	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n; k++)
		{
			con_temp[i][k] = its(con[i][k]);
			j_temp[j] = its(j);
			string s3 = hmac<SHA__256>(j_temp[j], con_temp[i][k]);
			num_temp[j][k] = tran1(s3);
		}
	}
}


//这一部分是计算加密空间向量,参数为用户序号，计算出的是该用户加密向量每一列的值Hi[l]
void key_space(int i)
{
	for (int j = 0; j < n; j++)
	{
		Integer sum = 0;
		for (int k = 0; k < n; k++)
		{
			string s3 = hmac<SHA__256>(j_temp[j], con_temp[i][k]);

			//num 是hmac加密后的数
			Integer num = num_temp[j][k];

			if (i == k)
			{
				//这里按理说应该是加num，但是为了检验是否ΣH'=0，暂时先加0
				sum = sum + 0;
			}

			else if (i < k)
			{
				sum = (sum + -num) % M;
			}

			else
			{
				sum = (sum + num) % M;
			}
		}
		//space[i][j]表示 Hi（j）
		space[i][j] = sum;
	}

}

//生成所有加密空间向量
void ev()
{
	for (int i = 0; i < n; i++)
	{
		key_space(i);
	}
}

//生成指定用户（单个用户）的加密向量的值
void ev_single(int x)
{
	key_space(x);
}


//累加检验，看是否为ΣH为0
void check()
{
	Integer sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sum = sum + space[i][j];
		}

	}
	cout << "累加值为：" << sum << endl << endl;
}

//输出函数，输出的内容保存在项目路径下的test.xls中
void Output()
{
	//更改后缀可改变存储方式
	outfile.open("test.xls");

	//输出p、g的值
	outfile << "p、g的值为：" << endl;
	outfile << p << " " << g << endl;
	outfile << endl;

	//输出n个私钥
	outfile << "用户私钥值为：" << endl;
	for (int i = 0; i < n; i++)
	{
		outfile << pr[i] << endl;
	}
	outfile << endl;

	//输出n个公钥
	outfile << "用户公钥值为：" << endl;
	for (int i = 0; i < n; i++)
	{
		outfile << pu[i] << endl;
	}
	outfile << endl;

	//输出n*n对协商值
	outfile << "协商值为：" << endl;
	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n; j++)
		{
			outfile << con[i][j] << " ";
		}
		outfile << endl;
	}

}

//扩展欧几里得、CRT合并多维数据
Integer extended_euclid(Integer a, Integer b, Integer &x, Integer  &y) 
{
       Integer d;
       if(b == 0) 
       {x = 1; y = 0; return a;}
       d = extended_euclid(b, a % b, y, x);
       y -= a / b * x;
       return d;   
}
Integer chinese_remainder(int user, int len) {

       Integer  d, x, y, m, n, ret;
       ret = 0; n = 1;
	   for (int i = 0; i < len; i++)
	   {
			 n = n * w[i];  
	   }
       for(int  i = 0; i < len ;i++) 
       {
            m = n / w[i];
            d = extended_euclid(w[i], m, x, y);
			ret = (ret + y * m * b[user][i]) % n % M ;
       }
       return (n + ret % n) % n % M;
}


//计算EV向量的函数
void cul_ev(int user)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == user)
			EV[user][i] = (space[user][i] + crt_1[user]);
		else
			EV[user][i] = space[user][i];
	}
}
 
 //聚合函数
 void agg()
 {

	 for (int i = 0; i < n; i++)
	 {
		 for (int j = 0; j < n; j++)
		 {
			 AG[i] = (AG[i] + EV[j][i]) % M;

			 if (i == j)
			 {
				 //模拟减去自身协商值的时间
				 AG[i] = AG[i] - 1;
			 }
		 }
	 }
 }
 


//还原多维数据的函数
void crt_recover(int user)
{
	for (int i = 0; i < DM; i++)
	{
		crt_2[user][i] = crt_1[user] % w[i];

		////查看是否成功还原
		//cout << crt_1[user] << endl;
		//cout << w[i] << endl;
		//cout << crt_2[user][i]<<endl;
	}
}


int main()
{
		//cout << M;
		cout << "请输入用户数：";
		cin >> n;
		cout << endl;

		//初始化时间统计变量
		Timer tm(TimerBase::MILLISECONDS);

		tm.StartTimer();
		Init();
		sec();
		cout << "初始化花费的时间（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;
	
		tm.StartTimer();
		Key_gen();
		cout << "生成公钥私钥花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;
	
		tm.StartTimer();
		Con_gen();
		cout << "生成协商值花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()/n << endl << endl;
	

		temp_tran(0);
		tm.StartTimer();
		key_space(0);
		cout << "生成单用户加密空间需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;


		////计算生成加密空间时间的平均值
		//double sum_H = 0;
		//for (int i = 0; i < 10; i++)
		//{
		//	tm.StartTimer();

		//	ev_single(0);

		//	sum_H = sum_H + tm.ElapsedTimeAsDouble();

		//	//cout << "生成加密空间需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() / n << endl << endl;
		//}
		//cout << "加密空间平均值为:" << sum_H / 10 << endl;


		tm.StartTimer();
		Decode();
		Output();
		cout << "解码并输出花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;
	
		////累加检验函数，经检验，加密函数无误
		//check();
	
	//签名过程
		temp_SigKeyGen(1);
		tm.StartTimer();
		SigKeyGen(1);
		cout << "初始化一个用户签名的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;

		temp_Sig_Com(1, 0);
		tm.StartTimer();
		Sig_Com(1, 0);
		cout << "计算一个用户签名的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()*n << endl << endl;

		temp_Sig_ver(1, 0);
		tm.StartTimer();
		Sig_ver(1, 0);
		cout << "用户验签的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()*(n) << endl << endl;

		tm.StartTimer();
		Sig_rec(1, 0);
		cout << "还原一个用户签名的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()*n << endl << endl;


		//tm.StartTimer();
		//string s1 = its(con[0][0]);
		//cout << "执行一次its的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;

		//tm.StartTimer();
		//string s2 = hmac<SHA__256>(s1, "1");
		//cout << "执行一次hmac加密的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;

		//tm.StartTimer();
		//Integer tempp = tran1(s2);
		//cout << "执行一次tran1的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;

		
		////给CRT中的b赋值，1、2、4、8位
		//for (int i = 0; i < n; i++)
		//{
		//	//cout << "请输入第" << i << "位用户的16维数据" << endl << endl;
		//	for (int j = 0; j < DM; j++)
		//	{
		//		//b[i][j] = 128 + j;

		//		b[i][j] = 32768 + j;

		//		//b[i][j] = j % 4;

		//		//b[i][j] = j % 2;

		//	}
		//}

		//CRT与被除数相同位数
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < DM; j++)
			{
				b[i][0] = 2325;
				b[i][1] = 11;
				b[i][2] = 2302;
				b[i][3] = 5850;
				b[i][4] = 500;
				b[i][5] = 9;
			}
		}

	
		tm.StartTimer();
		for (int i = 0; i < n; i++)
		{
			crt_1[i] = chinese_remainder(i, DM);
		}
		cout << "单用户的多维数据（16维）转换为一维的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;


		//向量加上降维之后的数据
		for (int i = 0; i < n; i++)
		{
			cul_ev(i);
		}
		

		tm.StartTimer();
		agg();
		cout << "聚合累加的时间为：" << tm.ElapsedTimeAsDouble() << endl << endl;


		tm.StartTimer();
		for (int i = 0; i < n; i++)
		{
			crt_recover(i);
		}
		cout << "单用户的一维数据还原多维所需的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()/n << endl << endl;


	getchar();
	getchar();
	return 0;

}


