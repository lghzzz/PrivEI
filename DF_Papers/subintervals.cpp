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
////取随机数的函数
//int getRand(int min, int max) 
//{
//    return (rand() % (max - min)) + min + 1;
//}
//
////用户数
//int member;
//
////每个用户自己的值
//int user[1000];
//
////初始切割区间
//int cutt[1000];
//
////用于存放最终切割区间
//vector<int> v1;
//
////标记数组，用于不生成重复的随机值
//bool vis1[2000000] = {false};
//bool vis2[2000000] = {false};
//
////递归调用时，用于递归时的随机生成区间边界的存放以及对应的标记函数,
//int cut_temp[1000][1000];
//bool vis_temp[500][2000000] = {false};
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
//
////随机数生成函数，几个参数是：存放随机值的变量、标记数组、随机数下界、随机数上界（左闭右开）、生成随机数的个数
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
////初步计算每个区间内用户个数的函数，还没有加入H(X)
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
////论文中的切割函数，几个参数是：下界、上界、区间内用户个数、递归深度（次数）
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
//    //用户数
//    cout << "请输入用户数："<< endl;
//    cin >> member;
//    cout << endl;
//
//    //上界
//    int upper = pow(member, 3);
//
//    //论文函数中的三个定值
//    L0 = ceil(log(member) / log(log(member)));
//    L1 = ceil(pow(ceil(log(member)), 4/3));
//    L2 = pow(ceil(log(member)),3/2);
//
//    srand(time(0));
//
//    //初始化用户随机数
//    initer(user, vis1, 0, upper, member);
//
//    //初次均分区间
//    for (int i = 0; i < member - 1; i++)
//    {
//        cutt[i] = (i + 1) * pow(member, 2);
//    }
//
//    //排序是为了便于后面划分自子区间工作
//    sort(user, user + member);
//    sort(cutt, cutt + member -1);
//
//
//    cout << "用户的值为：" << endl;
//    for (int i = 0; i < member; i++)
//    {
//        cout << user[i] << " ";
//    }
//    cout << endl;
//
//
//    cout << "L0、L0'、L0''的值为：" << endl;
//    cout << L0 << " " << L1 << " " << L2 << endl;
//
//
//    cout << "初始化分区间为：" << endl;
//    cout << "1" << " ";
//    for (int i = 0; i < member - 1; i++)
//    {
//        cout << cutt[i] << " ";
//    }
//    cout << upper << endl;
//
//    //调用划分区间函数，第一个和最后一个与以上下界作为上下限，因此单独列出
//    PartitionIntervals(0, cutt[0], CountNumbers(0, cutt[0]), 0);
//    for (int i = 0; i < member - 2; i = i + 1)
//    {
//        PartitionIntervals(cutt[i], cutt[i + 1], CountNumbers(cutt[i], cutt[i + 1]), 0);
//    }
//    PartitionIntervals(cutt[member - 2], upper, CountNumbers(cutt[member - 2], upper), 0);
//
//    //区间合并
//    //v1[v1.size() - 1] = upper;
//    for (int i = 0; i < v1.size(); i++)
//    {
//        if (i % 2 == 0)
//            v1[i] = v1[i]+ 1;
//    }
//
//    cout << "区间划分的值为：" << endl;
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
//    cout << endl << "需计算H（x)的次数为：" << num_sum << endl;
//
//    return 0;
//}
