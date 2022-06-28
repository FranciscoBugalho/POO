#ifndef AUTODROMO_H
#define AUTODROMO_H

#include "Utils.h"
#include "Pista.h"
#include "Garagem.h"

class Autodromo {
	string nome;					// Nome do autódromo (deve ser único)
	Pista pista;					// Pista do autódromo
	Garagem garagem;				// Garagem do autódromo
	static int conta;				// Variável auxiliar para o nome do autódromo
	static vector<string> nomes;	// Vetor de nomes já existentes
	bool corrida;					// Variável de controlo de corridas (True - corrida a decorrer, false caso contrário)

public:
	// Construtor
	Autodromo(const string& nome, int maxcarros, int comprimento);

	// Construtor por cópia
	Autodromo(const Autodromo& obj);

	// Destrutor
	~Autodromo();

	// Getter nome do Autódromo
	string getNome()const;
	// Setter do nome do Autódromo
	void setNome(string nome);

	// Getter da corrida
	bool isCorrida() const;
	// Setter da corrida
	void setCorrida();

	// Getter da pista do Autódromo
	Pista getPista()const;

	// Getter da garagem do Autódromo
	Garagem getGaragem()const;

	// Getter do vetor de pilotos sem carros
	vector<Piloto*>getPilotosSemCarros() const;

	// Getter do vetor de carros sem pilotos
	vector<Carro*> getCarrosSemPilotos() const;

	// Coloca os pilotos e os carros no autódromo
	void colocaPilotosECarros(vector<Piloto*> pilotos);

	// Coloca os carros sem piloto na garagem
	void colocaCarrosSemPilotos(vector<Carro*> carros);

	// Coloca os pilotos sem carro na garagem
	void colocaPilotosSemCarros(vector<Piloto*> pilotos);

	// Passa X tempo
	string passatempo(int tempo);

	// Inicia a corrida
	// Retorna True se a corrida foi iniciada, False se a corrida já está a decorrer
	bool iniciaCorrida();

	// Mostra a informação relativa aos carros no autódromo
	string listaCarros() const;

	// Carrega a bateria do carro indicado com a quantidade fornecida
	string carregaBateria(const char identificador, float energia);

	// Carrega todas as baterias
	string carregaBaterias();

	// Causa um acidente ao carro indicado
	int causaAcidente(const char identificador);

	// Dá ordem de paragem ao piloto indicado
	string stop(const string nome);

	// Destrói o carro indicado
	// Retorna -1 se a corrida não estiver iniciada, 0 se destruiu o carro, 1 se nada aconteceu
	int destroi(const char identificador);

	// Obtém o piloto dado o carro que está a conduzir
	string getPiloto(const char identificador);

	// Obtém o vetor de pistas
	vector<vector<char>> getArrayPistas() const;

	// Obtém a informação dos carros na garagem
	vector<string> getCarrosNaGaragem() const;

	// Retorna o nome do piloto do índice i
	string getNomePiloto(int i);

	// Obtém o máximo de carros na pista
	int getMaxCarrosNaPista() const;

	// Obtém o tempo da corrida
	int getTempo() const;

	// Obtém os identificadores de carros na pista com o sinal de emergência ativo
	vector<char> getCarrosEmergencia() const;

	// Obtém o tamanho do vetor de pilotos na pista // Número de pilotos/carros na pista
	int nCarrosPista() const;

	// Obtém o identificador do carro dado o nome do piloto
	char getIdCarro(const string nome) const;

	// Atualiza vetores da pista e da garagem
	void atualizaVectors();

	// Verifica os nomes de todos os autódromos já existentes
	void verificaNomes(const string nome);

	// Alterar o nome do autodromo
	void mudaNome(const string nome);

	// Redefiniçao do operador atribuição
	Autodromo& operator=(const Autodromo& a);

	// GetAsString retorna uma string com a informação da classe.
	string getAsString()const;

};

// Redefinição da função operator<<
ostream& operator<<(ostream& o, const Autodromo& a);

// Redefinição da função operator+
// Objetivo: tornar o nome único
string operator+(const int i, const string nome);

#endif // !AUTODROMO