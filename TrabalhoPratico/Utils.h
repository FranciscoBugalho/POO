#ifndef UTILS_H
#define UTILS_H

// Ponto h com includes de bibliotecas standads
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>

// Namespace
using namespace std;

class Utils {

public:
	// Fun��o para garantir que o comando, se certo, � lido independentemente da forma como o utilizador o introduz
	// Retorna o comando em min�sculas
	static string minusculas(string comandos);
};


#endif // !UTILS