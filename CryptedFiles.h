#include <bits/stdc++.h>
#define MAX_INPUT_POINTS 5
#define MAX_OUTPUT_POINTS 5
#define MAX_ROWS 3
#define POINT_CIRCLE_RADIUS 4
#define MAX_ROW_SIZE 50
#define PI 3.14159265

struct Componenta
{
    std::string adresa;
};

Componenta Componente[13];

void initializeComponentTypes()
{
    Componente[0].adresa="components/ElectricalCell.txt";
    Componente[1].adresa="components/Resistor.txt";
    Componente[2].adresa="components/Bulb.txt";
    Componente[3].adresa="components/Diode.txt";
    Componente[4].adresa="components/Ammeter.txt";
    Componente[5].adresa="components/Voltmeter.txt";
    Componente[6].adresa="components/Capacitor.txt";
    Componente[7].adresa="components/Fuse.txt";
    Componente[8].adresa="components/Connector.txt";
    Componente[9].adresa="components/Transistor.txt";

}

