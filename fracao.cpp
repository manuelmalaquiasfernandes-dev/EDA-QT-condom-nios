#include "fracao.h"
#include <cstring>
using namespace std;


Fracao::Fracao(unsigned int codigo, char identificacao[], char descricao[], float permilagem, unsigned int codigoCondomino) {
    this->codigo=codigo;
    strncpy(this->identificacao, identificacao, 3);
    this->identificacao[3] = '\0';
    strncpy(this->descricao, descricao, 15);
    this->descricao[15] = '\0';
    this->permilagem=permilagem;
    this->codigoCondomino = codigoCondomino;
}

unsigned int Fracao::returnCodigo() const {
    return codigo;
}

const char* Fracao :: returnIdentificacao() const{
    return identificacao;
}

const char* Fracao::returnDescricao() const {
    return descricao;
}

float Fracao::returnPermilagem() const {
    return permilagem;
}

unsigned int Fracao::returnCodigoCondomino() const {
    return codigoCondomino;
}

void Fracao::atualizaCodigoCondomino(unsigned int novoCodigo) {
    codigoCondomino=novoCodigo;
}
