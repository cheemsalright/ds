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
		// ���ϵͳ�˵�
		cout << "=====������Ϣ����ϵͳ=====" << endl;
		cout << "*    1.������������ͼ    *" << endl;
		cout << "*    2.��ѯ������Ϣ      *" << endl;
		cout << "*    3.���ξ��㵼��      *" << endl;
		cout << "*    4.�������·��      *" << endl;
		cout << "*    5.�����·�滮      *" << endl;
		cout << "*    0.�˳�              *" << endl;
		cout << "==========================" << endl;

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
			cout << "лл��ʹ�ñ�ϵͳ��" << endl;
			break;
		default:
			cout << "���������������������룡" << endl
				<< endl;
		}

	} while (choice != 0);

	return 0;
}
