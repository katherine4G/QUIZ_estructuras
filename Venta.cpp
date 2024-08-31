#include "Venta.h"

ListaVentas::ListaVentas()
{ 
    cabeza = nullptr;
}

void ListaVentas:: insertarVenta(int cantidad) {
    NodoVenta* nuevaVenta = new NodoVenta(cantidad);

    if (cabeza == nullptr || cabeza->cantidad < cantidad) {
        nuevaVenta->siguiente = cabeza;
        cabeza = nuevaVenta;
    }
    else {
        NodoVenta* temp = cabeza;
        while (temp->siguiente != nullptr && temp->siguiente->cantidad >= cantidad) {
            temp = temp->siguiente;
        }
        nuevaVenta->siguiente = temp->siguiente;
        temp->siguiente = nuevaVenta;
    }
}

void ListaVentas::mostrarVentas() {
    NodoVenta* temp = cabeza;
    while (temp != nullptr) {
        cout << "    Cantidad: " << temp->cantidad << endl;
        temp = temp->siguiente;
    }
}

int ListaVentas::calcularTotalVentas() {
    int total = 0;
    NodoVenta* temp = cabeza;
    while (temp != nullptr) {
        total += temp->cantidad;
        temp = temp->siguiente;
    }
    return total;
}