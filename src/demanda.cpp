#include "Demanda.hpp"

//construtor padrão
Demanda::Demanda(){
    id = 0;
    tempo = 0.0;
    origem = Ponto(); //inicializa ponto na origem (0,0)
    destino = Ponto(); //inicializa ponto na origem (0,0)
    estado = DEMANDADA; //estado inicial padrão
}

//construtor parametrizado
Demanda::Demanda(int id, double tempo, const Ponto& origem, const Ponto& destino){
    this->id = id;
    this->tempo = tempo;
    this->origem = origem;
    this->destino = destino;
    this->estado = DEMANDADA; //demanda sempre começa como DEMANDADA
}

//getters e setters
int Demanda::getId() const{
    return id;
}

double Demanda::getTempo() const{
    return tempo;
}

Ponto Demanda::getOrigem() const{
    return origem;
}

Ponto Demanda::getDestino() const{
    return destino;
}

EstadoDemanda Demanda::getEstado() const{
    return estado;
}

void Demanda::setEstado(EstadoDemanda estado){
    this->estado = estado;
}

//funções auxiliares

//calcula a distância entre a origem desta demanda e a de outra
double Demanda::distanciaOrigem(const Demanda& outra) const {
    //reutiliza a função distancia do TAD Ponto
    return origem.distancia(outra.origem);
}

//calcula a distância entre o destino desta demanda e o de outra
double Demanda::distanciaDestino(const Demanda& outra) const {
    //reutiliza a função distancia do TAD Ponto
    return destino.distancia(outra.destino);
}