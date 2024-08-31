#pragma once

#include <iostream>
#include "Empleado.h" 
using namespace std;

struct NodoPiso {
    int numPiso;
    int totalVentasPiso;
    NodoEmpleado* listaEmpleados;
    NodoPiso* arriba;
    NodoPiso* abajo;

    NodoPiso(int numPiso) : numPiso(numPiso), totalVentasPiso(0), listaEmpleados(nullptr), arriba(nullptr), abajo(nullptr) {}
   
};

class ListaPisos {
public:
    NodoPiso* INI;

    ListaPisos();

    void insertarPiso(int numPiso);

    NodoPiso* buscarPiso(int numPiso);

    void insertarEmpleadoEnPiso(int numPiso, const string& nombreEmpleado);

    void verificarSumatorias();

    void eliminarPisoYTransferirEmpleados(int pisoAEliminar, int pisoDestino);

    void mostrarDatos();

    void insertarVentaEnEmpleado(int numPiso, const string& nombreEmpleado, int cantidad);

};
