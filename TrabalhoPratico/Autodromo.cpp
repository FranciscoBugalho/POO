#include "Autodromo.h"

int Autodromo::conta = 0;
vector<string> Autodromo::nomes;

Autodromo::Autodromo(const string& nome, int comprimento, int maxcarros) : nome(nome), pista(comprimento, maxcarros), garagem() { 
	this->corrida = false;
	verificaNomes(nome);
}

Autodromo::Autodromo(const Autodromo& obj) : pista(obj.pista.getComprimento(), obj.pista.getMaxCarros()) {
	*this = obj;
}

Autodromo::~Autodromo() {
	for (Piloto* p : pista.getPilotos()) {
		if (p->getCarro() != nullptr) {
			p->getCarro()->setDano(1);
			p->getCarro()->setVelocidade(-p->getCarro()->getVelocidade());
			p->saiDoCarro();
		}
	}
	for (Piloto* p : garagem.getPilotos()) {
		if (p->getCarro() != nullptr && p != nullptr) {
			p->getCarro()->setDano(1);
			p->saiDoCarro();
		}
	}
	for (Carro* c : garagem.getCarrosSemPilotos())
		c->setDano(1);
}

string Autodromo::getNome() const { return nome; }

void Autodromo::setNome(string nome) { this->nome = nome; }

bool Autodromo::isCorrida() const { return corrida; }

void Autodromo::setCorrida() {
	if (corrida == true) corrida = false;
	else corrida = true;
}

Pista Autodromo::getPista() const { return pista; }

Garagem Autodromo::getGaragem() const { return garagem; }

vector<Piloto*> Autodromo::getPilotosSemCarros() const {
	vector<Piloto*> piloto;
	for (Piloto* p : garagem.getPilotosSemCarro())
		piloto.push_back(p);
	return piloto;
}

vector<Carro*> Autodromo::getCarrosSemPilotos() const { 
	vector<Carro*> carro;
	for (Carro* c : garagem.getCarrosSemPilotos())
		carro.push_back(c);
	return carro;
}

void Autodromo::colocaPilotosECarros(vector<Piloto*> pilotos) {
	int aux = pista.setPilotos(pilotos);
	if (aux <= pista.getMaxCarros())
		garagem.setPilotos(aux, pilotos);
}

void Autodromo::colocaCarrosSemPilotos(vector<Carro*> carros) {
	garagem.setCarrosSemPilotos(carros);
}

void Autodromo::colocaPilotosSemCarros(vector<Piloto*> pilotos) {
	garagem.setPilotosSemCarros(pilotos);
}

string Autodromo::passatempo(int tempo) {
	ostringstream oss;
	//atualizaVectors();
	oss << pista.passatempo(tempo);
	atualizaVectors();
	return oss.str();
}

bool Autodromo::iniciaCorrida() { 
	if (corrida == false) {
		setCorrida();
		return true;
	}
	return false;
}

string Autodromo::listaCarros() const {
	ostringstream oss;
	oss << "Pista " << pista.getComprimento() << "m (" << pista.getMaxCarros() << "): \n";
	oss << pista.listaCarros();
	oss << "\n Garagem: \n";
	oss << garagem.listaCarros();

	return oss.str();
}

string Autodromo::carregaBateria(const char identificador, float energia) {
	ostringstream oss;
	if (isCorrida())
		return "Nao pode executar este comando durante a corrida!\n";

	if (pista.carregaBateria(identificador, energia))
		oss << "A bateria do carro " << identificador << " foi carregada!\n";
	else if (garagem.carregaBateria(identificador, energia))
		oss << "A bateria do carro " << identificador << " foi carregada!\n";
	else
		oss << "O carro " << identificador << " nao existe neste autodromo!\n";
	return oss.str();
}

string Autodromo::carregaBaterias() {
	ostringstream oss;
	if (isCorrida())
		return "Nao pode executar este comando durante a corrida!\n";

	oss << pista.carregaBaterias();
	oss << garagem.carregaBaterias();

	return oss.str();
}

int Autodromo::causaAcidente(const char identificador) {
	if (!isCorrida())
		return -1;
	return pista.causaAcidente(identificador);
}

string Autodromo::stop(const string nome) {
	if (!isCorrida())
		return "Nao pode executar este comando durante a corrida!\n";
	return pista.stop(nome);
}

int Autodromo::destroi(const char identificador) {
	if (!isCorrida())
		return -1;
	return pista.destroi(identificador);
}

string Autodromo::getPiloto(const char identificador) {  return pista.getPiloto(identificador); }

vector<vector<char>> Autodromo::getArrayPistas() const { return pista.getArrayPistas(); }

vector<string> Autodromo::getCarrosNaGaragem() const { return garagem.getInfoCarros(); }

string Autodromo::getNomePiloto(int i) { return pista.getNomePiloto(i); }

int Autodromo::getMaxCarrosNaPista() const { return pista.getMaxCarros(); }

int Autodromo::getTempo() const { return pista.getTempo(); }

vector<char> Autodromo::getCarrosEmergencia() const { return pista.getCarrosEmergencia(); }

int Autodromo::nCarrosPista() const { return pista.nCarrosPista(); }

char Autodromo::getIdCarro(const string nome) const { return pista.getIdCarro(nome); }

void Autodromo::atualizaVectors() {
	vector<Piloto*> piloto;
	vector<Piloto*> pilotosSemCarro;
	vector<Carro*> carro;

	if (!pista.getCarros().empty())
		for (Carro* c : pista.getCarros())
			carro.push_back(c);
	if (!pista.getPilotosSemCarro().empty())
		for (Piloto* p : pista.getPilotosSemCarro())
			pilotosSemCarro.push_back(p);
	if (!pista.getPilotos().empty())
		for (Piloto* p : pista.getPilotos())
			piloto.push_back(p);
	pista.limpaVetores();

	if (!garagem.getCarrosSemPilotos().empty())
		for (Carro* c : garagem.getCarrosSemPilotos())
			carro.push_back(c);
	if (!garagem.getPilotos().empty())
		for (Piloto* p : garagem.getPilotos())
			piloto.push_back(p);
	if (!garagem.getPilotosSemCarro().empty())
		for (Piloto* p : garagem.getPilotosSemCarro())
			pilotosSemCarro.push_back(p);
		
	colocaPilotosECarros(piloto);
	colocaCarrosSemPilotos(carro);
	colocaPilotosSemCarros(pilotosSemCarro);
}

void Autodromo::verificaNomes(const string nome) {
	bool feito = false;
	for (string n : nomes) {
		if (Utils::minusculas(n) == Utils::minusculas(nome)) {
			++this->conta;
			mudaNome(nome);
			feito = true;
			break;
		}
	}
	if (!feito)
		setNome(nome);
	nomes.push_back(nome);
}

void Autodromo::mudaNome(const string nome) {
	setNome(conta + nome);
}

Autodromo& Autodromo::operator=(const Autodromo& a) {
	if (this == &a)
		return *this;

	corrida = a.isCorrida();
	
	return *this;
}

string Autodromo::getAsString() const {
	ostringstream oss;

	oss << "\n Autodromo " << getNome() << "\n" << pista.getAsString() << "\n" << garagem.getAsString() << endl;

	return oss.str();
}

ostream& operator<<(ostream& o, const Autodromo& a) {
	o << a.getAsString();
	return o;
}

string operator+(const int i, const string nome) {
	ostringstream oss;
	oss << nome <<  i;
	return oss.str();
}
