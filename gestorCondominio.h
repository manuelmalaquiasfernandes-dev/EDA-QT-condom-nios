#ifndef GESTORCONDOMINIO_H
#define GESTORCONDOMINIO_H
#include "Movimentos.h"
#include "TipoMovimento.h"
#include "listacondominos.h"

class GestorCondominio{
private:
    ListaMovimentos listaMovimentosGeral;
    ListaTipoMovimento listaTiposGeral;

    double saldoOrcamento;
    double saldoAtualCondominio;
    bool anoAberto;


public:
    GestorCondominio();
    
    void carregarDados(); 
    void guardarDados()const;

    void inserirNovoTipo(); 
    void mostraTipos()const; 

    void inserirReceita(ListaCondominos& listaCondominos); 
    void inserirDespesa(ListaCondominos& listaCondominos); 
    void mostraTodosMovimentos()const; 

    void mostraMovimentosPorCondomino(unsigned int CodigoCondomino)const;
    void mostraMovimentosPorTipo(unsigned int CodigoTipo)const;
    void mostraReceitas()const; 
    void mostraDespesas()const; 
    
    void modificarTipo();
    void modificarReceita();
    void modificarDespesa();
    
    void inserirOrcamento(ListaCondominos& listaCondominos,ListaFracoes& listaFracoes);
    void inserirSaldoInicial();
    
    void mostraResumoFinanceiro()const; 

    bool isAnoAberto()const;
    void mostraResumoTodosCondominos(ListaCondominos& listaCondominos, ListaFracoes& listaFracoes) const;
};

#endif // GESTORCONDOMINIO_H