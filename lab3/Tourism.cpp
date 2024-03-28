#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <sstream>

#include "Graph.h"

using namespace std;

extern Graph m_Graph;

// 函数名：LoadVex
// 参数：void
// 返回值：void
// 功能：实现从Vex.txt文件中读取景点信息并输出
void LoadVex(void)
{
	ifstream VexFile("Vex.txt");
	if (!VexFile)
	{
		cout << "Vex.txt文件打开失败，请检查！" << endl;
		return;
	}

	// 暂存从Vex.txt读取到的一行数据
	char num[2];
	char name[20];
	char desc[1024];
	Vex sVex;

	// 逐行读取Vex.txt中的数据
	VexFile.getline(num, 2); // 将第一行的数据读出丢掉

	//cout << "景区数目：" << atoi(num) << endl;
	//cout << "-----顶点-----" << endl;
	// 将顶点信息保存到顶点数组中
	while (VexFile.getline(num, 2))
	{
		sVex.num = atoi(num);
		VexFile.getline(name, 20);
		strcpy(sVex.name, name);
		VexFile.getline(desc, 1024);
		strcpy(sVex.desc, desc);

		// 将顶点信息输出
		cout << sVex.num << "-" << sVex.name << endl;

		// 设置图的顶点
		if (!InsertVex(sVex))
		{
			//cout << "新增景点失败！" << endl;
			continue;
		}
	}
	//cout << "------------" << endl;
	VexFile.close();
}

// 函数名：LoadPath
// 参数：void
// 返回值：void
// 功能：实现从Edge.txt文件中读取路径信息并输出
void LoadPath()
{
	ifstream EdgeFile("Edge.txt");
	if (!EdgeFile)
	{
		//cout << "Edge.txt文件打开失败，请检查！" << endl;
		return;
	}

	Edge edge;
	//cout << "------边------" << endl;
	while (EdgeFile)
	{
		EdgeFile >> edge.vex1 >> edge.vex2 >> edge.weight;
		//cout << "<" << edge.vex1 << "," << edge.vex2 << ">   " << edge.weight << endl;

		// 设置图的边
		if (!InsertEdge(edge))
		{
			//cout << "新增路径信息失败！" << endl;
			continue;
		}
	}
	//cout << "-------------" << endl;
	EdgeFile.close();
	//cout << "======================" << endl;
}

// 函数名:CreateGraph
// 参数：void
// 返回值：void
// 功能：读取文件，获取景点信息和道路信息
void CreateGraph(void)
{

	Init();		// 初始化图
	LoadVex();	// 从Vex.txt文件中读取景点信息并输出
	LoadPath(); // 从Edge.txt文件中读取路径信息并输出
}

// 函数名：GetSpotInfo
// 参数：void
// 返回值：void
// 功能：调用GetVex（）函数，得到所有顶点信息并输出
std::string GetSpotInfo(int number)
{
	//cout << "\n=====查询景点信息=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0)
	{
		//cout << "请先创建图！" << endl;
		//return;
	}

	// 提示用户根据编号进行查询
	//cout << "\n请输入想要查询的景点编号：";
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

// 函数名：TravelPath
// 参数：void
// 返回值：void
// 功能：通过调用DFSTraverse（）函数，实现旅游景点导航功能，将查询到的景点导航路线显示在界面上
//void TravelPath()
//{
//	//cout << "\n=======旅游景点导航======" << endl;
//
//	
//	//cout << "=========================" << endl;
//
//	// 输入景点编号
//	cout << "请输入想要导航的起始点编号：";
//	int startNum;
//	cin >> startNum;
//	if (startNum < 0 || startNum >= m_Graph.m_nVexNum)
//	{
//		cout << "您输入的编号有误！" << endl;
//		return;
//	}
//
//	// 遍历景区景点图
//	PathList pList = new Path;
//	PathList pHead = pList;
//	DFSTraverse(startNum, pList);
//
//	cout << endl;
//
//	// 输出遍历结果
//	cout << "导航路线为：" << endl;
//	int i = 1;
//	pList = pHead;
//	while (pList->next != NULL)
//	{
//		Vex vex = GetVex(pList->vexs[0]);
//		cout << "路线" << i++ << ":" << vex.name;
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

// 函数名：FindShortPath
// 功能：调用Graph.cpp文件中的FindShortPath函数查询两个景点间的最短路径和距离
// 参数：void
// 返回值：void
std::string FindShortPath(int a,int b)
{
	//cout << "\n======搜索最短路径======\n";

	int nVexNum = m_Graph.m_nVexNum;

	if (nVexNum == 0)
	{
		//cout << "请先创建图！" << endl;
	}


	// 输入两个景点的编号
	int start_place=a, end_place=b;

	if (start_place < 0 || start_place >= m_Graph.m_nVexNum || end_place < 0 || end_place >= m_Graph.m_nVexNum)
	{
		//cout << "输入错误！请重新输入！！！" << endl;
	}

	Edge aPath[20]; // 边信息数组，依次保存最短的路径

	for (int i = 0; i < 20; i++)
	{
		// 初始化边信息数组
		aPath->vex1 = -1;
		aPath->vex2 = -1;
		aPath->weight = -1;
	}

	// 搜索最短路径
	int index = FindShortPath(start_place, end_place, aPath);
	int length = 0; // 最短路径总长度
	Vex sVex = GetVex(aPath[0].vex1);

	// 得到最短路径和最短距离
	//cout << "\n最短路径为：" << sVex.name;

	std::ostringstream oss;
	for (int i = 0; i < index; i++) {
		Vex sVex = GetVex(aPath[i].vex2);
		oss << "->" << sVex.name << " ";
	}
	oss << std::endl;
	for (int i = 0; i < index; i++) {
		length += aPath[i].weight;
	}
	oss << "最短距离为: " << length << "米" << std::endl << std::endl;
	return oss.str();
}

// 函数名：DesignPath
// 功能：查询电路铺设规划图
// 参数：void
// 返回值：void

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

