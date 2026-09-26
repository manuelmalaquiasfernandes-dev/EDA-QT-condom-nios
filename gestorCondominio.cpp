#include "GestorCondominio.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

GestorCondominio::GestorCondominio(){
    saldoOrcamento = 0.0;
    saldoAtualCondominio = 0.0;
    anoAberto = false;
}

void GestorCondominio::carregarDados(){
    listaMovimentosGeral.lerDeFicheiro("movimentos.txt");
    listaTiposGeral.lerDeFicheiro("tipos.txt");
    ifstream fin("orcamento.txt");
    if(fin.is_open()){
        fin >> saldoOrcamento >> saldoAtualCondominio >> anoAberto;
        fin.close();
    } else {
        anoAberto = false; 
    }
}

void GestorCondominio::guardarDados()const {
    listaMovimentosGeral.guardarEmFicheiro("movimentos.txt");
    listaTiposGeral.guardarEmFicheiro("tipos.txt");
    ofstream fout("orcamento.txt");
    if(fout.is_open()){
        fout <<saldoOrcamento<<endl<<saldoAtualCondominio<<endl<<anoAberto<<endl;
        fout.close();
    }
}

void GestorCondominio::inserirNovoTipo(){
    unsigned int codigo;
    char descricao[21];
    
    cout <<"Inserir Novo Tipo"<<endl;
    cout <<"Codigo do tipo de movimento:";
    while (!(cin >>codigo)){
        cout <<"Entrada invalida,insira apenas numeros:";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Descricao do tipo de movimento:";
    cin.ignore();
    cin.getline(descricao,21);
    
    TipoMovimento::DiferentesMovimentos pacoteTipo; 
    pacoteTipo._codigo=codigo; 
    pacoteTipo.descricao=descricao;

    TipoMovimento novoTipo(pacoteTipo);  
    listaTiposGeral.inserirTipo(novoTipo);

    cout <<endl<<"Tipo de movimento inserido com sucesso!"<<endl;
} 

void GestorCondominio::mostraTipos()const {
    listaTiposGeral.mostraTipos(); 
}

void GestorCondominio::inserirReceita(ListaCondominos& listaCondominos){ 
    Movimentos::DadosdeMovimentos pacoteMovi;
    unsigned int codigo,codigoTipo,origem;
    double valor;
    char dataTemp[11];
    char descricao[31];
    cout <<endl<<"NOVA RECEITA"<<endl;
    cout <<"Insira o codigo do movimento:";
    while (!(cin >>codigo)) {
        cout <<"Entrada invalida,insira apenas numeros:";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Insira a data:";
    cin >>dataTemp;
    cout <<"Insira o valor:";
    while (!(cin >>valor)) {
        cout <<"Entrada invalida,insira apenas numeros:";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Insira o codigo do tipo de movimento:";
    while (!(cin >>codigoTipo)) {
        cout <<"Entrada invalida,insira apenas numeros:";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Insira a descricao do movimento:";
    cin.ignore();
    cin.getline(descricao,31);
    cout <<"Insira a origem:";
    while (!(cin >>origem)) {
        cout <<"Entrada invalida,insira apenas numeros:";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    pacoteMovi._Codigo=codigo;
    pacoteMovi._descricao=descricao;
    pacoteMovi._valor=valor;
    pacoteMovi._data=dataTemp;
    pacoteMovi._CodigoTipo=codigoTipo;
    pacoteMovi._origem=origem;
    saldoAtualCondominio=saldoAtualCondominio+pacoteMovi._valor;
    pacoteMovi._saldo=saldoAtualCondominio;
    Movimentos novoMov(pacoteMovi);
    listaMovimentosGeral.inserirMovimento(novoMov);
    
    if(pacoteMovi._origem!=0) {
        listaCondominos.atualizarSaldoCondomino(pacoteMovi._origem,pacoteMovi._valor);
    }
    
    cout << endl <<"Receita inserida com sucesso!"<<endl;
}

void GestorCondominio::inserirDespesa(ListaCondominos& listaCondominos) { 
    Movimentos::DadosdeMovimentos pacoteMovi;
    unsigned int codigo,codigoTipo,origem;
    double valor,valorLido;
    char dataTemp[11];
    char descricao[31];

    cout <<endl<<"NOVA DESPESA"<<endl;
    cout <<"Insira o codigo do movimento:";
    while (!(cin >>codigo)) {
        cout <<"Entrada invalida,insira apenas numeros:";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Insira a data:";
    cin >>dataTemp;
    cout << "Insira o valor : ";
    while (!(cin >>valorLido)) {
        cout <<"Entrada invalida,insira apenas numeros:";
        cin.clear();
        cin.ignore(1000,'\n');
    }

    if (valorLido>0) {
        valor=-valorLido;
    } else {
        valor=valorLido;
    }

    cout <<"Insira o codigo do tipo de movimento:";
    while (!(cin >>codigoTipo)) {
        cout <<"Entrada invalida,insira apenas numeros:";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Insira a descricao do movimento:";
    cin.ignore();
    cin.getline(descricao,31);
    cout <<"Insira a origem:";
    while (!(cin >>origem)) {
        cout <<"Entrada invalida,insira apenas numeros:";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    
    pacoteMovi._Codigo=codigo;
    pacoteMovi._descricao=descricao;
    pacoteMovi._valor=valor;
    pacoteMovi._data=dataTemp;
    pacoteMovi._CodigoTipo=codigoTipo;
    pacoteMovi._origem=origem;
    
    saldoAtualCondominio=saldoAtualCondominio+pacoteMovi._valor;
    pacoteMovi._saldo=saldoAtualCondominio;
    
    Movimentos novoMov(pacoteMovi);
    listaMovimentosGeral.inserirMovimento(novoMov);
    if(pacoteMovi._origem!=0){
        listaCondominos.atualizarSaldoCondomino(pacoteMovi._origem,pacoteMovi._valor);
    }
    
    cout <<endl<<"Despesa inserida com sucesso!"<<endl;
}

void GestorCondominio::mostraTodosMovimentos()const {
    listaMovimentosGeral.mostraGeral();
}

void GestorCondominio::mostraReceitas()const {
    listaMovimentosGeral.mostraReceitas();
}

void GestorCondominio::mostraDespesas()const {
    listaMovimentosGeral.mostraDespesas();
}

void GestorCondominio::mostraMovimentosPorCondomino(unsigned int codigoCondomino)const {
    listaMovimentosGeral.mostraMovimentosPorCondomino(codigoCondomino);
}

void GestorCondominio::mostraMovimentosPorTipo(unsigned int codigoTipo)const {
    listaMovimentosGeral.mostraMovimentosPorTipo(codigoTipo);
}

void GestorCondominio::inserirOrcamento(ListaCondominos& listaCondominos,ListaFracoes& listaFracoes){
    cout <<"ORCAMENTO ANUAL"<<endl;
    cout <<"Qual o valor do Orcamento Anual em euros?: ";
    while (!(cin >>saldoOrcamento)){
        cout <<"Entrada invalida, insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    CNoListaCondominos* atualC = listaCondominos.returnCabeca();
    while(atualC!=nullptr){
        unsigned int cod=atualC->condomino.returnCodigo();
        float permilagem=0.0;
        CNolistafracoes* atualF=listaFracoes.returnCabeca();
        while(atualF != nullptr){
            if(atualF->fracao.returnCodigoCondomino() == cod){
                permilagem=permilagem+atualF->fracao.returnPermilagem();
            }
            atualF=atualF->proximo;
        }
        double quota=(permilagem / 1000.0)*saldoOrcamento;
        listaCondominos.atualizarSaldoCondomino(cod, -quota); 
        atualC=atualC->proximo;
    }
    cout <<endl<<"Orcamento inserido e quotas anuais debitadas aos condominos!"<<endl;
}

void GestorCondominio::inserirSaldoInicial(){
    cout <<"SALDO INICIAL"<<endl;
    cout <<"Qual o Saldo Inicial do Condominio em euros?: ";
    while (!(cin >>saldoAtualCondominio)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    anoAberto=true;
}
    
void GestorCondominio::mostraResumoFinanceiro()const {
    cout <<endl;
    cout <<fixed<<setprecision(2);
    cout <<"Saldo do Orcamento:"<<saldoOrcamento<<"EUR"<<endl;
    cout <<"Saldo Atual do Condominio: "<<saldoAtualCondominio<<"EUR"<<endl; 
    cout <<endl;
}

void GestorCondominio::modificarTipo(){
    unsigned int codigo;
    char novaDescricao[21];
    
    cout <<"Modificar Tipo de Movimento"<<endl;
    cout <<"Codigo do tipo a modificar: ";
    while (!(cin >>codigo)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Nova descricao:";
    cin.ignore();
    cin.getline(novaDescricao,21);
    
    if(listaTiposGeral.modificarTipo(codigo,novaDescricao)){
        cout <<endl<<"Tipo de movimento modificado com sucesso!"<<endl;
    } else {
        cout <<endl<<"Tipo de movimento com o codigo: "<<codigo<<"nao encontrado."<<endl;
    }
}

void GestorCondominio::modificarReceita(){
    unsigned int codigo;
    char novaData[11];
    double novoValor,diferenca;
    unsigned int novoCodigoTipo,novaOrigem;
    char novaDescricao[31];

    cout <<"Modificar Receita"<<endl;
    cout <<"Codigo do movimento a modificar:";
    while (!(cin >>codigo)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Nova data:";
    cin >>novaData;
    cout <<"Novo valor:";
    while (!(cin >>novoValor)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Novo codigo do tipo de movimento: ";
    while (!(cin >>novoCodigoTipo)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Nova descricao: ";
    cin.ignore();
    cin.getline(novaDescricao,31);
    cout << "Nova origem:";
    while (!(cin >>novaOrigem)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }

    if(listaMovimentosGeral.modificarMovimento(codigo,novaData,novoValor,novoCodigoTipo,novaDescricao,novaOrigem,diferenca)){
        saldoAtualCondominio=saldoAtualCondominio+diferenca;
        cout <<endl<<"Receita modificada com sucesso!"<<endl;
    } else {
        cout <<endl<<"Movimento com o codigo: "<< codigo<<"nao encontrado"<<endl;
    }
}

void GestorCondominio::modificarDespesa(){
    unsigned int codigo;
    char novaData[11];
    double novoValor,diferenca;
    unsigned int novoCodigoTipo,novaOrigem;
    char novaDescricao[31];

    cout <<"Modificar Despesa"<<endl;
    cout <<"Codigo do movimento a modificar: ";
    while (!(cin >>codigo)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Nova data:";
    cin >>novaData;
    cout <<"Novo valor:";
    while (!(cin >>novoValor)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }

    if (novoValor>0) {
        novoValor= -novoValor;
    }

    cout <<"Novo codigo do tipo de movimento: ";
    while (!(cin >>novoCodigoTipo)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cout <<"Nova descricao: ";
    cin.ignore();
    cin.getline(novaDescricao,31);
    cout <<"Nova origem: ";
    while (!(cin >>novaOrigem)) {
        cout <<"Entrada invalida,insira apenas numeros: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }

    if(listaMovimentosGeral.modificarMovimento(codigo,novaData,novoValor,novoCodigoTipo,novaDescricao,novaOrigem,diferenca)){
        saldoAtualCondominio=saldoAtualCondominio+diferenca;
        cout <<endl<<"Despesa modificada com sucesso!"<<endl;
    } else {
        cout <<endl<<"Movimento com o codigo"<< codigo<<"nao encontrado"<<endl;
    }
}

bool GestorCondominio::isAnoAberto()const{
    return anoAberto;
}

void GestorCondominio::mostraResumoTodosCondominos(ListaCondominos& listaCondominos,ListaFracoes& listaFracoes)const{
    CNoListaCondominos* atualC = listaCondominos.returnCabeca();
    if(atualC==nullptr) {
        cout <<"Nao existem condominos registados."<<endl;
        return;
    }
    cout <<endl<<"RESUMO ANUAL POR CONDOMINO"<<endl;
    while(atualC!=nullptr) {
        unsigned int cod=atualC->condomino.returnCodigo();
        string nome=atualC->condomino.returnNome();
        double saldo=atualC->condomino.returnSaldo();
        float permilagem=0.0;
        CNolistafracoes* atualF=listaFracoes.returnCabeca();
        while(atualF!=nullptr) {
            if(atualF->fracao.returnCodigoCondomino()==cod) {
                permilagem=permilagem+atualF->fracao.returnPermilagem();
            }
            atualF=atualF->proximo;
        }
        double quota=(permilagem / 1000.0)*saldoOrcamento;
        cout << endl;
        cout <<"Condomino: " <<nome<< "   Codigo: "<<cod<<endl;
        cout <<"Quota Anual: "<<fixed<<setprecision(2)<<quota<<" EUR"<<endl;
        cout <<"Saldo em divida/credito: "<<saldo<<" EUR"<<endl;
        cout <<"Movimentos: "<<endl;
        listaMovimentosGeral.mostraMovimentosPorCondomino(cod);
        atualC=atualC->proximo;
    }
    cout <<endl;
}
