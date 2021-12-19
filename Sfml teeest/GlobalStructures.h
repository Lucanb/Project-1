#include <bits/stdc++.h>

//HEADER FILES
#include "GlobalVariables.h"
#include <SFML/Graphics.hpp>

using namespace std;

struct Point
{
    float x, y;
    float initialX, initialY;
    float scale=1;
    int rotationAngle=0;
    bool hasBeenRotated=false;
    bool hasBeenScaled=false;

    bool isConnected=false;

    void readPoint(char str[MAX_ROW_SIZE],int rowIndex)
    {
        char *pointValue=strtok(str," ");
        x=-1;
        y=-1;
        while(pointValue)
        {
            if(x==-1)
            {
                x=atoi(pointValue);
            }
            else if(y==-1)
                y=atoi(pointValue);
            else
            {
                cout<<"For the point declared on line "<<rowIndex+1<<" an extra value '"<<pointValue<<"' has been introduced. Please follow the component file structure example located in the exampleComponent.txt file.";
                exit(1);
            }
            pointValue=strtok(NULL," ");
        }

    }

    void rotatePoint(int ang)
    {
        if(hasBeenRotated==false&&hasBeenScaled==false)
            initialX=x,initialY=y;
        rotationAngle=ang;
        hasBeenRotated=true;
        float s=sin(ang*PI/180.0);
        float c=cos(ang*PI/180.0);
        Point fp;
        fp.x=(initialX*scale)*c-(initialY*scale)*s;
        fp.y=(initialX*scale)*s+(initialY*scale)*c;
        x=fp.x;
        y=fp.y;
    }
    void scalePoint(float scaledAt)
    {
        if(hasBeenRotated==false&&hasBeenScaled==false)
            initialX=x,initialY=y;
        hasBeenScaled=true;
        scale=scaledAt;
        x=initialX*scale;
        y=initialY*scale;
        if(hasBeenRotated==true)
        {
            float s=sin(rotationAngle*PI/180.0);
            float c=cos(rotationAngle*PI/180.0);
            Point fp;
            fp.x=(x)*c-(y)*s;
            fp.y=(x)*s+(y)*c;
            x=fp.x;
            y=fp.y;
        }
    }

    void draw(Point origin,sf::RenderWindow &win)
    {
        sf::CircleShape circle(POINT_CIRCLE_RADIUS);
        circle.setPosition(sf::Vector2f(origin.x+x-POINT_CIRCLE_RADIUS,origin.y+y-POINT_CIRCLE_RADIUS));
        circle.setFillColor(sf::Color(0,0,0));
        circle.setOutlineColor(sf::Color(255,255,255));
        circle.setOutlineThickness(1);

        win.draw(circle);
    }

    bool mouseOn(Point origin,int mouseX, int mouseY)
    {
        sf::CircleShape circle(POINT_CIRCLE_RADIUS);
        circle.setPosition(sf::Vector2f(origin.x+x-POINT_CIRCLE_RADIUS,origin.y+y-POINT_CIRCLE_RADIUS));
        circle.setFillColor(sf::Color(0,0,0));
        circle.setOutlineColor(sf::Color(0,0,0));
        circle.setOutlineThickness(1);
        sf::FloatRect containingRect=circle.getGlobalBounds();
        if(containingRect.contains(sf::Vector2f(mouseX,mouseY)))
            return true;
        return false;
    }


    void open(FILE *file)
    {
        fread(&x, sizeof(float),1,file);
        fread(&y, sizeof(float),1,file);
        fread(&initialX, sizeof(float),1,file);
        fread(&initialY, sizeof(float),1,file);
        fread(&scale, sizeof(float),1,file);
        fread(&rotationAngle, sizeof(int),1,file);
        fread(&hasBeenScaled, sizeof(bool),1,file);
        fread(&hasBeenRotated, sizeof(bool),1,file);

    }

    void save(FILE *file)
    {
        fwrite(&x, sizeof(float),1,file);
        fwrite(&y, sizeof(float),1,file);
        fwrite(&initialX, sizeof(float),1,file);
        fwrite(&initialY, sizeof(float),1,file);
        fwrite(&scale, sizeof(float),1,file);
        fwrite(&rotationAngle, sizeof(int),1,file);
        fwrite(&hasBeenScaled, sizeof(bool),1,file);
        fwrite(&hasBeenRotated, sizeof(bool),1,file);

    }

};


struct LetterSubComponent
{
    Point topLeftCorner;
    char letter[1];
    sf::Font font;

    bool isSmall=false;


    void initializeFont()
    {
        font.loadFromFile("OpenSans-Regular.ttf");
    }
    void read(char str[MAX_ROW_SIZE], int rowIndex)
    {
        topLeftCorner.x=-1;
        topLeftCorner.y=-1;
        letter[0]='0';
        //a Letter Component needs a letter value, and the coordinates of the top left corner, data needed for the SFML Circle class
        char *circleValue=strtok(str," ");
        while(circleValue)
        {
            if(letter[0]=='0')
            {
                strcpy(letter,circleValue);
            }
            else if(topLeftCorner.x==-1)
            {
                topLeftCorner.x=atoi(circleValue);
            }
            else if(topLeftCorner.y==-1)
            {
                topLeftCorner.y=atoi(circleValue);
            }
            else
            {
                cout<<"For the Letter subcomponent declared on line "<<rowIndex+1<<" an extra value '"<<circleValue<<"' has been introduced. Please follow the component file structure example located in the exampleComponent.txt file.";
                exit(1);
            }
            circleValue=strtok(NULL," ");
        }
    }

    void draw(Point origin,int rotatedAt, float scaledAt, sf::RenderWindow &win)
    {
        sf::Text letterComponent;
        letterComponent.setPosition(topLeftCorner.x+origin.x,topLeftCorner.y+origin.y);
        letterComponent.rotate(rotatedAt);
        if(isSmall)
            letterComponent.setCharacterSize(12*scaledAt);
        else
            letterComponent.setCharacterSize(20*scaledAt);
        letterComponent.setString(letter);
        letterComponent.setColor(sf::Color::White);
        letterComponent.setFont(font);
        win.draw(letterComponent);
    }

    void open(FILE *file)
    {
        fread(&letter, sizeof(char),1,file);
        fread(&isSmall, sizeof(bool),1,file);
        topLeftCorner.open(file);
    }

    void save(FILE *file)
    {
        fwrite(&letter, sizeof(char),1,file);
        fwrite(&isSmall, sizeof(bool),1,file);
        topLeftCorner.save(file);
    }
};

struct CircleSubComponent
{
    Point topLeftCorner;
    int r=-1;

    void read(char str[MAX_ROW_SIZE], int rowIndex)
    {
        r=-1;
        topLeftCorner.x=-1;
        topLeftCorner.y=-1;

        //a Circled needs a radius value, and the coordinates of the top left corner, data needed for the SFML Circle class
        char *circleValue=strtok(str," ");
        while(circleValue)
        {
            if(r==-1)
            {
                r=atoi(circleValue);
            }
            else if(topLeftCorner.x==-1)
            {
                topLeftCorner.x=atoi(circleValue);
            }
            else if(topLeftCorner.y==-1)
            {
                topLeftCorner.y=atoi(circleValue);
            }
            else
            {
                cout<<"For the Circle subcomponent declared on line "<<rowIndex+1<<" an extra value '"<<circleValue<<"' has been introduced. Please follow the component file structure example located in the exampleComponent.txt file.";
                exit(1);
            }
            circleValue=strtok(NULL," ");
        }
    }

    void draw(Point origin,int rotatedAt, float scaledAt, sf::RenderWindow &win)
    {
        sf::CircleShape circle(r);
        circle.setPosition(topLeftCorner.x+origin.x,topLeftCorner.y+origin.y);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color(255,255,255));
        circle.setOutlineThickness(1);
        circle.rotate(rotatedAt);
        circle.setScale(sf::Vector2f(scaledAt,scaledAt));
        win.draw(circle);
    }

    void open(FILE *file)
    {
        fread(&r, sizeof(int),1,file);
        topLeftCorner.open(file);

    }

    void save(FILE *file)
    {
        fwrite(&r, sizeof(int),1,file);
        topLeftCorner.save(file);
    }
};




struct RectangleSubComponent
{
    int width, height;
    Point topLeftCorner;

    void read(char str[MAX_ROW_SIZE], int rowIndex)
    {
        width=-1;
        height=-1;
        topLeftCorner.x=-1;
        topLeftCorner.y=-1;

        //a rectangle has a width, height and the coordinates of the left top corner, data needed for the SFML Rectangle class

        char *rectangleValue=strtok(str," ");
        while(rectangleValue)
        {
            if(width==-1)
            {
                width=atoi(rectangleValue);
            }
            else if(height==-1)
            {
                height=atoi(rectangleValue);
            }
            else if(topLeftCorner.x==-1)
            {
                topLeftCorner.x=atoi(rectangleValue);
            }
            else if(topLeftCorner.y==-1)
            {
                topLeftCorner.y=atoi(rectangleValue);
            }
            else
            {
                cout<<"For the Rectangle subcomponent declared on line "<<rowIndex+1<<" an extra value '"<<rectangleValue<<"' has been introduced. Please follow the component file structure example located in the exampleComponent.txt file.";
                exit(1);
            }
            rectangleValue=strtok(NULL," ");
        }
    }

    void draw(Point origin,int rotatedAt,float scaledAt, sf::RenderWindow &win)
    {
        sf::RectangleShape rectangle(sf::Vector2f(width,height));
        rectangle.setPosition(topLeftCorner.x+origin.x,topLeftCorner.y+origin.y);
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineColor(sf::Color(255,255,255));
        rectangle.setOutlineThickness(3);
        rectangle.setScale(sf::Vector2f(scaledAt,scaledAt));
        rectangle.rotate(rotatedAt);
        win.draw(rectangle);
    }

    void open(FILE *file)
    {
        fread(&width, sizeof(int),1,file);
        fread(&height, sizeof(int),1,file);
        topLeftCorner.open(file);

    }

    void save(FILE *file)
    {
        fwrite(&width, sizeof(int),1,file);
        fwrite(&height, sizeof(int),1,file);
        topLeftCorner.save(file);
    }
};




struct LineSubComponent
{
    Point p1;
    Point p2;

    void read(char str[MAX_ROW_SIZE], int rowIndex)
    {
        p1.x=-1;
        p1.y=-1;
        p2.x=-1;
        p2.y=-1;
        char *pointValue=strtok(str," ");
        while(pointValue)
        {
            if(p1.x==-1)
            {
                p1.x=atoi(pointValue);
            }
            else if(p1.y==-1)
            {
                p1.y=atoi(pointValue);
            }
            else if(p2.x==-1)
            {
                p2.x=atoi(pointValue);
            }
            else if(p2.y==-1)
            {
                p2.y=atoi(pointValue);
            }
            else
            {
                cout<<"For the Line subcomponent declared on line "<<rowIndex+1<<" an extra value '"<<pointValue<<"' has been introduced. Please follow the component file structure example located in the exampleComponent.txt file.";
                exit(1);
            }
            pointValue=strtok(NULL," ");
        }
    }

    void draw(Point origin, sf::RenderWindow &win)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(p1.x +origin.x, p1.y+origin.y)),
            sf::Vertex(sf::Vector2f(p2.x +origin.x, p2.y+origin.y))
        };

        win.draw(line, 2, sf::Lines);
    }

    void open(FILE *file)
    {
        p1.open(file);
        p2.open(file);
    }

    void save(FILE *file)
    {
        p1.save(file);
        p2.save(file);
    }

};




struct ConnectionSubComponent
{
    int outputComponentId=-1, inputComponentId=-1;
    int componentOutputPointIndex=-1,componentInputPointIndex=-1;
    Point startPoint,endPoint;
    bool isDeleted=false;

    void draw(sf::RenderWindow &win)
    {
        if(isDeleted==false)
        {
            sf::Vertex line1[] =
            {
                sf::Vertex(sf::Vector2f(startPoint.x, startPoint.y)),
                sf::Vertex(sf::Vector2f(startPoint.x+(endPoint.x-startPoint.x)/2, startPoint.y))
            };
            sf::Vertex line2[] =
            {
                sf::Vertex(sf::Vector2f(startPoint.x+(endPoint.x-startPoint.x)/2, startPoint.y)),
                sf::Vertex(sf::Vector2f(startPoint.x+(endPoint.x-startPoint.x)/2, endPoint.y))
            };
            sf::Vertex line3[] =
            {
                sf::Vertex(sf::Vector2f(startPoint.x+(endPoint.x-startPoint.x)/2, endPoint.y)),
                sf::Vertex(sf::Vector2f(endPoint.x, endPoint.y))
            };

            win.draw(line1, 2, sf::Lines);
            win.draw(line2, 2, sf::Lines);
            win.draw(line3, 2, sf::Lines);
        }
    }

    void open(FILE *file)
    {
        fread(&outputComponentId, sizeof(int),1,file);
        fread(&inputComponentId, sizeof(int),1,file);
        fread(&componentOutputPointIndex, sizeof(int),1,file);
        fread(&componentInputPointIndex, sizeof(int),1,file);
        startPoint.open(file);
        startPoint.open(file);

    }

    void save(FILE *file)
    {
        fwrite(&outputComponentId, sizeof(int),1,file);
        fwrite(&inputComponentId, sizeof(int),1,file);
        fwrite(&componentOutputPointIndex, sizeof(int),1,file);
        fwrite(&componentInputPointIndex, sizeof(int),1,file);
        startPoint.save(file);
        startPoint.save(file);

    }
};

struct Action
{
    string type;
    Point previousComponentTopLeftCorner;
    float previousScaledAt;
    int previousRotatedAt;


    Point usedComponentNewTopLeftCorner;
    float scaledAt=1;
    int rotatedAt=0;
    int oldComponentId=-1;
    int oldPointIndex=-1;
    int pointIndex=-1;
    int connectionId=-1;
    int componentId=-1;
};

