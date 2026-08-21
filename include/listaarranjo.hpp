#ifndef LISTAARRANJO_HPP
#define LISTAARRANJO_HPP

#include <stdexcept>

template <typename T>

class ListaArranjo{
private:
    T* data; //ponteiro para o array de dados no heap
    int capacidade; //tamanho total do array
    int tamanho; //número de elementos atualmente na lista

    //método para dobrar a capacidade do array
    void expandir(){
        int novaCapacidade = capacidade * 2;
        T* novo = new T[novaCapacidade];

        for (int i = 0; i < tamanho; i++){
            novo[i] = data[i];
        }

        delete[] data; //libera o array antigo
        data = novo;
        capacidade = novaCapacidade;
    }

public:
    //construtor
    ListaArranjo(int capacidade = 10){
        this->capacidade = capacidade;
        tamanho = 0;
        data = new T[capacidade];
    }

    //detrutor responsável por liberar a memória do array
    ~ListaArranjo(){
        delete[] data;
    }

    //inserção no final
    void push_back(const T& item){
        if (tamanho == capacidade){
            expandir(); //expande se estiver cheio
        }
        data[tamanho++] = item;
    }

    //remoção no final
    void pop_back(){
        if (tamanho > 0){
            tamanho--;
        }
    }

    //acesso por índice (o(1))
    T& operator[](int index){
        if (index < 0 || index >= tamanho)
            throw std::out_of_range("Index invalido");
        return data[index];
    }

    //acesso por índice (versão const, o(1))
    const T& operator[](int index) const{
        if (index < 0 || index >= tamanho)
            throw std::out_of_range("Index invalido");
        return data[index];
    }

    //retorna o número de elementos na lista
    int size() const{
        return tamanho;
    }

    //limpa a lista
    void clear(){
        tamanho = 0;
    }
};

#endif