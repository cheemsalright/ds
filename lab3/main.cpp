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
			cout<<GetSpotInfo(3)<<endl;
			break;
		case 3:
			//TravelPath();
			break;
		case 4:
			cout<<FindShortPath(1,5)<<endl;
			break;
		case 5:
			cout << DesignPath() << endl;
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
