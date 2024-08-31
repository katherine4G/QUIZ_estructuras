#pragma once
#ifndef VENTA_H
#define VENTA_H
#include <iostream>
using namespace std;

struct NodoVenta {
    int cantidad;
    NodoVenta* siguiente;

    NodoVenta(int cantidad) {
        this->cantidad = cantidad;
        this->siguiente = nullptr;
    }
};

class ListaVentas {
public:
    NodoVenta* cabeza;

    ListaVentas();

    void insertarVenta(int cantidad);

    void mostrarVentas();

    int calcularTotalVentas();
};
#endif 

