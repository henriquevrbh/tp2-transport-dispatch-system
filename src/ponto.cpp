#include "Ponto.hpp"
#include <cmath> 

//construtor padrão
Ponto::Ponto(){
    x = 0.0;
    y = 0.0;
}

//construtor parametrizado
Ponto::Ponto(double x, double y){
    this->x = x;
    this->y = y;
}

//calcula a distância euclidiana
double Ponto::distancia(const Ponto& ponto) const{
    double deltaX = this->x - ponto.x;
    double deltaY = this->y - ponto.y;

    return std::sqrt(std::pow(deltaX,2) + std::pow(deltaY,2));
}