#pragma once

#include <iostream>
#include "Venta.h"

using namespace std;


struct NodoEmpleado {
  
    string nombreEmpleado;
    int totalVentas;
    NodoEmpleado* siguiente;
    NodoVenta* listaVentas;

    NodoEmpleado(const string& nombreEmpleado) : nombreEmpleado(nombreEmpleado), totalVentas(0), siguiente(nullptr), listaVentas(nullptr) {}

};

class ListaEmpleados {
public:
    NodoEmpleado* cabeza;

    ListaEmpleados();

    void insertarEmpleado(const string& nombreEmpleado);

    NodoEmpleado* buscarEmpleado(const string& nombreEmpleado);

    void mostrarEmpleados();

    void actualizarTotalVentasEmpleado(NodoEmpleado* empleado);

    
};