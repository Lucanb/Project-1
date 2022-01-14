#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComponentsConstruct.h"
#include "ModifText.h"
#include <fstream>
unsigned int W, H;
double CoeficientMarimeNouaW, CoeficientMarimeNouaH;
bool middleButtonsStatus = false;
int toAddComponentType=-1;
char caleCurentaCatreFisier[250];
bool isOnAnyButton=false;
Component ToDisplayComponents[10];
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

    void afiseazaButon(sf::RenderWindow& win,bool selected)
    {
        if(selected==true)
        grid.setOutlineColor(sf::Color::White);
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
    Button buttons[26];
    Menu(sf::Font &font)
    {
        sf::FloatRect textRect;

        buttons[0].text.setString("Proiect Nou");
        buttons[0].text.setFont(font);
        buttons[0].text.setCharacterSize(50);

        textRect = buttons[0].text.getLocalBounds();
        buttons[0].text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top);

        buttons[0].text.setPosition(W*0.25, H / 2);
        buttons[0].text.setFillColor(sf::Color::Green);
        buttons[0].grid.setSize(sf::Vector2f(buttons[0].text.getGlobalBounds().width + 20, buttons[0].text.getGlobalBounds().height + 17));
        buttons[0].grid.setPosition(buttons[0].text.getGlobalBounds().left - 10, buttons[0].text.getGlobalBounds().top - 10);


        buttons[1].text.setString("Inapoi");
        buttons[1].text.setFont(font);
        buttons[1].text.setCharacterSize(30);
        buttons[1].text.setPosition(4, -1);
        buttons[1].text.setFillColor(sf::Color::Green);
        buttons[1].grid.setSize(sf::Vector2f(buttons[1].text.getGlobalBounds().width + 10, buttons[1].text.getGlobalBounds().height + 7));
        buttons[1].grid.setPosition(buttons[1].text.getGlobalBounds().left - 5, buttons[1].text.getGlobalBounds().top - 5);

        buttons[2].text.setString(" Deschide Proiect ");
        buttons[2].text.setFont(font);
        buttons[2].text.setCharacterSize(50);
        textRect = buttons[2].text.getLocalBounds();
        buttons[2].text.setOrigin(textRect.left + textRect.width/2.0f,
                                  textRect.top);

        buttons[2].text.setPosition(W * 0.5, H /2); //+ 75 * (0.5 + CoeficientMarimeNouaH)
        buttons[2].text.setFillColor(sf::Color::Green);
        buttons[2].grid.setSize(sf::Vector2f(buttons[2].text.getGlobalBounds().width + 20, buttons[2].text.getGlobalBounds().height + 17));
        buttons[2].grid.setPosition(buttons[2].text.getGlobalBounds().left - 10, buttons[2].text.getGlobalBounds().top - 10);

        buttons[3].text.setString("Informatii");
        buttons[3].text.setFont(font);
        buttons[3].text.setCharacterSize(55);
        textRect = buttons[3].text.getLocalBounds();
        buttons[3].text.setOrigin(textRect.left + textRect.width/2.0f,
                                  textRect.top);
        buttons[3].text.setPosition(W *0.75 , H / 2); // + 150 * (0.5 + CoeficientMarimeNouaH)
        buttons[3].text.setFillColor(sf::Color::Green);
        buttons[3].grid.setSize(sf::Vector2f(buttons[3].text.getGlobalBounds().width + 20, buttons[3].text.getGlobalBounds().height + 17));
        buttons[3].grid.setPosition(buttons[3].text.getGlobalBounds().left - 10, buttons[3].text.getGlobalBounds().top - 10);

        buttons[4].text.setString("Iesire");
        buttons[4].text.setFont(font);
        buttons[4].text.setCharacterSize(50);
        textRect = buttons[4].text.getLocalBounds();
        buttons[4].text.setOrigin(textRect.left + textRect.width/2.0f,
                                  textRect.top);
        buttons[4].text.setPosition(W / 2, H / 3 + 225 * (0.5 + CoeficientMarimeNouaH));
        buttons[4].text.setFillColor(sf::Color::Green);
        buttons[4].grid.setSize(sf::Vector2f(buttons[4].text.getGlobalBounds().width + 20, buttons[4].text.getGlobalBounds().height + 17));
        buttons[4].grid.setPosition(buttons[4].text.getGlobalBounds().left - 10, buttons[4].text.getGlobalBounds().top - 10);

        unsigned int sizeBarButton = (W - buttons[1].text.getGlobalBounds().width - 17)/5;

        buttons[5].text.setString("Salveaza");
        buttons[5].text.setFont(font);
        buttons[5].text.setCharacterSize(30);
        buttons[5].text.setPosition(100 - buttons[5].text.getGlobalBounds().width/2, 105);
        buttons[5].text.setFillColor(sf::Color::White);
        buttons[5].grid.setSize(sf::Vector2f(200, 50));
        buttons[5].grid.setPosition(1,100);

        buttons[6].text.setString("Salveaza ca");
        buttons[6].text.setFont(font);
        buttons[6].text.setCharacterSize(30);
        buttons[6].text.setPosition(100 - buttons[6].text.getGlobalBounds().width/2, 155);
        buttons[6].text.setFillColor(sf::Color::White);
        buttons[6].grid.setSize(sf::Vector2f(200, 50));
        buttons[6].grid.setPosition(1,150);

        buttons[7].text.setString("Deschide");
        buttons[7].text.setFont(font);
        buttons[7].text.setCharacterSize(30);
        buttons[7].text.setPosition(100 - buttons[7].text.getGlobalBounds().width/2, 205);
        buttons[7].text.setFillColor(sf::Color::White);
        buttons[7].grid.setSize(sf::Vector2f(200, 50));
        buttons[7].grid.setPosition(1,200);

        buttons[8].text.setString("Comenzi");
        buttons[8].text.setFont(font);
        buttons[8].text.setCharacterSize(30);
        buttons[8].text.setPosition(100 - buttons[8].text.getGlobalBounds().width/2, 255);
        buttons[8].text.setFillColor(sf::Color::White);
        buttons[8].grid.setSize(sf::Vector2f(200, 50));
        buttons[8].grid.setPosition(1,250);

        buttons[9].text.setString("Ajutor");
        buttons[9].text.setFont(font);
        buttons[9].text.setCharacterSize(30);
        buttons[9].text.setPosition(100 - buttons[9].text.getGlobalBounds().width/2, 305);
        buttons[9].text.setFillColor(sf::Color::White);
        buttons[9].grid.setSize(sf::Vector2f(200, 50));
        buttons[9].grid.setPosition(1,300);

        buttons[10].text.setString("Anuleaza");
        buttons[10].text.setFont(font);
        buttons[10].text.setCharacterSize(30);
        buttons[10].text.setPosition(650 - buttons[10].text.getGlobalBounds().width/2, 1);
        buttons[10].text.setFillColor(sf::Color::White);
        buttons[10].grid.setSize(sf::Vector2f(150, 35));
        buttons[10].grid.setPosition(575, 2);

        buttons[11].text.setString("Reface");
        buttons[11].text.setFont(font);
        buttons[11].text.setCharacterSize(30);
        buttons[11].text.setPosition(800 - buttons[11].text.getGlobalBounds().width/2, 1);
        buttons[11].text.setFillColor(sf::Color::White);
        buttons[11].grid.setSize(sf::Vector2f(150, 35));
        buttons[11].grid.setPosition(725, 2);

        buttons[12].text.setString("Editeaza");
        buttons[12].text.setFont(font);
        buttons[12].text.setCharacterSize(30);
        buttons[12].text.setPosition(950 - buttons[12].text.getGlobalBounds().width/2, 1);
        buttons[12].text.setFillColor(sf::Color::White);
        buttons[12].grid.setSize(sf::Vector2f(150, 35));
        buttons[12].grid.setPosition(875, 2);

        buttons[13].text.setString("Sterge");
        buttons[13].text.setFont(font);
        buttons[13].text.setCharacterSize(30);
        buttons[13].text.setPosition(1100 - buttons[13].text.getGlobalBounds().width/2, 1);
        buttons[13].text.setFillColor(sf::Color::White);
        buttons[13].grid.setSize(sf::Vector2f(150, 35));
        buttons[13].grid.setPosition(1025, 2);

        buttons[14].grid.setSize(sf::Vector2f(150, 70));
        buttons[14].grid.setPosition(W - 152, H/2 - 350);

        buttons[15].grid.setSize(sf::Vector2f(150, 70));
        buttons[15].grid.setPosition(W - 152, H/2 - 280);

        buttons[16].grid.setSize(sf::Vector2f(150, 70));
        buttons[16].grid.setPosition(W - 152, H/2 - 210);

        buttons[17].grid.setSize(sf::Vector2f(150, 70));
        buttons[17].grid.setPosition(W - 152, H/2 - 140);

        buttons[18].grid.setSize(sf::Vector2f(150, 70));
        buttons[18].grid.setPosition(W - 152, H/2 - 70);

        buttons[19].grid.setSize(sf::Vector2f(150, 70));
        buttons[19].grid.setPosition(W - 152, H/2 - 0);

        buttons[20].grid.setSize(sf::Vector2f(150, 70));
        buttons[20].grid.setPosition(W - 152, H/2 + 70);

        buttons[21].grid.setSize(sf::Vector2f(150, 70));
        buttons[21].grid.setPosition(W - 152, H/2 + 140);

        buttons[22].grid.setSize(sf::Vector2f(150, 70));
        buttons[22].grid.setPosition(W - 152, H/2 + 210);

        buttons[23].grid.setSize(sf::Vector2f(150, 90));
        buttons[23].grid.setPosition(W - 152, H/2 + 280);

        buttons[24].text.setString("  Resetare !  ");
        buttons[24].text.setFont(font);
        buttons[24].text.setCharacterSize(47);
        buttons[24].text.setPosition(100 - buttons[24].text.getGlobalBounds().width/2, H/2 + 300);
        buttons[24].text.setFillColor(sf::Color::White);
        buttons[24].grid.setSize(sf::Vector2f(200, 100));
        buttons[24].grid.setPosition(1,H/2 + 285);

    };
    void updateGraphicsPos()
    {

        unsigned int sizeBarButton = (W - buttons[1].text.getGlobalBounds().width - 17)/5;
        buttons[0].text.setPosition(W*0.25, H / 2);
        buttons[2].text.setPosition(W * 0.5, H /2);
        buttons[3].text.setPosition(W *0.75 , H / 2);
        buttons[4].text.setPosition(W / 2, H / 3 + 225 * (0.5 + CoeficientMarimeNouaH));
        buttons[5].text.setPosition(100 - buttons[5].text.getGlobalBounds().width/2, 105);
        buttons[6].text.setPosition(100 - buttons[6].text.getGlobalBounds().width/2, 155);
        buttons[7].text.setPosition(100 - buttons[7].text.getGlobalBounds().width/2, 205);
        buttons[8].text.setPosition(100 - buttons[8].text.getGlobalBounds().width/2, 255);
        buttons[9].text.setPosition(100 - buttons[9].text.getGlobalBounds().width/2, 305);
        buttons[10].text.setPosition(650 - buttons[10].text.getGlobalBounds().width/2, 1);
        buttons[11].text.setPosition(800 - buttons[11].text.getGlobalBounds().width/2, 1);
        buttons[12].text.setPosition(950 - buttons[12].text.getGlobalBounds().width/2, 1);
        buttons[13].text.setPosition(1100 - buttons[13].text.getGlobalBounds().width/2, 1);
        buttons[24].text.setPosition(100 - buttons[24].text.getGlobalBounds().width/2, H/2 + 300);

        buttons[0].grid.setSize(sf::Vector2f(buttons[0].text.getGlobalBounds().width + 20, buttons[0].text.getGlobalBounds().height + 17));
        buttons[0].grid.setPosition(buttons[0].text.getGlobalBounds().left - 10, buttons[0].text.getGlobalBounds().top - 10);
        buttons[2].grid.setSize(sf::Vector2f(buttons[2].text.getGlobalBounds().width + 20, buttons[2].text.getGlobalBounds().height + 17));
        buttons[2].grid.setPosition(buttons[2].text.getGlobalBounds().left - 10, buttons[2].text.getGlobalBounds().top - 10);
        buttons[3].grid.setSize(sf::Vector2f(buttons[3].text.getGlobalBounds().width + 20, buttons[3].text.getGlobalBounds().height + 17));
        buttons[3].grid.setPosition(buttons[3].text.getGlobalBounds().left - 10, buttons[3].text.getGlobalBounds().top - 10);
        buttons[4].grid.setSize(sf::Vector2f(buttons[4].text.getGlobalBounds().width + 20, buttons[4].text.getGlobalBounds().height + 17));
        buttons[4].grid.setPosition(buttons[4].text.getGlobalBounds().left - 10, buttons[4].text.getGlobalBounds().top - 10);
        buttons[5].grid.setSize(sf::Vector2f(200, 50));
        buttons[5].grid.setPosition(1,100);
        buttons[6].grid.setSize(sf::Vector2f(200, 50));
        buttons[6].grid.setPosition(1,150);
        buttons[7].grid.setSize(sf::Vector2f(200, 50));
        buttons[7].grid.setPosition(1,200);
        buttons[8].grid.setSize(sf::Vector2f(200, 50));
        buttons[8].grid.setPosition(1,250);
        buttons[9].grid.setSize(sf::Vector2f(200, 50));
        buttons[9].grid.setPosition(1,300);
        buttons[10].grid.setSize(sf::Vector2f(150, 35));
        buttons[10].grid.setPosition(575, 2);
        buttons[11].grid.setSize(sf::Vector2f(150, 35));
        buttons[11].grid.setPosition(725, 2);
        buttons[12].grid.setSize(sf::Vector2f(150, 35));
        buttons[12].grid.setPosition(875, 2);
        buttons[13].grid.setSize(sf::Vector2f(150, 35));
        buttons[13].grid.setPosition(1025, 2);
        buttons[14].grid.setPosition(W - 152, H/2 - 350);
        buttons[15].grid.setPosition(W - 152, H/2 - 280);
        buttons[16].grid.setPosition(W - 152, H/2 - 210);
        buttons[17].grid.setPosition(W - 152, H/2 - 140);
        buttons[18].grid.setPosition(W - 152, H/2 -70);
        buttons[19].grid.setPosition(W - 152, H/2 - 0);
        buttons[20].grid.setPosition(W - 152, H/2 + 70);
        buttons[21].grid.setPosition(W - 152, H/2 + 140);
        buttons[22].grid.setPosition(W - 152, H/2 + 210);
        buttons[23].grid.setPosition(W - 152, H/2 + 280);
        buttons[24].grid.setSize(sf::Vector2f(200, 100));
        buttons[24].grid.setPosition(1,H/2 + 300);
    };
};

int main()
{

    FILE *fileToRead, *fileToWrite;


    ///FOR SMOOTH SHAPES
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    W = sf::VideoMode::getDesktopMode().width - 100;
    H = sf::VideoMode::getDesktopMode().height - 100 ;

    CoeficientMarimeNouaW = double(W/1920.0);
    CoeficientMarimeNouaH = double(H/1017.0);
    double cpyCoefW = CoeficientMarimeNouaW;
    double cpyCoefH = CoeficientMarimeNouaH;
    int cpyW = W;
    int cpyH = H;

    initializeComponentTypes();
    sf::RenderWindow window(sf::VideoMode(W, H), "Electron");//  sf::Style::Default, settings);
    sf::Text title;
    sf::Font font;

    CircuitStructure Circuit;

    font.loadFromFile("Sweet Saturday.ttf");
    Menu menu(font);

    sf::Texture bgImageTexture;
    bgImageTexture.loadFromFile("bg.jpg");

    sf::Sprite bgImage(bgImageTexture);
    bgImage.setScale(CoeficientMarimeNouaW, CoeficientMarimeNouaH);

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
    SliderDesign rotationSlider(W - 250, 50, 0);
    rotationSlider.create(0, 360);

    SliderDesign scaleSlider(W - 250, 100, 0);
    scaleSlider.create(1, 5);
    scaleSlider.setSliderValue(5);

    int latestScaleSliderValue = scaleSlider.getSliderValue();
    float latestRotationSliderValue = rotationSlider.getSliderValue()/5.0f;


    TextModal help(W, H, font, "Ajutor");
    help.setString("Inapoi     	     intoarcere la pagina principala\nSalveaza       salveaza modificarile facute în acelasi fisier de proiect\nSalveaza ca     salveaza proiectul intr-un alt fisier\nDeschide 	    deschide un proiect existent\nComenzi         afiseaza comenzile specifice\n                          componentelor\nUndo 		     va anula ultima operatie efectuata\nRedo 		     va anula ultimul Undo\nEditeaza 		 deschide o fereastra unde pot fi modificati parametrii\n                        componentelor\nStergere 		 sterge o componenta sau o conexiune\nFirst Slider   roteste componenta selectata\nSecond Slider  mareste/micsoreaza componenta selectata");
    bool addResistors=false;

    for(int i=0; i<=9; i++)
    {
        ToDisplayComponents[i].tipComponent = i;
        ToDisplayComponents[i].ColtStangaSus.x = W - 73;
        if(i==9)
            ToDisplayComponents[i].ColtStangaSus.y = H / 2 - 350 + i * 70 + 45;
        else
            ToDisplayComponents[i].ColtStangaSus.y = H / 2 - 350 + i * 70 + 35;
        ToDisplayComponents[i].read();
    }

    sf::RectangleShape workBench({500, 500});
    workBench.setPosition({250,150});
    workBench.setFillColor(sf::Color::Transparent);
    workBench.setOutlineColor(sf::Color(120, 255, 0));
    workBench.setOutlineThickness(-4);
    while (window.isOpen())
    {
        workBench.setSize({W-450, H-200});
        window.clear();
        window.draw(workBench);

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
                    for (int i = 0; i <= 24; i++)
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

                            if(i==2 && renderPattern == -1)
                            {
                                Circuit.openFile(caleCurentaCatreFisier,renderPattern);
                                renderPattern=0;
                            }
                            if(i == 4 && renderPattern == -1)
                                exit(0);
                            if(renderPattern == -1 && i != 1)
                            {
                                if(i == 3)
                                 std::cout<<"pressed"<<std::endl;

                                renderPattern = i;
                                break;
                            }
                            if (i == 1)
                            {
                                middleButtonsStatus = false;
                                renderPattern=-1;
                            }
                            ///Bug corectat!
                            if(i==7 && renderPattern==0)
                            {
                                Circuit.openFile(caleCurentaCatreFisier,renderPattern);
                            }
                            if(i==5 && renderPattern == 0)
                            {
                              Circuit.saveFileAs(caleCurentaCatreFisier);
                            }
                            if(i==6 && renderPattern == 0)
                            {
                                Circuit.saveFileAs(caleCurentaCatreFisier);
                            }
                            if(i==8 && renderPattern == 0)
                            {
                                if(middleButtonsStatus == false)
                                    middleButtonsStatus = true;
                                else
                                    middleButtonsStatus = false;
                            }
                            if(i == 9 && renderPattern == 0)
                            {
                                help.open();
                            }

                            if(i == 10&& renderPattern == 0 && middleButtonsStatus == true)
                            {
                                Circuit.undoAction();
                            }

                            if(i == 11&& renderPattern == 0 && middleButtonsStatus == true)
                            {
                                Circuit.refaActiunea();
                            }

                            if(i == 12&& renderPattern == 0 && middleButtonsStatus == true)
                            {
                                if(Circuit.currentSelectedComponent!=-1)
                                {
                                    Circuit.toEditComponentId=Circuit.currentSelectedComponent;
                                    toAddComponentType=-1;
                                    Circuit.openModal();
                                }
                            }

                            if(i==13 && middleButtonsStatus == true)
                            {
                                Circuit.deleteElement();
                            }

                             if(i==24 && renderPattern == 0)
                             {
                                 Circuit.reset();
                                 std::cout << "Am facut un reset\n";
                             }

                            if(i>=14 && renderPattern == 0 && i!=24)
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

                if(W < 1200)
                    W = 1200;
                if(H < 880)
                    H = 880;

                Circuit.updateModalPos(W/2 - 200, H/3);
                help.updateGraphicsPos(W, H);
                rotationSlider.updateSliderPos(W -10, 80);
                rotationSlider.setSliderValue(rotationSlider.getSliderValue());
                scaleSlider.updateSliderPos(W - 10, 130);
                scaleSlider.setSliderValue(scaleSlider.getSliderValue()/1.0f);

                CoeficientMarimeNouaW = double(W/1920.0);
                CoeficientMarimeNouaH = double(H/1017.0);

                sf::Vector2u newSize;

                newSize.x = W;
                newSize.y = H;
                window.setSize(newSize);
                bgImage.setScale(CoeficientMarimeNouaW, CoeficientMarimeNouaH);
                menu.updateGraphicsPos();

                for(int i=0; i<=9; i++)
                {
                    ToDisplayComponents[i].ColtStangaSus.x = W - 73;
                    if(i==9)
                        ToDisplayComponents[i].ColtStangaSus.y=H/2-350+i*70+45;
                    else
                        ToDisplayComponents[i].ColtStangaSus.y=H/2-350+i*70+35;
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
                else menu.buttons[i].afiseazaButon(window,false);
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
            else menu.buttons[1].afiseazaButon(window,false);
            for(int i = 5; i < 10; i++)
                if (menu.buttons[i].isOn(mousePos.x, mousePos.y))
                {
                    menu.buttons[i].displayHoveredButton(window);
                    isOnAButton=true;
                }
                else menu.buttons[i].afiseazaButon(window,i-14==toAddComponentType);
            if(middleButtonsStatus == true)
                for(int i = 10; i <= 13; i++)
                    if (menu.buttons[i].isOn(mousePos.x, mousePos.y))
                    {
                        menu.buttons[i].displayHoveredButton(window);
                        isOnAButton=true;
                    }
                    else menu.buttons[i].afiseazaButon(window,i-14==toAddComponentType);
            for(int i = 14; i<=24; i++)
                if (menu.buttons[i].isOn(mousePos.x, mousePos.y))
                {
                    menu.buttons[i].displayHoveredButton(window);
                    isOnAButton=true;
                }
                else menu.buttons[i].afiseazaButon(window,i-14==toAddComponentType);
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

            if(scaleSlider.getSliderValue()/5.0f != latestScaleSliderValue&&scaleSlider.isActivated==true)
            {
                float scaleAt=scaleSlider.getSliderValue()/5.0f;
                Circuit.scaleSelectedComponent(scaleAt);
            }
            latestScaleSliderValue = scaleSlider.getSliderValue()/5.0f;
            help.draw(window);
            Circuit.drawModal(window);

        }

          if (renderPattern == 2)
        {
            title.setString("Proiectul Tau");
            title.setPosition(W / 2 - title.getGlobalBounds().width / 2, H / 8);

            window.draw(title);
            if (menu.buttons[1].isOn(mousePos.x, mousePos.y))
                menu.buttons[1].displayHoveredButton(window);
            else menu.buttons[1].afiseazaButon(window,false);
        }

        if (renderPattern == 3)
        {

            title.setString("Informatii legate de elemente");
            title.setPosition(W / 2 - title.getGlobalBounds().width / 2, 20);
            infoImage[0].loadFromFile("electrical_cell.jpg");
            infoImages[0].setTexture(infoImage[0]);
            infoImages[0].setPosition(100, 200);
            infoImages[0].setScale(0.3, 0.3);
            info[0].setPosition(cpyW/6, 200);
            info[0].setString("O celula electrica este o sursa de alimentare pentru un circuit, \nlasand curentul sa curga de la borna pozitiva \ndin jurul circuitului la borna negativa. Celula creeaza o diferenta \nde potential in sine prin furnizarea de energie sarcinilor.");


            infoImage[1].loadFromFile("resistor.png");
            infoImages[1].setTexture(infoImage[1]);
            infoImages[1].setPosition(100, 325);
            infoImages[1].setScale(0.064, 0.075);
            info[1].setPosition(cpyW/6, 325);
            info[1].setString("Un rezistor este o componenta care limiteaza fluxul de curent \nintr-un circuit. Tensiunea V pe rezistor \neste direct proportionala cu curentul I,I printr-un rezistor.");


            infoImage[2].loadFromFile("bulb.png");
            infoImages[2].setTexture(infoImage[2]);
            infoImages[2].setPosition(100, 430);
            infoImages[2].setScale(0.38, 0.38);
            info[2].setPosition(cpyW/6, 450);
            info[2].setString("Un bec este o componenta care transforma energia electrica in\nenergie luminoasa. Luminozitatea becului depinde de puterea acestuia \nP, care are unitatile de wati, W.");


            infoImage[3].loadFromFile("diode.png");
            infoImages[3].setTexture(infoImage[3]);
            infoImages[3].setPosition(100, 575);
            infoImages[3].setScale(0.47, 0.38);
            info[3].setPosition(cpyW/6, 575);
            info[3].setString("O dioda ideala este o componenta care permite curent doar intr-o\ndirectie. Acest lucru se datoreaza faptului ca dioda ideala are un \nrezistenta infinita in sens invers si \nrezistenta zero in directia inainte.");


            infoImage[4].loadFromFile("ammeter.jpg");
            infoImages[4].setTexture(infoImage[4]);
            infoImages[4].setPosition(100, 700);
            infoImages[4].setScale(0.485, 0.5);
            info[4].setPosition(cpyW/6, 700);
            info[4].setString("Un ampermetru este un dispozitiv care masoara curentul care curge\nintre capetele sale. Curentul este viteza de curgere a sarcinii\n si se masoara in amperi cu simbolul A.");


            infoImage[5].loadFromFile("voltmeter.png");
            infoImages[5].setTexture(infoImage[5]);
            infoImages[5].setPosition(cpyW/3*2 - 200, 200);
            infoImages[5].setScale(0.30, 0.3);
            info[5].setPosition(cpyW/3*2, 200);
            info[5].setString("Un voltmetru este un dispozitiv care masoara potentialul \ndiferenta dintre capetele sale. Diferenta potentiala este adesea\n numita tensiune si se masoara in volti cu simbolul V.");


            infoImage[6].loadFromFile("capacitor.jpg");
            infoImages[6].setTexture(infoImage[6]);
            infoImages[6].setPosition(cpyW/3*2 - 200, 325);
            infoImages[6].setScale(0.79, 0.53);
            info[6].setPosition(cpyW/3*2, 325);
            info[6].setString("Un condensator este o componenta care consta din doua \nplaci conductoare separate printr-un izolator. Este folosit pentru a \nstoca temporar sarcina electrica si energie.");


            infoImage[7].loadFromFile("transistor.png");
            infoImages[7].setTexture(infoImage[7]);
            infoImages[7].setPosition(cpyW/3*2 - 200, 450);
            infoImages[7].setScale(0.383, 0.3);
            info[7].setPosition(cpyW/3*2, 450);
            info[7].setString("Un tranzistor actioneaza ca un comutator sau ca un amplificator\n in circuitele electrice. Cei trei pini sunt colectorul C, baza B si emitatorul E. \nCand exista o tensiune zero intre baza si masa, tranzistorul nu permite \nniciunui curent sa curga de la pinul C la pinul E.");


            infoImage[8].loadFromFile("fuse.png");
            infoImages[8].setTexture(infoImage[8]);
            infoImages[8].setPosition(cpyW/3*2 - 200, 625);
            infoImages[8].setScale(0.82, 0.82);
            info[8].setPosition(cpyW/3*2, 625);
            info[8].setString("O siguranta este un dispozitiv care permite curentului sa circule \nin timp ce acesta este sub o anumita valoare, care depinde de \nvaloarea nominala a sigurantei. Cand curentul depaseste \naceasta valoare, siguranta se va topi sau se va rupe, ceea ce \nintrerupe circuitul si opreste complet curgerea curentului.");

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
            else menu.buttons[1].afiseazaButon(window,false);
        }

        window.display();

    }

    return 0;
}


