#include <iostream>
#include <fstream>
#include <iomanip>

#include "Ponto.hpp"
#include "Demanda.hpp"
#include "Parada.hpp"
#include "Trecho.hpp"
#include "ListaArranjo.hpp"
#include "Evento.hpp"
#include "MinHeap.hpp"
#include "Escalonador.hpp"
#include "Corrida.hpp"

//parâmetros globais da simulação
int ETA;
double GAMA;
double DELTA;
double ALFA;
double BETA;
double LAMBDA;

//função para ler a entrada (cin ou arquivo)
int lerEntrada(std::istream& leitor, ListaArranjo<Demanda*>& listaDeDemandas){
    int numDemandas;
    
    leitor >> ETA >> GAMA >> DELTA >> ALFA >> BETA >> LAMBDA;
    leitor >> numDemandas;

    for (int i = 0; i < numDemandas; i++){
        int id;
        double tempo, ox, oy, dx, dy;
        leitor >> id >> tempo >> ox >> oy >> dx >> dy;

        Ponto origem(ox, oy);
        Ponto destino(dx, dy);

        listaDeDemandas.push_back(new Demanda(id, tempo, origem, destino));
    }
    return numDemandas;
}

//agrupa demandas em corridas e agenda os primeiros eventos
void construirCorridas(ListaArranjo<Demanda*>& listaDeDemandas, Escalonador& escalonador, ListaArranjo<Corrida*>& corridasParaDeletar){
    int numDemandas = listaDeDemandas.size();
    //controle para marcar demandas que já foram agrupadas
    bool* alocada = new bool[numDemandas];
    for (int i = 0; i < numDemandas; i++){
        alocada[i] = false;
    }

    //loop principal, itera por cada demanda base
    for (int i = 0; i < numDemandas; i++){
        if (alocada[i]) continue;

        Demanda* c0 = listaDeDemandas[i];
        
        //cria uma nova corrida
        Corrida* novaCorrida = new Corrida(GAMA);
        novaCorrida->adicionarDemanda(c0);
        alocada[i] = true;//marca c0 como alocada

        //loop secundário que tenta fazer o agrupamento com c0
        for (int j = i + 1; j < numDemandas; j++){
            if (alocada[j]) continue;

            Demanda* ci = listaDeDemandas[j];

            //filtro de tempo
            if ((ci->getTempo() - c0->getTempo()) >= DELTA){
                break;
            }

            //filtro da capacidade de passageiros
            if (novaCorrida->getNumPassageiros() >= ETA){
                break;
            }

            //filtro distâncias alfa e beta
            if (!novaCorrida->checaDistancias(ci, ALFA, BETA)){
                break;
            }

            //filtro eficiencia lamba
            novaCorrida->adicionarDemanda(ci); //tenta adicionar para testar
            novaCorrida->gerarRotaBasica(); //gera a rota temporária

            if (novaCorrida->calcularEficiencia() < LAMBDA){
                //falhou, desfaz
                novaCorrida->removerUltimaDemanda();
                break;
            } else {
                //sucesso, aloca permanentemente 
                alocada[j] = true;
            }
        }

        //gera a rota final
        novaCorrida->gerarRotaBasica();
        
        ////cria o primeiro evento
        Evento eventoInicial = novaCorrida->gerarEventoInicial();
        escalonador.inserirEvento(eventoInicial);//adiciona o evento na fila de prioridade
        
        corridasParaDeletar.push_back(novaCorrida);

    }

    delete[] alocada; //limpa o controle
}

//executa a simulação de eventos discretos
void executarSimulacao(Escalonador& escalonador){
    std::cout << std::fixed << std::setprecision(2);

    //loop principal da simulação, processa eventos em ordem de tempo
    while (!escalonador.vazio()){
        
        //retira o próximo evento (menor tempo) do heap
        Evento evento = escalonador.retirarProximoEvento();
        Corrida* corrida = evento.getCorrida();

        //processa o evento atual e recebe o próximo evento
        Evento proximoEvento = corrida->processarEvento(evento);

        //se for o fim, imprime as estatísticas
        if (proximoEvento.getTipo() == FIM_DA_CORRIDA){
            
            std::cout << evento.getTempo() << " ";
            std::cout << corrida->getDistanciaTotal() << " ";
            std::cout << corrida->getNumParadas() << " ";

            for (int i = 0; i < corrida->getNumParadas(); i++){
                Parada* parada = corrida->getParada(i);
                std::cout << parada->coordenadas.x << " " << parada->coordenadas.y << (i == corrida->getNumParadas() - 1 ? "" : " ");
            }
            std::cout << std::endl;

        } else{
            //se não, insere o próximo evento no escalonador
            escalonador.inserirEvento(proximoEvento);
        }
    }
}

//função auxiliar para liberar toda a memória alocada com new
void limparMemoria(ListaArranjo<Demanda*>& demandas, ListaArranjo<Corrida*>& corridas){
    for (int i = 0; i < corridas.size(); i++){
        delete corridas[i];
    }

    for (int i = 0; i < demandas.size(); i++){
        delete demandas[i];
    }
}


int main(int argc, char* argv[]){
    
    //bloco de gerenciamento de entrada
    std::ifstream fileStream;
    std::istream* leitor = &std::cin;

    if (argc > 1) {
        fileStream.open(argv[1]);
        if (!fileStream.is_open()){
            std::cerr << "Erro: Não foi possível abrir o arquivo " << argv[1] << std::endl;
            return 1;
        }
        leitor = &fileStream;
    }

    //leitura dos dados
    ListaArranjo<Demanda*> listaDeDemandas;
    lerEntrada(*leitor, listaDeDemandas);

    //agrupamento e criação de Corridas
    Escalonador escalonador;
    ListaArranjo<Corrida*> corridasParaDeletar;
    construirCorridas(listaDeDemandas, escalonador, corridasParaDeletar);
    
    //simulação de eventos
    executarSimulacao(escalonador);

    //limpeza da memória alocada
    limparMemoria(listaDeDemandas, corridasParaDeletar);

    if (fileStream.is_open()){
        fileStream.close();
    }

    return 0;
}