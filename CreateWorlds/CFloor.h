#pragma once
#include "CVector2D.h"
#include "CRoom.h"
#include <vector>
#include <list>
#include "CGrafo.h"

struct Triangle
{
	node *point0;
	node *point1;
	node *point2;
};
class CFloor
{
private:
	int m_iEllipseWidth;
	int m_iEllipseHeight;
	int m_iMinWidthSizeRoom;
	int m_iMaxWidthSizeRoom;
	int m_iMinHeightSizeRoom;
	int m_iMaxHeightSizeRoom;
	int m_iNumberRooms;
	int m_iOffsetX;
	int m_iOffsetY;

	std::vector<node>::iterator selectedNodeDelaunay;
public:
	std::list<Triangle> m_DelaunayTriangles;
	CVector2D m_ContainerRectangle;
	float m_ContainerRectangleWidth;
	float m_ContainerRectangleHeight;

	std::vector<node> m_graph;
	std::vector<CRoom> m_vRooms;
	void SetSizeRoom(int minWidth, int minHeight, int maxWidth, int maxHeight);
	void SetSizeEllipse(int width, int height);
	void SetNumberOfRooms(int numberRooms);
	void CreateRooms();
	void PrepareDelaunayTriangulations();
	bool StepDelaunayTriangulations();
	bool SeparateRooms();
	bool IsInsideNodeInCircle(CVector2D origin, float radius);
	void FilterRooms(int minWidth, int minHeight, int maxWidth, int maxHeight);
	CVector2D CreatePointInsideEllipse();
	void CreateFirstTriangule();
	void Init();
	void SetOffset(int x, int y);
	CFloor();
	~CFloor();
};

