#ifndef GARAGEM_H
#define GARAGEM_H

#include "Utils.h"
#include "Piloto.h"

class Garagem {
	vector<Piloto*> pilotos;			// Pilotos na garagem
	vector<Carro*> carros;				// Vetor de carros sem pilotos
	vector<Piloto*> pilotosSemCarros;	// Vetor de pilotos sem carros

public:
	// Construtor
	Garagem();

	// Destrutor
	~Garagem();

	// Getter dos pilotos
	vector<Piloto*> getPilotos() const;

	// Getter dos pilotos sem carros
	vector<Piloto*> getPilotosSemCarro() const;

	// Getter dos carros sem pilotos
	vector<Carro*> getCarrosSemPilotos() const;
	   
	// Coloca os pilotos e os carros na garagem
	void setPilotos(int nCarros, vector<Piloto*> pilotos);

	// Coloca os carros sem piloto
	void setCarrosSemPilotos(vector<Carro*> carros);

	// Coloca os pilotos sem carro
	void setPilotosSemCarros(vector<Piloto*> piloto);

	// Obtém a informação dos carros na garagem
	string listaCarros() const;

	// Carrega a bateria com a quantidade indicada do carro indicado
	// Retorna True se o carro existe na pista e a bateria foi carregada, False caso contrário
	bool carregaBateria(char identificador, float energia);

	// Carrega as baterias dos carros na garagem
	string carregaBaterias();

	// Retorna um vetor de strings com informação dos carros para o ecrã
	vector<string> getInfoCarros() const;

	// Função auxiliar ao getAsString
	// Retorna uma string com os dados dos pilotos
	string getPilotosStr() const;

	// GetAsString retorna uma string com a informação da classe.
	string getAsString()const;
};

#endif // !GARAGEM
