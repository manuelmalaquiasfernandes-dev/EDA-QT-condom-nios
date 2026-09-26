#ifndef TIPOMOVIMENTO_H
#define TIPOMOVIMENTO_H
#include <string>

using namespace std;

class TipoMovimento{
private:
    unsigned int codigo;
    char descricao[21];
public:
    struct DiferentesMovimentos{
        unsigned int _codigo;
        const char*descricao;
    };

    TipoMovimento(DiferentesMovimentos dados);

    unsigned int obterCodigo()const;
    const char*obterDescricao()const;

    void modificarDescricao(const char*novaDescricao);
};


class CNoListaTipoMovimento {
public:
    TipoMovimento tipo;
    CNoListaTipoMovimento*proximo;

    CNoListaTipoMovimento(TipoMovimento t):tipo(t),proximo(nullptr) {}
};

class ListaTipoMovimento{
private:
    CNoListaTipoMovimento*cabeca; 

public:
    ListaTipoMovimento();
    ~ListaTipoMovimento();

    void inserirTipo(TipoMovimento t);
    bool modificarTipo(unsigned int codigo, const char*novaDescricao);
    void mostraTipos()const; 

    void guardarEmFicheiro(string nomeFicheiro)const;
    void lerDeFicheiro(string nomeFicheiro);
};

#endif // TIPOMOVIMENTO_H
