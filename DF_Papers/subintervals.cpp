//#include<iostream>
//#include<cmath>
//#include<random>
//#include <ctime>
//#include <cstdlib>
//#include <vector>
//#include<algorithm>
//
//using namespace std;
//
////ȡ������ĺ���
//int getRand(int min, int max) 
//{
//    return (rand() % (max - min)) + min + 1;
//}
//
////�û���
//int member;
//
////ÿ���û��Լ���ֵ
//int user[1000];
//
////��ʼ�и�����
//int cutt[1000];
//
////���ڴ�������и�����
//vector<int> v1;
//
////������飬���ڲ������ظ������ֵ
//bool vis1[2000000] = {false};
//bool vis2[2000000] = {false};
//
////�ݹ����ʱ�����ڵݹ�ʱ�������������߽�Ĵ���Լ���Ӧ�ı�Ǻ���,
//int cut_temp[1000][1000];
//bool vis_temp[500][2000000] = {false};
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
//
////��������ɺ��������������ǣ�������ֵ�ı�����������顢������½硢������Ͻ磨����ҿ���������������ĸ���
//void initer(int a[], bool b[], int left, int right, int num)
//{
//    for (int i = 0; i < num; i++)
//    {
//        int r = getRand(left, right);
//        while (b[r] == true)
//        {
//            r = getRand(left, right);
//        }
//        a[i] = r;
//        b[r] = true;
//    }
//}
//
//
////��������ÿ���������û������ĺ�������û�м���H(X)
//int CountNumbers(int left, int right)
//{
//    int ans = 0;
//    for (int i = 0; i < member; i++)
//    {
//        if (user[i] > left && user[i] <= right)
//            ans++;
//    }
//    return ans;
//}
//
//
////�����е��и�������������ǣ��½硢�Ͻ硢�������û��������ݹ���ȣ�������
//void PartitionIntervals(int left, int right, int num, int turn)
//{
//    cout << left << " " << right << " " << endl;
//    if (num == 0)
//        return;
//
//    else if (num == 1)
//    {
//        sub_count[turn]++;
//        v1.push_back(left);
//        v1.push_back(right);
//        return;
//    }
//
//    else if (2 <= num <= L1)
//    {
//        sub_count[turn]++;
//
//        sub_user[turn] += num;
//
//        turn++;
//
//        int temp1 = pow(L1, 2);
//
//        if (num < temp1)
//            temp1 = num;
//
//
//        initer(cut_temp[turn], vis_temp[turn], left, right, temp1 - 1);
//        sort(cut_temp[turn], cut_temp[turn] + temp1 - 1);
//
//        PartitionIntervals(left, cut_temp[turn][0], CountNumbers(left, cut_temp[turn][0]), turn);
//
//        if(temp1 > 2)
//        for (int i = 0; i < temp1 - 2; i = i + 1)
//        {
//          PartitionIntervals(cut_temp[turn][i], cut_temp[turn][i + 1], CountNumbers(cut_temp[turn][i], cut_temp[turn][i + 1]), turn);
//        }
//
//        PartitionIntervals(cut_temp[turn][temp1 - 2], right, CountNumbers(cut_temp[turn][temp1 - 2], right), turn);
//    }
//
//    else
//    { 
//        sub_count[turn]++;
//
//        sub_user[turn] += num;
//
//        turn++;
//
//        int temp2 = pow(L2, 2);
//
//        if (num < temp2)
//            temp2 = num;
//
//
//        initer(cut_temp[turn], vis_temp[turn], left, right, temp2 - 1);
//        sort(cut_temp[turn], cut_temp[turn] + temp2 - 1);
//
//        PartitionIntervals(left, cut_temp[turn][0], CountNumbers(left, cut_temp[turn][0]), turn);
//
//        if (temp2 > 2)
//        for (int i = 0; i < temp2 - 2; i = i + 1)
//        {
//            PartitionIntervals(cut_temp[turn][i], cut_temp[turn][i + 1], CountNumbers(cut_temp[turn][i], cut_temp[turn][i + 1]), turn);
//        }
//
//        PartitionIntervals(cut_temp[turn][temp2 - 2], right, CountNumbers(cut_temp[turn][temp2 - 2], right), turn);
//    }
//
//}
//
//
//int main()
//{
//    //�û���
//    cout << "�������û�����"<< endl;
//    cin >> member;
//    cout << endl;
//
//    //�Ͻ�
//    int upper = pow(member, 3);
//
//    //���ĺ����е�������ֵ
//    L0 = ceil(log(member) / log(log(member)));
//    L1 = ceil(pow(ceil(log(member)), 4/3));
//    L2 = pow(ceil(log(member)),3/2);
//
//    srand(time(0));
//
//    //��ʼ���û������
//    initer(user, vis1, 0, upper, member);
//
//    //���ξ�������
//    for (int i = 0; i < member - 1; i++)
//    {
//        cutt[i] = (i + 1) * pow(member, 2);
//    }
//
//    //������Ϊ�˱��ں��滮���������乤��
//    sort(user, user + member);
//    sort(cutt, cutt + member -1);
//
//
//    cout << "�û���ֵΪ��" << endl;
//    for (int i = 0; i < member; i++)
//    {
//        cout << user[i] << " ";
//    }
//    cout << endl;
//
//
//    cout << "L0��L0'��L0''��ֵΪ��" << endl;
//    cout << L0 << " " << L1 << " " << L2 << endl;
//
//
//    cout << "��ʼ��������Ϊ��" << endl;
//    cout << "1" << " ";
//    for (int i = 0; i < member - 1; i++)
//    {
//        cout << cutt[i] << " ";
//    }
//    cout << upper << endl;
//
//    //���û������亯������һ�������һ���������½���Ϊ�����ޣ���˵����г�
//    PartitionIntervals(0, cutt[0], CountNumbers(0, cutt[0]), 0);
//    for (int i = 0; i < member - 2; i = i + 1)
//    {
//        PartitionIntervals(cutt[i], cutt[i + 1], CountNumbers(cutt[i], cutt[i + 1]), 0);
//    }
//    PartitionIntervals(cutt[member - 2], upper, CountNumbers(cutt[member - 2], upper), 0);
//
//    //����ϲ�
//    //v1[v1.size() - 1] = upper;
//    for (int i = 0; i < v1.size(); i++)
//    {
//        if (i % 2 == 0)
//            v1[i] = v1[i]+ 1;
//    }
//
//    cout << "���仮�ֵ�ֵΪ��" << endl;
//    for (int i = 0; i < v1.size(); i++)
//    {
//        
//        if (i % 2 == 0)
//            cout << v1[i] << "-";
//        else
//            cout << v1[i] << " ";
//    }
//
//    int num_sum = 0;
//    for (int i = 0; sub_user[i] != 0; i++)
//    {
//        num_sum = num_sum + sub_user[i];
//    }
//    num_sum += member;
//
//    cout << endl << "�����H��x)�Ĵ���Ϊ��" << num_sum << endl;
//
//    return 0;
//}
