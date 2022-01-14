#include <SFML/Graphics.hpp>
#include <iostream>

class SliderDesign
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
	SliderDesign(int x, int y, bool vert);
	sf::Text returnText(int x, int y, std::string z, int fontSize);
	void logic(sf::RenderWindow &window);
	void draw(sf::RenderWindow & window);
    void updateSliderPos(int w, int h);
	float getSliderValue();
	void create(int min, int max);
	void setSliderValue(float newValue);
};

