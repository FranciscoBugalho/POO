#ifndef PILOTO_H
#define PILOTO_H

#include "Utils.h"
#include "Carro.h"

class Piloto {
	string nome;					// Nome do piloto (único)
	string tipo;					// Tipo do piloto (Crazy Driver || Piloto Rapido || Piloto Surpresa)
	Carro* carro;					// Carro onde se encontra o piloto (nullptr == não está dentro de nenhum carro)
	int pontuacao;					// Pontuacao total do campeonato
	bool pontua;					// True -> pode pontuar, False -> caso contrário
	static vector<string> nomes;	// Todos os nomes dos pilotos
	static int contador;			// Variável auxiliar para o nome

	void setNome(string nome);
public:
	// Construtor
	Piloto(const string& nome, const string& tipo);

	// Construtor por cópia
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
	// Getter da pontuação
	int getPontuacao()const;
	// Setter da pontuação
	void setPontuacao(int pontuacao);
	// Getter da variável pontua
	bool getPontua() const;
	// Setter da variável pontua
	void setPontua(bool pode);

	// Verifica se já existe o nome inserido
	void verificaNome(const string nome);

	// Alterar o nome do piloto
	void mudaNome(const string nome);

	// Colocar o piloto num carro
	// Retorna uma string com informação
	string entraNoCarro(Carro* carro);

	// Indica ao piloto para sair do carro em que se encontra
	void saiDoCarro();

	// Atualiza a posição do carro (x e y)
	void atualizaXYCarro(int x, int y);

	// Atualiza o movimento do carro
	void atualizaMovimento(bool movimento);

	// Movimenta o carro
	// Retorna 1 se o carro se está a mover, 0 se o carro está parado, retorna -1 se estragou o carro
	virtual int movimenta(int tempo, int posicao, int nCarrosPista) = 0;

	// Acelera o carro X m/s
	// Retorna 1 se estiver em movimento, 0 se não estiver em movimento, -1 se ficar sem energia
	int acelera(int velocidade);

	// Trava o carro X m/s
	// Retorna 1 se estiver em movimento, 0 se não estiver em movimento, -1 se ficar sem energia
	int trava(int velocidade);

	// Trava até parar por falta de energia
	void travaAteParar();

	// Danifica o carro
	void danificaCarro(int dano);

	// Ativa o sinal de emergência
	void ativaEmergencia(bool emergencia);

	// Coloca o piloto na meta
	void vaiMeta(int posicao);

	// Causa um acidente e um dano irreparável ao carro
	// Retorna -1 se causar danos ao piloto anterior, 0 se só causar dano a ele mesmo
	virtual int acidente() = 0;

	// Redefiniçao do operador atribuição
	Piloto &operator=(const Piloto& p);

	// GetAsString retorna uma string com a informação da classe.
	virtual string getAsString()const;

	// Retorna um novo piloto dependendo da sua classe (função virtual pura)
	virtual Piloto* duplica()const = 0;
};

// Redefinição da função operator<<
ostream& operator<<(ostream& o, const Piloto& p);

// Redefinição da função operator+
// Objetivo: tornar o nome único
string operator+(const string nome, const int i);

#endif // !PILOTO