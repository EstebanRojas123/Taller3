#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include "Nodo.h"
#include "Conexion.h"   

class Grafo {
public:
    std::vector<Nodo> nodos;
    std::vector<Conexion> conexiones;

    void agregarNodo(int id, const std::string& nombre, const std::string& tipo) {
        nodos.emplace_back(id, nombre, tipo);
    }

    void agregarConexion(int idCliente, int idServidor, int velocidad, int distancia) {
        conexiones.emplace_back(idCliente, idServidor, velocidad, distancia);
    }

    //implementacion de bellman ford
    void bellmanFord(int origen) {
        int numNodos = nodos.size();
        int numConexiones = conexiones.size();
        std::vector<int> distanciaMinima(numNodos, std::numeric_limits<int>::max());
        distanciaMinima[origen] = 0;

        // Relajación de las aristas
        for (int i = 1; i < numNodos; ++i) {
            for (int j = 0; j < numConexiones; ++j) {
                int u = conexiones[j].idCliente;
                int v = conexiones[j].idServidor;
                int peso = conexiones[j].distancia;

                if (distanciaMinima[u] != std::numeric_limits<int>::max() && distanciaMinima[u] + peso < distanciaMinima[v]) {
                    distanciaMinima[v] = distanciaMinima[u] + peso;
                }
            }
        }

        // Verificar ciclos negativos
        for (int i = 0; i < numConexiones; ++i) {
            int u = conexiones[i].idCliente;
            int v = conexiones[i].idServidor;
            int peso = conexiones[i].distancia;

            if (distanciaMinima[u] != std::numeric_limits<int>::max() && distanciaMinima[u] + peso < distanciaMinima[v]) {
                std::cout << "El grafo contiene ciclos negativos. No se puede calcular el camino más corto." << std::endl;
                return;
            }
        }

        // Imprimir distancias mínimas
        for (int i = 0; i < numNodos; ++i) {
            std::cout << "Distancia mínima desde el nodo " << origen << " hasta " << nodos[i].nombre << ": " << distanciaMinima[i] << std::endl;
        }
    }


    std::vector<int> obtenerRuta(int idCliente) {
    std::vector<int> ruta;
    int nodoActual = idCliente;

    while (true) {
        ruta.push_back(nodoActual);
        int siguienteNodo = -1;

        for (const auto& conexion : conexiones) {
            if (conexion.idCliente == nodoActual) {
                siguienteNodo = conexion.idServidor;
                break;
            }
        }

        if (siguienteNodo == -1) {
            break; // Llegamos al último nodo de la ruta
        }

        nodoActual = siguienteNodo;
    }

    return ruta;
}


};