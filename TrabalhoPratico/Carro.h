#ifndef CARRO_H
#define CARRO_H

#include "Utils.h"

#define CAPACIDADE_DEFAULT 25			// Capacidade default de um carro
#define VELOCIDADE_DEFAULT 120			// Velocidade default de um carro

class Piloto;

class Carro {
	string marca;						// Marca do carro
	string modelo;						// Modelo do carro
	char identificacao;					// Identificador dos carros (a - z [quando n�o pilotados] || A - Z [quando pilotados] || '?')
	static int contador;				// Vari�vel auxiliar para o identificador
	float energia;						// Energia atual do carro (mAh)
	const float CAPACIDADE_MAXIMA;		// Capacidade m�xima de energia dos carros
	bool movimento;						// True -> est� em movimento || False -> parado
	bool travao;						// True -> est� a travar || False -> caso contr�rio
	const int VELOCIDADE_MAXIMA;		// Velocidade m�xima ating�vel pelo carro
	int velocidade;						// Velocidade atual do carro (m/s)
	bool emergencia;					// True -> Esta ligado || False -> N�o est� ligado
	int danificado;						// 0 -> N�o danificado || 1 -> Irremediavelmente danificado || 2 -> Irrepar�vel
	int posicao;						// Posi��o do carro na pista
	int lugar;							// Lugar do carro na corrida;
	int x;								// Posi��o em x (-1 est� na garagem)
	Piloto* piloto;						// Ponteiro para o piloto que conduz o carro

public:
	// Construtores: 
	// � necess�rio indicar o modelo
	Carro(const string& marca, const string& modelo, float capadicadeInicial, const float capacidadeMaxima, const int velocidadeMaxima);

	// O modelo assume o valor de "Modelo Base" 
	Carro(const string& marca, float capadicadeInicial, const float capacidadeMaxima, const int velocidadeMaxima);

	// Construtor por c�pia
	Carro(const Carro& obj);

	// Destrutor
	~Carro();

	// Getter da marca
	string getMarca()const;
	// Getter do modelo
	string getModelo()const;
	// Getter da identifica��o
	char getIdentificacao()const;
	// Setter da identifica��o
	void setIdentificacao();
	// Getter da energia
	float getEnergia()const;
	// Setter da energia
	void setEnergia(float energia);
	// Getter da capacidade m�xima do carro
	const float getCapacidadeMaxima()const;
	// Getter do movimento
	bool isMovimento()const;
	// Setter do movimento
	void setMovimento(bool movimento);
	// Getter do trav�o
	bool isTravao()const;
	// Setter do trav�o
	void setTravao(bool travao);
	// Getter da velocidade m�xima do carro
	const int getVelocidadeMaxima()const;
	// Getter da velocidade
	int getVelocidade()const;
	// Setter da velocidade
	void setVelocidade(int velocidade);
	// Getter da emerg�ncia
	bool isEmergencia()const;
	// Setter da emerg�ncia
	void setEmergencia(bool emergencia);
	// Getter do dano
	int getDano()const;
	// Setter do dano
	void setDano(int dano);
	// Getter do piloto
	Piloto* getPiloto() const;
	// Setter do piloto
	void setPiloto(Piloto* p);
	// Getter da posi��o
	int getPosicao()const;
	// Setter da posi��o
	void setPosicao(int posicao);
	// Getter do lugar
	int getLugar()const;
	// Setter do lugar
	void setLugar(int lugar);
	// Getter de x
	int getX()const;
	// Setter de x
	void setX(int x);

	 
	// Verifica se a energia inicial indicada est� no intervalo [0; capacidadeM�xima]
	// Retorna a energia inicial a atribuir 
	float verificaEnergiaInicial(float capacidadeInicial, const float capacidadeMaxima);

	// Fun��o para carregar a energia
	// Retorna a uma string com informa��o 
	string carregarEnergia(float energia);

	// Fun��o auxiliar para atualizar as vari�veis piloto e identifica��o
	// Invoca os seus setters
	void atualizaPilotoEIdentificacao(Piloto* p);

	// Acelerar o carro X m/s
	// Retorna 1 se estiver em movimento, 0 se n�o estiver em movimento, -1 se ficar sem energia
	int acelerar(int velocidade);

	// Travar o carro X m/s
	// Retorna 1 se estiver em movimento, 0 se n�o estiver em movimento, -1 se ficar sem energia
	int travar(int velocidade);

	// Trava at� parar por falta de energia
	void travaAteParar();

	// Danifica o carro
	void danificaCarro(int dano);

	// Adicionar um piloto. 
	// Retorna uma string com informa��o
	string adicionaPiloto(Piloto* p);

	// Redefini�ao do operador atribui��o
	Carro &operator=(const Carro& c);

	// Redefini��o do operador menor
	//bool operator<(const Piloto& p)const;

	// GetAsString retorna uma string com toda a informa��o da classe. 
	string getAsString()const;

};

// Redefini��o da fun��o operator<<
ostream& operator<<(ostream& o, const Carro& c);

#endif // !CARRO