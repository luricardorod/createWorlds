#include <SFML/Graphics.hpp>
#include "CFloor.h"
#include <iostream>
#include "BMPperlinnoise.cpp"
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

	GenerateBMP(512, 512, 33333);
	CFloor m_floor;
	int state = 0;
	int minXRoom = 12;
	int minYRoom = 12;
	int maxXRoom = 25;
	int maxYRoom = 25;

	m_floor.SetSizeEllipse(100, 100);
	m_floor.SetNumberOfRooms(100);
	m_floor.SetSizeRoom(10, 10, 50, 50);
	m_floor.SetOffset(640, 400);

	m_floor.CreateRooms();

	bool flagStepDelaunay = true;
	bool flagNextStepDelaunay = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && state == 3)
			{
				if (flagStepDelaunay)
				{
					flagStepDelaunay = m_floor.StepDelaunayTriangulations();
				}
				else
				{
					flagNextStepDelaunay = true;
				}
			}
		}

		switch (state)
		{
		case 0:
			if (!m_floor.SeparateRooms())
			{
				state = 1;
			}
			break;
		case 1:
			m_floor.FilterRooms(minXRoom, minYRoom, maxXRoom, maxYRoom);
			state = 2;
			break;
		case 2:
			m_floor.PrepareDelaunayTriangulations();
			state = 3;
			break;
		case 3:
			if (flagNextStepDelaunay)
			{
				state = 4;
			}
			break;
		case 4:
			m_floor.CleanDelauneyTriangulation();
			state = 5;
			break;
		case 5:
			m_floor.DesconectNodes();
			state = 6;
			break;
		case 6:
			m_floor.GenerateMatrixFloor();
			state = 7;
			break;
		default:
			break;
		}

		
		window.clear();
		m_floor.m_conectionsFloor;
		for (auto room = m_floor.m_vRooms.begin(); room != m_floor.m_vRooms.end(); room++)
		{
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(room->m_iWidth,room->m_iHeight));
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setOutlineColor(sf::Color::White);
			rectangle.setOutlineThickness(1);
			rectangle.setPosition(room->m_v2Position.x, room->m_v2Position.y);
			window.draw(rectangle);
		}
		if (state > 2)
		{
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(m_floor.m_ContainerRectangleWidth, m_floor.m_ContainerRectangleHeight));
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineColor(sf::Color::White);
			rectangle.setOutlineThickness(1);
			rectangle.setPosition(m_floor.m_ContainerRectangle.x, m_floor.m_ContainerRectangle.y);
			window.draw(rectangle);
			for (auto centerRoom = m_floor.m_graph.begin(); centerRoom != m_floor.m_graph.end(); centerRoom++)
			{
				sf::CircleShape point(1);
				point.setFillColor(sf::Color::Green);
				point.setPosition(centerRoom->m_position.x, centerRoom->m_position.y);
				window.draw(point);
			}

			if (state == 3)
			{
				for (auto tri = m_floor.m_DelaunayTriangles.begin(); tri != m_floor.m_DelaunayTriangles.end(); tri++)
				{
					sf::ConvexShape convex;
					convex.setPointCount(3);
					convex.setFillColor(sf::Color::Transparent);
					convex.setOutlineColor(sf::Color::White);
					convex.setOutlineThickness(.5);


					// define the points
					convex.setPoint(0, sf::Vector2f(tri->point0->m_position.x, tri->point0->m_position.y));
					convex.setPoint(1, sf::Vector2f(tri->point1->m_position.x, tri->point1->m_position.y));
					convex.setPoint(2, sf::Vector2f(tri->point2->m_position.x, tri->point2->m_position.y));
					window.draw(convex);
				}
			}
			if (state >= 5)
			{
				for (auto node= m_floor.m_graph.begin(); node != m_floor.m_graph.end(); node++)
				{
					for (auto connection = node->m_conections.begin(); connection != node->m_conections.end(); connection++)
					{
						if (connection->m_bstatus)
						{
							sf::Vertex line[] =
							{
								sf::Vertex(sf::Vector2f(connection->m_node->m_position.x, connection->m_node->m_position.y)),
								sf::Vertex(sf::Vector2f(node->m_position.x, node->m_position.y))
							};

							window.draw(line, 2, sf::Lines);
						}
					}
				}
			}
			
		}
		window.display();
	}

	return 0;
}