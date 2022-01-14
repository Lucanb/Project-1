#include <SFML/Graphics.hpp>


class TextModal{
private:
    sf::RectangleShape grid;
    sf::Text content;
    sf::RectangleShape exit;
    sf::Text exitText;
    sf::RectangleShape blur;
    sf::Text title;
    bool isOpen = false;
public:
    TextModal(int w, int h, sf::Font &font, std::string name)
    {
        content.setFont(font);
        content.setCharacterSize(20);
        content.setPosition(w/2- 325 + 25, h/6-50+65);
        content.setFillColor(sf::Color::White);

        grid.setSize(sf::Vector2f(650, 450));
        grid.setPosition(w/2-325, h/6-50);
        grid.setFillColor(sf::Color::Black);
        grid.setOutlineColor(sf::Color::Red);
        grid.setOutlineThickness(3);

        title.setFont(font);
        title.setCharacterSize(20);
        title.setString(name);
        title.setPosition(w/2 - title.getGlobalBounds().width/2, h/6-50+10);
        title.setFillColor(sf::Color::White);

        blur.setPosition(0, 0);
        blur.setSize(sf::Vector2f(3000, 3000));
        blur.setFillColor(sf::Color(0, 0, 0, 200));

        exit.setSize(sf::Vector2f(30, 20));
        exit.setFillColor(sf::Color::Transparent);
        exit.setOutlineColor(sf::Color::White);
        exit.setOutlineThickness(3);
        exit.setPosition(sf::Vector2f(w/2-325 + 650 - 33, h/6-50+ 3));
        exitText.setFont(font);
        exitText.setPosition(w/2-325 + 650 - 26, h/6-50 - 9);
        exitText.setString("x");
        exitText.setColor(sf::Color::White);

    }
    void draw(sf::RenderWindow &window)
    {
        if(isOpen == true){
        window.draw(blur);
        window.draw(grid);
        window.draw(content);
        window.draw(exit);
        window.draw(exitText);
        window.draw(title);
        }
    }
    void updateGraphicsPos(int w, int h)
    {
        grid.setPosition(w/2-325, h/6-50);
        content.setPosition(w/2- 325 + 25, h/6-50+65);
        exit.setPosition(sf::Vector2f(w/2-325 + 650 - 33, h/6-50+ 3));
        exitText.setPosition(w/2-325 + 650 - 26, h/6-50 - 9);
        title.setPosition(w/2 - title.getGlobalBounds().width/2, h/6-50+10);
    }
    void open(){

        isOpen = true;
    }
    void logic(sf::Event event, sf::RenderWindow &window)
    {
        if(sf::Mouse::getPosition(window).x >= exit.getPosition().x && sf::Mouse::getPosition(window).x <= exit.getPosition().x + exit.getGlobalBounds().width &&
            sf::Mouse::getPosition(window).y >= exit.getPosition().y && sf::Mouse::getPosition(window).y <= exit.getPosition().y + exit.getGlobalBounds().height)
                        exit.setOutlineColor(sf::Color::Red);
        else
            exit.setOutlineColor(sf::Color::White);
        if (event.type == sf::Event::MouseButtonPressed)
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if(sf::Mouse::getPosition(window).x >= exit.getPosition().x && sf::Mouse::getPosition(window).x <= exit.getPosition().x + exit.getGlobalBounds().width &&
                    sf::Mouse::getPosition(window).y >= exit.getPosition().y && sf::Mouse::getPosition(window).y <= exit.getPosition().y + exit.getGlobalBounds().height)
                        isOpen = false;
            }
    }
    void setString(std::string newText)
    {
        content.setString(newText);
    }
};
