#include "Empleado.h"



ListaEmpleados::ListaEmpleados()
{ 
    cabeza = nullptr;
}


void ListaEmpleados::insertarEmpleado(const string& nombreEmpleado) {
    NodoEmpleado* nuevoEmpleado = new NodoEmpleado(nombreEmpleado);

    if (cabeza == nullptr || cabeza->nombreEmpleado > nombreEmpleado) {
        nuevoEmpleado->siguiente = cabeza;
        cabeza = nuevoEmpleado;
    }
    else {
        NodoEmpleado* temp = cabeza;
        while (temp->siguiente != nullptr && temp->siguiente->nombreEmpleado < nombreEmpleado) {
            temp = temp->siguiente;
        }
        nuevoEmpleado->siguiente = temp->siguiente;
        temp->siguiente = nuevoEmpleado;
    }
}

NodoEmpleado* ListaEmpleados::buscarEmpleado(const string& nombreEmpleado) {
    NodoEmpleado* temp = cabeza;
    while (temp != nullptr && temp->nombreEmpleado != nombreEmpleado) {
        temp = temp->siguiente;
    }
    return temp;
}

void ListaEmpleados::mostrarEmpleados() {
    NodoEmpleado* temp = cabeza;
    while (temp != nullptr) {
        cout << "  Empleado: " << temp->nombreEmpleado << ", Total Ventas: " << temp->totalVentas << endl;
        NodoVenta* tempVenta = temp->listaVentas;
        while (tempVenta != nullptr) {
            cout << "    Venta: " << tempVenta->cantidad << endl;
            tempVenta = tempVenta->siguiente;
        }
        temp = temp->siguiente;
    }
}

void ListaEmpleados::actualizarTotalVentasEmpleado(NodoEmpleado* empleado) {
    if (empleado != nullptr) {
        int totalVentas = 0;
        NodoVenta* tempVenta = empleado->listaVentas;
        while (tempVenta != nullptr) {
            totalVentas += tempVenta->cantidad;
            tempVenta = tempVenta->siguiente;
        }
        empleado->totalVentas = totalVentas;
    }
}