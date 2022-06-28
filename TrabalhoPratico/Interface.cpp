#include "Simulacao.h"
#include "Interface.h"
#include "Consola.h"

Interface::Interface() { }

Interface::~Interface() { }

int Interface::simular(Simulacao& s) {
	int valor = 0;

	if (!mainMenu()) {
		Consola::gotoxy(0, Y_MAX - 6);
		return -1;
	}

	Consola::clrscr();

	do {
		while (valor == 0) {
			valor = leComandos_modo1(s);
		}

		if (valor == 1) { // Campeonato
			valor = leComandos_modo2(s);
		}
	} while (valor != -1);

	if (valor == -1)
		return terminaPrograma();

	return 0;
}

int Interface::execComandosM2(Simulacao& s, vector<string> comandos, int nArgs) {

	for (unsigned int i = 0; i < comandos.size(); i++) {
		comandos[i] = Utils::minusculas(comandos[i]);
	}

	if (comandos[0] == CMD_LISTACARROS) {
		if (nArgs == 1) {
			limpaInformacaoM2();
			cout << s.listaCarros();
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_CARREGABAT) {
		if (nArgs == 3) {
			limpaInformacaoM2();
			if (testaExcecoesSTOF(comandos[2])) {
				limpaInformacaoM2();
				cout << s.carregaBateria(comandos[1][0], stof(comandos[2]));
				limpaEscritaM2();
			}
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_CARREGATUDO) {
		if (nArgs == 1) {
			limpaInformacaoM2();
			cout << s.carregaBaterias();
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_CORRIDA) {
		if (nArgs == 1) {
			if (!s.corridaIniciada()) {
				limpaPista();
				limpaInformacaoM2();
				cout << s.iniciaCorrida();
				limpaEscritaM2();
			}
			else {
				limpaInformacaoM2();
				Consola::gotoxy(1, 23);
				cout << "So pode executar este comando quando a corrida em curso terminar!";
				limpaEscritaM2();
			}
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_ACIDENTE) {
		if (nArgs == 2) {
			limpaInformacaoM2();
			cout << s.causaAcidente(comandos[1][0]);
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_STOP) {
		if (nArgs == 2) {
			limpaInformacaoM2();
			cout << s.stop(comandos[1]);
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_DESTROI) {
		if (nArgs == 2) {
			limpaInformacaoM2();
			cout << s.destroi(comandos[1][0]);
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_PASSATEMPO) {
		if (nArgs == 2) {
			limpaInformacaoM2();
			if (s.corridaIniciada()) {
				if (testaExcecoesSTOI(comandos[1])) {
					if (!s.tempoValido(stoi(comandos[1]))) {
						limpaInformacaoM2();
						cout << "Tempo invalido";
						Consola::gotoxy(10, 22);
						limpaEscritaM2();
						return 1;
					}
					for (int i = 0; i < stoi(comandos[1]); i++) {
						int controlo = 0;
						do {
							switch (Consola::getch()) {
							case Consola::ENTER:
								cout << s.passatempo(1);
								imprimePistas(s.getArrayPistas(), s.getMaxCarros(), s.getCarrosEmergencia());
								Consola::gotoxy(1, 23);
								controlo = 1;
								break;
							default:
								controlo = 0;
								break;

							}
						} while (controlo == 0);
					}
				}
			}
			else {
				limpaInformacaoM2();
				cout << "Tem de iniciar a corrida primeiro!";
				Consola::gotoxy(10, 22);
				limpaEscritaM2();
			}
			Consola::gotoxy(10, 22);
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_LOG) {
		if (nArgs == 1) {
			limpaInformacaoM2();
			cout << imprimeLogs(s.getLogs());
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_PONTUACAO) {
		if (nArgs == 1) {
			limpaInformacaoM2();
			cout << s.getPontuacoes();
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_MODO1) {
		if (nArgs == 1) {
			limpaInformacaoM2();
			cout << " A voltar para o modo 1!\n";
			s.resetCampeonato();
			Consola::clrscr();
			limpaEscritaM2();
			return 0;
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_AJUDA) {
		if (nArgs == 1) {
			limpaInformacaoM2();
			cout << "listacarros" << endl << " carregabat <letracarro> <Q mAh>" << endl << " carregatudo" << endl << " corrida" << endl
				<< " acidente <letracarro>" << endl << " stop <nomePiloto>" << endl << " destroi <letracarro>" << endl << " passatempo <T segundos>" << endl
				<< " log" << endl << " pontuacao" << endl << " modo1" << endl << " ajuda" << endl << " sair";
			limpaEscritaM2();
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else if (comandos[0] == CMD_SAIR) {
		if (nArgs == 1) {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "A sair";
			limpaEscritaM2();
			return -1;
		}
		else {
			limpaInformacaoM2();
			Consola::gotoxy(1, 23);
			cout << "Numero de argumentos invalido!";
			limpaEscritaM2();
		}
	}
	else {
		limpaInformacaoM2();
		Consola::gotoxy(1, 23);
		cout << "O comando \"" << comandos[0] << "\" nao existe!";
		limpaEscritaM2();
	}
	return 1;
}

int Interface::execComandosM1(Simulacao& s, vector<string> comandos, int nArgs) {

	for (unsigned int i = 0; i < comandos.size(); i++) {
		comandos[i] = Utils::minusculas(comandos[i]);
	}

	if (comandos[0] == CMD_CARREGAP) {
		if (nArgs == 2) {
			if (comandos[1] == NOME_FICH_PILOTOS) {
				limpaInformacaoM1();
				cout << s.lePilotos(NOME_FICH_PILOTOS);
				desenhaLista(s);
				limpaEscritaM1();
			}
			else {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << "Nome do ficheiro invalido (p.e.: " << NOME_FICH_PILOTOS << ")";
				desenhaLista(s);
				limpaEscritaM1();
			}
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_CARREGAC) {
		if (nArgs == 2) {
			if (comandos[1] == NOME_FICH_CARROS) {
				limpaInformacaoM1();
				cout << s.leCarros(NOME_FICH_CARROS);
				desenhaLista(s);
				limpaEscritaM1();
			}
			else {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << "Nome do ficheiro invalido (p.e.: " << NOME_FICH_CARROS << ")";
				desenhaLista(s);
				limpaEscritaM1();
			}
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_CARREGAA) {
		if (nArgs == 2) {
			if (comandos[1] == NOME_FICH_AUTODROMOS) {
				limpaInformacaoM1();
				cout << s.leAutodromos(NOME_FICH_AUTODROMOS);
				desenhaLista(s);
				limpaEscritaM1();
			}
			else {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << "Nome do ficheiro invalido (p.e.: " << NOME_FICH_AUTODROMOS << ")";
				desenhaLista(s);
				limpaEscritaM1();
			}
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_CRIA) {
		if (nArgs == 4) {
			if (comandos[1] == CHAR_PILOTO) {
				if (comandos[2] == CHAR_CRAZYDRIVER || comandos[2] == CHAR_PILOTORAPIDO || comandos[2] == CHAR_PILOTOSURPRESA || comandos[2] == "assassino") {
					limpaInformacaoM1();
					Consola::gotoxy(1, 6);
					cout << s.adicionaPiloto(comandos[2], comandos[3]);
					desenhaLista(s);
					limpaEscritaM1();
				}
				else {
					limpaInformacaoM1();
					Consola::gotoxy(1, 6);
					cout << "Tipo de piloto invalido!";
					desenhaLista(s);
					limpaEscritaM1();
				}
			}
			else {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << "Segundo argumento incorreto!";
				desenhaLista(s);
				limpaEscritaM1();
			}
		}
		else if (nArgs == 5) {
			if (comandos[1] == CHAR_PILOTO) {
				if (comandos[2] == CHAR_CRAZYDRIVER || comandos[2] == CHAR_PILOTORAPIDO || comandos[2] == CHAR_PILOTOSURPRESA || comandos[2] == "assassino") {
					limpaInformacaoM1();
					Consola::gotoxy(1, 6);
					cout << s.adicionaPiloto(comandos[2], comandos[3] + " " + comandos[4]);
					desenhaLista(s);
					limpaEscritaM1();
				}
				else {
					limpaInformacaoM1();
					Consola::gotoxy(1, 6);
					cout << "Tipo de piloto invalido!";
					desenhaLista(s);
					limpaEscritaM1();
				}
			}
			else if (comandos[1] == CHAR_AUTODROMO) {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				if (testaExcecoesSTOI(comandos[3]) && testaExcecoesSTOI(comandos[4]))
					cout << s.adicionaAutodromo(comandos[2], stoi(comandos[3]), stoi(comandos[4]));
				desenhaLista(s);
				limpaEscritaM1();
			}
			else {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << "Argumentos incorretos!";
				desenhaLista(s);
				limpaEscritaM1();
			}
		}
		else if (nArgs == 6) {
			if (comandos[1] == CHAR_CARRO) {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				if(testaExcecoesSTOF(comandos[3]) && testaExcecoesSTOF(comandos[4]) && testaExcecoesSTOI(comandos[5]))
					cout << s.adicionaCarroSM(comandos[2], stof(comandos[3]), stof(comandos[4]), stoi(comandos[5]));
				desenhaLista(s);
				limpaEscritaM1();
			}
			else {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << "Segundo argumento incorreto!";
				desenhaLista(s);
				limpaEscritaM1();
			}
		}
		else if (nArgs == 7) {
			if (comandos[1] == CHAR_CARRO) {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				if (testaExcecoesSTOF(comandos[4]) && testaExcecoesSTOF(comandos[5]) && testaExcecoesSTOI(comandos[6]))
					cout << s.adicionaCarro(comandos[2], comandos[3], stof(comandos[4]), stof(comandos[5]), stoi(comandos[6]));
				desenhaLista(s);
				limpaEscritaM1();
			}
			else {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << "Segundo argumento incorreto!";
				desenhaLista(s);
				limpaEscritaM1();
			}
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido! Sugestao: ver comando ajuda.";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_APAGA) {
		if (nArgs == 3) {
			if (comandos[1] == CHAR_CARRO) {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << s.removerCarro(comandos[2][0]);
				desenhaLista(s);
				limpaEscritaM1();
			}
			else if (comandos[1] == CHAR_PILOTO) {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << s.removerPiloto(comandos[2]);
				desenhaLista(s);
				limpaEscritaM1();
			}
			else if (comandos[1] == CHAR_AUTODROMO) {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << s.removerAutodromo(comandos[2]);
				desenhaLista(s);
				limpaEscritaM1();
			}
			else {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << "Segundo argumento incorreto!";
				desenhaLista(s);
				limpaEscritaM1();
			}
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_ENTRANOCARRO) {
		if (nArgs == 3) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << s.entraNoCarro(comandos[1][0], comandos[2]);
			desenhaLista(s);
			limpaEscritaM1();
		}
		else if(nArgs == 4) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << s.entraNoCarro(comandos[1][0], comandos[2] + " " + comandos[3]);
			desenhaLista(s);
			limpaEscritaM1();
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_SAIDOCARRO) {
		if (nArgs == 2) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << s.saiDoCarro(comandos[1][0]);
			desenhaLista(s);
			limpaEscritaM1();
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_LISTA) {
		if (nArgs == 1) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << s;
			desenhaLista(s);
			limpaEscritaM1();
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_SAVEDGV) {
		if (nArgs == 2) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << s.saveDGV(comandos[1]);
			desenhaLista(s);
			limpaEscritaM1();
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_LOADDGV) {
		if (nArgs == 2) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << s.loadDGV(comandos[1]);
			desenhaLista(s);
			limpaEscritaM1();
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_DELDGV) {
		if (nArgs == 2) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << s.deleteDGV(comandos[1]);
			desenhaLista(s);
			limpaEscritaM1();
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_LISTABACKUPS) {
		if (nArgs == 1) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << s.listaBackups();
			desenhaLista(s);
			limpaEscritaM1();
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_CAMPEONATO) {
		if (nArgs >= 2) {
			if (s.isPilotosEmCarros()) {
				limpaInformacaoM1();
				if (s.criaCampeonato(comandos) == 1) {
					Consola::clrscr();
					return 1;
				}
				else {
					limpaInformacaoM1();
					Consola::gotoxy(1, 6);
					cout << "Nao indicou autodromos existentes!";
					desenhaLista(s);
					limpaEscritaM1();
				}
			}
			else {
				limpaInformacaoM1();
				Consola::gotoxy(1, 6);
				cout << "Nao existem carros com pilotos suficientes!";
				desenhaLista(s);
				limpaEscritaM1();
			}
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_AJUDA) {
		if (nArgs == 1) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "carregaP <nomeFicheiro>" << endl << " carregaC <nomeFicheiro>\n carregaA <nomeFicheiro>" << endl <<
				" cria <letraTipo> <dados do objeto>\n{letraTipo: p + crazy||rapido||surpresa - piloto; c - carro; a - autodromo}" << endl <<
				" apaga <letraTipo> <identificador>\n\t{identificador: c - letra; a & p - nome}" << endl <<
				" entranocarro <letraCarro> <nomePiloto>" << endl << " saidocarro <letraCarro>" << endl << 
				" lista {mostra info sobre carros, pilotos e autodromos}" << endl <<
				" savedgv <nomeFicheiro>" << endl << " loaddgv <nomeFicheiro>" << endl << " deldgv <nomeFicheiro> " << endl << " listaBackups\n" << endl <<
				" ajuda {mostra os comandos}" << endl << " sair";
			desenhaLista(s);
			limpaEscritaM1();
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else if (comandos[0] == CMD_SAIR) {
		if (nArgs == 1) {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "A sair";
			limpaEscritaM1();
			return -1;
		}
		else {
			limpaInformacaoM1();
			Consola::gotoxy(1, 6);
			cout << "Numero de argumentos invalido!";
			desenhaLista(s);
			limpaEscritaM1();
		}
	}
	else {
		limpaInformacaoM1();
		Consola::gotoxy(1, 6);
		cout << "O comando \"" << comandos[0] << "\" nao existe!";
		desenhaLista(s);
		limpaEscritaM1();
	}
	return 0;
}

int Interface::leComandos_modo1(Simulacao& s) {
	size_t posicao;
	vector<string> listaComandos;
	string cmd, palavra;
	string espaco = { ' ' };

	imprimeTituloModo1();

	Consola::gotoxy(1, 5);
	cout << "Comando: ";
	Consola::gotoxy(10, 5);

	Consola::setTextColor(Consola::BRANCO_CLARO);
	getline(cin, cmd);
	Consola::setTextColor(Consola::BRANCO);

	while ((posicao = cmd.find(espaco)) != string::npos) {	// npos == até ao fim da string
		palavra = cmd.substr(0, posicao);
		listaComandos.push_back(palavra);
		cmd.erase(0, posicao + espaco.length());
	}
	listaComandos.push_back(cmd);

	return execComandosM1(s, listaComandos, (int)listaComandos.size());
}

int Interface::leComandos_modo2(Simulacao& s) {
	size_t posicao;
	vector<string> listaComandos2;
	string cmd, palavra;
	string espaco = { ' ' };

	imprimeTituloModo2();

	imprimeAutodromo(s.getNomeAutodromoAtual());

	imprimeTituloGaragem();

	imprimeGaragem(s.getCarrosGaragemSTR());

	imprimePosicoes(s.getPosicoes());

	imprimePistas(s.getArrayPistas(), s.getMaxCarros(), s.getCarrosEmergencia());

	Consola::gotoxy(1, 22);
	cout << "Comando: ";
	Consola::gotoxy(10, 22);

	Consola::setTextColor(Consola::BRANCO_CLARO);
	getline(cin, cmd);
	Consola::setTextColor(Consola::BRANCO);

	while ((posicao = cmd.find(espaco)) != string::npos) {
		palavra = cmd.substr(0, posicao);
		listaComandos2.push_back(palavra);
		cmd.erase(0, posicao + espaco.length());
	}
	listaComandos2.push_back(cmd);

	return execComandosM2(s, listaComandos2, (int)listaComandos2.size());
}

bool Interface::mainMenu() {
	int controlo = 0;

	imprimeBorda();
	imprimeTituloPrincipal();
	imprimeInformacoes();

	do {
		switch (Consola::getch()) {
		case Consola::ENTER:
			controlo = 1;
			break;
		case Consola::ESCAPE:
			controlo = -1;
			break;
		default:
			break;
		}
	} while (controlo == 0);

	if (controlo == -1)
		return false;

	return true;
}

void Interface::desenhaLista(Simulacao& s) {
	int posY = 2;

	if (s.podeEscreverALista()) {
		Consola::setTextColor(Consola::AMARELO_CLARO);
		Consola::gotoxy((X_MAX / 2) + 10, posY);
		cout << "CARROS";

		Consola::gotoxy((X_MAX / 2) + (X_MAX / 6) + 10, posY);
		cout << "PILOTOS";

		Consola::gotoxy((X_MAX / 2) + (X_MAX / 3) + 8, posY);
		cout << "AUTODROMOS";

		Consola::setTextColor(Consola::VERMELHO_CLARO);
		while (posY < Y_MAX - 1) {
			Consola::gotoxy(X_MAX / 2, posY);
			cout << "|";
			Consola::gotoxy((X_MAX / 2) + (X_MAX / 6), posY);
			cout << "|";
			Consola::gotoxy((X_MAX / 2) + (X_MAX / 3), posY);
			cout << "|";
			++posY;
		}
		Consola::setTextColor(Consola::BRANCO);

		mostraPilotos(s.getPilotosListaSTR());
		mostraCarros(s.getCarrosListaSTR());
		mostraAutodromos(s.getAutodromosListaSTR());
	}
}

void Interface::mostraPilotos(vector<string> vp) {
	auto i = 0;
	Consola::setTextColor(Consola::BRANCO);
	limpaPilotos(i);
	for (i; i != vp.size(); ) {
		while (vp[i] != "BREAK") {
			Consola::gotoxy((X_MAX / 2) + (X_MAX / 6) + 2, 4 + i);
			cout << vp[i];
			i++;
		}
		i++;
	}
	limpaPilotos(i);
}

void Interface::mostraCarros(vector<string> vc) {
	auto i = 0;
	Consola::setTextColor(Consola::BRANCO);
	limpaCarros(i); 
	for (i; i != vc.size(); ) {
		while (vc[i] != "BREAK") {
			Consola::gotoxy((X_MAX / 2) + 2, 4 + i);
			cout << vc[i];
			i++;
		}
		i++;
	}
	limpaCarros(i);
}

void Interface::mostraAutodromos(vector<string> va) {
	auto i = 0;
	Consola::setTextColor(Consola::BRANCO);
	limpaAutodromos(i);
	for (i; i != va.size(); ) {
		while (va[i] != "BREAK") {
			Consola::gotoxy((X_MAX / 2) + (X_MAX / 3) + 2, 4 + i);
			cout << va[i];
			i++;
		}
		i++;
	}
	limpaAutodromos(i);
}

void Interface::limpaPilotos(int l) {
	for (int i = l; i < Y_MAX; i++) {
		Consola::gotoxy((X_MAX / 2) + (X_MAX / 6) + 2, 4 + i);
		cout << "                      ";
	}
}

void Interface::limpaCarros(int l) {
	for (int i = l; i < Y_MAX; i++) {
		Consola::gotoxy((X_MAX / 2) + 2, 4 + i);
		cout << "                      ";
	}
}

void Interface::limpaAutodromos(int l) {
	for (int i = l; i < Y_MAX; i++) {
		Consola::gotoxy((X_MAX / 2) + (X_MAX / 3) + 2, 4 + i);
		cout << "                      ";
	}
}

void Interface::imprimeBorda() {
	int posX_Max, posY_Max;
	int posX, posY;
	int posX_AUX, posY_AUX;
	int posX_f, posY_f;
	int posX_atual, posY_atual;

	// Equivale ao total do ecrã
	posX_Max = X_MAX;
	posY_Max = Y_MAX;

	// Equivale a meio do ecrã
	posX_AUX = posX_Max / 2;
	posY_AUX = posY_Max / 2;

	// Equivale a 1/4 do ecrã
	posX = posX_Max / 4;
	posY = posY_Max / 4;

	// Equivale a 3/4 do ecrã
	posX_f = posX + posX_AUX;
	posY_f = posY + posY_AUX;

	posX_atual = posX;

	Consola::setTextColor(Consola::AMARELO);

	// Linha de Cima (mantém Y, muda X)
	while (posX_atual <= posX_f) {
		Consola::gotoxy(posX_atual, posY);
		cout << "*";
		posX_atual = posX_atual + 1;
	}

	// Linha de baixo (mantém Y, muda X)
	posX_atual = posX;
	while (posX_atual <= posX_f) {
		Consola::gotoxy(posX_atual, posY_f);
		cout << "*";
		posX_atual = posX_atual + 1;
	}

	// Coluna da direita (mantém X, muda Y)
	posY_atual = posY;
	while (posY_atual <= posY_f) {
		Consola::gotoxy(posX, posY_atual);
		cout << "*";
		posY_atual = posY_atual + 1;
	}

	// Coluna da esquerda (mantém X, muda Y)
	posY_atual = posY;
	while (posY_atual <= posY_f) {
		Consola::gotoxy(posX_f, posY_atual);
		cout << "*";
		posY_atual = posY_atual + 1;
	}
}

void Interface::imprimeTituloPrincipal() {
	// Posição Y para a escrita
	int posY = (Y_MAX / 2) - (Y_MAX / 5);

	Consola::setTextColor(Consola::CYAN_CLARO);
	Consola::gotoxy(67, posY);
	cout << " F1 SIMULATOR ";
}

void Interface::imprimeTituloModo1() {
	Consola::setTextColor(Consola::CYAN_CLARO);
	Consola::gotoxy(X_MAX / 8, 0);
	cout << " Modo 1 - Preparacao ";
	Consola::setTextColor(Consola::BRANCO);
}

void Interface::imprimeTituloModo2() {
	Consola::setTextColor(Consola::CYAN_CLARO);
	Consola::gotoxy((X_MAX / 2) - 15, 0);
	cout << " Modo 2 - Campeonato ";
	Consola::setTextColor(Consola::BRANCO);
}

void Interface::imprimePosicoes(string posicoes) {
	Consola::setTextColor(Consola::CINZENTO);
	Consola::gotoxy(1, 4);
	cout << "                                                               ";
	Consola::gotoxy(1, 4);
	cout << posicoes;
	Consola::setTextColor(Consola::BRANCO);
}

void Interface::imprimePistas(vector<vector<char>> pista, int maxcarros, vector<char> carrosEmergencia) {
	Consola::gotoxy(1, 6);

	for (int j = 0, i = 0; i < maxcarros ; i++) {
		for (int t = 0, k = 0; k != pista.size(); k++) {
			if (pista[i][k] == '.') {
				if ((i % 2) == 0) {
					Consola::gotoxy(1 + t, 6 + j);
					Consola::setTextColor(Consola::VERDE);
					Consola::setBackgroundColor(Consola::VERDE);
					cout << (char)pista[i][k];
					cout << (char)pista[i][k];
					Consola::gotoxy(1 + t, 6 + j + 1);
					cout << (char)pista[i][k];
					cout << (char)pista[i][k];
					t += 2;
				}
				else {
					Consola::gotoxy(1 + t, 6 + j);
					Consola::setTextColor(Consola::VERDE_CLARO);
					Consola::setBackgroundColor(Consola::VERDE_CLARO);
					cout << (char)pista[i][k];
					cout << (char)pista[i][k];
					Consola::gotoxy(1 + t, 6 + j + 1);
					cout << (char)pista[i][k];
					cout << (char)pista[i][k];
					t += 2;
				}
			}
			else if (pista[i][k] == '+') {
				Consola::gotoxy(1 + t, 6 + j);
				Consola::setTextColor(Consola::CINZENTO);
				Consola::setBackgroundColor(Consola::CINZENTO);
				cout << (char)pista[i][k];
				cout << (char)pista[i][k];
				Consola::gotoxy(1 + t, 6 + j + 1);
				cout << (char)pista[i][k];
				cout << (char)pista[i][k];
				t += 2;
			}
			else if ((pista[i][k] >= 'A' && pista[i][k] <= 'Z') || pista[i][k] == '?') {
				Consola::gotoxy(1 + t, 6 + j);
				if ((t + 2) == 98) {
					if ((i % 2) == 0) {
						Consola::setBackgroundColor(Consola::VERDE);

						if (carrosEmergencia.size() > 0) {
							for (int id = 0; id != carrosEmergencia.size(); id++) {
								if (pista[i][k] == carrosEmergencia[id]) {
									Consola::setTextColor(Consola::VERMELHO_CLARO);
									break;
								}
								else
									Consola::setTextColor(Consola::BRANCO_CLARO);
							}
						}
						else
							Consola::setTextColor(Consola::BRANCO_CLARO);
						cout << (char)pista[i][k];
						Consola::setBackgroundColor(Consola::VERDE);
						Consola::setTextColor(Consola::VERDE);
						cout << (char)'.';
						Consola::gotoxy(1 + t, 6 + j + 1);
						cout << (char)'.';
						cout << (char)'.';
						t += 2;
					}
					else {
						Consola::setBackgroundColor(Consola::VERDE_CLARO);
						if (carrosEmergencia.size() > 0) {
							for (int id = 0; id != carrosEmergencia.size(); id++) {
								if (pista[i][k] == carrosEmergencia[id]) {
									Consola::setTextColor(Consola::AZUL_CLARO);
									break;
								}
								else
									Consola::setTextColor(Consola::PRETO);
							}
						}
						else
							Consola::setTextColor(Consola::PRETO);
						cout << (char)pista[i][k];
						Consola::setBackgroundColor(Consola::VERDE_CLARO);
						Consola::setTextColor(Consola::VERDE_CLARO);
						cout << (char)'.';
						Consola::gotoxy(1 + t, 6 + j + 1);
						cout << (char)'.';
						cout << (char)'.';
						t += 2;
					}
				}
				int k1 = k + 1;	// [k + 1] dava warning!
				if (k1 >= pista.size()) {
					if (((t + 2) == 2) || ((t + 2) == 4) || ((t + 2) == 98) || ((t + 2) == 100)) {
						if ((i % 2) == 0) {
							Consola::setBackgroundColor(Consola::VERDE);
							if (carrosEmergencia.size() > 0) {
								for (int id = 0; id != carrosEmergencia.size(); id++) {
									if (pista[i][k] == carrosEmergencia[id]) {
										Consola::setTextColor(Consola::VERMELHO_CLARO);
										break;
									}
									else
										Consola::setTextColor(Consola::BRANCO_CLARO);
								}
							}
							else
								Consola::setTextColor(Consola::BRANCO_CLARO);
							cout << (char)pista[i][k];
							Consola::setBackgroundColor(Consola::VERDE);
							Consola::setTextColor(Consola::VERDE);
							cout << (char)'.';
							Consola::gotoxy(1 + t, 6 + j + 1);
							cout << (char)'.';
							cout << (char)'.';
							t += 2;
						}
						else {
							Consola::setBackgroundColor(Consola::VERDE_CLARO);
							if (carrosEmergencia.size() > 0) {
								for (int id = 0; id != carrosEmergencia.size(); id++) {
									if (pista[i][k] == carrosEmergencia[id]) {
										Consola::setTextColor(Consola::AZUL_CLARO);
										break;
									}
									else
										Consola::setTextColor(Consola::PRETO);
								}
							}
							else
								Consola::setTextColor(Consola::PRETO);
							cout << (char)pista[i][k];
							Consola::setBackgroundColor(Consola::VERDE_CLARO);
							Consola::setTextColor(Consola::VERDE_CLARO);
							cout << (char)'.';
							Consola::gotoxy(1 + t, 6 + j + 1);
							cout << (char)'.';
							cout << (char)'.';
							t += 2;
						}
					}
					else {
						if (carrosEmergencia.size() > 0) {
							for (int id = 0; id != carrosEmergencia.size(); id++) {
								if (pista[i][k] == carrosEmergencia[id]) {
									Consola::setTextColor(Consola::VERMELHO_CLARO);
									break;
								}
								else
									Consola::setTextColor(Consola::BRANCO_CLARO);
							}
						}
						else
							Consola::setTextColor(Consola::BRANCO_CLARO);
						Consola::setBackgroundColor(Consola::CINZENTO);
						cout << (char)pista[i][k];
						Consola::setTextColor(Consola::CINZENTO);
						Consola::setBackgroundColor(Consola::CINZENTO);
						cout << (char)'+';
						Consola::gotoxy(1 + t, 6 + j + 1);
						cout << (char)'+';
						cout << (char)'+';
						t += 2;
					}
				}
				else {
					if (pista[i][k1] == '.') {
						if (((t + 2) == 2) || ((t + 2) == 4) || ((t + 2) == 98) || ((t + 2) == 100)) {
							if (carrosEmergencia.size() > 0) {
								for (int id = 0; id != carrosEmergencia.size(); id++) {
									if (pista[i][k] == carrosEmergencia[id]) {
										Consola::setTextColor(Consola::VERMELHO_CLARO);
										break;
									}
									else
										Consola::setTextColor(Consola::BRANCO_CLARO);
								}
							}
							else
								Consola::setTextColor(Consola::BRANCO_CLARO);
							Consola::setBackgroundColor(Consola::CINZENTO);
							cout << (char)pista[i][k];
							Consola::setTextColor(Consola::CINZENTO);
							Consola::setBackgroundColor(Consola::CINZENTO);
							cout << (char)'+';
							Consola::gotoxy(1 + t, 6 + j + 1);
							cout << (char)'+';
							cout << (char)'+';
							t += 2;
						}
						else {
							if ((i % 2) == 0) {
								Consola::setBackgroundColor(Consola::VERDE);
								if (carrosEmergencia.size() > 0) {
									for (int id = 0; id != carrosEmergencia.size(); id++) {
										if (pista[i][k] == carrosEmergencia[id]) {
											Consola::setTextColor(Consola::VERMELHO_CLARO);
											break;
										}
										else
											Consola::setTextColor(Consola::BRANCO_CLARO);
									}
								}
								else
									Consola::setTextColor(Consola::BRANCO_CLARO);
								cout << (char)pista[i][k];
								Consola::setBackgroundColor(Consola::VERDE);
								Consola::setTextColor(Consola::VERDE);
								cout << (char)pista[i][k1];
								Consola::gotoxy(1 + t, 6 + j + 1);
								cout << (char)pista[i][k1];
								cout << (char)pista[i][k1];
								t += 2;
							}
							else {
								Consola::setBackgroundColor(Consola::VERDE_CLARO);
								if (carrosEmergencia.size() > 0) {
									for (int id = 0; id != carrosEmergencia.size(); id++) {
										if (pista[i][k] == carrosEmergencia[id]) {
											Consola::setTextColor(Consola::AZUL_CLARO);
											break;
										}
										else
											Consola::setTextColor(Consola::PRETO);
									}
								}
								else
									Consola::setTextColor(Consola::PRETO);
								cout << (char)pista[i][k];
								Consola::setBackgroundColor(Consola::VERDE_CLARO);
								Consola::setTextColor(Consola::VERDE_CLARO);
								cout << (char)pista[i][k1];
								Consola::gotoxy(1 + t, 6 + j + 1);
								cout << (char)pista[i][k1];
								cout << (char)pista[i][k1];
								t += 2;
							}
						}
					}
					else if (pista[i][k1] == '+') {
						if ((i % 2) == 0) {
							if (carrosEmergencia.size() > 0) {
								for (int id = 0; id != carrosEmergencia.size(); id++) {
									if (pista[i][k] == carrosEmergencia[id]) {
										Consola::setTextColor(Consola::VERMELHO_CLARO);
										break;
									}
									else
										Consola::setTextColor(Consola::BRANCO_CLARO);
								}
							}
							else
								Consola::setTextColor(Consola::BRANCO_CLARO);
							Consola::setBackgroundColor(Consola::VERDE);
							cout << (char)pista[i][k];
							Consola::setTextColor(Consola::VERDE);
							Consola::setBackgroundColor(Consola::VERDE);
							if (((t + 2) < 2) || ((t + 2) > 4) || ((t + 2) < 98) || ((t + 2) > 100)) {
								cout << (char)pista[i][k1];
								Consola::gotoxy(1 + t, 6 + j + 1);
								cout << (char)pista[i][k1];
								cout << (char)pista[i][k1];
								t += 2;
							}
						}
						else {
							if (carrosEmergencia.size() > 0) {
								for (int id = 0; id != carrosEmergencia.size(); id++) {
									if (pista[i][k] == carrosEmergencia[id]) {
										Consola::setTextColor(Consola::AZUL_CLARO);
										break;
									}
									else
										Consola::setTextColor(Consola::PRETO);
								}
							}
							else
								Consola::setTextColor(Consola::PRETO);
							Consola::setBackgroundColor(Consola::VERDE_CLARO);
							cout << (char)pista[i][k];
							Consola::setTextColor(Consola::VERDE_CLARO);
							Consola::setBackgroundColor(Consola::VERDE_CLARO);
							if (((t + 2) < 2) || ((t + 2) > 4) || ((t + 2) < 98) || ((t + 2) > 100)) {
								cout << (char)pista[i][k1];
								Consola::gotoxy(1 + t, 6 + j + 1);
								cout << (char)pista[i][k1];
								cout << (char)pista[i][k1];
								t += 2;
							}
						}
					}
				}
			}
		}
		j += 2;
	}
	Consola::setTextColor(Consola::BRANCO);
	Consola::setBackgroundColor(Consola::PRETO);
}

string Interface::imprimeLogs(vector<string> logs) {
	ostringstream oss;
	for (int i = 0; i != logs.size(); i++)
		oss << logs[i];
	return oss.str();
}

void Interface::imprimeGaragem(vector<string> carros) {
	int i = 0;
	limpaGaragem(5);
	for (i; i != carros.size(); ) {
		while (carros[i] != "BREAK") {
			Consola::gotoxy((X_MAX / 2) + (X_MAX / 4) + 4, 6 + i);
			cout << carros[i];
			i++;
		}
		i++;
	}
	limpaGaragem(i + 1);
}

void Interface::imprimeTituloGaragem() {
	desenhaLinha();
	Consola::gotoxy((X_MAX / 2) + (X_MAX / 4) + 15, 3);
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	cout << "Garagem";
	Consola::setTextColor(Consola::BRANCO);
}

void Interface::limpaGaragem(int l) {
	for (int i = l; i < Y_MAX; i++) {
		Consola::gotoxy((X_MAX / 2) + (X_MAX / 4) + 2, 4 + i);
		cout << "                                    ";
	}
}

void Interface::desenhaLinha() {
	for (int i = 3; i < Y_MAX - 5; i++) {
		Consola::gotoxy((X_MAX / 2) + (X_MAX / 4), i);
		Consola::setTextColor(Consola::CYAN);
		cout << "|";
	}
	Consola::setTextColor(Consola::BRANCO);
}

void Interface::imprimeInformacoes() {
	vector<string> informacoes = { "Modo 1 - Define tudo o que existe: carros, autodromos e pilotos.", "\tE' possivel fazer backup da DGV.",
									"Modo 2 - Simulacao de um campeonato personalizado pelo utilizador." };
	int tam = (int)informacoes.size();

	Consola::setTextColor(Consola::BRANCO);

	for (int i = 0; i < tam; i++) {
		Consola::gotoxy(45, 16 + i);
		cout << informacoes[i];
	}

	Consola::gotoxy(45, 16 + tam + 3);
	cout << "Pressione ENTER para avancar ou ESC para sair - ";
}

void Interface::imprimeAutodromo(const string nome) {
	Consola::gotoxy((X_MAX / 2) - 10, 2);
	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << nome;
	Consola::setTextColor(Consola::BRANCO);
}

int Interface::terminaPrograma() {
	Consola::clrscr();
	Consola::gotoxy((X_MAX / 3) + 20, (Y_MAX / 2) - 2);
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	cout << "Exit!";
	Consola::setTextColor(Consola::BRANCO);
	Consola::gotoxy((X_MAX / 3) + 10, (Y_MAX / 2));
	cout << "Prima uma tecla para sair. ";
	Consola::getch();
	Consola::gotoxy(0, Y_MAX - 10);
	return -2;
}

void Interface::limpa_buffer() {
	cin.ignore(1000, '\n');
	fflush(stdin);
}

void Interface::limpaEscritaM1() {
	Consola::gotoxy(10, 5);
	cout << "                                                                     ";
	Consola::gotoxy(10, 5);
}

void Interface::limpaInformacaoM1() {
	for (int i = 6; i < 40; i++) {
		Consola::gotoxy(0, i);
		cout << "                                                                                        ";
		Consola::gotoxy(0, i);
	}
	Consola::gotoxy(0, 6);
}

void Interface::limpaInformacaoM2() {
	for (int i = 23; i < 40; i++) {
		Consola::gotoxy(0, i);
		cout << "                                                                                                               ";
		Consola::gotoxy(0, i);
	}
	Consola::gotoxy(1, 23);
}

void Interface::limpaEscritaM2() {
	Consola::gotoxy(10, 22);
	cout << "                                                                                        ";
	Consola::gotoxy(10, 22);
}

void Interface::limpaPista() {
	for (int i = 6; i < 21; i++) {
		Consola::gotoxy(0, i);
		cout << "                                                                                                     ";
	}
}

bool Interface::testaExcecoesSTOI(string valor) {
	try {
		int value = stoi(valor);
	}
	catch (std::invalid_argument& ) {
		cout << "O valor " << valor << " e um valor invalido!\n";
		return false;
	}
	catch (std::out_of_range& ) {
		cout << "O valor inserido " << valor << " nao esta dentro dos valores desejados.\n";
		return false;
	}
	catch (...) {
		cout << "[ERRO]: conversao do valor " << valor << " para inteiro.\n";
		return false;
	}
	return true;
}

bool Interface::testaExcecoesSTOF(string valor) {
	try {
		float value = stof(valor);
	}
	catch (std::invalid_argument& ) {
		cout << "O valor " << valor << " e um valor invalido!\n";
		return false;
	}
	catch (std::out_of_range& ) {
		cout << "O valor inserido " << valor << " nao esta dentro dos valores desejados.\n";
		return false;
	}
	catch (...) {
		cout << "[ERRO]: conversao do valor " << valor << " para float.\n";
		return false;
	}
	return true;
}
