#ifndef LISTACONDOMINOS_H
#define LISTACONDOMINOS_H

#include "condomino.h"
#include "listafracoes.h"

class CNoListaCondominos{
public:
    Condomino condomino;
    CNoListaCondominos *proximo;
};

class ListaCondominos {
private:
    CNoListaCondominos *cabeca;
public:
    ListaCondominos();
    ~ListaCondominos();
    Condomino lerDados();
    void inserirCondomino(CNolistafracoes* fracao);
    void mostraCondominos(CNolistafracoes* fracao) const;
    void eleminaCondominos();
    void modificaCondominos(CNolistafracoes* fracao);
    float atualizaPermilagem(unsigned int codCondomino, CNolistafracoes *cabeca)const;
    void guardarEmFicheiro(string nomeFicheiro) const;
    void lerDeFicheiro(string nomeFicheiro);
    bool atualizarSaldoCondomino(unsigned int codigoCondomino, double valor);
    CNoListaCondominos* returnCabeca()const{ return cabeca; }

};

#endif // LISTACONDOMINOS_H