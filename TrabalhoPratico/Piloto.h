#ifndef PILOTO_H
#define PILOTO_H

#include "Utils.h"
#include "Carro.h"

class Piloto {
	string nome;					// Nome do piloto (�nico)
	string tipo;					// Tipo do piloto (Crazy Driver || Piloto Rapido || Piloto Surpresa)
	Carro* carro;					// Carro onde se encontra o piloto (nullptr == n�o est� dentro de nenhum carro)
	int pontuacao;					// Pontuacao total do campeonato
	bool pontua;					// True -> pode pontuar, False -> caso contr�rio
	static vector<string> nomes;	// Todos os nomes dos pilotos
	static int contador;			// Vari�vel auxiliar para o nome

	void setNome(string nome);
public:
	// Construtor
	Piloto(const string& nome, const string& tipo);

	// Construtor por c�pia
	Piloto(const Piloto& obj);

	// Destrutor
	virtual ~Piloto();

	// Getters do nome
	string getNome()const;
	// Getter do tipo
	string getTipo()const;
	// Getter do carro
	Carro* getCarro()const;
	// Setter do carro
	void setCarro(Carro* carro);
	// Getter da pontua��o
	int getPontuacao()const;
	// Setter da pontua��o
	void setPontuacao(int pontuacao);
	// Getter da vari�vel pontua
	bool getPontua() const;
	// Setter da vari�vel pontua
	void setPontua(bool pode);

	// Verifica se j� existe o nome inserido
	void verificaNome(const string nome);

	// Alterar o nome do piloto
	void mudaNome(const string nome);

	// Colocar o piloto num carro
	// Retorna uma string com informa��o
	string entraNoCarro(Carro* carro);

	// Indica ao piloto para sair do carro em que se encontra
	void saiDoCarro();

	// Atualiza a posi��o do carro (x e y)
	void atualizaXYCarro(int x, int y);

	// Atualiza o movimento do carro
	void atualizaMovimento(bool movimento);

	// Movimenta o carro
	// Retorna 1 se o carro se est� a mover, 0 se o carro est� parado, retorna -1 se estragou o carro
	virtual int movimenta(int tempo, int posicao, int nCarrosPista) = 0;

	// Acelera o carro X m/s
	// Retorna 1 se estiver em movimento, 0 se n�o estiver em movimento, -1 se ficar sem energia
	int acelera(int velocidade);

	// Trava o carro X m/s
	// Retorna 1 se estiver em movimento, 0 se n�o estiver em movimento, -1 se ficar sem energia
	int trava(int velocidade);

	// Trava at� parar por falta de energia
	void travaAteParar();

	// Danifica o carro
	void danificaCarro(int dano);

	// Ativa o sinal de emerg�ncia
	void ativaEmergencia(bool emergencia);

	// Coloca o piloto na meta
	void vaiMeta(int posicao);

	// Causa um acidente e um dano irrepar�vel ao carro
	// Retorna -1 se causar danos ao piloto anterior, 0 se s� causar dano a ele mesmo
	virtual int acidente() = 0;

	// Redefini�ao do operador atribui��o
	Piloto &operator=(const Piloto& p);

	// GetAsString retorna uma string com a informa��o da classe.
	virtual string getAsString()const;

	// Retorna um novo piloto dependendo da sua classe (fun��o virtual pura)
	virtual Piloto* duplica()const = 0;
};

// Redefini��o da fun��o operator<<
ostream& operator<<(ostream& o, const Piloto& p);

// Redefini��o da fun��o operator+
// Objetivo: tornar o nome �nico
string operator+(const string nome, const int i);

#endif // !PILOTO