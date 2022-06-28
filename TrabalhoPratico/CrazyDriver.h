#ifndef CRAZYDRIVER_H
#define CRAZYDRIVER_H

#include "Piloto.h"

#define PROB_ACIDENTE 5			// Constante da probabilidade de acidente

class CrazyDriver : public Piloto {
	int posicaoAnterior;		// Posi��o no segundo anterior
	int iniciaCorrida;			// Segundo em que vai iniciar a corrida (1 a 5)			

public:
	// Construtor
	CrazyDriver(const string& nome, const string& tipo);

	// Movimenta o carro
	// Retorna 1 se o carro se est� a mover, 0 se o carro est� parado, retorna -1 se estragou o carro, -2 se ativar o sinal de emerg�ncia
	int movimenta(int tempo, int posicao, int nCarrosPista) override;

	// Causa um acidente e um dano irrepar�vel ao carro
	// Retorna -1 se causar danos ao piloto anterior, 0 se s� causar dano a ele mesmo
	int acidente() override;

	// GetAsString retorna uma string com a informa��o da classe.
	string getAsString()const override;

	// Retorna um piloto do tipo CrazyDriver
	Piloto* duplica()const override;
};

#endif // !CRAZYDRIVER