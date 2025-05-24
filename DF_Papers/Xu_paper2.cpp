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
////文件流对象
//ofstream of;
//
////用户数
//int n;
//
////s的公私钥、c的公私钥
//SecByteBlock ss[MAX];
//SecByteBlock sp[MAX];
//
//
////s的协商值、c的协商值
//Integer scon[MAX][MAX];
//
//Integer SN_f[MAX][MAX];
//
////s公私钥转整型，c公私钥转整型
//Integer ss1[MAX];
//Integer sp1[MAX];
//
//
////EI存储加密空间,它的含义是第I个用户的e值,mes是解密后切分给每个用户的消息
//string EI[MAX];
//Integer mes[MAX] = {0};
//Integer EI1[MAX];
//
//
////Sig_M表示签名过程中的Mi，Sig_S表示签名过程中的si
//string Sig_E[MAX];
//Integer Sig_S[MAX];
//
//
////V用于字符串转vector，SN存放随机生成的序列号
//vector<int> V;
//vector<int> SN;
//
////定义三个基本数p,q,g
//AutoSeededRandomPool rng;
//Integer p, q, g;
//Integer K = 5;
//Integer k;
//
////用户消息和时间tm，为简化，这里时间tm固定为100,eagg是聚合之后的数据（未进行切割解密的）
//string mi[MAX];
//Integer tm = 100;
//Integer eagg[MAX][MAX];
//
////计算累加值的临时变量rain
//Integer rain;
//
////定义加密空间数值转换的中间变量
//string scon_temp[MAX][MAX];
//string j_temp[MAX][MAX];
//Integer num_temp1[MAX][MAX];
//Integer num_temp2[MAX][MAX];
//string temp_temp[MAX];
//string temp_v;
//Integer temp_e;
//
////认证签名的中间变量
//Integer temp_Sig_E[MAX];
//string temp_s;
//
//
////Integer型转字符串
//string its(Integer n)
//{
//	ostringstream stream;
//
//	stream << n;  //n为integer类型
//
//	return stream.str();
//}
//
//
////整型转字符串
//string its(int n)
//
//{
//	ostringstream stream;
//
//	stream << n;  //n为int类型
//
//	return stream.str();
//
//}
//
////字符串转Integer型（十六进制）
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
////字符串转整型
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
////字符串转Integer型(10进制）
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
////字符串转vector函数（V是全局变量，使用时自动完成清空）
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
////取位函数（因为数较大，不能用一般的log）
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
//	//cout << endl << "长度为：" << ans.length();
//	return ans;
//
//}
//
////字符串切割函数,start是起始位置，n为长度
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
////大数幂模运算取余（下方函数调用该函数）
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
////大数幂模运算
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
////生成随机序列号bi
//void sec()
//{
//	srand(time(0));
//	for (int i = 0; i < n; i++)
//	{
//		SN.push_back(i);
//	}
//	// 产生[vec.begin(), vec.end())之间的随机序列，前闭后开
//	random_shuffle(SN.begin(), SN.end());
//}
//
//
////初始化函数，随机生成p，g，q
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
////生成私钥和公钥的函数（包括s和c两对）
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
////生成协商值的函数
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
////解码函数，将之前保存的私钥公钥地址中存储的内容解码，保存到Integer型的两个数组中
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
//// //这一部分是将计算加密空间向量中的数值转换步骤提出来，减少时间
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
////计算加密空间向量
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
////生成所有加密空间向量
//void ev()
//{
//	for (int i = 0; i < n; i++)
//	{
//		key_space(i);
//	}
//}
//
////生成指定用户（单个用户）的加密向量的值
//void ev_single(int x)
//{
//	key_space(x);
//}
//
//
////数据聚合
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
//////数据聚合
////void cul_ev()
////{
////	//累次异或
////	for (int i = 0; i < n; i++)
////	{
////		eagg = eagg ^ EI1[i];
////	}
////
////	//数据切分恢复
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
////签名过程剔除数制转换
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
////Schnorr签名过程，这里的公私钥使用之前由DH生成的公私钥，消息暂使用用户加密空间EI[]
//void sig_cul(int i)
//{
//	k = 3123123;
//	Integer v = ModularExponentiation(g, k, p);
//	string s = EI[i]+ temp_v;
//	string e = hmac<SHA__256>(s, "0");
//
//	//中间变量
//	Integer mid = ModularMultiplication(ss1[i], temp_e, q);
//	Integer S = ModularMultiplication(1, k - mid, q);
//
//	Sig_E[i] = e;
//	Sig_S[i] = S;
//
//}
//
//////Schnorr签名过程，这里的公私钥使用之前由DH生成的公私钥，消息暂使用用户加密空间EI[]
////void sig_cul(int i)
////{
////	k = 3123123;
////	Integer v = ModularExponentiation(g, k, p);
////	string s = EI[i] + its(v);
////	string e = hmac<SHA__256>(s, "0");
////
////	//中间变量
////	Integer mid = ModularMultiplication(ss1[i], tran1(e), q);
////	Integer S = ModularMultiplication(1, k - mid, q);
////
////	Sig_E[i] = e;
////	Sig_S[i] = S;
////
////}
//
//
////Schnorr签名认证过程
//bool temp_sig_ver(int i)
//{
//	Integer v = ModularMultiplication(ModularExponentiation(g, Sig_S[i], p), ModularExponentiation(ss1[i], tran1(Sig_E[i]), p), p);
//	temp_Sig_E[i] = tran1(Sig_E[i]);
//	temp_s = its(v);
//}
//
////Schnorr签名认证过程
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
////输出函数，输出的内容保存在项目路径下的test.xls中
//void Output()
//{
//	//更改后缀可改变存储方式
//	of.open(".\\dh\\rp1.1.txt");
//
//	//输出n个私钥
//	of << "用户私钥值为：" << endl;
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
//	cout << "请输入用户数：";
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
//	cout << "初始化花费的时间（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//
//	tm.StartTimer();
//	Key_gen();
//	cout << "生成公私钥、序列号花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	//生成序列号
//	sec();
//
//
//	////计算密钥生成平均值
//	//double sum_G = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//
//	//	Key_gen();
//
//	//	sum_G = sum_G + tm.ElapsedTimeAsDouble();
//
//	//	//cout << "生成秘钥需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "密钥生成平均值为 " << sum_G / 10 << endl << endl;
//
//
//	tm.StartTimer();
//	Con_gen();
//	cout << "单用户生成协商值花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()/n  << endl << endl;
//
//	temp_tran(0);
//	tm.StartTimer();
//	ev_single(0);
//	cout << "单用户生成加密空间需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() *5 << endl << endl;
//
//	tm.StartTimer();
//	Decode();
//	Output();
//	cout << "解码并输出花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	temp_sig_cul(0);
//	double sum2 = 0;
//	for (int i = 0; i < 10; i++)
//	{
//		tm.StartTimer();
//		sig_cul(0);
//		sum2 = sum2 + tm.ElapsedTimeAsDouble() * n;
//	}
//	cout << "签名的时间为：" << sum2 / 10 * 6 << endl << endl;
//	
//
//	temp_sig_ver(0);
//	tm.StartTimer();
//	sig_ver(0);
//	cout << "认证签名的时间为：" << tm.ElapsedTimeAsDouble() * 6 * n << endl << endl;
//
//
//	//计算累加的临时变量
//	int len = EI[0].length();
//	int l = len / n;
//	rain =tran1( cut(EI[0], 0, l));
//
//
//	tm.StartTimer();
//	cul_ev();
//	cout << "实现聚合累加花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() * 6 << endl << endl;
//
//
//	//tm.StartTimer();
//	//ModularExponentiation(g,k,p);
//	//cout << "执行一次幂模运算花费的时间为 ：" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	getchar();
//	getchar();
//	return 0;
//
//}