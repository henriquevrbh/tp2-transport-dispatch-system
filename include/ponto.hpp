#ifndef PONTO_HPP
#define PONTO_HPP

struct Ponto{
    double x; //coordenada x
    double y; //coordenada y

    //construtor padrão (ponto 0,0)
    Ponto();
    //construtor parametrizado
    Ponto(double x, double y); 

    //calcula a distância euclidiana
    double distancia(const Ponto& ponto) const;
};

#endif