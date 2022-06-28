#ifndef INTERFACE_H
#define INTERFACE_H

#include "Utils.h"
#include "Identificadores.h"

#define X_MAX 150					// Tamanho m�ximo de linhas da consola
#define Y_MAX 35					// Tamanho m�ximo de colunas da consola

class Interface {

public:
	// Construtor
	Interface();

	// Destrutor
	~Interface();

	// Fun��o para o in�cio da simula��o
	int simular(Simulacao& s);

	// =============================== COMANDOS MODO 1 =============================== 

	// Faz a leitura dos comandos inseridos pelo utilizador
	// Retorna 1 se o comando inserido for campeonato, -1 se o comando for sair, 0 nos restantes casos
	int leComandos_modo1(Simulacao& s);
	
	// Executa os comandos inseridos pelo utilizador
	// Retorna 1 se o comando inserido for campeonato, -1 se o comando for sair, 0 nos restantes casos
	int execComandosM1(Simulacao& s, vector<string> comandos, int nComandos);

	// Desenha a lista extra na interface Carros | Pilotos | Aut�dromos
	void desenhaLista(Simulacao& s);

	// Mostra a informa��o necess�ria dos pilotos
	void mostraPilotos(vector<string> vp);

	// Mostra a informa��o necess�ria dos carros
	void mostraCarros(vector<string> vc);

	// Mostra a informa��o necess�ria dos aut�dromos
	void mostraAutodromos(vector<string> va);

	// Limpa informa��o a mais do ecr� (zona dos pilotos)
	void limpaPilotos(int l);

	// Limpa informa��o a mais do ecr� (zona dos carros)
	void limpaCarros(int l);

	// Limpa informa��o a mais do ecr� (zona dos autodromos)
	void limpaAutodromos(int l);

	// Imprime a borda com asteriscos ('*')
	void imprimeBorda();

	// Imprime o t�tulo da simula��o "F1 Simulator"
	void imprimeTituloPrincipal();

	// Imprime o t�tulo do modo 1 "Modo 1 - Prepara��o"
	void imprimeTituloModo1();

	// Limpa os carateres introduzidos pelo utilizador
	void limpaEscritaM1();

	// Limpa a informa��o (linha a baixo de "Comandos: ") 
	void limpaInformacaoM1();

	// ===============================================================================


	// =============================== COMANDOS MODO 2 =============================== 

	// Fz leitura dos comandos inseridos pelo utilzador para o modo 2.
	int leComandos_modo2(Simulacao& s);

	// Executa os comandos executados pelo utilzador para o modo 2
	int execComandosM2(Simulacao& s, vector<string> comandos, int nArgs);

	// Imprime o nome do aut�dromo atual
	void imprimeAutodromo(const string nome);

	// Imprime o t�tulo do modo 2 "Modo 2 - Campeonato"
	void imprimeTituloModo2();

	// Imprime as posi��es dos pilotos
	void imprimePosicoes(string posicoes);

	// Imprime as pistas e os carros no ecr� (com/sem sinal de emerg�ncia ativo)
	void imprimePistas(vector<vector<char>> pista, int maxcarros, vector<char> carrosEmergencia);

	// Imprime os logs na interface
	string imprimeLogs(vector<string> logs);

	// Imprime os carros na garagem
	void imprimeGaragem(vector<string> carros);

	// Imprime o titulo "Garagem"
	void imprimeTituloGaragem();

	// Limpa informa��o a mais do ecr� (zona da garagem)
	void limpaGaragem(int l);

	// Desenha uma linha reta no ecr�
	void desenhaLinha();

	// Limpa os carateres introduzidos pelo utilizador	
	void limpaEscritaM2();

	// Limpa a pista do ecr�
	void limpaPista();

	// Limpa a informa��o (linha a baixo de "Comandos: ") 
	void limpaInformacaoM2();

	// ===============================================================================

	// Imprime o menu inicial da simula��o
	// Retorna true se precionar ENTER e false se precionar ESC
	bool mainMenu();

	// Termina o programa ap�s ser inserido o comando "sair"
	int terminaPrograma();

	// Imprime o menu de informa��es
	void imprimeInformacoes();

	// Limpa o buffer de entrada (stdin)
	void limpa_buffer();

	// Verifica se a convers�o de string para int � poss�vel
	bool testaExcecoesSTOI(string valor);

	// Verifica se a convers�o de string para float � poss�vel
	bool testaExcecoesSTOF(string valor);
};

#endif // !INTERFACE