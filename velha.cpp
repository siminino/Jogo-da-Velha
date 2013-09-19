#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

char *velha[3][3] = {{"1", "2", "3"}, {"4", "5", "6"}, {"7", "8", "9"}};
vector<int> jogados;

void desenha_velha() {
	cout << velha[0][0] << " | " << velha[0][1] << " | " << velha[0][2] << "\n";
	cout << velha[1][0] << " | " << velha[1][1] << " | " << velha[1][2] << "\n";
	cout << velha[2][0] << " | " << velha[2][1] << " | " << velha[2][2] << "\n";
}

int obter_jogada() {
	char entrada;
	int jogada;
	while (true) {
		cin >> entrada;
		cout << entrada << "\n";
		jogada = (int)entrada - 48;
		if (std::find(jogados.begin(), jogados.end(), jogada) != jogados.end()) {
			cout << "Posicao " << jogada << " já foi jogado.\n";
		} else if (jogada >= 1 and jogada <= 9) {
			break;
		} else {
			cout << "Jogada invalida.\n";
		}
		cout << "Escolha outra posicao: ";
	}
	jogados.push_back(jogada);	
	return jogada;
}

void preenche_jogada(int jogada, char *simbolo){
	if (jogada >= 1 and jogada <= 3) {
		velha[0][jogada-1] = simbolo;
	} else if (jogada >= 4 and jogada <= 6) {
		velha[1][jogada-4] = simbolo;
	} else if (jogada >= 7 and jogada <= 9) {
		velha[2][jogada-7] = simbolo;
	}
}

void jogar_computador(int jogada) {
	char* simbolo = "O";
	cout << "Vez do computador.\n";
	preenche_jogada(jogada, simbolo);
	jogados.push_back(jogada);	
	desenha_velha();
}

int jogar_jogador() {
	int jogada;
	char *simbolo = "X";
	cout << "Sua vez: ";
	jogada = obter_jogada();
	preenche_jogada(jogada, simbolo);
	desenha_velha();
	return jogada;
}

void galho(int primeira_decisao, int primeira_chance, int segunda_decisao, int segunda_chance, int ultima_jogada) {
	int jogada;
	jogar_computador(primeira_decisao);
	jogada = jogar_jogador();
	if (jogada == primeira_chance) {
		jogar_computador(segunda_decisao);
		jogada = jogar_jogador();
		if (jogada == segunda_chance) {
			jogar_computador(ultima_jogada);
		} else {
			jogar_computador(segunda_chance);
		}
	} else {
		jogar_computador(primeira_chance);
	}
}

int game_loop() {
	int jogada;
	desenha_velha();

	jogar_computador(1);
	jogada = jogar_jogador();

	if (jogada == 2 or jogada == 3) {
		galho(7, 4, 9, 5, 8);
	} else if (jogada == 4 or jogada == 7) {
		galho(3, 2, 9, 5, 6);
	} else if (jogada == 6 or jogada == 8) {
		galho(3, 2, 5, 7, 9);
	} else if (jogada == 9) {
		galho(3, 2, 7, 5, 4);
	} else if (jogada == 5) {
		jogar_computador(9);
		jogada = jogar_jogador();
		if (jogada == 3) {
			jogar_computador(7);
			jogada = jogar_jogador();
			if (jogada == 4) {
				jogar_computador(8);
			} else {
				jogar_computador(4);
			}
		} else if (jogada == 7){
			jogar_computador(3);
			jogada = jogar_jogador();
			if (jogada == 2) {
				jogar_computador(6);
			} else {
				jogar_computador(2);
			}
		} else if (jogada == 2){
			jogar_computador(8);
			jogada = jogar_jogador();
			if (jogada == 7) {
				jogar_computador(3);
				jogada = jogar_jogador();
				//bloco velha
				if (jogada == 6) {
					jogar_computador(4);	
					return 1;
				} else {
					jogar_computador(6);
				}
			} else {
				jogar_computador(7);
			}	
		} else if (jogada == 4){
			jogar_computador(6);
			jogada = jogar_jogador();
			if (jogada == 3) {
				jogar_computador(7);
				jogada = jogar_jogador();
				//bloco velha
				if (jogada == 8) {
					jogar_computador(2);	
					return 1;
				} else {
					jogar_computador(8);
				}
			} else {
				jogar_computador(3);
			}	
		} else if (jogada == 6){
			jogar_computador(4);
			jogada = jogar_jogador();
			if (jogada == 7) {
				jogar_computador(3);
				jogada = jogar_jogador();
				//bloco velha
				if (jogada == 2) {
					jogar_computador(8);	
					return 1;
				} else {
					jogar_computador(2);
				}
			} else {
				jogar_computador(7);
			}	
		} else if (jogada == 8){
			jogar_computador(2);
			jogada = jogar_jogador();
			if (jogada == 3) {
				jogar_computador(7);
				jogada = jogar_jogador();
				//bloco velha
				if (jogada == 4) {
					jogar_computador(6);	
					return 1;
				} else {
					jogar_computador(4);
				}
			} else {
				jogar_computador(3);
			}
		}
	}
	return 0;
}

int main() {
	int resultado;
	resultado = game_loop();
	if (resultado == 0) {
		cout << "O computador venceu.\n";
	} else {
		cout << "Deu velha.\n";
	}
	return 0;
}