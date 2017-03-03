#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include <vector>

class Graph {
public:
	Graph();
	
	void draw(sf::RenderWindow& window);

	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);

	void setLabelX(const sf::String& string);
	void setLabelY(const sf::String& string);

	void addPoint(const sf::Vector2f& point);

	void resetPoints();

private:
	sf::RectangleShape			m_background;
	sf::VertexArray				m_line;
	sf::Text					m_labelX;
	sf::Text					m_labelY;
	sf::Text					m_xScaleMin;
	sf::Text					m_xScaleMax;
	sf::Text					m_yScaleMin;
	sf::Text					m_yScaleMax;

	std::vector<sf::Vector2f>	m_points;

	//repositions the labels on the Graph based on size of the Graph and text
	void repositionLabels();

	//repositions the text for the scales on the Graph based on size of the Graph and text
	void repositionScaleText();

	//repositions points on the Graph based on the X,Y "coordinates" and the range of point values
	void repositionPoints();
};

#endif