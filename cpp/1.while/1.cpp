#include<iostream>
#include<ctime>
using namespace std;

int main()
{
    //添加随机数种子，防止每一次随机数都一样
    srand((unsigned int)time(NULL));
	//1.系统生成一个随机数
	//2.提示玩家开始猜测
	//3.玩家输入猜测数字
	//4.判断输入数字过大还是过小
	//5.猜对，结束游戏
	//6.猜错，提示，重新输入
	int num = rand() % 100 + 1;//生成一个0-99的随机数，rand()%
	int num1 = 101;
	cout << "玩家请输入猜测的值" << endl;
	cin >> num1;
    cout<<"您输入的是"<<num1<<endl;
	while (num1 != num)
	{
		if (num1 > num)
		{
			cout << "输入值大于该数" << endl;
			cout << "玩家重新请输入猜测的值" << endl;
			cin >> num1;
		}
		else
		{
			cout << "输入值小于该数" << endl;
			cout << "玩家重新请输入猜测的值" << endl;
			cin >> num1;
		}
	}
	cout << "恭喜您，猜对啦" << "        该随机数为" << num << endl;
	cout << "您输入的是" << num1 << endl;
	system("pause");
}