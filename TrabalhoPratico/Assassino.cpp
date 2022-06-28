#include "Assassino.h"

Assassino::Assassino(const string& nome, const string& tipo) : Piloto(nome, tipo) { }

int Assassino::movimenta(int tempo, int posicao, int nCarrosPista) {
	if (tempo <= 0)
		return 0;

	if (rand() % 100 + 1 <= PROB_DESTRUIR) {
		if (acelera(1) == -1) {
			ativaEmergencia(true);
			travaAteParar();
			return 0;
		}

		return -3;
	}

	if (acelera(1) == -1) {
		ativaEmergencia(true);
		travaAteParar();
		return 0;
	}
	return 1;
}

int Assassino::acidente() {
	danificaCarro(2); 
	return 0; 
}

string Assassino::getAsString() const {
	ostringstream oss;
	oss << " Tipo: Piloto Assassino\n" << Piloto::getAsString();
	return oss.str();
}

Piloto* Assassino::duplica() const {
	return new Assassino(*this);
}
