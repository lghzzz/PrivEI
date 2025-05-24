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


//DM��ʾ�й�ʣ�ඨ�����û����ݵ�ά��
#define MAX 1000
#define DM 6



using namespace std;
using namespace CryptoPP;


//�ļ�������
ofstream outfile;


//pr��pu����Integer���ͱ������֮���˽Կ����Կ��con�洢������Э��ֵ
//p1��p2���Ե�ַ����ʽ��SecByteBlock������˽Կ�͹�Կ��Ŀ�����ڷ���ʹ�ÿ��е�agreeЭ�̺���
int n;
Integer pr[MAX];
Integer pu[MAX];
Integer con[MAX][MAX];

SecByteBlock p1[MAX];
SecByteBlock p2[MAX];

//space�洢���ܿռ�,���ĺ����ǵ�I���û��ĵ�J�еĹ�ϣֵ����H
Integer space[MAX][MAX];

//��������������p,q,g
AutoSeededRandomPool rng;
Integer p, q, g;
Integer K = 1;

//��Щ���鶼�����ǩ��������Ҫ���м���������M2��ǩ����֤֮��洢��ֵ
Integer gamma[MAX][MAX], beta[MAX][MAX];
string L[MAX], R[MAX];
Integer C[MAX][MAX], S[MAX][MAX];
Integer M1[MAX], M2[MAX][MAX];
Integer Sig_r;
vector<int> V;

//�����ַ���תInteger����tran1
Integer tran1(string s);

//���к�
vector<int> SN;

//�й�ʣ�ඨ�������ͳ�����ģ����
typedef long long llong;
Integer b[MAX][DM];


//�й�ʣ�ඨ��W��ֵ
// 16ά
//Integer w[DM] = { 131,137 ,139 ,149 ,151 ,157 ,163 ,167 ,173 ,179 ,181 ,191 ,193 ,197 ,199 ,211 };
//Integer w[DM] = {32771,32779,32783 ,32789, 32797, 32801, 32803, 32831, 32833, 32839, 32843, 32869, 32887, 32909, 32911,32917};
//Integer w[DM] = {tran1("2332913579"),tran1("3537815783"),tran1("3901918367"),tran1("3521966627"),tran1("4041359759"),tran1("2560834439"),tran1("3927551339"),tran1("3252618827"),tran1("4068467087"),tran1("2777096207"),tran1("2846247707"),tran1("4060407383"),tran1("2844487307"),tran1("2201980343"),tran1("2499728207"),tran1("3358379183") };
//Integer w[DM] = {tran1("14799980878431137483"),tran1("11375890615488983567"),tran1("17946625525685077583"),tran1("11072502421788333047"),tran1("14391117850104244559"),tran1("14507098390601505203"),tran1("11691624821837589599"),tran1("14908258777734559379"),tran1("11144752929418587539"),tran1("10787199373909830083"),tran1("13286396365882500647"),tran1("17178023310558063599"),tran1("13627461406213581503"),tran1("13012120592205740207"),tran1("16201609614510235667"),tran1("17962597866526172243") };

//8ά
//Integer w[DM] = { 131,137 ,139 ,149 ,151 ,157 ,163 ,167};
Integer w[DM] = {32771,32779,32783 ,32789, 32797, 32801};
//Integer w[DM] = {tran1("2332913579"),tran1("3537815783"),tran1("3901918367"),tran1("3521966627"),tran1("4041359759"),tran1("2560834439")};
//Integer w[DM] = {tran1("14799980878431137483"),tran1("11375890615488983567"),tran1("17946625525685077583"),tran1("11072502421788333047"),tran1("14391117850104244559"),tran1("14507098390601505203"),tran1("11691624821837589599"),tran1("14908258777734559379") };

//4ά
//Integer w[DM] = {131,137 ,139 ,149};
//Integer w[DM] = {32771,32779,32783 ,32789};
//Integer w[DM] = {tran1("2332913579"),tran1("3537815783"),tran1("3901918367"),tran1("3521966627")};
//Integer w[DM] = { tran1("14799980878431137483"),tran1("11375890615488983567"),tran1("17946625525685077583"),tran1("11072502421788333047")};



//EV������crt_1��mbi,crt_2�ǻ�ԭ���ÿ���û�ÿ��ά�ȵ�����mil,agg�����վۺϺ���
Integer EV[MAX][MAX];
Integer crt_1[MAX];
Integer crt_2[MAX][16];
Integer AG[MAX];

//��ȫ���� 128λ
string secur = "340282366920938463463374607431768211456";
Integer M = tran1(secur);


//������ܿռ���ֵת�����м����
string con_temp[MAX][MAX];
string j_temp[MAX];
Integer num_temp[MAX][MAX];

//ǩ���㷨����ת���м����
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


//Integer��ת�ַ���
string its(Integer n)
{
	ostringstream stream;
	stream << n;  //nΪint����
	string ans = stream.str();
	int l = ans.length();
	ans.erase(l - 1, 1);
	return ans;
}

//����ת�ַ���
string its(int n)

{
	ostringstream stream;

	stream << n;  //nΪint����

	return stream.str();

}

//�ַ���תInteger�ͣ�ʮ�����ƣ�
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

//�ַ���ת����
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

//�ַ���תInteger��(10���ƣ�
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



//�ַ���תvector������V��ȫ�ֱ�����ʹ��ʱ�Զ������գ�
void stv(string s)
{
	V.clear();
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		V.push_back(s[i] - '0');
	}

}

//ȡλ��������Ϊ���ϴ󣬲�����һ���log��
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
	//cout << endl << "����Ϊ��" << ans.length();
	return ans;

}

//�ַ����и��,start����ʼλ�ã�nΪ����
string cut(string s1, int start, int n)
{
	string ans;
	for (int i = start; n > 0; n--, i++)
	{
		ans = ans + s1[i];
	}
	return ans;
}

//������ģ����ȡ�ࣨ�·��������øú�����

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


//������ģ����
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


//��ʼ���������������p��g��q
void Init()
{
	PrimeAndGenerator pg;
	pg.Generate(1, rng, 512, 511);
	p = pg.Prime();
	q = pg.SubPrime();
	g = pg.Generator();

}

//�������к�
void sec()
{
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		SN.push_back(i);
	}
	// ����[vec.begin(), vec.end())֮���������У�ǰ�պ�
	random_shuffle(SN.begin(), SN.end());
}

//������תʮ����
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

//����˽Կ�͹�Կ�ĺ���
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

//ǩ����ʼ����������ת��
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

//ǩ������һ��ǩ����ʼ������
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


////ǩ������һ��ǩ����ʼ������
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



//ǩ�����㲽������ת��
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


//ǩ���������ǩ�����㲽��(�޳�����ת��)
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



////ǩ���������ǩ�����㲽��
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


//ǩ����֤����ת��
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


//ǩ����������ǩ����֤����(�޳�����ת��)
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

////ǩ����������ǩ����֤����
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




//ǩ����ԭ����
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


//����Э��ֵ�ĺ���
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

//���뺯������֮ǰ�����˽Կ��Կ��ַ�д洢�����ݽ��룬���浽Integer�͵�����������
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

//��һ�����ǽ�������ܿռ������е���ֵת�����������������ʱ��
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


//��һ�����Ǽ�����ܿռ�����,����Ϊ�û���ţ���������Ǹ��û���������ÿһ�е�ֵHi[l]
void key_space(int i)
{
	for (int j = 0; j < n; j++)
	{
		Integer sum = 0;
		for (int k = 0; k < n; k++)
		{
			string s3 = hmac<SHA__256>(j_temp[j], con_temp[i][k]);

			//num ��hmac���ܺ����
			Integer num = num_temp[j][k];

			if (i == k)
			{
				//���ﰴ��˵Ӧ���Ǽ�num������Ϊ�˼����Ƿ�H'=0����ʱ�ȼ�0
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
		//space[i][j]��ʾ Hi��j��
		space[i][j] = sum;
	}

}

//�������м��ܿռ�����
void ev()
{
	for (int i = 0; i < n; i++)
	{
		key_space(i);
	}
}

//����ָ���û��������û����ļ���������ֵ
void ev_single(int x)
{
	key_space(x);
}


//�ۼӼ��飬���Ƿ�Ϊ��HΪ0
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
	cout << "�ۼ�ֵΪ��" << sum << endl << endl;
}

//�����������������ݱ�������Ŀ·���µ�test.xls��
void Output()
{
	//���ĺ�׺�ɸı�洢��ʽ
	outfile.open("test.xls");

	//���p��g��ֵ
	outfile << "p��g��ֵΪ��" << endl;
	outfile << p << " " << g << endl;
	outfile << endl;

	//���n��˽Կ
	outfile << "�û�˽ԿֵΪ��" << endl;
	for (int i = 0; i < n; i++)
	{
		outfile << pr[i] << endl;
	}
	outfile << endl;

	//���n����Կ
	outfile << "�û���ԿֵΪ��" << endl;
	for (int i = 0; i < n; i++)
	{
		outfile << pu[i] << endl;
	}
	outfile << endl;

	//���n*n��Э��ֵ
	outfile << "Э��ֵΪ��" << endl;
	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n; j++)
		{
			outfile << con[i][j] << " ";
		}
		outfile << endl;
	}

}

//��չŷ����á�CRT�ϲ���ά����
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


//����EV�����ĺ���
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
 
 //�ۺϺ���
 void agg()
 {

	 for (int i = 0; i < n; i++)
	 {
		 for (int j = 0; j < n; j++)
		 {
			 AG[i] = (AG[i] + EV[j][i]) % M;

			 if (i == j)
			 {
				 //ģ���ȥ����Э��ֵ��ʱ��
				 AG[i] = AG[i] - 1;
			 }
		 }
	 }
 }
 


//��ԭ��ά���ݵĺ���
void crt_recover(int user)
{
	for (int i = 0; i < DM; i++)
	{
		crt_2[user][i] = crt_1[user] % w[i];

		////�鿴�Ƿ�ɹ���ԭ
		//cout << crt_1[user] << endl;
		//cout << w[i] << endl;
		//cout << crt_2[user][i]<<endl;
	}
}


int main()
{
		//cout << M;
		cout << "�������û�����";
		cin >> n;
		cout << endl;

		//��ʼ��ʱ��ͳ�Ʊ���
		Timer tm(TimerBase::MILLISECONDS);

		tm.StartTimer();
		Init();
		sec();
		cout << "��ʼ�����ѵ�ʱ�䣨���룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
	
		tm.StartTimer();
		Key_gen();
		cout << "���ɹ�Կ˽Կ���ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
	
		tm.StartTimer();
		Con_gen();
		cout << "����Э��ֵ���ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()/n << endl << endl;
	

		temp_tran(0);
		tm.StartTimer();
		key_space(0);
		cout << "���ɵ��û����ܿռ���Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;


		////�������ɼ��ܿռ�ʱ���ƽ��ֵ
		//double sum_H = 0;
		//for (int i = 0; i < 10; i++)
		//{
		//	tm.StartTimer();

		//	ev_single(0);

		//	sum_H = sum_H + tm.ElapsedTimeAsDouble();

		//	//cout << "���ɼ��ܿռ���Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() / n << endl << endl;
		//}
		//cout << "���ܿռ�ƽ��ֵΪ:" << sum_H / 10 << endl;


		tm.StartTimer();
		Decode();
		Output();
		cout << "���벢������ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
	
		////�ۼӼ��麯���������飬���ܺ�������
		//check();
	
	//ǩ������
		temp_SigKeyGen(1);
		tm.StartTimer();
		SigKeyGen(1);
		cout << "��ʼ��һ���û�ǩ����ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;

		temp_Sig_Com(1, 0);
		tm.StartTimer();
		Sig_Com(1, 0);
		cout << "����һ���û�ǩ����ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()*n << endl << endl;

		temp_Sig_ver(1, 0);
		tm.StartTimer();
		Sig_ver(1, 0);
		cout << "�û���ǩ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()*(n) << endl << endl;

		tm.StartTimer();
		Sig_rec(1, 0);
		cout << "��ԭһ���û�ǩ����ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()*n << endl << endl;


		//tm.StartTimer();
		//string s1 = its(con[0][0]);
		//cout << "ִ��һ��its��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;

		//tm.StartTimer();
		//string s2 = hmac<SHA__256>(s1, "1");
		//cout << "ִ��һ��hmac���ܵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;

		//tm.StartTimer();
		//Integer tempp = tran1(s2);
		//cout << "ִ��һ��tran1��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;

		
		////��CRT�е�b��ֵ��1��2��4��8λ
		//for (int i = 0; i < n; i++)
		//{
		//	//cout << "�������" << i << "λ�û���16ά����" << endl << endl;
		//	for (int j = 0; j < DM; j++)
		//	{
		//		//b[i][j] = 128 + j;

		//		b[i][j] = 32768 + j;

		//		//b[i][j] = j % 4;

		//		//b[i][j] = j % 2;

		//	}
		//}

		//CRT�뱻������ͬλ��
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
		cout << "���û��Ķ�ά���ݣ�16ά��ת��Ϊһά��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;


		//�������Ͻ�ά֮�������
		for (int i = 0; i < n; i++)
		{
			cul_ev(i);
		}
		

		tm.StartTimer();
		agg();
		cout << "�ۺ��ۼӵ�ʱ��Ϊ��" << tm.ElapsedTimeAsDouble() << endl << endl;


		tm.StartTimer();
		for (int i = 0; i < n; i++)
		{
			crt_recover(i);
		}
		cout << "���û���һά���ݻ�ԭ��ά�����ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()/n << endl << endl;


	getchar();
	getchar();
	return 0;

}


