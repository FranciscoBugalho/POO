#ifndef ASSASSINO_H
#define ASSASSINO_H

#include "Piloto.h"

#define PROB_DESTRUIR 50

class Assassino : public Piloto {

public:
	// Construtor
	Assassino(const string& nome, const string& tipo);

	// Movimenta o carro
	// Retorna 1 se o carro se est� a mover, 0 se o carro est� parado, -3 se assassinar algu�m
	int movimenta(int tempo, int posicao, int nCarrosPista) override;

	// Causa um acidente e um dano irrepar�vel ao carro
	// Retorna -1 se causar danos ao piloto anterior, 0 se s� causar dano a ele mesmo
	int acidente() override;

	// GetAsString retorna uma string com a informa��o da classe.
	string getAsString()const override;

	// Retorna um piloto do tipo PilotoRapido
	Piloto* duplica()const override;
};

#endif // !PILOTORAPIDO