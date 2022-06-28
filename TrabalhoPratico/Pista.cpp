#include "Pista.h"

Pista::Pista(int comprimento, int maximoCarros) :
		comprimento((comprimento < 100 || comprimento > COMPRIMENTO_MAXIMO) ? COMPRIMENTO_DEFAULT : comprimento),
		maximoCarros((maximoCarros < 2 || maximoCarros > MAX_MAXCARROS) ? MAXCARROS_DEFAULT : maximoCarros) {
	this->tempo = 0;
	initPista();
}

Pista::~Pista() { }

vector<Piloto*> Pista::getPilotos() const { return pilotos; }

vector<Carro*> Pista::getCarros() const { return carros; }

vector<Piloto*> Pista::getPilotosSemCarro() const { return pilotosSemCarros; }

int Pista::getComprimento() const { return comprimento; }

int Pista::getMaxCarros() const { return maximoCarros; }

int Pista::getTempo() const { return tempo; }

void Pista::setTempo() { this->tempo++; }

int Pista::nCarrosPista() const { return (int)pilotos.size(); }

int Pista::setPilotos(const vector<Piloto*> piloto) {
	int contador = 0;
	int divisor = comprimento / TAM_LINHA_FICH;

	if (!pilotos.empty() && piloto.size() != 0)
		pilotos.clear();

	for (Piloto* p : piloto) {
		if (getTempo() == 0) {
			if (p->getCarro() != nullptr && contador < maximoCarros && p->getCarro()->getDano() == 0) {
				p->atualizaXYCarro(0, contador);
				p->getCarro()->setVelocidade(-p->getCarro()->getVelocidade());
				pilotos.push_back(p);
				++contador;
				updatePistas(p->getCarro()->getIdentificacao(), p->getCarro()->getX() / divisor, p->getCarro()->getPosicao());
			}
		}
		else {
			if (p->getCarro() != nullptr && contador < maximoCarros && p->getCarro()->getDano() == 0 && p->getCarro()->getX() > 0 && !p->getCarro()->isEmergencia()) {
				pilotos.push_back(p);
				++contador;
				updatePistas(p->getCarro()->getIdentificacao(), p->getCarro()->getX() / divisor, p->getCarro()->getPosicao());
			}
			else if (p->getCarro() != nullptr && contador < maximoCarros && p->getCarro()->getDano() == 0 && p->getCarro()->getX() == 0 && !p->getCarro()->isEmergencia()) {
				p->atualizaXYCarro(0, p->getCarro()->getPosicao());
				pilotos.push_back(p);
				++contador;
				updatePistas(p->getCarro()->getIdentificacao(), p->getCarro()->getX() / divisor, p->getCarro()->getPosicao());
			}
		}
	}
	organizaPosicoes();
	return contador;
}

string Pista::passatempo(int tempo) {
	int posicaoAtual = 0, comprimento = (getComprimento() / (getComprimento() / TAM_LINHA_FICH));
	int divisor = this->comprimento / comprimento;
	int acidente = 0, contador = 0;
	ostringstream oss;
	
	limpaPista();
	initPista();

	setTempo();
	
	for (Piloto* p : pilotos) {
			posicaoAtual = (p->getCarro()->getX() + p->getCarro()->getVelocidade()) + 1;
			posicaoAtual /= divisor;

			if (posicaoAtual <= comprimento) {
				if (p->getCarro()->getDano() == 0 && !p->getCarro()->isTravao()) {
					p->atualizaMovimento(true);
					// Houve acidente
					acidente = p->movimenta(getTempo(), getPosicaoPiloto(p->getNome()), nCarrosPista());
					if (acidente == -1) {
						int a = this->acidente(getPosicaoPiloto(p->getNome()));
						atualizaPistaAcidente(p->getCarro()->getX(), p->getCarro()->getPosicao());
						oss << "Acidente com o piloto " << p->getNome() << ".\n";

						pilotosSemCarros.push_back(p);
						carros.push_back(p->getCarro());
						p->saiDoCarro();
						remove(pilotos.begin(), pilotos.end(), p);
						pilotos.resize(pilotos.size() - 1);

						if (a != -1) {
							a--;

							oss << " Infelizmente o piloto " << pilotos[a]->getNome() << " tambem ficou envolvido.\n";

							pilotosSemCarros.push_back(pilotos[a]);
							carros.push_back(pilotos[a]->getCarro());
							pilotos[a]->saiDoCarro();
							remove(pilotos.begin(), pilotos.end(), pilotos[a]);
							int anterior = (int)pilotos.size();
							pilotos.resize(pilotos.size() - 1);
							if (pilotos.size() < anterior)
								break;
						}
						else
							oss << " Felizmente nao afetou mais nenhum piloto.\n";
					}
					// Ativou sinal de emergência
					else if (acidente == -2) {
						atualizaPistaAcidente(p->getCarro()->getX(), p->getCarro()->getPosicao());
						oss << "O piloto " << p->getNome() << " ativou o sinal de emergencia.\n";
					}
					else if (acidente == -3) {
						int a = this->acidente(getPosicaoPiloto(p->getNome()));
						oss << "Piloto assassino " << p->getNome() << ".\n";


						if (a != pilotos.size()) {
							oss << " Infelizmente o piloto " << pilotos[a]->getNome() << " foi assassinado.\n";

							atualizaPistaAcidente(pilotos[a]->getCarro()->getX(), pilotos[a]->getCarro()->getPosicao());

							pilotosSemCarros.push_back(pilotos[a]);
							carros.push_back(pilotos[a]->getCarro());
							pilotos[a]->saiDoCarro();
							remove(pilotos.begin(), pilotos.end(), pilotos[a]);
							int anterior = (int)pilotos.size();
							pilotos.resize(pilotos.size() - 1);
						}

						if (a != -1) {
							a = a - 2;

							if (a < 0)
								break;

							oss << " Infelizmente o piloto " << pilotos[a]->getNome() << " foi assassinado.\n";

							atualizaPistaAcidente(pilotos[a]->getCarro()->getX(), pilotos[a]->getCarro()->getPosicao());

							pilotosSemCarros.push_back(pilotos[a]);
							carros.push_back(pilotos[a]->getCarro());
							pilotos[a]->saiDoCarro();
							remove(pilotos.begin(), pilotos.end(), pilotos[a]);
							int anterior = (int)pilotos.size();
							pilotos.resize(pilotos.size() - 1);
							if (anterior > (int)pilotos.size())
								break;
						}


					}
					else
						updatePistas(p->getCarro()->getIdentificacao(), p->getCarro()->getX() / divisor, p->getCarro()->getPosicao());
				}
				else {
					if (p->getCarro()->getVelocidade() <= 0) {
						atualizaPistaAcidente(p->getCarro()->getX(), p->getCarro()->getPosicao());
						p->getCarro()->setX(-1);
						p->atualizaMovimento(false);
					}
					else {
						p->trava(1);
						updatePistas(p->getCarro()->getIdentificacao(), p->getCarro()->getX(), p->getCarro()->getPosicao());
					}
				}
			}
			else {
				if (posicaoAtual > comprimento) {
					if (p->getCarro()->getDano() == 0) {
						p->vaiMeta(this->comprimento);
						updatePistas(p->getCarro()->getIdentificacao(), comprimento - 1, p->getCarro()->getPosicao());
						p->atualizaMovimento(false);

						for (int i = 0; i != pilotos.size(); i++) {
							// Primeiro
							if (Utils::minusculas(pilotos[i]->getNome()) == Utils::minusculas(p->getNome()) && p->getPontua() && i == 0) {
								p->setPontuacao(PONTOS_PRIMEIRO);
								p->setPontua(false);
								break;
							}
							// Segundo
							else if (Utils::minusculas(pilotos[i]->getNome()) == Utils::minusculas(p->getNome()) && p->getPontua() && i == 1) {
								p->setPontuacao(PONTOS_SEGUNDO);
								p->setPontua(false);
								break;
							}
							// Terceiro
							else if (Utils::minusculas(pilotos[i]->getNome()) == Utils::minusculas(p->getNome()) && p->getPontua() && i == 2) {
								p->setPontuacao(PONTOS_TERCEIRO);
								p->setPontua(false);
								break;
							}
						}
					}
				}
				++contador;
			}				
	}

	organizaPosicoes();

	if ((int)pilotos.size() == 0) {
		oss << "Nao ha mais pilotos na pista! Fim da corrida!";
		return oss.str();
	}

	if (contador >= (int)pilotos.size()) {
		oss << "Fim da corrida!";
		return oss.str();
	}

	oss << "Passou " << tempo << "s. (Total: " << getTempo() << "s)";
	return oss.str();
}

int Pista::acidente(int posicao) {
	if (posicao > 0 && posicao < nCarrosPista()) {
		pilotos[posicao]->getCarro()->danificaCarro(1);
		return posicao;
	}
	return -1;
}

bool Pista::carregaBateria(char identificador, float energia) {
	for (Piloto* p : pilotos) {
		if (tolower(p->getCarro()->getIdentificacao()) == tolower(identificador)) {
			p->getCarro()->setEnergia(energia);
			return true;
		}
	}
	return false;
}

string Pista::carregaBaterias() {
	ostringstream oss;
	int contador = 0;

	for (Piloto* p : pilotos) {
		p->getCarro()->setEnergia(p->getCarro()->getCapacidadeMaxima());
		contador++;
	}

	if (contador == 0)
		return "Nao ha carros na pista para carregar baterias!\n";

	oss << "Foram carregadas " << contador << " baterias de carros na pista!\n";
	return oss.str();
}

bool Pista::causaAcidente(const char identificador) {
	ostringstream oss;

	for (Piloto* p : pilotos) {
		if (tolower(p->getCarro()->getIdentificacao()) == tolower(identificador)) {
			if (p->acidente() == -1) {
				int a = acidente(getPosicaoPiloto(p->getNome()));
				atualizaPistaAcidente(p->getCarro()->getX(), p->getCarro()->getPosicao());
				carros.push_back(p->getCarro());
				remove(pilotos.begin(), pilotos.end(), p);
				pilotos.resize(pilotos.size() - 1);

				if (a != -1) {
					a--;
					pilotosSemCarros.push_back(pilotos[a]);
					carros.push_back(pilotos[a]->getCarro());
					pilotos[a]->saiDoCarro();
					remove(pilotos.begin(), pilotos.end(), pilotos[a]);
					pilotos.resize(pilotos.size() - 1);
				}
				return 0;
			}
			else {
				atualizaPistaAcidente(p->getCarro()->getX(), p->getCarro()->getPosicao());
				carros.push_back(p->getCarro());
				remove(pilotos.begin(), pilotos.end(), p);
				pilotos.resize(pilotos.size() - 1);
				return 0;
			}
		}
	}
	return 1;
}

string Pista::stop(const string nome) {
	ostringstream oss;
	for (Piloto* p : pilotos) {
		if (Utils::minusculas(p->getNome()) == Utils::minusculas(nome)) {
			if (p->getCarro()->isTravao()) {
				oss << "Ja foi dada ordem de paragem ao piloto " << nome << "!";
				return oss.str();
			}
			p->travaAteParar();
			oss << "Ordem de paragem dada ao piloto " << nome << ".";
			return oss.str();
		}
	}
	oss << "O piloto " << nome << " nao esta na pista!";
	return oss.str();
}

int Pista::destroi(const char identificador) {
	for (Piloto* p : pilotos) {
		if (tolower(p->getCarro()->getIdentificacao()) == tolower(identificador)) {
			atualizaPistaAcidente(p->getCarro()->getX(), p->getCarro()->getPosicao());
			p->getCarro()->setX(-1);
			organizaPosicoes();
			p->saiDoCarro();
			pilotosSemCarros.push_back(p);
			remove(pilotos.begin(), pilotos.end(), p);
			pilotos.resize(pilotos.size() - 1);
			return 0;
		}
	}
	return 1;
}

string Pista::getPiloto(const char identificador) {
	for (Piloto* p : pilotos) {
		if(tolower(p->getCarro()->getIdentificacao()) == tolower(identificador))
			return p->getNome();
	}
	return "";
}

vector<vector<char>> Pista::getArrayPistas() const { return pistas; }

void Pista::initPista() {
	for (int i = 0; i < TAM_LINHA_FICH; i++) {
		pistas.push_back(lePista(NOME_FICH_PISTA));
	}
}

void Pista::updatePistas(const char id, int x, int y) {
	for (int i = 0; i != pistas.size(); i++) {
		for (int j = 0; j < getMaxCarros(); j++) {
			if (i == x && j == y) {
				pistas[j][i] = id;
			}
		}
	}
}

void Pista::atualizaPistaAcidente(int x, int y) {
	if (x == 1 || x == 48)
		updatePistas('+', x, y);
	else
		updatePistas('.', x, y);
}

vector<char> Pista::lePista(const string& nome_fich) {
	fstream ficheiro(nome_fich);
	vector<char> pista;
	int i = 0, j = 0;

	if (ficheiro) {
		string frase;
		getline(ficheiro, frase);
		
		while(i != frase.length()) {
			pista.push_back(frase[i]);
			i++;
		}
		ficheiro.close();
	}
	return pista;
}

void Pista::limpaPista() {
	for (int i = 0; i < TAM_LINHA_FICH; i++)
		pistas.pop_back();
}

string Pista::getNomePiloto(int i) { return pilotos[i]->getNome(); }

int Pista::getPosicaoPiloto(const string nome) {
	for (int i = 0; i != pilotos.size(); i++) {
		if (Utils::minusculas(pilotos[i]->getNome()) == Utils::minusculas(nome))
			return i + 1;
	}
	return -1;
}

void Pista::organizaPosicoes() {
	sort(pilotos.begin(), pilotos.end(), [](Piloto* a, Piloto* b) { return a->getCarro()->getX() > b->getCarro()->getX(); });
}

vector<char> Pista::getCarrosEmergencia() const {
	vector<char> identificadoresEmergencia;
	for (Piloto* p : pilotos) {
		if (p->getCarro()->isEmergencia())
			identificadoresEmergencia.push_back(p->getCarro()->getIdentificacao());
	}
	return identificadoresEmergencia;
}

char Pista::getIdCarro(const string nome) const {
	for (Piloto* p : pilotos) {
		if (Utils::minusculas(p->getNome()) == Utils::minusculas(nome))
			return p->getCarro()->getIdentificacao();
	}
	return ' ';
}

void Pista::limpaVetores() {
	carros.clear();
	pilotosSemCarros.clear();
}

string Pista::listaCarros() const {
	ostringstream oss;
	int contador = 0;
	for (Piloto* p : pilotos) {
		oss << " " << p->getCarro()->getIdentificacao() << " " << p->getCarro()->getMarca() << " / " << p->getNome() << " (" << p->getTipo() << ") - " 
			<< p->getCarro()->getEnergia() << "mAh, " << p->getCarro()->getCapacidadeMaxima() << "mAh - " << p->getCarro()->getX() << "m - " 
			<< p->getCarro()->getVelocidade() << "m/s \n";
		contador++;
	}
	if (contador == 0)
		return " Nao ha carros na pista!\n";
	return oss.str();
}

string Pista::getPilotosStr() const {
	ostringstream oss;
	for (Piloto* p : pilotos)
		oss << p->getAsString();
	return oss.str();
}

string Pista::getAsString() const {
	ostringstream oss;

	oss << " Pista: " << "\n\tComprimento: " << getComprimento() << ";\n\tMaximo de carros: " << getMaxCarros() 
		<< ";\n\tPilotos: " << getPilotosStr();

	return oss.str();
}

