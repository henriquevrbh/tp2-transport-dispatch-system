#include "Evento.hpp"

//construtor padrão
Evento::Evento(){
    tempo = 0.0;
    tipo = FIM_DA_CORRIDA; //tipo padrão para um evento vazio
    indice = -1;
    corrida = nullptr;
}

//construtor parametrizado
Evento::Evento(double tempo, TipoEvento tipo, int indice, Corrida* corrida){
    this->tempo = tempo;
    this->tipo = tipo;
    this->indice = indice;
    this->corrida = corrida;
}

//getters
double Evento::getTempo() const{
    return tempo;
}

TipoEvento Evento::getTipo() const{
    return tipo;
}

int Evento::getIndice() const{
    return indice;
}

Corrida* Evento::getCorrida() const{
    return corrida;
}

//sobrecarga do operador < para o minheap
bool Evento::operator<(const Evento& outro) const{
    //compara dois eventos baseado no tempo
    //menor tempo = maior prioridade no minheap
    return this->tempo < outro.tempo;
}