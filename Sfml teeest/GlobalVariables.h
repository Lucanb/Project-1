#include <bits/stdc++.h>
#define MAX_INPUT_POINTS 5
#define MAX_OUTPUT_POINTS 5
#define MAX_ROW_SIZE 50
#define MAX_SPACING_ROWS 3
#define PI 3.14159265
#define POINT_CIRCLE_RADIUS 4

struct ComponentType
{
    std::string filePath;
};

struct ActionType{
    int id;
    std::string identifier;
};

ComponentType ComponentTypes[13];

void initializeComponentTypes()
{
    ComponentTypes[0].filePath="components/ElectricalCell.txt";
    ComponentTypes[1].filePath="components/Resistor.txt";
    ComponentTypes[2].filePath="components/Bulb.txt";
    ComponentTypes[3].filePath="components/Diode.txt";
    ComponentTypes[4].filePath="components/Ammeter.txt";
    ComponentTypes[5].filePath="components/Voltmeter.txt";
    ComponentTypes[6].filePath="components/Capacitor.txt";
    ComponentTypes[7].filePath="components/Fuse.txt";
    ComponentTypes[8].filePath="components/Connector.txt";
    ComponentTypes[9].filePath="components/Transistor.txt";

}

