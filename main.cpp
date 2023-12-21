#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "Grafo.h"
#include <sstream>
#include <cmath>
using namespace std;

// Función para leer nodos desde el archivo servidores.csv
void leerNodosDesdeArchivo(const std::string& nombreArchivo, Grafo& grafo) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        int id;
        std::string nombre, tipo;
        while (archivo >> id >> nombre >> tipo) {
            grafo.agregarNodo(id, nombre, tipo);
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        exit(1);
    }
}

// Función para leer conexiones desde el archivo conexiones.csv
void leerConexionesDesdeArchivo(const std::string& nombreArchivo, Grafo& grafo) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        int idCliente, idServidor, velocidad, distancia;
        while (archivo >> idCliente >> idServidor >> velocidad >> distancia) {
            grafo.agregarConexion(idCliente, idServidor, velocidad, distancia);
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        exit(1);
    }
};




// Función para particionar el archivo
void particionarYEnviarArchivo(Grafo& grafo, int idCliente, int tamanoArchivo) {
    // Obtener la velocidad y distancia desde el cliente hasta el servidor
    int velocidadMaxima = -1;
    int distanciaTotal = 0;

    for (const auto& conexion : grafo.conexiones) { //recorre las conexiones
        if (conexion.idCliente == idCliente) {   //verifico si las id son iguales
            velocidadMaxima = std::max(velocidadMaxima, conexion.velocidad);
            distanciaTotal += conexion.distancia; //suma las distancias
        }
    }

    // Calcular el tiempo total y la cantidad de partes
    int tiempoTotal = ceil(static_cast<double>(tamanoArchivo) / velocidadMaxima);
    int cantidadPartes = ceil(static_cast<double>(tamanoArchivo) / 300);

    // Imprimir información
    cout << "Archivo de " << tamanoArchivo << " MB desde Cliente " << idCliente << " hacia el servidor:" << endl;
    cout << "Velocidad máxima: " << velocidadMaxima << " MB/s" << endl;
    cout << "Distancia total: " << distanciaTotal << " unidades" << endl;
    cout << "Tiempo total estimado: " << tiempoTotal << " segundos" << endl;

    // Imprimir información sobre la partición del archivo
    cout << "El archivo se dividirá en " << cantidadPartes << " partes:" << endl;

        for (int i = 0; i < cantidadPartes; ++i) {
        if (i < grafo.conexiones.size()) {
            int tiempoParte = ceil(static_cast<double>(grafo.conexiones[i].distancia) / grafo.conexiones[i].velocidad);
            cout << "Parte " << i + 1 << ": Enviar al router " << grafo.conexiones[i].idServidor
                << " - Tiempo estimado: " << tiempoParte << " segundos" << endl;
        } else {
            cout << "Error: No hay suficientes conexiones para la cantidad de partes especificadas." << endl;
            break;
        }
}
    // Mostrar la ruta desde el cliente hasta el servidor
    cout << "\nRuta desde Cliente " << idCliente << " hasta el servidor:" << endl;
    vector<int> ruta = grafo.obtenerRuta(idCliente);
    for (int i = 0; i < ruta.size(); ++i) {
        cout << "Nodo " << ruta[i];
        if (i < ruta.size() - 1) {
            cout << " -> ";
        }
    }
    cout << "\n" << endl;
}

// Función para ejecutar el menú
void ejecutarMenu(Grafo& grafo) {
    int opcion;
    do {
        cout << "\n*** Menú ***" << endl;
        cout << "1. Particionar y enviar archivo" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese el número de la opción deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int idCliente, tamanoArchivo;
                cout << "Ingrese el cliente que desea simular (ID): ";
                cin >> idCliente;
                cout << "Ingrese el tamaño del archivo a enviar (en MB): ";
                cin >> tamanoArchivo;
                particionarYEnviarArchivo(grafo, idCliente, tamanoArchivo); //particion
                break;
            }
            case 2:
                cout << "Saliendo del programa. ¡Hasta luego!" << endl; //salir
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo." << endl; //control de errores
                break;
        }

    } while (opcion != 2);
}

int main() {
    Grafo grafo;

    // Leer servidores.csv
    leerNodosDesdeArchivo("servidores.csv", grafo);

    // Leer conexiones.csv
    leerConexionesDesdeArchivo("conexiones.csv", grafo);

    // Ejecutar el menú
    ejecutarMenu(grafo);

    return 0;
}