#include "PilotoSurpresa.h"

PilotoSurpresa::PilotoSurpresa(const string& nome, const string& tipo) : Piloto(nome, tipo) { }

int PilotoSurpresa::movimenta(int tempo, int posicao, int nCarrosPista) {
	
	if (tempo <= 0)
		return 0;

	// Se o tempo for par
	if ((tempo % 2) == 0) {
		// Acelera se tiver energia
		if (acelera(1) == -1) {
			travaAteParar();
			return -2;
		}
	}
	// Se o tempo for impar
	else {
		// 3% de probabilidade de ativar o sinal de emergência
		if (rand() % 100 + 1 <= PROB_EMERGENCIA) {
			ativaEmergencia(true);
			return -2;
		}

		// Tem uma probabilidade de 25% de travar
		if (rand() % 100 + 1 <= PROB_TRAVAR) {
			// Trava se tiver energia
			if (trava(1) == -1) {
				travaAteParar();
				return -2;
			}
		}
		// Mantém a velocidade
		else {
			if (acelera(0) == -1) {
				travaAteParar();
				return -2;
			}
		}
	}
	return 1;
}

Piloto* PilotoSurpresa::duplica() const {
	return new PilotoSurpresa(*this);
}

int PilotoSurpresa::acidente() {
	danificaCarro(2);
	return 0;
}

string PilotoSurpresa::getAsString() const {
	ostringstream oss;
	oss << " Tipo: Piloto Surpresa\n" << Piloto::getAsString();
	return oss.str();
}