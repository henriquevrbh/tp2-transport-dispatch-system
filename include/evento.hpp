#ifndef EVENTO_HPP
#define EVENTO_HPP

//enum para os tipos de evento da simulação
enum TipoEvento{
    CHEGADA_EMBARQUE,   
    CHEGADA_DESEMBARQUE, 
    FIM_DA_CORRIDA      
};

class Corrida; //forward declaration

class Evento{
private:
    double tempo;       //tempo no qual o evento ocorre (chave do min-heap)
    TipoEvento tipo;    //tipo de evento
    int indice;         //índice da parada na lista de paradas da corrida
    Corrida* corrida;   //ponteiro para a corrida

public:
    //construtor padrão
    Evento();
    //construtor parametrizado
    Evento(double tempo, TipoEvento tipo, int indice, Corrida* corrida);

    // getters
    double getTempo() const;
    TipoEvento getTipo() const;
    int getIndice() const;
    Corrida* getCorrida() const;

    //necessário para MinHeap
    //sobrecarga do operador < para comparar eventos pelo tempo
    bool operator<(const Evento& outro) const;
};

#endif