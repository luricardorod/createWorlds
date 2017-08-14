#include "CFloor.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "CDijkstra.h"

#define VEL 1;
#define MARGINERROR 0
#define SEPARETEMARGIN 0


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

void CFloor::DesconectNodes()
{
	m_graph;

	CDijkstra dijkstra;
	CWalker *walker = &dijkstra;
	std::vector<node*> nodes;
	for (auto conection = m_conectionsFloor.begin(); conection != m_conectionsFloor.end(); conection++)
	{
		node* node1 = conection->m_node;
		conection++;
		node* node2 = conection->m_node;

		std::vector<Conection>::iterator itConection1;
		std::vector<Conection>::iterator itConection2;

		for (auto conection1 = node1->m_conections.begin(); conection1 != node1->m_conections.end(); conection1++)
		{
			if (conection1->m_node->m_id == node2->m_id)
			{
				itConection1 = conection1;
				break;
			}
		}
		for (auto conection2 = node2->m_conections.begin(); conection2 != node2->m_conections.end(); conection2++)
		{
			if (conection2->m_node->m_id == node1->m_id)
			{
				itConection2 = conection2;
				break;
			}
		}

		itConection1->m_bstatus = false;
		itConection2->m_bstatus = false;

		

		walker->SetStart(node1);
		walker->SetEnd(node2);
		walker->RunPathFinding();
		nodes = walker->PathFinding();
		if (nodes.size() == 0)
		{
			itConection1->m_bstatus = true;
			itConection2->m_bstatus = true;
		}
	}
	
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
	float a_0 = p0->x;
	float a_1 = p0->y;
	float b_0 = p1->x;
	float b_1 = p1->y;
	float c_0 = p2->x;
	float c_1 = p2->y;
	float p_0, p_1, D;

	D = (a_0 - c_0) * (b_1 - c_1) - (b_0 - c_0) * (a_1 - c_1);

	p_0 = (((a_0 - c_0) * (a_0 + c_0) + (a_1 - c_1) * (a_1 + c_1)) / 2 * (b_1 - c_1)
		- ((b_0 - c_0) * (b_0 + c_0) + (b_1 - c_1) * (b_1 + c_1)) / 2 * (a_1 - c_1))
		/ D;

	p_1 = (((b_0 - c_0) * (b_0 + c_0) + (b_1 - c_1) * (b_1 + c_1)) / 2 * (a_0 - c_0)
		- ((a_0 - c_0) * (a_0 + c_0) + (a_1 - c_1) * (a_1 + c_1)) / 2 * (b_0 - c_0))
		/ D;
	radius = sqrt(powf(c_0 - p_0, 2.0) + powf(c_1 - p_1, 2.0));
	float lu = sqrt(powf(a_0 - p_0, 2.0) + powf(a_1 - p_1, 2.0));
	float lus = sqrt(powf(b_0 - p_0, 2.0) + powf(b_1 - p_1, 2.0));


	return CVector2D(p_0, p_1);
}

void CFloor::ChangeTile(int positionX, int positionY, int value)
{
	int position = positionX + positionY * m_ContainerRectangleWidth;
	int limX = m_ContainerRectangleWidth - 1;
	int limY = m_ContainerRectangleHeight - 1;

	m_tilesRoom[position].leftDown = value;
	m_tilesRoom[position].leftUp = value;
	m_tilesRoom[position].rigthDown = value;
	m_tilesRoom[position].rigthUp = value;
	m_tilesRoom[position].value = value;

	if (positionX > 0)
	{
		if (positionY > 0)
		{
			int position = positionX - 1 + (positionY-1)* limX;
			m_tilesRoom[position].rigthDown = value;
		}
		int position = positionX - 1 + positionY * limX;

		m_tilesRoom[position].rigthDown = value;
		m_tilesRoom[position].rigthUp = value;
		if (positionY < limY)
		{
			int position = positionX - 1 + (positionY + 1)* limX;
			m_tilesRoom[position].rigthUp = value;
		}
	}
	if (positionY > 0)
	{
		int position = positionX + (positionY - 1)* limX;

		m_tilesRoom[position].rigthDown = value;
		m_tilesRoom[position].leftDown = value;
	}
	if (positionY < limY)
	{
		int position = positionX + (positionY + 1)* limX;

		m_tilesRoom[position].rigthUp = value;
		m_tilesRoom[position].leftUp = value;
	}
	if (positionX < limX)
	{
		if (positionY > 0)
		{
			int position = positionX + 1 + (positionY - 1)* limX;
			m_tilesRoom[position].leftDown = value;
		}
		int position = positionX + 1 + positionY * limX;
		m_tilesRoom[position].leftDown = value;
		m_tilesRoom[position].leftUp = value;
		if (positionY < limY)
		{
			int position = positionX + 1 + (positionY + 1)* limX;
			m_tilesRoom[position].leftUp = value;
		}
	}

}

void CFloor::ConnectIfNotRepeated(node *nodeTemp, node *conectionNode) {
	m_graph;
	for (std::vector<Conection>::iterator conection = nodeTemp->m_conections.begin(); conection != nodeTemp->m_conections.end(); ++conection)
	{
		if (conection->m_node->m_id == conectionNode->m_id)
		{
			return;
		}
	}
	float distance = (nodeTemp->m_position - conectionNode->m_position).Magnitude();

	nodeTemp->m_conections.push_back(Conection(distance, &(*conectionNode), true));
	conectionNode->m_conections.push_back(Conection(distance, &(*nodeTemp), true));
	std::list<Conection>::iterator oldConnection;
	for (oldConnection = m_conectionsFloor.begin(); oldConnection != m_conectionsFloor.end(); oldConnection++) {
		if (distance > (oldConnection)->m_fvalue)
		{
			break;
		}
		
		oldConnection++;

	}
	if (oldConnection == m_conectionsFloor.end())
	{
		m_conectionsFloor.push_back(Conection(distance, &(*conectionNode), true));
		m_conectionsFloor.push_back(Conection(distance, &(*nodeTemp), true));
	}
	else
	{
		m_conectionsFloor.insert(oldConnection, Conection(distance, &(*conectionNode), true));
		m_conectionsFloor.insert(oldConnection, Conection(distance, &(*nodeTemp), true));
	}
	

}

void CFloor::CreateFirstTriangule()
{
	float xMin = m_vRooms.begin()->m_v2Position.x;
	float xMax = m_vRooms.begin()->m_v2Position.x;
	float yMin = m_vRooms.begin()->m_v2Position.y;
	float yMax = m_vRooms.begin()->m_v2Position.y;

	for (auto point = m_vRooms.begin(); point < m_vRooms.end(); point++)
	{
		if (point->m_v2Position.x < xMin)
		{
			xMin = point->m_v2Position.x;
		}
		if (point->m_v2Position.x + point->m_iWidth > xMax)
		{
			xMax = point->m_v2Position.x + point->m_iWidth;
		}
		if (point->m_v2Position.y < yMin)
		{
			yMin = point->m_v2Position.y;
		}
		if (point->m_v2Position.y + point->m_iHeight > yMax)
		{
			yMax = point->m_v2Position.y + point->m_iHeight;
		}
	}
	
	m_ContainerRectangle.x = xMin;
	m_ContainerRectangle.y = yMin;
	m_ContainerRectangleHeight = yMax - yMin;
	m_ContainerRectangleWidth = xMax - xMin;
	m_DelaunayTriangles.clear();

	node temp;
	float halfWidth = m_ContainerRectangleWidth / 2;
	Triangle firstTriangle;

	temp.m_id = 10001;
	temp.m_position = CVector2D(m_ContainerRectangle.x + halfWidth, m_ContainerRectangle.y - m_ContainerRectangleHeight);
	m_graph.push_back(temp);

	temp.m_id = 10002;
	temp.m_position = CVector2D(m_ContainerRectangle.x - halfWidth, m_ContainerRectangle.y + m_ContainerRectangleHeight);
	m_graph.push_back(temp);

	temp.m_id = 10003;
	temp.m_position = CVector2D(m_ContainerRectangle.x + m_ContainerRectangleWidth + halfWidth, m_ContainerRectangle.y + m_ContainerRectangleHeight);
	m_graph.push_back(temp);

	firstTriangle.point0= &m_graph[m_graph.size() - 1];
	firstTriangle.point1 = &m_graph[m_graph.size() - 2];
	firstTriangle.point2 = &m_graph[m_graph.size() - 3];

	m_DelaunayTriangles.push_back(firstTriangle);
}

void CFloor::GenerateMatrixFloor()
{
	
	m_tilesRoom.resize(m_ContainerRectangleHeight * m_ContainerRectangleWidth);
	for (auto tile = m_tilesRoom.begin(); tile != m_tilesRoom.end(); tile++)
	{
		tile->rigthUp = 0;
		tile->rigthDown = 0;
		tile->leftUp = 0;
		tile->leftDown = 0;
	}

	for (auto room = m_vRooms.begin(); room != m_vRooms.end(); room++)
	{
		int offsetX = room->m_v2Position.x - m_ContainerRectangle.x;
		int offsetY = room->m_v2Position.y - m_ContainerRectangle.y;
		for (int j = 0; j < room->m_iHeight; j++)
		{
			for (int i = 0; i < room->m_iWidth; i++)
			{
				ChangeTile(offsetX + i, offsetY + j, 1);
			}
		}
	}
	int i = 0;
	i++;
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
	m_selectedNodeDelaunay = m_graph.begin();
}

bool CFloor::StepDelaunayTriangulations()
{
	int option = 100;
	std::list<Triangle>::iterator triangle;
	for (triangle = m_DelaunayTriangles.begin(); triangle != m_DelaunayTriangles.end(); triangle++)
	{
		
		CVector2D p = m_selectedNodeDelaunay->m_position;
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

	std::list<Triangle> tempTriangles;

	switch (option)
	{
	case 0:
		Triangle tempTriangle1;
		Triangle tempTriangle2;
		Triangle tempTriangle3;


		tempTriangle1.point0 = triangle->point0;
		tempTriangle1.point1 = triangle->point1;
		tempTriangle1.point2 = &*m_selectedNodeDelaunay;

		tempTriangle2.point0 = triangle->point0;
		tempTriangle2.point1 = triangle->point2;
		tempTriangle2.point2 = &*m_selectedNodeDelaunay;

		tempTriangle3.point0 = triangle->point1;
		tempTriangle3.point1 = triangle->point2;
		tempTriangle3.point2 = &*m_selectedNodeDelaunay;

		m_DelaunayTriangles.erase(triangle);

		tempTriangles.push_back(tempTriangle1);
		tempTriangles.push_back(tempTriangle2);
		tempTriangles.push_back(tempTriangle3);

		break;
	default:
		break;
	}
	while (tempTriangles.size() > 0)
	{
		bool flag = true;
		Triangle selectTempTriangle = tempTriangles.back();
		tempTriangles.pop_back();
		float radius;
		CVector2D originCircle = Circumcircle(radius, &selectTempTriangle.point0->m_position, &selectTempTriangle.point1->m_position, &selectTempTriangle.point2->m_position);


		for (auto selectedNode = m_graph.begin(); selectedNode != m_selectedNodeDelaunay; selectedNode++)
		{
			float distance = (originCircle - selectedNode->m_position).Magnitude();
			if (distance + MARGINERROR < radius)
			{
				for (triangle = m_DelaunayTriangles.begin(); triangle != m_DelaunayTriangles.end(); triangle++) {
					if (triangle->point0->m_id == selectTempTriangle.point0->m_id || triangle->point0->m_id == selectTempTriangle.point1->m_id || triangle->point0->m_id == selectedNode->m_id)
					{
						if (triangle->point1->m_id == selectTempTriangle.point0->m_id || triangle->point1->m_id == selectTempTriangle.point1->m_id || triangle->point1->m_id == selectedNode->m_id)
						{
							if (triangle->point2->m_id == selectTempTriangle.point0->m_id || triangle->point2->m_id == selectTempTriangle.point1->m_id || triangle->point2->m_id == selectedNode->m_id)
							{
								break;
							}
						}
					}
				}
				if (triangle != m_DelaunayTriangles.end())
				{
					selectTempTriangle.point0 = &*selectedNode;
					if (triangle->point0->m_id == selectTempTriangle.point1->m_id) {
						triangle->point0 = &*m_selectedNodeDelaunay;
					}
					else if (triangle->point1->m_id == selectTempTriangle.point1->m_id) {
						triangle->point1 = &*m_selectedNodeDelaunay;
					}
					else
					{
						triangle->point2 = &*m_selectedNodeDelaunay;
					}
					tempTriangles.push_back(*triangle);
					m_DelaunayTriangles.erase(triangle);
					flag = false;
					break;
				}
			}
		}
		if (flag)
		{
			m_DelaunayTriangles.push_back(selectTempTriangle);
		}
		else
		{
			tempTriangles.push_back(selectTempTriangle);
		}
	}
	m_selectedNodeDelaunay++;
	if (m_graph.end() - 3 != m_selectedNodeDelaunay)
	{
		return true;
	}
	return false;
}

bool OverlappingRooms(CRoom *room1, CRoom *room2) {

	float Ax = room1->m_v2Position.x - SEPARETEMARGIN;
	float AX = room1->m_v2Position.x + room1->m_iWidth + SEPARETEMARGIN;

	float Ay = room1->m_v2Position.y - SEPARETEMARGIN;
	float AY = room1->m_v2Position.y + room1->m_iHeight + SEPARETEMARGIN;

	float Bx = room2->m_v2Position.x - SEPARETEMARGIN;
	float BX = room2->m_v2Position.x + room2->m_iWidth + SEPARETEMARGIN;
	float By = room2->m_v2Position.y - SEPARETEMARGIN;
	float BY = room2->m_v2Position.y + room2->m_iHeight + SEPARETEMARGIN;

	return !(AX < Bx || BX < Ax || AY < By || BY < Ay);
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
			//room->m_v2Position.x = floor(room->m_v2Position.x);
			//room->m_v2Position.y = floor(room->m_v2Position.y);

		}
	}

	return flagSeparate;
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

void CFloor::CleanDelauneyTriangulation()
{

	for (auto triangle = m_DelaunayTriangles.begin(); triangle != m_DelaunayTriangles.end(); triangle++)
	{
		if (triangle->point0->m_id != 10001 && triangle->point0->m_id != 10002 && triangle->point0->m_id != 10003)
		{
			if (triangle->point1->m_id != 10001 && triangle->point1->m_id != 10002 && triangle->point1->m_id != 10003)
			{
				ConnectIfNotRepeated(triangle->point0, triangle->point1);
			}
			if (triangle->point2->m_id != 10001 && triangle->point2->m_id != 10002 && triangle->point2->m_id != 10003)
			{
				ConnectIfNotRepeated(triangle->point0, triangle->point2);
			}
		}
		if (triangle->point1->m_id != 10001 && triangle->point1->m_id != 10002 && triangle->point1->m_id != 10003)
		{
			if (triangle->point2->m_id != 10001 && triangle->point2->m_id != 10002 && triangle->point2->m_id != 10003)
			{
				ConnectIfNotRepeated(triangle->point1, triangle->point2);
			}
		}

	}

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
