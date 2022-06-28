#ifndef PILOTORAPIDO_H
#define PILOTORAPIDO_H

#include "Piloto.h"

#define PROB_ATAQUEPANICO 10	// Probabilidade de ataque de pânico

class PilotoRapido : public Piloto {
	int conta3Segundos;			// Verifica se passaram 3 segundos (para poder acelerar)
	int conta10Segundos;		// Verifica se passaram 10 segundos (pode ter um ataque de ansiedade)

public:
	// Construtor
	PilotoRapido(const string& nome, const string& tipo);

	// Movimenta o carro
	// Retorna 1 se o carro se está a mover, 0 se o carro está parado, -2 se ativar o sinal de emergência
	int movimenta(int tempo, int posicao, int nCarrosPista) override;

	// Causa um acidente e um dano irreparável ao carro
	// Retorna -1 se causar danos ao piloto anterior, 0 se só causar dano a ele mesmo
	int acidente() override;

	// GetAsString retorna uma string com a informação da classe.
	string getAsString()const override;

	// Retorna um piloto do tipo PilotoRapido
	Piloto* duplica()const override;
};

#endif // !PILOTORAPIDO