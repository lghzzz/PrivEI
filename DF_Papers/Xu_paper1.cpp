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
////�ļ�������
//ofstream of;
//
////�û���
//int n;
//
////s�Ĺ�˽Կ��c�Ĺ�˽Կ
//SecByteBlock ss[MAX];
//SecByteBlock sp[MAX];
//SecByteBlock cs[MAX];
//SecByteBlock cp[MAX];
//
////s��Э��ֵ��c��Э��ֵ
//Integer scon[MAX][MAX]; 
//Integer	ccon[MAX][MAX];
//Integer SN_f[MAX][MAX];
//
////s��˽Կת���ͣ�c��˽Կת����
//Integer ss1[MAX];
//Integer sp1[MAX];
//Integer cs1[MAX];
//Integer cp1[MAX];
//
////AES�������ݴ洢��AES�������ݴ洢
//string encryptS[MAX][MAX];
//string decryptS[MAX][MAX];
//
////space�洢���ܿռ�,���ĺ����ǵ�I���û��ĵ�J�еĹ�ϣֵ����H
//Integer vec[MAX][MAX];
//Integer agg[MAX];
//Integer rec[MAX];
//
////V�����ַ���תvector��SN���������ɵ����к�
//vector<int> V;
//vector<int> SN;
//
////��������������p,q,g
//AutoSeededRandomPool rng;
//Integer p, q, g;
//Integer K = 5;
//
////threshold�ǻָ��ļ����������t-out-of-n��t����nShars=n ���û�����
//int threshold, nShares;
//
////��ȫ����
//Integer M = 0xffffffffffffffff;
//
////shamir�з��ļ��ı���·��
//string filename = ".\\dh\\rp1.txt";
//
//
////������ܿռ���ֵת�����м����
//string con_temp[MAX][MAX];
//string sn_temp[MAX][MAX];
//string j_temp[MAX];
//Integer num_temp[MAX][MAX];
//
//
////���к����ɲ���
////�û���
//int member;
//
////ÿ���û��Լ���ֵ
//int user[1000];
//
////��ʼ�и�����
//int cutt[1000];
//
//int multi_users = 0;
//
////���ڴ�������и�����
//vector<int> v1;
//
////������飬���ڲ������ظ������ֵ
//bool vis1[2000000] = { false };
//bool vis2[2000000] = { false };
//
////�ݹ����ʱ�����ڵݹ�ʱ�������������߽�Ĵ���Լ���Ӧ�ı�Ǻ���,
//int cut_temp[1000][1000];
//bool vis_temp[500][2000000] = { false };
//
////�ݹ����
//int turn = 0;
//
////���ĺ����е�������ֵ
//int L0;
//int L1;
//int L2;
//
////ÿ�εݹ�����������
//int sub_count[2000000];
//
////ÿ�εݹ���û���num
//int sub_user[2000000];
//
////���������
//int getRand(int min, int max)
//{
//	return (rand() % (max - min)) + min + 1;
//}
//
////��������ɺ��������������ǣ�������ֵ�ı�����������顢������½硢������Ͻ磨����ҿ���������������ĸ���
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
////��������ÿ���������û������ĺ���
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
////�����е��и�������������ǣ��½硢�Ͻ硢�������û��������ݹ���ȣ�������
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
////��һ�����Ǽ�����ܿռ�����,����Ϊ�û���ţ����������Piv���գ����Լ�Pbi���գ�
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
//			//num ��hmac���ܺ����
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
////����ָ���û��������û����ļ���������ֵ
//void seq_ev_single(int i, int l)
//{
//	seq_space(i, l);
//}
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
////����Э��ֵ�ĺ���
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
//		C.Decode(cs[i].BytePtr(), cs[i].size());
//		D.Decode(cp[i].BytePtr(), cp[i].size());
//		cs1[i] = C;
//		cp1[i] = D;
//
//	}
//}
//
// 
// //��һ�����ǽ�������ܿռ������е���ֵת�����������������ʱ��
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
//			//num ��hmac���ܺ����
//			num_temp[j][k] = tran1(s3);
//		}
//	}
//}
//
//
////��һ�����Ǽ�����ܿռ�����,����Ϊ�û���ţ����������Piv���գ����Լ�Pbi���գ�
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
//			//num ��hmac���ܺ����
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
////�ۼӼ��飬���Ƿ�Ϊ��HΪ0
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
//	cout << "�ۼ�ֵΪ��" << sum << endl << endl;
//}
//
////�����������������ݱ�������Ŀ·���µ�test.xls��
//void Output()
//{
//	//���ĺ�׺�ɸı�洢��ʽ
//	of.open(".\\dh\\rp1.txt");
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
//
////shamir��Կ����-�зֺ���
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
////shamier��Կ����-��ԭ����
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
////ʹ���зֺ���
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
////ʹ�û�ԭ����
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
////�������ۼ�ev
//void cul_ev()
//{
//	//�ۼ�Vagg
//	for (int i = 0; i < n; i++)
//	{
//		Integer sum = 0;
//		for (int j = 0; j < n; j++)
//		{
//			sum = (sum + vec[j][i]) % M;
//		}
//		agg[i] = sum;
//	}
//	//���ݻ�ԭvagg
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
//	cout << "�������û�����";
//	cin >> n;
//	cout << endl;
//
//	Timer tm(TimerBase::MILLISECONDS);
//
//	tm.StartTimer();
//	Init();
//	cout << "��ʼ�����ѵ�ʱ�䣨���룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	tm.StartTimer();
//	Key_gen();
//	cout << "���ɹ�˽Կ�����кŻ��ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	//�������к�
//	sec();
//
//	tm.StartTimer();
//	Con_gen();
//	cout << "���û�����Э��ֵ���ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()/n << endl << endl;
//
//	temp_tran(0);
//	tm.StartTimer();
//	ev_single(0);
//	cout << "���û����ɼ��ܿռ���Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()*5 << endl << endl;
//
//	//���к����ɲ���
//	//�û���
//	member = n;
//	//�Ͻ�
//	int upper = pow(member, 3);
//	//���ĺ����е�������ֵ
//	L0 = ceil(log(member) / log(log(member)));
//	L1 = ceil(pow(ceil(log(member)), 4 / 3));
//	L2 = pow(ceil(log(member)), 3 / 2);
//
//	srand(time(0));
//	//��ʼ���û������
//	initer(user, vis1, 0, upper, member);
//
//	//���ξ�������
//	for (int i = 0; i < member - 1; i++)
//	{
//		cutt[i] = (i + 1) * pow(member, 2);
//	}
//
//	//������Ϊ�˱��ں��滮���������乤��
//	sort(user, user + member);
//	sort(cutt, cutt + member - 1);
//
//
//	//cout << "�û��ĳ�ʼֵΪ��" << endl;
//	//for (int i = 0; i < member; i++)
//	//{
//	//	cout << user[i] << " ";
//	//}
//	//cout << endl;
//
//
//	//cout << "��ʼ��������Ϊ��" << endl;
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
//		//���û������亯������һ�������һ���������½���Ϊ�����ޣ���˵����г�
//		PartitionIntervals(0, cutt[0], CountNumbers(0, cutt[0]), 0);
//		for (int i = 0; i < member - 2; i = i + 1)
//		{
//			PartitionIntervals(cutt[i], cutt[i + 1], CountNumbers(cutt[i], cutt[i + 1]), 0);
//		}
//		PartitionIntervals(cutt[member - 2], upper, CountNumbers(cutt[member - 2], upper), 0);
//		sum1 = sum1 + tm.ElapsedTimeAsDouble();
//	}
//	cout << "�û������������ʱ��Ϊ��" << sum1/5 << endl << endl;
//	
//
//
//	//������ת��Ϊ������
//	for (int i = 0; i < v1.size(); i++)
//	{
//		if (i % 2 == 0)
//			v1[i] = v1[i] + 1;
//	}
//
//	//cout << "�����仮�ֵ�ֵΪ��" << endl;
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
//	cout << "���к������м��ܵ�ʱ��Ϊ�����룩��" << sum2 / 5 << endl << endl;
//
//	
//
//	tm.StartTimer();
//	Decode();
//	Output();
//	cout << "���벢������ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	tm.StartTimer();
//		shamir_sec();
//	cout << "ʵ�ֵ��û�Share��Կ�����ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()*5 << endl << endl;
//
//
//	tm.StartTimer();
//		shamir_rec();
//	cout << "ʵ�ֵ��û�Share��Կ��ԭ���ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()*6*n << endl << endl;
//
//	tm.StartTimer();
//	for (int i = 0; i < n; i++)
//	{
//		aes(its(ccon[0][i]));
//	}
//	cout << "ʵ�ֵ��û�AES���ܽ��ܻ��ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()*5 << endl << endl;
//
//
//	//	//������Կ����ƽ��ֵ
//	//double sum_G = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//
//	//	Key_gen();
//
//	//	sum_G = sum_G + tm.ElapsedTimeAsDouble() / n;
//
//	//	//cout << "������Կ��Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "��Կ����ƽ��ֵΪ " << sum_G / 10 << endl;
//
//
//	////��Կ����ƽ��ʱ��
//	//double sum_S = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//	//	shamir_sec();
//	//	sum_S = sum_S + tm.ElapsedTimeAsDouble();
//	//	//cout << "������Կ��Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "��Կ����ƽ��ֵΪ " << sum_S / 10 << endl;
//
//
//	////AES����ʱ��
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
//	//	//cout << "������Կ��Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "AES����ƽ��ֵΪ " << sum_A / 10 << endl;
//
//
//	////������ԿЭ��ƽ��ֵ
//	//double sum_C = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//
//	//	Con_gen();
//
//	//	sum_C = sum_C + tm.ElapsedTimeAsDouble() / n;
//
//	//	//cout << "������Կ��Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "��ԿЭ��ƽ��ֵΪ " << sum_C / 10 << endl;
//
//	////����H����ƽ��ֵ
//	//double sum_H = 0;
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	tm.StartTimer();
//
//	//	ev_single(0);
//
//	//	sum_H = sum_H + tm.ElapsedTimeAsDouble();
//
//	//	//cout << "������Կ��Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() / n << endl << endl;
//	//}
//	//cout << "��Կ�ռ�����ƽ��ֵΪ " << sum_H / 10 << endl;
//
//
//	tm.StartTimer();
//	cul_ev();
//	cout << "ʵ�־ۺ��ۼӻ��ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()*6 << endl << endl;
//
//
//	getchar();
//	getchar();
//	return 0;
//
//}