// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
/*
以下是交换使用的数据结构
作者：李洪烈
时间：2020/6/1
*/
typedef struct _DoublePoint {
	double x;					//经度
	double y;					//纬度
}DoublePoint;

typedef struct _boat
{
	double longitude;//经度->0
	double latitude;//纬度->1
	double azimuth;//航向->2:北顺时针转动多少度
	double speed;//航速->3
	char Name[32];
	_boat* next;
	_boat()
	{
		longitude = 181;
		latitude = 91;
		azimuth = 0;
		speed = 0;

		memset(Name, 0, 32);
		next = NULL;
	}
	~_boat()
	{
		if (next != NULL)
			delete next;
	}
}boat;

typedef struct _RouteLine {
	double longitude;//经度->0
	double latitude;//纬度->1
	double XTE;
	int number;//航线序号 
	_RouteLine* next;
	_RouteLine()
	{
		next = NULL;
	}
	~_RouteLine()
	{
		if (next != NULL)
			delete next;
	}
}RouteLine;

typedef struct  _GridInfo
{
	DoublePoint StartPoint;
	DoublePoint EndPoint;
	DoublePoint offsetValue;
	int xNumber;
	int yNumber;
	unsigned char* GridInfo;
}GridInfo;

/*
作者:郑易松
定义的数据结构
时间：2020/06/07
*/
struct Point
{
	int x, y;																					//点坐标，这里为了方便按照C++的数组来计算，x代表横排，y代表竖列, length列表长度
	Point(int _x, int _y) :x(_x), y(_y)
	{
	}
};

#endif //PCH_H
