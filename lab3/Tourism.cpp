#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <sstream>

#include "Graph.h"

using namespace std;

extern Graph m_Graph;

// ��������LoadVex
// ������void
// ����ֵ��void
// ���ܣ�ʵ�ִ�Vex.txt�ļ��ж�ȡ������Ϣ�����
void LoadVex(void)
{
	ifstream VexFile("Vex.txt");
	if (!VexFile)
	{
		cout << "Vex.txt�ļ���ʧ�ܣ����飡" << endl;
		return;
	}

	// �ݴ��Vex.txt��ȡ����һ������
	char num[2];
	char name[20];
	char desc[1024];
	Vex sVex;

	// ���ж�ȡVex.txt�е�����
	VexFile.getline(num, 2); // ����һ�е����ݶ�������

	//cout << "������Ŀ��" << atoi(num) << endl;
	//cout << "-----����-----" << endl;
	// ��������Ϣ���浽����������
	while (VexFile.getline(num, 2))
	{
		sVex.num = atoi(num);
		VexFile.getline(name, 20);
		strcpy(sVex.name, name);
		VexFile.getline(desc, 1024);
		strcpy(sVex.desc, desc);

		// ��������Ϣ���
		cout << sVex.num << "-" << sVex.name << endl;

		// ����ͼ�Ķ���
		if (!InsertVex(sVex))
		{
			//cout << "��������ʧ�ܣ�" << endl;
			continue;
		}
	}
	//cout << "------------" << endl;
	VexFile.close();
}

// ��������LoadPath
// ������void
// ����ֵ��void
// ���ܣ�ʵ�ִ�Edge.txt�ļ��ж�ȡ·����Ϣ�����
void LoadPath()
{
	ifstream EdgeFile("Edge.txt");
	if (!EdgeFile)
	{
		//cout << "Edge.txt�ļ���ʧ�ܣ����飡" << endl;
		return;
	}

	Edge edge;
	//cout << "------��------" << endl;
	while (EdgeFile)
	{
		EdgeFile >> edge.vex1 >> edge.vex2 >> edge.weight;
		//cout << "<" << edge.vex1 << "," << edge.vex2 << ">   " << edge.weight << endl;

		// ����ͼ�ı�
		if (!InsertEdge(edge))
		{
			//cout << "����·����Ϣʧ�ܣ�" << endl;
			continue;
		}
	}
	//cout << "-------------" << endl;
	EdgeFile.close();
	//cout << "======================" << endl;
}

// ������:CreateGraph
// ������void
// ����ֵ��void
// ���ܣ���ȡ�ļ�����ȡ������Ϣ�͵�·��Ϣ
void CreateGraph(void)
{

	Init();		// ��ʼ��ͼ
	LoadVex();	// ��Vex.txt�ļ��ж�ȡ������Ϣ�����
	LoadPath(); // ��Edge.txt�ļ��ж�ȡ·����Ϣ�����
}

// ��������GetSpotInfo
// ������void
// ����ֵ��void
// ���ܣ�����GetVex�����������õ����ж�����Ϣ�����
std::string GetSpotInfo(int number)
{
	//cout << "\n=====��ѯ������Ϣ=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0)
	{
		//cout << "���ȴ���ͼ��" << endl;
		//return;
	}

	// ��ʾ�û����ݱ�Ž��в�ѯ
	//cout << "\n��������Ҫ��ѯ�ľ����ţ�";
	int num=number;
	//cin >> num;

	std::ostringstream oss;
	if (num < 0 || num >= m_Graph.m_nVexNum) {
		//return ;
	}
	else {
		Vex sVex = GetVex(num);
		oss << sVex.name << ":" << sVex.desc << std::endl;
		Edge aEdge[20];
		int EdgeNum = FindEdge(num, aEdge);
		for (int i = 0; i < EdgeNum; i++) {
			if (i > 0) {
				oss << " ";
			}
			Vex v1 = GetVex(aEdge[i].vex1);
			Vex v2 = GetVex(aEdge[i].vex2);
			oss << v1.name << "->" << v2.name << "   " << aEdge[i].weight << "m";
		}
	}
	return oss.str();
}

// ��������TravelPath
// ������void
// ����ֵ��void
// ���ܣ�ͨ������DFSTraverse����������ʵ�����ξ��㵼�����ܣ�����ѯ���ľ��㵼��·����ʾ�ڽ�����
//void TravelPath()
//{
//	//cout << "\n=======���ξ��㵼��======" << endl;
//
//	
//	//cout << "=========================" << endl;
//
//	// ���뾰����
//	cout << "��������Ҫ��������ʼ���ţ�";
//	int startNum;
//	cin >> startNum;
//	if (startNum < 0 || startNum >= m_Graph.m_nVexNum)
//	{
//		cout << "������ı������" << endl;
//		return;
//	}
//
//	// ������������ͼ
//	PathList pList = new Path;
//	PathList pHead = pList;
//	DFSTraverse(startNum, pList);
//
//	cout << endl;
//
//	// ����������
//	cout << "����·��Ϊ��" << endl;
//	int i = 1;
//	pList = pHead;
//	while (pList->next != NULL)
//	{
//		Vex vex = GetVex(pList->vexs[0]);
//		cout << "·��" << i++ << ":" << vex.name;
//		for (int j = 1; j < m_Graph.m_nVexNum; j++)
//		{
//			vex = GetVex(pList->vexs[j]);
//			cout << "->" << vex.name;
//		}
//		cout << endl;
//		pList = pList->next;
//	}
//	cout << endl;
//
//	delete pList;
//	pList = NULL;
//	pHead = NULL;
//}

// ��������FindShortPath
// ���ܣ�����Graph.cpp�ļ��е�FindShortPath������ѯ�������������·���;���
// ������void
// ����ֵ��void
std::string FindShortPath(int a,int b)
{
	//cout << "\n======�������·��======\n";

	int nVexNum = m_Graph.m_nVexNum;

	if (nVexNum == 0)
	{
		//cout << "���ȴ���ͼ��" << endl;
	}


	// ������������ı��
	int start_place=a, end_place=b;

	if (start_place < 0 || start_place >= m_Graph.m_nVexNum || end_place < 0 || end_place >= m_Graph.m_nVexNum)
	{
		//cout << "����������������룡����" << endl;
	}

	Edge aPath[20]; // ����Ϣ���飬���α�����̵�·��

	for (int i = 0; i < 20; i++)
	{
		// ��ʼ������Ϣ����
		aPath->vex1 = -1;
		aPath->vex2 = -1;
		aPath->weight = -1;
	}

	// �������·��
	int index = FindShortPath(start_place, end_place, aPath);
	int length = 0; // ���·���ܳ���
	Vex sVex = GetVex(aPath[0].vex1);

	// �õ����·������̾���
	//cout << "\n���·��Ϊ��" << sVex.name;

	std::ostringstream oss;
	for (int i = 0; i < index; i++) {
		Vex sVex = GetVex(aPath[i].vex2);
		oss << "->" << sVex.name << " ";
	}
	oss << std::endl;
	for (int i = 0; i < index; i++) {
		length += aPath[i].weight;
	}
	oss << "��̾���Ϊ: " << length << "��" << std::endl << std::endl;
	return oss.str();
}

// ��������DesignPath
// ���ܣ���ѯ��·����滮ͼ
// ������void
// ����ֵ��void

std::string DesignPath() {
	std::stringstream oss;

	Edge aPath[20];
	FindMinTree(aPath);

	int nVexNum = m_Graph.m_nVexNum;

	if (nVexNum == 0) {
		// No graph created
		return "";
	}

	int nAllLength = 0;

	for (int i = 0; i < m_Graph.m_nVexNum - 1; i++) {
		Vex nVex1 = GetVex(aPath[i].vex1);
		Vex nVex2 = GetVex(aPath[i].vex2);

		oss << "\t" << nVex1.name << "-" << nVex2.name << ":" << aPath[i].weight << "m" << std::endl;
		nAllLength += aPath[i].weight;
	}

	oss << nAllLength; // Appending the total length at the end

	return oss.str();
}

