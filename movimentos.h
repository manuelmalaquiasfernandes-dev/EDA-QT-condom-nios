#ifndef MOVIMENTOS_H
#define MOVIMENTOS_H
#include <string>

using namespace std;

class Movimentos{
private:
    unsigned int Codigo; /// Substituiu o "id"
    char data[11]; 
    double valor; 
    unsigned int CodigoTipo; /// Substituiu o "idTipo"
    char descricao[31]; 
    unsigned int origem;
    double saldoApos; 

public:
    struct DadosdeMovimentos{
        unsigned int _Codigo;  /// Substituiu o "_id"
        const char*_data; 
        double _valor;
        unsigned int _CodigoTipo; /// Substituiu o "_idTipo"
        const char*_descricao;
        unsigned int _origem;
        double _saldo;
    };
    
    Movimentos(DadosdeMovimentos dados);
    
    unsigned int obterCodigoTipo()const;
    double obterValor()const;
    unsigned int obterCodigo()const;
    const char *obterData()const;
    const char *obterDescricao()const;
    unsigned int obterOrigem()const;
    double obterSaldoApos()const;
    void modificarTudo(const char*novaData, double novoValor, unsigned int novoCodigoTipo, const char*novaDescricao,unsigned int novaOrigem);
    void atualizaSaldo(double s);
};

class CNoListaMovimentos{
public:
    Movimentos movimento; 
    CNoListaMovimentos*proximo;

    CNoListaMovimentos(Movimentos m):movimento(m),proximo(nullptr) {}
};

class ListaMovimentos{
private:
    CNoListaMovimentos*cabeca; 

public:
    ListaMovimentos();
    ~ListaMovimentos();
    
    bool inserirMovimento(Movimentos m); 
    bool modificarMovimento(unsigned int codigo, const char*novaData, double novoValor, unsigned int novoCodigoTipo, const char*novaDescricao,unsigned int novaOrigem, double &diferenca);
    void mostraMovimentos()const; 
    void mostraMovimentosPorCondomino(unsigned int CodigoCondomino)const; 
    void mostraMovimentosPorTipo(unsigned int CodigoTipo)const; 
    void mostraReceitas()const;
    void mostraDespesas()const;
    void mostraGeral()const;
    
    void guardarEmFicheiro(string nomeFicheiro)const;
    void lerDeFicheiro(string nomeFicheiro);
};

#endif // MOVIMENTOS_H