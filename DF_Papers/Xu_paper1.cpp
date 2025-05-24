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
//
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
//SecByteBlock cs[MAX];
//SecByteBlock cp[MAX];
//
////s的协商值、c的协商值
//Integer scon[MAX][MAX]; 
//Integer	ccon[MAX][MAX];
//Integer SN_f[MAX][MAX];
//
////s公私钥转整型，c公私钥转整型
//Integer ss1[MAX];
//Integer sp1[MAX];
//Integer cs1[MAX];
//Integer cp1[MAX];
//
////AES加密数据存储、AES解密数据存储
//string encryptS[MAX][MAX];
//string decryptS[MAX][MAX];
//
////space存储加密空间,它的含义是第I个用户的第J列的哈希值，即H
//Integer vec[MAX][MAX];
//Integer agg[MAX];
//Integer rec[MAX];
//
////V用于字符串转vector，SN存放随机生成的序列号
//vector<int> V;
//vector<int> SN;
//
////定义三个基本数p,q,g
//AutoSeededRandomPool rng;
//Integer p, q, g;
//Integer K = 5;
//
////threshold是恢复文件所需份数（t-out-of-n的t），nShars=n 是用户总数
//int threshold, nShares;
//
////安全参数
//Integer M = 0xffffffffffffffff;
//
////shamir切分文件的保存路径
//string filename = ".\\dh\\rp1.txt";
//
//
////定义加密空间数值转换的中间变量
//string con_temp[MAX][MAX];
//string sn_temp[MAX][MAX];
//string j_temp[MAX];
//Integer num_temp[MAX][MAX];
//
//
////序列号生成部分
////用户数
//int member;
//
////每个用户自己的值
//int user[1000];
//
////初始切割区间
//int cutt[1000];
//
//int multi_users = 0;
//
////用于存放最终切割区间
//vector<int> v1;
//
////标记数组，用于不生成重复的随机值
//bool vis1[2000000] = { false };
//bool vis2[2000000] = { false };
//
////递归调用时，用于递归时的随机生成区间边界的存放以及对应的标记函数,
//int cut_temp[1000][1000];
//bool vis_temp[500][2000000] = { false };
//
////递归深度
//int turn = 0;
//
////论文函数中的三个定值
//int L0;
//int L1;
//int L2;
//
////每次递归的子区间个数
//int sub_count[2000000];
//
////每次递归的用户数num
//int sub_user[2000000];
//
////生成随机数
//int getRand(int min, int max)
//{
//	return (rand() % (max - min)) + min + 1;
//}
//
////随机数生成函数，几个参数是：存放随机值的变量、标记数组、随机数下界、随机数上界（左闭右开）、生成随机数的个数
//void initer(int a[], bool b[], int left, int right, int num)
//{
//	for (int i = 0; i < num; i++)
//	{
//		int r = getRand(left, right);
//		while (b[r] == true)
//		{
//			r = getRand(left, right);
//		}
//		a[i] = r;
//		b[r] = true;
//	}
//}
//
//
////初步计算每个区间内用户个数的函数
//int CountNumbers(int left, int right)
//{
//	int ans = 0;
//	for (int i = 0; i < member; i++)
//	{
//		if (user[i] > left && user[i] <= right)
//			ans++;
//	}
//	return ans;
//}
//
//
////论文中的切割函数，几个参数是：下界、上界、区间内用户个数、递归深度（次数）
//void PartitionIntervals(int left, int right, int num, int turn)
//{
//	//cout << left << " " << right << " " << endl;
//	if (num == 0)
//		return;
//
//	else if (num == 1)
//	{
//		sub_count[turn]++;
//		v1.push_back(left);
//		v1.push_back(right);
//		return;
//	}
//
//	else if (2 <= num <= L1)
//	{
//		sub_count[turn]++;
//		sub_user[turn] += num;
//		turn++;
//
//		int temp1 = pow(L1, 2);
//		if (num < temp1)
//			temp1 = num;
//
//		initer(cut_temp[turn], vis_temp[turn], left, right, temp1 - 1);
//		sort(cut_temp[turn], cut_temp[turn] + temp1 - 1);
//
//		PartitionIntervals(left, cut_temp[turn][0], CountNumbers(left, cut_temp[turn][0]), turn);
//
//		if (temp1 > 2)
//			for (int i = 0; i < temp1 - 2; i = i + 1)
//			{
//				PartitionIntervals(cut_temp[turn][i], cut_temp[turn][i + 1], CountNumbers(cut_temp[turn][i], cut_temp[turn][i + 1]), turn);
//			}
//
//		PartitionIntervals(cut_temp[turn][temp1 - 2], right, CountNumbers(cut_temp[turn][temp1 - 2], right), turn);
//	}
//
//	else
//	{
//		sub_count[turn]++;
//		sub_user[turn] += num;
//		turn++;
//
//		int temp2 = pow(L2, 2);
//		if (num < temp2)
//			temp2 = num;
//
//		initer(cut_temp[turn], vis_temp[turn], left, right, temp2 - 1);
//		sort(cut_temp[turn], cut_temp[turn] + temp2 - 1);
//
//		PartitionIntervals(left, cut_temp[turn][0], CountNumbers(left, cut_temp[turn][0]), turn);
//
//		if (temp2 > 2)
//			for (int i = 0; i < temp2 - 2; i = i + 1)
//			{
//				PartitionIntervals(cut_temp[turn][i], cut_temp[turn][i + 1], CountNumbers(cut_temp[turn][i], cut_temp[turn][i + 1]), turn);
//			}
//
//		PartitionIntervals(cut_temp[turn][temp2 - 2], right, CountNumbers(cut_temp[turn][temp2 - 2], right), turn);
//	}
//
//}
//
////这一部分是计算加密空间向量,参数为用户序号，计算出的是Piv（φ）、以及Pbi（φ）
//void seq_space(int i, int l)
//{
//
//	for (int j = 0; j < n; j++)
//	{
//		Integer sum = 0;
//		for (int k = 0; k < l; k++)
//		{
//			string s3;
//
//			if (i != k)
//			{
//				s3 = hmac<SHA__256>(j_temp[j], con_temp[i][k]);
//			}
//
//			else
//			{
//				s3 = hmac<SHA__256>(j_temp[j], sn_temp[i][j]);
//			}
//
//			//num 是hmac加密后的数
//			if (i == k)
//			{
//				sum = (sum + num_temp[j][k]) % M;
//			}
//			else if (i < k)
//			{
//				sum = (sum - num_temp[j][k]) % M;
//			}
//			else
//			{
//				sum = (sum + num_temp[j][k]) % M;
//			}
//		}
//
//		vec[i][j] = sum;
//
//		//cout << vec[i][j] << endl;
//	}
//
//}
//
//
////生成指定用户（单个用户）的加密向量的值
//void seq_ev_single(int i, int l)
//{
//	seq_space(i, l);
//}
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
//		DH d2(p, q, g);
//		SecByteBlock Pri(d1.PrivateKeyLength());
//		SecByteBlock Pub(d1.PublicKeyLength());
//		SecByteBlock Sri(d2.PrivateKeyLength());
//		SecByteBlock Sub(d2.PublicKeyLength());
//		d1.GenerateKeyPair(rng, Pri, Pub);
//		d2.GenerateKeyPair(rng, Sri, Sub);
//		ss[i] = Pri;
//		sp[i] = Pub;
//		cs[i] = Sri;
//		cp[i] = Sub;
//
//	}
//}
//
//
////生成协商值的函数
//void Con_gen()
//{
//
//	DH d1(p, q, g);
//	DH d2(p, q, g);
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
//			d2.Agree(t2, cs[i], cp[j]);
//			Integer B;
//			B.Decode(t2.BytePtr(), t2.size());
//			ccon[i][j] = B;
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
//		C.Decode(cs[i].BytePtr(), cs[i].size());
//		D.Decode(cp[i].BytePtr(), cp[i].size());
//		cs1[i] = C;
//		cp1[i] = D;
//
//	}
//}
//
// 
// //这一部分是将计算加密空间向量中的数值转换步骤提出来，减少时间
//void temp_tran(int i)
//{
//	for (int j = 0; j < n; j++)
//	{
//		for (int k = 0; k < n; k++)
//		{
//			string s3;
//			con_temp[i][k] = its(scon[i][k]);
//			sn_temp[i][j] = its(SN[i]);
//			j_temp[j] = its(j);
//			
//			
//			if (i != k)
//			{
//				s3 = hmac<SHA__256>(j_temp[j], con_temp[i][k]);
//			}
//			else
//			{
//				s3 = hmac<SHA__256>(j_temp[j], sn_temp[i][j]);
//				SN_f[i][j] = tran1(s3);
//			}
//
//			//num 是hmac加密后的数
//			num_temp[j][k] = tran1(s3);
//		}
//	}
//}
//
//
////这一部分是计算加密空间向量,参数为用户序号，计算出的是Piv（φ）、以及Pbi（φ）
//void key_space(int i)
//{
//
//	for (int j = 0; j < n; j++)
//	{
//		Integer sum = 0;
//		for (int k = 0; k < n; k++)
//		{
//			string s3;
//			//string s1, s3;
//			//string s2 = its(j);
//
//			if (i != k)
//			{
//				//s1 = its(scon[i][k]);
//				s3 = hmac<SHA__256>(j_temp[j], con_temp[i][k]);
//			}
//			else
//			{
//				//s1 = its(SN[i]);
//				s3 = hmac<SHA__256>(j_temp[j], sn_temp[i][j]);
//				//SN_f[i][j] = tran1(s3);
//			}
//
//			//num 是hmac加密后的数
//			Integer num = num_temp[j][k] % M;
//
//			if (i == k)
//			{
//				sum = ( sum + num ) % M;
//			}
//			else if (i < k)
//			{
//				sum = ( sum - num ) % M;
//			}
//			else
//			{
//				sum = (sum + num) % M;
//			}
//		}
//		if (i == j)
//		{
//			sum = (sum + 1 + SN_f[i][j]) % M;
//		}
//		else
//		{
//			sum = (sum + SN_f[i][j]) % M;
//		}
//
//		vec[i][j] = sum;
//
//		//cout << vec[i][j] << endl;
//	}
//
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
////累加检验，看是否为ΣH为0
//void check()
//{
//	Integer sum = 0;
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			sum = sum + vec[i][j];
//		}
//
//	}
//	cout << "累加值为：" << sum << endl << endl;
//}
//
////输出函数，输出的内容保存在项目路径下的test.xls中
//void Output()
//{
//	//更改后缀可改变存储方式
//	of.open(".\\dh\\rp1.txt");
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
//
////shamir密钥共享-切分函数
//void SecretShareFile(int threshold, int nShares, const string filename)
//{
//	CRYPTOPP_ASSERT(nShares >= 1 && nShares <= 1000);
//		if (nShares < 1 || nShares > 1000)
//			throw InvalidArgument("SecretShareFile:" + IntToString(nShares) + "is not in range[1,1000]");
//			AutoSeededRandomPool rng;
//			ChannelSwitch *channelSwitch = new ChannelSwitch;
//			FileSource source(filename.c_str(), false, new SecretSharing(rng, threshold, nShares, channelSwitch));
//			vector_member_ptrs<FileSink> fileSinks(nShares);
//			std::string channel;
//			for (int i = 0; i < nShares; i++)
//			{
//				char extension[5] = ".000";
//				extension[1] = '0' + byte(i / 100);
//				extension[2] = '0' + byte((i / 10)%10);
//				extension[3] = '0' + byte(i %10);
//				fileSinks[i].reset(new FileSink((std::string(filename) + extension).c_str()));
//				channel = WordToString<word32>(i);
//				fileSinks[i]->Put((const byte*)channel.data(), 4);
//				channelSwitch->AddRoute(channel, *fileSinks[i], DEFAULT_CHANNEL);
//			}
//		source.PumpAll();
//
//}
//
////shamier密钥共享-还原函数
//void SecretRecoverFile(int threshold, const string& outFilename, const vector<string>& inFilenames)
//{
//	CRYPTOPP_ASSERT(threshold >= 1 && threshold <= 1000);
//	if (threshold < 1 || threshold > 1000)
//		throw InvalidArgument("SecretRecoverFile:" + IntToString(threshold) + "is not in range[1,1000]");
//	SecretRecovery recovery(threshold, new FileSink(outFilename.c_str()));
//	vector_member_ptrs<FileSource> fileSources(threshold);
//	SecByteBlock channel(4);
//
//	int i;
//	for (i = 0; i < threshold; i++)
//	{
//		fileSources[i].reset(new FileSource(inFilenames[i].c_str(), false));
//		fileSources[i]->Pump(4);
//		fileSources[i]->Get(channel, 4);
//		fileSources[i]->Attach(new ChannelSwitch(recovery, std::string((char*)channel.begin(), 4)));
//	}
//
//	while(fileSources[0]->Pump(256))
//		for (i = 1; i < threshold; i++)
//			fileSources[i]->Pump(256);
//	
//	for (i = 0; i < threshold; i++)
//		fileSources[i]->PumpAll();
//		
//}
//
////使用切分函数
//void shamir_sec()
//{
//	try
//	{
//		nShares = n;
//		threshold = 5;
//		SecretShareFile(threshold, nShares, filename);
//	}
//	catch (const Exception& e)
//	{
//		cout << e.what() << endl;
//	}
//}
//
////使用还原函数
//void shamir_rec()
//{
//	//try
//	//{
//	//	vector<string> inFilenames;
//
//	//	string file1 = ".\\dh\\rp1.txt.000";
//	//	inFilenames.push_back(file1);
//
//	//	string file2 = ".\\dh\\rp1.txt.001";
//	//	inFilenames.push_back(file2);
//
//	//	string file3 = ".\\dh\\rp1.txt.002";
//	//	inFilenames.push_back(file3);
//
//	//	string newfile = ".\\dh\\recover.txt";
//	//	SecretRecoverFile(threshold, newfile, inFilenames);
//
//	//}
//	try
//	{
//		vector<string> inFilenames;
//
//		for (int i = 0; i < threshold; i++)
//		{
//			string file = ".\\dh\\rp1.txt.000";
//			inFilenames.push_back(file);
//		}
//		string newfile = ".\\dh\\recover.txt";
//		SecretRecoverFile(threshold, newfile, inFilenames);
//
//	}
//	catch (const Exception& e)
//	{
//		cout << e.what() << endl;
//	}
//}
//
//void aes(string message)
//{
//	string cipher, recover;
//	HMAC<SHA3_512>hmac;
//	SecByteBlock hkey(hmac.DefaultKeyLength());
//	AutoSeededRandomPool rn;
//	rn.GenerateBlock(hkey, hkey.size());
//	hmac.SetKey(hkey, hkey.size());
//	CBC_Mode<AES>::Encryption cbc_aes_enc;
//	//CBC_Mode<AES>::Decryption cbc_aes_dec;
//
//	SecByteBlock aes_key(cbc_aes_enc.DefaultKeyLength());
//	SecByteBlock aes_iv(cbc_aes_enc.DefaultIVLength());
//
//	rng.GenerateBlock(aes_key, aes_key.size());
//	rng.GenerateBlock(aes_iv, aes_iv.size());
//
//	cbc_aes_enc.SetKeyWithIV(aes_key, aes_key.size(), aes_iv, aes_iv.size());
//	//cbc_aes_dec.SetKeyWithIV(aes_key, aes_key.size(), aes_iv, aes_iv.size());
//
//	//cout << "plain:" << endl;
//
//	//StringSource plainSrc(message, true, new HexEncoder(new FileSink(cout)));
//	StringSource encSrc(message, true, new StreamTransformationFilter(cbc_aes_enc, new HashFilter(hmac, new StringSink(cipher), true)));
//
//
//	//cout << endl << "cipher:" << endl;
//
//	//StringSource cipherSrc(cipher, true, new HexEncoder(new FileSink(cout)));
//	//StringSource decSrc(cipher, true, new HashVerificationFilter(hmac, new StreamTransformationFilter(cbc_aes_dec, new StringSink(recover)),
//	//HashVerificationFilter::HASH_AT_END | HashVerificationFilter::PUT_MESSAGE | HashVerificationFilter::THROW_EXCEPTION));
//
//	//cout << endl << "recover:" << endl;
//
//	//StringSource recoverSrc(recover, true, new HexEncoder(new FileSink(cout)));
//	//cout << endl;
//}
//
//
//
////服务器累加ev
//void cul_ev()
//{
//	//累加Vagg
//	for (int i = 0; i < n; i++)
//	{
//		Integer sum = 0;
//		for (int j = 0; j < n; j++)
//		{
//			sum = (sum + vec[j][i]) % M;
//		}
//		agg[i] = sum;
//	}
//	//数据还原vagg
//	/*for (int i = 0; i < n; i++)
//	{
//		string s1 = its(i);
//		string s2 = its(SN[i]);
//		string s3 = hmac<SHA__256>(s1, s2);
//		rec[i] = agg[i] - tran1(s3);
//	}*/
//}
//
//
//
//int main()
//{
//	
//	cout << "请输入用户数：";
//	cin >> n;
//	cout << endl;
//
//	Timer tm(TimerBase::MILLISECONDS);
//
//	tm.StartTimer();
//	Init();
//	cout << "初始化花费的时间（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	tm.StartTimer();
//	Key_gen();
//	cout << "生成公私钥、序列号花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	//生成序列号
//	sec();
//
//	tm.StartTimer();
//	Con_gen();
//	cout << "单用户生成协商值花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()/n << endl << endl;
//
//	temp_tran(0);
//	tm.StartTimer();
//	ev_single(0);
//	cout << "单用户生成加密空间需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()*5 << endl << endl;
//
//	//序列号生成部分
//	//用户数
//	member = n;
//	//上界
//	int upper = pow(member, 3);
//	//论文函数中的三个定值
//	L0 = ceil(log(member) / log(log(member)));
//	L1 = ceil(pow(ceil(log(member)), 4 / 3));
//	L2 = pow(ceil(log(member)), 3 / 2);
//
//	srand(time(0));
//	//初始化用户随机数
//	initer(user, vis1, 0, upper, member);
//
//	//初次均分区间
//	for (int i = 0; i < member - 1; i++)
//	{
//		cutt[i] = (i + 1) * pow(member, 2);
//	}
//
//	//排序是为了便于后面划分自子区间工作
//	sort(user, user + member);
//	sort(cutt, cutt + member - 1);
//
//
//	//cout << "用户的初始值为：" << endl;
//	//for (int i = 0; i < member; i++)
//	//{
//	//	cout << user[i] << " ";
//	//}
//	//cout << endl;
//
//
//	//cout << "初始化分区间为：" << endl;
//	//cout << "1" << " ";
//	//for (int i = 0; i < member - 1; i++)
//	//{
//	//	cout << cutt[i] << " ";
//	//}
//	//cout << upper << endl << endl;
//
//	double sum1 = 0;
//	for (int i = 0; i < 5; i++)
//	{
//		tm.StartTimer();
//		//调用划分区间函数，第一个和最后一个与以上下界作为上下限，因此单独列出
//		PartitionIntervals(0, cutt[0], CountNumbers(0, cutt[0]), 0);
//		for (int i = 0; i < member - 2; i = i + 1)
//		{
//			PartitionIntervals(cutt[i], cutt[i + 1], CountNumbers(cutt[i], cutt[i + 1]), 0);
//		}
//		PartitionIntervals(cutt[member - 2], upper, CountNumbers(cutt[member - 2], upper), 0);
//		sum1 = sum1 + tm.ElapsedTimeAsDouble();
//	}
//	cout << "用户划分子区间的时长为：" << sum1/5 << endl << endl;
//	
//
//
//	//子区间转换为闭区间
//	for (int i = 0; i < v1.size(); i++)
//	{
//		if (i % 2 == 0)
//			v1[i] = v1[i] + 1;
//	}
//
//	//cout << "子区间划分的值为：" << endl;
//	//for (int i = 0; i < v1.size(); i++)
//	//{
//
//	//	if (i % 2 == 0)
//	//		cout << v1[i] << "-";
//	//	else
//	//		cout << v1[i] << " ";
//	//}
//	//cout << endl << endl;
//
//	double sum2 = 0;
//	for (int i = 0; i < 5; i++)
//	{
//		tm.StartTimer();
//		for (int i = 0; sub_count[i] != 0; i++)
//		{
//			seq_ev_single(i, sub_count[i]);
//		}
//		sum2 = sum2 + tm.ElapsedTimeAsDouble();
//	}
//	cout << "序列号生成中加密的时间为（毫秒）：" << sum2 / 5 << endl << endl;
//
//	
//
//	tm.StartTimer();
//	Decode();
//	Output();
//	cout << "解码并输出花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	tm.StartTimer();
//		shamir_sec();
//	cout << "实现单用户Share秘钥共享花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()*5 << endl << endl;
//
//
//	tm.StartTimer();
//		shamir_rec();
//	cout << "实现单用户Share秘钥还原花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()*6*n << endl << endl;
//
//	tm.StartTimer();
//	for (int i = 0; i < n; i++)
//	{
//		aes(its(ccon[0][i]));
//	}
//	cout << "实现单用户AES加密解密花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()*5 << endl << endl;
//
//
//	//	//计算密钥生成平均值
//	//double sum_G = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//
//	//	Key_gen();
//
//	//	sum_G = sum_G + tm.ElapsedTimeAsDouble() / n;
//
//	//	//cout << "生成秘钥需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "密钥生成平均值为 " << sum_G / 10 << endl;
//
//
//	////秘钥共享平均时间
//	//double sum_S = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//	//	shamir_sec();
//	//	sum_S = sum_S + tm.ElapsedTimeAsDouble();
//	//	//cout << "生成秘钥需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "密钥共享平均值为 " << sum_S / 10 << endl;
//
//
//	////AES加密时间
//	//double sum_A = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//
//	//	for (int j = 0; j < n; j++)
//	//	{
//	//		aes(its(ccon[0][j]));
//	//	}
//
//	//	sum_A = sum_A + tm.ElapsedTimeAsDouble();
//
//	//	//cout << "生成秘钥需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "AES加密平均值为 " << sum_A / 10 << endl;
//
//
//	////计算密钥协商平均值
//	//double sum_C = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//
//	//	Con_gen();
//
//	//	sum_C = sum_C + tm.ElapsedTimeAsDouble() / n;
//
//	//	//cout << "生成秘钥需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "密钥协商平均值为 " << sum_C / 10 << endl;
//
//	////计算H生成平均值
//	//double sum_H = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//
//	//	ev_single(0);
//
//	//	sum_H = sum_H + tm.ElapsedTimeAsDouble();
//
//	//	//cout << "生成秘钥需要的时间为（毫秒）：" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "密钥空间生成平均值为 " << sum_H / 10 << endl;
//
//
//	tm.StartTimer();
//	cul_ev();
//	cout << "实现聚合累加花费的时间为（毫秒）：" << tm.ElapsedTimeAsDouble()*6 << endl << endl;
//
//
//	getchar();
//	getchar();
//	return 0;
//
//}