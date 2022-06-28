#ifndef INTERFACE_H
#define INTERFACE_H

#include "Utils.h"
#include "Identificadores.h"

#define X_MAX 150					// Tamanho máximo de linhas da consola
#define Y_MAX 35					// Tamanho máximo de colunas da consola

class Interface {

public:
	// Construtor
	Interface();

	// Destrutor
	~Interface();

	// Função para o início da simulação
	int simular(Simulacao& s);

	// =============================== COMANDOS MODO 1 =============================== 

	// Faz a leitura dos comandos inseridos pelo utilizador
	// Retorna 1 se o comando inserido for campeonato, -1 se o comando for sair, 0 nos restantes casos
	int leComandos_modo1(Simulacao& s);
	
	// Executa os comandos inseridos pelo utilizador
	// Retorna 1 se o comando inserido for campeonato, -1 se o comando for sair, 0 nos restantes casos
	int execComandosM1(Simulacao& s, vector<string> comandos, int nComandos);

	// Desenha a lista extra na interface Carros | Pilotos | Autódromos
	void desenhaLista(Simulacao& s);

	// Mostra a informação necessária dos pilotos
	void mostraPilotos(vector<string> vp);

	// Mostra a informação necessária dos carros
	void mostraCarros(vector<string> vc);

	// Mostra a informação necessária dos autódromos
	void mostraAutodromos(vector<string> va);

	// Limpa informação a mais do ecrã (zona dos pilotos)
	void limpaPilotos(int l);

	// Limpa informação a mais do ecrã (zona dos carros)
	void limpaCarros(int l);

	// Limpa informação a mais do ecrã (zona dos autodromos)
	void limpaAutodromos(int l);

	// Imprime a borda com asteriscos ('*')
	void imprimeBorda();

	// Imprime o título da simulação "F1 Simulator"
	void imprimeTituloPrincipal();

	// Imprime o título do modo 1 "Modo 1 - Preparação"
	void imprimeTituloModo1();

	// Limpa os carateres introduzidos pelo utilizador
	void limpaEscritaM1();

	// Limpa a informação (linha a baixo de "Comandos: ") 
	void limpaInformacaoM1();

	// ===============================================================================


	// =============================== COMANDOS MODO 2 =============================== 

	// Fz leitura dos comandos inseridos pelo utilzador para o modo 2.
	int leComandos_modo2(Simulacao& s);

	// Executa os comandos executados pelo utilzador para o modo 2
	int execComandosM2(Simulacao& s, vector<string> comandos, int nArgs);

	// Imprime o nome do autódromo atual
	void imprimeAutodromo(const string nome);

	// Imprime o título do modo 2 "Modo 2 - Campeonato"
	void imprimeTituloModo2();

	// Imprime as posições dos pilotos
	void imprimePosicoes(string posicoes);

	// Imprime as pistas e os carros no ecrã (com/sem sinal de emergência ativo)
	void imprimePistas(vector<vector<char>> pista, int maxcarros, vector<char> carrosEmergencia);

	// Imprime os logs na interface
	string imprimeLogs(vector<string> logs);

	// Imprime os carros na garagem
	void imprimeGaragem(vector<string> carros);

	// Imprime o titulo "Garagem"
	void imprimeTituloGaragem();

	// Limpa informação a mais do ecrã (zona da garagem)
	void limpaGaragem(int l);

	// Desenha uma linha reta no ecrã
	void desenhaLinha();

	// Limpa os carateres introduzidos pelo utilizador	
	void limpaEscritaM2();

	// Limpa a pista do ecrã
	void limpaPista();

	// Limpa a informação (linha a baixo de "Comandos: ") 
	void limpaInformacaoM2();

	// ===============================================================================

	// Imprime o menu inicial da simulação
	// Retorna true se precionar ENTER e false se precionar ESC
	bool mainMenu();

	// Termina o programa após ser inserido o comando "sair"
	int terminaPrograma();

	// Imprime o menu de informações
	void imprimeInformacoes();

	// Limpa o buffer de entrada (stdin)
	void limpa_buffer();

	// Verifica se a conversão de string para int é possível
	bool testaExcecoesSTOI(string valor);

	// Verifica se a conversão de string para float é possível
	bool testaExcecoesSTOF(string valor);
};

#endif // !INTERFACE