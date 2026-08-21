#include "Escalonador.hpp"

//construtor padrão
//incializa
Escalonador::Escalonador(){}

//finaliza
Escalonador::~Escalonador() {
    //a limpeza da memória do heap ocorre automatica pelo destrutor do MinHeap/ListaArranjo
}

//métodos de manipulação
//insere evento
void Escalonador::inserirEvento(const Evento& evento){
    heap.push(evento);
}

//retira próximo evento
Evento Escalonador::retirarProximoEvento(){
    return heap.pop();
}

//métodos de consulta
bool Escalonador::vazio() const{
    return heap.empty();
}

int Escalonador::tamanho() const{
    return heap.size();
}