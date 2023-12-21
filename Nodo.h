#pragma once
#include <string>
#include <iostream>


class Nodo {
public:
    int id;
    std::string nombre;
    std::string tipo;

    Nodo(int _id, const std::string& _nombre, const std::string& _tipo)
        : id(_id), nombre(_nombre), tipo(_tipo) {}
};  