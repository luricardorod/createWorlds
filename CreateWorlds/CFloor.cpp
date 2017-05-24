#include "CFloor.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define VEL .1;
#define MARGINERROR 0.1
void CFloor::SetSizeRoom(int minWidth, int minHeight, int maxWidth, int maxHeight)
{
	m_iMinWidthSizeRoom = minWidth;
	m_iMinHeightSizeRoom = minHeight;
	m_iMaxWidthSizeRoom = maxWidth;
	m_iMaxHeightSizeRoom = maxHeight;
}

void CFloor::SetSizeEllipse(int width, int height)
{
	m_iEllipseWidth = width;
	m_iEllipseHeight = height;
}

void CFloor::SetNumberOfRooms(int numberRooms)
{
	m_iNumberRooms = numberRooms;
}

void CFloor::CreateRooms()
{
	int intervalX = m_iMaxWidthSizeRoom - m_iMinWidthSizeRoom;
	int intervalY = m_iMaxHeightSizeRoom - m_iMinHeightSizeRoom;
	for (int i = 0; i < m_iNumberRooms; i++)
	{
		CRoom newRoom;
		newRoom.m_v2Position = CreatePointInsideEllipse();
		newRoom.m_iWidth = rand() % intervalX + 1 + m_iMinWidthSizeRoom;
		newRoom.m_iHeight = rand() % intervalY + 1 + m_iMinHeightSizeRoom;
		m_vRooms.push_back(newRoom);
	}

}

CVector2D Circumcircle(float &radius, CVector2D *p0, CVector2D *p1, CVector2D *p2) {
	radius = 0.0f;
	

	return CVector2D(0,0);
}

void connectionIfNotRepeated(node *nodeTemp, node *conectionNode) {
	for (std::vector<Conection>::iterator conection = nodeTemp->m_conections.begin(); conection != nodeTemp->m_conections.end(); ++conection)
	{
		if (conection->m_node->m_id == conectionNode->m_id)
		{
			return;
		}
	}
	nodeTemp->m_conections.push_back(Conection(1, &(*conectionNode)));
}

void CFloor::CreateFirstTriangule()
{
	float xMin = m_graph.begin()->m_position.x;
	float xMax = m_graph.begin()->m_position.x;
	float yMin = m_graph.begin()->m_position.y;
	float yMax = m_graph.begin()->m_position.y;

	for (auto point = m_graph.begin(); point < m_graph.end(); point++)
	{
		if (point->m_position.x < xMin)
		{
			xMin = point->m_position.x;
		}
		if (point->m_position.x > xMax)
		{
			xMax = point->m_position.x;
		}
		if (point->m_position.y < yMin)
		{
			yMin = point->m_position.y;
		}
		if (point->m_position.y > yMax)
		{
			yMax = point->m_position.y;
		}
	}
	m_ContainerRectangle.x = xMin - 10;
	m_ContainerRectangle.y = yMin - 10;
	m_ContainerRectangleHeight = yMax - yMin + 20;
	m_ContainerRectangleWidth = xMax - xMin + 20;
	m_DelaunayTriangles.clear();

	node temp;
	temp.m_id = 10000;
	float halfWidth = m_ContainerRectangleWidth / 2;
	Triangle firstTriangle;

	temp.m_position = CVector2D(m_ContainerRectangle.x + halfWidth, m_ContainerRectangle.y - m_ContainerRectangleHeight);
	m_graph.push_back(temp);
	firstTriangle.point0= &m_graph.back();

	temp.m_position = CVector2D(m_ContainerRectangle.x - halfWidth, m_ContainerRectangle.y + m_ContainerRectangleHeight);
	m_graph.push_back(temp);
	firstTriangle.point1 = &m_graph.back();

	temp.m_position = CVector2D(m_ContainerRectangle.x + m_ContainerRectangleWidth + halfWidth, m_ContainerRectangle.y + m_ContainerRectangleHeight);
	m_graph.push_back(temp);
	firstTriangle.point2 = &m_graph.back();

	m_DelaunayTriangles.push_back(firstTriangle);
}

void CFloor::PrepareDelaunayTriangulations()
{
	int counterId = 0;

	for (std::vector<CRoom>::iterator room = m_vRooms.begin(); room != m_vRooms.end(); ++room)
	{
		node temp;
		temp.m_id = counterId;
		counterId++;
		temp.m_position = CVector2D(room->m_v2Position.x + room->m_iWidth / 2.0, room->m_v2Position.y + room->m_iHeight / 2.0);
		m_graph.push_back(temp);
	}

	CreateFirstTriangule();
	selectedNodeDelaunay = m_graph.begin();
}

bool CFloor::StepDelaunayTriangulations()
{
	int option = 100;
	std::list<Triangle>::iterator triangle;
	for (triangle = m_DelaunayTriangles.begin(); triangle != m_DelaunayTriangles.end(); triangle++)
	{
		
		CVector2D p = selectedNodeDelaunay->m_position;
		CVector2D A1 = triangle->point0->m_position;
		CVector2D A2 = triangle->point1->m_position;
		CVector2D A3 = triangle->point2->m_position;

		float orientation0 = (A1.x - A3.x) * (A2.y - A3.y) - (A1.y - A3.y) * (A2.x - A3.x);
		float orientation1 = (A1.x - p.x) * (A2.y - p.y) - (A1.y - p.y) * (A2.x - p.x);
		float orientation2 = (A2.x - p.x) * (A3.y - p.y) - (A2.y - p.y) * (A3.x - p.x);
		float orientation3 = (A3.x - p.x) * (A1.y - p.y) - (A3.y - p.y) * (A1.x - p.x);

		if ((orientation0 > 0 && orientation1 > 0 && orientation2 > 0 && orientation3 > 0) || (orientation0 < 0 && orientation1 < 0 && orientation2 < 0 && orientation3 < 0))
		{
			option = 0;
			break;
		}
	}
	switch (option)
	{
	case 0:
		Triangle tempTriangle1;
		Triangle tempTriangle2;
		Triangle tempTriangle3;


		tempTriangle1.point0 = triangle->point0;
		tempTriangle1.point1 = triangle->point1;
		tempTriangle1.point2 = &*selectedNodeDelaunay;

		tempTriangle2.point0 = triangle->point0;
		tempTriangle2.point1 = triangle->point2;
		tempTriangle2.point2 = &*selectedNodeDelaunay;

		tempTriangle3.point0 = triangle->point1;
		tempTriangle3.point1 = triangle->point2;
		tempTriangle3.point2 = &*selectedNodeDelaunay;

		m_DelaunayTriangles.erase(triangle);

		m_DelaunayTriangles.push_back(tempTriangle1);
		m_DelaunayTriangles.push_back(tempTriangle2);
		m_DelaunayTriangles.push_back(tempTriangle3);

		break;
	default:
		break;
	}

	for (triangle = m_DelaunayTriangles.begin(); triangle != m_DelaunayTriangles.end(); triangle++)
	{
		// delaunisar
		
	}
	selectedNodeDelaunay++;
	if (m_graph.end() - 3 != selectedNodeDelaunay)
	{
		return true;
	}
	return false;
}

bool OverlappingRooms(CRoom *room1, CRoom *room2) {

	float Ax = room1->m_v2Position.x;
	float AX = room1->m_v2Position.x + room1->m_iWidth;

	float Ay = room1->m_v2Position.y;
	float AY = room1->m_v2Position.y + room1->m_iHeight;

	float Bx = room2->m_v2Position.x;
	float BX = room2->m_v2Position.x + room2->m_iWidth;
	float By = room2->m_v2Position.y;
	float BY = room2->m_v2Position.y + room2->m_iHeight;

	return !(Ax < Bx || BX < Ax || AY < By || BY < Ay);
}

bool CFloor::SeparateRooms()
{
	bool flagSeparate = false;

	for (std::vector<CRoom>::iterator room = m_vRooms.begin(); room != m_vRooms.end(); ++room) {
		CVector2D directionForce = CVector2D(0, 0);
		bool flagChange = false;
		for (std::vector<CRoom>::iterator roomOveralping = m_vRooms.begin(); roomOveralping != m_vRooms.end(); ++roomOveralping) {
			if (roomOveralping != room)
			{
				if (OverlappingRooms(&(*room), &(*roomOveralping)))
				{
					directionForce = directionForce + room->m_v2Position - roomOveralping->m_v2Position;
					flagSeparate = true;
					flagChange = true;
				}
			}
		}
		if (flagChange)
		{
			room->m_v2Position = room->m_v2Position +directionForce.Normalize() * VEL;
		}
	}

	return flagSeparate;
}

bool CFloor::IsInsideNodeInCircle(CVector2D origin, float radius)
{
	for (std::vector<node>::iterator nodo = m_graph.begin(); nodo != m_graph.end(); ++nodo)
	{
		float distance = (origin - nodo->m_position).Magnitude();
		if (distance + MARGINERROR < radius)
		{
			return true;
		}
	}
	return false;
}

void CFloor::FilterRooms(int minWidth, int minHeight, int maxWidth, int maxHeight)
{
	std::vector<CRoom> temp;
	for (std::vector<CRoom>::iterator room = m_vRooms.begin(); room != m_vRooms.end(); ++room) {
		if (minWidth <= room->m_iWidth && room->m_iWidth <= maxWidth && minHeight <= room->m_iHeight && room->m_iHeight <= maxHeight)
		{
			temp.push_back(*room);
		}
	}
	m_vRooms.clear();
	m_vRooms = temp;
}

CVector2D CFloor::CreatePointInsideEllipse()
{
	CVector2D tempPoint = CVector2D(0, 0);;
	float tempRandomAngle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.5708));
	float tempProportion = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / 2) - 1;
	float tempEllipseX = m_iEllipseWidth / 2.0f;
	float tempEllipseY = m_iEllipseHeight / 2.0f;

	tempPoint.x = floor(cosf(tempRandomAngle) * tempEllipseX) + m_iOffsetX - tempEllipseX;
	tempPoint.y = floor(sinf(tempRandomAngle) * tempProportion * tempEllipseY) + m_iOffsetY - tempEllipseY;

	return tempPoint;
}

void CFloor::Init()
{
	m_iEllipseWidth = 1;
	m_iEllipseHeight = 1;
	m_iMinWidthSizeRoom = 1;
	m_iMaxWidthSizeRoom = 1;
	m_iMinHeightSizeRoom = 1;
	m_iMaxHeightSizeRoom = 1;
	m_iNumberRooms = 1;
	m_iOffsetX = 0;
	m_iOffsetY = 0;
	srand(time(NULL));
}

void CFloor::SetOffset(int x, int y)
{
	m_iOffsetX = x;
	m_iOffsetY = y;
}

CFloor::CFloor()
{
	Init();
}


CFloor::~CFloor()
{
}
