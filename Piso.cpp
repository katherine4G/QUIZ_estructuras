#include "Piso.h"


ListaPisos::ListaPisos()
{ 
    INI = nullptr;
}

void ListaPisos::insertarPiso(int numPiso) {
    if (buscarPiso(numPiso) != nullptr) {
        cout << "El piso " << numPiso << " ya existe. No se puede insertar." << endl;
        return;
    }

    NodoPiso* nuevoPiso = new NodoPiso(numPiso);
    if (INI == nullptr || INI->numPiso < numPiso) {
        nuevoPiso->abajo = INI;
        if (INI != nullptr) INI->arriba = nuevoPiso;
        INI = nuevoPiso;
    }
    else {
        NodoPiso* temp = INI;
        while (temp->abajo != nullptr && temp->abajo->numPiso > numPiso) {
            temp = temp->abajo;
        }
        nuevoPiso->abajo = temp->abajo;
        if (temp->abajo != nullptr) temp->abajo->arriba = nuevoPiso;
        temp->abajo = nuevoPiso;
        nuevoPiso->arriba = temp;
    }

    cout << "\n\nPiso " << numPiso << " insertado correctamente." << endl;
}

// Buscar un piso por número
NodoPiso* ListaPisos::buscarPiso(int numPiso) {
    NodoPiso* temp = INI;
    while (temp != nullptr) {
        if (temp->numPiso == numPiso) {
            return temp;
        }
        temp = temp->abajo;
    }
    return nullptr;
}

// Insertar un empleado en un piso
void ListaPisos::insertarEmpleadoEnPiso(int numPiso, const string& nombreEmpleado) {
    NodoPiso* piso = buscarPiso(numPiso);

    if (piso != nullptr) {
        NodoEmpleado* nuevoEmpleado = new NodoEmpleado(nombreEmpleado);
        if (piso->listaEmpleados == nullptr || piso->listaEmpleados->nombreEmpleado > nombreEmpleado) {
            nuevoEmpleado->siguiente = piso->listaEmpleados;
            piso->listaEmpleados = nuevoEmpleado;
        }
        else {
            NodoEmpleado* temp = piso->listaEmpleados;
            while (temp->siguiente != nullptr && temp->siguiente->nombreEmpleado < nombreEmpleado) {
                temp = temp->siguiente;
            }
            nuevoEmpleado->siguiente = temp->siguiente;
            temp->siguiente = nuevoEmpleado;
        }
    }
    else {
        cout << "Piso No." << numPiso << " no encontrado" << endl;
    }
}

void  ListaPisos::verificarSumatorias() {
    if (INI == nullptr) {
        cout << "Aún no se han ingresado pisos." << endl;
        return;
    }
    NodoPiso* piso = INI;
    while (piso != nullptr) {
        cout << "Verificando piso " << piso->numPiso << "..." << endl;

        NodoEmpleado* empleado = piso->listaEmpleados;
        int totalVentasPisoCalculado = 0;

        while (empleado != nullptr) {
            int totalVentasEmpleadoCalculado = 0;
            NodoVenta* venta = empleado->listaVentas;

            while (venta != nullptr) {
                totalVentasEmpleadoCalculado += venta->cantidad;
                venta = venta->siguiente;
            }

            if (totalVentasEmpleadoCalculado != empleado->totalVentas) {
                cout << "Error en el empleado " << empleado->nombreEmpleado
                    << ": Total ventas calculado (" << totalVentasEmpleadoCalculado
                    << ") no coincide con el almacenado (" << empleado->totalVentas << ")." << endl;
            }
            else {
                cout << "Empleado " << empleado->nombreEmpleado
                    << ": Total ventas calculado (" << totalVentasEmpleadoCalculado
                    << ") coincide con el almacenado." << endl;
            }

            totalVentasPisoCalculado += totalVentasEmpleadoCalculado;
            empleado = empleado->siguiente;
        }

        if (totalVentasPisoCalculado != piso->totalVentasPiso) {
            cout << "Error en el piso " << piso->numPiso
                << ": Total ventas calculado (" << totalVentasPisoCalculado
                << ") no coincide con el almacenado (" << piso->totalVentasPiso << ")." << endl;
        }
        else {
            cout << "Piso " << piso->numPiso
                << ": Total ventas calculado (" << totalVentasPisoCalculado
                << ") coincide con el almacenado." << endl;
        }

        piso = piso->abajo;
    }
}

void ListaPisos::eliminarPisoYTransferirEmpleados(int pisoAEliminar, int pisoDestino) {
    NodoPiso* pisoEliminar = buscarPiso(pisoAEliminar);
    NodoPiso* pisoDestinoNodo = buscarPiso(pisoDestino);

    if (pisoEliminar != nullptr) {
        if (pisoDestinoNodo != nullptr) {
           
            NodoEmpleado* empleado = pisoEliminar->listaEmpleados; // Transferir empleados del piso a eliminar al piso destino
            while (empleado != nullptr) {
                NodoEmpleado* siguienteEmpleado = empleado->siguiente;

               
                NodoEmpleado* actual = pisoDestinoNodo->listaEmpleados; // Insertar el empleado en el piso en orden alfabético
                NodoEmpleado* anterior = nullptr;
                while (actual != nullptr && actual->nombreEmpleado < empleado->nombreEmpleado) {
                    anterior = actual;
                    actual = actual->siguiente;
                }

                if (anterior == nullptr) { //insertar inicio
                    empleado->siguiente = pisoDestinoNodo->listaEmpleados;
                    pisoDestinoNodo->listaEmpleados = empleado;
                }
                else {//insertar medio
                  
                    anterior->siguiente = empleado;
                    empleado->siguiente = actual;
                }

                int totalVentasEmpleado = 0;
                NodoVenta* venta = empleado->listaVentas;
                while (venta != nullptr) {
                    totalVentasEmpleado += venta->cantidad;
                    venta = venta->siguiente;
                }
                empleado->totalVentas = totalVentasEmpleado;
                pisoDestinoNodo->totalVentasPiso += totalVentasEmpleado;

                empleado = siguienteEmpleado;
            }

            pisoEliminar->listaEmpleados = nullptr;
            pisoEliminar->totalVentasPiso = 0;

            // Recalcular el total de ventas del piso destino
            NodoEmpleado* empleadoTemp = pisoDestinoNodo->listaEmpleados;
            pisoDestinoNodo->totalVentasPiso = 0;
            while (empleadoTemp != nullptr) {
                pisoDestinoNodo->totalVentasPiso += empleadoTemp->totalVentas;
                empleadoTemp = empleadoTemp->siguiente;
            }
        }
        else {
            cout << "Piso destino no encontrado: " << pisoDestino << endl;
        }

        NodoPiso* pisoPrevio = pisoEliminar->arriba; // Eliminar el piso eliminado (desvincularlo de la lista de pisos)
        NodoPiso* pisoSiguiente = pisoEliminar->abajo;

        if (pisoPrevio != nullptr) {
            pisoPrevio->abajo = pisoSiguiente;
        }

        if (pisoSiguiente != nullptr) {
            pisoSiguiente->arriba = pisoPrevio;
        }

        delete pisoEliminar; // Liberar memoria del piso eliminado
    }
    else {
        cout << "Piso a eliminar no encontrado: " << pisoAEliminar << endl;
    }
}

void ListaPisos::mostrarDatos() {

    NodoPiso* pisoActual = INI;
    while (pisoActual != nullptr) {
        cout << "Piso: " << pisoActual->numPiso << ", Total Ventas: " << pisoActual->totalVentasPiso << endl;

        NodoEmpleado* empleadoActual = pisoActual->listaEmpleados;
        while (empleadoActual != nullptr) {
            cout << "  Empleado: " << empleadoActual->nombreEmpleado << ", Total Ventas: " << empleadoActual->totalVentas << endl;

            NodoVenta* ventaActual = empleadoActual->listaVentas;
            while (ventaActual != nullptr) {
                cout << "    Venta: " << ventaActual->cantidad << endl;
                ventaActual = ventaActual->siguiente;
            }

            empleadoActual = empleadoActual->siguiente;
        }

        pisoActual = pisoActual->abajo;
    }
}
void ListaPisos::insertarVentaEnEmpleado(int numPiso, const string& nombreEmpleado, int cantidad) {
    NodoPiso* piso = buscarPiso(numPiso);

    if (piso != nullptr) {
        NodoEmpleado* empleado = piso->listaEmpleados;
        while (empleado != nullptr && empleado->nombreEmpleado != nombreEmpleado) {
            empleado = empleado->siguiente;
        }

        if (empleado != nullptr) {

            NodoVenta* nuevaVenta = new NodoVenta(cantidad);

            
            if (empleado->listaVentas == nullptr || empleado->listaVentas->cantidad <= cantidad) {// Insertar la nueva venta en la lista de ventas en orden descendente
                
                nuevaVenta->siguiente = empleado->listaVentas;
                empleado->listaVentas = nuevaVenta;
            }
            else {
                NodoVenta* tempVenta = empleado->listaVentas;
                while (tempVenta->siguiente != nullptr && tempVenta->siguiente->cantidad > cantidad) {
                    tempVenta = tempVenta->siguiente;
                }
                nuevaVenta->siguiente = tempVenta->siguiente;
                tempVenta->siguiente = nuevaVenta;
            }

            int totalVentasEmpleado = 0;
            NodoVenta* tempVenta = empleado->listaVentas;
            while (tempVenta != nullptr) {
                totalVentasEmpleado += tempVenta->cantidad;
                tempVenta = tempVenta->siguiente;
            }
            empleado->totalVentas = totalVentasEmpleado;

            piso->totalVentasPiso = 0;
            NodoEmpleado* tempEmpleado = piso->listaEmpleados;
            while (tempEmpleado != nullptr) {
                piso->totalVentasPiso += tempEmpleado->totalVentas;
                tempEmpleado = tempEmpleado->siguiente;
            }
        }
        else {
            cout << "Empleado no encontrado en el piso: " << numPiso << endl;
        }
    }
    else {
        cout << "Piso no encontrado: " << numPiso << endl;
    }
}