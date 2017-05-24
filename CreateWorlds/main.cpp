#include <SFML/Graphics.hpp>
#include "CFloor.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	
	CFloor m_floor;
	int state = 0;
	m_floor.SetSizeEllipse(100, 100);
	m_floor.SetNumberOfRooms(20);
	m_floor.SetSizeRoom(10, 10, 100, 100);
	m_floor.SetOffset(200, 300);

	m_floor.CreateRooms();

	bool flagStepDelaunay = true;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (flagStepDelaunay)
				{
					flagStepDelaunay = m_floor.StepDelaunayTriangulations();
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
			m_floor.FilterRooms(20, 20, 90, 90);
			state = 2;
			break;
		case 2:
			m_floor.PrepareDelaunayTriangulations();
			state = 3;
			break;
		case 3:
			//m_floor.StepDelaunayTriangulations();
			break;
		default:
			break;
		}

		
		window.clear();
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

			for (auto tri = m_floor.m_DelaunayTriangles.begin(); tri != m_floor.m_DelaunayTriangles.end(); tri++)
			{
				sf::ConvexShape convex;
				convex.setPointCount(3);
				convex.setFillColor(sf::Color::Transparent);
				convex.setOutlineColor(sf::Color::White);
				convex.setOutlineThickness(1);


				// define the points
				convex.setPoint(0, sf::Vector2f(tri->point0->m_position.x, tri->point0->m_position.y));
				convex.setPoint(1, sf::Vector2f(tri->point1->m_position.x, tri->point1->m_position.y));
				convex.setPoint(2, sf::Vector2f(tri->point2->m_position.x, tri->point2->m_position.y));
				window.draw(convex);
			}
			
		}
		window.display();
	}

	return 0;
}