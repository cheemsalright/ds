#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "Tourism.h"
#include "Graph.h"

using namespace std;

Graph m_Graph;

int main(void)
{
	int choice;

	// ϵͳ����
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
	printf("*��ӭ���뾰������ϵͳ*");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
	system("pause");
	system("cls");

	do
	{
		

		// �û�ѡ����
		cout << "������˵�����(0-5):";
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
			cout << "лл��ʹ�ñ�ϵͳ��" << endl;
			break;
		default:
			cout << "���������������������룡" << endl
				<< endl;
		}

	} while (choice != 0);

	return 0;
}
