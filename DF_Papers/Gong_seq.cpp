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
////��ȫ����M
//Integer M = 0xffffffffffffffff;
//
////r�Ĺ�˽Կ��t�Ĺ�˽Կ
//SecByteBlock rs[MAX][MAX];
//SecByteBlock rp[MAX][MAX];
//SecByteBlock ts[MAX][MAX];
//SecByteBlock tp[MAX][MAX];
//
////��Э��ֵ���յ�Э��ֵ
//Integer con1[MAX][MAX];
//Integer	con2[MAX][MAX];
//
//
//Integer SN_f[MAX][MAX];
//
//
////r��˽Կת���ͣ�t��˽Կת����
//Integer rs1[MAX][MAX];
//Integer rp1[MAX][MAX];
//Integer ts1[MAX][MAX];
//Integer tp1[MAX][MAX];
//
//
//
////vec�洢���ܿռ�,agg�������ۼ�֮��Ĵ�����
//Integer vec[MAX][MAX];
//Integer agg[MAX];
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
//
////������ܿռ���ֵת�����м����
//string con1_temp[MAX][MAX];
//string con2_temp[MAX][MAX];
//string j_temp[MAX];
//Integer s4_temp[MAX][MAX];
//Integer s5_temp[MAX][MAX];
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
////��������ÿ���������û������ĺ�������û�м���H(X)
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
////���к�����Hʱ�����
//void seq_space(int i, int l)
//{
//
//	for (int j = 0; j < n; j++)
//	{
//		Integer sum = 0;
//		for (int k = 0; k < l; k++)
//		{
//
//			if (i == k)
//			{
//				continue;
//			}
//
//			string s4 = hmac<SHA__256>("1", con1_temp[i][k]);
//			string s5 = hmac<SHA__256>("1", con2_temp[i][k]);
//			sum = (s4_temp[j][k] - s5_temp[j][k]) % M;
//		}
//	}
//}
//
////���û����к�����Hʱ�����
//void seq_ev_single(int i, int t)
//{
//	seq_space(i, t);
//}
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
////����˽Կ�͹�Կ�ĺ���������r��t���ԣ�
//void Key_gen()
//{
//	for (int i = 0; i < n; i++)
//	{
//
//		for (int j = 0; j < n; j++)
//		{
//			if (i == j)
//			{
//				continue;
//			}
//			DH d1(p, q, g);
//			DH d2(p, q, g);
//			SecByteBlock Pri(d1.PrivateKeyLength());
//			SecByteBlock Pub(d1.PublicKeyLength());
//			SecByteBlock Pri2(d2.PrivateKeyLength());
//			SecByteBlock Pub2(d2.PublicKeyLength());
//			d1.GenerateKeyPair(rng, Pri, Pub);
//			d2.GenerateKeyPair(rng, Pri2, Pub2);
//			rs[i][j] = Pri;
//			rp[i][j] = Pub;
//			ts[i][j] = Pri2;
//			tp[i][j] = Pub2;
//		}
//
//	}
//}
//
//
////����Э��ֵ�ĺ���������Э�̹���ʵ�ֵ������鹫˽Կ��ӦЭ�̣�
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
//			if (i == j)
//				continue;
//
//			//rij��tjiʵ��Э�̣������һ��Э��ֵ�������
//			d1.Agree(t1, rs[i][j], tp[j][i]);
//			Integer A;
//			A.Decode(t1.BytePtr(), t1.size());
//			con1[i][j] = A + 1;
//
//			//����Э��ֵ��ͬ���쳣�������A+1����
//			//con1[i][j] = A;
//
//			//rji��tijʵ��Э�̣�����ڶ���Э��ֵ�������
//			d2.Agree(t2, ts[j][i], rp[i][j]);
//			Integer B;
//			B.Decode(t2.BytePtr(), t2.size());
//			con2[i][j] = B;
//
//		}
//	}
//}
//
//
//
////���뺯������֮ǰ�����˽Կ��Կ��ַ�д洢�����ݽ��룬���浽Integer�͵�����������
//void Decode()
//{
//	Integer A, B, C, D;
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			A.Decode(rs[i][j].BytePtr(), rs[i][j].size());
//			B.Decode(rp[i][j].BytePtr(), rp[i][j].size());
//			rs1[i][j] = A;
//			rp1[i][j] = B;
//
//			C.Decode(ts[i][j].BytePtr(), ts[i][j].size());
//			D.Decode(tp[i][j].BytePtr(), tp[i][j].size());
//			ts1[i][j] = C;
//			tp1[i][j] = D;
//		}
//		
//	}
//}
//
//
////��һ�����ǽ�������ܿռ������е���ֵת�����������������ʱ��
//void temp_tran(int i)
//{
//	for (int j = 0; j < n; j++)
//	{
//		for (int k = 0; k < n; k++)
//		{
//			con1_temp[i][k] = its(con1[i][k]);
//			con2_temp[i][k] = its(con2[i][k]);
//			j_temp[j] = its(j);
//
//			 s4_temp[j][k] = tran1(hmac<SHA__256>(j_temp[j], con1_temp[i][k]));
//			 s5_temp[j][k] = tran1(hmac<SHA__256>(j_temp[j], con2_temp[i][k]));
//
//		}
//	}
//}
//
//
////��һ�����Ǽ�����ܿռ�����,����Ϊ�û���ţ����������Piv���գ����Լ�Pbi���գ�
//void key_space(int i)
//{
//	//��ȫ����M������64λȫ1ת����ʮ���ƣ�
//
//	for (int j = 0; j < n; j++)
//	{
//		Integer sum = 0;
//		for (int k = 0; k < n; k++)
//		{
//			//string s1,s2;
//
//			////s3��ʾ�к�
//			//string s3 = its(j);
//			//string s4,s5;
//			
//			
//			if (i == k)
//			{
//				continue;
//			}
//
//
//			////s1��s2�ֱ���ѭ����Ӧ�Ħ�Э��ֵ������ܲ����ͦ�Э��ֵ���ܲ���
//			//s1 = its(con1[i][k]);
//			//s2 = its(con2[i][k]);
//
//			//s4��s5�ֱ��ʾʹ��hmac���ܺ��H�����ı������ͼ����������е�HӦ�������߶��ۼ�����������������ѭ�������Ӧ��Ч��һ����
//			string s4 = hmac<SHA__256>(j_temp[j], con1_temp[i][k]);
//			string s5 = hmac<SHA__256>(j_temp[j], con2_temp[i][k]);
//
//			sum = sum + (s4_temp[j][k] - s5_temp[j][k]) % M;
//
//		}
//		
//		//���H������
//		vec[i][j] = sum;
//		//cout << vec[i][j] << endl
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
//	of.open(".\\dh\\rp2.txt");
//
//	//���n��˽Կ
//	of << "�û�˽ԿֵΪ��" << endl;
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			of << rs[i][j] << "   " << ts[i][j] << endl;
//		}
//		
//	}
//	of << endl;
//
//}
//
//
////�������ۼ�ev
//void cul_ev()
//{
//	for (int i = 0; i < n; i++)
//	{
//		Integer sum = 0;
//		for (int j = 0; j < n; j++)
//		{
//
//			if(i == j)
//				sum = (sum + vec[j][i] + 1) % M;
//			else
//				sum = (sum + vec[j][i]) % M;
//
//		}
//		agg[i] = sum;
//	}
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
//	cout << "���ɹ�˽Կ�����кŻ��ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()/n << endl << endl;
//
//	sec();
//
//	tm.StartTimer();
//	Con_gen();
//	cout << "����Э��ֵ���ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()/n << endl << endl;
//
//
//	temp_tran(0);
//	tm.StartTimer();
//	ev_single(0);
//	cout << "���ɼ��ܿռ���Ҫ��ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()* 5 << endl << endl;
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
//	cout << "���к������м��ܵ�ʱ��Ϊ�����룩��" << sum2/5 << endl << endl;
//
//
//	//tm.StartTimer();
//	//for (int i = 0; sub_count[i] != 0; i++)
//	//{
//	//	seq_ev_single(i, sub_count[i]);
//	//}
//	//cout << "���к������м��ܵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//    int num_sum = 0;
//    for (int i = 0; sub_user[i] != 0; i++)
//    {
//        num_sum = num_sum + sub_user[i];
//    }
//    num_sum += member;
//
//	cout << "num����Ϊ��" << num_sum << endl << endl;
//
//
//	tm.StartTimer();
//	Decode();
//	Output();
//	cout << "���벢������ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble() << endl << endl;
//
//	tm.StartTimer();
//	cul_ev();
//	cout << "ʵ�־ۺ��ۼӻ��ѵ�ʱ��Ϊ�����룩��" << tm.ElapsedTimeAsDouble()*6 << endl << endl;
//
//	getchar();
//	getchar();
//	return 0;
//
//}