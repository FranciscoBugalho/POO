#include "PilotoRapido.h"

PilotoRapido::PilotoRapido(const string& nome, const string& tipo) : Piloto(nome, tipo) {
	this->conta3Segundos = 1;
	this->conta10Segundos = 1;
}

int PilotoRapido::movimenta(int tempo, int posicao, int nCarrosPista) {

	// Começa a correr sempre no segundo 1
	if (tempo <= 0)
		return 0;
	
	// Energia == (CapacidadeMaxima / 2)
	if (getCarro()->getEnergia() <= (getCarro()->getCapacidadeMaxima() / 2)) {
		// Acelera 1m/s de 3 em 3 segundos
		if (this->conta3Segundos == 3) {
			acelera(1);
			this->conta3Segundos = 0;
		}
		// Mantém a velocidade até os 3 segundos
		else {
			acelera(0);
			this->conta3Segundos++;
		}

		// Pode ter um ataque de pânico (10%) a cada 10 segundos
		if (this->conta10Segundos == 10) {
			if (rand() % 100 + 1 <= PROB_ATAQUEPANICO) {
				this->conta10Segundos = 0;
				ativaEmergencia(true);
				return -2;
			}
		}
		else
			this->conta10Segundos++;
	}
	else
		// Acelera sempre
		acelera(1);
	return 1;
}

Piloto* PilotoRapido::duplica() const {
	return new PilotoRapido(*this);
}

int PilotoRapido::acidente() {
	danificaCarro(2);
	return 0;
}

string PilotoRapido::getAsString() const {
	ostringstream oss;
	oss << " Tipo: Piloto Rapido\n" << Piloto::getAsString();
	return oss.str();
}