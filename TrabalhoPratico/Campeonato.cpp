#include "Campeonato.h"

Campeonato::Campeonato(vector<Autodromo*> autodromos, vector<Piloto*> pilotos) : autodromos(autodromos), pilotos(pilotos) {
	this->nCorrida = 0;
	this->primeira = true;
	this->fim = false;
	colocaPilotosECarros();
	carregaTudo();
	inicializaPontuacoes();
}

Campeonato::~Campeonato() {
	for (auto ptrA : autodromos)
		delete ptrA;
}

int Campeonato::getNCorrida() const { return nCorrida; }

void Campeonato::setNCorrida() { ++nCorrida; }

vector<Autodromo*> Campeonato::getAutodromos() const { return autodromos;  }

string Campeonato::getAutodromoAtual() const { return autodromos[nCorrida]->getNome(); }

int Campeonato::getTempo() const { 
	if (!autodromos[nCorrida]->isCorrida())
		return 0;
	return autodromos[nCorrida]->getTempo(); 
}

int Campeonato::getMaxCarros() const { return autodromos[nCorrida]->getMaxCarrosNaPista(); }

vector<char> Campeonato::getCarrosEmergencia() const { return autodromos[nCorrida]->getCarrosEmergencia(); }

void Campeonato::setPilotosSemCarro() {
	if (!pilotosSemCarros.empty())
		pilotosSemCarros.clear();
	for (Piloto* p : autodromos[nCorrida]->getPilotosSemCarros()) {
		pilotosSemCarros.push_back(p);
		for (Piloto* piloto : pilotos) {
			if (Utils::minusculas(p->getNome()) == Utils::minusculas(piloto->getNome())) {
				remove(pilotos.begin(), pilotos.end(), p);
				pilotos.resize(pilotos.size() - 1);
			}
		}
	}
}

void Campeonato::setCarrosSemPiloto() {
	if (!carrosSemPilotos.empty())
		carrosSemPilotos.clear();
	for (Carro* c : autodromos[nCorrida]->getCarrosSemPilotos())
		carrosSemPilotos.push_back(c);
}

string Campeonato::getPosicoes() {
	ostringstream oss; 
	if (autodromos[nCorrida]->nCarrosPista() == 0)
		return "Nao existem carros na pista para esta corrida!";

	for (int i = 0; i != autodromos[nCorrida]->nCarrosPista(); i++)
		oss << i + 1 << (char)248 << ": " << autodromos[nCorrida]->getNomePiloto(i) << " (" << autodromos[nCorrida]->getIdCarro(autodromos[nCorrida]->getNomePiloto(i)) << "); ";	// 248 == º
	return oss.str();
}

void Campeonato::colocaPilotosECarros() { autodromos[nCorrida]->colocaPilotosECarros(pilotos); }

vector<vector<char>> Campeonato::getArrayPistas() { return autodromos[nCorrida]->getArrayPistas(); }

vector<string> Campeonato::getCarrosGaragem() { return autodromos[nCorrida]->getCarrosNaGaragem(); }

bool Campeonato::tempoValido(int tempo) {
	if (tempo <= 0 || tempo >= 20)
		return false;
	return true;
}

string Campeonato::passatempo(int tempo) {
	ostringstream oss;
	oss << autodromos[nCorrida]->passatempo(tempo);
	if (Utils::minusculas(oss.str()) == Utils::minusculas(FIM_CORRIDA) || Utils::minusculas(oss.str()) == Utils::minusculas(FIM_CORRIDA_sPilotos)) {
		this->primeira = false;
		setPilotosSemCarro();
		setCarrosSemPiloto();
		autodromos[nCorrida]->setCorrida();
		oss << " Pode passar para a proxima corrida inserido o comando \"corrida\"!\n";
		return oss.str();
	}
	return oss.str();
}

bool Campeonato::corridaIniciada() {
	if (autodromos[nCorrida]->isCorrida())
		return true;
	return false;
}

string Campeonato::iniciaCorrida() {
	if (!corridaIniciada()) {
		if (!primeira) {
			this->nCorrida++;
			if (nCorrida < ((int)autodromos.size())) {
				if (autodromos[nCorrida]->iniciaCorrida()) {
					colocaPilotosECarros();
					autodromos[nCorrida]->colocaPilotosSemCarros(pilotosSemCarros);
					autodromos[nCorrida]->colocaCarrosSemPilotos(carrosSemPilotos);
					podePontuar();
					if (autodromos[nCorrida]->nCarrosPista() < 2) {
						this->fim = true;
						for (int i = nCorrida; i != autodromos.size(); i++)
							autodromos[i]->setCorrida();
						return "So pode haver uma corrida quando tem 2 carros em condicoes de competir!\n Sugerimos que veja a pontuacao ou volte ao Modo 1 para um novo campeonato!\n";
					}
					return "A corrida foi iniciada.\n";
				}
				return "A corrida ja esta a decorrer.\n";
			}
			else {
				this->nCorrida--;
				this->fim = true;
			}
			return "Nao ha mais corridas! Pode ver as pontuacoes do campeonato ou voltar ao Modo 1.\n";
		}
		autodromos[nCorrida]->iniciaCorrida();
		return "A corrida foi iniciada.\n";
	}
	return "A corrida esta a decorrer.\n";
}

string Campeonato::listaCarros() {
	return autodromos[nCorrida]->listaCarros(); 
}

string Campeonato::carregaBateria(const char identificador, float energia) {
	if (corridaIniciada())
		return "Nao pode executar este comando durante a corrida!\n";
	return autodromos[nCorrida]->carregaBateria(identificador, energia);
}

string Campeonato::carregaBaterias() {
	if (corridaIniciada())
		return "Nao pode executar este comando durante a corrida!\n";
	return autodromos[nCorrida]->carregaBaterias();
}

void Campeonato::carregaTudo() { string aux = carregaBaterias(); }

void Campeonato::inicializaPontuacoes() {
	for (Piloto* p : pilotos) {
		p->setPontuacao(-p->getPontuacao());
		p->setPontua(true);
	}
}

void Campeonato::podePontuar() {
	for (Piloto* p : pilotos) {
		p->setPontua(true);
	}
}

int Campeonato::causaAcidente(const char identificador) {
	if (!corridaIniciada())
		return -1;
	if (getTempo() == 0)
		return -2;
	int acidente = autodromos[nCorrida]->causaAcidente(identificador);
	if (acidente == 0) {
		for (Piloto* p : pilotos) {
			if (tolower(p->getCarro()->getIdentificacao()) == tolower(identificador)) {
				p->saiDoCarro();
				remove(pilotos.begin(), pilotos.end(), p);
				pilotos.resize(pilotos.size() - 1);
			}
		}
	}
	return acidente;
}

string Campeonato::getPiloto(const char identificador) {
	return autodromos[nCorrida]->getPiloto(identificador);
}

string Campeonato::stop(const string nome) {
	if (!corridaIniciada())
		return "Nao pode executar este comando durante a corrida!\n";
	if (getTempo() == 0)
		return "Nao pode parar um piloto sem ele comecar a corrida!\n";
	return autodromos[nCorrida]->stop(nome);
}

int Campeonato::destroi(const char identificador) {
	if (!corridaIniciada())
		return -1;
	if (getTempo() == 0)
		return -2;
	int destruido = autodromos[nCorrida]->destroi(identificador);
	if (destruido == 0) {
		for (Piloto* p : pilotos) {
			if (p->getCarro() == nullptr) {
				remove(pilotos.begin(), pilotos.end(), p);
				pilotos.resize(pilotos.size() - 1);
			}
		}
	}
	return destruido;
}

string Campeonato::getPontuacoes() {
	if (!fim)
		return "O campeonato ainda nao terminou!\n";

	if (pilotos.empty() && pilotosSemCarros.empty())
		return "Nao existem pilotos para ver as classificacoes!\n";

	vector<Piloto*> aux;
	ostringstream oss;

	for (Piloto* p : pilotos)
		if(p->getCarro() != nullptr)
			aux.push_back(p);

	for (Piloto* p : pilotosSemCarros)
		aux.push_back(p);

	sort(aux.begin(), aux.end(), [](Piloto* a, Piloto* b) { return a->getPontuacao() > b->getPontuacao(); });

	oss << "Classificacoes: \n";
	if ((int)aux.size() >= 3) {
		for (int i = 0; i < 3; i++)
			oss << "\t" << (i + 1) << (char)248 << " - " << aux[i]->getNome() << " (Pontos: " << aux[i]->getPontuacao() << ") \n";
	}
	else {
		for (int i = 0; i != aux.size(); i++)
			oss << "\t" << (i + 1) << (char)248 << " - " << aux[i]->getNome() << " (Pontos: " << aux[i]->getPontuacao() << ") \n";
	}
	return oss.str();
}