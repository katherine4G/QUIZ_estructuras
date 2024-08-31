#include "Menu.h"

Menu::Menu()
{
    cantidad = 0;
    numPiso = 0;
}

Menu::~Menu()
{
}
void Menu::principalMenu() {
    cout << "----- Menú -----" << endl;
    cout << "1. Insertar Piso" << endl;
    cout << "2. Insertar Empleado en Piso" << endl;
    cout << "3. Insertar Venta en Empleado" << endl;
    cout << "4. Verificar Sumatorias" << endl;
    cout << "5. Eliminar Piso y Transferir Empleados" << endl;
    cout << "6. Mostrar Datos" << endl;
    cout << "7. Salir" << endl;
    cout << "----------------" << endl;
}

void Menu::showMenu() {
    setlocale(LC_CTYPE, "Spanish");

    int opcion;

    do {
        principalMenu();
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Entrada no válida. Por favor, ingrese un número." << endl;
            system("pause");
            system("cls");
            continue;
        }

        NodoPiso* piso = nullptr; 

        switch (opcion) {
        case 1:
            cout << "Ingrese el No. del piso: ";
            cin >> numPiso;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Número de piso no válido." << endl;
            }
            else {
                listaPisos.insertarPiso(numPiso);
            }
            break;

        case 2:
            cout << "Ingrese el No. del piso: ";
            cin >> numPiso;
            cout << "Ingrese el nombre del empleado: ";
            cin >> nombreEmpleado;

            piso = listaPisos.buscarPiso(numPiso);

            if (piso != nullptr) {
                listaPisos.insertarEmpleadoEnPiso(numPiso, nombreEmpleado);
                cout << "Empleado " << nombreEmpleado << " insertado en el piso " << numPiso << "." << endl;
            }
            else {
                cout << "Piso No." << numPiso << " no encontrado. No se pudo insertar el empleado." << endl;
            }
            break;

        case 3:
            cout << "Ingrese el No. del piso: ";
            cin >> numPiso;
            cout << "Ingrese el nombre del empleado: ";
            cin >> nombreEmpleado;
            cout << "Ingrese la cantidad de la venta: ";
            cin >> cantidad;

            piso = listaPisos.buscarPiso(numPiso);  

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Cantidad de venta no válida." << endl;
            }
            else if (piso != nullptr) {
                listaPisos.insertarVentaEnEmpleado(numPiso, nombreEmpleado, cantidad);
                cout << "Venta de " << cantidad << " insertada para el empleado " << nombreEmpleado << " en el piso " << numPiso << "." << endl;
            }
            else {
                cout << "Piso No." << numPiso << " no encontrado. No se pudo insertar la venta." << endl;
            }
            break;

        case 4:
            listaPisos.verificarSumatorias();

            break;

        case 5:
            int pisoEliminar, pisoDestino;
            cout << "Ingrese el No. del piso a eliminar: ";
            cin >> pisoEliminar;
            cout << "Ingrese el No. del piso a transferir los empleados: ";
            cin >> pisoDestino;
            listaPisos.eliminarPisoYTransferirEmpleados(pisoEliminar, pisoDestino);
            break;

        case 6:
            listaPisos.mostrarDatos();
            break;

        case 7:
            exit(-1);
            break;

        default:
            cout << "Opción no válida, intente de nuevo." << endl;
            break;
        }

        system("pause");
        system("cls");

    } while (opcion != 7);
}
