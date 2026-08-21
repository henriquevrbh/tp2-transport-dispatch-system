#ifndef DEMANDA_HPP
#define DEMANDA_HPP

#include "Ponto.hpp"

//enum para os estados possíveis de uma demanda
enum EstadoDemanda{
    DEMANDADA,
    INDIVIDUAL,
    COMPARTILHADA,
    CONCLUIDA
};

class Demanda{
private:
    int id; //id único da demanda
    double tempo; //tempo em que a demanda foi solicitada
    Ponto origem; //ponto de origem da demanda
    Ponto destino; //ponto de destino da demanda
    EstadoDemanda estado; //estado atual da demanda

public:
    //construtores
    Demanda(); //construtor padrão
    Demanda(int id, double tempo, const Ponto& origem, const Ponto& destino); //construtor parametrizado

    //getters e setters
    int getId() const;
    double getTempo() const;
    Ponto getOrigem() const;
    Ponto getDestino() const;
    EstadoDemanda getEstado() const;
    void setEstado(EstadoDemanda estado);

    //funções auxiliares
    //calcula a distância entre a origem desta demanda e a de outra
    double distanciaOrigem(const Demanda& outra) const;
    //calcula a distância entre o destino desta demanda e o de outra
    double distanciaDestino(const Demanda& outra) const;
};

#endif