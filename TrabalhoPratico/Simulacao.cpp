#include "Simulacao.h"

Simulacao::Simulacao() : DGV(), campeonato(nullptr) { }

Simulacao::~Simulacao() { delete campeonato;  }

DirecaoGeralViacao Simulacao::getDGV() const { return DGV; }

string Simulacao::adicionaPiloto(const string tipo, const string nome) {
	ostringstream oss;
	oss << "O piloto ";
	oss << nome;
	oss << " do tipo " << tipo;
	if (DGV.adicionaPiloto(tipo, nome) == " ") 
		oss << " nao foi adicionado.\n";
	else 
		oss << " foi adicionado com sucesso.\n";
	return oss.str();
}

string Simulacao::removerPiloto(const string& nome) {
	ostringstream oss;
	oss << "O piloto " << nome;
	if (DGV.removePiloto(nome))
		oss << " foi removido com sucesso!\n";
	else
		oss << " nao foi removido!\n";
	return oss.str();
}

string Simulacao::adicionaCarro(const string marca, const string modelo, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima) {
	ostringstream oss;
	oss << " O carro " << DGV.adicionaCarro(marca, modelo, capadicadeInicial, capacidadeMaxima, velocidadeMaxima) << " foi adicionado com sucesso.\n";
	return oss.str();
}

string Simulacao::adicionaCarroSM(const string marca, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima) {
	ostringstream oss;
	oss << " O carro " << DGV.adicionaCarroSM(marca, capadicadeInicial, capacidadeMaxima, velocidadeMaxima) << " foi adicionado com sucesso.\n";
	return oss.str();
}

string Simulacao::removerCarro(const char& identificador) {
	ostringstream oss;
	oss << "O carro " << identificador;
	if (DGV.removeCarro(identificador))
		oss << " foi removido com sucesso!\n";
	else
		oss << " nao foi removido!\n";
	return oss.str();
}

string Simulacao::adicionaAutodromo(const string nome, int maxcarros, int comprimento) {
	ostringstream oss;
	autodromosTotal.push_back(new Autodromo(nome, maxcarros, comprimento));
	oss << "O Autodromo " << nome << " foi adicionado com sucesso!\n";
	return oss.str();
}

string Simulacao::removerAutodromo(const string nome) {
	ostringstream oss;
	oss << "O Autodromo " << nome;
	for (auto ptr = autodromosTotal.begin(); ptr < autodromosTotal.end(); ) {
		if ((*ptr)->getNome() == nome) {
			delete (*ptr);
			ptr = autodromosTotal.erase(ptr);
			oss << " foi removido com sucesso!\n";
			return oss.str();
		}
		else
			*(ptr++);
	}
	oss << " nao existe!\n";
	return oss.str();
}

string Simulacao::entraNoCarro(const char& identificador, const string& nome) {
	return DGV.entraNoCarro(identificador, nome);
}

string Simulacao::saiDoCarro(const char& identificador) {
	return DGV.saiDoCarro(identificador);
}

bool Simulacao::isPilotosEmCarros() {
	return DGV.isPilotosEmCarros();
}

int Simulacao::criaCampeonato(vector<string> autodromos) {
	vector<Autodromo*> autodromoAux;
	int contador = 0;
	ostringstream oss;


	for (int i = 0; i != autodromos.size(); i++) {
		for (int j = 0; j != autodromosTotal.size(); j++) {
			if (Utils::minusculas(autodromos[i]) == Utils::minusculas(autodromosTotal[j]->getNome())) {
				autodromoAux.push_back(autodromosTotal[j]);
				contador++;
			}
		}
	}
	
	if (autodromoAux.size() <= 0)
		return 0;
	
	oss << "Criacao do campeonato com " << contador << " autodromos.\n Lista dos autodromos:";
	for (Autodromo* a : autodromoAux)
		oss << " " << a->getNome() << ";";
	oss << " \n";

	campeonato = new Campeonato(autodromoAux, DGV.getPilotosEmCarros());
	
	logs.push_back(oss.str());

	return 1;
}

string Simulacao::getPosicoes() {
	return campeonato->getPosicoes();
}

string Simulacao::passatempo(int tempo) {
	ostringstream oss;
	updateLogs("Inseriu o comando \"passatempo\"\n");
	oss << campeonato->passatempo(tempo) << "\n";
	updateLogs(oss.str());
	return oss.str();
}

bool Simulacao::tempoValido(int tempo) {
	return campeonato->tempoValido(tempo);
}

bool Simulacao::corridaIniciada() {
	return campeonato->corridaIniciada();
}

string Simulacao::iniciaCorrida() {
	ostringstream oss;
	updateLogs("Inseriu o comando \"corrida\"\n");
	oss << campeonato->iniciaCorrida();
	updateLogs(oss.str());
	return oss.str();
}

string Simulacao::listaCarros() {
	ostringstream oss;
	updateLogs("Inseriu o comando \"listacarros\"\n");
	oss << campeonato->listaCarros();
	updateLogs(oss.str());
	return oss.str();
}

string Simulacao::carregaBateria(const char identificador, float energia) {
	ostringstream oss;
	updateLogs("Inseriu o comando \"carregabateria\"\n");
	oss << campeonato->carregaBateria(identificador, energia);
	updateLogs(oss.str());
	return oss.str();
}

string Simulacao::carregaBaterias() {
	ostringstream oss;
	updateLogs("Inseriu o comando \"carregatudo\"\n");
	oss << campeonato->carregaBaterias();
	updateLogs(oss.str());
	return oss.str();
}

string Simulacao::causaAcidente(const char identificador) {
	ostringstream oss;
	updateLogs("Inseriu o comando \"acidente\"\n");
	string aux = campeonato->getPiloto(identificador);
	int aconteceu = campeonato->causaAcidente(identificador);
	if (aconteceu == -1) {
		updateLogs("Nao pode causar acidentes sem iniciar a corrida!\n");
		return "Nao pode causar acidentes sem iniciar a corrida!\n";
	}
	else if (aconteceu == -2) {
		updateLogs("Nao pode parar um piloto sem ele comecar a corrida!\n");
		return "Nao pode destruir carros sem iniciar a corrida!\n";
	}
	else if (aconteceu == 0) {
		string retorno = removerPiloto(aux);
		oss << "Acidente com o carro " << identificador << ". O piloto " << aux << " morreu.\n";
		oss << " " << campeonato->passatempo(1);
		updateLogs(oss.str());
		return oss.str();
	}
	oss << "Nao existe o carro " << identificador << " na pista.\n";
	updateLogs(oss.str());
	return oss.str();
}

string Simulacao::stop(const string nome) {
	ostringstream oss;
	updateLogs("Inseriu o comando \"stop\"\n");
	oss << campeonato->stop(nome) << " ";
	oss << campeonato->passatempo(1) << " \n";
	updateLogs(oss.str());
	return oss.str();
}


string Simulacao::destroi(const char identificador) {
	ostringstream oss;
	updateLogs("Inseriu o comando \"destroi\"\n");
	string nome = campeonato->getPiloto(identificador);
	int aux = campeonato->destroi(identificador);
	if (aux == -1) {
		updateLogs("Nao pode destruir carros sem iniciar a corrida!\n");
		return "Nao pode destruir carros sem iniciar a corrida!\n";
	}
	else if (aux == -2) {
		updateLogs("Nao pode parar um piloto sem ele comecar a corrida!\n");
		return "Nao pode destruir carros sem iniciar a corrida!\n";
	}
	else if (aux == 0) {
		string retorno = removerCarro(identificador);
		oss << "Destruido o carro " << identificador << ". O piloto " << nome << " ficou apeado.\n";
		oss << " " << campeonato->passatempo(1);
		updateLogs(oss.str());
		return oss.str();
	}
	oss << "Nao existe o carro " << identificador << " na pista.\n";
	updateLogs(oss.str());
	return oss.str();
}

vector<string> Simulacao::getLogs() { 
	updateLogs("Inseriu o comando \"log\"\n");
	return logs;
}

void Simulacao::updateLogs(string log) {
	ostringstream oss;
	string autodromo = campeonato->getAutodromoAtual();
	int tempo = campeonato->getTempo();
	
	oss << " " << autodromo << " - " << tempo << "s - " << log;
	logs.push_back(oss.str());
}

string Simulacao::getPontuacoes() {
	return campeonato->getPontuacoes();
}

void Simulacao::resetCampeonato() {
	for (Autodromo* a : campeonato->getAutodromos()) {
		remove(autodromosTotal.begin(), autodromosTotal.end(), a);
		autodromosTotal.resize(autodromosTotal.size() - 1);
	}
	delete campeonato;
	this->campeonato = nullptr;
	logs.clear();
}

string Simulacao::saveDGV(const string nome) {
	for (int i = 0; i != backups.size(); i++) {
		if (Utils::minusculas(backups[i].getNome()) == Utils::minusculas(nome)) {
			return "Ja existe um save com esse nome!\n";
		}
	}

	DirecaoGeralViacao dgv = DGV;
	dgv.setNome(nome);
	backups.push_back(dgv);
	return "Save efetuado com sucesso!\n";
}

string Simulacao::loadDGV(const string nome) {
	ostringstream oss;
	for (int i = 0; i != backups.size(); i++) {
		if (Utils::minusculas(backups[i].getNome()) == Utils::minusculas(nome)) {
			DGV = backups[i];
			return "Load efetuado com sucesso!\n";
		}
	}
	oss << "Nao existe um save com o nome \"" << nome << "\". \n";
	return oss.str();
}

string Simulacao::deleteDGV(const string nome) {
	ostringstream oss;
	for (int i = 0; i != backups.size(); i++) {
		if (Utils::minusculas(backups[i].getNome()) == Utils::minusculas(nome)) {
			backups.erase(backups.begin() + i);
			return "Eliminado o backup com sucesso!\n";
		}
	}
	oss << "Nao existe o backup com o nome \"" << nome << "\". \n";
	return oss.str();
}

string Simulacao::listaBackups() {
	ostringstream oss;

	if ((int)backups.size() == 0)
		return "Nao existem backups!";

	oss << "Backups: \n";
	for (int i = 0; i != backups.size(); i++)
		oss << " \t" << backups[i].getNome() << "; \n";
	return oss.str();
}

string Simulacao::lePilotos(const string& nome_fich) {
	fstream ficheiro(nome_fich);
	ostringstream oss;

	if (ficheiro) {
		string frase;

		while (getline(ficheiro, frase)) {
			string tipo, nome;
			istringstream iss(frase);

			if (iss >> tipo) {
				iss.ignore();
				if(getline(iss, nome))
					oss << adicionaPiloto(tipo, nome);
			}
		}
		ficheiro.close();
	}
	else
		oss << "Erro ao abrir o ficheiro " << nome_fich << " para leitura!\n";

	return oss.str();
}

string Simulacao::leCarros(const string& nome_fich) {
	fstream ficheiro(nome_fich);
	ostringstream oss;

	if (ficheiro) {
		string frase;

		while (getline(ficheiro, frase)) {
			int velMax;
			float capIni, capMax;
			string marca, modelo;
			istringstream iss(frase);

			if (iss >> velMax && iss >> capIni && iss >> capMax && iss >> marca) {
				iss.ignore();
				if(getline(iss, modelo))
					oss << adicionaCarro(marca, modelo, capIni, capMax, velMax);
				else
					oss << adicionaCarroSM(marca, capIni, capMax, velMax);
			}
		}
		ficheiro.close();
	}
	else
		oss << "Erro ao abrir o ficheiro " << nome_fich << " para leitura!\n";

	return oss.str();
}

string Simulacao::leAutodromos(const string& nome_fich) {
	fstream ficheiro(nome_fich);
	ostringstream oss;

	if (ficheiro) {
		string frase;

		while (getline(ficheiro, frase)) {
			int nCarros, tamPista;
			string nome;
			istringstream iss(frase);

			if (iss >> nCarros && iss >> tamPista && iss >> nome) {
				oss << adicionaAutodromo(nome, nCarros, tamPista);
			}
		}
		ficheiro.close();
	}
	else
		oss << "Erro ao abrir o ficheiro " << nome_fich << " para leitura!\n";

	return oss.str();
}

vector<vector<char>> Simulacao::getArrayPistas() { return campeonato->getArrayPistas(); }

int Simulacao::getMaxCarros() const { return campeonato->getMaxCarros(); }

vector<char> Simulacao::getCarrosEmergencia() const { return campeonato->getCarrosEmergencia(); }

bool Simulacao::podeEscreverALista() const {
	if (DGV.getPilotosSize() > 0 || DGV.getCarrosSize() > 0 || autodromosTotal.size() > 0)
		return true;
	return false;
}

string Simulacao::getNomeAutodromoAtual() const {
	return campeonato->getAutodromoAtual();
}

vector<string> Simulacao::getCarrosGaragemSTR() const {
	return campeonato->getCarrosGaragem();
}

vector<string> Simulacao::getPilotosListaSTR() const {
	return DGV.getPilotosListaSTR();
}

vector<string> Simulacao::getCarrosListaSTR() const {
	return DGV.getCarrosListaSTR();
}

vector<string> Simulacao::getAutodromosListaSTR() const {
	vector<string> autodromosSTR;
	ostringstream oss;

	for (Autodromo* a : autodromosTotal) {
		if (a != nullptr) {
			autodromosSTR.push_back("Nome: " + a->getNome());
			oss << "Pista: " << a->getPista().getComprimento() << "m";
			autodromosSTR.push_back(oss.str());
			oss.str("");
			oss.clear();
			oss << "N" << (char)248 << "Carros: " << a->getMaxCarrosNaPista();
			autodromosSTR.push_back(oss.str());
			autodromosSTR.push_back("BREAK");
			oss.str("");
			oss.clear();
		}
	}
	return autodromosSTR;
}

string Simulacao::getAutodromosStr() const {
	ostringstream oss;
	for (Autodromo* a : autodromosTotal)
		oss << a->getAsString();

	return oss.str();
}

string Simulacao::getAsString() const {
	ostringstream oss;
	oss << DGV;
	if (autodromosTotal.size() > 0)
		oss << "\n" << getAutodromosStr() << "\n";
	else
		oss << "\n" << " Sem autodromos \n";
	return oss.str();
}

ostream& operator<<(ostream& o, const Simulacao& s) {
	o << s.getAsString();
	return o;
}