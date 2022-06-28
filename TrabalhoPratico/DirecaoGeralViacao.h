#ifndef DIRECAOGERALVIACAO_H
#define DIRECAOGERALVIACAO_H

#include "Utils.h"
#include "CrazyDriver.h"
#include "PilotoRapido.h"
#include "PilotoSurpresa.h"

#include "Assassino.h"

// DVG - Direção Geral de Viação
class DirecaoGeralViacao {
	string nome;						// Nome = Direção Geral de Viação
	vector<Piloto *> pilotos;			// Vetor de pilotos
	vector<Carro *> carros;				// Vetor de carros

public:
	// Construtor sem parâmetros
	DirecaoGeralViacao();

	// Construtor por cópia
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

	// Função de pesquisa no vetor de pilotos
	// Retorna a posição do elemento no vetor caso exista. Senão retorna -1
	int pesquisaPilotos(const string nome);

	// Função de pesquisa no vetor de carros
	// Retorna a posição do elemento no vetor caso exista. Senão retorna -1
	int pesquisaCarros(const char identificador);

	// Função para adicionar um piloto
	string adicionaPiloto(const string tipo, const string nome);

	// Função para remover um piloto
	bool removePiloto(const string nome);

	// Função para adicionar um carro (dado modelo)
	char adicionaCarro(const string marca, const string modelo, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima);

	// Função para adicionar um carro (sem modelo)
	char adicionaCarroSM(const string marca, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima);

	// Função para remover um carro
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
	// Retorna TRUE - se existirem 2 ou mais; FALSE - caso contrário
	bool isPilotosEmCarros();

	// Obtém um vetor de pilotos em carros
	vector<Piloto*> getPilotosEmCarros();

	// Redefinição do operador atribuição
	DirecaoGeralViacao& operator=(const DirecaoGeralViacao& dgv);

	// Função extra auxiliar a imprimir informações dos pilotos no ecrã
	// Retorna o vetor separado [Posicao 0 - "Nome: axpto"; Posicao 1 - "A conduzir: {Nada ou Id do Carro}"; Posicao 3 - "BREAK" separa a informação dos vários pilotos]
	vector<string> getPilotosListaSTR() const;

	// Função extra auxiliar a imprimir informações dos carros no ecrã
	// Retorna o vetor separado [Posicao 0 - "Marca: abc"; Posicao 1 - "Idenficador: a"; Posicao 3 - "Com/Sem Piloto"; Posicao 4 - "BREAK" separa a informação dos vários carros]
	vector<string> getCarrosListaSTR() const;

	// Função auxiliar ao getAsString
	// Retorna uma string com os dados dos pilotos
	string getPilotosStr()const;

	// Função auxiliar ao getAsString
	// Retorna uma string com os dados dos carros
	string getCarrosStr()const;

	/*
	*	Funções SAVE, LOAD, DELETE
	*/

	// GetAsString retorna uma string com a informação da classe.
	string getAsString()const;
};

// Redefinição da função operator<<
ostream& operator<<(ostream& o, const DirecaoGeralViacao& dgv);

#endif // !DIRECAOGERALVIACAO