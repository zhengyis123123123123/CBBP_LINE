// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 经纬度转栅格坐标	(李洪烈提供函数)
// 输入：经纬度(船位坐标)、静态障碍物结构体
// 输出：新的坐标点结构体
Point* LonLatToCoordinate(double longitude, double latitude, GridInfo* StaticGrid)
{
	Point* point = new Point(-1, -1);
	if (StaticGrid == NULL || StaticGrid->xNumber == -1 || StaticGrid->yNumber == -1) {
		TRACE("静态数据传输错误，为空或越界\n");
	}
	int x = (int)((longitude - StaticGrid->StartPoint.x) / (StaticGrid->offsetValue.x / 60.f) + 0.5);
	int y = (int)((latitude - StaticGrid->StartPoint.y) / (StaticGrid->offsetValue.y / 60.f) + 0.5);
	if (x < 0 || x >= StaticGrid->xNumber || y < 0 || y >= StaticGrid->yNumber) {
		TRACE("数据传输错误，传入的数据越界\n");
	}
	point->x = x;
	point->y = y;
	return point;
}

// 方格坐标转纬度
double GetLonLatFromIDLat(GridInfo* chart, int x, int y)
{
	if (chart == NULL)
		return 0.0;
	if (chart->xNumber == -1 || chart->yNumber == -1)
		return 0.0;
	double lat = 0.0;
	if (y == 0) {
		lat = 0.0;
	}
	lat = chart->StartPoint.y + chart->offsetValue.y / 60 * y;
	return lat;
}

// 方格坐标转经度
double GetLonLatFromIDLon(GridInfo* chart, int x, int y)
{
	if (chart == NULL)
		return 0.0;
	if (chart->xNumber == -1 || chart->yNumber == -1)
		return 0.0;
	double lon = 0.0;
	if (x == 0) {
		lon = 0.0;
	}
	lon = chart->StartPoint.x + chart->offsetValue.x / 60 * x;
	return lon;
}

// 任务2020/12/4号下达
// Bresenham算法
// 输入参数
// 起始点X、Y坐标
// 终点X、Y坐标
// 返回值：链表，由起始点到终点，不带头节点
Point* CalculateBresenham(int startX, int startY, int endX, int endY) {
	Point* head = 0, * end = 0;//创建头指针以及尾指针
	int dx = abs(endX - startX);
	int dy = abs(endY - startY);
	bool is_great_than_45_degree = false;//用于表示起始点和终点的斜率
	if (dx <= dy)
		// 大于45度
		// Y 方向上变化速率快于 X 方向上变化速率，选择在 Y 方向上迭代，在每次迭代中计算 X 轴上变化；
		is_great_than_45_degree = true;
	int fx = ((endX - startX) > 0 ? 1 : -1);
	int fy = ((endY - endX) > 0 ? 1 : -1);
	if (dy == 0)//0°
		fy = 0;
	if (dx == 0)//90°
		fx = 0;
	int ix = startX;
	int iy = startY;
	int p1 = 2 * dy - dx; //小于等于45°
	int p2 = 2 * dx - dy; //大于45°
	if (is_great_than_45_degree) {
		while (iy != endY) {
			//将点添加到链表中
			Point* p = new Point;
			p->x = ix;
			p->y = iy;
			if (head == 0)          // 空链表
				head = p;
			else                      // 非空链表
				end->next = p;
			end = p;               // 修改尾指针
			p->next = 0;
			//p2>0
			if (p2 > 0) {
				p2 += 2 * (dx - dy);
				ix += fx;
			}
			else {
				p2 += 2 * dx;
			}
			iy += fy;
		}
	}
	else {
		while (ix != endX) {
			Point* p = new Point;
			p->x = ix;
			p->y = iy;
			if (head == 0)          // 空链表
				head = p;
			else                      // 非空链表
				end->next = p;
			end = p;               // 修改尾指针
			p->next = 0;

			//p1>0
			if (p1 > 0) {
				p1 += 2 * (dy - dx);
				iy += fy;
			}
			else {
				p1 += 2 * dy;
			}
			ix += fx;

		}
	}
	//将终点添加到链表中
	Point* p = new Point;
	p->x = endX;
	p->y = endY;
	if (head == 0)          // 空链表
		head = p;
	else                      // 非空链表
		end->next = p;
	end = p;               // 修改尾指针
	p->next = 0;
	return head;//返回链表中起始点的地址
}

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
RouteLine* CbbpLine(boat* myBoat, RouteLine* lineData, GridInfo* StaticGrid) {

	return NULL;
}

// 删除旧航线
void ReleaseRouteLine(RouteLine* pRoute)
{
	if (pRoute != NULL)
	{
		delete pRoute;
	}
}