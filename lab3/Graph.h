#pragma once
#pragma once

// �洢ͼ�Ķ�����Ϣ
struct Vex
{
	int num;		 // ������
	char name[20];	 // ��������
	char desc[1024]; // �������
};

// �洢�ߵ���Ϣ
struct Edge
{
	int vex1;	// �ߵĵ�һ������
	int vex2;	// �ߵĵڶ�������
	int weight; // Ȩֵ
};

// ����������ڽӾ�����������ͼ����Ϣ
struct Graph
{
	int m_aAdjMatrix[20][20]; // �ڽӾ���
	Vex m_aVexs[20];		  // ������Ϣ����
	int m_nVexNum;			  // ��ǰͼ�Ķ������
};

// �������� PathList ����������·��
typedef struct Path
{
	int vexs[20]; // ����һ��·��
	Path* next;	  // ��һ��·��
} *PathList;

// ��ʼ��ͼ
void Init(void);
// ���붥����Ϣ
bool InsertVex(Vex sVex);
// ����ߵ���Ϣ
bool InsertEdge(Edge sEdge);
// ͨ������Ķ����ţ����ض�Ӧ������Ϣ�ṹ��
Vex GetVex(int v);
// ��ѯ������ָ�����������ı�
int FindEdge(int v, Edge aEdge[]);
// ʹ��������������㷨����ͼ
void DFS(int nVex, bool isVisited[], int& nIndex, PathList& pList);
// ͨ������ DFS �������õ�����������������Ľ��
void DFSTraverse(int nVex, PathList& pList);
// Ѱ�����·��
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
// ͨ�� Prim �㷨������С������
void FindMinTree(Edge aPath[]);
