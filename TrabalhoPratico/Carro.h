#ifndef CARRO_H
#define CARRO_H

#include "Utils.h"

#define CAPACIDADE_DEFAULT 25			// Capacidade default de um carro
#define VELOCIDADE_DEFAULT 120			// Velocidade default de um carro

class Piloto;

class Carro {
	string marca;						// Marca do carro
	string modelo;						// Modelo do carro
	char identificacao;					// Identificador dos carros (a - z [quando não pilotados] || A - Z [quando pilotados] || '?')
	static int contador;				// Variável auxiliar para o identificador
	float energia;						// Energia atual do carro (mAh)
	const float CAPACIDADE_MAXIMA;		// Capacidade máxima de energia dos carros
	bool movimento;						// True -> está em movimento || False -> parado
	bool travao;						// True -> está a travar || False -> caso contrário
	const int VELOCIDADE_MAXIMA;		// Velocidade máxima atingível pelo carro
	int velocidade;						// Velocidade atual do carro (m/s)
	bool emergencia;					// True -> Esta ligado || False -> Não está ligado
	int danificado;						// 0 -> Não danificado || 1 -> Irremediavelmente danificado || 2 -> Irreparável
	int posicao;						// Posição do carro na pista
	int lugar;							// Lugar do carro na corrida;
	int x;								// Posição em x (-1 está na garagem)
	Piloto* piloto;						// Ponteiro para o piloto que conduz o carro

public:
	// Construtores: 
	// É necessário indicar o modelo
	Carro(const string& marca, const string& modelo, float capadicadeInicial, const float capacidadeMaxima, const int velocidadeMaxima);

	// O modelo assume o valor de "Modelo Base" 
	Carro(const string& marca, float capadicadeInicial, const float capacidadeMaxima, const int velocidadeMaxima);

	// Construtor por cópia
	Carro(const Carro& obj);

	// Destrutor
	~Carro();

	// Getter da marca
	string getMarca()const;
	// Getter do modelo
	string getModelo()const;
	// Getter da identificação
	char getIdentificacao()const;
	// Setter da identificação
	void setIdentificacao();
	// Getter da energia
	float getEnergia()const;
	// Setter da energia
	void setEnergia(float energia);
	// Getter da capacidade máxima do carro
	const float getCapacidadeMaxima()const;
	// Getter do movimento
	bool isMovimento()const;
	// Setter do movimento
	void setMovimento(bool movimento);
	// Getter do travão
	bool isTravao()const;
	// Setter do travão
	void setTravao(bool travao);
	// Getter da velocidade máxima do carro
	const int getVelocidadeMaxima()const;
	// Getter da velocidade
	int getVelocidade()const;
	// Setter da velocidade
	void setVelocidade(int velocidade);
	// Getter da emergência
	bool isEmergencia()const;
	// Setter da emergência
	void setEmergencia(bool emergencia);
	// Getter do dano
	int getDano()const;
	// Setter do dano
	void setDano(int dano);
	// Getter do piloto
	Piloto* getPiloto() const;
	// Setter do piloto
	void setPiloto(Piloto* p);
	// Getter da posição
	int getPosicao()const;
	// Setter da posição
	void setPosicao(int posicao);
	// Getter do lugar
	int getLugar()const;
	// Setter do lugar
	void setLugar(int lugar);
	// Getter de x
	int getX()const;
	// Setter de x
	void setX(int x);

	 
	// Verifica se a energia inicial indicada está no intervalo [0; capacidadeMáxima]
	// Retorna a energia inicial a atribuir 
	float verificaEnergiaInicial(float capacidadeInicial, const float capacidadeMaxima);

	// Função para carregar a energia
	// Retorna a uma string com informação 
	string carregarEnergia(float energia);

	// Função auxiliar para atualizar as variáveis piloto e identificação
	// Invoca os seus setters
	void atualizaPilotoEIdentificacao(Piloto* p);

	// Acelerar o carro X m/s
	// Retorna 1 se estiver em movimento, 0 se não estiver em movimento, -1 se ficar sem energia
	int acelerar(int velocidade);

	// Travar o carro X m/s
	// Retorna 1 se estiver em movimento, 0 se não estiver em movimento, -1 se ficar sem energia
	int travar(int velocidade);

	// Trava até parar por falta de energia
	void travaAteParar();

	// Danifica o carro
	void danificaCarro(int dano);

	// Adicionar um piloto. 
	// Retorna uma string com informação
	string adicionaPiloto(Piloto* p);

	// Redefiniçao do operador atribuição
	Carro &operator=(const Carro& c);

	// Redefinição do operador menor
	//bool operator<(const Piloto& p)const;

	// GetAsString retorna uma string com toda a informação da classe. 
	string getAsString()const;

};

// Redefinição da função operator<<
ostream& operator<<(ostream& o, const Carro& c);

#endif // !CARRO