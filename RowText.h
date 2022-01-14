
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#include <string>
class Textbox
{
public:
    void setUp(int size, sf::Color color, bool selectat, std::string barTitle)
    {
        textbox.setCharacterSize(size);
        textbox.setColor(color);
        isSelected = selectat;
        if (isSelected) textbox.setString("_");
        else textbox.setString("");
        title.setString(barTitle);
        title.setColor(sf::Color::White);
        title.setCharacterSize(30);
    }
    Textbox() {};
    void setFont(sf::Font &fonts)
    {
        textbox.setFont(fonts);
        title.setFont(fonts);
    }

    void setPosition(sf::Vector2f point)
    {
        textbox.setPosition(sf::Vector2f(point.x, point.y - 4));
        title.setPosition(sf::Vector2f(point.x - 20 - title.getGlobalBounds().width, point.y - 6));
        grid.setPosition(point.x - 5, point.y - 5);
        grid.setFillColor(sf::Color::Transparent);
        grid.setOutlineColor(sf::Color::White);
        grid.setOutlineThickness(1);
        grid.setSize(sf::Vector2f(textbox.getCharacterSize() * limit/3 * 2, textbox.getCharacterSize() * 4 / 3));
    }

    void seteazaLimita(int lim)
    {
        limit = lim - 1;
    }

    void setSelected(bool sel)
    {
        isSelected = sel;

        // If not selected, remove the '_' at the end:
        if (!sel)
        {
            std::string t = text.str();
            std::string newT = "";
            for (int i = 0; i < t.length(); i++)
            {
                newT += t[i];
            }
            textbox.setString(newT);
        }
        if(isSelected == true)
            grid.setOutlineColor(sf::Color::Red);
        else grid.setOutlineColor(sf::Color::White);
    }
    std::string getText()
    {
        return text.str();
    }
    void setText(std::string newText)
    {
        text.str("");
        text.clear();
        textbox.setString(newText);
        text << textbox.getString().toAnsiString();
    }
    void setFloat(float newFloat)
    {
        text.str("");
        text.clear();
        std::ostringstream newText;
        newText << newFloat;
        textbox.setString(newText.str());
        text << newText.str();
    }
    float getFloatValue()
    {
        float valToReturn;
        std::stringstream auxContainer;
        auxContainer << text.str();
        auxContainer >> valToReturn;
        return valToReturn;
    }
    void drawTo(sf::RenderWindow &window)
    {
        window.draw(textbox);
        window.draw(grid);
        window.draw(title);
    }
    bool isOn(int mx, int my)
    {
        if(mx >= grid.getPosition().x && mx <= grid.getPosition().x + grid.getLocalBounds().width &&
                my >= grid.getPosition().y && my <= grid.getPosition().y + grid.getLocalBounds().height)
            return true;
        return false;
    }
    void typedOn(sf::Event input)
    {
        if (isSelected)
        {
            int charTyped = input.text.unicode;
            if (charTyped < 128)
            {
                if (text.str().length() <= limit)
                {
                    inputLogic(charTyped);
                }
                else if (text.str().length() > limit && charTyped == DELETE_KEY)
                {
                    stergeUltimulCaracter();
                }

            }
        }
    }
private:
    sf::Text textbox;
    sf::Text title;
    sf::RectangleShape grid;
    std::ostringstream text;
    bool isSelected = false;
    int limit = 0;
    void stergeUltimulCaracter()
    {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++)
        {
            newT += t[i];
        }
        text.str("");
        text << newT;
        textbox.setString(text.str() + "_");
    }

    void inputLogic(int charTyped)
    {
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
        {
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == DELETE_KEY)
        {
            if (text.str().length() > 0)
            {
                stergeUltimulCaracter();
            }
        }
        textbox.setString(text.str() + "_");
    }
};








