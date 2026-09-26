#ifndef LISTAFRACOES_H
#define LISTAFRACOES_H
#include <string>
#include "fracao.h"
using namespace std;

class CNolistafracoes{
public:
    Fracao fracao;
    CNolistafracoes *proximo;
};


class ListaFracoes{
private:
    CNolistafracoes *cabeca;
public:
    ListaFracoes();
    ~ListaFracoes();
    void inserirFracao();
    void mostraFracoes()const;
    bool verificaPermilagem()const;
    void atribuirDonoAFracao(unsigned int codigoFracao, unsigned int codigoCondomino);
    void guardarEmFicheiro(string nomeFicheiro) const;
    void lerDeFicheiro(string nomeFicheiro);
    CNolistafracoes *returnCabeca() const;
};

#endif // LISTAFRACOES_H
