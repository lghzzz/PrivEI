//#include "HMAC_256.h"
//#include "SHA_256.h"
//#include<integer.h>
//#include<osrng.h>
//#include<nbtheory.h>
//#include<dh.h>
//#include<hrtimer.h>
//#include<math.h>
//#include<cmath>
//#include<fstream>
//#include<secblock.h>
//#include<files.h>
//#include<string>
//#include<sstream>
//#include<vector>
//#include<stack>
//#include <algorithm>
//#include <ctime>	
//#include<iostream>
//
//#define MAX 1000
//
////Message dimension for CRT transformation
//#define DM 16
//
//using namespace std;
//using namespace CryptoPP;
//
//ofstream outfile;
//
////Number of users
//int n;
//
////The decoded private key and public key saved in the form of Integer
//Integer pr[MAX];
//Integer pu[MAX];
//
////The value of key_agreement after decoding
//Integer con[MAX][MAX];
//
////Privateand public keys saved in the form of SecByteBlock
//SecByteBlock p1[MAX];
//SecByteBlock p2[MAX];
//
////The value of Encrypted space
//Integer space[MAX][MAX];
//
////Basic Generation Number
//AutoSeededRandomPool rng;
//Integer p, q, g;
//
////Signature parameter K
//Integer K = 1;
//
////Variables during the signature process
//Integer gamma[MAX][MAX], beta[MAX][MAX];
//string L[MAX], R[MAX];
//Integer C[MAX][MAX], S[MAX][MAX];
//Integer M1[MAX], M2[MAX][MAX];
//Integer Sig_r;
//vector<int> V;
//
////Type conversion function declaration
//Integer tran1(string s);
//
////Serial number 
//vector<int> SN;
//
////Dividend and divisor in CRT
//typedef long long llong;
//Integer b[MAX][DM];
//
//
////Customize 16-dimensional CRT conversion with different length of dividends
////Integer w[DM] = {131,137 ,139 ,149 ,151 ,157 ,163 ,167 ,173 ,179 ,181 ,191 ,193 ,197 ,199 ,211};
////Integer w[DM] = {32771,32779,32783 ,32789, 32797, 32801, 32803, 32831, 32833, 32839, 32843, 32869, 32887, 32909, 32911,32917};
////Integer w[DM] = {tran1("2332913579"),tran1("3537815783"),tran1("3901918367"),tran1("3521966627"),tran1("4041359759"),tran1("2560834439"),tran1("3927551339"),tran1("3252618827"),tran1("4068467087"),tran1("2777096207"),tran1("2846247707"),tran1("4060407383"),tran1("2844487307"),tran1("2201980343"),tran1("2499728207"),tran1("3358379183") };
////Integer w[DM] = {tran1("14799980878431137483"),tran1("11375890615488983567"),tran1("17946625525685077583"),tran1("11072502421788333047"),tran1("14391117850104244559"),tran1("14507098390601505203"),tran1("11691624821837589599"),tran1("14908258777734559379"),tran1("11144752929418587539"),tran1("10787199373909830083"),tran1("13286396365882500647"),tran1("17178023310558063599"),tran1("13627461406213581503"),tran1("13012120592205740207"),tran1("16201609614510235667"),tran1("17962597866526172243") };
//Integer w[DM] = {tran1("236352327434048884093165884294485198543"),tran1("241104854713119713855436951445894502579"),tran1("229938686131899413123627175019808496227"),tran1("288619776611061802805861766018370186079") ,tran1("303231301003668153107397533359523224643"),tran1("253296025495516439344853006566723328303"),tran1("300856890672932109951738566935957462127"),tran1("290358408110424816709957946844475931627"),tran1("199795153999838624823618329734755524699"),tran1(" 326467800465837109955572961592856406183"),tran1("325088363790868175199362309011603211039"),tran1("315802208284781647068436776341124356519"),tran1("177195080359077726998920175344740434219"),tran1("314169765472033131656446490557657799783"),tran1("266656291452018105430914920758158786179"),tran1("264152166962598913479844796610704093807")};
//
//
////vector EV
//Integer EV[MAX][MAX];
//
////Message values before and after CRT restoration
//Integer crt_1[MAX];
//Integer crt_2[MAX][DM];
//
////Final aggregation result
//Integer AG[MAX];
//
////Security parameter 
//Integer M = 0xffffffffffffffff;
//
////Integer type to string type
//string its(Integer n)
//{
//	ostringstream stream;
//	stream << n;  
//	string ans = stream.str();
//	int l = ans.length();
//	ans.erase(l - 1, 1);
//	return ans;
//}
//
////Int type to string type
//string its(int n)
//{
//	ostringstream stream;
//	stream << n;  
//	return stream.str();
//}
//
//
////String type to int
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
////String type to Integer
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
////Binary to decimal
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
////Save string to vector
//void stv(string s)
//{
//	V.clear();
//	int len = s.length();
//	for (int i = 0; i < len; i++)
//	{
//		V.push_back(s[i] - '0');
//	}
//}
//
////Bitwise function
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
//	//cout << endl << "The lenth is£º" << ans.length();
//	return ans;
//
//}
//
////String segmentation
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
////Modular and reminder operation of large numbers
//Integer mypow(Integer a, Integer k)
//{
//	a %= tran(its(p));
//	Integer res = 1;
//	for (int i = 0; i < k; i++)
//	{
//		res = res * a;
//		res %= tran(its(p));
//	}
//	return res;
//}
//
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
//
////Random generation of p q r 
//void Init()
//{
//	PrimeAndGenerator pg;
//	pg.Generate(1, rng, 512, 511);
//	p = pg.Prime();
//	q = pg.SubPrime();
//	g = pg.Generator();
//}
//
////Generation of serial number 
//void sec()
//{
//	srand(time(0));
//	for (int i = 0; i < n; i++)
//	{
//		SN.push_back(i);
//	}
//	random_shuffle(SN.begin(), SN.end());
//}
//
////Generation of public and private keys
//void Key_gen()
//{
//	for (int i = 0; i < n; i++)
//	{
//		DH d(p, q, g);
//		SecByteBlock Pri(d.PrivateKeyLength());
//		SecByteBlock Pub(d.PublicKeyLength());
//		d.GenerateKeyPair(rng, Pri, Pub);
//		p1[i] = Pri;
//		p2[i] = Pub;
//	}
//}
//
////Signature initialization
//void SigKeyGen(int i)
//{
//	for (int j = 0; j < K; j++)
//	{
//		string s1 = (hmac<SHA__256>(its(pr[i]) + its(j), "0"));
//		Integer R1 = ModularExponentiation(tran1(its(g)), tran1(s1), p);
//		Integer z = tran1(hmac<SHA__256>(its(pr[i]) + its(j), "1"));
//		gamma[i][j] = z ^ tran1(hmac<SHA__256>(its(R1), "0"));
//		beta[i][j] = tran1(hmac<SHA__256>(its(R1), "1"));
//	}
//}
//
////Signature calculation
//void Sig_Com(int i, int j)
//{
//	string s;
//	for (int t = 0; t < n; t++)
//	{
//		s = s + DecToBinary(its(space[i][t]));
//	}
//	int num = DecToBinary(its(q)).length();
//	int rlen = s.length() - num;
//	L[i] = cut(s, 0, num);
//	R[i] = cut(s, num, rlen);
//
//	C[i][j] = tran1(L[i]) ^ tran1(hmac<SHA__256>(its(pr[i]) + its(j), "1"));
//	Integer b = tran1(hmac<SHA__256>(its(C[i][j]) + R[i], "0"));
//	S[i][j] = tran1(hmac<SHA__256>(its(pr[i]) + its(j), "0")) - (b % q) * (pr[i] % q);
//	
//}
//
////Signature authentication 
//bool Sig_ver(int i, int j)
//{
//	string s1 = hmac<SHA__256>(its(pr[i]) + its(j), "0");
//	Integer r1 = ModularExponentiation(tran1(its(pu[i])), tran1(s1), p);
//	Integer r2 = ModularExponentiation(tran1(its(g)), tran1(s1), p);
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
//	
//}
//
////Signature restoration
//void Sig_rec(int i, int j)
//{
//	
//	if (C[i][j] < 0)
//		M1[i] = -(gamma[i][j] ^ tran1(hmac<SHA__256>(DecToBinary(its(Sig_r)), "0")) ^ C[i][j]);
//	else
//		M1[i] = gamma[i][j] ^ tran1(hmac<SHA__256>(DecToBinary(its(Sig_r)), "0")) ^ C[i][j];
//	string m = its(M1[i]) + R[i];
//
//	Integer temp = 0;
//	for (int t = 0; t < n; t++)
//	{
//		Integer len = its(space[i][t]).length();
//		M2[i][t] = tran1(cut(m, tran(its(temp)), tran(its(len))));
//		temp = temp + len;
//	}
//	
//}
//
////Key agreement calculation
//void Con_gen()
//{
//
//	DH d(p, q, g);
//	SecByteBlock t1(d.AgreedValueLength()), t2(d.AgreedValueLength());
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			d.Agree(t1, p1[i], p2[j]);
//			Integer A;
//			A.Decode(t1.BytePtr(), t1.size());
//			con[i][j] = A;
//		}
//	}
//}
//
////Decoding function 
//void Decode()
//{
//
//	Integer A, B;
//	for (int i = 0; i < n; i++)
//	{
//		A.Decode(p1[i].BytePtr(), p1[i].size());
//		B.Decode(p2[i].BytePtr(), p2[i].size());
//		pr[i] = A;
//		pu[i] = B;
//	}
//}
//
////Encrypted Space Computing
//void key_space(int i)
//{
//	for (int j = 0; j < n; j++)
//	{
//		Integer sum = 0;
//		for (int k = 0; k < n; k++)
//		{
//			string s1 = its(con[i][k]);
//			string s2 = its(j);
//			string s3 = hmac<SHA__256>(s2, s1);
//
//			Integer num = tran1(s3);
//
//			if (i == k)
//			{
//				sum = sum + num;
//			}
//
//			else if (i < k)
//			{
//				sum = (sum + -num) % M;
//			}
//
//			else
//			{
//				sum = (sum + num) % M;
//			}
//		}
//		space[i][j] = sum;
//	}
//}
//
////Generation of all encrypted space vectors
//void ev()
//{
//	for (int i = 0; i < n; i++)
//	{
//		key_space(i);
//	}
//}
//
////Generation of one encrypted space vector
//void ev_single(int x)
//{
//	key_space(x);
//}
//
////Accumulated result inspection
//void check()
//{
//	Integer sum = 0;
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			sum = sum + space[i][j];
//		}
//
//	}
//	cout << "Cumulative value is£º" << sum << endl << endl;
//}
//
////Output function
//void Output()
//{
//	outfile.open("test.xls");
//
//	outfile << "The private key of the users£º" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		outfile << pr[i] << endl;
//	}
//	outfile << endl;
//
//	outfile << "The public key of the users£º" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		outfile << pu[i] << endl;
//	}
//	outfile << endl;
//
//	outfile << "The value of key agreement£º" << endl;
//	for (int i = 0; i < n; i++)
//	{
//
//		for (int j = 0; j < n; j++)
//		{
//			outfile << con[i][j] << " ";
//		}
//		outfile << endl;
//	}
//
//}
//
////Extended Euclideanand Chinese Remainder Theorem
//Integer extended_euclid(Integer a, Integer b, Integer &x, Integer  &y) 
//{
//       Integer d;
//       if(b == 0) 
//       {x = 1; y = 0; return a;}
//       d = extended_euclid(b, a % b, y, x);
//       y -= a / b * x;
//       return d;   
//}
//
//Integer chinese_remainder(int user, int len) {
//
//       Integer  d, x, y, m, n, ret;
//       ret = 0; n = 1;
//	   for (int i = 0; i < len; i++)
//	   {
//			 n = n * w[i];  
//	   }
//       for(int  i = 0; i < len ;i++) 
//       {
//            m = n / w[i];
//            d = extended_euclid(w[i], m, x, y);
//			ret = (ret + y*m*b[user][i]) % n;
//       }
//       return (n + ret%n) % n;
//}
//
////The calculation of EV vector
//void cul_ev(int user)
//{
//	int sum = 0;
//	for (int i = 0; i < n; i++)
//	{
//		if (i == user)
//			EV[user][i] = (space[user][i] + crt_1[user]) % M;
//		else
//			EV[user][i] = space[user][i];
//	}
//}
// 
// //Aggregation
// void agg()
// {
//
//	 for (int i = 0; i < n; i++)
//	 {
//		 for (int j = 0; j < n; j++)
//		 {
//			 AG[i] = (AG[i] + EV[j][i]) % M;
//
//			 if (i == j)
//			 {
//				 AG[i] = AG[i];
//			 }
//		 }
//	 }
// }
// 
//
////CRT data restoration
//void crt_recover(int user)
//{
//	for (int i = 0; i < DM; i++)
//	{
//		crt_2[user][i] = crt_1[user] % w[i];
//	}
//}
//
//
///* 
//	Due to the large amount of time-consuming data type conversion process involved in the code(tran, tran1, its), we have eliminated the time required 
//	for the data type conversion step in some steps and only focused on the duration of our protocol. Some operations are not shown in this code.
//*/
//
//int main()
//{
//		cout << "Enter the number of users£º";
//		cin >> n;
//		cout << endl;
//
//		//Time Statistics enable
//		Timer tm(TimerBase::MILLISECONDS);
//
//
//		tm.StartTimer();
//		Init();
//		sec();
//		cout << "Time taken to initialize is(milliseconds)£º" << tm.ElapsedTimeAsDouble() << endl << endl;
//	
//		tm.StartTimer();
//		Key_gen();
//		cout << "The time taken to generate public and private keys is(milliseconds): " << tm.ElapsedTimeAsDouble() << endl << endl;
//	
//		tm.StartTimer();
//		Con_gen();
//		cout << "The time taken to generate the key agreement value is(milliseconds): " << tm.ElapsedTimeAsDouble() << endl << endl;
//	
//		tm.StartTimer();
//		ev();
//		cout << "The time teken to generate all user encrypted space is(milliseconds): " << tm.ElapsedTimeAsDouble() << endl << endl;
//
//		tm.StartTimer();
//		Decode();
//		Output();
//		cout << "The time taken to decodeand output is(milliseconds): " << tm.ElapsedTimeAsDouble() << endl << endl;
//	
//		tm.StartTimer();
//		SigKeyGen(1);
//		cout << "The time taken to initialize a user signature is(milliseconds): " << tm.ElapsedTimeAsDouble() << endl << endl;
//
//		tm.StartTimer();
//		Sig_Com(1, 0);
//		cout << "The time taken to calculate a user's signature is(milliseconds): " << tm.ElapsedTimeAsDouble() << endl << endl;
//
//		tm.StartTimer();
//		Sig_ver(1, 0);
//		cout << "The time for user signature verification is(milliseconds): " << tm.ElapsedTimeAsDouble() * n << endl << endl;
//
//		tm.StartTimer();
//		Sig_rec(1, 0);
//		cout << "The time taken to restore a user signature is(milliseconds):" << tm.ElapsedTimeAsDouble() * n << endl << endl;
//
//		//CRT message value initialization. We take setting the same length of messages and CRT dividend as an example
//		for (int i = 0; i < n; i++)
//		{
//			for (int j = 0; j < DM; j++)
//			{
//				b[i][j] = w[j] - 1;
//			}
//		}
//
//		tm.StartTimer();
//		for (int i = 0; i < n; i++)
//		{
//			crt_1[i] = chinese_remainder(i, DM);
//		}
//		cout << "The time taken for converting a single user's multidimensional data to one-dimensional data is(milliseconds): " << tm.ElapsedTimeAsDouble()/n << endl << endl;
//
//		//The calculation of the sum of EV vectorand and message
//		for (int i = 0; i < n; i++)
//		{
//			cul_ev(i);
//		}
//		
//		tm.StartTimer();
//		agg();
//		cout << "The time taken to aggregation accumulation is(milliseconds): " << tm.ElapsedTimeAsDouble() << endl << endl;
//
//		tm.StartTimer();
//		for (int i = 0; i < n; i++)
//		{
//			crt_recover(i);
//		}
//		cout << "The time required to restore multidimensional data for a single user is(milliseconds): " << tm.ElapsedTimeAsDouble()/n << endl << endl;
//
//
//	getchar();
//	getchar();
//	return 0;
//
//}
//
//
