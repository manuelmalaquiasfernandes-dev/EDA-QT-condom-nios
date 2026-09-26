#include "listafracoes.h"
#include "listacondominos.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;



ListaFracoes::ListaFracoes(){
    cabeca=nullptr;
}

ListaFracoes::~ListaFracoes(){
    CNolistafracoes* atual=cabeca;
    while(atual!=nullptr){
        CNolistafracoes* proximo=atual->proximo;
        delete atual;
        atual=proximo;
    }
}

void ListaFracoes:: inserirFracao(){
    unsigned int codigo=0;
    unsigned int codigoProprietario;
    char identificacao[4];
    char descricao[16];
    float permilagem;

    cout << "NOVA FRACAO" << endl;
    bool codigoValido=false;

    while(codigoValido==false){
        cout << "Insira o codigo da fracao: ";
        cin >> codigo;

        if(cin.fail() || codigo<=0){
            cout << "O codigo deve ser maior que zero" << endl << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } 
        else{
            CNolistafracoes *atual=cabeca;
            bool codigoRepetido=false;
            while(atual!=nullptr){
                if(atual->fracao.returnCodigo()==codigo){
                    codigoRepetido=true;
                }
                atual=atual->proximo;
            }
            if(codigoRepetido==true){
                cout << "Ja existe uma fracao com o codigo " << codigo << endl << endl;
            }
            else{
                codigoValido=true;
            }
        }
    }

    cin.ignore(1000, '\n');

    cout << "Insira a identificacao da fracao: ";
    cin.getline(identificacao, 4);
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Insira a descricao da fracao: ";
    cin.getline(descricao, 16);
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Insira a permilagem: ";
    while(!(cin >> permilagem) || permilagem <= 0){
        cout << "Insira uma permilagem valida: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Insira o codigo do Condomino: ";
    while(!(cin >> codigoProprietario) || codigoProprietario == 0){
        cout << "Insira um codigo de condomino valido: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    Fracao novaFracao(codigo, identificacao, descricao, permilagem, codigoProprietario);

    CNolistafracoes* novo = new CNolistafracoes{novaFracao, nullptr};

    if(cabeca==nullptr){
        cabeca=novo;
    }
    else{
        CNolistafracoes *atual=cabeca;
        while(atual->proximo!=nullptr){
            atual=atual->proximo;
        }
        atual->proximo=novo;
    }
    cout << endl << "Fracao criada" << endl;
    guardarEmFicheiro("fracoes.txt");
}

void ListaFracoes:: mostraFracoes()const{
    if(cabeca==nullptr){
        cout << "A lista de fracoes esta vazia." << endl;
        return;
    }
    CNolistafracoes *atual=cabeca;
    cout <<  endl << "LISTA DE FRACOES" << endl << endl;
    while(atual!=nullptr){
        cout << "Codigo: " << atual->fracao.returnCodigo() << endl << "Identificacao: " << atual->fracao.returnIdentificacao() << endl << "Descricao: " << atual->fracao.returnDescricao() << endl << "Permilagem: " << fixed << setprecision(2) << atual->fracao.returnPermilagem() << endl << "Codigo Proprietario: " << atual->fracao.returnCodigoCondomino() << endl << endl;
        atual=atual->proximo;
    }
}

bool ListaFracoes::verificaPermilagem()const{
    float soma=0.0;
    CNolistafracoes* atual=cabeca;
    while(atual!=nullptr){
        soma=soma+atual->fracao.returnPermilagem();
        atual=atual->proximo;
    }
    if(soma==1000){
        return true;
    }
    return false;
}

void ListaFracoes::atribuirDonoAFracao(unsigned int codigoFracao, unsigned int codigoCondomino){
    CNolistafracoes *atual=cabeca;
    while(atual!=nullptr){
        if(atual->fracao.returnCodigo() == codigoFracao){
            atual->fracao.atualizaCodigoCondomino(codigoCondomino);
            cout << "Fracao " << codigoFracao << " e propriedade do condomino " << codigoCondomino << endl;
            guardarEmFicheiro("fracoes.txt");
            return;
        }
        atual=atual->proximo;
    }
    cout << "Fracao nao encontrada" << endl;
}

void ListaFracoes :: guardarEmFicheiro(string nomeFicheiro) const{
    ofstream ficheiro(nomeFicheiro); 
    if(!ficheiro.is_open()){
        cout << "Nao foi possivel abrir o ficheiro para guardar os dados" << endl;
        return;
    }
    CNolistafracoes *atual=cabeca;
    while(atual!=nullptr){
        ficheiro << atual->fracao.returnCodigo() << endl;
        ficheiro << atual->fracao.returnIdentificacao() << endl;
        ficheiro << atual->fracao.returnDescricao() << endl;
        ficheiro << atual->fracao.returnPermilagem() << endl;
        ficheiro << atual->fracao.returnCodigoCondomino() << endl;
        
        atual=atual->proximo;
    }
    ficheiro.close(); 
}
void ListaFracoes::lerDeFicheiro(string nomeFicheiro){
    ifstream ficheiro(nomeFicheiro);
    if(!ficheiro.is_open()) 
        return;
    string linha;
    while(getline(ficheiro, linha)){
        if (linha=="") {
            continue; 
        }
        unsigned int codigo = stoi(linha);
        
        string identificacaoString, descricaoString;
        getline(ficheiro, identificacaoString);
        getline(ficheiro, descricaoString);

        char identificacao[4]; 
        char descricao[16];
        strncpy(identificacao, identificacaoString.c_str(), 3);
        identificacao[3] = '\0';
        strncpy(descricao, descricaoString.c_str(), 15);
        descricao[15] = '\0';

        string permilagemString;
        string codigoCondominoString;
        getline(ficheiro, permilagemString);
        float permilagem=stof(permilagemString);
        getline(ficheiro, codigoCondominoString);
        unsigned int codigoCondomino=stoi(codigoCondominoString);
        
        Fracao frac(codigo, identificacao, descricao, permilagem, codigoCondomino);
        CNolistafracoes *novo=new CNolistafracoes{frac, nullptr};
        
        if(cabeca==nullptr){
            cabeca=novo;
        }
        else{
            CNolistafracoes *atual=cabeca;
            while(atual->proximo!=nullptr){
                atual=atual->proximo;
            }
            atual->proximo=novo;
        }
    }
    ficheiro.close();
}

CNolistafracoes* ListaFracoes :: returnCabeca() const{
    return cabeca;
}