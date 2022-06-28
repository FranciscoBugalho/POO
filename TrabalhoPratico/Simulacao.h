#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "Utils.h"
#include "DirecaoGeralViacao.h"
#include "Campeonato.h"

class Simulacao {
	DirecaoGeralViacao DGV;					// Dire��o Geral de Via��o [cont�m os pilotos e os carros]
	vector<DirecaoGeralViacao> backups;		// Backups da Dire��o Geral de Via��o
	Campeonato* campeonato;					// Campeonato
	vector<Autodromo*> autodromosTotal;		// Vetor de aut�dromos
	vector<string> logs;					// Vetor de strings para guardar os logs

public:
	// Construtor sem par�metros
	Simulacao();

	// Destrutor
	~Simulacao();

	// Getter da DirecaoGeralViacao
	DirecaoGeralViacao getDGV()const;

	// Adicionar um piloto
	string adicionaPiloto(const string tipo, const string nome);

	// Remover um piloto
	string removerPiloto(const string& nome);

	// Adicionar um carro (dado modelo)
	string adicionaCarro(const string marca, const string modelo, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima);

	// Adicionar um carro (sem modelo)
	string adicionaCarroSM(const string marca, float capadicadeInicial, float capacidadeMaxima, int velocidadeMaxima);

	// Remover um carro
	string removerCarro(const char& identificador);

	// Adiciona um aut�dromo
	string adicionaAutodromo(const string nome, int maxcarros, int comprimento);

	// Remover um autodromo
	string removerAutodromo(const string nome);

	// Colocar um piloto no carro
	string entraNoCarro(const char& identificador, const string& nome);

	// Tirar do carro o piloto
	string saiDoCarro(const char& identificador);

	// Verifica se existem pelo menos dois pilotos nos carros
	// Retorna TRUE - se existirem 2 ou mais; FALSE - caso contr�rio
	bool isPilotosEmCarros();

	// Cria um campeonato com os aut�dromos recebidos
	// Retorna 1 se o campeonato for criado, -1 - caso contr�rio
	int criaCampeonato(vector<string> autodromos);

	// Obt�m a string de posicoes no campeonato
	string getPosicoes();

	// Passa X tempo
	string passatempo(int tempo);

	// Verifica se o tempo para passar � v�lido
	// Retorna True - v�lido || False - inv�lido
	bool tempoValido(int tempo);

	// Verifica se a corrida j� foi iniciada
	bool corridaIniciada();

	// Inicia a pr�xima corrida
	string iniciaCorrida();

	// Mostra informa��o relativa aos carros
	string listaCarros();

	// Carrega a bateria do carro indicado
	string carregaBateria(const char identificador, float energia);

	// Carrega todas as baterias
	string carregaBaterias();

	// Causa um acidente, se ocorre o acidente mata/apaga o piloto
	string causaAcidente(const char identificador);

	// D� ordem de paragem ao piloto indicado
	string stop(const string nome);

	// Destr�i o carro indicado
	string destroi(const char identificador);

	// Getter da vari�vel logs
	vector<string> getLogs();

	// Atualiza a vari�vel logs
	void updateLogs(string log);

	// Obt�m a classifica��o no final do campeonato
	string getPontuacoes();

	// Reseta o campeonato
	void resetCampeonato();

	// Save da Dire��o Geral de Via��o com o nome indicado
	string saveDGV(const string nome);

	// Load da Dire��o Geral de Via��o com o nome indicado
	string loadDGV(const string nome);

	// Apaga o backup com o nome indicado
	string deleteDGV(const string nome);

	// Lista todos os backups existentes
	string listaBackups();

	// L� um vetor de pilotos dado o nome do ficheiro
	string lePilotos(const string& nome_fich);

	// L� um vetor de carros dado o nome do ficheiro
	string leCarros(const string& nome_fich);

	// L� um autodromo dado o nome do ficheiro
	string leAutodromos(const string& nome_fich);

	// Obt�m o vetor das pistas para imprimir no ecr�
	vector<vector<char>> getArrayPistas();

	// Obt�m o m�ximo de carros
	int getMaxCarros()const;

	// Obt�m os identificadores dos carros com o sinal de emerg�ncia ativo
	vector<char> getCarrosEmergencia() const;

	// Verifica se o vetor de carros, pilotos e aut�dromos tem informa��o
	// Retorna TRUE se pelo menos um tiver informa��o, FALSE caso contr�rio
	bool podeEscreverALista() const;

	// Obt�m o nome do aut�dromo onde est� a decorrer a corrida
	string getNomeAutodromoAtual() const;

	// Obt�m um vetor com informa��o dos carros na garagem
	vector<string> getCarrosGaragemSTR() const;

	// Obtem a informa��o necess�ria dos pilotos para aprensentar no ecr�
	vector<string> getPilotosListaSTR() const;

	// Obtem a informa��o necess�ria dos carros para aprensentar no ecr�
	vector<string> getCarrosListaSTR() const;

	// Obtem a informa��o necess�ria dos autodromos para aprensentar no ecr�
	vector<string> getAutodromosListaSTR() const;

	// Fun��o auxiliar para obter inform��o dos aut�dromos
	string getAutodromosStr() const;
	
	// GetAsString retorna uma string com a informa��o da classe.
	string getAsString()const;

};

// Redefini��o da fun��o operator<<
ostream& operator<<(ostream& o, const Simulacao& s);

#endif // !SIMULACAO