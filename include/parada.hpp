#ifndef PARADA_HPP
#define PARADA_HPP

#include "Ponto.hpp"

//enum para os tipos de parada
enum TipoParada{
    EMBARQUE,
    DESEMBARQUE
};

struct Parada{
    Ponto coordenadas; //coordenada da parada (origem ou destino)
    TipoParada tipo; //tipo da parada
    int idDemanda; //id da demanda desta parada

    //construtores
    Parada(); //construtor padrão
    Parada(const Ponto& coordenadas, TipoParada tipo, int idDemanda); //construtor parametrizado
};

#endif