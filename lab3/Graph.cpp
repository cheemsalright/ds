#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "Graph.h"

extern Graph m_Graph;

// 函数名：Init
// 参数：void
// 返回值：void
// 功能：实现图的初始化，权值信息都初始化为0
void Init(void)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			m_Graph.m_aAdjMatrix[i][j] = 0; // 权值信息初始化为0
		}
		m_Graph.m_nVexNum = 0; // 景点数目初始化为0
	}
}

// 函数名：InsertVex
// 参数：结构体vex
// 返回值：true：顶点未满   false：顶点已满
// 功能：通过传入结构体，将顶点的相关信息插入到顶点信息数组中
bool InsertVex(Vex sVex)
{
	if (m_Graph.m_nVexNum == 20)
	{
		// 顶点已满
		return false;
	}
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex; // 插入顶点信息
	return true;
}

// 函数名：InsertEdge
// 参数：Edge结构体
// 返回值：true:插入成功   false：下表越界
// 功能：通过传入Edge结构体，将边的相关信息插入到权值矩阵中
bool InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_Graph.m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_Graph.m_nVexNum)
	{
		// 下标越界
		return false;
	}
	// 插入边的信息
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}

// 函数名：GetVex
// 参数：输入的编号
// 返回值：对应编号的顶点信息结构体
// 功能：通过传入的顶点编号，返回对应顶点信息结构体
Vex GetVex(int v)
{
	return m_Graph.m_aVexs[v];
}

// 函数名：FindEdge
// 参数：nVex:想要查询的顶点   aEdge[]:
// 返回值：边的条数
// 功能：查询与指定顶点相连的边
int FindEdge(int nVex, Edge aEdge[])
{
	int k = 0;

	// 遍历整个图的邻接矩阵
	for (int i = 0; i < 20; i++)
	{
		if (m_Graph.m_aAdjMatrix[nVex][i] != 0 && nVex != i)
		{
			// 得到边的信息
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_Graph.m_aAdjMatrix[nVex][i];
			k++;
		}
	}
	return k;
}

// 函数名：DFS
// 参数：int nVex:顶点编号  bVisted[]:bool类型的数组，用来记录某个顶点是否被遍历过   int &nIndex:记录遍历深度   PathList &pList:遍历得到的结果
// 返回值：void
// 功能：使用深度优先搜索算法遍历图
void DFS(int nVex, bool isVisited[], int& nIndex, PathList& pList)
{
	isVisited[nVex] = true;		  // 修改为已访问
	pList->vexs[nIndex++] = nVex; // 访问顶点nVex

	int num = 0; // 被访问过的节点数
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		if (isVisited[i])
		{ // 如果当前i节点被访问过，则num++
			num++;
		}
	}

	if (num == m_Graph.m_nVexNum)
	{ // 如果所有节点都被访问过
		// 保存一条路径
		pList->next = new Path;
		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;
		pList->next = NULL;
	}
	else
	{
		for (int w = 0; w < m_Graph.m_nVexNum; w++)
		{ // 搜索v的所有邻接点
			if (m_Graph.m_aAdjMatrix[nVex][w] > 0 && !isVisited[w])
			{									  // 如果w是nVex的邻接点并未被访问
				DFS(w, isVisited, nIndex, pList); // 递归调用DFS
				isVisited[w] = false;			  // 改为未访问
				nIndex--;						  // 索引值减1
			}
		}
	}
}

// 函数名：DFSTraverse
// 参数：int nVex：顶点编号   PathList &pList：遍历得到的结果
// 返回值：void
// 功能：通过调用DFS（）函数，得到深度有限搜索遍历的结果
void DFSTraverse(int nVex, PathList& pList)
{
	int nIndex = 0;
	bool bVisited[20] = { false };
	DFS(nVex, bVisited, nIndex, pList);
}

// 函数名：FindShortPath
// 功能：寻找最短路径
// 参数：景点的起始跟目的编号；边的路径结构数组
// 返回值：nIndex
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[20][20]; // 最短路径，行表示终点，列表示从起点到终点的最短路径的每一步
	int nShortDistance[20]; // 保存从起点到任一顶点的最短距离
	bool aVisited[20];		// 判断某点是否已在最短路径中
	int v;					// 每一次找到的可以加入集合的顶点

	// 初始化
	for (v = 0; v < m_Graph.m_nVexNum; v++)
	{
		aVisited[v] = false;

		if (m_Graph.m_aAdjMatrix[nVexStart][v] != 0)
		{
			// 如果顶点v和nVexStart相连，则最短距离设置为两顶点间的距离
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];
		}
		else
		{
			// 如果不相连，则最短距离设置为最大值
			nShortDistance[v] = 0x7FFFFFFF;
		}

		nShortPath[v][0] = nVexStart; // 起始点为nVexStart
		// 初始化最短路径
		for (int w = 1; w < m_Graph.m_nVexNum; w++)
		{
			nShortPath[v][w] = -1;
		}
	}
	// 初始化，将nVexStart顶点加入到集合中
	aVisited[nVexStart] = true;

	int min; // 暂存路径的最小值
	for (int i = 1; i < m_Graph.m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false; // 判断是否还有顶点可以加入集合

		for (int w = 0; w < m_Graph.m_nVexNum; w++)
		{
			if (!aVisited[w] && nShortDistance[w] < min)
			{
				v = w;					 // w顶点距离nVexStart顶点最近
				min = nShortDistance[w]; // w到nVexStart的最短距离为min
				bAdd = true;
			}
		}
		// 如果没有顶点可以加入到集合，则跳出循环
		if (!bAdd)
		{
			break;
		}

		aVisited[v] = true;	  // 将w顶点加入到集合
		nShortPath[v][i] = v; // 每次找到最短路径后，就相当于从源点出发到了终点，所以nShortPath[v][i]=v

		for (int w = 0; w < m_Graph.m_nVexNum; w++)
		{
			// 将w作为中间点计算nVexStart到所有顶点的最短距离
			if (!aVisited[w] && (min + m_Graph.m_aAdjMatrix[v][w] < nShortDistance[w]) && (m_Graph.m_aAdjMatrix[v][w] > 0))
			{
				// 如果有新的最短距离,则更新最短路径及距离
				nShortDistance[w] = min + m_Graph.m_aAdjMatrix[v][w];
				for (int i = 0; i < m_Graph.m_nVexNum; i++)
				{
					// 如果通过w到达顶点i的距离比较短，则将w的最短路径赋值给i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;

	// 将最短路径保存到边的结构体数组中
	for (int i = 1; i < m_Graph.m_nVexNum; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_Graph.m_aAdjMatrix[nVex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}
	return nIndex;
}

// 函数名：FindMinTree
// 功能：通过Prim算法构建最小生成树
// 参数：Edge aPath[]
// 返回值：void
void FindMinTree(Edge aPath[])
{
	bool aVisited[20] = { false }; // 判断某顶点是否在最小生成树中
	aVisited[0] = true;			 // 从0号顶点开始，加入到集合中
	int min;
	int nVex1, nVex2;

	for (int k = 0; k < m_Graph.m_nVexNum - 1; k++)
	{
		min = 0X7FFFFFFF;

		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			// 从集合中取一个顶点
			if (aVisited[i])
			{
				for (int j = 0; j < m_Graph.m_nVexNum; j++)
				{
					// 从不在集合的顶点中取出一个顶点
					if (!aVisited[j])
					{
						if ((m_Graph.m_aAdjMatrix[i][j] < min) && (m_Graph.m_aAdjMatrix[i][j] != 0))
						{
							nVex1 = i;
							nVex2 = j;
							// 找出最短边
							min = m_Graph.m_aAdjMatrix[i][j];
						}
					}
				}
			}
		}

		// 保存最短边的两个顶点
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = m_Graph.m_aAdjMatrix[nVex1][nVex2];

		// 将两个顶点加入集合
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}
}
