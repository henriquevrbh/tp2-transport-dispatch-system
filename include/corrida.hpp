#ifndef CORRIDA_HPP
#define CORRIDA_HPP

#include "Demanda.hpp"
#include "Parada.hpp"
#include "Trecho.hpp"
#include "Evento.hpp"
#include "ListaArranjo.hpp"

class Corrida{
private:

    ListaArranjo<Demanda*> demandas; //ponteiros para as demandas atendidas
    ListaArranjo<Parada*> paradas;   //ponteiros para as paradas da rota 
    ListaArranjo<Trecho*> trechos;   //ponteiros para os trechos da rota

    double gama; //velocidade

    //método para limpar a memória
    void limparRota();

public:
    //construtor simples
    Corrida(double velocidade);

    //destrutor
    ~Corrida();

    //adiciona uma demanda e recalcula a rota
    void adicionarDemanda(Demanda* d);

    //remove a última demanda (se a eficiência falhar)
    void removerUltimaDemanda();

    //gera a rota de paradas e trechos
    void gerarRotaBasica();

    //verifica se uma nova demanda cabe
    bool checaDistancias(Demanda* nova, double alfa, double beta) const;

    //calcula a eficiência da rota atual
    double calcularEficiencia() const;
    
    //métodos simulação
    //cria o primeiro evento da simulação para esta corrida
    Evento gerarEventoInicial();

    //processa um evento e retorna o próximo evento
    Evento processarEvento(const Evento& ev);


    //getters
    int getNumPassageiros() const;
    int getNumParadas() const;
    double getDistanciaTotal() const;
    double getTempoTotal() const;
    
    //getters para estatísticas finais
    Demanda* getDemanda(int i) const;
    Parada* getParada(int i) const;
};

#endif