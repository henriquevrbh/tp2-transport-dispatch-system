#include "Trecho.hpp"
#include <cmath>

//construtor padrão
Trecho::Trecho(){
    this->inicio = nullptr;
    this->fim = nullptr;
    this->tipo = DESLOCAMENTO; //tipo padrão arbitrário
    this->distancia = 0.0;
    this->tempo = 0.0;
}

//construtor parametrizado
Trecho::Trecho(Parada* inicio, Parada* fim, TipoTrecho tipo, double gama){
    this->inicio = inicio;
    this->fim = fim;
    this->tipo = tipo;

    //calcula e armazena a distância uma única vez
    this->distancia = this->calcularDistancia();

    //cálculo do tempo com robustez
    if(gama > 0){
        this->tempo = this->distancia / gama;
    } else {
        this->tempo = 0.0; //evita divisão por zero
    }
}

//método auxiliar para calcular a distância
double Trecho::calcularDistancia() const{
    //robustez contra ponteiros nulos
    if (!inicio || !fim){ 
        return 0.0;
    }
    
    double deltaX = inicio->coordenadas.x - fim->coordenadas.x;
    double deltaY = inicio->coordenadas.y - fim->coordenadas.y;
    
    return std::sqrt(std::pow(deltaX,2) + std::pow(deltaY,2));
}


//getters, apenas retornam os valores (privados) da classe
Parada* Trecho::getInicio() const{ 
    return inicio; 
}

Parada* Trecho::getFim() const{ 
    return fim; 
}

TipoTrecho Trecho::getTipo() const{ 
    return tipo;
}

double Trecho::getDistancia() const{ 
    return distancia;
}

double Trecho::getTempo() const{ 
    return tempo;
}