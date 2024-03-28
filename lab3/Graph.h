#pragma once
#pragma once

// 存储图的顶点信息
struct Vex
{
	int num;		 // 景点编号
	char name[20];	 // 景点名字
	char desc[1024]; // 景点介绍
};

// 存储边的信息
struct Edge
{
	int vex1;	// 边的第一个顶点
	int vex2;	// 边的第二个顶点
	int weight; // 权值
};

// 顶点数组和邻接矩阵，用来保存图的信息
struct Graph
{
	int m_aAdjMatrix[20][20]; // 邻接矩阵
	Vex m_aVexs[20];		  // 顶点信息数组
	int m_nVexNum;			  // 当前图的顶点个数
};

// 定义链表 PathList 来保存所有路径
typedef struct Path
{
	int vexs[20]; // 保存一条路径
	Path* next;	  // 下一条路径
} *PathList;

// 初始化图
void Init(void);
// 插入顶点信息
bool InsertVex(Vex sVex);
// 插入边的信息
bool InsertEdge(Edge sEdge);
// 通过传入的顶点编号，返回对应顶点信息结构体
Vex GetVex(int v);
// 查询所有与指定顶点相连的边
int FindEdge(int v, Edge aEdge[]);
// 使用深度优先搜索算法遍历图
void DFS(int nVex, bool isVisited[], int& nIndex, PathList& pList);
// 通过调用 DFS 函数，得到深度有限搜索遍历的结果
void DFSTraverse(int nVex, PathList& pList);
// 寻找最短路径
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
// 通过 Prim 算法构建最小生成树
void FindMinTree(Edge aPath[]);
