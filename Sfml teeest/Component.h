#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

//HEADER FILES
#include "GlobalStructures.h"
#include "SliderSFML.cpp"
#include "Textbox.h"
#include <windows.h>
using namespace std;

struct Component
{
    string filePath;
    int gridWidth, gridHeight;

    int componentType;

    int id;

    int rotatedAt=0;

    float scaledAt=1;

    int inputPointsLength=0,outputPointsLength=0;

    Point topLeftCorner;

    Point inputPoints[MAX_INPUT_POINTS];
    Point outputPoints[MAX_OUTPUT_POINTS];

    int circlesLength=0;
    CircleSubComponent Circles[10];

    int rectanglesLength=0;
    RectangleSubComponent Rectangles[10];

    int linesLength=0;
    LineSubComponent Lines[10];

    int lettersLength=0;
    LetterSubComponent Letters[10];

    string name="Component";
    char name2[25];
    float R=0;
    float V=0;


    bool selected=false;

    bool isDeleted=false;

    void read()
    {
        FILE* componentFile;
        filePath=ComponentTypes[componentType].filePath;
        int rowIndex=0;
        char row[MAX_ROW_SIZE];
        int spacingRows=0;
        string currentRecursiveValues="";
        char filePathChar[150];
        strcpy(filePathChar,filePath.c_str());
        if (!(componentFile = fopen(filePathChar, "r")))
        {
            char error[150]="Error opening the component that should be located at ";
            strcat(error,filePathChar);
            strcat(error,", possible reason:");
            perror(error);
            exit(1);
        }
        while(!feof(componentFile))
        {
            if (!fgets(row,MAX_ROW_SIZE,componentFile))
            {
                perror("Error reading the component file row: ");
                exit(1);
            }
            if(rowIndex==0)
            {
                char *gridValue=strtok(row," ");
                gridWidth=-1;
                gridHeight=-1;
                while(gridValue)
                {
                    if(gridWidth==-1)
                    {
                        gridWidth=atoi(gridValue);
                    }
                    else
                        gridHeight=atoi(gridValue);
                    gridValue=strtok(NULL," ");
                }
                if(!(gridWidth!=-1&&gridHeight!=-1))
                {
                    cout<<"The componenent file structure located at "<<filePath<<" does not contain a valid grid size at line "<<rowIndex+1<<". Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                    exit(1);
                }
                else
                    rowIndex++;
            }
            else
            {
                bool wasAnyCase=false;
                switch(row[0])
                {
                case 'I':
                    currentRecursiveValues="INPUT_POINTS";
                    wasAnyCase=true;
                    break;
                case 'O':
                    currentRecursiveValues="OUTPUT_POINTS";
                    wasAnyCase=true;
                    break;
                case 'F':
                    currentRecursiveValues="SUBCOMPONENTS_FUNCTIONS";
                    wasAnyCase=true;
                    break;
                }

                if(wasAnyCase==false)
                {
                    if(row[0]=='\n'||row[0]==' ')
                    {
                        spacingRows++;
                        if(spacingRows>MAX_SPACING_ROWS)
                        {
                            cout<<"On line "<<rowIndex+1<<" an extra spacing row has been used then the maximum of "<<MAX_SPACING_ROWS<<" allowed. Delete it and try again!";
                            exit(1);
                        }
                        else
                            rowIndex++;
                    }
                    else if(currentRecursiveValues=="INPUT_POINTS")
                    {
                        spacingRows=0;
                        inputPoints[inputPointsLength].readPoint(row,rowIndex);
                        if(!(inputPoints[inputPointsLength].x!=-1&&inputPoints[inputPointsLength].y!=-1))
                        {
                            cout<<"The component file structure located at "<<filePath<<" does not contain a valid input point at line "<<rowIndex+1<<". Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                            exit(1);
                        }
                        else
                        {
                            inputPoints[inputPointsLength].x=inputPoints[inputPointsLength].x-gridWidth/2.0;
                            inputPoints[inputPointsLength].y=inputPoints[inputPointsLength].y-gridHeight/2.0;
                            inputPointsLength++;
                        }
                        rowIndex++;
                    }
                    else if(currentRecursiveValues=="OUTPUT_POINTS")
                    {
                        spacingRows=0;
                        outputPoints[outputPointsLength].readPoint(row,rowIndex);
                        if(!(outputPoints[outputPointsLength].x!=-1&&outputPoints[outputPointsLength].y!=-1))
                        {
                            cout<<"The component file structure located at "<<filePath<<" does not contain a valid output point at line "<<rowIndex+1<<". Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                            exit(1);
                        }
                        else
                        {
                            outputPoints[outputPointsLength].x=outputPoints[outputPointsLength].x-gridWidth/2.00;
                            outputPoints[outputPointsLength].y=outputPoints[outputPointsLength].y-gridHeight/2.00;
                            outputPointsLength++;
                        }
                        rowIndex++;
                    }
                    else if(currentRecursiveValues=="SUBCOMPONENTS_FUNCTIONS")
                    {
                        spacingRows=0;
                        if(row[0]=='C')
                        {
                            strcpy(row, row+1);
                            Circles[circlesLength].read(row,rowIndex);
                            if(Circles[circlesLength].r==-1)
                            {
                                cout<<"The Circle subcomponent declared on line "<<rowIndex+1<<" does not contain a valid radius. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                exit(1);
                            }
                            if(!(Circles[circlesLength].topLeftCorner.x!=-1&&Circles[circlesLength].topLeftCorner.y!=-1))
                            {
                                cout<<"The Circle subcomponent declared on line "<<rowIndex+1<<" does not contain a valid top left point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                exit(1);
                            }
                            else
                            {
                                Circles[circlesLength].topLeftCorner.x=Circles[circlesLength].topLeftCorner.x-gridWidth/2.00;
                                Circles[circlesLength].topLeftCorner.y=Circles[circlesLength].topLeftCorner.y-gridHeight/2.00;
                                circlesLength++;
                            }
                        }

                        else if(row[0]=='R')
                        {
                            strcpy(row, row+1);
                            Rectangles[rectanglesLength].read(row,rowIndex);
                            if(!(Rectangles[rectanglesLength].topLeftCorner.x!=-1&&Rectangles[rectanglesLength].topLeftCorner.y!=-1))
                            {
                                cout<<"The Rectangle subcomponent declared on line "<<rowIndex+1<< " does not contain a valid top left corner point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                exit(1);
                            }
                            else if(!(Rectangles[rectanglesLength].width!=-1&&Rectangles[rectanglesLength].height!=-1))
                            {
                                cout<<"The Rectangle subcomponent declared on line "<<rowIndex+1<< " does not contain valid width or height values. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                exit(1);
                            }
                            else
                            {
                                Rectangles[rectanglesLength].topLeftCorner.x=Rectangles[rectanglesLength].topLeftCorner.x-gridWidth/2.00;
                                Rectangles[rectanglesLength].topLeftCorner.y=Rectangles[rectanglesLength].topLeftCorner.y-gridHeight/2.00;
                                rectanglesLength++;
                            }
                        }

                        else if(row[0]=='L')
                        {
                            if(row[1]=='T')
                            {
                                strcpy(row, row+2);
                                Letters[lettersLength].read(row,rowIndex);
                                if(Letters[lettersLength].letter=="0")
                                {
                                    cout<<"The Letter subcomponent declared on line "<<rowIndex+1<<" does not contain a valid letter. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                if(!(Letters[lettersLength].topLeftCorner.x!=-1&&Letters[lettersLength].topLeftCorner.y!=-1))
                                {
                                    cout<<"The Letter subcomponent declared on line "<<rowIndex+1<<" does not contain a valid top left point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                else
                                {
                                    Letters[lettersLength].topLeftCorner.x=Letters[lettersLength].topLeftCorner.x-gridWidth/2.00;
                                    Letters[lettersLength].topLeftCorner.y=Letters[lettersLength].topLeftCorner.y-gridHeight/2.00;
                                    Letters[lettersLength].initializeFont();
                                    lettersLength++;
                                }
                            }
                            else if(row[1]=='S')
                            {
                                strcpy(row, row+2);
                                Letters[lettersLength].read(row,rowIndex);
                                Letters[lettersLength].isSmall=true;
                                if(Letters[lettersLength].letter=="0")
                                {
                                    cout<<"The Letter subcomponent declared on line "<<rowIndex+1<<" does not contain a valid letter. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                if(!(Letters[lettersLength].topLeftCorner.x!=-1&&Letters[lettersLength].topLeftCorner.y!=-1))
                                {
                                    cout<<"The Letter subcomponent declared on line "<<rowIndex+1<<" does not contain a valid top left point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                else
                                {
                                    Letters[lettersLength].topLeftCorner.x=Letters[lettersLength].topLeftCorner.x-gridWidth/2.00;
                                    Letters[lettersLength].topLeftCorner.y=Letters[lettersLength].topLeftCorner.y-gridHeight/2.00;
                                    Letters[lettersLength].initializeFont();
                                    lettersLength++;
                                }
                            }
                            else
                            {
                                strcpy(row, row+1);
                                Lines[linesLength].read(row,rowIndex);
                                if(!(Lines[linesLength].p1.x!=-1&&Lines[linesLength].p1.y!=-1))
                                {
                                    cout<<"The Line subcomponent declared on line "<<rowIndex+1<< " does not contain a valid first point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                else if(!(Lines[linesLength].p2.x!=-1&&Lines[linesLength].p2.y!=-1))
                                {
                                    cout<<"The Line subcomponent declared on line "<<rowIndex+1<< " does not contain a valid second point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                else
                                {
                                    Lines[linesLength].p1.x=Lines[linesLength].p1.x-gridWidth/2.00;
                                    Lines[linesLength].p1.y=Lines[linesLength].p1.y-gridHeight/2.00;
                                    Lines[linesLength].p2.x=Lines[linesLength].p2.x-gridWidth/2.00;
                                    Lines[linesLength].p2.y=Lines[linesLength].p2.y-gridHeight/2.00;
                                    linesLength++;
                                }
                            }
                        }
                        else
                        {

                        }
                        rowIndex++;
                    }
                    else
                    {

                    }
                }
                else
                {
                    rowIndex++;
                }
            }
        }
        fclose(componentFile);
    }

    void open(FILE *file)
    {
        fread(&gridWidth,sizeof(int),1,file);
        fread(&gridHeight,sizeof(int),1,file);
        fread(&componentType,sizeof(int),1,file);

        fread(&id,sizeof(int),1,file);

        fread(&rotatedAt,sizeof(int),1,file);
        fread(&scaledAt,sizeof(float),1,file);

        fread(&inputPointsLength,sizeof(int),1,file);
        fread(&outputPointsLength,sizeof(int),1,file);

        topLeftCorner.open(file);


        for(int i=0; i<inputPointsLength; i++)
        {
            inputPoints[i].open(file);
        }

        for(int i=0; i<outputPointsLength; i++)
        {
            outputPoints[i].open(file);
        }

        fread(&circlesLength,sizeof(int),1,file);

        for(int i=0; i<circlesLength; i++)
        {
            Circles[i].open(file);
        }

        fread(&lettersLength,sizeof(int),1,file);

        for(int i=0; i<lettersLength; i++)
        {
            Letters[i].open(file);
        }

        fread(&rectanglesLength,sizeof(int),1,file);
        for(int i=0; i<rectanglesLength; i++)
        {
            Rectangles[i].open(file);
        }

        fread(&linesLength,sizeof(int),1,file);
        for(int i=0; i<linesLength; i++)
        {
            Lines[i].open(file);
        }
        fread(&name2,sizeof(char),25,file);
        name=name2;
        fread(&R,sizeof(float),1,file);
        fread(&V,sizeof(float),1,file);
    }

    void saveComponent(FILE *file)
    {

        fwrite(&gridWidth,sizeof(int),1,file);
        fwrite(&gridHeight,sizeof(int),1,file);
        fwrite(&componentType,sizeof(int),1,file);

        fwrite(&id,sizeof(int),1,file);

        fwrite(&rotatedAt,sizeof(int),1,file);
        fwrite(&scaledAt,sizeof(float),1,file);

        fwrite(&inputPointsLength,sizeof(int),1,file);
        fwrite(&outputPointsLength,sizeof(int),1,file);

        topLeftCorner.save(file);


        for(int i=0; i<inputPointsLength; i++)
        {
            inputPoints[i].save(file);
        }

        for(int i=0; i<outputPointsLength; i++)
        {
            outputPoints[i].save(file);
        }

        fwrite(&circlesLength,sizeof(int),1,file);

        for(int i=0; i<circlesLength; i++)
        {
            Circles[i].save(file);
        }

        fwrite(&lettersLength,sizeof(int),1,file);

        for(int i=0; i<lettersLength; i++)
        {
            Letters[i].save(file);
        }

        fwrite(&rectanglesLength,sizeof(int),1,file);
        for(int i=0; i<rectanglesLength; i++)
        {
            Rectangles[i].save(file);
        }

        fwrite(&linesLength,sizeof(int),1,file);
        for(int i=0; i<linesLength; i++)
        {
            Lines[i].save(file);
        }
        strcpy(name2,name.c_str());
        fwrite(&name2,sizeof(char),25,file);
        fwrite(&R,sizeof(float),1,file);
        fwrite(&V,sizeof(float),1,file);

    }

    void rotateComponent(int ang)
    {
        rotatedAt=ang;
        for(int i=0; i<inputPointsLength; i++)
            inputPoints[i].rotatePoint(ang);
        for(int i=0; i<outputPointsLength; i++)
            outputPoints[i].rotatePoint(ang);
        for(int i=0; i<linesLength; i++)
        {
            Lines[i].p1.rotatePoint(ang);
            Lines[i].p2.rotatePoint(ang);
        }
        for(int i=0; i<circlesLength; i++)
        {
            Circles[i].topLeftCorner.rotatePoint(ang);
        }
        for(int i=0; i<lettersLength; i++)
        {
            Letters[i].topLeftCorner.rotatePoint(ang);
        }
        for(int i=0; i<rectanglesLength; i++)
        {
            Rectangles[i].topLeftCorner.rotatePoint(ang);
        }

    }

    void scaleComponent(float scale)
    {
        scaledAt=scale;
        for(int i=0; i<inputPointsLength; i++)
            inputPoints[i].scalePoint(scale);
        for(int i=0; i<outputPointsLength; i++)
            outputPoints[i].scalePoint(scale);
        for(int i=0; i<linesLength; i++)
        {
            Lines[i].p1.scalePoint(scale);
            Lines[i].p2.scalePoint(scale);
        }
        for(int i=0; i<circlesLength; i++)
        {
            Circles[i].topLeftCorner.scalePoint(scale);
        }
        for(int i=0; i<lettersLength; i++)
        {
            Letters[i].topLeftCorner.scalePoint(scale);
        }
        for(int i=0; i<rectanglesLength; i++)
        {
            Rectangles[i].topLeftCorner.scalePoint(scale);
        }
    }

    void draw(sf::RenderWindow &win)
    {
        if(isDeleted==false)
        {
            if(selected==true)
            {
                sf::RectangleShape grid(sf::Vector2f(gridWidth,gridHeight));
                grid.setPosition(topLeftCorner.x,topLeftCorner.y);
                grid.setOrigin(gridWidth/2,gridHeight/2);
                grid.setFillColor(sf::Color::Transparent);
                grid.setOutlineColor(sf::Color(245, 230, 83));
                grid.rotate(rotatedAt);
                grid.setScale(sf::Vector2f(scaledAt,scaledAt));
                grid.setOutlineThickness(2);
                win.draw(grid);
            }

            for(int i=0; i<inputPointsLength; i++)
            {
                inputPoints[i].draw(topLeftCorner,win);
            }

            for(int i=0; i<outputPointsLength; i++)
            {
                outputPoints[i].draw(topLeftCorner,win);
            }

            for(int i=0; i<circlesLength; i++)
            {
                Circles[i].draw(topLeftCorner,rotatedAt,scaledAt,win);
            }
            for(int i=0; i<lettersLength; i++)
            {
                Letters[i].draw(topLeftCorner,rotatedAt,scaledAt,win);
            }
            for(int i=0; i<rectanglesLength; i++)
            {
                Rectangles[i].draw(topLeftCorner,rotatedAt,scaledAt,win);
            }
            for(int i=0; i<linesLength; i++)
            {
                Lines[i].draw(topLeftCorner,win);
            }
        }
    }

    void initializeFont()
    {
        for(int i=0; i<lettersLength; i++)
        {
            Letters[i].initializeFont();
        }
    }

    bool mouseOn(int mouseX, int mouseY)
    {
        if(isDeleted==true)
            return false;
        sf::RectangleShape grid(sf::Vector2f(gridWidth,gridHeight));
        grid.setPosition(topLeftCorner.x,topLeftCorner.y);
        grid.setOrigin(gridWidth/2,gridHeight/2);
        grid.setFillColor(sf::Color::Transparent);
        grid.setOutlineColor(sf::Color::Transparent);
        grid.setOutlineThickness(1);
        grid.rotate(rotatedAt);
        grid.setScale(sf::Vector2f(scaledAt,scaledAt));

        sf::Vector2f topLeft = grid.getTransform().transformPoint(sf::Vector2f(0,0));
        sf::Vector2f topRight = grid.getTransform().transformPoint(sf::Vector2f(grid.getSize().x,0));
        sf::Vector2f bottomLeft = grid.getTransform().transformPoint(sf::Vector2f(0,grid.getSize().y));
        sf::Vector2f bottomRight = grid.getTransform().transformPoint(sf::Vector2f(grid.getSize().x,grid.getSize().y));

        if((topLeft.x - topRight.x) * (mouseY - topRight.y) - (mouseX - topRight.x) * (topLeft.y - topRight.y)<=0&&
                (topRight.x - bottomRight.x) * (mouseY -bottomRight.y) - (mouseX - bottomRight.x) * (topRight.y - bottomRight.y)<=0&&
                (bottomRight.x - bottomLeft.x) * (mouseY -bottomLeft.y) - (mouseX - bottomLeft.x) * (bottomRight.y - bottomLeft.y)<=0&&
                (bottomLeft.x - topLeft.x) * (mouseY -topLeft.y) - (mouseX - topLeft.x) * (bottomLeft.y - topLeft.y)<=0

          )

            //POINT INSIDE CONVEX POLYGON https://stackoverflow.com/questions/2752725/finding-whether-a-point-lies-inside-a-rectangle-or-not


            return true;
        return false;
    }

    int isOnAnyOutputPoints(int mouseX,int mouseY)
    {
        for(int i=0; i<outputPointsLength; i++)
        {
            if(outputPoints[i].mouseOn(topLeftCorner,mouseX,mouseY)==true)
            {
                return i;
            }
        }
        return -1;
    }

    int isOnAnyInputPoints(int mouseX,int mouseY)
    {
        for(int i=0; i<inputPointsLength; i++)
        {
            if(inputPoints[i].mouseOn(topLeftCorner,mouseX,mouseY)==true)
            {
                return i;
            }
        }
        return -1;
    }
};


struct CircuitStructure
{
    int componentsLength=0;
    Component Components[100];
    int connectionsLength=0;
    ConnectionSubComponent Connections[100];
    int actionsLength=0,actionIndex=-1;
    Action Actions[100];
    int currentSelectedComponent=-1;

    int currentSelectedConnection=-1;

    bool isMouseLongPressed;

    bool isInputConnectionSelected, isOutputConnectionSelected;


    float mouseLongPressXDiff,mouseLongPressYDiff;

    sf::RectangleShape modalGrid;
    sf::Text modalEditorTitle;
    sf::RectangleShape modalEdit;
    sf::Text modalEditText;
    sf::RectangleShape modalExit;
    sf::Text modalExitText;
    sf::RectangleShape modalBlur;
    Textbox modalName;
    Textbox modalRezistenta;
    Textbox modalVoltaj;

    sf::RectangleShape modalSuccessGrid;
    sf::Text modalSuccessTitle;
    sf::Text modalSuccessText;
    sf::RectangleShape modalSuccessDone;
    sf::Text modalSuccessDoneText;
    sf::RectangleShape modalSuccessExit;
    sf::Text modalSuccessExitText;
    sf::RectangleShape modalSuccessBlur;

    bool justAddedAComponent=false;
    bool isModalClosed=true;
    int isASliderSelected=0;
    bool isMessageModalClosed=true;

    int oldOutputComponentId=-1;
    int oldComponentOutputPointIndex=-1;

    int oldInputComponentId=-1;
    int oldComponentInputPointIndex=-1;

    bool isFromExistingConnection=false;
    int toEditComponentId=-1;


    void coutActions()
    {
        for(int i=4; i<actionsLength; i++)
            cout<<Actions[i].type<<" "<<Actions[i].oldComponentId<<" "<<Actions[i].componentId<<" "<<Actions[i].oldPointIndex<<" "<<Actions[i].pointIndex<<endl;
        cout<<endl;
    }
    void openCircuit(char filename[])
    {
        FILE *fileToRead;
        if ((fileToRead = fopen(filename,"rb")) == NULL)
        {
            printf("Error! opening file");
            // Program exits if the file pointer returns NULL.
            exit(1);
        }

        fread(&componentsLength, sizeof(int), 1, fileToRead);
        for(int i=0; i<componentsLength; i++)
        {
            Components[i].open(fileToRead);
        }
        fread(&connectionsLength, sizeof(int), 1, fileToRead);
        fread(&Connections, sizeof(ConnectionSubComponent), connectionsLength, fileToRead);

        fclose(fileToRead);
        initializeLetterComponentsFonts();
    }

    void saveCircuit(char filename[])
    {
        FILE *fileToWrite;
        if ((fileToWrite = fopen(filename,"wb")) == NULL)
        {
            printf("Error! opening file");
            // Program exits if the file pointer returns NULL.
            exit(1);
        }
        fwrite(&componentsLength, sizeof(int), 1, fileToWrite);
        for(int i=0; i<componentsLength; i++)
        {
            Components[i].saveComponent(fileToWrite);
        }
        fwrite(&connectionsLength, sizeof(int), 1, fileToWrite);
        fwrite(&Connections, sizeof(ConnectionSubComponent), connectionsLength, fileToWrite);

        fclose(fileToWrite);
        isMessageModalClosed=false;

    }

    void openFile(char filePath[],int &renderPattern)
    {
        char filename[ 200 ];

        OPENFILENAME ofn;
        ZeroMemory( &filename, sizeof( filename ) );
        ZeroMemory( &ofn,      sizeof( ofn ) );
        ofn.lStructSize  = sizeof( ofn );
        ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
        ofn.lpstrFilter  = "Electron Files\0*.electron\0Any File\0*.*\0";
        ofn.lpstrFile    = filename;
        ofn.nMaxFile     = MAX_PATH;
        ofn.lpstrTitle   = "Open an Electron project";
        ofn.Flags=OFN_NOCHANGEDIR;
        if (GetOpenFileNameA( &ofn ))
        {
            strcpy(filePath,filename);
            openCircuit(filename);
            initializeLetterComponentsFonts();
            renderPattern=0;
        }
        else
            renderPattern=-1;
    }

    void saveFileAs(char filePath[])
    {
        OPENFILENAME saveFileDialog;
        char szSaveFileName[MAX_PATH];
        strcpy(szSaveFileName,"test.electron");
        ZeroMemory(&saveFileDialog, sizeof(saveFileDialog));
        saveFileDialog.lStructSize= sizeof(saveFileDialog);
        saveFileDialog.hwndOwner = NULL;
        saveFileDialog.lpstrFilter = "Electron Files\0*.electron\0Any File\0*.*\0";
        saveFileDialog.lpstrFile = szSaveFileName;
        saveFileDialog.lpstrTitle   = "Save an Electron project as";
        saveFileDialog.nMaxFile = MAX_PATH;
        saveFileDialog.Flags=OFN_NOCHANGEDIR;

        if(GetSaveFileName(&saveFileDialog))
        {
            saveCircuit(szSaveFileName);
        }
    }

    void addElement(int cType,float x,float y)
    {
        Components[componentsLength].componentType=cType;
        Components[componentsLength].id=componentsLength;
        Components[componentsLength].topLeftCorner.x=x;
        Components[componentsLength].topLeftCorner.y=y;
        Components[componentsLength].read();
        currentSelectedComponent=componentsLength;
        Components[componentsLength].selected=true;

        Actions[actionIndex+1].type="COMPONENT_ADDED";
        Actions[actionIndex+1].componentId=componentsLength;
        actionIndex++;
        clearExtraComponentsOrConnections(actionIndex);
        justAddedAComponent=true;

        componentsLength++;

    }

    void deleteElement()
    {
        if(currentSelectedComponent!=-1)
        {
            Components[currentSelectedComponent].isDeleted=true;
            Components[currentSelectedComponent].selected=false;

            Actions[actionIndex+1].type="COMPONENT_DELETED";
            Actions[actionIndex+1].componentId=currentSelectedComponent;
            actionIndex++;
            clearExtraComponentsOrConnections(actionIndex);

            currentSelectedComponent=-1;
        }
    }

    void undoAction()
    {
        unsetCurrentSelectedComponent();
        if(actionIndex>-1)
        {
            if(Actions[actionIndex].type=="COMPONENT_MOVED")
            {
                Components[Actions[actionIndex].componentId].topLeftCorner.x=Actions[actionIndex].previousComponentTopLeftCorner.x;
                Components[Actions[actionIndex].componentId].topLeftCorner.y=Actions[actionIndex].previousComponentTopLeftCorner.y;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="COMPONENT_ADDED")
            {
                Components[Actions[actionIndex].componentId].isDeleted=true;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="COMPONENT_DELETED")
            {
                Components[Actions[actionIndex].componentId].isDeleted=false;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="COMPONENT_ROTATED")
            {
                cout<<Actions[actionIndex].componentId<<" "<<actionIndex<<endl;
                Components[Actions[actionIndex].componentId].rotateComponent(Actions[actionIndex].previousRotatedAt);
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="COMPONENT_SCALED")
            {
                cout<<Actions[actionIndex].componentId<<" "<<actionIndex<<endl;
                Components[Actions[actionIndex].componentId].scaleComponent(Actions[actionIndex].previousScaledAt);
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="CONNECTION_DELETED")
            {
                Connections[Actions[actionIndex].connectionId].isDeleted=false;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="CONNECTION_ADDED")
            {
                Connections[Actions[actionIndex].connectionId].isDeleted=true;
            }
            else if(Actions[actionIndex].type=="CONNECTION_CHANGED_INPUT")
            {
                Connections[Actions[actionIndex].connectionId].inputComponentId=Actions[actionIndex].oldComponentId;
                Connections[Actions[actionIndex].connectionId].componentInputPointIndex=Actions[actionIndex].oldPointIndex;
                modifyCertainComponentConnections(Actions[actionIndex].oldComponentId);
            }
            else if(Actions[actionIndex].type=="CONNECTION_CHANGED_OUTPUT")
            {
                Connections[Actions[actionIndex].connectionId].outputComponentId=Actions[actionIndex].oldComponentId;
                Connections[Actions[actionIndex].connectionId].componentOutputPointIndex=Actions[actionIndex].oldPointIndex;
                modifyCertainComponentConnections(Actions[actionIndex].oldComponentId);
            }
            actionIndex--;
        }
    }

    void redoAction()
    {
        unsetCurrentSelectedComponent();
        if(actionIndex+1<actionsLength)
        {
            actionIndex++;
            if(Actions[actionIndex].type=="COMPONENT_MOVED")
            {
                Components[Actions[actionIndex].componentId].topLeftCorner.x=Actions[actionIndex].usedComponentNewTopLeftCorner.x;
                Components[Actions[actionIndex].componentId].topLeftCorner.y=Actions[actionIndex].usedComponentNewTopLeftCorner.y;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="COMPONENT_ADDED")
            {
                Components[Actions[actionIndex].componentId].isDeleted=false;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="COMPONENT_DELETED")
            {
                Components[Actions[actionIndex].componentId].isDeleted=true;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="COMPONENT_ROTATED")
            {
                Components[Actions[actionIndex].componentId].rotateComponent(Actions[actionIndex].rotatedAt);
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="COMPONENT_SCALED")
            {
                Components[Actions[actionIndex].componentId].scaleComponent(Actions[actionIndex].scaledAt);
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="CONNECTION_DELETED")
            {
                Connections[Actions[actionIndex].connectionId].isDeleted=true;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="CONNECTION_ADDED")
            {
                Connections[Actions[actionIndex].connectionId].isDeleted=false;
            }
            else if(Actions[actionIndex].type=="CONNECTION_CHANGED_INPUT")
            {
                Connections[Actions[actionIndex].connectionId].inputComponentId=Actions[actionIndex].componentId;
                Connections[Actions[actionIndex].connectionId].componentInputPointIndex=Actions[actionIndex].pointIndex;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
            else if(Actions[actionIndex].type=="CONNECTION_CHANGED_OUTPUT")
            {
                Connections[Actions[actionIndex].connectionId].outputComponentId=Actions[actionIndex].componentId;
                Connections[Actions[actionIndex].connectionId].componentOutputPointIndex=Actions[actionIndex].pointIndex;
                modifyCertainComponentConnections(Actions[actionIndex].componentId);
            }
        }
    }

    void addRotationAction()
    {
        if(currentSelectedComponent!=-1)
        {
            if(Actions[actionIndex+1].previousRotatedAt!=Components[currentSelectedComponent].rotatedAt)
            {
                actionIndex++;
                Actions[actionIndex].type="COMPONENT_ROTATED";
                Actions[actionIndex].rotatedAt=Components[currentSelectedComponent].rotatedAt;
                Actions[actionIndex].componentId=currentSelectedComponent;
                cout<<currentSelectedComponent<<" "<<Actions[actionIndex].componentId<<" "<<actionIndex<<endl;
                clearExtraComponentsOrConnections(actionIndex);
            }
        }
    }

    void addScaleAction()
    {
        if(currentSelectedComponent!=-1)
        {
            if(Actions[actionIndex+1].previousScaledAt!=Components[currentSelectedComponent].scaledAt)
            {
                actionIndex++;
                Actions[actionIndex].type="COMPONENT_SCALED";
                Actions[actionIndex].scaledAt=Components[currentSelectedComponent].scaledAt;
                Actions[actionIndex].componentId=currentSelectedComponent;
                cout<<currentSelectedComponent<<" "<<Actions[actionIndex].componentId<<" "<<actionIndex<<endl;
                clearExtraComponentsOrConnections(actionIndex);
            }
        }
    }

    void clearExtraComponentsOrConnections(int ai)
    {
        actionsLength=ai+1;
    }
    void addConnection(int selectedComponentIndex,int selectedIOIndex,int selectedPointType,int mouseX, int mouseY)
    {
        if(selectedPointType==1)
        {
            Connections[connectionsLength].startPoint.x=Components[selectedComponentIndex].outputPoints[selectedIOIndex].x+Components[selectedComponentIndex].topLeftCorner.x;
            Connections[connectionsLength].startPoint.y=Components[selectedComponentIndex].outputPoints[selectedIOIndex].y+Components[selectedComponentIndex].topLeftCorner.y;
            Connections[connectionsLength].endPoint.x=mouseX;
            Connections[connectionsLength].endPoint.y=mouseY;
            Connections[connectionsLength].outputComponentId=selectedComponentIndex;
            Connections[connectionsLength].componentOutputPointIndex=selectedIOIndex;
            currentSelectedConnection=connectionsLength;
            connectionsLength++;

        }
        else
        {
            Connections[connectionsLength].startPoint.x=mouseX;
            Connections[connectionsLength].startPoint.y=mouseY;
            Connections[connectionsLength].endPoint.x=Components[selectedComponentIndex].inputPoints[selectedIOIndex].x+Components[selectedComponentIndex].topLeftCorner.x;
            Connections[connectionsLength].endPoint.y=Components[selectedComponentIndex].inputPoints[selectedIOIndex].y+Components[selectedComponentIndex].topLeftCorner.y;
            Connections[connectionsLength].inputComponentId=selectedComponentIndex;
            Connections[connectionsLength].componentInputPointIndex=selectedIOIndex;
            currentSelectedConnection=connectionsLength;
            connectionsLength++;
        }

    }

    void modifyComponentConnections()
    {
        for (int i=0; i<connectionsLength; i++)
        {
            if(Connections[i].outputComponentId==currentSelectedComponent||currentSelectedComponent==-1)
            {
                Connections[i].startPoint.x=Components[currentSelectedComponent].outputPoints[Connections[i].componentOutputPointIndex].x+Components[currentSelectedComponent].topLeftCorner.x;
                Connections[i].startPoint.y=Components[currentSelectedComponent].outputPoints[Connections[i].componentOutputPointIndex].y+Components[currentSelectedComponent].topLeftCorner.y;
            }
            if(Connections[i].inputComponentId==currentSelectedComponent||currentSelectedComponent==-1)
            {
                Connections[i].endPoint.x=Components[currentSelectedComponent].inputPoints[Connections[i].componentInputPointIndex].x+Components[currentSelectedComponent].topLeftCorner.x;
                Connections[i].endPoint.y=Components[currentSelectedComponent].inputPoints[Connections[i].componentInputPointIndex].y+Components[currentSelectedComponent].topLeftCorner.y;
            }
        }
    }

    void modifyCertainComponentConnections(int id)
    {
        for (int i=0; i<connectionsLength; i++)
        {
            if(Connections[i].outputComponentId==id)
            {
                Connections[i].startPoint.x=Components[id].outputPoints[Connections[i].componentOutputPointIndex].x+Components[id].topLeftCorner.x;
                Connections[i].startPoint.y=Components[id].outputPoints[Connections[i].componentOutputPointIndex].y+Components[id].topLeftCorner.y;
            }
            if(Connections[i].inputComponentId==id)
            {
                Connections[i].endPoint.x=Components[id].inputPoints[Connections[i].componentInputPointIndex].x+Components[id].topLeftCorner.x;
                Connections[i].endPoint.y=Components[id].inputPoints[Connections[i].componentInputPointIndex].y+Components[id].topLeftCorner.y;
            }
        }
    }


    void addSecondConnectionPoint(int selectedComponentIndex,int selectedIOIndex,int selectedPointType)
    {
        if(selectedPointType==1)
        {
            Connections[currentSelectedConnection].startPoint.x=Components[selectedComponentIndex].outputPoints[selectedIOIndex].x+Components[selectedComponentIndex].topLeftCorner.x;
            Connections[currentSelectedConnection].startPoint.y=Components[selectedComponentIndex].outputPoints[selectedIOIndex].y+Components[selectedComponentIndex].topLeftCorner.y;
            Connections[currentSelectedConnection].outputComponentId=selectedComponentIndex;
            Connections[currentSelectedConnection].componentOutputPointIndex=selectedIOIndex;
        }
        else
        {
            Connections[currentSelectedConnection].endPoint.x=Components[selectedComponentIndex].inputPoints[selectedIOIndex].x+Components[selectedComponentIndex].topLeftCorner.x;
            Connections[currentSelectedConnection].endPoint.y=Components[selectedComponentIndex].inputPoints[selectedIOIndex].y+Components[selectedComponentIndex].topLeftCorner.y;
            Connections[currentSelectedConnection].inputComponentId=selectedComponentIndex;
            Connections[currentSelectedConnection].componentInputPointIndex=selectedIOIndex;
        }

    }

    void initializeLetterComponentsFonts()
    {
        for(int i=0; i<componentsLength; i++)
        {
            Components[i].initializeFont();
        }
    }

    void unsetCurrentSelectedComponent()
    {
        if(currentSelectedComponent!=-1)
        {
            Components[currentSelectedComponent].selected=false;
            currentSelectedComponent=-1;
        }
    }
    void rotateSelectedComponent(int angle)
    {
        if(currentSelectedComponent!=-1)
        {
            Components[currentSelectedComponent].rotateComponent(angle);
            modifyComponentConnections();
        }
    }

    void scaleSelectedComponent(float scaleAt)
    {
        if(currentSelectedComponent!=-1)
        {
            Components[currentSelectedComponent].scaleComponent(scaleAt);
            modifyComponentConnections();
        }
    }

    bool onMousePress(int mouseX,int mouseY,sf::RenderWindow &win)
    {
        bool isAnyHoveredComponent=false;
        for(int i=0; i<componentsLength; i++)
            if(Components[i].mouseOn(mouseX,mouseY))
            {
                for(int j=0; j<componentsLength; j++)
                    Components[j].selected=false;
                Components[i].selected=true;
                currentSelectedComponent=i;
                isMouseLongPressed=true;
                isAnyHoveredComponent=true;
                mouseLongPressXDiff=mouseX-Components[i].topLeftCorner.x;
                mouseLongPressYDiff=mouseY-Components[i].topLeftCorner.y;

                if(currentSelectedComponent!=-1&&currentSelectedComponent!=i)
                {
                    Components[currentSelectedComponent].selected=false;
                }

                Actions[actionIndex+1].previousComponentTopLeftCorner.x=Components[currentSelectedComponent].topLeftCorner.x;
                Actions[actionIndex+1].previousComponentTopLeftCorner.y=Components[currentSelectedComponent].topLeftCorner.y;
                Actions[actionIndex+1].previousRotatedAt=Components[currentSelectedComponent].rotatedAt;
                Actions[actionIndex+1].previousScaledAt=Components[currentSelectedComponent].scaledAt;
                Actions[actionIndex+1].componentId=currentSelectedComponent;


                int selectedInputPointIndex=Components[i].isOnAnyInputPoints(mouseX,mouseY);
                if(selectedInputPointIndex!=-1)
                {

                    bool isAlreadyConnected=false;
                    for(int j=0; j<=connectionsLength; j++)
                        if(Connections[j].isDeleted==false&&Connections[j].outputComponentId!=-1&&Connections[j].outputComponentId!=i&&selectedInputPointIndex==Connections[j].componentInputPointIndex&&Connections[j].inputComponentId==i)
                        {
                            currentSelectedConnection=j;
                            Connections[j].endPoint.x=mouseX;
                            Connections[j].endPoint.y=mouseY;

                            oldInputComponentId=Connections[j].inputComponentId;
                            oldComponentInputPointIndex=Connections[j].componentInputPointIndex;

                            Connections[j].inputComponentId=-1;
                            Connections[j].componentInputPointIndex=-1;
                            isAlreadyConnected=true;
                            break;
                        }
                    if(isAlreadyConnected==true)
                    {
                        isOutputConnectionSelected=true;
                        isFromExistingConnection=true;
                    }
                    else
                    {
                        isInputConnectionSelected=true;
                        addConnection(i,selectedInputPointIndex,0,mouseX,mouseY);
                    }
                }
                else
                {
                    int selectedOutputPointIndex=Components[i].isOnAnyOutputPoints(mouseX,mouseY);
                    if(selectedOutputPointIndex!=-1)
                    {
                        bool isAlreadyConnected=false;
                        for(int j=0; j<=connectionsLength; j++)
                            if(Connections[j].isDeleted==false&&Connections[j].inputComponentId!=-1&&Connections[j].inputComponentId!=i&&selectedOutputPointIndex==Connections[j].componentOutputPointIndex&&Connections[j].outputComponentId==i)
                            {
                                currentSelectedConnection=j;
                                Connections[j].startPoint.x=mouseX;
                                Connections[j].startPoint.y=mouseY;

                                oldOutputComponentId=Connections[j].outputComponentId;
                                oldComponentOutputPointIndex=Connections[j].componentOutputPointIndex;

                                Connections[j].outputComponentId=-1;
                                Connections[j].componentOutputPointIndex=-1;
                                isAlreadyConnected=true;
                                break;
                            }
                        if(isAlreadyConnected==true)
                        {
                            isInputConnectionSelected=true;
                            isFromExistingConnection=true;
                        }
                        else
                        {
                            isOutputConnectionSelected=true;
                            addConnection(i,selectedOutputPointIndex,1,mouseX,mouseY);
                        }
                    }
                }
                break;
            }
        return isAnyHoveredComponent;
    }

    void onMouseMove(int mouseX,int mouseY)
    {
        if(isMouseLongPressed==true)
        {
            if(currentSelectedComponent!=-1&&currentSelectedConnection==-1)
            {
                Components[currentSelectedComponent].topLeftCorner.x=mouseX-mouseLongPressXDiff;
                Components[currentSelectedComponent].topLeftCorner.y=mouseY-mouseLongPressYDiff;
                modifyComponentConnections();
            }
            else if(currentSelectedConnection!=-1)
            {
                if(isInputConnectionSelected==true)
                {
                    Connections[currentSelectedConnection].startPoint.x=mouseX;
                    Connections[currentSelectedConnection].startPoint.y=mouseY;
                }
                else if(isOutputConnectionSelected==true)
                {
                    Connections[currentSelectedConnection].endPoint.x=mouseX;
                    Connections[currentSelectedConnection].endPoint.y=mouseY;
                }

            }
        }
    }

    void onMouseRelease(int mouseX,int mouseY)
    {
        isMouseLongPressed=false;
        if(isInputConnectionSelected==true)
        {
            bool hasFoundAComponent=false;
            for(int i=0; i<componentsLength; i++)
                if(Components[i].mouseOn(mouseX,mouseY))
                {
                    int selectedOutputPointIndex=Components[i].isOnAnyOutputPoints(mouseX,mouseY);
                    if(selectedOutputPointIndex!=-1&&i!=Connections[currentSelectedConnection].inputComponentId)
                    {
                        addSecondConnectionPoint(i,selectedOutputPointIndex,1);
                        hasFoundAComponent=true;

                        if(oldOutputComponentId!=i)
                        {
                            if(isFromExistingConnection==false)
                            {
                                actionIndex++;
                                Actions[actionIndex].type="CONNECTION_ADDED";
                                Actions[actionIndex].connectionId=currentSelectedConnection;
                                clearExtraComponentsOrConnections(actionIndex);
                            }
                            else
                            {
                                actionIndex++;
                                Actions[actionIndex].type="CONNECTION_CHANGED_OUTPUT";
                                Actions[actionIndex].oldComponentId=oldOutputComponentId;
                                Actions[actionIndex].oldPointIndex=oldComponentOutputPointIndex;
                                Actions[actionIndex].componentId=i;
                                Actions[actionIndex].pointIndex=selectedOutputPointIndex;

                                Actions[actionIndex].connectionId=currentSelectedConnection;
                                clearExtraComponentsOrConnections(actionIndex);
                            }
                        }
                    }
                }
            if(hasFoundAComponent==false)
            {
                Connections[currentSelectedConnection].outputComponentId=oldOutputComponentId;
                Connections[currentSelectedConnection].componentOutputPointIndex=oldComponentOutputPointIndex;
                Connections[currentSelectedConnection].isDeleted=true;

                actionIndex++;
                Actions[actionIndex].type="CONNECTION_DELETED";
                Actions[actionIndex].componentId=oldOutputComponentId;
                Actions[actionIndex].connectionId=currentSelectedConnection;
                clearExtraComponentsOrConnections(actionIndex);
            }
            currentSelectedConnection=-1;
            isInputConnectionSelected=false;
        }
        else if(isOutputConnectionSelected==true)
        {
            bool hasFoundAComponent=false;
            for(int i=0; i<componentsLength; i++)
                if(Components[i].mouseOn(mouseX,mouseY))
                {
                    int selectedInputPointIndex=Components[i].isOnAnyInputPoints(mouseX,mouseY);
                    if(selectedInputPointIndex!=-1&&i!=Connections[currentSelectedConnection].outputComponentId)
                    {
                        addSecondConnectionPoint(i,selectedInputPointIndex,0);
                        hasFoundAComponent=true;

                        if(isFromExistingConnection==false)
                        {
                            actionIndex++;
                            Actions[actionIndex].type="CONNECTION_ADDED";
                            Actions[actionIndex].connectionId=currentSelectedConnection;
                            clearExtraComponentsOrConnections(actionIndex);
                        }
                        else
                        {
                            actionIndex++;
                            Actions[actionIndex].type="CONNECTION_CHANGED_INPUT";
                            Actions[actionIndex].oldComponentId=oldInputComponentId;
                            Actions[actionIndex].oldPointIndex=oldComponentInputPointIndex;
                            Actions[actionIndex].componentId=i;
                            Actions[actionIndex].pointIndex=selectedInputPointIndex;

                            Actions[actionIndex].connectionId=currentSelectedConnection;
                            clearExtraComponentsOrConnections(actionIndex);
                        }
                    }
                }
            if(hasFoundAComponent==false)
            {
                Connections[currentSelectedConnection].inputComponentId=oldInputComponentId;
                Connections[currentSelectedConnection].componentInputPointIndex=oldComponentInputPointIndex;
                Connections[currentSelectedConnection].isDeleted=true;

                actionIndex++;
                Actions[actionIndex].componentId=oldInputComponentId;
                Actions[actionIndex].type="CONNECTION_DELETED";
                Actions[actionIndex].connectionId=currentSelectedConnection;
                clearExtraComponentsOrConnections(actionIndex);
            }
            currentSelectedConnection=-1;
            isOutputConnectionSelected=false;
        }
        else if(currentSelectedComponent!=-1&&justAddedAComponent==false)
        {
            if(isASliderSelected==0)
                if(mouseX-mouseLongPressXDiff!=Actions[actionIndex+1].previousComponentTopLeftCorner.x||mouseY-mouseLongPressYDiff!=Actions[actionIndex+1].previousComponentTopLeftCorner.y&&isASliderSelected==0)
                {
                    actionIndex++;
                    Actions[actionIndex].type="COMPONENT_MOVED";
                    Actions[actionIndex].usedComponentNewTopLeftCorner.x=mouseX;
                    Actions[actionIndex].usedComponentNewTopLeftCorner.y=mouseY;
                    Actions[actionIndex].componentId=currentSelectedComponent;
                    clearExtraComponentsOrConnections(actionIndex);
                }
            Actions[actionIndex+1].previousComponentTopLeftCorner.x=Components[currentSelectedComponent].topLeftCorner.x;
            Actions[actionIndex+1].previousComponentTopLeftCorner.y=Components[currentSelectedComponent].topLeftCorner.y;
            Actions[actionIndex+1].previousRotatedAt=Components[currentSelectedComponent].rotatedAt;
            Actions[actionIndex+1].previousScaledAt=Components[currentSelectedComponent].scaledAt;
        }
        justAddedAComponent=false;
        oldInputComponentId=-1;
        oldOutputComponentId=-1;
        oldComponentInputPointIndex=-1;
        oldComponentOutputPointIndex-1;
        isFromExistingConnection=false;
        coutActions();
    }

    void draw(sf::RenderWindow &win)
    {
        for(int i=0; i<componentsLength; i++)
        {
            Components[i].draw(win);
        }
        for(int i=0; i<connectionsLength; i++)
        {
            if(Components[Connections[i].inputComponentId].isDeleted==false&&Components[Connections[i].outputComponentId].isDeleted==false)
                Connections[i].draw(win);
        }
    }




    void initializeModal(int x, int y, sf::Font &font)
    {

        modalBlur.setSize(sf::Vector2f(3000, 3000));
        modalBlur.setPosition(0, 0);
        modalBlur.setFillColor(sf::Color(0, 0, 0, 200));

        modalGrid.setSize(sf::Vector2f(400, 300));
        modalGrid.setFillColor(sf::Color::Black);
        modalGrid.setOutlineColor(sf::Color::Red);
        modalGrid.setOutlineThickness(3);
        modalGrid.setPosition(sf::Vector2f(x,y));
        modalEditorTitle.setFont(font);
        modalEditorTitle.setCharacterSize(40);
        modalEditorTitle.setString("Parameters");
        modalEditorTitle.setColor(sf::Color::White);
        modalEditorTitle.setPosition(x + 200 - modalEditorTitle.getGlobalBounds().width/2, y + 10);

        modalExit.setSize(sf::Vector2f(30, 20));
        modalExit.setFillColor(sf::Color::Transparent);
        modalExit.setOutlineColor(sf::Color::White);
        modalExit.setOutlineThickness(3);
        modalExit.setPosition(sf::Vector2f(x + 400 - 33, y + 3));
        modalExitText.setFont(font);
        modalExitText.setPosition(x + 400 - 26, y - 9);
        modalExitText.setString("x");
        modalExitText.setColor(sf::Color::White);

        modalEdit.setSize(sf::Vector2f(100, 40));
        modalEdit.setFillColor(sf::Color::Transparent);
        modalEdit.setOutlineColor(sf::Color::White);
        modalEdit.setOutlineThickness(3);
        modalEdit.setPosition(sf::Vector2f(x + 200 - 48, y + 225));
        modalEditText.setFont(font);
        modalEditText.setString("Edit");
        modalEditText.setPosition(x + 200 - modalEditText.getGlobalBounds().width/2, y + 225);
        modalEditText.setColor(sf::Color::White);

        modalName.setUp(25, sf::Color::White, false, "Nume");
        modalName.setFont(font);
        modalName.setLimit(10);
        modalName.setPosition(sf::Vector2f(x + 200, y + 80));

        modalRezistenta.setUp(25, sf::Color::White, false, "Rezistenta");
        modalRezistenta.setFont(font);
        modalRezistenta.setFloat(1.23);
        modalRezistenta.setLimit(10);
        modalRezistenta.setPosition(sf::Vector2f(x + 200, y + 120));

        modalVoltaj.setUp(25, sf::Color::White, false, "Voltaj");
        modalVoltaj.setFont(font);
        modalVoltaj.setFloat(2.0);
        modalVoltaj.setLimit(10);
        modalVoltaj.setPosition(sf::Vector2f(x + 200, y + 160));

        //MESSAGE MODAL
        modalSuccessGrid.setPosition(sf::Vector2f(x,y));
        modalSuccessTitle.setPosition(x + 200 - modalSuccessTitle.getGlobalBounds().width/2, y + 10);
        modalSuccessText.setPosition(x+(400 - modalSuccessText.getGlobalBounds().width)/2, y + 100);
        modalSuccessExit.setPosition(sf::Vector2f(x + 400 - 33, y + 3));
        modalSuccessExitText.setPosition(x + 400 - 26, y - 9);
        modalSuccessDone.setPosition(sf::Vector2f(x + 200 - 48, y + 225));
        modalSuccessDoneText.setPosition(x + 200 - modalSuccessDoneText.getGlobalBounds().width/2, y + 225);

        modalSuccessBlur.setSize(sf::Vector2f(3000, 3000));
        modalSuccessBlur.setPosition(0, 0);
        modalSuccessBlur.setFillColor(sf::Color(0, 0, 0, 200));

        modalSuccessGrid.setSize(sf::Vector2f(400, 300));
        modalSuccessGrid.setFillColor(sf::Color::Black);
        modalSuccessGrid.setOutlineColor(sf::Color::Red);
        modalSuccessGrid.setOutlineThickness(3);
        modalSuccessGrid.setPosition(sf::Vector2f(x,y));
        modalSuccessTitle.setFont(font);
        modalSuccessTitle.setCharacterSize(40);
        modalSuccessTitle.setString("Success");
        modalSuccessTitle.setColor(sf::Color::White);
        modalSuccessTitle.setPosition(x + 200 - modalSuccessTitle.getGlobalBounds().width/2, y + 10);

        modalSuccessText.setFont(font);
        modalSuccessText.setCharacterSize(25);
        modalSuccessText.setString("The Electron project has been\n        successfully saved!     ");
        modalSuccessText.setColor(sf::Color::White);
        modalSuccessText.setPosition(x+(400 - modalSuccessText.getGlobalBounds().width)/2, y + 100);

        modalSuccessExit.setSize(sf::Vector2f(30, 20));
        modalSuccessExit.setFillColor(sf::Color::Transparent);
        modalSuccessExit.setOutlineColor(sf::Color::White);
        modalSuccessExit.setOutlineThickness(3);
        modalSuccessExit.setPosition(sf::Vector2f(x + 400 - 33, y + 3));
        modalSuccessExitText.setFont(font);
        modalSuccessExitText.setPosition(x + 400 - 26, y - 9);
        modalSuccessExitText.setString("x");
        modalSuccessExitText.setColor(sf::Color::White);

        modalSuccessDone.setSize(sf::Vector2f(100, 40));
        modalSuccessDone.setFillColor(sf::Color::Transparent);
        modalSuccessDone.setOutlineColor(sf::Color::White);
        modalSuccessDone.setOutlineThickness(3);
        modalSuccessDone.setPosition(sf::Vector2f(x + 200 - 48, y + 225));
        modalSuccessDoneText.setFont(font);
        modalSuccessDoneText.setString("Ok");
        modalSuccessDoneText.setPosition(x + 200 - modalSuccessDoneText.getGlobalBounds().width/2, y + 225);
        modalSuccessDoneText.setColor(sf::Color::White);

    }

    void updateModalPos(int x,int y)
    {

        modalGrid.setPosition(sf::Vector2f(x,y));
        modalEditorTitle.setPosition(x + 200 - modalEditorTitle.getGlobalBounds().width/2, y + 10);
        modalExit.setPosition(sf::Vector2f(x + 400 - 33, y + 3));
        modalExitText.setPosition(x + 400 - 26, y - 9);
        modalEdit.setPosition(sf::Vector2f(x + 200 - 48, y + 225));
        modalEditText.setPosition(x + 200 - modalEditText.getGlobalBounds().width/2, y + 225);
        modalName.setPosition(sf::Vector2f(x + 200, y + 80));
        modalRezistenta.setPosition(sf::Vector2f(x + 200, y + 120));
        modalVoltaj.setPosition(sf::Vector2f(x + 200, y + 160));

        modalSuccessGrid.setPosition(sf::Vector2f(x,y));
        modalSuccessTitle.setPosition(x + 200 - modalSuccessTitle.getGlobalBounds().width/2, y + 10);
        modalSuccessText.setPosition(x+(400 - modalSuccessText.getGlobalBounds().width)/2, y + 100);
        modalSuccessExit.setPosition(sf::Vector2f(x + 400 - 33, y + 3));
        modalSuccessExitText.setPosition(x + 400 - 26, y - 9);
        modalSuccessDone.setPosition(sf::Vector2f(x + 200 - 48, y + 225));
        modalSuccessDoneText.setPosition(x + 200 - modalSuccessDoneText.getGlobalBounds().width/2, y + 225);

    }

    void modalLogic(sf::Event event, sf::RenderWindow &window)
    {

        if(event.type == sf::Event::TextEntered)
        {
            modalName.typedOn(event);
            modalRezistenta.typedOn(event);
            modalVoltaj.typedOn(event);
        }

        if(sf::Mouse::getPosition(window).x >= modalExit.getPosition().x && sf::Mouse::getPosition(window).x <= modalExit.getPosition().x + modalExit.getGlobalBounds().width &&
                sf::Mouse::getPosition(window).y >= modalExit.getPosition().y && sf::Mouse::getPosition(window).y <= modalExit.getPosition().y + modalExit.getGlobalBounds().height)
            modalExit.setOutlineColor(sf::Color::Red);
        else modalExit.setOutlineColor(sf::Color::White);

        if(sf::Mouse::getPosition(window).x >= modalSuccessDone.getPosition().x && sf::Mouse::getPosition(window).x <= modalSuccessDone.getPosition().x + modalSuccessDone.getGlobalBounds().width &&
                sf::Mouse::getPosition(window).y >= modalSuccessDone.getPosition().y && sf::Mouse::getPosition(window).y <= modalSuccessDone.getPosition().y + modalSuccessDone.getGlobalBounds().height)
            modalSuccessDone.setOutlineColor(sf::Color::Red);
        else modalSuccessDone.setOutlineColor(sf::Color::White);

        if(sf::Mouse::getPosition(window).x >= modalEdit.getPosition().x && sf::Mouse::getPosition(window).x <= modalEdit.getPosition().x + modalEdit.getGlobalBounds().width &&
                sf::Mouse::getPosition(window).y >= modalEdit.getPosition().y && sf::Mouse::getPosition(window).y <= modalEdit.getPosition().y + modalEdit.getGlobalBounds().height)
            modalEdit.setOutlineColor(sf::Color::Red);
        else modalEdit.setOutlineColor(sf::Color::White);

        if(sf::Mouse::getPosition(window).x >= modalSuccessExit.getPosition().x && sf::Mouse::getPosition(window).x <= modalSuccessExit.getPosition().x + modalSuccessExit.getGlobalBounds().width &&
                sf::Mouse::getPosition(window).y >= modalSuccessExit.getPosition().y && sf::Mouse::getPosition(window).y <= modalSuccessExit.getPosition().y + modalSuccessExit.getGlobalBounds().height)
            modalSuccessExit.setOutlineColor(sf::Color::Red);
        else modalSuccessExit.setOutlineColor(sf::Color::White);

        if (event.type == sf::Event::MouseButtonPressed)
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if(modalName.isOn(event.mouseButton.x, event.mouseButton.y))
                    modalName.setSelected(true);
                else modalName.setSelected(false);

                if(modalRezistenta.isOn(event.mouseButton.x, event.mouseButton.y))
                    modalRezistenta.setSelected(true);
                else modalRezistenta.setSelected(false);

                if(modalVoltaj.isOn(event.mouseButton.x, event.mouseButton.y))
                    modalVoltaj.setSelected(true);
                else modalVoltaj.setSelected(false);

                if(sf::Mouse::getPosition(window).x >= modalExit.getPosition().x && sf::Mouse::getPosition(window).x <= modalExit.getPosition().x + modalExit.getGlobalBounds().width &&
                        sf::Mouse::getPosition(window).y >= modalExit.getPosition().y && sf::Mouse::getPosition(window).y <= modalExit.getPosition().y + modalExit.getGlobalBounds().height)
                    isModalClosed = true;

                if(sf::Mouse::getPosition(window).x >= modalSuccessExit.getPosition().x && sf::Mouse::getPosition(window).x <= modalSuccessExit.getPosition().x + modalSuccessExit.getGlobalBounds().width &&
                        sf::Mouse::getPosition(window).y >= modalSuccessExit.getPosition().y && sf::Mouse::getPosition(window).y <= modalSuccessExit.getPosition().y + modalSuccessExit.getGlobalBounds().height)
                    isMessageModalClosed = true;

                if(sf::Mouse::getPosition(window).x >= modalEdit.getPosition().x && sf::Mouse::getPosition(window).x <= modalEdit.getPosition().x + modalEdit.getGlobalBounds().width &&
                        sf::Mouse::getPosition(window).y >= modalEdit.getPosition().y && sf::Mouse::getPosition(window).y <= modalEdit.getPosition().y + modalEdit.getGlobalBounds().height&&isModalClosed==false)
                    modalEditComponent();

                if(sf::Mouse::getPosition(window).x >= modalSuccessDone.getPosition().x && sf::Mouse::getPosition(window).x <= modalSuccessDone.getPosition().x + modalSuccessDone.getGlobalBounds().width &&
                        sf::Mouse::getPosition(window).y >= modalSuccessDone.getPosition().y && sf::Mouse::getPosition(window).y <= modalSuccessDone.getPosition().y + modalSuccessDone.getGlobalBounds().height)
                    isMessageModalClosed=true;
            }


    }

    void openModal()
    {
        modalName.setText(Components[toEditComponentId].name);
        modalRezistenta.setFloat(Components[toEditComponentId].R);
        modalVoltaj.setFloat(Components[toEditComponentId].V);
        isModalClosed = false;
    }

    void drawModal(sf::RenderWindow &window)
    {

        if(isModalClosed == false)
        {
            window.draw(modalBlur);
            window.draw(modalGrid);
            window.draw(modalExit);
            window.draw(modalEdit);
            window.draw(modalEditText);
            window.draw(modalExitText);
            window.draw(modalEditorTitle);
            modalName.drawTo(window);
            modalRezistenta.drawTo(window);
            modalVoltaj.drawTo(window);
        }
        else if(isMessageModalClosed==false)
        {
            window.draw(modalSuccessBlur);
            window.draw(modalSuccessGrid);
            window.draw(modalSuccessTitle);
            window.draw(modalSuccessText);
            window.draw(modalSuccessDone);
            window.draw(modalSuccessDoneText);
            window.draw(modalSuccessExit);
            window.draw(modalSuccessExitText);
        }
    }
    void modalEditComponent()
    {
        Components[toEditComponentId].name=modalName.getText();
        Components[toEditComponentId].R=modalRezistenta.getFloatValue();
        Components[toEditComponentId].V=modalVoltaj.getFloatValue();
        isModalClosed=true;
    }
};



