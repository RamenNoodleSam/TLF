#include <sstream>
#include <iomanip>
#include "Graph.h"
#include "GlobalAssetPool.h"

Graph::Graph() :
	m_background({ 400, 400 })
{
	m_background.setFillColor({ 20, 20, 20 });

	//initialise X axis label
	m_labelX.setFont(GlobalAssetPool::getInstance()->m_font);
	m_labelX.setString("Label X");
	m_labelX.setCharacterSize(16);
	m_labelX.setStyle(m_labelX.Bold);
	m_labelX.setFillColor({ 255, 140, 0 });

	//initialise Y axis label
	m_labelY.setFont(GlobalAssetPool::getInstance()->m_font);
	m_labelY.setString("Label Y");
	m_labelY.setCharacterSize(16);
	m_labelY.setStyle(m_labelY.Bold);
	m_labelY.setFillColor({ 255, 140, 0 });

	m_xScaleMin.setFont(GlobalAssetPool::getInstance()->m_font);
	m_xScaleMin.setCharacterSize(12);
	m_xScaleMin.setStyle(m_xScaleMin.Bold);
	m_xScaleMin.setFillColor({ 255, 140, 0 });

	m_xScaleMax.setFont(GlobalAssetPool::getInstance()->m_font);
	m_xScaleMax.setCharacterSize(12);
	m_xScaleMax.setStyle(m_xScaleMax.Bold);
	m_xScaleMax.setFillColor({ 255, 140, 0 });

	m_yScaleMin.setFont(GlobalAssetPool::getInstance()->m_font);
	m_yScaleMin.setCharacterSize(12);
	m_yScaleMin.setStyle(m_yScaleMin.Bold);
	m_yScaleMin.setFillColor({ 255, 140, 0 });

	m_yScaleMax.setFont(GlobalAssetPool::getInstance()->m_font);
	m_yScaleMax.setCharacterSize(12);
	m_yScaleMax.setStyle(m_yScaleMax.Bold);
	m_yScaleMax.setFillColor({ 255, 140, 0 });

	//position axis labels
	repositionLabels();

	//initialise line between points
	m_line.setPrimitiveType(sf::LinesStrip);
}

void Graph::draw(sf::RenderWindow& window) {
	window.draw(m_background);
	window.draw(m_labelX);
	window.draw(m_labelY);
	window.draw(m_line);
	window.draw(m_xScaleMin);
	window.draw(m_xScaleMax);
	window.draw(m_yScaleMin);
	window.draw(m_yScaleMax);
}

void Graph::setPosition(const sf::Vector2f& position) {
	m_background.setPosition(position);
	repositionLabels();
	repositionScaleText();
}

void Graph::setSize(const sf::Vector2f& size) {
	m_background.setSize(size);
	repositionLabels();
	repositionScaleText();
}

void Graph::setLabelX(const sf::String& string) {
	m_labelX.setString(string);
	repositionLabels();
}

void Graph::setLabelY(const sf::String& string) {
	m_labelY.setString(string);
	repositionLabels();
}

void Graph::addPoint(const sf::Vector2f& point) {
	m_points.push_back(point);
	repositionPoints();
	repositionScaleText();
}

void Graph::resetPoints() {
	m_points.clear();
	m_xScaleMin.setString("");
	m_xScaleMax.setString("");
	m_yScaleMin.setString("");
	m_yScaleMax.setString("");
	repositionPoints();
}

void Graph::repositionLabels() {
	//centre m_labelX text
	sf::FloatRect textRect = m_labelX.getLocalBounds();
	m_labelX.setOrigin(textRect.left + textRect.width / 2.0f,
					   textRect.top + textRect.height / 2.0f);

	//set label for X axis to be in the middle underneath the graph
	m_labelX.setPosition(m_background.getPosition() + 
						 sf::Vector2f(m_background.getSize().x * 0.5f, m_background.getSize().y * 1.1f));
	
	//centre m_labelY text
	textRect = m_labelY.getLocalBounds();
	m_labelY.setOrigin(textRect.left + textRect.width / 2.0f,
					   textRect.top + textRect.height / 2.0f);

	//rotate label for Y axis 90 degrees counter-clockwise to be orientated correctly
	m_labelY.setRotation(-90.f);

	//set label for Y axis to be half way down the left of the graph
	m_labelY.setPosition(m_background.getPosition() +
						 sf::Vector2f(-m_background.getSize().x * 0.1f, m_background.getSize().y * 0.5f));
}

void Graph::repositionScaleText() {
	//centre m_xScaleMin text
	sf::FloatRect textRect = m_xScaleMin.getLocalBounds();
	m_xScaleMin.setOrigin(textRect.left + textRect.width / 2.0f,
						  textRect.top + textRect.height / 2.0f);

	//position underneath the graph on the left
	m_xScaleMin.setPosition(m_background.getPosition() +
							sf::Vector2f(0.f, m_background.getSize().y * 1.03f));

	//centre m_xScaleMax text
	textRect = m_xScaleMax.getLocalBounds();
	m_xScaleMax.setOrigin(textRect.left + textRect.width / 2.0f,
						  textRect.top + textRect.height / 2.0f);

	//position underneath the graph on the right
	m_xScaleMax.setPosition(m_background.getPosition() +
							sf::Vector2f(m_background.getSize().x, m_background.getSize().y * 1.03f));

	//set origin to the right of the text so it doesn't overlap the graph
	textRect = m_yScaleMin.getLocalBounds();
	m_yScaleMin.setOrigin(textRect.left + textRect.width,
						  textRect.top + textRect.height / 2.0f);

	//position at the top on the left side
	m_yScaleMin.setPosition(m_background.getPosition() +
							sf::Vector2f(-m_background.getSize().x * 0.03f, m_background.getSize().y));

	//set origin to the right of the text so it doesn't overlap the graph
	textRect = m_yScaleMax.getLocalBounds();
	m_yScaleMax.setOrigin(textRect.left + textRect.width,
						  textRect.top + textRect.height / 2.0f);

	//position at the bottom on the left side
	m_yScaleMax.setPosition(m_background.getPosition() +
							sf::Vector2f(-m_background.getSize().x * 0.03f, 0.f));
}

void Graph::repositionPoints() {
	size_t numberOfPoints(m_points.size());

	//clear any points currently in the line (but without affecting memory)
	m_line.clear();

	if (numberOfPoints >= 2) {
		//find the highest and lowest points in the x axis, as well as the range
		float highestXValue = std::max_element(m_points.begin(), m_points.end(), [](const sf::Vector2f& p1, const sf::Vector2f& p2) { return p1.x < p2.x;})->x;
		float lowestXValue = std::min_element(m_points.begin(), m_points.end(), [](const sf::Vector2f& p1, const sf::Vector2f& p2) {	return p1.x < p2.x; })->x;
		float xAxisRange = highestXValue - lowestXValue;

		//find the highest and lowest points in the y axis, as well as the range
		float highestYValue = std::max_element(m_points.begin(), m_points.end(), [](const sf::Vector2f& p1, const sf::Vector2f& p2) { return p1.y < p2.y; })->y;
		float lowestYValue = std::min_element(m_points.begin(), m_points.end(), [](const sf::Vector2f& p1, const sf::Vector2f& p2) { return p1.y < p2.y; })->y;
		float yAxisRange = highestYValue - lowestYValue;

		for (int i = 0; i < numberOfPoints; ++i) {
			m_line.append(sf::Vertex(m_background.getPosition() + 
									 sf::Vector2f((m_points[i].x - lowestXValue) / xAxisRange * m_background.getSize().x,
												  m_background.getSize().y - ((m_points[i].y - lowestYValue) / yAxisRange * m_background.getSize().y)),
									 sf::Color(255, 140, 0)));
		}

		std::ostringstream oss;
		oss << std::setprecision(0) << std::fixed << lowestXValue;
		m_xScaleMin.setString(oss.str());

		oss.str("");
		oss.clear();
		oss << std::setprecision(0) << std::fixed << highestXValue;
		m_xScaleMax.setString(oss.str());

		oss.str("");
		oss.clear();
		oss << std::setprecision(2) << std::fixed << lowestYValue;
		m_yScaleMin.setString(oss.str());

		oss.str("");
		oss.clear();
		oss << std::setprecision(2) << std::fixed << highestYValue;
		m_yScaleMax.setString(oss.str());

		repositionScaleText();
	}
}