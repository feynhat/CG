#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Graphics.h"

const float RADIUS = 3.f;

using namespace CG;
using std::vector;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Convex Hull");
	vector<Point> points;

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
					std::cout << "the left button was pressed\n";
					float x = event.mouseButton.x;
					float y = event.mouseButton.y;
					std::cout << "mouse x: " << x
						<< " mouse y: " << y
						<< "\n";
					Point p(x, y);
					if (find(points.begin(), points.end(), p) == points.end())
						points.push_back(p);
				}
			}
		}

		window.clear(sf::Color::White);

		Polygon convex_hull = ConvexHull(points);
		sf::ConvexShape conv;
		conv.setFillColor(sf::Color::Green);
		conv.setPointCount(convex_hull.points.size());
		for (int i = 0; i < convex_hull.points.size(); ++i) {
			Point p = convex_hull.points[i];
			conv.setPoint(i, sf::Vector2f(p.x, p.y));
		}

		window.draw(conv);
		sf::CircleShape shape(RADIUS);
		shape.setFillColor(sf::Color::Black);
		for (auto p: points) {
			shape.setPosition(p.x-RADIUS, p.y-RADIUS);
			window.draw(shape);
		}
		window.display();

	}

	return 0;
}
