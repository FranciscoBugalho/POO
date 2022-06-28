#include "Identificadores.h"
#include "DirecaoGeralViacao.h"

DirecaoGeralViacao::DirecaoGeralViacao() : nome("Direcao Geral de Viacao") { }

DirecaoGeralViacao::DirecaoGeralViacao(const DirecaoGeralViacao& obj) {
	*this = obj;
}

DirecaoGeralViacao::~DirecaoGeralViacao() {
	for (auto ptrP : getPilotos())
		delete ptrP;

	for (auto ptrC : getCarros())
		delete ptrC;
}

string DirecaoGeralViacao::getNome() const { return this->nome; }

void DirecaoGeralViacao::setNome(const string nome) { this->nome = nome; }

vector<Piloto*> DirecaoGeralViacao::getPilotos() const { return pilotos; }

vector<Carro*> DirecaoGeralViacao::getCarros() const { return carros; }

int DirecaoGeralViacao::pesquisaPilotos(const string nome) {
	for (int i = 0; i != pilotos.size(); i++) {
		if (Utils::minusculas(pilotos[i]->getNome()) == Utils::minusculas(nome))
			return i;
	}
	return -1;
}

int DirecaoGeralViacao::pesquisaCarros(const char identificador) {
	for (int i = 0; i != carros.size(); i++) {
		if (tolower(carros[i]->getIdentificacao()) == tolower(identificador))
			return i;
	}
	return -1;
}

string DirecaoGeralViacao::adicionaPiloto(const string tipo, const string nome) {
	if (tipo == CHAR_CRAZYDRIVER)
		pilotos.push_back(new CrazyDriver(nome, tipo));
	else if (tipo == CHAR_PILOTORAPIDO)
		pilotos.push_back(new PilotoRapido(nome, tipo));
	else if (tipo == CHAR_PILOTOSURPRESA)
		pilotos.push_back(new PilotoSurpresa(nome, tipo));
	else if (tipo == "assassino")
		pilotos.push_back(new Assassino(nome, tipo));
	else
		return " ";
	return nome;
}

bool DirecaoGeralViacao::removePiloto(const string nome) {
	for (auto ptr = pilotos.begin(); ptr < pilotos.end(); ) {
		if (Utils::minusculas((*ptr)->getNome()) == Utils::minusculas(nome)) {
			if((*ptr)->getCarro() != nullptr)
				(*ptr)->saiDoCarro();
			delete (*ptr);
			ptr = pilotos.erase(ptr);
			return true;
		}
		else {
			*(ptr++);
		}
	}
	return false;
}

char DirecaoGeralViacao::adicionaCarro(const string marca, const string modelo, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima) {
	Carro* c = new Carro(marca, modelo, capadicadeInicial, capacidadeMaxima, velocidadeMaxima);
	carros.push_back(c);
	return c->getIdentificacao();
}

char DirecaoGeralViacao::adicionaCarroSM(const string marca, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima) {
	Carro* c = new Carro(marca, capadicadeInicial, capacidadeMaxima, velocidadeMaxima);
	carros.push_back(c);
	return c->getIdentificacao();
}

bool DirecaoGeralViacao::removeCarro(const char identificador) {
	for (auto ptr = carros.begin(); ptr < carros.end(); ) {
		if (toupper((*ptr)->getIdentificacao()) == toupper(identificador)) {
			if ((*ptr)->getPiloto() != nullptr)
				ostringstream oss(saiDoCarro((*ptr)->getIdentificacao()));
			delete (*ptr);
			ptr = carros.erase(ptr);
			return true;
		}
		else
			*(ptr++);
	}
	return false;
}

string DirecaoGeralViacao::entraNoCarro(const char& identificador, const string& nome) {
	ostringstream oss;
	int posicaoCarro = pesquisaCarros(identificador);
	int posicaoPiloto = pesquisaPilotos(nome);

	if (posicaoCarro == -1 && posicaoPiloto == -1) {
		oss << "O carro " << identificador << "  e o piloto " << nome << " nao existem.\n";
		return oss.str();
	}

	if (posicaoCarro == -1) {
		oss << "O carro " << identificador << " nao existe.\n";
		return oss.str();
	}

	if (posicaoPiloto == -1) {
		oss << "O piloto " << nome << " nao existe na " << getNome() << ".\n";
		return oss.str();
	}

	oss << getPilotos()[posicaoPiloto]->entraNoCarro(getCarros()[posicaoCarro]);

	return oss.str();
}

string DirecaoGeralViacao::saiDoCarro(const char& identificador) {
	ostringstream oss;
	int posicaoCarro = pesquisaCarros(identificador);

	if (posicaoCarro == -1) {
		oss << "O carro " << identificador << " nao existe!\n";
		return oss.str();
	}

	if (getCarros()[posicaoCarro]->getPiloto() == nullptr) {
		oss << "O carro " << identificador << " nao tem piloto!\n";
		return oss.str();
	}
	else {
		for (Piloto* p : getPilotos()) {
			if (p->getCarro() != nullptr) {
				if (tolower(p->getCarro()->getIdentificacao()) == tolower(identificador)) {
					p->saiDoCarro();
					oss << "O piloto " << p->getNome() << " saiu do carro " << identificador << ".\n";
					return oss.str();
				}
			}
			
		}
	}
	return " ";
}

int DirecaoGeralViacao::getPilotosSize() const {
	return (int)pilotos.size();
}

int DirecaoGeralViacao::getCarrosSize() const {
	return (int)carros.size();
}

bool DirecaoGeralViacao::isPilotosEmCarros() {
	int contador = 0;

	for (Piloto* p : pilotos) {
		if (p->getCarro() != nullptr)
			contador++;
	}
	if (contador >= 2)
		return true;

	return false;	
}

vector<Piloto*> DirecaoGeralViacao::getPilotosEmCarros() {
	vector<Piloto*> pilotosAux;
	for (Piloto* p : pilotos) {
		if (p->getCarro() != nullptr)
			pilotosAux.push_back(p);
	}
	return pilotosAux;
}

DirecaoGeralViacao& DirecaoGeralViacao::operator=(const DirecaoGeralViacao& dgv) {
	if (this == &dgv)
		return *this;

	for (Carro* c : carros)
		delete c;
	carros.clear();

	for (Carro* c : dgv.carros)
		carros.push_back(new Carro(*c));

	for (Piloto* p : pilotos)
		delete p;
	pilotos.clear();

	for (Piloto* p : dgv.pilotos)
		pilotos.push_back(p->duplica());

	nome = dgv.nome;

	return *this;
}

vector<string> DirecaoGeralViacao::getPilotosListaSTR() const {
	ostringstream oss;

	vector<string> pilotosSTR;
	for (Piloto* p : getPilotos()) {
		pilotosSTR.push_back("Nome: " + p->getNome());
		pilotosSTR.push_back("Tipo: " + p->getTipo());
		if (p->getCarro() == nullptr)
			pilotosSTR.push_back("A conduzir: N/A");
		else {
			oss << "A conduzir: " << p->getCarro()->getIdentificacao() << "  ";
			pilotosSTR.push_back(oss.str());
		}
		pilotosSTR.push_back("BREAK");
		oss.str("");
		oss.clear();
	}
	return pilotosSTR;
}

vector<string> DirecaoGeralViacao::getCarrosListaSTR() const {
	vector<string> carrosSTR;
	ostringstream oss;
	for (Carro* c : getCarros()) {
		carrosSTR.push_back("Marca: " + c->getMarca());
		oss << "Identificador: " << c->getIdentificacao();
		carrosSTR.push_back(oss.str());
		if (c->getPiloto() == nullptr)
			carrosSTR.push_back("Sem piloto");
		else
			carrosSTR.push_back("Piloto: " + c->getPiloto()->getNome());
		if (c->getDano() != 0) {
			oss.str("");
			oss.clear();
			oss << "Dano: " << c->getDano();
			carrosSTR.push_back(oss.str());
		}
		carrosSTR.push_back("BREAK");
		oss.str("");
		oss.clear();
	}
	return carrosSTR;
}

string DirecaoGeralViacao::getPilotosStr() const { 
	ostringstream oss;
	for (Piloto* p : pilotos)
		oss << p->getAsString();
	return oss.str();
}

string DirecaoGeralViacao::getCarrosStr() const {
	ostringstream oss;
	for (Carro* c : carros)
		oss << c->getAsString();
	return oss.str();
}

string DirecaoGeralViacao::getAsString() const {
	ostringstream oss;
	oss << "" << getNome() << ":\n" << getCarrosStr() << "\n" << getPilotosStr() << endl;
	return oss.str();
}

ostream& operator<<(ostream& o, const DirecaoGeralViacao& dgv) {
	o << dgv.getAsString();
	return o;
}
