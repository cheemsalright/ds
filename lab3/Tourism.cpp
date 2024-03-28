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
void LoadVex() {
	// 定义景点信息数组
	Vex vexArray[] = {
		{0, "A区", "风景优美，气候宜人。门票10元。"},
		{1, "B区", "风景优美，气候宜人。门票20元。"},
		{2, "C区", "风景优美，气候宜人。门票30元。"},
		{3, "D区", "风景优美，气候宜人。门票40元。"},
		{4, "E区", "风景优美，气候宜人。门票50元。"},
		{5, "F区", "风景优美，气候宜人。门票60元。"},
		{6, "G区", "风景优美，气候宜人。门票70元。"}
	};

	// 遍历景点信息数组，并将每个景点信息插入到图中
	for (const auto& vex : vexArray) {
		//cout << vex.num << "-" << vex.name << endl;
		InsertVex(vex); // 假设 InsertVex 函数可以将景点信息插入到图中
	}
}


// 函数名：LoadPath
// 参数：void
// 返回值：void
// 功能：实现从Edge.txt文件中读取路径信息并输出
void LoadPath() {
	// 定义路径信息数组
	Edge edgeArray[] = {
		{0, 2, 700},
		{0, 4, 1000},
		{0, 5, 600},
		{1, 2, 1000},
		{1, 6, 1000},
		{2, 3, 400},
		{3, 4, 300},
		{3, 6, 400},
		{4, 5, 600},
		{5, 6, 500}
	};

	// 遍历路径信息数组，并将每个路径信息插入到图中
	for (const auto& edge : edgeArray) {
		cout << "<" << edge.vex1 << "," << edge.vex2 << ">   " << edge.weight << endl;
		InsertEdge(edge); // 假设 InsertEdge 函数可以将路径信息插入到图中
	}
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

	oss << nAllLength<<"米"; // Appending the total length at the end

	return oss.str();
}

