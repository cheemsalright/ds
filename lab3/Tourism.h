#pragma once
#pragma once

// 读取文件，创建景区景点图
void CreateGraph(void);
// 调用 GetVex() 函数，得到所有顶点信息并输出
std::string GetSpotInfo(int);
// 通过调用 DFSTraverse() 函数，实现旅游景点导航功能，将查询到的景点导航路线显示在界面上
//void TravelPath();
// 调用 Graph.cpp 文件中的 FindShortPath() 函数查询两个景点间的最短路径和距离
std::string FindShortPath(int, int);
// 查询铺设电路规划图
std::string DesignPath();
