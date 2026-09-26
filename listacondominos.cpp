#include "listacondominos.h"
#include "listafracoes.h"
#include "condomino.h"
#include "fracao.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;


ListaCondominos::ListaCondominos(){
    cabeca=nullptr;
}

ListaCondominos::~ListaCondominos(){
    CNoListaCondominos* atual=cabeca;
    while(atual!=nullptr){
        CNoListaCondominos *proximo=atual->proximo;
        delete atual;
        atual=proximo;
    }
}

Condomino ListaCondominos::lerDados(){
    unsigned int codigoNovo;
    string nomeNovo;
    string moradaNovo;
    string emailNovo;
    string numTelemovelNovo;
    double saldoNovo;

    cout <<  endl << "NOVO CONDOMINO" << endl;
    bool repetido;
    do{
        repetido=false; 
        cout << "Insira o codigo do novo condomino: ";
        while(!(cin >> codigoNovo) || codigoNovo==0){
            cout << "Insira apenas numeros: ";
            cin.clear();
            cin.ignore(1000,'\n');
        }
        CNoListaCondominos *atual=cabeca;
        while(atual!=nullptr){
            if(atual->condomino.returnCodigo()==codigoNovo){
                cout << "Ja existe um condomino com o codigo " << codigoNovo << endl;
                repetido=true;
                break;
            }
            atual=atual->proximo;
        }
    }while(repetido);
    
    cin.ignore(1000, '\n');

    cout << "Insira o nome do condomino: ";
    getline(cin, nomeNovo); 

    cout << "Insira a morada do condomino: ";
    getline(cin, moradaNovo);

    cout << "Insira o email do condomino: ";
    cin >> emailNovo;

    cout << "Insira o numero de telemovel do condomino: ";
    cin >> numTelemovelNovo;

    cout << "Insira o saldo do condomino: ";
    cin >>saldoNovo;

    return Condomino(codigoNovo, nomeNovo, moradaNovo, emailNovo, numTelemovelNovo, saldoNovo);
}
void ListaCondominos::inserirCondomino(CNolistafracoes* fracao){
    Condomino novoCondomino=lerDados();
    CNoListaCondominos *atual=cabeca;
    while(atual!=nullptr){
        if(atual->condomino.returnCodigo()==novoCondomino.returnCodigo()){
            cout << "Ja existe um condomino com o codigo " << novoCondomino.returnCodigo() << endl;
            return;
        }
        atual=atual->proximo;
    }
    CNoListaCondominos *novo = new CNoListaCondominos{novoCondomino, nullptr};
    
    if(cabeca==nullptr){
        cabeca=novo;
    } 
    else{
        atual=cabeca;
        while(atual->proximo != nullptr){
            atual=atual->proximo;
        }
        atual->proximo=novo;
    }
    cout << "Condomino inserido" << endl;
    atualizaPermilagem(novo->condomino.returnCodigo(), fracao);
    guardarEmFicheiro("condominos.txt");
}

void ListaCondominos::modificaCondominos(CNolistafracoes* fracao){
    unsigned int codigo;
    cout << "Introduza o codigo do condomino que deseja modificar: ";
    cin >> codigo;

    CNoListaCondominos *atual=cabeca;
    while(atual!=nullptr && atual->condomino.returnCodigo()!=codigo){
        atual=atual->proximo;
    }

    if(atual==nullptr){
        cout << "Condomino nao encontrado" <<  endl << endl;
        return;
    }
    unsigned int codigoOriginal=atual->condomino.returnCodigo();
    double saldoOriginal=atual->condomino.returnSaldo();
    string nomeNovo, moradaNovo, emailNovo, numTelemovelNovo;

    cout << "Introduza os novos dados do condomino " << endl;
    cin.ignore(1000, '\n'); 

    cout << "Insira o nome do condomino: ";
    getline(cin, nomeNovo); 

    cout << "Insira a morada do condomino: ";
    getline(cin, moradaNovo);

    cout << "Insira o email do condomino: ";
    cin >> emailNovo;

    cout << "Insira o numero de telemovel do condomino: ";
    cin >> numTelemovelNovo;

    atual->condomino=Condomino(codigoOriginal, nomeNovo, moradaNovo, emailNovo, numTelemovelNovo, saldoOriginal);

    atualizaPermilagem(atual->condomino.returnCodigo(), fracao);
    guardarEmFicheiro("condominos.txt");
    cout << "A ficha do condomino foi modificada com sucesso" << endl << endl;
}

void ListaCondominos::mostraCondominos(CNolistafracoes *fracao) const{
    if(cabeca==nullptr) {
        cout << "A lista de condominos esta vazia" <<  endl << endl;
        return;
    }

    CNoListaCondominos *atual=cabeca;
    cout << "LISTA DE CONDOMINOS" << endl << endl;


    while(atual!=nullptr){
        cout << "Codigo: " << atual->condomino.returnCodigo() << endl << "Nome: " << atual->condomino.returnNome() << endl << "Saldo: " << fixed << setprecision(2) << atual->condomino.returnSaldo() << " EUR" << endl << endl;
        atualizaPermilagem(atual->condomino.returnCodigo(), fracao);
        atual=atual->proximo;
    }
}

void ListaCondominos :: eleminaCondominos(){
    unsigned int codigoRemover;
    cout << "Introduza o codigo do conomino que deseja remover: ";
    cin >> codigoRemover;
    CNoListaCondominos *atual=cabeca;
    CNoListaCondominos *anterior=nullptr;
    while(atual!=nullptr && atual->condomino.returnCodigo()!=codigoRemover){
        anterior=atual;
        atual=atual->proximo;
    }
    if(atual==nullptr){
        cout << "Condomino nao encontrado" <<  endl << endl;
        return;
    }
    if(anterior==nullptr) 
        cabeca=atual->proximo;
    else 
        anterior->proximo=atual->proximo;
    delete atual;
    guardarEmFicheiro("condominos.txt");
    cout << "Condomino removido" << endl << endl;
}

float ListaCondominos::atualizaPermilagem(unsigned int codigoCondomino, CNolistafracoes *fracao) const{
    float total=0.0;
    CNolistafracoes *atual=fracao;
    while(atual!=nullptr){
        if(atual->fracao.returnCodigoCondomino()==codigoCondomino){
            total=total+atual->fracao.returnPermilagem();
        }
        atual=atual->proximo;
    }
    cout << endl << "A permilagem do condomino com o codigo  " << codigoCondomino << " e " << setprecision(2) << fixed << total << endl << endl;
    return total;
}

void ListaCondominos::guardarEmFicheiro(string nomeFicheiro) const {
    ofstream ficheiro(nomeFicheiro); 
    if(!ficheiro.is_open()){
        cout << "Nao foi possivel abrir o ficheiro para guardar os dados!" << endl << endl;
        return;
    }
    CNoListaCondominos *atual=cabeca;
    while(atual!=nullptr){
        ficheiro << atual->condomino.returnCodigo() << endl;
        ficheiro << atual->condomino.returnNome() << endl;
        ficheiro << atual->condomino.returnMorada() << endl;
        ficheiro << atual->condomino.returnEmail() << endl;
        ficheiro << atual->condomino.returnNumTelemovel() << endl;
        ficheiro << atual->condomino.returnSaldo() << endl;

        atual=atual->proximo;
    }
    ficheiro.close(); 
}


void ListaCondominos::lerDeFicheiro(string nomeFicheiro){
    ifstream ficheiro(nomeFicheiro);
    if(!ficheiro.is_open()){
        return;
    }
    string linha;
    while(getline(ficheiro, linha)){
        if (linha == ""){
            continue; 
        }
        unsigned int codigo=stoi(linha);
        string nome;
        string morada;
        string email;
        string numTelemovel;
        string saldoString;
        double saldo;

        getline(ficheiro, nome);
        getline(ficheiro, morada);
        getline(ficheiro, email);
        getline(ficheiro, numTelemovel);
        getline(ficheiro, saldoString);
        saldo=stod(saldoString);

        Condomino condomino(codigo, nome, morada, email, numTelemovel, saldo);
        CNoListaCondominos *novo = new CNoListaCondominos{condomino, nullptr};
        if(cabeca==nullptr){
            cabeca=novo;
        }
        else{
            CNoListaCondominos *atual=cabeca;
            while(atual->proximo!=nullptr){
                atual=atual->proximo;
            }
            atual->proximo=novo;
        }
    }
    ficheiro.close(); 
}

bool ListaCondominos::atualizarSaldoCondomino(unsigned int codigoCondomino, double valor) {
    CNoListaCondominos *atual=cabeca;
    while(atual!=nullptr){
        if(atual->condomino.returnCodigo()==codigoCondomino){
            atual->condomino.atualizaSaldo(valor);
            guardarEmFicheiro("condominos.txt");
            return true;
        }
        atual=atual->proximo;
    }
    return false;
}
