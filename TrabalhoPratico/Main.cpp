/*
*	F1 Simulator
*	Programa��o Orientada a Objetos (POO) 2�Ano 1�Semestre
*
*	Realizado por:
*		Diogo Claro Justo   N� 2017020070 Turma P6
*		Jos� Francisco de Jesus Bugalho   N� 2017009414 Turma P3
*/


#include "Utils.h"
#include "Simulacao.h"
#include "Interface.h"

int main() {
	Simulacao simulacao;
	Interface interface;

	srand((int)time(NULL));

	interface.simular(simulacao);

	return 0;
}