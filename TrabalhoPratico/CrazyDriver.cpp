#include "CrazyDriver.h"

CrazyDriver::CrazyDriver(const string& nome, const string& tipo) : Piloto(nome, tipo) {
	this->posicaoAnterior = 0;
	this->iniciaCorrida = rand() % 5 + 1;
}

int CrazyDriver::movimenta(int tempo, int posicao, int nCarrosPista) {

	// In�cio da corrida
	if (iniciaCorrida > tempo) {
		this->posicaoAnterior = posicao;
		return 0;
	}		

	// Momento de come�ar a correr
	if (iniciaCorrida == tempo) {
		acelera(1);
		this->posicaoAnterior = posicao;
		return 1;
	}

	// Meio da corrida
	if (iniciaCorrida < tempo) {
		// Pode danificar o carro (5%)
		if (rand() % 100 + 1 <= PROB_ACIDENTE) {
			// Danifica irremedi�velmente (1)
			danificaCarro(1);
			this->posicaoAnterior = posicao;
			return -1;
		}

		// Primeiro
		if (posicao == 1) {
			// Mant�m a velocidade se for > 0
			if (getCarro()->getVelocidade() > 0) {
				// Mantem velocidade se tiver energia
				if (acelera(0) == -1) {
					ativaEmergencia(true);
					travaAteParar();
					this->posicaoAnterior = posicao;
					return 0;
				}
				this->posicaoAnterior = posicao;
				return 1;
			}
			// Mant�m a velocidade por�m d� um toque no acelerador porque a velocidade � igual a 0
			else {
				if (acelera(1) == -1) {
					ativaEmergencia(true);
					travaAteParar();
					this->posicaoAnterior = posicao;
					return 0;
				}
				this->posicaoAnterior = posicao;
				return 1;
			}
		}
		// �ltimo
		else if (posicao == nCarrosPista) {
			if (trava(1) == -1) {
				// Ativa o sinal de emerg�ncia se n�o tem energia
				ativaEmergencia(true);
				travaAteParar();
				this->posicaoAnterior = posicao;
				return -2;
			}
			this->posicaoAnterior = posicao;
			return 1;
		}
		// 2� ou Pen�ltimo
		else {
			// Perdeu posi��es
			if (this->posicaoAnterior < posicao) {
				// Acelera 2m/s se tiver energia
				if (acelera(2) == -1) {
					// Ativa o sinal de emerg�ncia se n�o tem energia
					ativaEmergencia(true);
					travaAteParar();
					this->posicaoAnterior = posicao;
					return -2;
				}
				this->posicaoAnterior = posicao;
				return 1;
			}
			else {
				// Acelera 1m/s se tiver energia
				if (acelera(1) == -1) {
					// Ativa o sinal de emerg�ncia se n�o tem energia
					ativaEmergencia(true);
					travaAteParar();
					this->posicaoAnterior = posicao;
					return -2;
				}
				this->posicaoAnterior = posicao;
				return 1;
			}
		}
	}
	this->posicaoAnterior = posicao;
	return 0;
}

int CrazyDriver::acidente() {
	danificaCarro(2);
	return -1;
}

Piloto* CrazyDriver::duplica() const {
	return new CrazyDriver(*this);
}

string CrazyDriver::getAsString() const {
	ostringstream oss;
	oss << " Tipo: Crazy Driver\n" << Piloto::getAsString();
	return oss.str();
}

