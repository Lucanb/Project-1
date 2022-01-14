#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "ComonentsParts.h"
#include "SliderDesign.cpp"
#include "RowText.h"
#include <Windows.h>
#include <Commdlg.h>
using namespace std;

struct Component
{
    string filePath;
    int gridWidth, gridHeight;
    int tipComponent;
    int id;
    int gradeRotire=0;
    float scaledAt=1;
    int LungimeInputPoints=0,LungimeOutputPoints=0;
    Point ColtStangaSus;
    Point inputPoints[MAX_INPUT_POINTS];
    Point outputPoints[MAX_OUTPUT_POINTS];

    int lungimeCercuri=0;
    CircleSubComponent Cercuri[10];

    int LungimeDreptunghiuri=0;
    RectangleSubComponent Rectangles[10];

    int lungimeLinii=0;
    LineSubComponent Lines[10];

    int lungimeLitere=0;
    LetterSubComponent Letters[10];

    string name="Componenta";
    char name2[25];
    float R=0;
    float V=0;
    bool selected=false;
    bool isDeleted=false;
    void read()
    {
        FILE* componentFile;
        filePath=Componente[tipComponent].adresa;
        int rowIndex=0;
        char row[MAX_ROW_SIZE];
        int spacingRows=0;
        string currentRecursiveValues="";
        char filePathChar[150];
        strcpy(filePathChar,filePath.c_str());
        if (!(componentFile = fopen(filePathChar, "r")))
        {
            exit(1);
        }
        while(!feof(componentFile))
        {
            if (!fgets(row,MAX_ROW_SIZE,componentFile))
                exit(1);
            if(rowIndex==0)
            {
                char *gridValue=strtok(row," ");
                gridWidth=-1;
                gridHeight=-1;
                while(gridValue)
                {
                    if(gridWidth==-1)
                        gridWidth=atoi(gridValue);
                    else
                        gridHeight=atoi(gridValue);
                    gridValue=strtok(NULL," ");
                }
                if(!(gridWidth!=-1&&gridHeight!=-1))
                    exit(1);
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
                        if(spacingRows > MAX_ROWS)
                            exit(1);
                        else
                            rowIndex++;
                    }
                    else if(currentRecursiveValues=="INPUT_POINTS")
                    {
                        spacingRows=0;
                        inputPoints[LungimeInputPoints].readPoint(row,rowIndex);
                        if(!(inputPoints[LungimeInputPoints].x!=-1&&inputPoints[LungimeInputPoints].y!=-1))
                            exit(1);
                        else
                        {
                            inputPoints[LungimeInputPoints].x=inputPoints[LungimeInputPoints].x-gridWidth/2.0;
                            inputPoints[LungimeInputPoints].y=inputPoints[LungimeInputPoints].y-gridHeight/2.0;
                            LungimeInputPoints++;
                        }
                        rowIndex++;
                    }
                    else if(currentRecursiveValues=="OUTPUT_POINTS")
                    {
                        spacingRows=0;
                        outputPoints[LungimeOutputPoints].readPoint(row,rowIndex);
                        if(!(outputPoints[LungimeOutputPoints].x!=-1&&outputPoints[LungimeOutputPoints].y!=-1))
                            exit(1);
                        else
                        {
                            outputPoints[LungimeOutputPoints].x=outputPoints[LungimeOutputPoints].x-gridWidth/2.00;
                            outputPoints[LungimeOutputPoints].y=outputPoints[LungimeOutputPoints].y-gridHeight/2.00;
                            LungimeOutputPoints++;
                        }
                        rowIndex++;
                    }
                    else if(currentRecursiveValues=="SUBCOMPONENTS_FUNCTIONS")
                    {
                        spacingRows=0;
                        if(row[0]=='C')
                        {
                            strcpy(row, row+1);
                            Cercuri[lungimeCercuri].read(row,rowIndex);
                            if(Cercuri[lungimeCercuri].r==-1)
                            {
                                cout<<"The Circle subcomponent declared on line "<<rowIndex+1<<" does not contain a valid radius. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                exit(1);
                            }
                            if(!(Cercuri[lungimeCercuri].ColtStangaSus.x!=-1&&Cercuri[lungimeCercuri].ColtStangaSus.y!=-1))
                            {
                                cout<<"The Circle subcomponent declared on line "<<rowIndex+1<<" does not contain a valid top left point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                exit(1);
                            }
                            else
                            {
                                Cercuri[lungimeCercuri].ColtStangaSus.x=Cercuri[lungimeCercuri].ColtStangaSus.x-gridWidth/2.00;
                                Cercuri[lungimeCercuri].ColtStangaSus.y=Cercuri[lungimeCercuri].ColtStangaSus.y-gridHeight/2.00;
                                lungimeCercuri++;
                            }
                        }

                        else if(row[0]=='R')
                        {
                            strcpy(row, row+1);
                            Rectangles[LungimeDreptunghiuri].read(row,rowIndex);
                            if(!(Rectangles[LungimeDreptunghiuri].ColtStangaSus.x!=-1&&Rectangles[LungimeDreptunghiuri].ColtStangaSus.y!=-1))
                            {
                                cout<<"The Rectangle subcomponent declared on line "<<rowIndex+1<< " does not contain a valid top left corner point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                exit(1);
                            }
                            else if(!(Rectangles[LungimeDreptunghiuri].width!=-1&&Rectangles[LungimeDreptunghiuri].height!=-1))
                            {
                                cout<<"The Rectangle subcomponent declared on line "<<rowIndex+1<< " does not contain valid width or height values. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                exit(1);
                            }
                            else
                            {
                                Rectangles[LungimeDreptunghiuri].ColtStangaSus.x=Rectangles[LungimeDreptunghiuri].ColtStangaSus.x-gridWidth/2.00;
                                Rectangles[LungimeDreptunghiuri].ColtStangaSus.y=Rectangles[LungimeDreptunghiuri].ColtStangaSus.y-gridHeight/2.00;
                                LungimeDreptunghiuri++;
                            }
                        }

                        else if(row[0]=='L')
                        {
                            if(row[1]=='T')
                            {
                                strcpy(row, row+2);
                                Letters[lungimeLitere].read(row,rowIndex);
                                if(Letters[lungimeLitere].letter=="0")
                                {
                                    cout<<"The Letter subcomponent declared on line "<<rowIndex+1<<" does not contain a valid letter. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                if(!(Letters[lungimeLitere].ColtStangaSus.x!=-1&&Letters[lungimeLitere].ColtStangaSus.y!=-1))
                                {
                                    cout<<"The Letter subcomponent declared on line "<<rowIndex+1<<" does not contain a valid top left point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                else
                                {
                                    Letters[lungimeLitere].ColtStangaSus.x=Letters[lungimeLitere].ColtStangaSus.x-gridWidth/2.00;
                                    Letters[lungimeLitere].ColtStangaSus.y=Letters[lungimeLitere].ColtStangaSus.y-gridHeight/2.00;
                                    Letters[lungimeLitere].initializeFont();
                                    lungimeLitere++;
                                }
                            }
                            else if(row[1]=='S')
                            {
                                strcpy(row, row+2);
                                Letters[lungimeLitere].read(row,rowIndex);
                                Letters[lungimeLitere].isSmall=true;
                                if(Letters[lungimeLitere].letter=="0")
                                {
                                    cout<<"The Letter subcomponent declared on line "<<rowIndex+1<<" does not contain a valid letter. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                if(!(Letters[lungimeLitere].ColtStangaSus.x!=-1&&Letters[lungimeLitere].ColtStangaSus.y!=-1))
                                {
                                    cout<<"The Letter subcomponent declared on line "<<rowIndex+1<<" does not contain a valid top left point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                else
                                {
                                    Letters[lungimeLitere].ColtStangaSus.x=Letters[lungimeLitere].ColtStangaSus.x-gridWidth/2.00;
                                    Letters[lungimeLitere].ColtStangaSus.y=Letters[lungimeLitere].ColtStangaSus.y-gridHeight/2.00;
                                    Letters[lungimeLitere].initializeFont();
                                    lungimeLitere++;
                                }
                            }
                            else
                            {
                                strcpy(row, row+1);
                                Lines[lungimeLinii].read(row,rowIndex);
                                if(!(Lines[lungimeLinii].p1.x!=-1&&Lines[lungimeLinii].p1.y!=-1))
                                {
                                    cout<<"The Line subcomponent declared on line "<<rowIndex+1<< " does not contain a valid first point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                else if(!(Lines[lungimeLinii].p2.x!=-1&&Lines[lungimeLinii].p2.y!=-1))
                                {
                                    cout<<"The Line subcomponent declared on line "<<rowIndex+1<< " does not contain a valid second point. Please follow the component file structure example located in the exampleComponent.txt file."<<endl;
                                    exit(1);
                                }
                                else
                                {
                                    Lines[lungimeLinii].p1.x=Lines[lungimeLinii].p1.x-gridWidth/2.00;
                                    Lines[lungimeLinii].p1.y=Lines[lungimeLinii].p1.y-gridHeight/2.00;
                                    Lines[lungimeLinii].p2.x=Lines[lungimeLinii].p2.x-gridWidth/2.00;
                                    Lines[lungimeLinii].p2.y=Lines[lungimeLinii].p2.y-gridHeight/2.00;
                                    lungimeLinii++;
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
        fread(&tipComponent,sizeof(int),1,file);

        fread(&id,sizeof(int),1,file);

        fread(&gradeRotire,sizeof(int),1,file);
        fread(&scaledAt,sizeof(float),1,file);

        fread(&LungimeInputPoints,sizeof(int),1,file);
        fread(&LungimeOutputPoints,sizeof(int),1,file);

        ColtStangaSus.open(file);


        for(int i=0; i<LungimeInputPoints; i++)
        {
            inputPoints[i].open(file);
        }

        for(int i=0; i<LungimeOutputPoints; i++)
        {
            outputPoints[i].open(file);
        }

        fread(&lungimeCercuri,sizeof(int),1,file);

        for(int i=0; i<lungimeCercuri; i++)
        {
            Cercuri[i].open(file);
        }

        fread(&lungimeLitere,sizeof(int),1,file);

        for(int i=0; i<lungimeLitere; i++)
        {
            Letters[i].open(file);
        }

        fread(&LungimeDreptunghiuri,sizeof(int),1,file);
        for(int i=0; i<LungimeDreptunghiuri; i++)
        {
            Rectangles[i].open(file);
        }

        fread(&lungimeLinii,sizeof(int),1,file);
        for(int i=0; i<lungimeLinii; i++)
        {
            Lines[i].open(file);
        }
        fread(&name2,sizeof(char),25,file);
        name=name2;
        fread(&R,sizeof(float),1,file);
        fread(&V,sizeof(float),1,file);
    }

    void salveazaComponent(FILE *file)
    {

        fwrite(&gridWidth,sizeof(int),1,file);
        fwrite(&gridHeight,sizeof(int),1,file);
        fwrite(&tipComponent,sizeof(int),1,file);

        fwrite(&id,sizeof(int),1,file);

        fwrite(&gradeRotire,sizeof(int),1,file);
        fwrite(&scaledAt,sizeof(float),1,file);

        fwrite(&LungimeInputPoints,sizeof(int),1,file);
        fwrite(&LungimeOutputPoints,sizeof(int),1,file);

        ColtStangaSus.save(file);


        for(int i=0; i<LungimeInputPoints; i++)
        {
            inputPoints[i].save(file);
        }

        for(int i=0; i<LungimeOutputPoints; i++)
        {
            outputPoints[i].save(file);
        }

        fwrite(&lungimeCercuri,sizeof(int),1,file);

        for(int i=0; i<lungimeCercuri; i++)
        {
            Cercuri[i].save(file);
        }

        fwrite(&lungimeLitere,sizeof(int),1,file);

        for(int i=0; i<lungimeLitere; i++)
        {
            Letters[i].save(file);
        }

        fwrite(&LungimeDreptunghiuri,sizeof(int),1,file);
        for(int i=0; i<LungimeDreptunghiuri; i++)
        {
            Rectangles[i].save(file);
        }

        fwrite(&lungimeLinii,sizeof(int),1,file);
        for(int i=0; i<lungimeLinii; i++)
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
        gradeRotire=ang;
        for(int i=0; i<LungimeInputPoints; i++)
            inputPoints[i].rotatePoint(ang);
        for(int i=0; i<LungimeOutputPoints; i++)
            outputPoints[i].rotatePoint(ang);
        for(int i=0; i<lungimeLinii; i++)
        {
            Lines[i].p1.rotatePoint(ang);
            Lines[i].p2.rotatePoint(ang);
        }
        for(int i=0; i<lungimeCercuri; i++)
        {
            Cercuri[i].ColtStangaSus.rotatePoint(ang);
        }
        for(int i=0; i<lungimeLitere; i++)
        {
            Letters[i].ColtStangaSus.rotatePoint(ang);
        }
        for(int i=0; i<LungimeDreptunghiuri; i++)
        {
            Rectangles[i].ColtStangaSus.rotatePoint(ang);
        }

    }

    void scaleComponent(float scale)
    {
        scaledAt=scale;
        for(int i=0; i<LungimeInputPoints; i++)
            inputPoints[i].scalePoint(scale);
        for(int i=0; i<LungimeOutputPoints; i++)
            outputPoints[i].scalePoint(scale);
        for(int i=0; i<lungimeLinii; i++)
        {
            Lines[i].p1.scalePoint(scale);
            Lines[i].p2.scalePoint(scale);
        }
        for(int i=0; i<lungimeCercuri; i++)
        {
            Cercuri[i].ColtStangaSus.scalePoint(scale);
        }
        for(int i=0; i<lungimeLitere; i++)
        {
            Letters[i].ColtStangaSus.scalePoint(scale);
        }
        for(int i=0; i<LungimeDreptunghiuri; i++)
        {
            Rectangles[i].ColtStangaSus.scalePoint(scale);
        }
    }
///Let s see.
    void draw(sf::RenderWindow &win)
    {
        if(isDeleted==false)
        {
            if(selected==true)
            {
                sf::RectangleShape grid(sf::Vector2f(gridWidth,gridHeight));
                grid.setPosition(ColtStangaSus.x,ColtStangaSus.y);
                grid.setOrigin(gridWidth/2,gridHeight/2);
                grid.setFillColor(sf::Color::Transparent);
                grid.setOutlineColor(sf::Color(204, 0, 0));
                grid.rotate(gradeRotire);
                grid.setScale(sf::Vector2f(scaledAt,scaledAt));
                grid.setOutlineThickness(2);
                win.draw(grid);
            }

           for(int i=0; i<LungimeInputPoints; i++)
            {
                inputPoints[i].draw(ColtStangaSus,win);
            }

            for(int i=0; i<LungimeOutputPoints; i++)
            {
                outputPoints[i].draw(ColtStangaSus,win);
            }

            for(int i=0; i<lungimeCercuri; i++)
            {
                Cercuri[i].draw(ColtStangaSus,gradeRotire,scaledAt,win);
            }
            for(int i=0; i<lungimeLitere; i++)
            {
                Letters[i].draw(ColtStangaSus,gradeRotire,scaledAt,win);
            }
            for(int i=0; i<LungimeDreptunghiuri; i++)
            {
                Rectangles[i].draw(ColtStangaSus,gradeRotire,scaledAt,win);
            }
            for(int i=0; i<lungimeLinii; i++)
            {
                Lines[i].draw(ColtStangaSus,win);
            }
        }
    }

    void initializeFont()
    {
        for(int i=0; i<lungimeLitere; i++)
        {
            Letters[i].initializeFont();
        }
    }

    bool mouseOn(int mouseX, int mouseY)
    {
        if(isDeleted==true)
            return false;
        sf::RectangleShape grid(sf::Vector2f(gridWidth,gridHeight));
        grid.setPosition(ColtStangaSus.x,ColtStangaSus.y);
        grid.setOrigin(gridWidth/2,gridHeight/2);
        grid.setFillColor(sf::Color::Transparent);
        grid.setOutlineColor(sf::Color::Transparent);
        grid.setOutlineThickness(1);
        grid.rotate(gradeRotire);
        grid.setScale(sf::Vector2f(scaledAt,scaledAt));

        sf::Vector2f topLeft = grid.getTransform().transformPoint(sf::Vector2f(0,0));
        sf::Vector2f topRight = grid.getTransform().transformPoint(sf::Vector2f(grid.getSize().x,0));
        sf::Vector2f bottomLeft = grid.getTransform().transformPoint(sf::Vector2f(0,grid.getSize().y));
        sf::Vector2f bottomRight = grid.getTransform().transformPoint(sf::Vector2f(grid.getSize().x,grid.getSize().y));

        if((topLeft.x - topRight.x) * (mouseY - topRight.y) - (mouseX - topRight.x) * (topLeft.y - topRight.y)<=0&&
                (topRight.x - bottomRight.x) * (mouseY -bottomRight.y) - (mouseX - bottomRight.x) * (topRight.y - bottomRight.y)<=0&&
                (bottomRight.x - bottomLeft.x) * (mouseY -bottomLeft.y) - (mouseX - bottomLeft.x) * (bottomRight.y - bottomLeft.y)<=0&&
                (bottomLeft.x - topLeft.x) * (mouseY -topLeft.y) - (mouseX - topLeft.x) * (bottomLeft.y - topLeft.y)<=0)
            return true;
        return false;
    }

    int isOnAnyOutputPoints(int mouseX,int mouseY)
    {
        for(int i=0; i<LungimeOutputPoints; i++)
        {
            if(outputPoints[i].mouseOn(ColtStangaSus,mouseX,mouseY)==true)
            {
                return i;
            }
        }
        return -1;
    }

    int isOnAnyInputPoints(int mouseX,int mouseY)
    {
        for(int i=0; i<LungimeInputPoints; i++)
        {
            if(inputPoints[i].mouseOn(ColtStangaSus,mouseX,mouseY)==true)
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
    int lungimeConexiuni=0;
    ConnectionSubComponent Connections[100];
    int actionsLength=0,currentIndexAction=-1;
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

    int oldOutputIDComponent=-1;
    int oldComponentOutputPointIndex=-1;

    int oldInputIDComponent=-1;
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
        fread(&lungimeConexiuni, sizeof(int), 1, fileToRead);
        fread(&Connections, sizeof(ConnectionSubComponent), lungimeConexiuni, fileToRead);

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
            Components[i].salveazaComponent(fileToWrite);
        }
        fwrite(&lungimeConexiuni, sizeof(int), 1, fileToWrite);
        fwrite(&Connections, sizeof(ConnectionSubComponent), lungimeConexiuni, fileToWrite);

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
        ofn.hwndOwner    = NULL;
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
        float W = sf::VideoMode::getDesktopMode().width - 100;
        float H = sf::VideoMode::getDesktopMode().height - 100;
        float gridWidth = Components[currentSelectedComponent].gridWidth;
        float gridHeight = Components[currentSelectedComponent].gridHeight;
        ///
        float scaleAt =Components[currentSelectedComponent].scaledAt;
        if(!(x>=255.0f + gridWidth/2*scaleAt && x<=W-207.0f - gridWidth/2*scaleAt && y >=155.0f + gridHeight/2*scaleAt && y<=H-55.0f - gridHeight/2*scaleAt))
            return;

        Components[componentsLength].tipComponent=cType;
        Components[componentsLength].id=componentsLength;
        Components[componentsLength].ColtStangaSus.x=x;
        Components[componentsLength].ColtStangaSus.y=y;
        Components[componentsLength].read();
        currentSelectedComponent=componentsLength;
        Components[componentsLength].selected=true;

        Actions[currentIndexAction + 1].type = "COMPONENT_ADDED";
        Actions[currentIndexAction + 1].componentId = componentsLength;
        currentIndexAction++;
        clearExtraComponentsOrConnections(currentIndexAction);
        justAddedAComponent=true;

        componentsLength++;

    }

    void deleteElement()
    {
        if(currentSelectedComponent!=-1)
        {
            Components[currentSelectedComponent].isDeleted=true;
            Components[currentSelectedComponent].selected=false;
            Actions[currentIndexAction + 1].type = "COMPONENT_DELETED";
            Actions[currentIndexAction + 1].componentId = currentSelectedComponent;
            currentIndexAction++;
            clearExtraComponentsOrConnections(currentIndexAction);
            currentSelectedComponent = -1;
        }
    }

    void undoAction()
    {
        unsetCurrentSelectedComponent();
        if(currentIndexAction>-1)
        {
            if(Actions[currentIndexAction].type=="COMPONENT_MOVED")
            {
                Components[Actions[currentIndexAction].componentId].ColtStangaSus.x=Actions[currentIndexAction].previousComponentColtStangaSus.x;
                Components[Actions[currentIndexAction].componentId].ColtStangaSus.y=Actions[currentIndexAction].previousComponentColtStangaSus.y;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="COMPONENT_ADDED")
            {
                Components[Actions[currentIndexAction].componentId].isDeleted=true;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="COMPONENT_DELETED")
            {
                Components[Actions[currentIndexAction].componentId].isDeleted=false;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="COMPONENT_ROTATED")
            {
                cout<<Actions[currentIndexAction].componentId<<" "<<currentIndexAction<<endl;
                Components[Actions[currentIndexAction].componentId].rotateComponent(Actions[currentIndexAction].lastGradeRotire);
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="COMPONENT_SCALED")
            {
                cout<<Actions[currentIndexAction].componentId<<" "<<currentIndexAction<<endl;
                Components[Actions[currentIndexAction].componentId].scaleComponent(Actions[currentIndexAction].lastGradeRotire);
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="CONNECTION_DELETED")
            {
                Connections[Actions[currentIndexAction].connectionId].isDeleted=false;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="CONNECTION_ADDED")
            {
                Connections[Actions[currentIndexAction].connectionId].isDeleted=true;
            }
            else if(Actions[currentIndexAction].type=="CONNECTION_CHANGED_INPUT")
            {
                Connections[Actions[currentIndexAction].connectionId].InputIDComponent=Actions[currentIndexAction].oldComponentId;
                Connections[Actions[currentIndexAction].connectionId].componentInputPointIndex=Actions[currentIndexAction].oldPointIndex;
                modifyCertainComponentConnections(Actions[currentIndexAction].oldComponentId);
            }
            else if(Actions[currentIndexAction].type=="CONNECTION_CHANGED_OUTPUT")
            {
                Connections[Actions[currentIndexAction].connectionId].OutputIDComponent=Actions[currentIndexAction].oldComponentId;
                Connections[Actions[currentIndexAction].connectionId].componentOutputPointIndex=Actions[currentIndexAction].oldPointIndex;
                modifyCertainComponentConnections(Actions[currentIndexAction].oldComponentId);
            }
            currentIndexAction--;
        }
    }

    void refaActiunea()
    {
        unsetCurrentSelectedComponent();
        if(currentIndexAction+1<actionsLength)
        {
            currentIndexAction++;
            if(Actions[currentIndexAction].type=="COMPONENT_MOVED")
            {
                Components[Actions[currentIndexAction].componentId].ColtStangaSus.x=Actions[currentIndexAction].usedComponentNewColtStangaSus.x;
                Components[Actions[currentIndexAction].componentId].ColtStangaSus.y=Actions[currentIndexAction].usedComponentNewColtStangaSus.y;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="COMPONENT_ADDED")
            {
                Components[Actions[currentIndexAction].componentId].isDeleted=false;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="COMPONENT_DELETED")
            {
                Components[Actions[currentIndexAction].componentId].isDeleted=true;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="COMPONENT_ROTATED")
            {
                Components[Actions[currentIndexAction].componentId].rotateComponent(Actions[currentIndexAction].rotatedAt);
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="COMPONENT_SCALED")
            {
                Components[Actions[currentIndexAction].componentId].scaleComponent(Actions[currentIndexAction].scaledAt);
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="CONNECTION_DELETED")
            {
                Connections[Actions[currentIndexAction].connectionId].isDeleted=true;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="CONNECTION_ADDED")
            {
                Connections[Actions[currentIndexAction].connectionId].isDeleted=false;
            }
            else if(Actions[currentIndexAction].type=="CONNECTION_CHANGED_INPUT")
            {
                Connections[Actions[currentIndexAction].connectionId].InputIDComponent=Actions[currentIndexAction].componentId;
                Connections[Actions[currentIndexAction].connectionId].componentInputPointIndex=Actions[currentIndexAction].pointIndex;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
            else if(Actions[currentIndexAction].type=="CONNECTION_CHANGED_OUTPUT")
            {
                Connections[Actions[currentIndexAction].connectionId].OutputIDComponent=Actions[currentIndexAction].componentId;
                Connections[Actions[currentIndexAction].connectionId].componentOutputPointIndex=Actions[currentIndexAction].pointIndex;
                modifyCertainComponentConnections(Actions[currentIndexAction].componentId);
            }
        }
    }
    void reset()
    {
        for(int i = 0; i < componentsLength; ++i)
            Components[i] = Component();
        componentsLength=0;

        for(int i = 0; i < lungimeConexiuni; ++i)
            Connections[i] = ConnectionSubComponent();
        lungimeConexiuni=0;

        for(int i = 0; i < actionsLength; ++i)
            Actions[i] = Action();
        actionsLength=0,currentIndexAction=-1;
        currentSelectedComponent=-1;
        currentSelectedConnection=-1;
        isMouseLongPressed = false;
        isInputConnectionSelected = false, isOutputConnectionSelected = false;


        mouseLongPressXDiff = 0, mouseLongPressYDiff = 0;

///Take care initializare!!!
        justAddedAComponent=false;
        isModalClosed=true;
        isASliderSelected=0;
        isMessageModalClosed=true;

        oldOutputIDComponent=-1;
        oldComponentOutputPointIndex=-1;

        oldInputIDComponent=-1;
        oldComponentInputPointIndex=-1;

        isFromExistingConnection=false;
        toEditComponentId=-1;
    }

    void addRotationAction()
    {
        if(currentSelectedComponent!=-1)
        {
            if(Actions[currentIndexAction+1].lastGradeRotire!=Components[currentSelectedComponent].gradeRotire)
            {
                currentIndexAction++;
                Actions[currentIndexAction].type="COMPONENT_ROTATED";
                Actions[currentIndexAction].rotatedAt=Components[currentSelectedComponent].gradeRotire;
                Actions[currentIndexAction].componentId=currentSelectedComponent;
                cout<<currentSelectedComponent<<" "<<Actions[currentIndexAction].componentId<<" "<<currentIndexAction<<endl;
                clearExtraComponentsOrConnections(currentIndexAction);
            }
        }
    }

    void addScaleAction()
    {
        if(currentSelectedComponent!=-1)
        {
            if(Actions[currentIndexAction+1].lastGradeRotire!=Components[currentSelectedComponent].scaledAt)
            {
                currentIndexAction++;
                Actions[currentIndexAction].type="COMPONENT_SCALED";
                Actions[currentIndexAction].scaledAt=Components[currentSelectedComponent].scaledAt;
                Actions[currentIndexAction].componentId=currentSelectedComponent;
                cout<<currentSelectedComponent<<" "<<Actions[currentIndexAction].componentId<<" "<<currentIndexAction<<endl;
                clearExtraComponentsOrConnections(currentIndexAction);
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
            Connections[lungimeConexiuni].PointInceput.x=Components[selectedComponentIndex].outputPoints[selectedIOIndex].x+Components[selectedComponentIndex].ColtStangaSus.x;
            Connections[lungimeConexiuni].PointInceput.y=Components[selectedComponentIndex].outputPoints[selectedIOIndex].y+Components[selectedComponentIndex].ColtStangaSus.y;
            Connections[lungimeConexiuni].PointSfarsit.x=mouseX;
            Connections[lungimeConexiuni].PointSfarsit.y=mouseY;
            Connections[lungimeConexiuni].OutputIDComponent=selectedComponentIndex;
            Connections[lungimeConexiuni].componentOutputPointIndex=selectedIOIndex;
            currentSelectedConnection=lungimeConexiuni;
            lungimeConexiuni++;

        }
        else
        {
            Connections[lungimeConexiuni].PointInceput.x=mouseX;
            Connections[lungimeConexiuni].PointInceput.y=mouseY;
            Connections[lungimeConexiuni].PointSfarsit.x=Components[selectedComponentIndex].inputPoints[selectedIOIndex].x+Components[selectedComponentIndex].ColtStangaSus.x;
            Connections[lungimeConexiuni].PointSfarsit.y=Components[selectedComponentIndex].inputPoints[selectedIOIndex].y+Components[selectedComponentIndex].ColtStangaSus.y;
            Connections[lungimeConexiuni].InputIDComponent=selectedComponentIndex;
            Connections[lungimeConexiuni].componentInputPointIndex=selectedIOIndex;
            currentSelectedConnection=lungimeConexiuni;
            lungimeConexiuni++;
        }

    }

    void modifyComponentConnections()
    {
        for (int i=0; i<lungimeConexiuni; i++)
        {
            if(Connections[i].OutputIDComponent==currentSelectedComponent||currentSelectedComponent==-1)
            {
                Connections[i].PointInceput.x=Components[currentSelectedComponent].outputPoints[Connections[i].componentOutputPointIndex].x+Components[currentSelectedComponent].ColtStangaSus.x;
                Connections[i].PointInceput.y=Components[currentSelectedComponent].outputPoints[Connections[i].componentOutputPointIndex].y+Components[currentSelectedComponent].ColtStangaSus.y;
            }
            if(Connections[i].InputIDComponent==currentSelectedComponent||currentSelectedComponent==-1)
            {
                Connections[i].PointSfarsit.x=Components[currentSelectedComponent].inputPoints[Connections[i].componentInputPointIndex].x+Components[currentSelectedComponent].ColtStangaSus.x;
                Connections[i].PointSfarsit.y=Components[currentSelectedComponent].inputPoints[Connections[i].componentInputPointIndex].y+Components[currentSelectedComponent].ColtStangaSus.y;
            }
        }
    }

    void modifyCertainComponentConnections(int id)
    {
        for (int i=0; i<lungimeConexiuni; i++)
        {
            if(Connections[i].OutputIDComponent==id)
            {
                Connections[i].PointInceput.x=Components[id].outputPoints[Connections[i].componentOutputPointIndex].x+Components[id].ColtStangaSus.x;
                Connections[i].PointInceput.y=Components[id].outputPoints[Connections[i].componentOutputPointIndex].y+Components[id].ColtStangaSus.y;
            }
            if(Connections[i].InputIDComponent==id)
            {
                Connections[i].PointSfarsit.x=Components[id].inputPoints[Connections[i].componentInputPointIndex].x+Components[id].ColtStangaSus.x;
                Connections[i].PointSfarsit.y=Components[id].inputPoints[Connections[i].componentInputPointIndex].y+Components[id].ColtStangaSus.y;
            }
        }
    }


    void addSecondConnectionPoint(int selectedComponentIndex,int selectedIOIndex,int selectedPointType)
    {
        if(selectedPointType==1)
        {
            Connections[currentSelectedConnection].PointInceput.x=Components[selectedComponentIndex].outputPoints[selectedIOIndex].x+Components[selectedComponentIndex].ColtStangaSus.x;
            Connections[currentSelectedConnection].PointInceput.y=Components[selectedComponentIndex].outputPoints[selectedIOIndex].y+Components[selectedComponentIndex].ColtStangaSus.y;
            Connections[currentSelectedConnection].OutputIDComponent=selectedComponentIndex;
            Connections[currentSelectedConnection].componentOutputPointIndex=selectedIOIndex;
        }
        else
        {
            Connections[currentSelectedConnection].PointSfarsit.x=Components[selectedComponentIndex].inputPoints[selectedIOIndex].x+Components[selectedComponentIndex].ColtStangaSus.x;
            Connections[currentSelectedConnection].PointSfarsit.y=Components[selectedComponentIndex].inputPoints[selectedIOIndex].y+Components[selectedComponentIndex].ColtStangaSus.y;
            Connections[currentSelectedConnection].InputIDComponent=selectedComponentIndex;
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
                mouseLongPressXDiff=mouseX-Components[i].ColtStangaSus.x;
                mouseLongPressYDiff=mouseY-Components[i].ColtStangaSus.y;

                if(currentSelectedComponent!=-1&&currentSelectedComponent!=i)
                {
                    Components[currentSelectedComponent].selected=false;
                }

                Actions[currentIndexAction+1].previousComponentColtStangaSus.x=Components[currentSelectedComponent].ColtStangaSus.x;
                Actions[currentIndexAction+1].previousComponentColtStangaSus.y=Components[currentSelectedComponent].ColtStangaSus.y;
                Actions[currentIndexAction+1].lastGradeRotire=Components[currentSelectedComponent].gradeRotire;
                Actions[currentIndexAction+1].lastGradeRotire=Components[currentSelectedComponent].scaledAt;
                Actions[currentIndexAction+1].componentId=currentSelectedComponent;


                int selectedInputPointIndex=Components[i].isOnAnyInputPoints(mouseX,mouseY);
                if(selectedInputPointIndex!=-1)
                {

                    bool isAlreadyConnected=false;
                    for(int j=0; j<=lungimeConexiuni; j++)
                        if(Connections[j].isDeleted==false&&Connections[j].OutputIDComponent!=-1&&Connections[j].OutputIDComponent!=i&&selectedInputPointIndex==Connections[j].componentInputPointIndex&&Connections[j].InputIDComponent==i)
                        {
                            currentSelectedConnection=j;
                            Connections[j].PointSfarsit.x=mouseX;
                            Connections[j].PointSfarsit.y=mouseY;

                            oldInputIDComponent=Connections[j].InputIDComponent;
                            oldComponentInputPointIndex=Connections[j].componentInputPointIndex;

                            Connections[j].InputIDComponent=-1;
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
                        for(int j=0; j<=lungimeConexiuni; j++)
                            if(Connections[j].isDeleted==false&&Connections[j].InputIDComponent!=-1&&Connections[j].InputIDComponent!=i&&selectedOutputPointIndex==Connections[j].componentOutputPointIndex&&Connections[j].OutputIDComponent==i)
                            {
                                currentSelectedConnection=j;
                                Connections[j].PointInceput.x=mouseX;
                                Connections[j].PointInceput.y=mouseY;

                                oldOutputIDComponent=Connections[j].OutputIDComponent;
                                oldComponentOutputPointIndex=Connections[j].componentOutputPointIndex;

                                Connections[j].OutputIDComponent=-1;
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

                float W = sf::VideoMode::getDesktopMode().width - 100;
                float H = sf::VideoMode::getDesktopMode().height - 100;
                float rectWidth = Components[currentSelectedComponent].gridWidth;
                float rectHeight = Components[currentSelectedComponent].gridHeight;
                float scaleAt = Components[currentSelectedComponent].scaledAt;
                float angleAt = Components[currentSelectedComponent].gradeRotire*1.0f;

                Point ColtStangaSus = Components[currentSelectedComponent].ColtStangaSus;
                sf::RectangleShape grid(sf::Vector2f(rectWidth,rectHeight));
                grid.setPosition(ColtStangaSus.x,ColtStangaSus.y);
                grid.setOrigin(rectWidth/2,rectHeight/2);
                grid.rotate(angleAt);
                grid.setScale(sf::Vector2f(scaleAt,scaleAt));


                float gridWidth  = grid.getGlobalBounds().width;
                float gridHeight = grid.getGlobalBounds().height;
                float gridX = grid.getGlobalBounds().left + gridWidth/2;
                float gridY = grid.getGlobalBounds().top  + gridHeight/2;

                sf::Vector2f coordMe = {mouseX-mouseLongPressXDiff, mouseY-mouseLongPressYDiff};
                coordMe.x = max(coordMe.x,   255.0f + gridWidth/2);
                coordMe.x = min(coordMe.x, W-207.0f - gridWidth/2);
                coordMe.y = max(coordMe.y,   155.0f + gridHeight/2);
                coordMe.y = min(coordMe.y, H-55.0f  - gridHeight/2);

                for(int index = 0; index < componentsLength; ++index)
                {
                    if(index != currentSelectedComponent)
                    {
                        float currentWidthTmp  = Components[index].gridWidth;
                        float currentHeightTmp = Components[index].gridHeight;
                        float scaleAt = Components[index].scaledAt;
                        float angleAt = Components[index].gradeRotire*1.0f;

                        Point ColtStangaSus = Components[index].ColtStangaSus;
                        sf::RectangleShape currentGrid(sf::Vector2f(currentWidthTmp,currentHeightTmp));
                        currentGrid.setPosition(ColtStangaSus.x,ColtStangaSus.y);
                        currentGrid.setOrigin(currentWidthTmp/2,currentHeightTmp/2);
                        currentGrid.rotate(angleAt);
                        currentGrid.setScale(sf::Vector2f(scaleAt,scaleAt));

                        float currentWidth  = currentGrid.getGlobalBounds().width;
                        float currentHeight = currentGrid.getGlobalBounds().height;
                        float currentX = currentGrid.getGlobalBounds().left + currentWidth/2;
                        float currentY = currentGrid.getGlobalBounds().top  + currentHeight/2;

                        sf::Vector2f var = coordMe;
                        sf::Vector2f delta(gridWidth + currentWidth, gridHeight + currentHeight);

                        if(coordMe.x > currentX) {
                            var.x = max(coordMe.x, currentX + delta.x/2);
                        }
                        else {
                            var.x = min(coordMe.x, currentX - delta.x/2);
                        }
                        if(coordMe.y > currentY) {
                            var.y = max(coordMe.y, currentY + delta.y/2);
                        }
                        else {
                            var.y = min(coordMe.y, currentY - delta.y/2);
                        }

                        if(fabs(var.x - coordMe.x) * delta.y < fabs(var.y - coordMe.y) * delta.x) {
                            coordMe.x = var.x;
                        }
                        else {
                            coordMe.y = var.y;
                        }
                    }
                }

                Components[currentSelectedComponent].ColtStangaSus.x = coordMe.x;
                Components[currentSelectedComponent].ColtStangaSus.y = coordMe.y;
                modifyComponentConnections();
            }
            else if(currentSelectedConnection!=-1)
            {
                if(isInputConnectionSelected==true)
                {
                    Connections[currentSelectedConnection].PointInceput.x=mouseX;
                    Connections[currentSelectedConnection].PointInceput.y=mouseY;
                }
                else if(isOutputConnectionSelected==true)
                {
                    Connections[currentSelectedConnection].PointSfarsit.x=mouseX;
                    Connections[currentSelectedConnection].PointSfarsit.y=mouseY;
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
                    if(selectedOutputPointIndex!=-1&&i!=Connections[currentSelectedConnection].InputIDComponent)
                    {
                        addSecondConnectionPoint(i,selectedOutputPointIndex,1);
                        hasFoundAComponent=true;

                    if(oldOutputIDComponent!=i)
                    {
                        if(isFromExistingConnection==false)
                        {
                            currentIndexAction++;
                            Actions[currentIndexAction].type="CONNECTION_ADDED";
                            Actions[currentIndexAction].connectionId=currentSelectedConnection;
                            clearExtraComponentsOrConnections(currentIndexAction);
                        }
                        else
                        {
                            currentIndexAction++;
                            Actions[currentIndexAction].type="CONNECTION_CHANGED_OUTPUT";
                            Actions[currentIndexAction].oldComponentId=oldOutputIDComponent;
                            Actions[currentIndexAction].oldPointIndex=oldComponentOutputPointIndex;
                            Actions[currentIndexAction].componentId=i;
                            Actions[currentIndexAction].pointIndex=selectedOutputPointIndex;

                            Actions[currentIndexAction].connectionId=currentSelectedConnection;
                            clearExtraComponentsOrConnections(currentIndexAction);
                        }
                    }
                }
            }
            if(hasFoundAComponent==false)
            {
                Connections[currentSelectedConnection].OutputIDComponent=oldOutputIDComponent;
                Connections[currentSelectedConnection].componentOutputPointIndex=oldComponentOutputPointIndex;
                Connections[currentSelectedConnection].isDeleted=true;

                currentIndexAction++;
                Actions[currentIndexAction].type="CONNECTION_DELETED";
                Actions[currentIndexAction].componentId=oldOutputIDComponent;
                Actions[currentIndexAction].connectionId=currentSelectedConnection;
                clearExtraComponentsOrConnections(currentIndexAction);
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
                    if(selectedInputPointIndex!=-1&&i!=Connections[currentSelectedConnection].OutputIDComponent)
                    {
                        addSecondConnectionPoint(i,selectedInputPointIndex,0);
                        hasFoundAComponent=true;

                        if(isFromExistingConnection==false)
                        {
                            currentIndexAction++;
                            Actions[currentIndexAction].type="CONNECTION_ADDED";
                            Actions[currentIndexAction].connectionId=currentSelectedConnection;
                            clearExtraComponentsOrConnections(currentIndexAction);
                        }
                        else
                        {
                            currentIndexAction++;
                            Actions[currentIndexAction].type="CONNECTION_CHANGED_INPUT";
                            Actions[currentIndexAction].oldComponentId=oldInputIDComponent;
                            Actions[currentIndexAction].oldPointIndex=oldComponentInputPointIndex;
                            Actions[currentIndexAction].componentId=i;
                            Actions[currentIndexAction].pointIndex=selectedInputPointIndex;

                            Actions[currentIndexAction].connectionId=currentSelectedConnection;
                            clearExtraComponentsOrConnections(currentIndexAction);
                        }
                    }
                }
            if(hasFoundAComponent==false)
            {
                Connections[currentSelectedConnection].InputIDComponent=oldInputIDComponent;
                Connections[currentSelectedConnection].componentInputPointIndex=oldComponentInputPointIndex;
                Connections[currentSelectedConnection].isDeleted=true;

                currentIndexAction++;
                Actions[currentIndexAction].componentId=oldInputIDComponent;
                Actions[currentIndexAction].type="CONNECTION_DELETED";
                Actions[currentIndexAction].connectionId=currentSelectedConnection;
                clearExtraComponentsOrConnections(currentIndexAction);
            }
            currentSelectedConnection=-1;
            isOutputConnectionSelected=false;
        }
        else if(currentSelectedComponent!=-1&&justAddedAComponent==false)
        {
            if(isASliderSelected==0)
                if(mouseX-mouseLongPressXDiff!=Actions[currentIndexAction+1].previousComponentColtStangaSus.x||mouseY-mouseLongPressYDiff!=Actions[currentIndexAction+1].previousComponentColtStangaSus.y&&isASliderSelected==0)
                {
                    currentIndexAction++;
                    Actions[currentIndexAction].type="COMPONENT_MOVED";
                    Actions[currentIndexAction].usedComponentNewColtStangaSus.x=mouseX;
                    Actions[currentIndexAction].usedComponentNewColtStangaSus.y=mouseY;
                    Actions[currentIndexAction].componentId=currentSelectedComponent;
                    clearExtraComponentsOrConnections(currentIndexAction);
                }
            Actions[currentIndexAction+1].previousComponentColtStangaSus.x=Components[currentSelectedComponent].ColtStangaSus.x;
            Actions[currentIndexAction+1].previousComponentColtStangaSus.y=Components[currentSelectedComponent].ColtStangaSus.y;
            Actions[currentIndexAction+1].lastGradeRotire=Components[currentSelectedComponent].gradeRotire;
            Actions[currentIndexAction+1].lastGradeRotire=Components[currentSelectedComponent].scaledAt;
        }
        justAddedAComponent=false;
        oldInputIDComponent=-1;
        oldOutputIDComponent=-1;
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
        for(int i=0; i<lungimeConexiuni; i++)
        {
            if(Components[Connections[i].InputIDComponent].isDeleted==false&&Components[Connections[i].OutputIDComponent].isDeleted==false)
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
        modalEditorTitle.setString("Parametri");
        modalEditorTitle.setColor(sf::Color::White);
        modalEditorTitle.setPosition(x + 200 - modalEditorTitle.getGlobalBounds().width/2, y + 10);

        modalExit.setSize(sf::Vector2f(120, 40));
        modalExit.setFillColor(sf::Color::Transparent);
        modalExit.setOutlineColor(sf::Color::White);
        modalExit.setOutlineThickness(3);
        modalExit.setPosition(sf::Vector2f(x + 400 - 33 - 150, y + 225));
        modalExitText.setFont(font);
        modalExitText.setPosition(x + 400 - 26 - 150, y + 225);
        modalExitText.setString("Anuleaza");
        modalExitText.setColor(sf::Color::White);

        modalEdit.setSize(sf::Vector2f(120, 40));
        modalEdit.setFillColor(sf::Color::Transparent);
        modalEdit.setOutlineColor(sf::Color::White);
        modalEdit.setOutlineThickness(3);
        modalEdit.setPosition(sf::Vector2f(x + 200 - 48 - 80, y + 225));
        modalEditText.setFont(font);
        modalEditText.setString("Editeaza");
        modalEditText.setPosition(x + 200 - modalEditText.getGlobalBounds().width/2 - 70, y + 225);
        modalEditText.setColor(sf::Color::White);


        modalName.setUp(25, sf::Color::White, false, "Nume");
        modalName.setFont(font);
        modalName.seteazaLimita(10);
        modalName.setPosition(sf::Vector2f(x + 200, y + 80));

        modalRezistenta.setUp(25, sf::Color::White, false, "Rezistenta");
        modalRezistenta.setFont(font);
        modalRezistenta.setFloat(1.23);
        modalRezistenta.seteazaLimita(10);
        modalRezistenta.setPosition(sf::Vector2f(x + 200, y + 120));

        modalVoltaj.setUp(25, sf::Color::White, false, "Voltaj");
        modalVoltaj.setFont(font);
        modalVoltaj.setFloat(2.0);
        modalVoltaj.seteazaLimita(10);
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
        modalExit.setPosition(sf::Vector2f(x + 400 - 33 - 150, y + 225));

        modalExitText.setPosition(x + 400 - 26 - 150, y + 225);

        modalEdit.setPosition(sf::Vector2f(x + 200 - 48 - 80, y + 225));
        modalEditText.setPosition(x + 200 - modalEditText.getGlobalBounds().width/2 - 70, y + 225);

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



