#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "Utils.h"
#include "Autodromo.h"

#define FIM_CORRIDA "Fim da corrida!"											// Final de uma corrida
#define FIM_CORRIDA_sPilotos "Nao ha mais pilotos na pista! Fim da corrida!"	// Final de uma corrida pois n�o h� pilotos na pista

class Campeonato {
	vector<Autodromo*> autodromos;				// Vetores dos aut�dromos no campeonato
	vector<Piloto*> pilotos;					// Vetores de pilotos (com carros)
	vector<Piloto*> pilotosSemCarros;			// Pilotos sem carros
	vector<Carro*> carrosSemPilotos;			// Carros sem pilotos
	int nCorrida;								// N�mero da corrida
	bool primeira;								// True -> Primeira corrida do campeonato || False -> caso contr�rio 
	bool fim;									// Controla o fim do campeonato (True -> fim || False -> caso contr�rio)

public:
	// Construtor	
	Campeonato(vector<Autodromo*> autodromos, vector<Piloto*> pilotos);

	// Destrutor
	~Campeonato();

	// Getter do n�mero da corrida
	int getNCorrida() const;
	// Setter do n�mero da corrida
	void setNCorrida();

	// Getter do vetor de aut�dromos
	vector<Autodromo*> getAutodromos() const;

	// Obt�m o nome do aut�dromo onde est� a decorrer a corrida
	string getAutodromoAtual() const;

	// Obt�m o tempo do aut�dromo
	int getTempo() const;

	// Obt�m o n�mero m�ximo de carros
	int getMaxCarros() const;

	// Obt�m num vetor de carateres os identificadores de carros com o sinal de emerg�ncia ativo
	vector<char> getCarrosEmergencia() const;

	// Atualiza o vetor de pilotos sem carros
	void setPilotosSemCarro();

	// Atualiza o vetor de carros sem pilotos
	void setCarrosSemPiloto();

	// Obt�m as posic�es dos pilotos/carros na corrida
	string getPosicoes();

	// Fun��o para colocar os pilotos/carros na pista
	void colocaPilotosECarros();

	// Obt�m o vetor das pistas
	vector<vector<char>> getArrayPistas();

	// Obt�m o vetor com informa��o dos pilotos/carros na garagem
	vector<string> getCarrosGaragem();

	// Verifica se o tempo para passar � v�lido
	// Retorna True - v�lido || False - inv�lido
	bool tempoValido(int tempo);

	// Passa o tempo
	string passatempo(int tempo);

	// Verifica se a corrida j� foi iniciada
	bool corridaIniciada();

	// Inicia a pr�xima corrida
	string iniciaCorrida();

	// Mostra informa��o relativa aos carros no campeonato
	string listaCarros();

	// Carrega a bateria do carro indicado
	string carregaBateria(const char identificador, float energia);

	// Carrega todas as baterias
	string carregaBaterias();

	// Carrega todas as baterias
	void carregaTudo();

	// Coloca as pontua��es a 0
	void inicializaPontuacoes();

	// O piloto pode pontuar na pr�xima corrida
	void podePontuar();

	// Causa acidente ao carro indicado
	// Retorna -2 se estiver no segundo 0, -1 se a corrida n�o estiver iniciada, 0 se causou acidente, 1 se nada aconteceu
	int causaAcidente(const char identificador);

	// Obt�m o nome do piloto dado o carro que est� a conduzir
	string getPiloto(const char identificador);

	// D� ordem de paragem ao piloto indicado
	string stop(const string nome);

	// Destr�i o carro indicado
	// Retorna -2 se estiver no segundo 0, -1 se a corrida n�o estiver iniciada, 0 se destruiu o carro, 1 se nada aconteceu
	int destroi(const char identificador);

	// Obt�m a classifica��o dos pilotos no final do campeonato
	string getPontuacoes();

};

#endif // !CAMPEONATO