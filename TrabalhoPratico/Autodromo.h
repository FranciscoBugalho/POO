#ifndef AUTODROMO_H
#define AUTODROMO_H

#include "Utils.h"
#include "Pista.h"
#include "Garagem.h"

class Autodromo {
	string nome;					// Nome do aut�dromo (deve ser �nico)
	Pista pista;					// Pista do aut�dromo
	Garagem garagem;				// Garagem do aut�dromo
	static int conta;				// Vari�vel auxiliar para o nome do aut�dromo
	static vector<string> nomes;	// Vetor de nomes j� existentes
	bool corrida;					// Vari�vel de controlo de corridas (True - corrida a decorrer, false caso contr�rio)

public:
	// Construtor
	Autodromo(const string& nome, int maxcarros, int comprimento);

	// Construtor por c�pia
	Autodromo(const Autodromo& obj);

	// Destrutor
	~Autodromo();

	// Getter nome do Aut�dromo
	string getNome()const;
	// Setter do nome do Aut�dromo
	void setNome(string nome);

	// Getter da corrida
	bool isCorrida() const;
	// Setter da corrida
	void setCorrida();

	// Getter da pista do Aut�dromo
	Pista getPista()const;

	// Getter da garagem do Aut�dromo
	Garagem getGaragem()const;

	// Getter do vetor de pilotos sem carros
	vector<Piloto*>getPilotosSemCarros() const;

	// Getter do vetor de carros sem pilotos
	vector<Carro*> getCarrosSemPilotos() const;

	// Coloca os pilotos e os carros no aut�dromo
	void colocaPilotosECarros(vector<Piloto*> pilotos);

	// Coloca os carros sem piloto na garagem
	void colocaCarrosSemPilotos(vector<Carro*> carros);

	// Coloca os pilotos sem carro na garagem
	void colocaPilotosSemCarros(vector<Piloto*> pilotos);

	// Passa X tempo
	string passatempo(int tempo);

	// Inicia a corrida
	// Retorna True se a corrida foi iniciada, False se a corrida j� est� a decorrer
	bool iniciaCorrida();

	// Mostra a informa��o relativa aos carros no aut�dromo
	string listaCarros() const;

	// Carrega a bateria do carro indicado com a quantidade fornecida
	string carregaBateria(const char identificador, float energia);

	// Carrega todas as baterias
	string carregaBaterias();

	// Causa um acidente ao carro indicado
	int causaAcidente(const char identificador);

	// D� ordem de paragem ao piloto indicado
	string stop(const string nome);

	// Destr�i o carro indicado
	// Retorna -1 se a corrida n�o estiver iniciada, 0 se destruiu o carro, 1 se nada aconteceu
	int destroi(const char identificador);

	// Obt�m o piloto dado o carro que est� a conduzir
	string getPiloto(const char identificador);

	// Obt�m o vetor de pistas
	vector<vector<char>> getArrayPistas() const;

	// Obt�m a informa��o dos carros na garagem
	vector<string> getCarrosNaGaragem() const;

	// Retorna o nome do piloto do �ndice i
	string getNomePiloto(int i);

	// Obt�m o m�ximo de carros na pista
	int getMaxCarrosNaPista() const;

	// Obt�m o tempo da corrida
	int getTempo() const;

	// Obt�m os identificadores de carros na pista com o sinal de emerg�ncia ativo
	vector<char> getCarrosEmergencia() const;

	// Obt�m o tamanho do vetor de pilotos na pista // N�mero de pilotos/carros na pista
	int nCarrosPista() const;

	// Obt�m o identificador do carro dado o nome do piloto
	char getIdCarro(const string nome) const;

	// Atualiza vetores da pista e da garagem
	void atualizaVectors();

	// Verifica os nomes de todos os aut�dromos j� existentes
	void verificaNomes(const string nome);

	// Alterar o nome do autodromo
	void mudaNome(const string nome);

	// Redefini�ao do operador atribui��o
	Autodromo& operator=(const Autodromo& a);

	// GetAsString retorna uma string com a informa��o da classe.
	string getAsString()const;

};

// Redefini��o da fun��o operator<<
ostream& operator<<(ostream& o, const Autodromo& a);

// Redefini��o da fun��o operator+
// Objetivo: tornar o nome �nico
string operator+(const int i, const string nome);

#endif // !AUTODROMO