#include "Garagem.h"

Garagem::Garagem() { }

Garagem::~Garagem() { }

vector<Piloto*> Garagem::getPilotos() const { return pilotos; }

vector<Piloto*> Garagem::getPilotosSemCarro() const { return pilotosSemCarros; }

vector<Carro*> Garagem::getCarrosSemPilotos() const { return carros; }

void Garagem::setPilotos(int nCarros, vector<Piloto*> pilotos) {
	if (!this->pilotos.empty() && pilotos.size() != 0)
		this->pilotos.clear();

	for (auto i = nCarros; i < pilotos.size(); i++) {
		if (pilotos[i]->getCarro() != nullptr)
			this->pilotos.push_back(pilotos[i]);
	}

	for (Piloto* p : this->pilotos) {
		if (p->getCarro() != nullptr) {
			p->getCarro()->setVelocidade(0);
			p->getCarro()->setTravao(false);
			p->ativaEmergencia(false);
			p->getCarro()->setX(-1);
		}
	}
}

void Garagem::setCarrosSemPilotos(vector<Carro*> carros) {
	if (!this->carros.empty() && carros.size() != 0)
		this->carros.clear();
	for (Carro* c : carros) {
		c->setVelocidade(0);
		c->setTravao(false);
		c->setEmergencia(false);
		c->setX(-1);
		this->carros.push_back(c);
	}
}

void Garagem::setPilotosSemCarros(vector<Piloto*> piloto) {
	if (!pilotosSemCarros.empty() && piloto.size() != 0)
		pilotosSemCarros.clear();
	for (Piloto* p : piloto)
		pilotosSemCarros.push_back(p);
}

string Garagem::listaCarros() const {
	ostringstream oss;
	int contador = 0;
	for (Piloto* p : pilotos) {
		oss << " " << p->getCarro()->getIdentificacao() << " " << p->getCarro()->getMarca() << " / " << p->getNome() << " (" << p->getTipo() << ") - "
			<< p->getCarro()->getEnergia() << "mAh, " << p->getCarro()->getCapacidadeMaxima() << "mAh \n";
		contador++;
	}
	for (Carro* c : carros) {
		oss << " " << c->getIdentificacao() << " " << c->getMarca() << " / Sem piloto - " << c->getEnergia() << "mAh, " << c->getCapacidadeMaxima() << "mAh; Dano: " << c->getDano() << " \n";
		contador++;
	}
	for (Piloto* p : pilotosSemCarros) {
		oss << " Piloto " << p->getNome() << " (" << p->getTipo() << ").\n";
		contador++;
	}
	if (contador == 0)
		return " Nao ha carros nem pilotos na garagem!\n";
	return oss.str();
}

bool Garagem::carregaBateria(char identificador, float energia) {
	for (Piloto* p : pilotos) {
		if (tolower(p->getCarro()->getIdentificacao()) == tolower(identificador)) {
			if (p->getCarro()->getDano() == 0)
				p->getCarro()->setEnergia(energia);
			return true;
		}
	}
	return false;
}

string Garagem::carregaBaterias() {
	ostringstream oss;
	int contador = 0;
	int total = 0;

	for (Piloto* p : pilotos) {
		if (p->getCarro()->getDano() == 0) {
			p->getCarro()->setEnergia(p->getCarro()->getCapacidadeMaxima());
			contador++;
		}
		++total;
	}

	if (contador == 0)
		return " Nao ha carros na garagem para carregar baterias!\n";

	oss << " Foram carregadas " << contador << " baterias num total de " << total << " carros na garagem!\n";
	return oss.str();
}

vector<string> Garagem::getInfoCarros() const {
	vector<string> carrosAux;
	ostringstream oss;

	for (Piloto* p : pilotos) {
		if (p->getCarro() != nullptr) {
			carrosAux.push_back("Piloto: " + p->getNome() + " (" + p->getTipo() + ") ");
			oss << "Ident: " << p->getCarro()->getIdentificacao() << "; Dano: " << p->getCarro()->getDano() << "; Energia: " << p->getCarro()->getEnergia();
			carrosAux.push_back(oss.str());
			carrosAux.push_back("BREAK");
			oss.str("");
			oss.clear();
		}
	}

	for (Carro* c : carros) {
		carrosAux.push_back("Piloto: Sem Piloto     ");
		oss << "Ident: " << c->getIdentificacao() << "; Dano: " <<c->getDano() << "; Energia: " << c->getEnergia();
		carrosAux.push_back(oss.str());
		carrosAux.push_back("BREAK");
		oss.str("");
		oss.clear();
	}

	for (Piloto* p : pilotosSemCarros) {
		carrosAux.push_back("Piloto: " + p->getNome() + " (" + p->getTipo() + ") ");
		carrosAux.push_back("Sem carro.                     ");
		carrosAux.push_back("BREAK");
		oss.str("");
		oss.clear();
	}

	return carrosAux;
}

string Garagem::getPilotosStr() const {
	ostringstream oss;
	for (Piloto* p : pilotos)
		oss << p->getAsString();
	return oss.str();
}

string Garagem::getAsString() const {
	ostringstream oss;

	oss << " Garagem: " << getPilotosStr();

	return oss.str();
}
