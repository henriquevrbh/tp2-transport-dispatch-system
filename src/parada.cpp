#include "Parada.hpp"

//construtor padrão
Parada::Parada(){
    this->coordenadas = Ponto(); //inicializa ponto na origem (0,0)
    this->tipo = EMBARQUE;      //define um tipo padrão
    this->idDemanda = 0;     //define um id padrão
}

//construtor parametrizado
Parada::Parada(const Ponto& coordenadas, TipoParada tipo, int idDemanda){
    this->coordenadas = coordenadas;
    this->tipo = tipo;
    this->idDemanda = idDemanda;
}