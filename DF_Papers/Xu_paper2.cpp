//#include "HMAC_256.h"
//#include "SHA_256.h"
//#include<integer.h>
//#include<iostream>
//#include<osrng.h>
//#include<nbtheory.h>
//#include<dh.h>
//#include<hrtimer.h>
//#include<secblock.h>
//#include<files.h>
//#include<math.h>
//#include<cmath>
//#include<fstream>
//#include<string>
//#include<sstream>
//#include<vector>
//#include<stack>
//#include <algorithm>
//#include <ctime>	
//#include<ida.h>
//#include<channels.h>
//#include<hex.h>
//#include<hmac.h>
//#include<sha3.h>
//#include<aes.h>
//#include<modes.h>
//
//#define MAX 1000
//
//using namespace std;
//using namespace CryptoPP;
//
//
////�ļ�������
//ofstream of;
//
////�û���
//int n;
//
////s�Ĺ�˽Կ��c�Ĺ�˽Կ
//SecByteBlock ss[MAX];
//SecByteBlock sp[MAX];
//
//
////s��Э��ֵ��c��Э��ֵ
//Integer scon[MAX][MAX];
//
//Integer SN_f[MAX][MAX];
//
////s��˽Կת���ͣ�c��˽Կת����
//Integer ss1[MAX];
//Integer sp1[MAX];
//
//
////EI�洢���ܿռ�,���ĺ����ǵ�I���û���eֵ,mes�ǽ��ܺ��зָ�ÿ���û�����Ϣ
//string EI[MAX];
//Integer mes[MAX] = {0};
//Integer EI1[MAX];
//
//
////Sig_M��ʾǩ�������е�Mi��Sig_S��ʾǩ�������е�si
//string Sig_E[MAX];
//Integer Sig_S[MAX];
//
//
////V�����ַ���תvector��SN���������ɵ����к�
//vector<int> V;
//vector<int> SN;
//
////��������������p,q,g
//AutoSeededRandomPool rng;
//Integer p, q, g;
//Integer K = 5;
//Integer k;
//
////�û���Ϣ��ʱ��tm��Ϊ�򻯣�����ʱ��tm�̶�Ϊ100,eagg�Ǿۺ�֮������ݣ�δ�����и���ܵģ�
//string mi[MAX];
//Integer tm = 100;
//Integer eagg[MAX][MAX];
//
////�����ۼ�ֵ����ʱ����rain
//Integer rain;
//
////������ܿռ���ֵת�����м����
//string scon_temp[MAX][MAX];
//string j_temp[MAX][MAX];
//Integer num_temp1[MAX][MAX];
//Integer num_temp2[MAX][MAX];
//string temp_temp[MAX];
//string temp_v;
//Integer temp_e;
//
////��֤ǩ�����м����
//Integer temp_Sig_E[MAX];
//string temp_s;
//
//
////Integer��ת�ַ���
//string its(Integer n)
//{
//	ostringstream stream;
//
//	stream << n;  //nΪinteger����
//
//	return stream.str();
//}
//
//
////����ת�ַ���
//string its(int n)
//
//{
//	ostringstream stream;
//
//	stream << n;  //nΪint����
//
//	return stream.str();
//
//}
//
////�ַ���תInteger�ͣ�ʮ�����ƣ�
//Integer trans(string s)
//{
//	Integer c = s.length();
//	Integer n = 0;
//	for (int i = 0; i < c; i++)
//	{
//		if (s[i] >= '0' && s[i] <= '9')
//		{
//			Integer m = s[i] - '0';
//			n = n + m;
//		}
//		else
//		{
//			Integer m = s[i] - 'a' + 10;
//			n = n + m;
//		}
//		if (i < c - 1)
//			n = n * 16;
//	}
//	return n;
//}
//
////�ַ���ת����
//int tran(string s)
//{
//
//	if (s[0] != '-')
//	{
//		int c = s.length();
//		int n = 0;
//		for (int i = 0; i < c; i++)
//		{
//			int m = s[i] - '0';
//			n = n + m;
//
//			if (i < c - 1)
//				n = n * 10;
//		}
//		return n;
//	}
//	else
//	{
//		int c = s.length();
//		int n = 0;
//		for (int i = 1; i < c; i++)
//		{
//			int m = s[i] - '0';
//			n = n + m;
//
//			if (i < c - 1)
//				n = n * 10;
//		}
//		n = -n;
//		return n;
//	}
//
//}
//
////�ַ���תInteger��(10���ƣ�
//Integer tran1(string s)
//{
//
//	if (s[0] != '-')
//	{
//		int c = s.length();
//		Integer n = 0;
//		for (int i = 0; i < c; i++)
//		{
//			int m = s[i] - '0';
//			n = n + m;
//
//			if (i < c - 1)
//				n = n * 10;
//		}
//		return n;
//	}
//	else
//	{
//		int c = s.length();
//		Integer n = 0;
//		for (int i = 1; i < c; i++)
//		{
//			int m = s[i] - '0';
//			n = n + m;
//
//			if (i < c - 1)
//				n = n * 10;
//		}
//		n = -n;
//		return n;
//	}
//
//}
//
////�ַ���תvector������V��ȫ�ֱ�����ʹ��ʱ�Զ������գ�
//void stv(string s)
//{
//	V.clear();
//	int len = s.length();
//	for (int i = 0; i < len; i++)
//	{
//		V.push_back(s[i] - '0');
//	}
//
//}
//
////ȡλ��������Ϊ���ϴ󣬲�����һ���log��
//string DecToBinary(const string &dec)
//{
//	int i, len, sta;
//	stack<int> s;
//
//	len = dec.length();
//	int *num = new int[len + 1];
//
//	for (i = 0; i < len; ++i)
//	{
//		num[i] = dec[i] - '0';
//	}
//
//	while (true)
//	{
//		sta = len;
//		for (i = 0; i < len; ++i)
//		{
//			if (num[i] != 0)
//			{
//				sta = i;
//				break;
//			}
//
//		}
//
//		if (sta == len) break;
//
//		int remain = 0;
//		for (i = sta; i < len; ++i)
//		{
//			remain = remain * 10 + num[i];
//			num[i] = remain / 2;
//			remain = remain % 2;
//		}
//		s.push(remain);
//	}
//
//	string ans;
//	while (!s.empty())
//	{
//		ans += s.top() + '0';
//		s.pop();
//	}
//	if (ans.length() == 0)
//		ans = "0";
//
//	delete[] num;
//	//cout << endl << "����Ϊ��" << ans.length();
//	return ans;
//
//}
//
////�ַ����и��,start����ʼλ�ã�nΪ����
//string cut(string s1, int start, int n)
//{
//	string ans;
//	for (int i = start; n > 0; n--, i++)
//	{
//		ans = ans + s1[i];
//	}
//	return ans;
//}
//
//
////������ģ����ȡ�ࣨ�·��������øú�����
//Integer mypow(Integer a, Integer k)
//{
//	a %= tran(its(p));
//	Integer res = 1;
//
//	for (int i = 0; i < k; i++)
//	{
//		res = res * a;
//		res %= tran(its(p));
//	}
//
//	return res;
//}
//
////������ģ����
//Integer superPow(Integer a, vector<int>& b)
//{
//	if (b.empty())
//		return 1;
//	int last = b.back();
//	b.pop_back();
//
//	Integer part1 = mypow(a, last);
//	Integer part2 = mypow(superPow(a, b), 10);
//	return (part1 * part2) % tran1(its(p));
//}
//
//Integer BTD(string s)
//{
//	int len = s.length();
//	Integer m = 0xffffffffffffffff;
//	Integer n = 0;
//	for (int i = 0; i < len; ++i)
//	{
//
//		if (s[i] == '1')
//			n += ModularExponentiation(2, len - 1 - i, m);
//	}
//	return n;
//}
//
//
////����������к�bi
//void sec()
//{
//	srand(time(0));
//	for (int i = 0; i < n; i++)
//	{
//		SN.push_back(i);
//	}
//	// ����[vec.begin(), vec.end())֮���������У�ǰ�պ�
//	random_shuffle(SN.begin(), SN.end());
//}
//
//
////��ʼ���������������p��g��q
//void Init()
//{
//	PrimeAndGenerator pg;
//	pg.Generate(1, rng, 512, 511);
//	p = pg.Prime();
//	q = pg.SubPrime();
//	g = pg.Generator();
//}
//
//
//
////����˽Կ�͹�Կ�ĺ���������s��c���ԣ�
//void Key_gen()
//{
//	for (int i = 0; i < n; i++)
//	{
//		DH d1(p, q, g);
//		SecByteBlock Pri(d1.PrivateKeyLength());
//		SecByteBlock Pub(d1.PublicKeyLength());
//		d1.GenerateKeyPair(rng, Pri, Pub);
//		ss[i] = Pri;
//		sp[i] = Pub;
//
//	}
//}
//
//
//
////����Э��ֵ�ĺ���
//void Con_gen()
//{
//	DH d1(p, q, g);
//	SecByteBlock t1(d1.AgreedValueLength()), t2(d1.AgreedValueLength());
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			d1.Agree(t1, ss[i], sp[j]);
//			Integer A;
//			A.Decode(t1.BytePtr(), t1.size());
//			scon[i][j] = A;
//
//		}
//	}
//}
//
////���뺯������֮ǰ�����˽Կ��Կ��ַ�д洢�����ݽ��룬���浽Integer�͵�����������
//void Decode()
//{
//	Integer A, B, C, D;
//	for (int i = 0; i < n; i++)
//	{
//		A.Decode(ss[i].BytePtr(), ss[i].size());
//		B.Decode(sp[i].BytePtr(), sp[i].size());
//		ss1[i] = A;
//		sp1[i] = B;
//
//	}
//}
//
//// //��һ�����ǽ�������ܿռ������е���ֵת�����������������ʱ��
//void temp_tran(int k)
//{
//	for (int i = 0; i < n; i++)
//	{
//		Integer temp;
//		for (int j = 0; j < n; j++)
//		{
//			if (i == SN[k])
//			{
//				scon_temp[i][j] = its(SN[k] + tm);
//				j_temp[i][j] = its(scon[k][SN[k]]);
//				string s3 = hmac<SHA__256>(scon_temp[i][j], j_temp[i][j]);
//				num_temp1[i][j] = tran1(s3);
//				num_temp2[i][j] = tran1(mi[k]);
//
//			}
//
//			else
//			{
//
//				scon_temp[i][j] = its(i + tm);
//				j_temp[i][j] = its(scon[k][j]);
//				string s3 = hmac<SHA__256>(scon_temp[i][j], j_temp[i][j]);
//				num_temp1[i][j] = tran1(s3);
//				num_temp2[i][j] = tran1(mi[k]);
//			}
//			temp = temp ^ num_temp1[i][j] ^ num_temp2[i][j];
//		}
//		temp_temp[k] = its(temp);
//	}
//}
//
//
//
////������ܿռ�����
//void key_space(int k)
//{
//	
//	for (int i = 0; i < n; i++)
//	{
//		Integer temp;
//		string ans;
//		for (int j = 0; j < n; j++)
//		{
//			if (i == SN[k])
//			{
//				//string s1 = its(SN[k] + tm);
//				//string s2 = its(scon[k][SN[k]]);
//				string s3 = hmac<SHA__256>(scon_temp[i][j], j_temp[i][j]);
//				temp = temp ^ num_temp1[i][j] ^ num_temp2[i][j];
//			}
//
//			else
//			{
//				//string s1 = its(i + tm);
//				//string s2 = its(scon[k][j]);
//				string s3 = hmac<SHA__256>(scon_temp[i][j], j_temp[i][j]);
//				temp = temp ^ num_temp1[i][j] ^ num_temp2[i][j];
//			}
//		}
//		EI[k] = EI[k] + temp_temp[k];
//	}
//}
//
//
////�������м��ܿռ�����
//void ev()
//{
//	for (int i = 0; i < n; i++)
//	{
//		key_space(i);
//	}
//}
//
////����ָ���û��������û����ļ���������ֵ
//void ev_single(int x)
//{
//	key_space(x);
//}
//
//
////���ݾۺ�
//void cul_ev()
//{
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			int len = EI[j].length();
//			int l = len / n;
//			//eagg[i][j] = tran1(cut(EI[i], j * l, l));
//			//cout << eagg[i][j];
//			//mes[i] = mes[i] ^ eagg[i][j];
//			mes[i] = mes[i] ^ rain;
//
//		}
//	}
//}
//
//
//////���ݾۺ�
////void cul_ev()
////{
////	//�۴����
////	for (int i = 0; i < n; i++)
////	{
////		eagg = eagg ^ EI1[i];
////	}
////
////	//�����зָֻ�
////	string temp = DecToBinary(its(eagg));
////	int len = temp.length();
////	int l = len / n;
////	for (int i = 0; i < n; i++)
////	{
////		mes[i] = BTD(cut(temp, i * l, l));
////	}
////}
//
//
////ǩ�������޳�����ת��
//void temp_sig_cul(int i)
//{
//	k = 3123123;
//	Integer v = ModularExponentiation(g, k, p);
//	temp_v = its(v);
//	string s = EI[i] + its(v);
//	string e = hmac<SHA__256>(s, "0");
//	temp_e = tran1(e);
//}
//
//
////Schnorrǩ�����̣�����Ĺ�˽Կʹ��֮ǰ��DH���ɵĹ�˽Կ����Ϣ��ʹ���û����ܿռ�EI[]
//void sig_cul(int i)
//{
//	k = 3123123;
//	Integer v = ModularExponentiation(g, k, p);
//	string s = EI[i]+ temp_v;
//	string e = hmac<SHA__256>(s, "0");
//
//	//�м����
//	Integer mid = ModularMultiplication(ss1[i], temp_e, q);
//	Integer S = ModularMultiplication(1, k - mid, q);
//
//	Sig_E[i] = e;
//	Sig_S[i] = S;
//
//}
//
//////Schnorrǩ�����̣�����Ĺ�˽Կʹ��֮ǰ��DH���ɵĹ�˽Կ����Ϣ��ʹ���û����ܿռ�EI[]
////void sig_cul(int i)
////{
////	k = 3123123;
////	Integer v = ModularExponentiation(g, k, p);
////	string s = EI[i] + its(v);
////	string e = hmac<SHA__256>(s, "0");
////
////	//�м����
////	Integer mid = ModularMultiplication(ss1[i], tran1(e), q);
////	Integer S = ModularMultiplication(1, k - mid, q);
////
////	Sig_E[i] = e;
////	Sig_S[i] = S;
////
////}
//
//
////Schnorrǩ����֤����
//bool temp_sig_ver(int i)
//{
//	Integer v = ModularMultiplication(ModularExponentiation(g, Sig_S[i], p), ModularExponentiation(ss1[i], tran1(Sig_E[i]), p), p);
//	temp_Sig_E[i] = tran1(Sig_E[i]);
//	temp_s = its(v);
//}
//
////Schnorrǩ����֤����
//bool sig_ver(int i)
//{
//	Integer v = ModularMultiplication(ModularExponentiation(g, Sig_S[i], p), ModularExponentiation(ss1[i], temp_Sig_E[i], p), p);
//	string s = temp_s;
//	string s2 = EI[i] + s;
//	string m = hmac<SHA__256>(s2, "0");
//
//	if (m == Sig_E[i])
//	{
//		return true;
//	}
//
//	else
//	{
//		return false;
//	}
//}
//
//
////�����������������ݱ�������Ŀ·���µ�test.xls��
//void Output()
//{
//	//���ĺ�׺�ɸı�洢��ʽ
//	of.open(".\\dh\\rp1.1.txt");
//
//	//���n��˽Կ
//	of << "�û�˽ԿֵΪ��" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		of << ss[i] << endl;
//	}
//	of << endl;
//
//}
//
//int main()
//{
//
//	cout << "�������û�����";
//	cin >> n;
//	cout << endl;
//
//	for (int i = 0; i < n; i++)
//	{
//		mi[i] = "100";
//	}
//
//	Timer tm(TimerBase::MILLISECONDS);
//
//	tm.StartTimer();
//	Init();
//	cout << "��ʼ�����ѵ�ʱ�䣨���룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//
//	tm.StartTimer();
//	Key_gen();
//	cout << "���ɹ�˽Կ�����кŻ��ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	//�������к�
//	sec();
//
//
//	////������Կ����ƽ��ֵ
//	//double sum_G = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//
//	//	Key_gen();
//
//	//	sum_G = sum_G + tm.ElapsedTimeAsDouble();
//
//	//	//cout << "������Կ��Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "��Կ����ƽ��ֵΪ " << sum_G / 10 << endl << endl;
//
//
//	tm.StartTimer();
//	Con_gen();
//	cout << "���û�����Э��ֵ���ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()/n  << endl << endl;
//
//	temp_tran(0);
//	tm.StartTimer();
//	ev_single(0);
//	cout << "���û����ɼ��ܿռ���Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() *5 << endl << endl;
//
//	tm.StartTimer();
//	Decode();
//	Output();
//	cout << "���벢������ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	temp_sig_cul(0);
//	double sum2 = 0;
//	for (int i = 0; i < 10; i++)
//	{
//		tm.StartTimer();
//		sig_cul(0);
//		sum2 = sum2 + tm.ElapsedTimeAsDouble() * n;
//	}
//	cout << "ǩ����ʱ��Ϊ��" << sum2 / 10 * 6 << endl << endl;
//	
//
//	temp_sig_ver(0);
//	tm.StartTimer();
//	sig_ver(0);
//	cout << "��֤ǩ����ʱ��Ϊ��" << tm.ElapsedTimeAsDouble() * 6 * n << endl << endl;
//
//
//	//�����ۼӵ���ʱ����
//	int len = EI[0].length();
//	int l = len / n;
//	rain =tran1( cut(EI[0], 0, l));
//
//
//	tm.StartTimer();
//	cul_ev();
//	cout << "ʵ�־ۺ��ۼӻ��ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() * 6 << endl << endl;
//
//
//	//tm.StartTimer();
//	//ModularExponentiation(g,k,p);
//	//cout << "ִ��һ����ģ���㻨�ѵ�ʱ��Ϊ ��" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	getchar();
//	getchar();
//	return 0;
//
//}