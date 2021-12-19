#include <SFML/Graphics.hpp>
#include <iostream>
#include "Component.h"
#include "TextModal.h"
#include <fstream>

unsigned int W, H;
double resizedCoefW, resizedCoefH;

int toAddComponentType=-1;

bool isOnAnyButton=false;

Component ToDisplayComponents[10];

char currentFilePath[250];

class Button
{
public:
    sf::Text text;
    sf::RectangleShape grid;


    bool isOn(unsigned int mx, unsigned int my)
    {
        if (my > grid.getGlobalBounds().top && my < grid.getGlobalBounds().top + grid.getGlobalBounds().height
                && mx > grid.getGlobalBounds().left && mx < grid.getGlobalBounds().left + grid.getGlobalBounds().width)
            return true;
        return false;
    }

    void displayButton(sf::RenderWindow& win,bool selected)
    {
        if(selected==true)
            grid.setOutlineColor(sf::Color::Green);
        else
            grid.setOutlineColor(sf::Color::White);
        grid.setOutlineThickness(2);
        grid.setFillColor(sf::Color::Transparent);
        win.draw(grid);
        win.draw(text);

    }

    void displayHoveredButton(sf::RenderWindow& win)
    {
        if(isOnAnyButton==false)
        {
            isOnAnyButton=true;
        }
        grid.setOutlineColor(sf::Color::Red);
        grid.setOutlineThickness(2);
        grid.setFillColor(sf::Color::Transparent);
        win.draw(grid);
        win.draw(text);
    }
};

class Menu
{

public:
    Button buttons[25];
    Menu(sf::Font &font)
    {

        sf::FloatRect textRect;


        buttons[0].text.setString("New Project");
        buttons[0].text.setFont(font);
        buttons[0].text.setCharacterSize(60);

        textRect = buttons[0].text.getLocalBounds();
        buttons[0].text.setOrigin(textRect.left + textRect.width/2.0f,
                                  textRect.top);
        buttons[0].text.setPosition(W*0.25, H / 2);
        buttons[0].text.setFillColor(sf::Color::Green);
        buttons[0].grid.setSize(sf::Vector2f(buttons[0].text.getGlobalBounds().width + 20, buttons[0].text.getGlobalBounds().height + 17));
        buttons[0].grid.setPosition(buttons[0].text.getGlobalBounds().left - 10, buttons[0].text.getGlobalBounds().top - 10);


        buttons[1].text.setString("back");
        buttons[1].text.setFont(font);
        buttons[1].text.setCharacterSize(60);
        buttons[1].text.setPosition(4, -1);
        buttons[1].text.setFillColor(sf::Color::Green);
        buttons[1].grid.setSize(sf::Vector2f(buttons[1].text.getGlobalBounds().width + 10, buttons[1].text.getGlobalBounds().height + 7));
        buttons[1].grid.setPosition(buttons[1].text.getGlobalBounds().left - 5, buttons[1].text.getGlobalBounds().top - 5);

        buttons[2].text.setString("Open Project");
        buttons[2].text.setFont(font);
        buttons[2].text.setCharacterSize(60);
        textRect = buttons[2].text.getLocalBounds();
        buttons[2].text.setOrigin(textRect.left + textRect.width/2.0f,
                                  textRect.top);

        buttons[2].text.setPosition(W * 0.5, H /2); //+ 75 * (0.5 + resizedCoefH)
        buttons[2].text.setFillColor(sf::Color::Green);
        buttons[2].grid.setSize(sf::Vector2f(buttons[2].text.getGlobalBounds().width + 20, buttons[2].text.getGlobalBounds().height + 17));
        buttons[2].grid.setPosition(buttons[2].text.getGlobalBounds().left - 10, buttons[2].text.getGlobalBounds().top - 10);

        buttons[3].text.setString("Info");
        buttons[3].text.setFont(font);
        buttons[3].text.setCharacterSize(65);
        textRect = buttons[3].text.getLocalBounds();
        buttons[3].text.setOrigin(textRect.left + textRect.width/2.0f,
                                  textRect.top);
        buttons[3].text.setPosition(W *0.75 , H / 2); // + 150 * (0.5 + resizedCoefH)
        buttons[3].text.setFillColor(sf::Color::Green);
        buttons[3].grid.setSize(sf::Vector2f(buttons[3].text.getGlobalBounds().width + 20, buttons[3].text.getGlobalBounds().height + 17));
        buttons[3].grid.setPosition(buttons[3].text.getGlobalBounds().left - 10, buttons[3].text.getGlobalBounds().top - 10);

        buttons[4].text.setString("Exit");
        buttons[4].text.setFont(font);
        buttons[4].text.setCharacterSize(60);
        textRect = buttons[4].text.getLocalBounds();
        buttons[4].text.setOrigin(textRect.left + textRect.width/2.0f,
                                  textRect.top);
        buttons[4].text.setPosition(W / 2, H / 3 + 225 * (0.5 + resizedCoefH));
        buttons[4].text.setFillColor(sf::Color::Green);
        buttons[4].grid.setSize(sf::Vector2f(buttons[4].text.getGlobalBounds().width + 20, buttons[4].text.getGlobalBounds().height + 17));
        buttons[4].grid.setPosition(buttons[4].text.getGlobalBounds().left - 10, buttons[4].text.getGlobalBounds().top - 10);

        unsigned int sizeBarButton = (W - buttons[1].text.getGlobalBounds().width - 17)/5;

    /*    buttons[5].text.setString("Save");
        buttons[5].text.setFont(font);
        buttons[5].text.setCharacterSize(30);
        buttons[5].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[5].text.getGlobalBounds().width / 2, -1);
        buttons[5].text.setFillColor(sf::Color::White);
        buttons[5].grid.setSize(sf::Vector2f(sizeBarButton, 29));
        buttons[5].grid.setPosition(buttons[1].text.getGlobalBounds().width + 16, buttons[5].text.getGlobalBounds().top - 6);
     */
        buttons[6].text.setString("Save As");
        buttons[6].text.setFont(font);
        buttons[6].text.setCharacterSize(30);
        buttons[6].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[6].text.getGlobalBounds().width / 2 + sizeBarButton, -4);
        buttons[6].text.setFillColor(sf::Color::White);
        buttons[6].grid.setSize(sf::Vector2f(sizeBarButton, 29));
        buttons[6].grid.setPosition(buttons[1].text.getGlobalBounds().width + sizeBarButton + 20, buttons[6].text.getGlobalBounds().top -3);
/*
        buttons[7].text.setString("Open");
        buttons[7].text.setFont(font);
        buttons[7].text.setCharacterSize(30);
        buttons[7].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[7].text.getGlobalBounds().width / 2 + 2*sizeBarButton, -4);
        buttons[7].text.setFillColor(sf::Color::White);
        buttons[7].grid.setSize(sf::Vector2f(sizeBarButton, 29));
        buttons[7].grid.setPosition(buttons[1].text.getGlobalBounds().width + 2*sizeBarButton +24, buttons[7].text.getGlobalBounds().top - 3);
 */
        buttons[8].text.setString("Reset");
        buttons[8].text.setFont(font);
        buttons[8].text.setCharacterSize(30);
        buttons[8].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[8].text.getGlobalBounds().width / 2 + 3*sizeBarButton, -2);
        buttons[8].text.setFillColor(sf::Color::White);
        buttons[8].grid.setSize(sf::Vector2f(sizeBarButton, 29));
        buttons[8].grid.setPosition(buttons[1].text.getGlobalBounds().width + 3*sizeBarButton +28, buttons[8].text.getGlobalBounds().top - 5);
/*
        buttons[9].text.setString("Help");
        buttons[9].text.setFont(font);
        buttons[9].text.setCharacterSize(30);
        buttons[9].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[9].text.getGlobalBounds().width / 2 + 4*sizeBarButton, -5);
        buttons[9].text.setFillColor(sf::Color::White);
        buttons[9].grid.setSize(sf::Vector2f(sizeBarButton-17, 29));
        buttons[9].grid.setPosition(buttons[1].text.getGlobalBounds().width + 4*sizeBarButton +32, buttons[9].text.getGlobalBounds().top - 1);
*/
        buttons[10].text.setString("Undo");
        buttons[10].text.setFont(font);
        buttons[10].text.setCharacterSize(30);
        buttons[10].text.setPosition(74 - buttons[10].text.getGlobalBounds().width/2, H-35);
        buttons[10].text.setFillColor(sf::Color::White);
        buttons[10].grid.setSize(sf::Vector2f(150, 29));
        buttons[10].grid.setPosition(2, H-31);
 /*
        buttons[11].text.setString("Redo");
        buttons[11].text.setFont(font);
        buttons[11].text.setCharacterSize(30);
        buttons[11].text.setPosition(230 - buttons[11].text.getGlobalBounds().width/2, H-35);
        buttons[11].text.setFillColor(sf::Color::White);
        buttons[11].grid.setSize(sf::Vector2f(150, 29));
        buttons[11].grid.setPosition(156, H-31);
*/
        buttons[12].text.setString("Edit");
        buttons[12].text.setFont(font);
        buttons[12].text.setCharacterSize(30);
        buttons[12].text.setPosition(384 - buttons[12].text.getGlobalBounds().width/2, H-35);
        buttons[12].text.setFillColor(sf::Color::White);
        buttons[12].grid.setSize(sf::Vector2f(150, 29));
        buttons[12].grid.setPosition(310, H-31);

        buttons[13].text.setString("Delete");
        buttons[13].text.setFont(font);
        buttons[13].text.setCharacterSize(30);
        buttons[13].text.setPosition(538 - buttons[13].text.getGlobalBounds().width/2, H-35);
        buttons[13].text.setFillColor(sf::Color::White);
        buttons[13].grid.setSize(sf::Vector2f(150, 29));
        buttons[13].grid.setPosition(464, H-31);

        buttons[14].grid.setSize(sf::Vector2f(150, 70));
        buttons[14].grid.setPosition(2, H/2 - 350);

        buttons[15].grid.setSize(sf::Vector2f(150, 70));
        buttons[15].grid.setPosition(2, H/2 - 280);

        buttons[16].grid.setSize(sf::Vector2f(150, 70));
        buttons[16].grid.setPosition(2, H/2 - 210);

        buttons[17].grid.setSize(sf::Vector2f(150, 70));
        buttons[17].grid.setPosition(2, H/2 - 140);

        buttons[18].grid.setSize(sf::Vector2f(150, 70));
        buttons[18].grid.setPosition(2, H/2 - 70);

        buttons[19].grid.setSize(sf::Vector2f(150, 70));
        buttons[19].grid.setPosition(2, H/2 - 0);

        buttons[20].grid.setSize(sf::Vector2f(150, 70));
        buttons[20].grid.setPosition(2, H/2 + 70);

        buttons[21].grid.setSize(sf::Vector2f(150, 70));
        buttons[21].grid.setPosition(2, H/2 + 140);

        buttons[22].grid.setSize(sf::Vector2f(150, 70));
        buttons[22].grid.setPosition(2, H/2 + 210);

        buttons[23].grid.setSize(sf::Vector2f(150, 90));
        buttons[23].grid.setPosition(2, H/2 + 280);

    };

    void updatePos()
    {

        unsigned int sizeBarButton = (W - buttons[1].text.getGlobalBounds().width - 17)/5;

        buttons[0].text.setPosition(W / 2, H / 3);
        buttons[2].text.setPosition(W / 2, H / 3 + 75 * (0.5 + resizedCoefH));
        buttons[3].text.setPosition(W / 2, H / 3 + 150 * (0.5 + resizedCoefH));
        buttons[4].text.setPosition(W / 2, H / 3 + 225 * (0.5 + resizedCoefH));
        buttons[5].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[5].text.getGlobalBounds().width / 2, -1);
        buttons[6].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[6].text.getGlobalBounds().width / 2 + sizeBarButton, -4);
        buttons[7].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[7].text.getGlobalBounds().width / 2 + 2*sizeBarButton, -4);
        buttons[8].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[8].text.getGlobalBounds().width / 2 + 3*sizeBarButton, -2);
     //   buttons[9].text.setPosition(buttons[1].text.getGlobalBounds().width + 16 + (W - buttons[1].text.getGlobalBounds().width- 17)/10 - buttons[9].text.getGlobalBounds().width / 2 + 4*sizeBarButton, -5);
        buttons[10].text.setPosition(74 - buttons[10].text.getGlobalBounds().width/2, H-35);
        buttons[11].text.setPosition(230 - buttons[11].text.getGlobalBounds().width/2, H-35);
        buttons[12].text.setPosition(384 - buttons[12].text.getGlobalBounds().width/2, H-35);
        buttons[13].text.setPosition(538 - buttons[13].text.getGlobalBounds().width/2, H-35);

        buttons[0].grid.setSize(sf::Vector2f(buttons[0].text.getGlobalBounds().width + 20, buttons[0].text.getGlobalBounds().height + 17));
        buttons[0].grid.setPosition(buttons[0].text.getGlobalBounds().left - 10, buttons[0].text.getGlobalBounds().top - 10);
        buttons[2].grid.setSize(sf::Vector2f(buttons[2].text.getGlobalBounds().width + 20, buttons[2].text.getGlobalBounds().height + 17));
        buttons[2].grid.setPosition(buttons[2].text.getGlobalBounds().left - 10, buttons[2].text.getGlobalBounds().top - 10);
        buttons[3].grid.setSize(sf::Vector2f(buttons[3].text.getGlobalBounds().width + 20, buttons[3].text.getGlobalBounds().height + 17));
        buttons[3].grid.setPosition(buttons[3].text.getGlobalBounds().left - 10, buttons[3].text.getGlobalBounds().top - 10);
        buttons[4].grid.setSize(sf::Vector2f(buttons[4].text.getGlobalBounds().width + 20, buttons[4].text.getGlobalBounds().height + 17));
        buttons[4].grid.setPosition(buttons[4].text.getGlobalBounds().left - 10, buttons[4].text.getGlobalBounds().top - 10);
        buttons[5].grid.setSize(sf::Vector2f(sizeBarButton, 29));
        buttons[5].grid.setPosition(buttons[1].text.getGlobalBounds().width + 16, buttons[5].text.getGlobalBounds().top - 6);
        buttons[6].grid.setSize(sf::Vector2f(sizeBarButton, 29));
        buttons[6].grid.setPosition(buttons[1].text.getGlobalBounds().width + sizeBarButton + 20, buttons[6].text.getGlobalBounds().top -3);
        buttons[7].grid.setSize(sf::Vector2f(sizeBarButton, 29));
        buttons[7].grid.setPosition(buttons[1].text.getGlobalBounds().width + 2*sizeBarButton +24, buttons[7].text.getGlobalBounds().top - 3);
        buttons[8].grid.setSize(sf::Vector2f(sizeBarButton, 29));
        buttons[8].grid.setPosition(buttons[1].text.getGlobalBounds().width + 3*sizeBarButton +28, buttons[8].text.getGlobalBounds().top - 5);
        buttons[9].grid.setSize(sf::Vector2f(sizeBarButton - 13, 29));
        buttons[9].grid.setPosition(buttons[1].text.getGlobalBounds().width + 4*sizeBarButton +32, buttons[9].text.getGlobalBounds().top - 1);
        buttons[10].grid.setPosition(2, H-31);
        buttons[11].grid.setPosition(156, H-31);
        buttons[12].grid.setPosition(310, H-31);
        buttons[13].grid.setPosition(464, H-31);
        buttons[14].grid.setPosition(2, H/2 - 350);
        buttons[15].grid.setPosition(2, H/2 - 280);
        buttons[16].grid.setPosition(2, H/2 - 210);
        buttons[17].grid.setPosition(2, H/2 - 140);
        buttons[18].grid.setPosition(2, H/2 -70);
        buttons[19].grid.setPosition(2, H/2 - 0);
        buttons[20].grid.setPosition(2, H/2 + 70);
        buttons[21].grid.setPosition(2, H/2 + 140);
        buttons[22].grid.setPosition(2, H/2 + 210);
        buttons[23].grid.setPosition(2, H/2 + 280);
    };

};

int main()
{

    FILE *fileToRead, *fileToWrite;


    ///FOR SMOOTH SHAPES

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    W = sf::VideoMode::getDesktopMode().width - 100;
    H = sf::VideoMode::getDesktopMode().height - 100;

    resizedCoefW = double(W/1920.0);
    resizedCoefH = double(H/1017.0);
    double cpyCoefW = resizedCoefW;
    double cpyCoefH = resizedCoefH;
    int cpyW = W;
    int cpyH = H;

    initializeComponentTypes();
    sf::RenderWindow window(sf::VideoMode(W, H), "Electron");//  sf::Style::Default, settings);
    sf::Text title;
    sf::Font font;

    CircuitStructure Circuit;

    font.loadFromFile("OpenSans-Regular.ttf");
    Menu menu(font);

    sf::Texture bgImageTexture;
    bgImageTexture.loadFromFile("bg.jpg");

    sf::Sprite bgImage(bgImageTexture);
    bgImage.setScale(resizedCoefW, resizedCoefH);

    title.setString("ELECTRON");
    title.setFont(font);
    title.setCharacterSize(100);
    title.setPosition(W / 2 - title.getGlobalBounds().width / 2, H / 8);
    title.setFillColor(sf::Color::White);

    Circuit.initializeModal(W/2 - 200, H/3, font);

    sf::Texture infoImage[9];
    sf::Sprite infoImages[9];

    sf::Text info[9];
    for(int i = 0; i<9; i++)
    {
        info[i].setFont(font);
        info[i].setCharacterSize(20);
        info[i].setFillColor(sf::Color::White);
    }
    int renderPattern = -1;
/// SLIDER INITIALIZATION
    SliderSFML rotationSlider(W - 250, H - 30, 0);
    rotationSlider.create(0, 360);

    SliderSFML scaleSlider(W - 50, H - 160, 1);
    scaleSlider.create(3, 8);
    scaleSlider.setSliderValue(4);

    int latestScaleSliderValue = scaleSlider.getSliderValue();
    float latestRotationSliderValue = rotationSlider.getSliderValue()/4.0f;


    TextModal help(W, H, font, "Help");
    help.setString("back     	  - return to menu page\nSave     	  - save changes made in the same project file\nSave As      - save project into another file\nOpen     	 - open an existing project from file directory\nReset    	  - deletes every component on the screen\nComponent Button  - creates a circuit object of that type by \n		               clicking the button, then a place on screen\nUndo 		 - will negate the last operation made\nRedo 		  - will negate the last Undo operation made\nEdit 		    - opens a window where the component\n		               parameters can be modified\nDelete 		- deletes a component or a conection\nVertical Slider   - when a component is selected, changes\n		               the size multiplier coeficient\nHorizontal Slider - when a component is selected, changes \n		               the rotation value of that object\n\nA component is selected when the specific component gets \nclicked.\nTo make a conection between two components, click and hold \non a I/O point, drag and release on a O/I point.");

    bool addResistors=false;

    for(int i=0; i<=9; i++)
    {
        ToDisplayComponents[i].componentType=i;
        ToDisplayComponents[i].topLeftCorner.x=75;
        if(i==9)
            ToDisplayComponents[i].topLeftCorner.y=H/2-350+i*70+45;
        else
            ToDisplayComponents[i].topLeftCorner.y=H/2-350+i*70+35;
        ToDisplayComponents[i].read();
    }

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        sf::Vector2i mousePos;
        mousePos = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bool isOnCRUDButton=false;
                    bool isOnAnyButton=false;
                    for (int i = 0; i < 24; i++)
                    {
                        if (menu.buttons[i].isOn(event.mouseButton.x, event.mouseButton.y))
                        {
                            if(i>=10&&i<=13)
                            {
                                isOnCRUDButton=true;
                            }
                            else
                                isOnAnyButton=true;

                            if(i == 0 && renderPattern == -1)
                            {
                                renderPattern = 0;
                            }

                            if(i == 3 && renderPattern == -1)
                            {
                                renderPattern = 3;
                            }

                           // if(i==2 && renderPattern == -1)
                            //{
                              //  Circuit.openFile(currentFilePath,renderPattern);

                             //   renderPattern=0;
                           // }
                            if(i == 4 && renderPattern == -1)
                                exit(0);
                           if (renderPattern == -1 && i != 1)
                            {
                                if(i == 3)
                                 std::cout<<"pressed"<<std::endl;

                                renderPattern = i;
                                break;
                            }
                            if (i == 1)
                            {
                                renderPattern=-1;
                            }
                            //if(i==5 && renderPattern == 0)
                            //{
                              //  Circuit.saveFileAs(currentFilePath);
                            //}
                            if(i==6 && renderPattern == 0)
                            {
                                Circuit.saveFileAs(currentFilePath);
                            }
                           // if(i==8 && renderPattern == 0)
                            //{
                                    //Circuit.reset(currentFilePath);
                            //}
                            if(i == 9 && renderPattern == 0)
                            {
                                help.open();
                            }

                            //COMPONENT ACTIONS

                            if(i == 10&& renderPattern == 0)
                            {
                                Circuit.undoAction();
                            }

                            if(i == 11&& renderPattern == 0)
                            {
                                Circuit.redoAction();
                            }

                            if(i == 12&& renderPattern == 0)
                            {
                                if(Circuit.currentSelectedComponent!=-1)
                                {
                                    Circuit.toEditComponentId=Circuit.currentSelectedComponent;
                                    toAddComponentType=-1;
                                    Circuit.openModal();
                                }
                            }

                            if(i==13)
                            {
                                Circuit.deleteElement();
                            }



                            if(i>=14 && renderPattern == 0)
                            {
                                if(toAddComponentType==i-14)
                                    toAddComponentType=-1;
                                else
                                    toAddComponentType=i-14;
                            }
                        }
                    }

                    if(Circuit.onMousePress(mousePos.x,mousePos.y,window)==false)
                    {
                        if(scaleSlider.isMouseOn(window)==0&&rotationSlider.isMouseOn(window)==0&&isOnAnyButton==false&&isOnCRUDButton==false)
                            Circuit.unsetCurrentSelectedComponent();
                        else
                        {

                        }
                        if(toAddComponentType!=-1&&isOnAnyButton==false&&isOnCRUDButton==false)
                        {
                            if(rotationSlider.isMouseOn(window)==false&&scaleSlider.isMouseOn(window)==false)
                                Circuit.addElement(toAddComponentType,event.mouseButton.x,event.mouseButton.y);
                            else
                                toAddComponentType=-1;
                        }
                    }
                }
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                if(Circuit.currentSelectedComponent!=-1)
                    Circuit.Components[Circuit.currentSelectedComponent].selected=false;
                Circuit.currentSelectedComponent=-1;
                Circuit.currentSelectedConnection=-1;
                toAddComponentType=-1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if(Circuit.currentSelectedComponent!=-1)
                    Circuit.Components[Circuit.currentSelectedComponent].selected=false;
                Circuit.currentSelectedComponent=-1;
                Circuit.currentSelectedConnection=-1;
                toAddComponentType=-1;

            }
            if (event.type == sf::Event::MouseMoved)
            {
                Circuit.onMouseMove(mousePos.x,mousePos.y);
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if(scaleSlider.isActivated==true||rotationSlider.isActivated==true)
                    Circuit.isASliderSelected=1;
                else
                    Circuit.isASliderSelected=0;
                if(rotationSlider.isActivated==true)
                {
                    Circuit.addRotationAction();
                }
                if(scaleSlider.isActivated==true)
                {
                    Circuit.addScaleAction();
                }
                Circuit.onMouseRelease(mousePos.x,mousePos.y);

                rotationSlider.isActivated=false;
                scaleSlider.isActivated=false;
            }




            if(event.type == sf::Event::Resized)
            {

                if(renderPattern == 3)
                {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                    window.setSize(sf::Vector2u(cpyW, cpyH));
                    continue;
                }
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                W = window.getSize().x;
                H = window.getSize().y;

                if(W < 1000)
                    W = 1000;
                if(H < 880)
                    H = 880;
                Circuit.updateModalPos(W/2 - 200, H/3);
                help.updatePos(W, H);
                rotationSlider.updateSliderPos(W, H);
                rotationSlider.setSliderValue(rotationSlider.getSliderValue());
                scaleSlider.updateSliderPos(W, H);
                scaleSlider.setSliderValue(scaleSlider.getSliderValue());

                resizedCoefW = double(W/1920.0);
                resizedCoefH = double(H/1017.0);

                sf::Vector2u newSize;

                newSize.x = W;
                newSize.y = H;
                window.setSize(newSize);
                bgImage.setScale(resizedCoefW, resizedCoefH);
                menu.updatePos();

                for(int i=0; i<=9; i++)
                {
                    ToDisplayComponents[i].topLeftCorner.x=75;
                    if(i==9)
                        ToDisplayComponents[i].topLeftCorner.y=H/2-350+i*70+45;
                    else
                        ToDisplayComponents[i].topLeftCorner.y=H/2-350+i*70+35;
                }


            }

            Circuit.modalLogic(event, window);
            help.logic(event, window);


        }

        if (renderPattern == 1)
            renderPattern = -1;
        if (renderPattern == -1)
        {
            title.setString("ELECTRON");
            title.setPosition(W / 2 - title.getGlobalBounds().width / 2, H / 8);

            window.draw(bgImage);
            window.draw(title);
            for (int i = 0; i < 5; i++)
            {
                if (i == 1)
                    continue;
                if (menu.buttons[i].isOn(mousePos.x, mousePos.y))
                    menu.buttons[i].displayHoveredButton(window);
                else menu.buttons[i].displayButton(window,false);
            }
        }


        if (renderPattern == 0)
        {
            Circuit.draw(window);
            rotationSlider.draw(window);
            scaleSlider.draw(window);
            for(int i=0; i<=9; i++)
            {
                ToDisplayComponents[i].draw(window);
            }

            bool isOnAButton=false;
            if (menu.buttons[1].isOn(mousePos.x, mousePos.y))
            {
                menu.buttons[1].displayHoveredButton(window);
                isOnAButton=true;
            }
            else menu.buttons[1].displayButton(window,false);

            for(int i = 5; i<=24; i++)
                if (menu.buttons[i].isOn(mousePos.x, mousePos.y))
                {
                    menu.buttons[i].displayHoveredButton(window);
                    isOnAButton=true;
                }
                else menu.buttons[i].displayButton(window,i-14==toAddComponentType);
            if(isOnAButton==false)
            {
                isOnAnyButton=false;
            }
            if(int(rotationSlider.getSliderValue()) != latestRotationSliderValue&&rotationSlider.isActivated==true)
            {
                int angle=int(rotationSlider.getSliderValue());
                Circuit.rotateSelectedComponent(angle);
            }
            latestRotationSliderValue = int(rotationSlider.getSliderValue());

            if(scaleSlider.getSliderValue()/4.0f != latestScaleSliderValue&&scaleSlider.isActivated==true)
            {
                float scaleAt=scaleSlider.getSliderValue()/4.0f;
                Circuit.scaleSelectedComponent(scaleAt);
            }
            latestScaleSliderValue = scaleSlider.getSliderValue()/4.0f;
            help.draw(window);
            Circuit.drawModal(window);

        }

          if (renderPattern == 2)
        {
            title.setString("Waiting for your Project");
            title.setPosition(W / 2 - title.getGlobalBounds().width / 2, H / 8);

            window.draw(title);
            if (menu.buttons[1].isOn(mousePos.x, mousePos.y))
                menu.buttons[1].displayHoveredButton(window);
            else menu.buttons[1].displayButton(window,false);
        }

        if (renderPattern == 3)
        {

            title.setString("Components Information");
            title.setPosition(W / 2 - title.getGlobalBounds().width / 2, 20);
          //  infoImage[0].loadFromFile("electrical_cell.png");
           // infoImages[0].setTexture(infoImage[0]);
            //infoImages[0].setPosition(100, 200);
            //infoImages[0].setScale(0.55, 0.55);
            ///pana aici las dupa sterg acolada si le unesc
             window.setSize(sf::Vector2u(cpyW, cpyH));
            bgImage.setScale(cpyCoefW, cpyCoefH);
            window.draw(bgImage);
            window.draw(title);

        }
        /*{

            info[0].setPosition(cpyW/6, 200);
            info[0].setString("An electrical cell is a power supply for a circuit,\n letting current flow from the positive terminal around the circuit \nto the negative terminal. The cell creates a potential \ndifference across itself by supplying energy to charges.");


            infoImage[1].loadFromFile("resistor.png");
            infoImages[1].setTexture(infoImage[1]);
            infoImages[1].setPosition(100, 325);
            infoImages[1].setScale(0.064, 0.075);
            info[1].setPosition(cpyW/6, 325);
            info[1].setString("A resistor is a component that restricts flow of current \nin a circuit. The voltage V across the resistor \nis directly proportional to the current I,I through a resistor.");


            infoImage[2].loadFromFile("bulb.png");
            infoImages[2].setTexture(infoImage[2]);
            infoImages[2].setPosition(100, 430);
            infoImages[2].setScale(0.38, 0.38);
            info[2].setPosition(cpyW/6, 450);
            info[2].setString("A bulb is a component that transforms electrical energy into \nlight energy. The brightness of the bulb depends on its power \nP, which has the units of watts, W.");


            infoImage[3].loadFromFile("diode.png");
            infoImages[3].setTexture(infoImage[3]);
            infoImages[3].setPosition(100, 575);
            infoImages[3].setScale(0.47, 0.38);
            info[3].setPosition(cpyW/6, 575);
            info[3].setString("An ideal diode is a component that only allows current in one \ndirection. This is because the ideal diode has an \ninfinite resistance in the reverse direction and \nzero resistance in the forward direction.");


            infoImage[4].loadFromFile("ammeter.jpg");
            infoImages[4].setTexture(infoImage[4]);
            infoImages[4].setPosition(100, 700);
            infoImages[4].setScale(0.485, 0.5);
            info[4].setPosition(cpyW/6, 700);
            info[4].setString("An ammeter is a device that measures current flowing \nbetween its ends. Current is the rate of flow of charge\n and is measured in amps with symbol A.");


            infoImage[5].loadFromFile("voltmeter.jpg");
            infoImages[5].setTexture(infoImage[5]);
            infoImages[5].setPosition(cpyW/3*2 - 200, 200);
            infoImages[5].setScale(0.485, 0.53);
            info[5].setPosition(cpyW/3*2, 200);
            info[5].setString("An voltmeter is a device that measures the potential \ndifference between its ends. Potential difference is often\n called voltage and is measured in volts with symbol V.");


            infoImage[6].loadFromFile("capacitor.jpg");
            infoImages[6].setTexture(infoImage[6]);
            infoImages[6].setPosition(cpyW/3*2 - 200, 325);
            infoImages[6].setScale(0.79, 0.53);
            info[6].setPosition(cpyW/3*2, 325);
            info[6].setString("A capacitor is a component that consists of two \nconducting plates separated by an insulator. It is used to\n temporarily store electrical charge and energy.");


            infoImage[7].loadFromFile("transistor.jpg");
            infoImages[7].setTexture(infoImage[7]);
            infoImages[7].setPosition(cpyW/3*2 - 200, 450);
            infoImages[7].setScale(0.383, 0.3);
            info[7].setPosition(cpyW/3*2, 450);
            info[7].setString("A transistor acts as a switch or as an amplifier\n in electrical circuits. The three pins are the\n Collector C, Base B and Emitter E. When there is zero \nvoltage between the base and ground the transistor does not \nallow any current to flow though it from its C pin to its E pin.");


            infoImage[8].loadFromFile("fuse.jpg");
            infoImages[8].setTexture(infoImage[8]);
            infoImages[8].setPosition(cpyW/3*2 - 200, 625);
            infoImages[8].setScale(0.82, 0.82);
            info[8].setPosition(cpyW/3*2, 625);
            info[8].setString("A fuse is a device that allows current to flow while it is below \na certain value, which depends on the rating of fuse. When the\n current exceeds this value, the fuse will blow (melt or break),\n which breaks the circuit and stops current flowing altogether.");

            window.setSize(sf::Vector2u(cpyW, cpyH));
            bgImage.setScale(cpyCoefW, cpyCoefH);
            window.draw(bgImage);
            window.draw(title);


            for(int i = 0; i<9; i++)
            {
                window.draw(info[i]);
                window.draw(infoImages[i]);
            }
            if (menu.buttons[1].isOn(mousePos.x, mousePos.y))
                menu.buttons[1].displayHoveredButton(window);
            else menu.buttons[1].displayButton(window,false);
        }
*/
        window.display();

    }

    return 0;
}


