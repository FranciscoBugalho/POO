#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "Utils.h"
#include "DirecaoGeralViacao.h"
#include "Campeonato.h"

class Simulacao {
	DirecaoGeralViacao DGV;					// Direção Geral de Viação [contém os pilotos e os carros]
	vector<DirecaoGeralViacao> backups;		// Backups da Direção Geral de Viação
	Campeonato* campeonato;					// Campeonato
	vector<Autodromo*> autodromosTotal;		// Vetor de autódromos
	vector<string> logs;					// Vetor de strings para guardar os logs

public:
	// Construtor sem parâmetros
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

	// Adiciona um autódromo
	string adicionaAutodromo(const string nome, int maxcarros, int comprimento);

	// Remover um autodromo
	string removerAutodromo(const string nome);

	// Colocar um piloto no carro
	string entraNoCarro(const char& identificador, const string& nome);

	// Tirar do carro o piloto
	string saiDoCarro(const char& identificador);

	// Verifica se existem pelo menos dois pilotos nos carros
	// Retorna TRUE - se existirem 2 ou mais; FALSE - caso contrário
	bool isPilotosEmCarros();

	// Cria um campeonato com os autódromos recebidos
	// Retorna 1 se o campeonato for criado, -1 - caso contrário
	int criaCampeonato(vector<string> autodromos);

	// Obtém a string de posicoes no campeonato
	string getPosicoes();

	// Passa X tempo
	string passatempo(int tempo);

	// Verifica se o tempo para passar é válido
	// Retorna True - válido || False - inválido
	bool tempoValido(int tempo);

	// Verifica se a corrida já foi iniciada
	bool corridaIniciada();

	// Inicia a próxima corrida
	string iniciaCorrida();

	// Mostra informação relativa aos carros
	string listaCarros();

	// Carrega a bateria do carro indicado
	string carregaBateria(const char identificador, float energia);

	// Carrega todas as baterias
	string carregaBaterias();

	// Causa um acidente, se ocorre o acidente mata/apaga o piloto
	string causaAcidente(const char identificador);

	// Dá ordem de paragem ao piloto indicado
	string stop(const string nome);

	// Destrói o carro indicado
	string destroi(const char identificador);

	// Getter da variável logs
	vector<string> getLogs();

	// Atualiza a variável logs
	void updateLogs(string log);

	// Obtém a classificação no final do campeonato
	string getPontuacoes();

	// Reseta o campeonato
	void resetCampeonato();

	// Save da Direção Geral de Viação com o nome indicado
	string saveDGV(const string nome);

	// Load da Direção Geral de Viação com o nome indicado
	string loadDGV(const string nome);

	// Apaga o backup com o nome indicado
	string deleteDGV(const string nome);

	// Lista todos os backups existentes
	string listaBackups();

	// Lê um vetor de pilotos dado o nome do ficheiro
	string lePilotos(const string& nome_fich);

	// Lê um vetor de carros dado o nome do ficheiro
	string leCarros(const string& nome_fich);

	// Lê um autodromo dado o nome do ficheiro
	string leAutodromos(const string& nome_fich);

	// Obtém o vetor das pistas para imprimir no ecrã
	vector<vector<char>> getArrayPistas();

	// Obtém o máximo de carros
	int getMaxCarros()const;

	// Obtém os identificadores dos carros com o sinal de emergência ativo
	vector<char> getCarrosEmergencia() const;

	// Verifica se o vetor de carros, pilotos e autódromos tem informação
	// Retorna TRUE se pelo menos um tiver informação, FALSE caso contrário
	bool podeEscreverALista() const;

	// Obtém o nome do autódromo onde está a decorrer a corrida
	string getNomeAutodromoAtual() const;

	// Obtém um vetor com informação dos carros na garagem
	vector<string> getCarrosGaragemSTR() const;

	// Obtem a informação necessária dos pilotos para aprensentar no ecrã
	vector<string> getPilotosListaSTR() const;

	// Obtem a informação necessária dos carros para aprensentar no ecrã
	vector<string> getCarrosListaSTR() const;

	// Obtem a informação necessária dos autodromos para aprensentar no ecrã
	vector<string> getAutodromosListaSTR() const;

	// Função auxiliar para obter informção dos autódromos
	string getAutodromosStr() const;
	
	// GetAsString retorna uma string com a informação da classe.
	string getAsString()const;

};

// Redefinição da função operator<<
ostream& operator<<(ostream& o, const Simulacao& s);

#endif // !SIMULACAO