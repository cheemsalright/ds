#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "Tourism.h"
#include "Graph.h"

using namespace std;

Graph m_Graph;

int main(void)
{
	int choice;

	// 系统界面
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
	printf("*欢迎进入景区管理系统*");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
	system("pause");
	system("cls");

	do
	{
		// 输出系统菜单
		cout << "=====景区信息管理系统=====" << endl;
		cout << "*    1.创建景区景点图    *" << endl;
		cout << "*    2.查询景点信息      *" << endl;
		cout << "*    3.旅游景点导航      *" << endl;
		cout << "*    4.搜索最短路径      *" << endl;
		cout << "*    5.铺设电路规划      *" << endl;
		cout << "*    0.退出              *" << endl;
		cout << "==========================" << endl;

		// 用户选择功能
		cout << "请输入菜单项编号(0-5):";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			CreateGraph();
			break;
		case 2:
			GetSpotInfo(3);
			break;
		case 3:
			//TravelPath();
			break;
		case 4:
			FindShortPath(1,5);
			break;
		case 5:
			DesignPath();
			break;
		case 0:
			cout << "谢谢您使用本系统！" << endl;
			break;
		default:
			cout << "您的输入有误！请重新输入！" << endl
				<< endl;
		}

	} while (choice != 0);

	return 0;
}
