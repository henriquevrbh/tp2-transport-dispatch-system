#include "Corrida.hpp"
#include <stdexcept>

//construtor
Corrida::Corrida(double velocidade){
    this->gama = velocidade;
}

//destrutor
Corrida::~Corrida(){
    this->limparRota();
}

//método responsável por limpar a memória das rotas
void Corrida::limparRota(){
    //deleta todos os trechos alocados
    for (int i = 0; i < trechos.size(); i++){
        delete trechos[i];
    }
    //deleta todos as paradas alocadas
    for (int i = 0; i < paradas.size(); i++){
        delete paradas[i];
    }
    
    //limpa as listas de ponteiros
    trechos.clear();
    paradas.clear();
}


void Corrida::adicionarDemanda(Demanda* d){
    demandas.push_back(d);
}

void Corrida::removerUltimaDemanda(){
    demandas.pop_back();
}

//verifica se uma nova demanda se encaixa pelos critérios alfa/beta
bool Corrida::checaDistancias(Demanda* nova, double alfa, double beta) const{
    //compara a nova demanda com todas as demandas já existentes na corrida
    for (int i = 0; i < demandas.size(); i++){
        Demanda* existente = demandas[i];
        
        //critério ALFA (origem) 
        if (existente->distanciaOrigem(*nova) > alfa){
            return false;
        }
        //critério BETA (destino)
        if (existente->distanciaDestino(*nova) > beta){
            return false;
        }
    }
    return true; //passou em todas as checagens
}

//gera a rota de paradas e trechos
void Corrida::gerarRotaBasica(){
    //limpa qualquer rota anterior
    this->limparRota();

    int n = demandas.size();
    if (n == 0) return;

    //cria a lista de Paradas

    //adiciona todas as paradas de EMBARQUE
    for (int i = 0; i < n; i++){
        paradas.push_back(new Parada(demandas[i]->getOrigem(), EMBARQUE, demandas[i]->getId()));
    }
    //adiciona todas as paradas de DESEMBARQUE
    for (int i = 0; i < n; i++){
        paradas.push_back(new Parada(demandas[i]->getDestino(), DESEMBARQUE, demandas[i]->getId()));
    }

    //cria a lista de trechos que conectam as paradas
    for (int i = 0; i < paradas.size() - 1; i++) {
        Parada* p1 = paradas[i];
        Parada* p2 = paradas[i + 1];

        TipoTrecho tipo;
        
        //define o tipo do trecho
        if (p1->tipo == EMBARQUE && p2->tipo == EMBARQUE){
            tipo = COLETA;
        } else if (p1->tipo == EMBARQUE && p2->tipo == DESEMBARQUE){
            tipo = DESLOCAMENTO; //trecho entre a última coleta e a primeira entrega
        } else{ //DESEMBARQUE -> DESEMBARQUE
            tipo = ENTREGA;
        }
        
        trechos.push_back(new Trecho(p1, p2, tipo, this->gama));
    }
}

//calcula a eficiência da rota atual
double Corrida::calcularEficiencia() const{
    double distanciaIndividualTotal = 0.0;
    double distanciaCompartilhadaTotal = 0.0;

    //soma as distâncias das corridas individuais
    for (int i = 0; i < demandas.size(); i++){
        distanciaIndividualTotal += demandas[i]->getOrigem().distancia(demandas[i]->getDestino());
    }

    //soma as distâncias de todos os trechos da rota compartilhada
    for (int i = 0; i < trechos.size(); i++) {
        distanciaCompartilhadaTotal += trechos[i]->getDistancia();
    }

    if (distanciaCompartilhadaTotal == 0) {
        if (distanciaIndividualTotal == 0) return 1.0; //corrida de 0m
        return 0.0; //robustez: vita divisão por zero
    }
    
    //retorna o calculo da eficiendia em si
    return distanciaIndividualTotal / distanciaCompartilhadaTotal;
}

//métodos simulação

//cria o primeiro evento da simulação para esta corrida
Evento Corrida::gerarEventoInicial(){
    if (demandas.size() == 0 || paradas.size() == 0){
        //corrida inválida, retorna um evento "fim"
        return Evento(0.0, FIM_DA_CORRIDA, -1, nullptr);
    }
    
    //o primeiro evento é a chegada no primeiro ponto de embarque
    Demanda* c0 = demandas[0];
    
    return Evento(c0->getTempo(), CHEGADA_EMBARQUE, 0, (Corrida*)this);
}

//processa um evento e retorna o próximo evento
Evento Corrida::processarEvento(const Evento& ev){
    int indiceParadaAtual = ev.getIndice();
    int indiceProximaParada = indiceParadaAtual + 1;

    int indiceTrechoAtual = indiceParadaAtual;

    //verifica se foi fim
    if (indiceTrechoAtual >= trechos.size()){
        return Evento(ev.getTempo(), FIM_DA_CORRIDA, -1, (Corrida*)this);
    }

    //se não for fim gera o próximo evento
    
    //pega o trecho que acabou de ser percorrido
    Trecho* trecho = trechos[indiceTrechoAtual];
    
    //pega a parada de destino
    Parada* proximaParada = paradas[indiceProximaParada];

    //calcula o tempo de chegada no próximo ponto
    double tempoAtual = ev.getTempo();
    double tempoViagem = trecho->getTempo();
    double tempoChegada = tempoAtual + tempoViagem;

    //define o tipo do próximo evento
    TipoEvento tipoProximoEvento;
    if (proximaParada->tipo == EMBARQUE){
        tipoProximoEvento = CHEGADA_EMBARQUE;
    } else{
        tipoProximoEvento = CHEGADA_DESEMBARQUE;
    }

    //retorna o novo evento, que será agendado pelo main
    return Evento(tempoChegada, tipoProximoEvento, indiceProximaParada, (Corrida*)this);
}


//getters

int Corrida::getNumPassageiros() const{
    return demandas.size();
}

int Corrida::getNumParadas() const{
    return paradas.size();
}

//calcula a distância total somando os trechos
double Corrida::getDistanciaTotal() const{
    double total = 0.0;
    for (int i = 0; i < trechos.size(); i++){
        total += trechos[i]->getDistancia();
    }
    return total;
}

//calcula o tempo total somando os trechos
double Corrida::getTempoTotal() const{
    double total = 0.0;
    for (int i = 0; i < trechos.size(); i++){
        total += trechos[i]->getTempo();
    }
    return total;
}

//getters de estatisticas finais com robustez
Demanda* Corrida::getDemanda(int i) const{
    if (i < 0 || i >= demandas.size()){
        throw std::out_of_range("Índice de demanda inválido");
    }
    return demandas[i];
}

Parada* Corrida::getParada(int i) const{
    if (i < 0 || i >= paradas.size()){
        throw std::out_of_range("Índice de parada inválido");
    }
    return paradas[i];
}