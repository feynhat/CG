#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Graphics.h"

const float RADIUS = 3.f;

using namespace CG;
using std::vector;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Line Segment Intersections");
	vector<LineSegment> ls;
	vector<Point> endpoints;
	bool lineState = false;
	Point begin, end;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Q) {
					window.close();
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					float x = event.mouseButton.x;
					float y = event.mouseButton.y;
					if (lineState) {
						lineState = false;
						ls.push_back(LineSegment(begin, end));
						end = Point(x, y);
						endpoints.push_back(end);
					} else {
						lineState = true;
						begin = Point(x, y);
						end = Point(x, y);
						endpoints.push_back(begin);
					}
				}
			}

			if (event.type == sf::Event::MouseMoved) {
				float x = event.mouseMove.x;
				float y = event.mouseMove.y;
				end = Point(x, y);
			}
		}

		window.clear(sf::Color::White);

		sf::CircleShape shape(RADIUS);
		shape.setFillColor(sf::Color::Black);
		if (lineState) {
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(begin.x, begin.y)),
				sf::Vertex(sf::Vector2f(end.x, end.y)),
			};
			line[0].color = sf::Color::Black;
			line[1].color = sf::Color::Black;
			window.draw(line, 2, sf::Lines);
		}
		for (auto p: endpoints) {
			shape.setPosition(p.x-RADIUS, p.y-RADIUS);
			window.draw(shape);
		}
		for (auto l: ls) {
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(l.begin.x, l.begin.y)),
				sf::Vertex(sf::Vector2f(l.end.x, l.end.y)),
			};
			line[0].color = sf::Color::Black;
			line[1].color = sf::Color::Black;
			window.draw(line, 2, sf::Lines);
		}

		for (int i = 0; i < ls.size(); ++i) {
			for (int j = i+1; j < ls.size(); ++j) {
				//std::cout<<"here 0\n";
				if (ls[i].intersects(ls[j])) {
					//std::cout << "here\n";
					Point p = ls[i].intersection(ls[j]);
					shape.setPosition(p.x-RADIUS, p.y-RADIUS);
					shape.setFillColor(sf::Color::Red);
					window.draw(shape);
				}
			}
		}
		window.display();
	}

	return 0;
}
