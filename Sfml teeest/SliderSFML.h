#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class SliderSFML
{
	sf::RectangleShape slider;
	sf::RectangleShape axis;
	sf::Font font;
	sf::Text text;
	int minValue;
	int maxValue;
	int xCord;
	int yCord;
	int axisWidth;
	int axisHeight;
	int sliderWidth;
	int sliderHeight;
	float sliderValue;
	bool vertical;
public:
	SliderSFML(int x, int y, bool vert);
	sf::Text returnText(int x, int y, std::string z, int fontSize);
	void create(int min, int max);
	void logic(sf::RenderWindow &window);
	float getSliderValue();
	void setSliderValue(float newValue);
	void draw(sf::RenderWindow & window);
    void updateSliderPos(int w, int h);
};

