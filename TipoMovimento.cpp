#include "TipoMovimento.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

TipoMovimento::TipoMovimento(DiferentesMovimentos dados){
    if(dados._codigo>0){
        codigo=dados._codigo;
    }else{
        codigo=1; 
    }
    strncpy(descricao,dados.descricao,20);
    descricao[20]='\0';
}

unsigned int TipoMovimento::obterCodigo()const{ 
    return codigo;
}

const char*TipoMovimento::obterDescricao()const{
    return descricao;
}

void TipoMovimento::modificarDescricao(const char*novaDescricao){ 
    strncpy(descricao,novaDescricao,20 );
    descricao[20]='\0';
}

ListaTipoMovimento::ListaTipoMovimento(){
    cabeca=nullptr;
}

void ListaTipoMovimento::inserirTipo(TipoMovimento t){
    CNoListaTipoMovimento*verifica=cabeca;
    while(verifica!=nullptr){
        if(verifica->tipo.obterCodigo()==t.obterCodigo()){
            cout<<"Erro: Ja existe um tipo com esse codigo!"<<endl;
            return;
        }
        verifica=verifica->proximo;
    }
    CNoListaTipoMovimento*novoNo=new CNoListaTipoMovimento(t);
    if(cabeca==nullptr){
        cabeca=novoNo;
    }else{
        CNoListaTipoMovimento*atual=cabeca;
        while(atual->proximo!=nullptr){
            atual=atual->proximo;
        }
        atual->proximo=novoNo;
    }
}

 ListaTipoMovimento::~ListaTipoMovimento(){
    CNoListaTipoMovimento*atual=cabeca;
    CNoListaTipoMovimento*proximoNo;

    while(atual!=nullptr){
        proximoNo=atual->proximo;
        delete atual;
        atual=proximoNo;
    }
 }

void ListaTipoMovimento::mostraTipos()const{
    CNoListaTipoMovimento*atual=cabeca;
    if(atual==nullptr){
        cout<<"Nao existem tipos de movimentos registados."<<endl;
        return;
    }
    while(atual!=nullptr){
        cout<<"Codigo:"<<atual->tipo.obterCodigo()<<"Descricao:"<<atual->tipo.obterDescricao()<<endl;
        atual=atual->proximo;
    }
}

void ListaTipoMovimento::guardarEmFicheiro(string nomeFicheiro)const {
    ofstream ficheiro(nomeFicheiro);
    if(!ficheiro.is_open()){
        cout <<"Erro ao abrir o ficheiro para escrita."<<endl;
        return;
    }
    CNoListaTipoMovimento*atual = cabeca;
    while(atual!=nullptr){
        ficheiro <<atual->tipo.obterCodigo()<< endl<<atual->tipo.obterDescricao()<<endl;
        atual=atual->proximo;
    }
    ficheiro.close();
}

void ListaTipoMovimento::lerDeFicheiro(string nomeFicheiro) {
    ifstream ficheiro(nomeFicheiro);
    if(!ficheiro.is_open()){
        cout <<"Ficheiro de tipos nao encontrado, lista iniciada vazia"<<endl;
        return;
    }
    TipoMovimento::DiferentesMovimentos dados;
    string descTemp;
    while(ficheiro >> dados._codigo){
        ficheiro.ignore(1000, '\n');
        getline(ficheiro, descTemp);
        char tempDesc[21];
        strncpy(tempDesc, descTemp.c_str(), 20);
        tempDesc[20] = '\0';
        dados.descricao = tempDesc; 
        TipoMovimento t(dados);
        inserirTipo(t);
    }
    ficheiro.close();
}

bool ListaTipoMovimento::modificarTipo(unsigned int codigo, const char*novaDescricao){
    CNoListaTipoMovimento*atual=cabeca;
    while(atual!=nullptr){
        if(atual->tipo.obterCodigo()==codigo){
            atual->tipo.modificarDescricao(novaDescricao);
            guardarEmFicheiro("tipos.txt"); 
            return true;
        }
        atual=atual->proximo;
    }
    return false;
}