#ifndef PISTA_H
#define PISTA_H

#include "Utils.h"
#include "Piloto.h"

#define NOME_FICH_PISTA	 "pista.txt"	// Nome do ficheiro dos carateres da pista
#define TAM_LINHA_FICH	50				// Tamanho de uma linha do ficheiro

#define COMPRIMENTO_MAXIMO 500			// Comprimento m�ximo da pista
#define COMPRIMENTO_DEFAULT 100			// Comprimento default da pista (caso o valor seja inv�lido)
#define MAXCARROS_DEFAULT 5				// N�mero de carros default na pista (caso o valor seja inv�lido)
#define MAX_MAXCARROS 8					// M�ximo de carros permitido em cada pista

#define PONTOS_PRIMEIRO 10				// Pontos para o primeiro classificado
#define PONTOS_SEGUNDO 5				// Pontos para o segundo classificado
#define PONTOS_TERCEIRO 2				// Pontos para o terceiro classificado
#define PONTOS_OUTROS 0					// Pontos para os restantes pilotos

class Pista {
	vector<Piloto*> pilotos;			// Pilotos e carros na pista 
	vector<Carro*> carros;				// Vetor de carros sem pilotos
	vector<Piloto*> pilotosSemCarros;	// Vetor de pilotos sem carros
	const int comprimento;				// Comprimento da pista
	const int maximoCarros;				// M�ximo de carros permitidos na pista
	int tempo;							// Tempo da corrida
	vector<vector<char>> pistas;		// Pistas

public:
	// Construtor
	Pista(int comprimento, int maximoCarros);

	// Destrutor
	~Pista();

	// Getter do vetor de pilotos
	vector<Piloto*> getPilotos()const;
	// Getter do vetor de carros sem pilotos
	vector<Carro*> getCarros()const;
	// Getter do vetor de pilotos sem carro
	vector<Piloto*> getPilotosSemCarro() const;
	// Getter do comprimento
	int getComprimento()const;
	// Getter do n�mero m�ximo de carros
	int getMaxCarros()const;
	// Getter do tempo
	int getTempo()const;
	// Setter do tempo
	void setTempo();

	// Obt�m o tamanho do vetor de pilotos // N�mero de pilotos/carros na pista
	int nCarrosPista() const;

	// Coloca o vetor de pilotos na pista
	// Retorna o n�mero de pilotos na pista
	int setPilotos(const vector<Piloto*> piloto);

	// Passa o tempo e atualiza a pista
	string passatempo(int tempo);

	// Acidente com um CrazyDriver, danifica o carro antes dele
	// Retorna a posi��o do piloto que sofreu tamb�m com o acidente || -1 se n�o afetar nenhum outro piloto
	int acidente(int posicao);

	// Carrega a bateria com a quantidade indicada do carro indicado
	// Retorna True se o carro existe na pista e a bateria foi carregada, False caso contr�rio
	bool carregaBateria(char identificador, float energia);

	// Carrega as baterias dos carros da pista
	string carregaBaterias();

	// Causa um acidente ao carro indicado
	bool causaAcidente(const char identificador);

	// D� ordem de paragem ao piloto indicado, trava at� parar
	string stop(const string nome);

	// Destr�i o carro indicado
	// Retorna -1 se a corrida n�o estiver iniciada, 0 se destruiu o carro, 1 se nada aconteceu
	int destroi(const char identificador);

	// Obt�m o nome do piloto que conduz o carro indicado
	string getPiloto(const char identificador);

	// Getter do vetor de carateres - pistas
	vector<vector<char>> getArrayPistas() const;

	// Inicializa o vetor de pistas
	void initPista();

	// Atualiza o id do carro na pista
	void updatePistas(const char id, int x, int y);

	// Atualiza o local da pista onde houve o acidente
	void atualizaPistaAcidente(int x, int y);

	// L� o ficheiro "pista.txt" para o vetor pista
	vector<char> lePista(const string& nomeFich);

	// Limpa o vetor da pista para reescrever
	void limpaPista();

	// Retorna o nome do piloto no �ndice indicado
	string getNomePiloto(int i);

	// Retorna a posi��o do piloto na corrida (posi��o no vetor + 1) com o nome �ndicado ( -1 se n�o existe)
	int getPosicaoPiloto(const string nome);

	// Organiza vetor de posi��es
	void organizaPosicoes();

	// Obt�m os identificadores dos carros com o sinal de emerg�ncia ativo
	vector<char> getCarrosEmergencia() const;

	// Obt�m o identificador do carro dado o nome do piloto
	char getIdCarro(const string nome) const;

	// Limpa os vetores de carro sem pilotos e pilotos sem carros
	void limpaVetores();

	// Lista os carros na pista
	string listaCarros() const;

	// Fun��o auxiliar ao getAsString
	// Retorna uma string com os dados dos pilotos
	string getPilotosStr() const;

	// GetAsString retorna uma string com a informa��o da classe.
	string getAsString()const;
};


#endif // !PISTA