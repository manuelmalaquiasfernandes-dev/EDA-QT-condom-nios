#ifndef CONDOMINO_H
#define CONDOMINO_H
#include <string>
using namespace std;
class Condomino{
    unsigned int codigo;
    string nome;
    string morada;
    string email;
    string numTelemovel;
    double saldo;


public:
    Condomino (unsigned int codigo, string nome, string morada, string email, string telefone, double saldo);
    unsigned int returnCodigo()const;
    string returnNome()const;
    double returnSaldo()const;

    string returnMorada() const;
    string returnEmail() const;
    string returnNumTelemovel() const;

    void defineSaldo(double saldoNovo);
    void atualizaMorada(string moradaNova);
    void atualizaSaldo(double saldo);
};

#endif
