#ifndef DIRECAOGERALVIACAO_H
#define DIRECAOGERALVIACAO_H

#include "Utils.h"
#include "CrazyDriver.h"
#include "PilotoRapido.h"
#include "PilotoSurpresa.h"

#include "Assassino.h"

// DVG - Dire��o Geral de Via��o
class DirecaoGeralViacao {
	string nome;						// Nome = Dire��o Geral de Via��o
	vector<Piloto *> pilotos;			// Vetor de pilotos
	vector<Carro *> carros;				// Vetor de carros

public:
	// Construtor sem par�metros
	DirecaoGeralViacao();

	// Construtor por c�pia
	DirecaoGeralViacao(const DirecaoGeralViacao& obj);

	// Destrutor
	~DirecaoGeralViacao();

	// Getter do nome
	string getNome()const;
	// Setter do nome
	void setNome(const string nome);
	// Getter do vetor de pilotos
	vector<Piloto*> getPilotos()const;
	// Getter do vetor de carros
	vector<Carro*> getCarros()const;

	// Fun��o de pesquisa no vetor de pilotos
	// Retorna a posi��o do elemento no vetor caso exista. Sen�o retorna -1
	int pesquisaPilotos(const string nome);

	// Fun��o de pesquisa no vetor de carros
	// Retorna a posi��o do elemento no vetor caso exista. Sen�o retorna -1
	int pesquisaCarros(const char identificador);

	// Fun��o para adicionar um piloto
	string adicionaPiloto(const string tipo, const string nome);

	// Fun��o para remover um piloto
	bool removePiloto(const string nome);

	// Fun��o para adicionar um carro (dado modelo)
	char adicionaCarro(const string marca, const string modelo, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima);

	// Fun��o para adicionar um carro (sem modelo)
	char adicionaCarroSM(const string marca, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima);

	// Fun��o para remover um carro
	bool removeCarro(const char identificador);

	// Colocar um piloto no carro
	string entraNoCarro(const char& identificador, const string& nome);

	// Remove o piloto do carro indicado
	string saiDoCarro(const char& identificador);

	// Indica o tamanho do vetor de pilotos
	int getPilotosSize() const;

	// Indica o tamanho do vetor de carros
	int getCarrosSize() const;

	// Verifica se existem pelo menos 2 pilotos nos carros
	// Retorna TRUE - se existirem 2 ou mais; FALSE - caso contr�rio
	bool isPilotosEmCarros();

	// Obt�m um vetor de pilotos em carros
	vector<Piloto*> getPilotosEmCarros();

	// Redefini��o do operador atribui��o
	DirecaoGeralViacao& operator=(const DirecaoGeralViacao& dgv);

	// Fun��o extra auxiliar a imprimir informa��es dos pilotos no ecr�
	// Retorna o vetor separado [Posicao 0 - "Nome: axpto"; Posicao 1 - "A conduzir: {Nada ou Id do Carro}"; Posicao 3 - "BREAK" separa a informa��o dos v�rios pilotos]
	vector<string> getPilotosListaSTR() const;

	// Fun��o extra auxiliar a imprimir informa��es dos carros no ecr�
	// Retorna o vetor separado [Posicao 0 - "Marca: abc"; Posicao 1 - "Idenficador: a"; Posicao 3 - "Com/Sem Piloto"; Posicao 4 - "BREAK" separa a informa��o dos v�rios carros]
	vector<string> getCarrosListaSTR() const;

	// Fun��o auxiliar ao getAsString
	// Retorna uma string com os dados dos pilotos
	string getPilotosStr()const;

	// Fun��o auxiliar ao getAsString
	// Retorna uma string com os dados dos carros
	string getCarrosStr()const;

	/*
	*	Fun��es SAVE, LOAD, DELETE
	*/

	// GetAsString retorna uma string com a informa��o da classe.
	string getAsString()const;
};

// Redefini��o da fun��o operator<<
ostream& operator<<(ostream& o, const DirecaoGeralViacao& dgv);

#endif // !DIRECAOGERALVIACAO