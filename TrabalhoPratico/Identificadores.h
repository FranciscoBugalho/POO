#ifndef IDENTIFICADORES_H
#define IDENTIFICADORES_H

#include "Utils.h"

// ================================ Comandos do Modo 1 ================================ 

#define NOME_FICH_PILOTOS	 "pilotos.txt"			// Nome do ficheiro dos pilotos
#define NOME_FICH_CARROS	 "carros.txt"			// Nome do ficheiro dos carros
#define NOME_FICH_AUTODROMOS "autodromos.txt"		// Nome do ficheiro dos autódromos

#define CMD_CARREGAP "carregap"		// Comando para carregar pilotos de um ficheiro
#define CMD_CARREGAC "carregac"		// Comando para carregar carros de um ficheiro
#define CMD_CARREGAA "carregaa"		// Comando para carregar autódromos de um ficheiro

#define CMD_CRIA	"cria"			// Comando para criar um piloto / carro / autódromo
#define CMD_APAGA	"apaga"			// Comando para apagar um piloto / carro / autódromo

#define CMD_ENTRANOCARRO "entranocarro"	// Comando que indica a um piloto para entrar num determinado carro
#define CMD_SAIDOCARRO	 "saidocarro"	// Comando que retira o piloto do carro indicado (caso esse carro esteja a ser pilotado)

#define CMD_LISTA "lista"			// Comando para listar a informação relativa a pilotos, carros e autódromos

#define CMD_SAVEDGV "savedgv"		// Comando para guardar uma DGV em memória
#define CMD_LOADDGV "loaddgv"		// Comando para carregar uma DGV da memória
#define CMD_DELDGV  "deldgv"		// Comando para apagar uma DVG da memória

#define CMD_LISTABACKUPS "listabackups"	// Comando para mostrar os backups

#define CMD_CAMPEONATO "campeonato" // Comando para iniciar um campeonato

#define CMD_AJUDA "ajuda"			// Comando ajuda - mostra os comandos e os seus argumentos

// ====================================================================================

// ================================ Comandos do Modo 2 ================================ 

#define CMD_LISTACARROS "listacarros"	// Comando para listar a informação relativa aos carros no campeonato

#define CMD_CARREGABAT "carregabat"		// Comando para carregar a bateria em X do carro indicado

#define CMD_CARREGATUDO "carregatudo"	// Comando para carregar TODA a energia dos carros

#define CMD_CORRIDA "corrida"			// Comando para dar início a uma corrida

#define CMD_ACIDENTE "acidente"			// Comando para causar um acidente a um determinado carro

#define CMD_STOP "stop"					// Comando para parar um determinado carro

#define CMD_DESTROI "destroi"			// Comando para destruir um carro

#define CMD_PASSATEMPO "passatempo"		// Comando para passar o tempo (em segundos)

#define CMD_LOG "log"					// Comando para ver os logs de uma corrida

#define CMD_PONTUACAO "pontuacao"		// Comando para ver a pontuação no final do campeonato

#define CMD_MODO1 "modo1"				// Comando para voltar ao modo 1

// ====================================================================================

// ---------------------------- Defines comuns ----------------------------------------

#define CHAR_PILOTO			"p"			// Carater identificador de um piloto
#define CHAR_CRAZYDRIVER	"crazy"		// Carater referente a um piloto do tipo Crazy Driver
#define CHAR_PILOTORAPIDO	"rapido"	// Carater referente a um piloto do tipo Piloto Rápido
#define CHAR_PILOTOSURPRESA "surpresa"	// Carater referente a um piloto do tipo Piloto Surpresa
#define CHAR_CARRO			"c"			// Carater identificador a um carro
#define CHAR_AUTODROMO		"a"			// Carater identificador a um autódromo

#define CMD_SAIR "sair"				// Comando sair - sai do modo

#endif // !IDENTIFICADORES