#pragma once
#include <cstdlib> 
#include<locale.h> 
#include "Piso.h"
class Menu
{
   
    ListaPisos listaPisos;
    int numPiso;
    string nombreEmpleado;
    int cantidad;

public:
    
    Menu();
    ~Menu();
    void principalMenu();
    void showMenu();

};


