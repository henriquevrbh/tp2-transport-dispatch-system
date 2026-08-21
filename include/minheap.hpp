#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "ListaArranjo.hpp"
#include <stdexcept>

template <typename T>

class MinHeap{
private:
    ListaArranjo<T> dados;

    //retorna o índice do nó pai
    int pai(int i) const{ 
        return (i - 1)/2;
    }

    //retorna o índice do filho da esquerda
    int filhoEsq(int i) const{
        return 2*i + 1;
    }

    //retorna o índice do filho da direita
    int filhoDir(int i) const{
        return 2*i + 2;
    }

    //mantém propriedade do min-heap após inserção
    void heapifyUp(int i){
        int p = pai(i);
        //enquanto o filho for menor que o pai, troca
        while (i > 0 && dados[i] < dados[p]){  
            T temp = dados[i];
            dados[i] = dados[p];
            dados[p] = temp;

            //atualiza o índice para continuar subindo
            i = p;
            p = pai(i);
        }
    }

    //mantém propriedade do min-heap após remoção
    void heapifyDown(int i){
        int menor = i;
        int esq = filhoEsq(i);
        int dir = filhoDir(i);
        int n = dados.size();

        //compara com filho da esquerda
        if (esq < n && dados[esq] < dados[menor]){
            menor = esq;
        }

        //compara com filho da direita
        if (dir < n && dados[dir] < dados[menor]){
            menor = dir;
        }

        //se menor mudou, troca e continua descendo
        if (menor != i){
            T temp = dados[i];
            dados[i] = dados[menor];
            dados[menor] = temp;

            heapifyDown(menor);
        }
    }

public:
    //construtor padrão
    MinHeap() {}

    //verifica se o heap está vazio
    bool empty() const{
        return dados.size() == 0;
    }

    //retorna o número de elementos no heap
    int size() const{
        return dados.size();
    }

    //retorna a raiz sem remover
    const T& top() const{
        if (empty())
            throw std::runtime_error("Heap vazio");
        return dados[0];
    }

    //inserção O(log n)
    void push(const T& item){
        dados.push_back(item);               //adiciona no fim
        heapifyUp(dados.size() - 1);         //conserta subindo
    }

    //remoção O(log n)
    T pop(){
        if (empty())
            throw std::runtime_error("Heap vazio");

        T raiz = dados[0];                     //menor elemento

        dados[0] = dados[dados.size() - 1];    //último vira raiz
        dados.pop_back();                      //remove último

        if (!empty())
            heapifyDown(0);                    //conserta descendo

        return raiz;
    }
};

#endif