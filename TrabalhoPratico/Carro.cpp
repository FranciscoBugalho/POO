#include "Piloto.h"
#include "Carro.h"

int Carro::contador = 96;		// 97(a) - 122(z)

Carro::Carro(const string& marca, const string& modelo, float capadicadeInicial, const float capacidadeMaxima, const int velocidadeMaxima)
	: marca(marca), modelo(modelo), 
		CAPACIDADE_MAXIMA((capacidadeMaxima <= 0.0) ? CAPACIDADE_DEFAULT : capacidadeMaxima), 
		VELOCIDADE_MAXIMA((velocidadeMaxima <= 0) ? VELOCIDADE_DEFAULT : velocidadeMaxima) {
	
	this->energia = verificaEnergiaInicial(capadicadeInicial, CAPACIDADE_MAXIMA);

	this->movimento = false;
	this->travao = false;
	this->velocidade = 0;
	this->emergencia = false;
	this->danificado = 0;
	this->piloto = nullptr;
	this->posicao = 0;
	this->lugar = 0;
	this->x = 0;

	if (contador < 122)
		this->identificacao = ++contador;
	else
		this->identificacao = '?';		// 63
}

Carro::Carro(const string& marca, float capadicadeInicial, const float capacidadeMaxima, const int velocidadeMaxima)
	: marca(marca), modelo("Modelo Base"),
		CAPACIDADE_MAXIMA((capacidadeMaxima <= 0.0) ? CAPACIDADE_DEFAULT : capacidadeMaxima),
		VELOCIDADE_MAXIMA((velocidadeMaxima <= 0) ? VELOCIDADE_DEFAULT : velocidadeMaxima) {
	
	this->energia = verificaEnergiaInicial(capadicadeInicial, CAPACIDADE_MAXIMA);

	this->movimento = false;
	this->travao = false;
	this->velocidade = 0;
	this->emergencia = false;
	this->danificado = 0;
	this->piloto = nullptr;
	this->posicao = 0;
	this->lugar = 0;
	this->x = 0;

	if (contador < 122)
		this->identificacao = ++contador;
	else
		this->identificacao = '?';	// 63
}

Carro::Carro(const Carro& obj) : CAPACIDADE_MAXIMA(obj.getCapacidadeMaxima()), VELOCIDADE_MAXIMA(obj.getVelocidadeMaxima()) {
	*this = obj;
}

Carro::~Carro() { }

string Carro::getMarca() const { return marca; }

string Carro::getModelo() const { return modelo; }

char Carro::getIdentificacao() const { return identificacao; }

void Carro::setIdentificacao() {
	if (getIdentificacao() == toupper(getIdentificacao()))  this->identificacao = tolower(getIdentificacao());
	else this->identificacao = toupper(getIdentificacao());
}

float Carro::getEnergia() const { return energia; }

void Carro::setEnergia(float energia) { 
	if (this->energia + energia >= CAPACIDADE_MAXIMA)
		this->energia = CAPACIDADE_MAXIMA;
	else if (this->energia + energia <= 0)
		this->energia = 0;
	else
		this->energia += energia; 
}

const float Carro::getCapacidadeMaxima() const { return CAPACIDADE_MAXIMA; }

bool Carro::isMovimento() const { return movimento; }

void Carro::setMovimento(bool movimento) { this->movimento = movimento; }

bool Carro::isTravao() const { return travao; }

void Carro::setTravao(bool travao) { this->travao = travao; }

const int Carro::getVelocidadeMaxima() const { return VELOCIDADE_MAXIMA; }

int Carro::getVelocidade() const { return velocidade; }

void Carro::setVelocidade(int velocidade) { 
	if (this->velocidade + velocidade >= getVelocidadeMaxima())
		this->velocidade = getVelocidadeMaxima();
	else if (this->velocidade + velocidade <= 0)
		this->velocidade = 0;
	else
		this->velocidade += velocidade;
}

bool Carro::isEmergencia() const { return emergencia; }

void Carro::setEmergencia(bool emergencia) { this->emergencia = emergencia; }

int Carro::getDano() const { return danificado; }

void Carro::setDano(int dano) {
	if (dano < 0 || dano > 2) this->danificado = 0;
	else this->danificado = dano;
}

Piloto* Carro::getPiloto() const { return piloto; }

void Carro::setPiloto(Piloto * p) { piloto = p; }

int Carro::getPosicao() const { return posicao; }

void Carro::setPosicao(int posicao) { this->posicao = posicao; }

int Carro::getLugar() const { return lugar; }

void Carro::setLugar(int lugar) { this->lugar = lugar; }

int Carro::getX() const { return x; }

void Carro::setX(int x) { this->x = x; }

float Carro::verificaEnergiaInicial(float capacidadeInicial, const float capacidadeMaxima) {
	if (capacidadeInicial < 0.0)
		return 0.0;
	else if (capacidadeInicial > capacidadeMaxima)
		return capacidadeMaxima;
	else
		return capacidadeInicial;
}

string Carro::carregarEnergia(float energia) {
	ostringstream oss;

	if (energia <= 0.0) {
		oss << "Necessita de indicar uma quantidade de energia maior que 0 (zero).";
		return oss.str();
	}

	oss << "O carro " << getIdentificacao();
	if (getIdentificacao() == '?')
		oss << " " << getMarca() << " " << getModelo();

	if (isMovimento() == true) {
		oss << " esta em movimento.";
		return oss.str();
	}
		
	if (getEnergia() == getCapacidadeMaxima()) {
		oss << " esta com a capacidade maxima (" << getCapacidadeMaxima() << ").";
		return oss.str();
	}

	if (getEnergia() + energia >= getCapacidadeMaxima()) {
		oss << " foi carregado ate a capacidade maxima (" << getCapacidadeMaxima() << ").";
		return oss.str();
	}
	else {
		setEnergia(energia);
		oss << " foi carregado. A sua energia atual e de " << getEnergia() << ".";
		return oss.str();
	}
}

void Carro::atualizaPilotoEIdentificacao(Piloto* p) {
	setIdentificacao();
	setPiloto(p);
}

int Carro::acelerar(int velocidade) {
	if (isMovimento()) {
		setTravao(false);
		setEnergia(-0.1);		
		if (getEnergia() > 0) {
			setVelocidade(velocidade);
			setX(getX() + getVelocidade());
			return 1;
		}
		else {
			setMovimento(false);
			return -1;
		}
	}
	return 0;
}

int Carro::travar(int velocidade) {
	if (isMovimento()) {
		setEnergia(-0.1);
		if (getEnergia() > 0) {
			setVelocidade(-velocidade);
			if(getVelocidade() >= 0)
				setX(getX() + getVelocidade());
			return 1;
		}
		else {
			setTravao(false);
			setMovimento(false);
			return -1;
		}
	}
	return 0;
}

void Carro::travaAteParar() {
	if (isMovimento()) {
		setTravao(true);
		setEnergia((-0.1 * getVelocidade()));
		if (getEnergia() > 0) {
			setVelocidade(-getVelocidade());
		}
	}
	else {
		setTravao(false);
		setMovimento(false);
	}
}

void Carro::danificaCarro(int dano) {
	setDano(dano);
	if (dano == 1) {
		setVelocidade(-getVelocidade());
		setTravao(false);
		setMovimento(false);
		setEmergencia(true);
	}
	else if (dano == 2) {
		setVelocidade(-getVelocidade());
		setTravao(false);
		setMovimento(false);
		setEmergencia(true);
	}
}

string Carro::adicionaPiloto(Piloto* p) {
	ostringstream oss;

	if (p == nullptr) {
		oss << "O argumento enviado é inválido.";
		return oss.str();
	}

	if (getPiloto() != nullptr) {
		oss << "O carro " << getIdentificacao() << " ja tem um piloto.";
		return oss.str();
	}
	else {
		if (getDano() == 0) {
			setPiloto(p);
			oss << "O Piloto foi adicionado ao carro " << getIdentificacao() << " com sucesso.";
			return oss.str();
		}
		else {
			if (getDano() == 1) {
				setPiloto(p);
				oss << "O Piloto foi adicionado ao carro " << getIdentificacao() << " com sucesso. Porem o carro esta irremediavelmente danificado.";
				return oss.str();
			}
			else {
				oss << "Nao e possivel adicionar um piloto a um carro irreparavel.";
				return oss.str();
			}
		}
	}
}

Carro &Carro::operator=(const Carro& c) {
	if (this == &c)
		return *this;

	if (c.getPiloto() != nullptr) {
		piloto = c.getPiloto()->duplica();
		string aux = piloto->entraNoCarro(this);
	}

	marca = c.getMarca();
	modelo = c.getModelo();
	energia = verificaEnergiaInicial(energia, c.getCapacidadeMaxima());
	movimento = c.isMovimento();
	travao = c.isTravao();
	velocidade = c.getVelocidade();
	emergencia = c.isEmergencia();
	danificado = c.getDano();
	identificacao = c.getIdentificacao();
	posicao = c.getPosicao();
	lugar = c.getLugar();
	x = c.getX();

	return *this;
}

//bool Carro::operator<(const Piloto& p) const {
//	return (this->posicao < p.getCarro()->getPosicao());
//}

string Carro::getAsString() const {
	ostringstream oss;

	oss << " Carro: \n\tIdentificador - " << getIdentificacao() << "; \n\tMarca - " << getMarca() << "; \n\tModelo - " << getModelo() <<
		";\n\tEnergia - " << getEnergia() << " \n\t  (Capacidade Maxima: " << getCapacidadeMaxima() << "); \n\tMovimento - " << isMovimento() <<
		";\n\tVelocidade - " << getVelocidade() << " \n\t  (Velocidade Maxima: " << getVelocidadeMaxima() << "); \n\tEmergencia - " << isEmergencia();

	if (getDano() == 0)
		oss << "\n\tDano - Nao esta danificado;";
	else if (getDano() == 1)
		oss << "\n\tDano - Irremediavelmente irreversivel;";
	else
		oss << "\n\tDano - Irreparavel";

	oss << "\n\tPiloto - ";
	
	if (getPiloto() == nullptr)
		oss << "Sem piloto!" << endl;
	else
		oss << getPiloto()->getNome() << endl;

	return oss.str();
}

ostream& operator<<(ostream& o, const Carro& c) {
	o << c.getAsString();
	return o;
}
