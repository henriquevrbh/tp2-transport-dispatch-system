#ifndef TRECHO_HPP
#define TRECHO_HPP

#include "Parada.hpp"

//enum para os tipos de trecho da rota
enum TipoTrecho{
    COLETA,       
    ENTREGA,      
    DESLOCAMENTO  
};

class Trecho{
private:
    Parada* inicio; //ponteiro para a parada inicial 
    Parada* fim;    //ponteiro para a parada final 
    TipoTrecho tipo;  //tipo do trecho 
    double distancia; //distância do trecho
    double tempo;     //tempo para percorrer o trecho 

    //método auxiliar privado para calcular a distância
    double calcularDistancia() const;
    
public:
    //construtor padrão
    Trecho();
    //construtor parametrizado (calcula dist e tempo)
    Trecho(Parada* inicio, Parada* fim, TipoTrecho tipo, double gama);

    //getters
    Parada* getInicio() const;
    Parada* getFim() const;
    TipoTrecho getTipo() const;
    double getDistancia() const;
    double getTempo() const;

};

#endif