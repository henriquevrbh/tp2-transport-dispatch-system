#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "MinHeap.hpp"
#include "Evento.hpp"

class Escalonador {
private:
    //minheap que armazena os eventos
    MinHeap<Evento> heap;

public:
    //construtor padrão
    //inicializa
    Escalonador();

    //destrutor padrão
    //finaliza 
    ~Escalonador();

    //insere um evento futuro na fila
    void inserirEvento(const Evento& e);

    //retira o próximo evento (menor tempo)
    Evento retirarProximoEvento();

    //verifica se ainda há eventos na fila
    bool vazio() const;

    //retorna quantos eventos ainda existem
    int tamanho() const;
};

#endif