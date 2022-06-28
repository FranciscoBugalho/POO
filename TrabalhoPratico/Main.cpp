/*
*	F1 Simulator
*	Programação Orientada a Objetos (POO) 2ºAno 1ºSemestre
*
*	Realizado por:
*		Diogo Claro Justo   Nº 2017020070 Turma P6
*		José Francisco de Jesus Bugalho   Nº 2017009414 Turma P3
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