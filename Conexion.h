#pragma once
#include <string>
#include <iostream>


class Conexion {
public:
    int idCliente;
    int idServidor;
    int velocidad;
    int distancia;

    Conexion(int _idCliente, int _idServidor, int _velocidad, int _distancia)
        : idCliente(_idCliente), idServidor(_idServidor), velocidad(_velocidad), distancia(_distancia) {}
};