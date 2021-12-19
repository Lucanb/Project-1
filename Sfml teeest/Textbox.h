#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#include <string>
class Textbox
{
public:
    void setUp(int size, sf::Color color, bool sel, std::string barTitle)
    {
        textbox.setCharacterSize(size);
        textbox.setColor(color);
        isSelected = sel;

        // Check if the textbox is selected upon creation and display it accordingly:
        if (isSelected)
            textbox.setString("_");
        else
            textbox.setString("");

        title.setString(barTitle);
        title.setColor(sf::Color::White);
        title.setCharacterSize(60);
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

    void setLimit(int lim)
    {
        limit = lim - 1;
    }

    // Change selected state:
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

    // Function for event loop:
    void typedOn(sf::Event input)
    {
        if (isSelected)
        {
            int charTyped = input.text.unicode;

            // Only allow normal inputs:
            if (charTyped < 128)
            {
                // Don't go over the limit:
                if (text.str().length() <= limit)
                {
                    inputLogic(charTyped);
                }
                // But allow for char deletions:
                else if (text.str().length() > limit && charTyped == DELETE_KEY)
                {
                    deleteLastChar();
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

    // Delete the last character of the text:
    void deleteLastChar()
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

    // Get user input:
    void inputLogic(int charTyped)
    {
        // If the key pressed isn't delete, or the two selection keys, then append the text with the char:
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
        {
            text << static_cast<char>(charTyped);
        }
        // If the key is delete, then delete the char:
        else if (charTyped == DELETE_KEY)
        {
            if (text.str().length() > 0)
            {
                deleteLastChar();
            }
        }
        // Set the textbox text:
        textbox.setString(text.str() + "_");
    }
};








