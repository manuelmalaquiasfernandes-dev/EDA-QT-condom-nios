#ifndef FRACAO_H
#define FRACAO_H

class Fracao{
    unsigned int codigo;
    char identificacao[4];
    char descricao[16];
    float permilagem;
    unsigned int codigoCondomino;
public:
    Fracao(unsigned int codigo, char identificacao[], char descricao[], float permilagem, unsigned int codigoProprietario);
    unsigned int returnCodigo() const;
    const char* returnIdentificacao() const;
    const char* returnDescricao() const;
    float returnPermilagem() const;
    unsigned int returnCodigoCondomino() const;
    void atualizaCodigoCondomino(unsigned int novoCodigo);

};

#endif // FRACAO_H

