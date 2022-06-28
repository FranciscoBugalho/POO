#include "Piloto.h"

int Piloto::contador = 0;
vector<string> Piloto::nomes;

Piloto::Piloto(const string& nome, const string& tipo) : nome(nome), tipo(tipo) {
	this->carro = nullptr;
	this->pontuacao = 0;
	this->pontua = true;
	verificaNome(nome);
}

Piloto::Piloto(const Piloto& obj) {
	//carro = nullptr;
	*this = obj;
}

Piloto::~Piloto() { }

string Piloto::getNome() const { return nome; }

string Piloto::getTipo() const { return tipo; }

void Piloto::setNome(string nome) { this->nome = nome; }

Carro* Piloto::getCarro() const { return carro; }

void Piloto::setCarro(Carro* carro) { this->carro = carro; }

int Piloto::getPontuacao() const { return pontuacao; }

void Piloto::setPontuacao(int pontuacao) { this->pontuacao += pontuacao; }

bool Piloto::getPontua() const { return pontua; }

void Piloto::setPontua(bool pode) {	this->pontua = pode; }

void Piloto::verificaNome(const string nome) {
	bool feito = false;
	for (string n : nomes) {
		if (Utils::minusculas(n) == Utils::minusculas(nome)) {
			++this->contador;
			mudaNome(nome);
			feito = true;
			break;
		}
	}
	if(!feito)	
		setNome(nome);
	nomes.push_back(nome);
}

void Piloto::mudaNome(const string nome) {
	setNome(nome + contador);
}

string Piloto::entraNoCarro(Carro* carro) {
	ostringstream oss;

	if (carro->getPiloto() != nullptr) {
		oss << "O carro em que pertende entrar ja tem um piloto!\n";
		return oss.str();
	}

	if (carro->getDano() != 0) {
		oss << "Nao pode entrar num carro danificado!\n";
		return oss.str();
	}

	oss << "O piloto " << getNome();

	if (getCarro() != nullptr) {
		oss << " encontra-se a conduzir o carro " << getCarro()->getIdentificacao() << ".\n Ira sair e entrar no carro " << carro->getIdentificacao() << ".\n";
		getCarro()->atualizaPilotoEIdentificacao(nullptr);
		setCarro(carro);
		carro->atualizaPilotoEIdentificacao(this);
		return oss.str();
	}
	else {
		oss << " nao se encontra a conduzir nenhum carro.\n Vai entrar no carro " << carro->getIdentificacao() << ".\n";
		setCarro(carro);
		carro->atualizaPilotoEIdentificacao(this);
		return oss.str();
	}

	if (getCarro()->getIdentificacao() == carro->getIdentificacao()) {
		oss << " ja se encontra no carro " << getCarro()->getIdentificacao() << ".\n";
		return oss.str();
	}
}

void Piloto::saiDoCarro() {
	carro->atualizaPilotoEIdentificacao(nullptr);
	setCarro(nullptr);
}

void Piloto::atualizaXYCarro(int x, int y) {
	carro->setX(x);
	carro->setPosicao(y);
}

void Piloto::atualizaMovimento(bool movimento) { carro->setMovimento(movimento); }

int Piloto::acelera(int velocidade) { return carro->acelerar(velocidade); }

int Piloto::trava(int velocidade) { return carro->travar(velocidade); }

void Piloto::travaAteParar() { carro->travaAteParar(); }

void Piloto::danificaCarro(int dano) { carro->danificaCarro(dano); }

void Piloto::ativaEmergencia(bool emergencia) { carro->setEmergencia(emergencia); }

void Piloto::vaiMeta(int posicao) { carro->setX(posicao); }

Piloto &Piloto::operator=(const Piloto& p) {
	if (&p == this)
		return *this;

	/*if (carro != nullptr) {
		saiDoCarro();
		delete carro;
	}*/

	if (p.getCarro() != nullptr) {
		carro = p.getCarro(); // BUG
		if (carro) {
			nome = p.getNome();
			pontuacao = p.getPontuacao();
			pontua = p.getPontua();
			tipo = p.getTipo();
			string aux = this->entraNoCarro(carro);
			return *this;
		}
	}

	nome = p.getNome();
	pontuacao = p.getPontuacao();
	pontua = p.getPontua();
	tipo = p.getTipo();

	return *this;
}

string Piloto::getAsString() const {
	ostringstream oss;

	oss << " Piloto " << getNome() << "\n A conduzir: ";

	if (getCarro() == nullptr)
		oss << "N/a.\n";
	else
		oss << getCarro()->getIdentificacao() << ".\n";

	return oss.str();
}

ostream& operator<<(ostream& o, const Piloto& p) {
	o << p.getAsString();
	return o;
}

string operator+(const string nome, const int i) {
	ostringstream oss;
	oss << nome << "_v" << i;
	return oss.str();
}
