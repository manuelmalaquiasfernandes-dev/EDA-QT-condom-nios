#include "Movimentos.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

Movimentos::Movimentos(DadosdeMovimentos dados){ 
    Codigo = dados._Codigo;
    valor = dados._valor;
    CodigoTipo = dados._CodigoTipo;
    origem = dados._origem;
    saldoApos = dados._saldo;

    strncpy(data, dados._data, 10); 
    data[10] = '\0';

    strncpy(descricao, dados._descricao, 30); 
    descricao[30] = '\0';
}

unsigned int Movimentos::obterCodigoTipo() const { return CodigoTipo; }
double Movimentos::obterValor() const { return valor; }
unsigned int Movimentos::obterCodigo() const { return Codigo; }
const char* Movimentos::obterData() const { return data; }
const char* Movimentos::obterDescricao() const { return descricao; }
unsigned int Movimentos::obterOrigem() const { return origem; }
double Movimentos::obterSaldoApos() const { return saldoApos; }

void Movimentos::atualizaSaldo(double s){ saldoApos = s; }

static string paraChaveCronologica(const char* dStr) {
    if(strlen(dStr) >= 10) {
        char chave[9];
        
        chave[0] = dStr[6];
        chave[1] = dStr[7];
        chave[2] = dStr[8];
        chave[3] = dStr[9];
        chave[4] = dStr[3];
        chave[5] = dStr[4];
        chave[6] = dStr[0];
        chave[7] = dStr[1];
        chave[8] = '\0';
        
        return string(chave);
    }
    return string(dStr);
}

ListaMovimentos::ListaMovimentos(){ cabeca = nullptr; }

ListaMovimentos::~ListaMovimentos(){
    CNoListaMovimentos* atual = cabeca;
    CNoListaMovimentos* proximoNo;

    while(atual != nullptr){
        proximoNo = atual->proximo; 
        delete atual; 
        atual = proximoNo; 
    }
}

bool ListaMovimentos::inserirMovimento(Movimentos m){
    CNoListaMovimentos* verifica = cabeca;

    while(verifica != nullptr){
        if(verifica->movimento.obterCodigo() == m.obterCodigo()){
            cout << endl << "O codigo de movimento ja existe!" << endl;
            return false;
        }
        verifica = verifica->proximo;
    }

    double novoSaldo = 0;

    if(cabeca == nullptr){
        if(m.obterOrigem() == 0){ novoSaldo = m.obterValor(); }
        else{ novoSaldo = 0; }

        m.atualizaSaldo(novoSaldo);
        CNoListaMovimentos* novo = new CNoListaMovimentos(m);
        cabeca = novo;
    }
    else{ 
        CNoListaMovimentos* atual = cabeca;
        while(atual->proximo != nullptr){ atual = atual->proximo; }

        double saldoAnterior = atual->movimento.obterSaldoApos();

        if(m.obterOrigem() == 0){ novoSaldo = saldoAnterior + m.obterValor(); }
        else{ novoSaldo = saldoAnterior; }

        m.atualizaSaldo(novoSaldo);
        CNoListaMovimentos* novo = new CNoListaMovimentos(m);
        atual->proximo = novo;
    }

    guardarEmFicheiro("movimentos.txt");
    return true;
}

void ListaMovimentos::mostraMovimentos() const {
    CNoListaMovimentos* atual = cabeca; 

    if(atual == nullptr) {
        cout << endl << "Nao existem movimentos registados." << endl;
        return;
    }

    while(atual != nullptr){  
        cout << "Codigo:" << atual->movimento.obterCodigo() 
             << "   Data:" << atual->movimento.obterData() 
             << "   Valor:" << atual->movimento.obterValor() << " EUR" 
             << "   Tipo:" << atual->movimento.obterCodigoTipo() 
             << "   Descricao:" << atual->movimento.obterDescricao() 
             << "   Origem:" << atual->movimento.obterOrigem() 
             << "   Saldo:" << atual->movimento.obterSaldoApos() << " EUR" << endl;
        atual = atual->proximo; 
    }
}

void ListaMovimentos::mostraMovimentosPorCondomino(unsigned int CodigoCondomino) const {
    CNoListaMovimentos* atual = cabeca;
    bool encontrou = false;

    while(atual != nullptr){
        if(atual->movimento.obterOrigem() == CodigoCondomino){
            encontrou = true;
            cout << "Codigo:" << atual->movimento.obterCodigo() 
                 << "   Data:" << atual->movimento.obterData() 
                 << "   Valor:" << atual->movimento.obterValor() << " EUR" 
                 << "   Descricao:" << atual->movimento.obterDescricao() 
                 << "   Saldo:" << atual->movimento.obterSaldoApos() << " EUR" << endl;
        }
        atual = atual->proximo;
    }

    if(!encontrou){ cout << endl << "Nao existem movimentos deste condomino." << endl; }
}

void ListaMovimentos::mostraMovimentosPorTipo(unsigned int CodigoTipo) const {
    CNoListaMovimentos* atual = cabeca;
    double total = 0;
    bool encontrou = false;

    while(atual != nullptr){
        if(atual->movimento.obterCodigoTipo() == CodigoTipo){
            encontrou = true;
            cout << "Codigo:" << atual->movimento.obterCodigo() 
                 << "   Data:" << atual->movimento.obterData() 
                 << "   Valor:" << atual->movimento.obterValor() << " EUR" 
                 << "   Descricao:" << atual->movimento.obterDescricao() 
                 << "   Saldo:" << atual->movimento.obterSaldoApos() << " EUR" << endl;
            total = total + atual->movimento.obterValor();
        }
        atual = atual->proximo;
    }

    if(!encontrou){ cout << endl << "Nao existem movimentos deste tipo." << endl; } 
    else{ cout << endl << "Total deste tipo: " << total << " EUR" << endl; }
}

void ListaMovimentos::mostraReceitas() const {
    if(cabeca == nullptr){
        cout << endl << "Nao existem receitas registadas." << endl;
        return;
    }

    CNoListaMovimentos* sorted = nullptr;
    CNoListaMovimentos* atual = cabeca;
    bool encontrou = false;

    while(atual != nullptr){
        if(atual->movimento.obterValor() > 0){
            encontrou = true;
            CNoListaMovimentos* novo = new CNoListaMovimentos(atual->movimento);
            string k1 = paraChaveCronologica(novo->movimento.obterData());

            if(sorted == nullptr){
                sorted = novo;
            }else{
                string k2 = paraChaveCronologica(sorted->movimento.obterData());
                if(k1 < k2){
                    novo->proximo = sorted;
                    sorted = novo;
                }else{
                    CNoListaMovimentos* temp = sorted;
                    while(temp->proximo != nullptr){
                        string k3 = paraChaveCronologica(temp->proximo->movimento.obterData());
                        if(k1 < k3) break;
                        temp = temp->proximo;
                    }
                    novo->proximo = temp->proximo;
                    temp->proximo = novo;
                }
            }
        }
        atual = atual->proximo;
    }

    if(!encontrou){
        cout << endl << "Nao existem receitas registadas." << endl;
        return;
    }

    cout << endl << "Listagem de Receitas:" << endl;
    CNoListaMovimentos* tS = sorted;

    while(tS != nullptr){
        cout << "Codigo:" << tS->movimento.obterCodigo() 
             << "   Data:" << tS->movimento.obterData() 
             << "   Valor:" << tS->movimento.obterValor() << " EUR" 
             << "   Descricao:" << tS->movimento.obterDescricao() 
             << "   Saldo:" << tS->movimento.obterSaldoApos() << " EUR" << endl;
        tS = tS->proximo;
    }

    while(sorted != nullptr){
        CNoListaMovimentos* apagar = sorted;
        sorted = sorted->proximo;
        delete apagar;
    }
}

void ListaMovimentos::mostraDespesas() const {
    if(cabeca == nullptr){
        cout << endl << "Nao existem despesas registadas." << endl;
        return;
    }

    CNoListaMovimentos* sorted = nullptr;
    CNoListaMovimentos* atual = cabeca;
    bool encontrou = false;

    while(atual != nullptr){
        if(atual->movimento.obterValor() < 0){
            encontrou = true;
            CNoListaMovimentos* novo = new CNoListaMovimentos(atual->movimento);
            string k1 = paraChaveCronologica(novo->movimento.obterData());

            if(sorted == nullptr){
                sorted = novo;
            }else{
                string k2 = paraChaveCronologica(sorted->movimento.obterData());
                if(k1 < k2){
                    novo->proximo = sorted;
                    sorted = novo;
                }else{
                    CNoListaMovimentos* temp = sorted;
                    while(temp->proximo != nullptr){
                        string k3 = paraChaveCronologica(temp->proximo->movimento.obterData());
                        if(k1 < k3) break;
                        temp = temp->proximo;
                    }
                    novo->proximo = temp->proximo;
                    temp->proximo = novo;
                }
            }
        }
        atual = atual->proximo;
    }

    if(!encontrou){
        cout << endl << "Nao existem despesas registadas." << endl;
        return;
    }

    cout << endl << "Listagem de Despesas:" << endl;
    CNoListaMovimentos* tS = sorted;

    while(tS != nullptr){
        cout << "Codigo:" << tS->movimento.obterCodigo() 
             << "   Data:" << tS->movimento.obterData() 
             << "   Valor:" << tS->movimento.obterValor() << " EUR" 
             << "   Descricao:" << tS->movimento.obterDescricao() 
             << "   Saldo:" << tS->movimento.obterSaldoApos() << " EUR" << endl;
        tS = tS->proximo;
    }

    while(sorted != nullptr){
        CNoListaMovimentos* apagar = sorted;
        sorted = sorted->proximo;
        delete apagar;
    }
}

void ListaMovimentos::mostraGeral() const {
    if(cabeca == nullptr){
        cout << endl << "Nao existem movimentos registados." << endl;
        return;
    }

    CNoListaMovimentos* sortedCabeca = nullptr;
    CNoListaMovimentos* atual = cabeca;

    while(atual != nullptr){
        CNoListaMovimentos* novo = new CNoListaMovimentos(atual->movimento);
        string k1 = paraChaveCronologica(novo->movimento.obterData());

        if(sortedCabeca == nullptr){
            sortedCabeca = novo;
        }
        else{
            string k2 = paraChaveCronologica(sortedCabeca->movimento.obterData());
            
            if(k1 < k2){
                novo->proximo = sortedCabeca;
                sortedCabeca = novo;
            }else{
                CNoListaMovimentos* temp = sortedCabeca;
                
                while(temp->proximo != nullptr && paraChaveCronologica(temp->proximo->movimento.obterData()) <= k1){
                    temp = temp->proximo;
                }
                
                novo->proximo = temp->proximo;
                temp->proximo = novo;
            }
        }
        atual = atual->proximo;
    }

    cout << endl << "Listagem Geral: " << endl;
    CNoListaMovimentos* tempSorted = sortedCabeca;

    while(tempSorted != nullptr){
        cout << left 
             << "Codigo: " << setw(4) << tempSorted->movimento.obterCodigo()
             << "Data: " << setw(12) << tempSorted->movimento.obterData()
             << "Tipo: " << setw(3) << tempSorted->movimento.obterCodigoTipo()
             << "Desc: " << setw(18) << tempSorted->movimento.obterDescricao()
             << "Valor: " << setw(8) << fixed << setprecision(2) << tempSorted->movimento.obterValor() << " EUR "
             << "Saldo: " << setw(8) << tempSorted->movimento.obterSaldoApos() << " EUR ";
        
        if(tempSorted->movimento.obterValor() > 0){
            cout << "Receita" << endl;
        }else{
            cout << "Despesa" << endl;
        }
        tempSorted = tempSorted->proximo;
    }

    while(sortedCabeca != nullptr){
        CNoListaMovimentos* apagar = sortedCabeca;
        sortedCabeca = sortedCabeca->proximo;
        delete apagar;
    }
}
void Movimentos::modificarTudo(const char* novaData, double novoValor, unsigned int novoCodigoTipo, const char* novaDescricao, unsigned int novaOrigem){
    strncpy(data, novaData, 10);
    data[10] = '\0';
    valor = novoValor;
    CodigoTipo = novoCodigoTipo;
    strncpy(descricao, novaDescricao, 30);
    descricao[30] = '\0';
    origem = novaOrigem;
}

bool ListaMovimentos::modificarMovimento(unsigned int codigo, const char* novaData, double novoValor, unsigned int novoCodigoTipo, const char* novaDescricao, unsigned int novaOrigem, double &diferenca){
    CNoListaMovimentos* atual = cabeca;

    while(atual != nullptr){
        if(atual->movimento.obterCodigo() == codigo){
            double vV = (atual->movimento.obterOrigem() == 0) ? atual->movimento.obterValor() : 0;
            double nV = (novaOrigem == 0) ? novoValor : 0;
            diferenca = nV - vV;

            atual->movimento.modificarTudo(novaData, novoValor, novoCodigoTipo, novaDescricao, novaOrigem);

            CNoListaMovimentos* recalc = cabeca;
            double sA = 0;

            while(recalc != nullptr){
                if(recalc->movimento.obterOrigem() == 0) sA += recalc->movimento.obterValor();
                recalc->movimento.atualizaSaldo(sA);
                recalc = recalc->proximo;
            }

            guardarEmFicheiro("movimentos.txt");
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

void ListaMovimentos::guardarEmFicheiro(string nomeFicheiro) const {
    ofstream ficheiro(nomeFicheiro);

    if(!ficheiro.is_open()){
        cout << endl << "Erro ao abrir o ficheiro para escrita." << endl;
        return;
    }

    CNoListaMovimentos* atual = cabeca;

    while(atual != nullptr){
        ficheiro << atual->movimento.obterCodigo() << endl
                 << atual->movimento.obterData() << endl
                 << atual->movimento.obterValor() << endl
                 << atual->movimento.obterCodigoTipo() << endl
                 << atual->movimento.obterDescricao() << endl
                 << atual->movimento.obterOrigem() << endl
                 << atual->movimento.obterSaldoApos() << endl;
        atual = atual->proximo;
    }
    ficheiro.close();
}

void ListaMovimentos::lerDeFicheiro(string nomeFicheiro) {
    ifstream ficheiro(nomeFicheiro);

    if(!ficheiro.is_open()){
        cout << endl << "Ficheiro nao encontrado, lista iniciada vazia." << endl;
        return;
    }

    string linha;

    while(getline(ficheiro, linha)){
        if (linha == "") continue; 
        Movimentos::DadosdeMovimentos dados;
        string dataTemp, descTemp;

        dados._Codigo = stoi(linha); 

        getline(ficheiro, linha);
        dataTemp = linha;
        char tempDataSafe[11];
        strncpy(tempDataSafe, dataTemp.c_str(), 10);
        tempDataSafe[10] = '\0';
        dados._data = tempDataSafe;

        getline(ficheiro, linha);
        dados._valor = stod(linha); 

        getline(ficheiro, linha);
        dados._CodigoTipo = stoi(linha);

        getline(ficheiro, linha);
        descTemp = linha;
        char tempDescSafe[31];
        strncpy(tempDescSafe, descTemp.c_str(), 30);
        tempDescSafe[30] = '\0';
        dados._descricao = tempDescSafe;

        getline(ficheiro, linha);
        dados._origem = stoi(linha);

        getline(ficheiro, linha);
        dados._saldo = stod(linha);

        Movimentos m(dados);
        CNoListaMovimentos* novoNo = new CNoListaMovimentos(m);

        if(cabeca == nullptr){ cabeca = novoNo; } 
        else {
            CNoListaMovimentos* atual = cabeca;
            while(atual->proximo != nullptr){ atual = atual->proximo; }
            atual->proximo = novoNo;
        }
    }
    ficheiro.close();
}
