#pragma once
#pragma once

// ��ȡ�ļ���������������ͼ
void CreateGraph(void);
// ���� GetVex() �������õ����ж�����Ϣ�����
std::string GetSpotInfo(int);
// ͨ������ DFSTraverse() ������ʵ�����ξ��㵼�����ܣ�����ѯ���ľ��㵼��·����ʾ�ڽ�����
//void TravelPath();
// ���� Graph.cpp �ļ��е� FindShortPath() ������ѯ�������������·���;���
std::string FindShortPath(int, int);
// ��ѯ�����·�滮ͼ
std::string DesignPath();
