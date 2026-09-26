#include <iostream>
#include <iomanip>
#include "condomino.h"
#include "fracao.h"
#include "GestorCondominio.h"
#include "listacondominos.h"
#include "listafracoes.h"
#include "Movimentos.h"
#include "GestorCondominio.h"

using namespace std;

void apresentacao(){
    cout << endl << endl << right << setw(30) << fixed << "Qt CONDOMINIOS" << endl;
    cout << right << setw(20) << "AUTORES : " << "MANUEL e LETICIA" << endl;
    cout << right << setw(28) << "DATA DE CONCLUSAO : " << "21/05/2026" << endl << endl;
}

int main(){
    apresentacao();

    ListaFracoes listaFracao;
    ListaCondominos listaCondominos;
    GestorCondominio gestor;

    listaFracao.lerDeFicheiro("fracoes.txt");
    listaCondominos.lerDeFicheiro("condominos.txt");
    gestor.carregarDados();

    int opcao;
    unsigned int codFracao, codCondomino;

    do {
        cout << endl << right << setw(17) << "MENU PRINCIPAL" << endl;
        cout << left << setw(20) << "1. Fracoes" << "(Ver, Inserir, Modificar)" << endl;
        cout << left << setw(20) << "2. Condominos" << "(Ver, Inserir, Eliminar, Modificar)" << endl;
        cout << left << setw(20) << "3. Tipo de despesa" << "(Ver, Inserir, Modificar)" << endl;
        cout << left << setw(20) << "4. Abertura do ano" << "(Inserir Orcamento Anual, Inserir Saldo Inical)" << endl;
        cout << left << setw(20) << "5. Receitas"<< "(Inserir, Modificar)" << endl;
        cout << left << setw(20) << "6. Despesas"<< "(Inserir, Modificar)" << endl;
        cout << left << setw(20) << "7. Resumo do ano"<< "(Despesas, Receitas, Geral)" << endl;
        cout << "8. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        
        if(opcao<1 || opcao>8){
            cout << endl << "Introduza um valor entre 1 e 8: " << endl;
            cin.clear();
            cin.ignore(1000,'\n');
            continue;
        }
        cin.ignore(1000, '\n');
        
        if(opcao>=4 && opcao<=7){
            if(!listaFracao.verificaPermilagem()) {
                cout << "Esta opcao so e possivel apos a permilagem total ser 1000." << endl << endl;
                continue; 
            }
        }

        switch (opcao){
            case 1: {
                int opcao2;
                cout << endl << endl << right << setw(30) << fixed << "Qt CONDOMINIOS" << endl << endl;
                cout << right << setw(10) << "Fracoes" << endl;
                cout << "1. Ver fracoes" << endl << "2. Inserir fracao" << endl << "3. Modificar proprietario" << endl << "4. Sair" << endl;
                cout << "Escolha uma opcao: ";
                cin >> opcao2;
                cout << endl; 
                
                if(opcao2!=1 && opcao2!=2 && opcao2!=3 && opcao2!=4){
                    cout << "Opcao invalida" << endl << endl;
                    break;
                }
                if(opcao2 == 1){
                    listaFracao.mostraFracoes();
                } 
                else if(opcao2 == 2){
                    listaFracao.inserirFracao();
                    listaFracao.guardarEmFicheiro("fracoes.txt");
                }
                else if(opcao2 == 3){
                    cout << "Codigo da Fracao: "; 
                    cin >> codFracao;
                    cout << "Codigo do Novo Dono: ";
                    cin >> codCondomino;
                    listaFracao.atribuirDonoAFracao(codFracao, codCondomino);
                    listaFracao.guardarEmFicheiro("fracoes.txt");
                }
                else if(opcao2==4){
                    break;
                }
                
                if(!listaFracao.verificaPermilagem()){
                    cout << "O total da permilagem nao e 1000" << endl;
                }
                else{
                    cout << "Permilagem total correta." << endl;
                }
                break;
            }

            case 2: {
                int opcao2;
                cout << endl << right << setw(31) << fixed << "Qt CONDOMINIOS" << endl << endl;
                cout << right << setw(13) << "Condominos" << endl;
                cout << "1. Ver" << endl << "2. Inserir" << endl << "3. Eliminar" << endl << "4. Modificar" << endl << "5. Sair" << endl;
                cout << "Escolha uma opcao: ";
                cin >> opcao2;
                cout << endl; 
                
                if(opcao2!=1 && opcao2!=2 && opcao2!=3 && opcao2!=4 && opcao2!=5){
                    cout << "Opcao invalida" << endl << endl;
                    break;
                }
                if(opcao2==1){
                    listaCondominos.mostraCondominos(listaFracao.returnCabeca());
                }
                else if(opcao2==2){
                    listaCondominos.inserirCondomino(listaFracao.returnCabeca());
                    listaCondominos.guardarEmFicheiro("condominos.txt");
                }else if(opcao2==3){
                    listaCondominos.eleminaCondominos();
                    listaCondominos.guardarEmFicheiro("condominos.txt");
                }
                else if(opcao2==4){
                    listaCondominos.modificaCondominos(listaFracao.returnCabeca());
                    listaCondominos.guardarEmFicheiro("condominos.txt");
                }
                else if(opcao2==5){
                    break;
                }
                break;
            }
            case 3:{
                int opcao2;
                cout << endl << right << setw(31) << fixed << "Qt CONDOMINIOS" << endl << endl;
                cout << right << setw(19) << "Tipo de Despesas" << endl;
                cout << "1. Ver" << endl << "2. Inserir" << endl << "3. Modificar" << endl << "4. Sair" << endl;
                cout << "Escolha uma opcao: ";
                cin >> opcao2;
                cout << endl; 
                
                if(opcao2!=1 && opcao2!=2 && opcao2!=3 && opcao2!=4){
                    cout << "Opcao invalida" << endl << endl;
                    break;
                }
                if(opcao2==1){
                    gestor.mostraTipos();
                }
                else if(opcao2==2){
                    gestor.inserirNovoTipo();
                    gestor.guardarDados();
                }else if(opcao2==3){
                    gestor.modificarTipo();
                    gestor.guardarDados();
                }
                else if(opcao2==4){
                    break;
                }
                break;
            }
            case 4:{
                int opcao2;
                cout << endl << right << setw(31) << fixed << "Qt CONDOMINIOS" << endl << endl;
                cout << right << setw(18) << "Abertura do Ano" << endl;
                cout << "1. Inserir Orcamento Anual" << endl << "2. Inserir saldo inical" << endl << "3. Sair" << endl;
                cout << "Escolha uma opcao: ";
                cin >> opcao2;
                cout << endl; 
                
                if(opcao2!=1 && opcao2!=2 && opcao2!=3){
                    cout << "Opcao invalida" << endl << endl;
                    break;
                }
                if(opcao2==1){
                    gestor.inserirOrcamento(listaCondominos, listaFracao);
                    gestor.guardarDados();
                    listaCondominos.guardarEmFicheiro("condominos.txt");
                }
                else if (opcao2==2){
                    gestor.inserirSaldoInicial();
                    gestor.guardarDados();
                }
                else if(opcao2==3){
                    break;
                }
                break;
            }
            case 5:{
                if(!gestor.isAnoAberto()){
                    cout << "O ano ainda nao esta aberto. Por favor insira o saldo incial e o orcamento primeiro" << endl;
                    break;
                }
                
                int opcao2;
                cout << endl << right << setw(31) << fixed << "Qt CONDOMINIOS" << endl << endl;
                cout << right << setw(11) << "Receitas" << endl; 
                cout << "1. Inserir" << endl << "2. Modificar" << endl << "3. Sair" << endl;
                cout << "Escolha uma opcao: ";
                cin >> opcao2;
                cout << endl; 
                
                if(opcao2!=1 && opcao2!=2 && opcao2!=3){
                    cout << "Opcao invalida" << endl << endl;
                    break;
                }
                if(opcao2==1){
                    gestor.inserirReceita(listaCondominos);
                    gestor.guardarDados();
                }
                else if(opcao2==2){
                    gestor.modificarReceita(); 
                    gestor.guardarDados();
                }
                else if(opcao2==3){
                    break;
                }
                break;
            }
            case 6:{
                if(!gestor.isAnoAberto()){
                    cout << "O ano ainda nao esta aberto. Por favor insira o orcamento e o saldo inicial primeiro." << endl;
                    break;
                }
                
                int opcao2;
                cout << endl << right << setw(31) << fixed << "Qt CONDOMINIOS" << endl << endl;
                cout << right << setw(11) << "Despesas" << endl;
                cout << "1. Inserir" << endl << "2. Modificar" << endl << "3. Sair" << endl;
                cout << "Escolha uma opcao: ";
                cin >> opcao2;
                cout << endl; 
                
                if(opcao2!=1 && opcao2!=2 && opcao2!=3){
                    cout << "Opcao invalida" << endl << endl;
                    break;
                }
                if(opcao2==1){
                    gestor.inserirDespesa(listaCondominos);
                    gestor.guardarDados();
                }
                else if (opcao2==2){
                    gestor.modificarDespesa(); 
                    gestor.guardarDados();
                }
                else if(opcao2==3){
                    break;
                }
                break;
            }
            case 7:{
                int opcao2;
                cout << endl << right << setw(31) << fixed << "Qt CONDOMINIOS" << endl << endl;
                cout << right << setw(16) << "Resumo do ano" << endl; 
                cout << "1. Listagem Despesas" << endl 
                     << "2. Listagem Receitas" << endl 
                     << "3. Geral (Todos e Saldo)" << endl 
                     << "4. Listagem por Tipo" << endl 
                     << "5. Listagem por Condomino" << endl
                     << "6. Sair" << endl;
                cout << "Escolha uma opcao: ";
                cin >> opcao2;
                cout << endl; 
                
                if(opcao2<1 || opcao2>6){
                    cout <<"Opcao invalida"<<endl<< endl;
                    break;
                }
                if(opcao2==1){
                    gestor.mostraDespesas();
                }
                else if (opcao2==2){
                    gestor.mostraReceitas();
                }
                else if(opcao2==3){
                    gestor.mostraTodosMovimentos();
                    gestor.mostraResumoFinanceiro();
                }
                else if(opcao2==4){
                    unsigned int tipoPesquisa;
                    cout <<"Insira o codigo do tipo de movimento:";
                    cin >>tipoPesquisa;
                    gestor.mostraMovimentosPorTipo(tipoPesquisa);
                }
                else if(opcao2==5){
                    gestor.mostraResumoTodosCondominos(listaCondominos, listaFracao);
                }
                else if(opcao2==6){
                    break;
                }
                break;
            }
            case 8: {
                char confirmar;
                cout << endl << "Tem a certeza que deseja sair? (S/N): ";
                cin >> confirmar;
                cout << endl; 

                if(confirmar == 'S' || confirmar == 's'){
                    listaFracao.guardarEmFicheiro("fracoes.txt");
                    listaCondominos.guardarEmFicheiro("condominos.txt");
                    
                    gestor.guardarDados(); 
                    
                    cout << "Dados guardados" << endl << endl;
                }
                else{
                    opcao = 0;
                    cout << "Operacao cancelada" << endl << endl;
                }
                break;
            }
        }
    } while (opcao!=8);
    return 0;
}
