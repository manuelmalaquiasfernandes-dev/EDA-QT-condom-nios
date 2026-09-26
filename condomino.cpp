#include "condomino.h"
#include <string>
using namespace std;

Condomino::Condomino(unsigned int codigo, string nome, string morada, string email, string telefone, double saldo) {
    this->codigo=codigo;
    this->nome=nome;
    this->morada=morada;
    this->email=email;
    this->numTelemovel=telefone;
    this->saldo=saldo;
}

unsigned int Condomino::returnCodigo() const {
    return codigo;
}
string Condomino::returnNome() const {
    return nome;
}
string Condomino::returnMorada() const {
    return morada;
}
string Condomino::returnNumTelemovel() const {
    return numTelemovel;
}
string Condomino::returnEmail() const {
    return email;
}

double Condomino::returnSaldo() const {
    return saldo;
}

void Condomino:: defineSaldo(double novoSaldo) {
    saldo=novoSaldo;
}

void Condomino::atualizaMorada(string novaMorada) {
    morada=novaMorada;
}

void Condomino::atualizaSaldo(double valor) {
    saldo=saldo+valor;
}