#include "Utils.h"

string Utils::minusculas(string comandos) {
	string aux = comandos;
	for (int i = 0; i != aux.size(); i++) {
		if (aux[i] >= 'A' && aux[i] <= 'Z') {
			aux[i] = tolower(aux[i]);
		}
	}
	return aux;
}