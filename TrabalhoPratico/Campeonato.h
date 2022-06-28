#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "Utils.h"
#include "Autodromo.h"

#define FIM_CORRIDA "Fim da corrida!"											// Final de uma corrida
#define FIM_CORRIDA_sPilotos "Nao ha mais pilotos na pista! Fim da corrida!"	// Final de uma corrida pois não há pilotos na pista

class Campeonato {
	vector<Autodromo*> autodromos;				// Vetores dos autódromos no campeonato
	vector<Piloto*> pilotos;					// Vetores de pilotos (com carros)
	vector<Piloto*> pilotosSemCarros;			// Pilotos sem carros
	vector<Carro*> carrosSemPilotos;			// Carros sem pilotos
	int nCorrida;								// Número da corrida
	bool primeira;								// True -> Primeira corrida do campeonato || False -> caso contrário 
	bool fim;									// Controla o fim do campeonato (True -> fim || False -> caso contrário)

public:
	// Construtor	
	Campeonato(vector<Autodromo*> autodromos, vector<Piloto*> pilotos);

	// Destrutor
	~Campeonato();

	// Getter do número da corrida
	int getNCorrida() const;
	// Setter do número da corrida
	void setNCorrida();

	// Getter do vetor de autódromos
	vector<Autodromo*> getAutodromos() const;

	// Obtém o nome do autódromo onde está a decorrer a corrida
	string getAutodromoAtual() const;

	// Obtém o tempo do autódromo
	int getTempo() const;

	// Obtém o número máximo de carros
	int getMaxCarros() const;

	// Obtém num vetor de carateres os identificadores de carros com o sinal de emergência ativo
	vector<char> getCarrosEmergencia() const;

	// Atualiza o vetor de pilotos sem carros
	void setPilotosSemCarro();

	// Atualiza o vetor de carros sem pilotos
	void setCarrosSemPiloto();

	// Obtém as posicões dos pilotos/carros na corrida
	string getPosicoes();

	// Função para colocar os pilotos/carros na pista
	void colocaPilotosECarros();

	// Obtém o vetor das pistas
	vector<vector<char>> getArrayPistas();

	// Obtém o vetor com informação dos pilotos/carros na garagem
	vector<string> getCarrosGaragem();

	// Verifica se o tempo para passar é válido
	// Retorna True - válido || False - inválido
	bool tempoValido(int tempo);

	// Passa o tempo
	string passatempo(int tempo);

	// Verifica se a corrida já foi iniciada
	bool corridaIniciada();

	// Inicia a próxima corrida
	string iniciaCorrida();

	// Mostra informação relativa aos carros no campeonato
	string listaCarros();

	// Carrega a bateria do carro indicado
	string carregaBateria(const char identificador, float energia);

	// Carrega todas as baterias
	string carregaBaterias();

	// Carrega todas as baterias
	void carregaTudo();

	// Coloca as pontuações a 0
	void inicializaPontuacoes();

	// O piloto pode pontuar na próxima corrida
	void podePontuar();

	// Causa acidente ao carro indicado
	// Retorna -2 se estiver no segundo 0, -1 se a corrida não estiver iniciada, 0 se causou acidente, 1 se nada aconteceu
	int causaAcidente(const char identificador);

	// Obtém o nome do piloto dado o carro que está a conduzir
	string getPiloto(const char identificador);

	// Dá ordem de paragem ao piloto indicado
	string stop(const string nome);

	// Destrói o carro indicado
	// Retorna -2 se estiver no segundo 0, -1 se a corrida não estiver iniciada, 0 se destruiu o carro, 1 se nada aconteceu
	int destroi(const char identificador);

	// Obtém a classificação dos pilotos no final do campeonato
	string getPontuacoes();

};

#endif // !CAMPEONATO