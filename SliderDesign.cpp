#include <sstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class SliderDesign
{
    sf::RectangleShape slider;
    sf::RectangleShape axis;
    sf::Font font;
    sf::Text text;
    int ValoareMinima, ValoareMaxima, xCord, yCord;
    int axisWidth, axisHeight, sliderWidth, sliderHeight;
    float sliderValue; bool vertical;
public:
    bool isActivated=false;
    SliderDesign(int x, int y, bool vert)
    {
        xCord = x;
        yCord = y;
        axisHeight = 3;
        axisWidth = 200;
        sliderWidth = 25;
        sliderHeight = 10;
        vertical = vert;
        if(vertical == 1)
        {
            std::swap(axisHeight, axisWidth);
            std::swap(sliderHeight, sliderWidth);
        }
        if (!font.loadFromFile("OpenSans-Regular.ttf")) std::cout << "Error loading font\n";
        text.setFont(font);
        text.setFillColor(sf::Color::White);

        axis.setPosition(x, y);
        axis.setOrigin(0, axisHeight / 2);
        axis.setSize(sf::Vector2f(axisWidth, axisHeight));
        axis.setFillColor(sf::Color(63,63,63));
        if(vertical == 0)
            slider.setPosition(x, y);
        else slider.setPosition(x + vertical, y + axisHeight/2);
        slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
        slider.setSize(sf::Vector2f(sliderWidth, sliderHeight));
        slider.setFillColor(sf::Color(204,0,0));
    }
    void create(int min, int max)
    {
        sliderValue = min;
        ValoareMinima = min;
        ValoareMaxima = max;
    }
    sf::Text returnText(int x, int y, std::string z, int fontSize)
    {
        text.setCharacterSize(fontSize);
        text.setPosition(x, y);
        text.setString(z);
        return text;
    }
    int isMouseOn(sf::RenderWindow &window)
    {
        return slider.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
                && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
    void logic(sf::RenderWindow &window)
    {
        if (slider.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
                && sf::Mouse::isButtonPressed(sf::Mouse::Left)||isActivated==true)
        {
            isActivated=true;
            if (sf::Mouse::getPosition(window).x >= xCord && sf::Mouse::getPosition(window).x <= xCord + axisWidth && vertical == 0)
            {
                slider.setPosition(sf::Mouse::getPosition(window).x, yCord);
                sliderValue = (ValoareMinima + ((slider.getPosition().x - xCord) / axisWidth * (ValoareMaxima - ValoareMinima)));
            }
            else if(sf::Mouse::getPosition(window).x >= xCord&& vertical == 0)
            {
                slider.setPosition(xCord+axisWidth, yCord);
                sliderValue=ValoareMaxima;
            }
            else if(sf::Mouse::getPosition(window).x <= xCord + axisWidth && vertical == 0)
            {
                slider.setPosition(xCord, yCord);
                sliderValue=ValoareMinima;
            }

            if (sf::Mouse::getPosition(window).y >= yCord - axisHeight/2 && sf::Mouse::getPosition(window).y <= yCord + axisHeight/2 && vertical == 1)
            {
                slider.setPosition(xCord + vertical, sf::Mouse::getPosition(window).y);
                sliderValue = ValoareMinima - ((slider.getPosition().y - yCord - axisHeight/2) / axisHeight * (ValoareMaxima - ValoareMinima));
            }
            else if(sf::Mouse::getPosition(window).y >= yCord - axisHeight/2&&vertical==1)
            {
                slider.setPosition(xCord + vertical, yCord+axisHeight/2);
                sliderValue=ValoareMinima;
            }
            else if(sf::Mouse::getPosition(window).y <= yCord + axisHeight/2 && vertical == 1)
            {
                slider.setPosition(xCord + vertical, yCord-axisHeight/2);
                sliderValue=ValoareMaxima;
            }
        }
    }
    float getSliderValue()
    {

        return sliderValue;
    }
    void setSliderValue(float newValue)
    {

        if (newValue >= ValoareMinima && newValue <= ValoareMaxima)
        {
            sliderValue = newValue;

            if(vertical == 0)
            {
                float diff = ValoareMaxima - ValoareMinima;
                float diff2 = newValue - ValoareMinima;
                float zzz = axisWidth / diff;
                float posX = zzz*diff2;
                posX += xCord;
                slider.setPosition(posX, yCord);
            }
            else
            {
                float diff = ValoareMinima - ValoareMaxima;
                float diff2 = newValue - ValoareMinima;
                float zzz = axisHeight / diff;
                float posY = zzz*diff2;
                posY += yCord + axisHeight/2;
                slider.setPosition(xCord + vertical, posY);
            }
        }
    }
    void draw(sf::RenderWindow & window)
    {
        logic(window);
        /// PRINTING THE SLIDER VALUES

        std::ostringstream str1;
        std::ostringstream str2;

        if(vertical == 0)
        {
            str1 << ValoareMinima;
            str2 << ValoareMaxima;

        }
        else
        {
            str1 << ValoareMinima / 4.0f;
            str2 << ValoareMaxima / 4.0f;

        }
        std::string minValString = str1.str();
        std::string maxValString = str2.str();


        if(vertical == 0)
        {
            minValString.append("°");
            maxValString.append("°");
            window.draw(returnText(xCord - 10, yCord + 5, minValString, 20));
            window.draw(returnText(xCord + axisWidth - 10, yCord + 5, maxValString, 20));
        }
        else
        {

            window.draw(returnText(xCord + 10, yCord + axisHeight/2, minValString, 20));
            window.draw(returnText(xCord + axisWidth + 5, yCord - axisHeight/2 - 20, maxValString, 20));

        }


        window.draw(axis);
        window.draw(slider);

    }
    void updateSliderPos(int w, int h)
    {

        if(vertical == 0)
        {
            slider.setPosition(w - 250, h - 30);
            axis.setPosition(w - 250, h - 30);
            xCord = w - 250;
            yCord = h - 30;
        }
        else
        {
            slider.setPosition(w - 50 + vertical, h - 160);
            axis.setPosition(w - 50, h - 160);
            xCord = w - 50;
            yCord = h - 160;
        }
    }

};


