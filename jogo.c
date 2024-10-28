#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cabecalho_do_jogo(){
    printf("\nJogo iniciado com Sucesso\n\n");
    printf("---------------------------------\n");
    printf("|    G A M E  D O  S A P O      |\n");
    printf("---------------------------------\n");
    printf("\nJogador 1 [AZUL]");
    printf("\nJogador 2 [VERMELHO]\n");
}

int conferir(int tab[10][10], int x){  //essa função confere se o jogo finalizou, e se as jogadas de ambos jogadores ja foi finalizada
    int cont=0;
    if (x==0){
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if(tab[i][j] == 1){
                    cont++;
                } else if(tab[i][j] == 2){
                    cont++;
                }
            }
        }
    }else if(x==1){
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if(tab[i][j] == 1){
                    cont++;
                }
            }
        }
    }else if(x==2){
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if(tab[i][j] == 2){
                    cont++;
                }
            }
        }
    }
    if(cont == 0){
        return 1;
    }else{
        return 0;}}

void criar(int tabuleiro[10][10]) {  //essa função cria a tab colocando todos elementos como sendo 0
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;}
    }}

void Saposelagos(int tab[10][10]) { //essa função tem a funcionalidade de distribuir os sapos(posições fixas) e lagos(aleatoriamente)
    //Sapos
    for (int j = 0; j < 10; j += 2) {
        tab[0][j] = 1; // Jogador Azul (1)
        tab[9][j + 1] = 2; // Jogador Vermelho (2)
    }
    //Lagos
    int armazenanumeros_aleatorios[10];
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios
    for (int i = 0; i < 5; i++) {     //sortear linhas
        int numero = rand() % 8 + 1; // Gera um número aleatório
        armazenanumeros_aleatorios[i] = numero;}
    for (int i = 5; i < 10; i++) {      //sortear colunas
        int numero = rand() % 10; // Gera um número aleatório
        armazenanumeros_aleatorios[i] = numero;}
    //add os lagos na matriz
    tab[armazenanumeros_aleatorios[0]][armazenanumeros_aleatorios[5]] = 7; //7 é o lago
    tab[armazenanumeros_aleatorios[1]][armazenanumeros_aleatorios[6]] = 7;
    tab[armazenanumeros_aleatorios[2]][armazenanumeros_aleatorios[7]] = 7;
    tab[armazenanumeros_aleatorios[3]][armazenanumeros_aleatorios[8]] = 7;
    tab[armazenanumeros_aleatorios[4]][armazenanumeros_aleatorios[9]] = 7;}

void mostra_tab(int tab[10][10]) { //essa função imprime o tabuleiro 
    printf("\n");
    for (int z = 0; z < 10; z++){      //esse for é para numerar a tab
        if(z==0){
            printf("   ");
        }
        printf("%d ", z);}
    printf("\n");
    for (int i = 0; i < 10; i++){
        printf("%d ", i);
        for (int j = 0; j < 10; j++) {
            if (tab[i][j] == 1) { //1-sapo azul/jog1 vivo
                printf("|A");
            } else if (tab[i][j] == 2) { //2-sapo vermelho/jog2 vivo
                printf("|V");
            } else if (tab[i][j] == 3){  //3-sapo azul/jog1 morto ou preso
                printf("|A");
            } else if (tab[i][j] == 4){  //4-sapo vermelho/jog2 morto ou preso
                printf("|V");
            }
            else {
                printf("| ");
            }
        }
        printf("|\n");
    }
    printf("\n");}

int moverjogador1(int tab[10][10], int movimento, int linha, int coluna, int ponto){  //essa função serve para mover o jogador 1
    if(linha!=9){   //encadeiamento de ifs que determinam qual movimento e acao serão realizadas pelos sapos
        //verificação de movimentos que não são possiveis
        if(linha==0 && (movimento=='W' || movimento=='Q' || movimento=='E')){
            printf("[ATENCAO] Esse movimento nao e possivel\n");}
        else if(coluna==0 && (movimento=='A' || movimento =='Q' || movimento == 'Z')){
            printf("[ATENCAO] Esse movimento nao e possivel\n");}
        else if(linha==9 && (movimento=='S' || movimento=='Z' || movimento=='X')){
            printf("[ATENCAO] Esse movimento nao e possivel\n");}
        else if(coluna==9 && (movimento=='D' || movimento=='E' || movimento=='X')){
            printf("[ATENCAO] Esse movimento nao e possivel\n");}
        else if(movimento=='W' && !(linha==0)){ //cima
            if(tab[linha-1][coluna] == 1 || tab[linha-1][coluna] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha][coluna] == 3 && !(tab[linha-1][coluna] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else if(tab[linha-1][coluna] == 7 && tab[linha][coluna] != 3){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else{ //essa parte serve para travar o sapo nas diagonais
                tab[linha-1][coluna] = 1;
                tab[linha][coluna] = 0;
                if(tab[linha-2][coluna] == 2 || tab[linha-1][coluna-1] == 2 || 
                tab[linha-1][coluna+1] == 2 || tab[linha-2][coluna] == 4 || 
                tab[linha-1][coluna-1] == 4 || tab[linha-1][coluna+1] == 4){
                    tab[linha-1][coluna] = 3;
                    if(tab[linha-2][coluna] == 2){
                        tab[linha-2][coluna] = 4;
                    }else if(tab[linha-1][coluna-1] == 2){
                        tab[linha-1][coluna-1] = 4;
                    }else if(tab[linha+1][coluna+1] == 2){
                        tab[linha+1][coluna+1] = 4;
                    }
                    
                }
            }
        }
        else if(movimento=='S' && !(linha==9)){ //baixo
            if(tab[linha+1][coluna] == 1 || tab[linha+1][coluna] == 3){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha][coluna] == 3 && !(tab[linha+1][coluna] == 'x')){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else if(tab[linha+1][coluna] == 7 && tab[linha][coluna] != 7){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else{
                //contagem de pontos
                if(linha+1 == 9 && !(tab[linha+1][coluna] == 2 || tab[linha+1][coluna] == 1)){
                    ponto++;
                    tab[linha+1][coluna] = 3; //sapo azul preso
                    tab[linha][coluna] = 0;
                }
                else{ //essa parte serve para travar o sapo nas diagonais
                    tab[linha+1][coluna] = 1;
                    tab[linha][coluna] = 0;
                    if(tab[linha+2][coluna] == 2 || tab[linha+1][coluna-1] == 2 || 
                    tab[linha+1][coluna+1] == 2 || tab[linha+2][coluna] == 4 || 
                    tab[linha+1][coluna-1] == 4 || tab[linha+1][coluna+1] == 4){
                        tab[linha+1][coluna] = 3;
                        if(tab[linha+2][coluna] == 2){
                            tab[linha+2][coluna] = 4;
                        }else if(tab[linha+1][coluna-1] == 2){
                            tab[linha+1][coluna-1] = 4;
                        }else if( tab[linha+1][coluna+1] == 2){
                            tab[linha+1][coluna+1] = 4;
                        }
                    }
                }
            }
        }
        else if(movimento=='A' && !(coluna==0)){ //esquerda
            if( tab[linha][coluna-1] == 1 || tab[linha][coluna-1] == 2 || tab[linha][coluna-1] == 3 || tab[linha][coluna-1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha][coluna] == 3 && !(tab[linha][coluna-1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else if(tab[linha][coluna-1] == 7 && tab[linha][coluna] != 3){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else{ //essa parte serve para travar o sapo nas diagonais
            tab[linha][coluna-1] = 1;
            tab[linha][coluna] = 0;
            if(tab[linha-1][coluna-1] == 2 || tab[linha+1][coluna-1] == 2 ||
            tab[linha][coluna-2] == 2 || tab[linha-1][coluna-1] == 4 || 
            tab[linha+1][coluna-1] == 4 || tab[linha][coluna-2] == 4){
                    tab[linha][coluna-1]  = 3;
                    if(tab[linha-1][coluna-1] == 2){
                        tab[linha-1][coluna-1] = 4;
                    }else if(tab[linha+1][coluna-1] == 2){
                        tab[linha+1][coluna-1] = 4;
                    }else if(tab[linha][coluna-2] == 4){
                        tab[linha][coluna-2] = 4;
                    }
                }
            }
        }
        else if(movimento=='D' && !(coluna==9)){ //direita
            if( tab[linha][coluna+1] == 1 || tab[linha][coluna+1] == 2 || tab[linha][coluna+1] == 3 || tab[linha][coluna+1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha][coluna+1] == 7 && tab[linha][coluna] != 3){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 3 && !(tab[linha][coluna+1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{ //essa parte serve para travar o sapo nas diagonais
            tab[linha][coluna+1] = 1;
            tab[linha][coluna] = 0;
            if(tab[linha-1][coluna+1] == 2 || tab[linha+1][coluna+1] == 2 || 
            tab[linha][coluna+2] == 2 || tab[linha-1][coluna+1] == 4 || 
            tab[linha+1][coluna+1] == 4 || tab[linha][coluna+2] == 4 ){
                    tab[linha][coluna+1]  = 3;
                    if(tab[linha-1][coluna+1] == 2){
                        tab[linha-1][coluna+1] = 4;
                    }else if(tab[linha+1][coluna+1] == 2){
                        tab[linha+1][coluna+1] = 4;
                    }else if(tab[linha][coluna+2] == 2){
                        tab[linha][coluna+2] = 4;
                    }
                }
            }
        }
        else if(movimento=='Q' && !(linha==0 || coluna==0)){  //superior esquerda
            if( tab[linha-1][coluna-1] == 1 || tab[linha-1][coluna-1] == 2 || tab[linha-1][coluna-1] == 3 || tab[linha-1][coluna-1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha-1][coluna-1] == 7 && tab[linha][coluna] != 3){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 3 && !(tab[linha-1][coluna-1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{ //essa parte serve para travar o sapo nas diagonais
                tab[linha-1][coluna-1] = 1;
                tab[linha][coluna] = 0;
                if(tab[linha-2][coluna-1] == 2 || tab[linha][coluna-1] == 2 ||
                tab[linha-1][coluna-2] == 2 || tab[linha-1][coluna] == 2 || 
                tab[linha-1][coluna-2] == 4 || tab[linha-1][coluna] == 4 ||
                tab[linha-2][coluna-1] == 4 || tab[linha][coluna-1] == 4){
                    tab[linha-1][coluna-1]  = 3;
                    if(tab[linha-2][coluna-1] == 2){
                        tab[linha-2][coluna-1] = 4;
                    }else if(tab[linha][coluna-1] == 2){
                        tab[linha][coluna-1] = 4;
                    }else if(tab[linha-1][coluna-2] == 2){
                        tab[linha-1][coluna-2] = 4;
                    }else if(tab[linha-1][coluna] == 2){
                        tab[linha-1][coluna] = 4;
                    }
                }
            }
        }
        else if(movimento=='E' && !(linha==0 || coluna==9)){ //superior direita
            if( tab[linha-1][coluna+1] == 1 || tab[linha-1][coluna+1] == 2 || tab[linha-1][coluna+1] == 3 || tab[linha-1][coluna+1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha-1][coluna+1] == 7 && tab[linha][coluna] != 3){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 3 && !(tab[linha-1][coluna+1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{ //essa parte serve para travar o sapo nas diagonais
                tab[linha-1][coluna+1] = 1;
                tab[linha][coluna] = 0;
                if(tab[linha-2][coluna+1] == 2 || tab[linha][coluna+1] == 2 ||
                tab[linha-1][coluna+2] == 2 || tab[linha-1][coluna] == 2 || 
                tab[linha-1][coluna+2] == 4 || tab[linha-1][coluna] == 4 ||
                tab[linha-2][coluna+1] == 4 || tab[linha][coluna+1] == 4){
                    tab[linha-1][coluna+1]  = 3;
                    if(tab[linha-2][coluna+1] == 2){
                        tab[linha-2][coluna+1] = 4;
                    }else if(tab[linha][coluna+1] == 2){
                        tab[linha][coluna+1] = 4;
                    }else if(tab[linha-1][coluna+2] == 2){
                        tab[linha-1][coluna+2] = 4;
                    }else if(tab[linha-1][coluna] == 2){
                        tab[linha-1][coluna] = 4;
                    }
                }
            }
        }
        else if(movimento=='Z' && !(coluna==0) && !(linha==9)){ //inferior esquerda
            if( tab[linha+1][coluna-1] == 1 || tab[linha+1][coluna-1] == 2){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha+1][coluna-1] == 7 && tab[linha][coluna] != 3){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 3 && !(tab[linha+1][coluna-1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{
                //contagem de pontos
                if(linha+1 == 9 && !(tab[linha+1][coluna-1] == 2 || tab[linha+1][coluna-1] == 1 || tab[linha+1][coluna-1] == 3 || tab[linha+1][coluna-1] == 4)){
                    ponto++;
                    tab[linha+1][coluna-1] = 3; //sapo vermelho preso
                    tab[linha][coluna] = 0;
                }
                else{ //essa parte serve para travar o sapo nas diagonais
                    tab[linha+1][coluna-1] = 1;
                    tab[linha][coluna] = 0;
                    if(tab[linha+2][coluna-1] == 2 || tab[linha][coluna-1] == 2 ||
                    tab[linha+1][coluna-2] == 2 || tab[linha+1][coluna] == 2 ||
                    tab[linha+1][coluna-2] == 4 || tab[linha+1][coluna] == 4 ||
                    tab[linha+2][coluna-1] == 4 || tab[linha][coluna-1] == 4){
                        tab[linha+1][coluna-1]  = 3;
                        if(tab[linha+2][coluna-1] == 2){
                            tab[linha+2][coluna-1] = 4;
                        }else if(tab[linha][coluna-1] == 2){
                            tab[linha][coluna-1] = 4;
                        }else if(tab[linha+1][coluna-2] == 2){
                            tab[linha+1][coluna-2] = 4;
                        }else if(tab[linha+1][coluna] == 2){
                            tab[linha+1][coluna] = 4;
                        }
                    }
                }
            }
        }
        else if(movimento=='X' && !(linha==9 || coluna==9)){  //inferior direita
            if( tab[linha+1][coluna+1] == 1 || tab[linha+1][coluna+1] == 2){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha+1][coluna+1] == 7 && tab[linha][coluna] != 3){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 3 && !(tab[linha+1][coluna+1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{
                //contagem de pontos
                if(linha+1 == 9 && !(tab[linha+1][coluna+1] == 2 || tab[linha+1][coluna+1] == 1 || tab[linha+1][coluna+1] == 3 || tab[linha+1][coluna+1] == 4)){
                    ponto++;
                    tab[linha+1][coluna+1] = 3; //sapo azul preso
                    tab[linha][coluna] = 0;
                }
                else{ //essa parte serve para travar o sapo nas diagonais
                    tab[linha+1][coluna+1]  = 1;
                    tab[linha][coluna] = 0;
                    if(tab[linha+2][coluna+1] == 2 || tab[linha][coluna+1] == 2 ||
                    tab[linha+1][coluna+2] == 2 || tab[linha+1][coluna] == 2 ||
                    tab[linha+1][coluna+2] == 4 || tab[linha+1][coluna] == 4 ||
                    tab[linha+2][coluna+1] == 4 || tab[linha][coluna+1] == 4){
                        tab[linha+1][coluna-1]  = 3;
                        if(tab[linha+2][coluna+1] == 2){
                            tab[linha+2][coluna+1] = 4;
                        }else if(tab[linha][coluna+1] == 2){
                            tab[linha][coluna+1] = 4;
                        }else if(tab[linha+1][coluna+2] == 2){
                            tab[linha+1][coluna+2] = 4;
                        }else if(tab[linha+1][coluna] == 2){
                            tab[linha+1][coluna] = 4;
                        }
                    }
                }
            }
        }
    }
    else{
        printf("\nEste Sapo esta IMOVEL!\n");
    return ponto;}}

int moverjogador2(int tab[10][10], int movimento, int linha, int coluna, int ponto){
    if(linha!=0){ //encadeiamento de ifs que determinam qual movimento e acao serão realizadas pelos sapos
        //verificação de movimentos que não são possiveis
        if(linha==0 && (movimento=='W' || movimento=='Q' || movimento=='E')){
            printf("[ATENCAO] Esse movimento nao e possivel\n");}
        else if(coluna==0 && (movimento=='A' || movimento =='Q' || movimento == 'Z')){
            printf("[ATENCAO] Esse movimento nao e possivel\n");}
        else if(linha==9 && (movimento=='S' || movimento=='Z' || movimento=='X')){
            printf("[ATENCAO] Esse movimento nao e possivel\n");}
        else if(coluna==9 && (movimento=='D' || movimento=='E' || movimento=='X')){
            printf("[ATENCAO] Esse movimento nao e possivel\n");}
        else if(movimento=='W' && !(linha==0)){ //cima
            if(tab[linha-1][coluna] == 2 || tab[linha-1][coluna] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha-1][coluna] == 7 && tab[linha][coluna] != 4){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 4 && !(tab[linha-1][coluna] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }else
                //contagem de pontos
                if(linha-1 == 0 && !(tab[linha-1][coluna] == 2 || tab[linha-1][coluna] == 1)){
                    ponto++;
                    tab[linha-1][coluna] = 4; //sapo vermelho preso
                    tab[linha][coluna] = 0;
                }
                else{ //essa parte serve para travar o sapo nas diagonais
                    tab[linha-1][coluna] = 2;
                    tab[linha][coluna] = 0;
                    if(tab[linha-2][coluna] == 1 || tab[linha-1][coluna-1] == 1 || 
                    tab[linha-1][coluna+1] == 1 || tab[linha-2][coluna] == 3 || 
                    tab[linha-1][coluna-1] == 3 || tab[linha-1][coluna+1] == 3){
                    tab[linha-1][coluna] = 4;
                    if(tab[linha-2][coluna] == 1){
                        tab[linha-2][coluna] = 3;
                    }else if(tab[linha-1][coluna-1] == 1){
                        tab[linha-1][coluna-1] = 3;
                    }else if(tab[linha+1][coluna+1] == 1){
                        tab[linha+1][coluna+1] = 3;
                    }
                    
                }
                }
            }
        else if(movimento=='S' && !(linha==9)){  //baixo
            if(tab[linha+1][coluna] == 2 || tab[linha+1][coluna] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha+1][coluna] == 7 && tab[linha][coluna] != 4){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 4 && !(tab[linha+1][coluna] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{ //essa parte serve para travar o sapo nas diagonais
                tab[linha+1][coluna] = 2;
                tab[linha][coluna] = 0;
                if(tab[linha+2][coluna] == 1 || tab[linha+1][coluna-1] == 1 || 
                    tab[linha+1][coluna+1] == 1 || tab[linha+2][coluna] == 3 || 
                    tab[linha+1][coluna-1] == 3 || tab[linha+1][coluna+1] == 3){
                        tab[linha+1][coluna] = 4;
                        if(tab[linha+2][coluna] == 1){
                            tab[linha+2][coluna] = 3;
                        }else if(tab[linha+1][coluna-1] == 1){
                            tab[linha+1][coluna-1] = 3;
                        }else if( tab[linha+1][coluna+1] == 1){
                            tab[linha+1][coluna+1] = 3;
                        }
                    }
            }
        }
        else if(movimento=='A' && !(coluna==0)){  //esquerda
            if( tab[linha][coluna-1] == 2 || tab[linha][coluna-1] == 1 || tab[linha][coluna-1] == 3 || tab[linha][coluna-1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha][coluna-1] == 7 && tab[linha][coluna] != 4){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 4 && !(tab[linha][coluna-1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{ //essa parte serve para travar o sapo nas diagonais
                tab[linha][coluna-1] = 2;
                tab[linha][coluna] = 0;
                if(tab[linha-1][coluna-1] == 1 || tab[linha+1][coluna-1] == 1 ||
                tab[linha][coluna-2] == 1 || tab[linha-1][coluna-1] == 3 || 
                tab[linha+1][coluna-1] == 3 || tab[linha][coluna-2] == 3){
                    tab[linha][coluna-1]  = 4;
                    if(tab[linha-1][coluna-1] == 1){
                        tab[linha-1][coluna-1] = 3;
                    }else if(tab[linha+1][coluna-1] == 1){
                        tab[linha+1][coluna-1] = 3;
                    }else if(tab[linha][coluna-2] == 1){
                        tab[linha][coluna-2] = 3;
                    }
                }
            }
        }
        else if(movimento=='D' && !(coluna==9)){  //direita
            if( tab[linha][coluna+1] == 2 || tab[linha][coluna+1] == 1 || tab[linha][coluna+1] == 3 || tab[linha][coluna+1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha][coluna+1] == 7 && tab[linha][coluna] != 4){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 4 && !(tab[linha][coluna+1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{ //essa parte serve para travar o sapo nas diagonais
                tab[linha][coluna+1] = 2;
                tab[linha][coluna] = 0;
                if(tab[linha-1][coluna+1] == 1 || tab[linha+1][coluna+1] == 1 || 
                tab[linha][coluna+2] == 1 || tab[linha-1][coluna+1] == 3 || 
                tab[linha+1][coluna+1] == 3 || tab[linha][coluna+2] == 3 ){
                    tab[linha][coluna+1]  = 4;
                    if(tab[linha-1][coluna+1] == 1){
                        tab[linha-1][coluna+1] = 3;
                    }else if(tab[linha+1][coluna+1] == 1){
                        tab[linha+1][coluna+1] = 3;
                    }else if(tab[linha][coluna+2] == 1){
                        tab[linha][coluna+2] = 3;
                    }
                }
            }
        }
        else if(movimento=='Q' && !(linha==0 || coluna==0)){  //superior esquerda
            if( tab[linha-1][coluna-1] == 2 || tab[linha-1][coluna-1] == 1 || tab[linha-1][coluna-1] == 3 || tab[linha-1][coluna-1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha-1][coluna-1] == 7 && tab[linha][coluna] != 4){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 4 && !(tab[linha-1][coluna-1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{
                //contagem de pontos
                if(linha-1 == 0 && !(tab[linha-1][coluna-1] == 2 || tab[linha-1][coluna-1] == 1)){
                    ponto++;
                    tab[linha-1][coluna-1] = 4; //sapo vermelho preso
                    tab[linha][coluna] = 0;
                }
                else{ //essa parte serve para travar o sapo nas diagonais
                    tab[linha-1][coluna-1] = 2;
                    tab[linha][coluna] = 0;
                    if(tab[linha-2][coluna-1] == 1 || tab[linha][coluna-1] == 1 ||
                    tab[linha-1][coluna-2] == 1 || tab[linha-1][coluna] == 1 || 
                    tab[linha-1][coluna-2] == 3 || tab[linha-1][coluna] == 3 ||
                    tab[linha-2][coluna-1] == 3 || tab[linha][coluna-1] == 3){
                    tab[linha-1][coluna-1]  = 4;
                    if(tab[linha-2][coluna-1] == 1){
                        tab[linha-2][coluna-1] = 3;
                    }else if(tab[linha][coluna-1] == 1){
                        tab[linha][coluna-1] = 3;
                    }else if(tab[linha-1][coluna-2] == 1){
                        tab[linha-1][coluna-2] = 3;
                    }else if(tab[linha-1][coluna] == 1){
                        tab[linha-1][coluna] = 3;}
                        
                }
            }
        }
        }
        else if(movimento=='E' && !(linha==0 || coluna==9)){  //superior direita
            if( tab[linha-1][coluna+1] == 2 || tab[linha-1][coluna+1] == 1 || tab[linha-1][coluna+1] == 3 || tab[linha-1][coluna+1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha-1][coluna+1] == 7 && tab[linha][coluna] != 4){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 4 && !(tab[linha-1][coluna+1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{
                //contagem de pontos
                if(linha-1 == 0 && !(tab[linha-1][coluna+1] == 2 || tab[linha-1][coluna+1] == 1)){
                    ponto++;
                    tab[linha-1][coluna+1] = 4; //sapo vermelho preso
                    tab[linha][coluna] = 0;
                }
                else{
                    tab[linha-1][coluna+1] = 2;
                    tab[linha][coluna] = 0;
                    if(tab[linha-2][coluna+1] == 1 || tab[linha][coluna+1] == 1 ||
                    tab[linha-1][coluna+2] == 1 || tab[linha-1][coluna] == 1 || 
                    tab[linha-1][coluna+2] == 3 || tab[linha-1][coluna] == 3 ||
                    tab[linha-2][coluna+1] == 3 || tab[linha][coluna+1] == 3){
                        tab[linha-1][coluna+1]  = 4;
                        if(tab[linha-2][coluna+1] == 1){
                            tab[linha-2][coluna+1] = 3;
                        }else if(tab[linha][coluna+1] == 1){
                            tab[linha][coluna+1] = 3;
                        }else if(tab[linha-1][coluna+2] == 1){
                            tab[linha-1][coluna+2] = 3;
                        }else if(tab[linha-1][coluna] == 1){
                            tab[linha-1][coluna] = 3;
                        }
                    }
                }
            }
        }                            
        else if(movimento=='Z' && !(coluna==0) && !(linha==9)){  //infeior esquerda
            if( tab[linha+1][coluna-1] == 2 || tab[linha+1][coluna-1] == 1 || tab[linha+1][coluna-1] == 3 || tab[linha+1][coluna-1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha+1][coluna-1] == 7 && tab[linha][coluna] != 4){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 4 && !(tab[linha+1][coluna-1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{  //essa parte serve para travar o sapo nas diagonais
                tab[linha+1][coluna-1] = 2;
                tab[linha][coluna] = 0;
                if(tab[linha+2][coluna-1] == 1 || tab[linha][coluna-1] == 1 ||
                    tab[linha+1][coluna-2] == 1 || tab[linha+1][coluna] == 1 ||
                    tab[linha+1][coluna-2] == 3 || tab[linha+1][coluna] == 3 ||
                    tab[linha+2][coluna-1] == 3 || tab[linha][coluna-1] == 3){
                        tab[linha+1][coluna-1]  = 4;
                        if(tab[linha+2][coluna-1] == 1){
                            tab[linha+2][coluna-1] = 3;
                        }else if(tab[linha][coluna-1] == 1){
                            tab[linha][coluna-1] = 3;
                        }else if(tab[linha+1][coluna-2] == 1){
                            tab[linha+1][coluna-2] = 3;
                        }else if(tab[linha+1][coluna] == 1){
                            tab[linha+1][coluna] = 3;
                        }
                }
            }
        }
        else if(movimento=='X' && !(linha==9 || coluna==9)){  //inferior direita
            if( tab[linha+1][coluna+1] == 2 || tab[linha+1][coluna+1] == 1 || tab[linha+1][coluna+1] == 3 || tab[linha+1][coluna+1] == 4){
                printf("\nEssa jogada nao e possivel!!\n");
            }
            else if(tab[linha+1][coluna+1] == 7 && tab[linha][coluna] != 4){
                printf("\n~~ O sapo caiu na lagoa e foi comido por jacares ~~\n");
                tab[linha][coluna] = 0;
            }
            else if(tab[linha][coluna] == 4 && !(tab[linha+1][coluna+1] == 7)){
                printf("\nEste Sapo esta IMOVEL!\n");
            }
            else{
                tab[linha+1][coluna+1] = 2;
                tab[linha][coluna] = 0;
                if(tab[linha+2][coluna+1] == 1 || tab[linha][coluna+1] == 1 ||
                    tab[linha+1][coluna+2] == 1 || tab[linha+1][coluna] == 1 ||
                    tab[linha+1][coluna+2] == 3 || tab[linha+1][coluna] == 3 ||
                    tab[linha+2][coluna+1] == 3 || tab[linha][coluna+1] == 3){
                        tab[linha+1][coluna-1]  = 4;
                        if(tab[linha+2][coluna+1] == 1){
                            tab[linha+2][coluna+1] = 3;
                        }else if(tab[linha][coluna+1] == 1){
                            tab[linha][coluna+1] = 3;
                        }else if(tab[linha+1][coluna+2] == 1){
                            tab[linha+1][coluna+2] = 3;
                        }else if(tab[linha+1][coluna] == 1){
                            tab[linha+1][coluna] = 3;
                        }
                        
                }
            }
        }
    }else{
        printf("\nEste Sapo esta IMOVEL!\n");}
    return ponto;}

int jogada(int tab[10][10], int ponto, int jogador, int finaldejogo){
    int linha, coluna;
    char lixo, movimento;
    printf("\n");
    mostra_tab(tab);
    printf("\nJOGADOR %d ESCOLHA UM SAPO INFORMANDO SUA...\nlinha:\n", jogador);
    scanf("%d", &linha);
    printf("E sua coluna:\n");
    scanf("%d", &coluna);
    if(jogador==1){
        if(finaldejogo==0){
            if(linha<=9 && linha>=0 && coluna<=9 && coluna>=0){ //verifica se a entrada da linha/coluna está no intervalo permitido
                if(tab[linha][coluna] != 1){  
                    if(tab[linha][coluna] == 3){  
                        printf("\nEste Sapo está IMOVEL!\n");
                    }else{
                        printf("Posicao invalida, perdeu a vez...\n");  //se 
                    }
                }
                else{
                    printf("\n---OBS. A LETRA DEVE SER MAIUSCULA!!---\n");
                    printf("\n[W].CIMA \n[S].BAIXO \n[A].ESQUERDA \n[D].DIREITA \n[Q].DIAGONAL SUPERIOR ESQUERDA \n[E].DIAGONAL SUPERIOR DIREITA \n[Z].DIAGONAL INFERIOR ESQUERDA \n[X].DIAGONAL INFERIOR DIREITA\nEscolha sua opcao de movimento:");
                    scanf("%c", &lixo);
                    scanf("%c", &movimento);
                    ponto = moverjogador1(tab, movimento, linha, coluna, ponto);
                }
            }else{
                printf("Posicao invalida, perdeu a vez...\n");
            }
            return ponto;}
    }else if(jogador==2){
        if(finaldejogo==0){
            if(linha<=9 && linha>=0 && coluna<=9 && coluna>=0){
                if(tab[linha][coluna] != 2 ){
                    if(tab[linha][coluna] == 4){
                        printf("\nEste Sapo está IMOVEL!\n");
                    }else{
                        printf("Posicao invalida, perdeu a vez...\n");
                    }
                }
                else{
                    printf("\n---OBS. A LETRA DEVE SER MAIUSCULA!!---\n");
                    printf("\n[W].CIMA \n[S].BAIXO \n[A].ESQUERDA \n[D].DIREITA \n[Q].DIAGONAL SUPERIOR ESQUERDA \n[E].DIAGONAL SUPERIOR DIREITA \n[Z].DIAGONAL INFERIOR ESQUERDA \n[X].DIAGONAL INFERIOR DIREITA\nEscolha sua opcao de movimento:");
                    scanf("%c", &lixo);
                    scanf("%c", &movimento);
                    ponto = moverjogador2(tab, movimento, linha, coluna, ponto);
                }
            }else{
                printf("Posicao invalida, perdeu a vez...\n");
            }
            return ponto;}
    }
}        

void theEnd(int tab[10][10], int pontodoazul, int pontodovermelho){
    printf("\n[JOGO FINALIZADO]\n");
    for (int k = 0; k < 10; k++) { //esse for é para numerar a tab
        if(k==0){
            printf("   ");}
        printf("%d ", k);}
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", i);
        for (int j = 0; j < 10; j++) {
            if (tab[i][j] == 1) { //1-BLUE VIVO 3-BLUE MORTO
                printf("|A");
            } else if (tab[i][j] == 2) { //2-RED VIVO 4-RED MORTO
                printf("|V");
            } else if (tab[i][j] == 3){
                printf("|A");
            } else if (tab[i][j] == 4){
                printf("|V");
            } else if (tab[i][j] == 7){ //vizualizar os lagos, obs 7 = x
                printf("|X");
            }
            else {
                printf("| ");
            }
        }
        printf("|\n");}
    //Qual jogador ganhou e mostra a pontuação
    if(pontodoazul>pontodovermelho){
        printf("\n[O JOGADOR VENCEDOR FOI: JOGADOR 1 - AZUL]\n");
        printf("Pontos Jogador 1: %d\nPontos Jogador 2: %d\n", pontodovermelho, pontodoazul);
    } else if (pontodovermelho>pontodoazul){
        printf("\n[O JOGADOR VENCEDOR FOI: JOGADOR 2 - VERMELHO]\n");
        printf("Pontos Jogador 1: %d\nPontos Jogador 2: %d\n", pontodovermelho, pontodoazul);
    }else{
        printf("\n[OCORREU EMPATE!!]\n");
        printf("Pontos Jogador 1: %d\nPontos Jogador 2: %d\n", pontodovermelho, pontodoazul);}
}

int main(){
    int tab[10][10]; //tab
    int inicio=1, pontodovermelho=0, pontodoazul=0, finaldejogo=0, finalizadojogo_do_azul=0, finalizadojogo_do_vermelho=0;
    cabecalho_do_jogo();
    criar(tab); //função que cria a tab que será o  tab
    Saposelagos(tab); //essa função posiciona os sapos e lagos 
    while (inicio==1){     //Inicia uma while infinita
        int conferencia=0, jogador=0;
        finaldejogo = conferir(tab, conferencia); //essa função confere se o jogo acabou
        conferencia=1;
        finalizadojogo_do_azul = conferir(tab, conferencia); //retorna 1 se acabou as jogadas do jogador azul
        conferencia=2;
        finalizadojogo_do_vermelho = conferir(tab, conferencia); //retorna 1 se acabou as jogadas do jogador vermelho
        if(finaldejogo==1){
            break; //finaliza o jogo
        }

        //vez do jogador 1
        if(finalizadojogo_do_azul==0){
            jogador=1;
            pontodoazul += jogada(tab, pontodoazul, jogador, finalizadojogo_do_azul); //retorna o ponto do jagador e soma com o valor ja acumulado na variavel
        }
        //vez do jogador 2
        if(finalizadojogo_do_vermelho==0){
            jogador=2;
            pontodovermelho += jogada(tab, pontodovermelho, jogador, finalizadojogo_do_vermelho);
        }
    }
    //finaliza o jogo! mostra a tab c/lagos
    theEnd(tab, pontodoazul, pontodovermelho);
    return 0;
}