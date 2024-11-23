
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>

typedef struct {
    int codigo_conta;
    char banco[50];
    char agencia[10];
    char numero_conta[20];
    char tipo_conta[20];
    double vl_saldo;
    double vl_limite;
    int status;
} Reg_conta;

typedef struct tipoitem *tipoapontador_conta;

typedef struct tipoitem {
    Reg_conta conteudo;
    tipoapontador_conta proximo;
} tipoitem;

typedef struct {
    tipoapontador_conta primeiro;
    tipoapontador_conta ultimo;
} tipolista_conta;

typedef struct Movimentacao {
    int sequencial;
    int codigoConta; 
    char dt_Movimento[11]; 
    char tp_movimentacao[15];
    char ds_favorecido[50]; 
    float vl_movimento; 
    float vl_saldo;  
} Reg_movimentacao;

typedef struct tipoitem_movimentacao *tipoapontador_movimentacao;

typedef struct tipoitem_movimentacao {
    Reg_movimentacao conteudo;
    tipoapontador_movimentacao proximo;
    tipoapontador_movimentacao anterior; 
} tipoitem_movimentacao;

typedef struct {
    tipoapontador_movimentacao primeiro;
    tipoapontador_movimentacao ultimo;
} tipolista_movimentacao;


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void tela() {
    system("cls");
    for (int linha = 1; linha < 29; linha++) {
        gotoxy(1, linha);
        printf("|");
        gotoxy(101, linha);
        printf("|");
    }
    gotoxy(1, 1);
    printf("+---------------------------------------------------------------------------------------------------+");
    gotoxy(1, 5);
    printf("+---------------------------------------------------------------------------------------------------+");
    gotoxy(1, 25);
    printf("+---------------------------------------------------------------------------------------------------+");
    gotoxy(1, 29);
    printf("+---------------------------------------------------------------------------------------------------+");
    gotoxy(2, 2);
    printf("UNICV");
    gotoxy(83, 2);
    printf("Estrutura de Dados");
    gotoxy(2, 3);
    printf("SISTEMA CONTROLE BANCARIO");
    gotoxy(86, 3);
    printf("Aluno: Lucas P.");
    gotoxy(86, 4);
    printf("Aluno: Jhonatan");
    gotoxy(2, 26);
    printf("MSG:");
}

void telaContaBancaria() {
    gotoxy(39, 4);
    printf("CONTA BANCARIA");
    gotoxy(5, 7);
    printf("Codigo da Conta..: ");
    gotoxy(5, 9);
    printf("1.Banco..........: ");
    gotoxy(5, 11);
    printf("2.Agencia........: ");
    gotoxy(5, 13);
    printf("3.Numero da Conta: ");
    gotoxy(5, 15);
    printf("4.Tipo de Conta..: ");
    gotoxy(5, 17);
    printf("5.Saldo..........: ");
    gotoxy(5, 19);
    printf("6.Limite.........: ");
    gotoxy(5, 21);
    printf("7.Status.........: ");
}

tipoapontador_conta pesquisarConta(tipolista_conta *L, int codigo) {
    tipoitem* item = L->primeiro;

    while (item != NULL) {
        if (item->conteudo.codigo_conta == codigo) {
            return item; // Retorna o ponteiro para o item encontrado
        }
        item = item->proximo;
    }
    return NULL; // Retorna NULL se nao encontrar
}

int contador(tipolista_conta *L) {
    int count = 0;
    tipoapontador_conta item = L->primeiro;

    while (item != NULL) {
        count++;
        item = item->proximo;
    }
    return count; // Retorna a contagem de contas
}

void CadastrarContaFinal(tipolista_conta *L) {
    int resposta = 0;
    do {
        Reg_conta* novaConta = (Reg_conta*)malloc(sizeof(Reg_conta)); // Aloca memoria para nova conta
        tipoitem* novoItem = NULL;
        

        do {
            tela();
            telaContaBancaria();
            gotoxy(34, 6);
            printf("CADASTRAR CONTA NO FINAL");
            gotoxy(67, 6);
            printf("              ");
            gotoxy(7, 26);
            printf("Digite 0 para sair\n");
            gotoxy(24, 7);
            scanf("%d", &novaConta->codigo_conta);

            if (novaConta->codigo_conta == 0) {
                gotoxy(7, 26);
                printf("Deseja cadastrar outra conta? (1-Sim / 2-Nao): ");
                scanf("%d", &resposta);
                if (resposta == 2) {
                    free(novaConta);  // Libera a memória alocada
                    return;  // Sai da função sem cadastrar a conta
                } else {
                    continue;  // Volta ao início do loop para continuar o cadastro
                }
            }

            // Verifica se o código da conta já existe
            novoItem = pesquisarConta(L, novaConta->codigo_conta);
            if (novoItem != NULL) {
                gotoxy(7, 26);
                printf("Codigo da conta ja cadastrado!\n");
                getch();  // Aguarda o usuário pressionar uma tecla
                // Não libera a memória aqui, pois vamos continuar com o loop
            }

        } while (novoItem != NULL);  // Continua pedindo o código até ser único

        if (novaConta->codigo_conta == 0) {
            continue;  // Se o código for 0, volta ao início do loop
        }

        // Coleta as informações da nova conta
        gotoxy(24, 9);
        getchar();  // Limpa o buffer de entrada
        fgets(novaConta->banco, 50, stdin);
        gotoxy(24, 11);
        fflush(stdin);
        fgets(novaConta->agencia, 10, stdin);
        gotoxy(24, 13);
        fflush(stdin);
        fgets(novaConta->numero_conta, 20, stdin);

        // Seleção do tipo de conta
        do {
            gotoxy(07, 26);
            printf("Utilizar: 1=Corrente / 2=Poupanca / 3=Cartao Credito");
            gotoxy(24, 15);
            fflush(stdin);
            fgets(novaConta->tipo_conta, 20, stdin);
            if (novaConta->tipo_conta[0] == '1') {
                gotoxy(24, 15);
                printf("1-Corrente");
            } else if (novaConta->tipo_conta[0] == '2') {
                gotoxy(24, 15);
                printf("2-Poupanca");
            } else if (novaConta->tipo_conta[0] == '3') {
                gotoxy(24, 15);
                printf("3-Cartao Credito");
            } else {
                gotoxy(7, 26);
                printf("                                                        ");
                gotoxy(7, 26);
                printf("Tipo de Conta invalido");
                getch();
                gotoxy(52, 15);
                printf("  ");
            }
        } while (novaConta->tipo_conta[0] != '1' && novaConta->tipo_conta[0] != '2' && novaConta->tipo_conta[0] != '3');

        gotoxy(24, 17);
        fflush(stdin);
        scanf("%lf", &novaConta->vl_saldo);
        gotoxy(24, 19);
        fflush(stdin);
        scanf("%lf", &novaConta->vl_limite);

        // Define o status como 1 (ativo) automaticamente
        novaConta->status = 1;

        // Exibe o valor de status automaticamente na tela
        gotoxy(24, 21);
        printf("%d", novaConta->status);

        // Pergunta ao usuário se deseja gravar os dados
        gotoxy(7, 26);
        printf("                                                           ");
        gotoxy(7, 26);
        printf("Deseja gravar os dados? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);

        if (resposta == 1) {
            tipoitem* novoItem = (tipoitem*)malloc(sizeof(tipoitem));
            novoItem->conteudo = *novaConta; // Atribui a conta ao novo item
            novoItem->proximo = NULL;

            // Adiciona o item no final da lista
            if (L->primeiro == NULL) {
                L->primeiro = novoItem;
                L->ultimo = novoItem;
            } else {
                L->ultimo->proximo = novoItem;
                L->ultimo = novoItem;
            }

            gotoxy(7, 27);
            printf("Conta cadastrada com sucesso!\n");

            
        }

        free(novaConta);  // Libera a memória de novaConta

        // Pergunta se deseja cadastrar outra conta
        gotoxy(7, 26);
        printf("                                                              ");
        gotoxy(7, 26);
        printf("Deseja cadastrar outra conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);
    } while (resposta == 1);  // Repete o loop se a resposta for 1 (Sim)
}



void CadastrarContaInicio(tipolista_conta *L) {
    int resposta = 0;

    do {
        Reg_conta* novaConta = (Reg_conta*)malloc(sizeof(Reg_conta));  // Aloca espaço para nova conta
        tipoitem* novoItem = NULL;  // Inicializa o ponteiro para item da lista

        // Loop para capturar o código da conta
        do {
            tela();
            telaContaBancaria();
            gotoxy(34, 4);
            printf("CADASTRAR CONTA NO INICIO");
            gotoxy(67, 6);
            printf("              ");
            gotoxy(7, 26);
            printf("Digite 0 para sair\n");
            gotoxy(24, 7);
            scanf("%d", &novaConta->codigo_conta);
            
            // Verifica se o usuário digitou 0 para sair
            if (novaConta->codigo_conta == 0) {
                // Pergunta se o usuário deseja cadastrar outra conta
                gotoxy(7, 26);
                printf("Deseja cadastrar outra conta? (1-Sim / 2-Nao): ");
                scanf("%d", &resposta);
                if (resposta == 2) {
                    free(novaConta);  // Libera a memória alocada
                    return;  // Sai da função sem cadastrar a conta
                } else {
                    continue;  // Volta para o início e começa o processo novamente
                }
            }

            novoItem = pesquisarConta(L, novaConta->codigo_conta);  // Verifica se o código já está cadastrado
            if (novoItem != NULL) {
                gotoxy(7, 26);
                printf("Codigo da conta ja cadastrado!\n");
                getch();  // Aguarda o usuário pressionar uma tecla para continuar
            }

        } while (novoItem != NULL); // Continua pedindo o código até ser válido

        // Se o código for válido, continua com o cadastro
        if (novaConta->codigo_conta == 0) {
            continue;  // Se o usuário digitou 0, ele retorna ao início do loop
        }

        // Coletando informações da nova conta
        gotoxy(24, 9);
        getchar(); 
        fgets(novaConta->banco, 50, stdin);
        gotoxy(24, 11);
        fflush(stdin);
        fgets(novaConta->agencia, 10, stdin);
        gotoxy(24, 13);
        fflush(stdin);
        fgets(novaConta->numero_conta, 20, stdin);

        do {
            gotoxy(07, 26);
            printf("Utilizar: 1=Corrente / 2=Poupanca / 3=Cartao Credito");
            gotoxy(24, 15);
            fflush(stdin);
            fgets(novaConta->tipo_conta, 20, stdin);
            if (novaConta->tipo_conta[0] == '1') {
                gotoxy(24, 15);
                printf("1-Corrente");
            } else if (novaConta->tipo_conta[0] == '2') {
                gotoxy(24, 15);
                printf("2-Poupanca");
            } else if (novaConta->tipo_conta[0] == '3') {
                gotoxy(24, 15);
                printf("3-Cartao Credito");
            } else {
                gotoxy(7, 26);
                printf("                                            ");
                gotoxy(7, 26);
                printf("Tipo de Conta invalido");
                getchar();  // Usar getchar em vez de getch
                gotoxy(52, 15);
                printf("  ");    
            }
        } while (novaConta->tipo_conta[0] != '1' && novaConta->tipo_conta[0] != '2' && novaConta->tipo_conta[0] != '3');
        
        gotoxy(24, 17);
        fflush(stdin);
        scanf("%lf", &novaConta->vl_saldo);
        gotoxy(24, 19);
        fflush(stdin);
        scanf("%lf", &novaConta->vl_limite);
        gotoxy(24, 21);

        novaConta->status = 1;

        gotoxy(24, 21);  
        printf("%d", novaConta->status);

        // Pergunta ao usuário se deseja gravar os dados
        gotoxy(7, 26);
        printf("                                                      ");
        gotoxy(7, 26);
        printf("Deseja gravar os dados? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);

        if (resposta == 1) {
            novoItem = (tipoitem*)malloc(sizeof(tipoitem));  // Aloca memória para novoItem
            novoItem->conteudo = *novaConta;  // Atribui o conteúdo da conta ao novo item
            novoItem->proximo = L->primeiro; // Aponta para o primeiro elemento

            // Atualiza a lista
            L->primeiro = novoItem;  // O novo item se torna o primeiro
            if (L->ultimo == NULL) {  // Se a lista estava vazia
                L->ultimo = novoItem; // O novo item é o último também
            }

            gotoxy(7, 27);
            printf("Conta cadastrada com sucesso!");
        }

        free(novaConta); // Libera a memória da conta temporária

        // Pergunta se deseja cadastrar outra conta
        gotoxy(7, 26);
        printf("                                                           ");
        gotoxy(7, 26);
        printf("Deseja cadastrar outra conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);
        gotoxy(7, 27);
      
    } while (resposta == 1);  // Se for 1, o loop continua para cadastrar outra conta
}

void CadastrarContaPosicao(tipolista_conta *L) {
    int resposta = 0;

    do {
        Reg_conta* novaConta = (Reg_conta*)malloc(sizeof(Reg_conta));
        tipoitem* novoItem = NULL;

        // Loop para garantir que o código da conta seja único
        do {
            tela();
            telaContaBancaria();
            gotoxy(34, 4);
            printf("CADASTRAR CONTA EM POSICAO");
            gotoxy(67, 6);
            printf("              ");
            gotoxy(7, 26);
            printf("Digite 0 para sair\n");
            gotoxy(24, 7);
            scanf("%d", &novaConta->codigo_conta);

            if (novaConta->codigo_conta == 0) {
                gotoxy(7, 26);
                printf("Deseja cadastrar outra conta? (1-Sim / 2-Nao): ");
                scanf("%d", &resposta);
                if (resposta == 2) {
                    free(novaConta);  // Libera a memória ao sair do cadastro
                    return; // Sai da função, encerrando o cadastro
                } else {
                    continue; // Continua o loop de cadastro
                }
            }

            novoItem = pesquisarConta(L, novaConta->codigo_conta);
            if (novoItem != NULL) {
                gotoxy(7, 26);
                printf("Codigo da conta ja cadastrado!");
                getch();  // Aguarda uma tecla para continuar
            }
        } while (novoItem != NULL);

        if (novaConta->codigo_conta == 0) {
            continue; // Se o código for 0, continua pedindo o código
        }

        // Coletando informações da nova conta
        gotoxy(24, 9);
        getchar(); 
        fgets(novaConta->banco, 50, stdin);
        gotoxy(24, 11);
        fflush(stdin); 
        fgets(novaConta->agencia, 10, stdin);
        gotoxy(24, 13);
        fflush(stdin); 
        fgets(novaConta->numero_conta, 20, stdin);

        // Tipo de conta
        do {
            gotoxy(07, 26);
            printf("Utilizar: 1=Corrente / 2=Poupanca / 3=Cartao Credito");
            gotoxy(24, 15);
            fflush(stdin); 
            fgets(novaConta->tipo_conta, 20, stdin);
            if (novaConta->tipo_conta[0] == '1') {
                gotoxy(24, 15);
                printf("1-Corrente");
            } else if (novaConta->tipo_conta[0] == '2') {
                gotoxy(24, 15);
                printf("2-Poupanca");
            } else if (novaConta->tipo_conta[0] == '3') {
                gotoxy(24, 15);
                printf("3-Cartao Credito");
            } else {
                gotoxy(7, 26);
                printf("                                            ");
                gotoxy(7, 26);
                printf("Tipo de Conta invalido");
                getch();
                gotoxy(52, 15);
                printf("  ");
            }
        } while (novaConta->tipo_conta[0] != '1' && novaConta->tipo_conta[0] != '2' && novaConta->tipo_conta[0] != '3');

        gotoxy(24, 17);
        fflush(stdin);
        scanf("%lf", &novaConta->vl_saldo);
        gotoxy(24, 19);
        fflush(stdin);
        scanf("%lf", &novaConta->vl_limite);

        // Define o status como 1 (ativo) automaticamente
        novaConta->status = 1;

        // Exibe o valor de status automaticamente na tela
        gotoxy(24, 21);
        printf("%d", novaConta->status);

        // Pergunta ao usuário em qual posição deseja inserir a conta
        gotoxy(7, 26);
        printf("                                                                            ");
        gotoxy(7, 26);
        printf("Digite qual a posicao: ");
        int posicao;
        scanf("%d", &posicao);

        // Pergunta ao usuário se deseja gravar os dados
        gotoxy(7, 26);
        printf("                                                                        ");
        gotoxy(7, 26);
        printf("Deseja gravar os dados? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);

        if (resposta == 1) {
            tipoitem* novoItem = (tipoitem*)malloc(sizeof(tipoitem));

            // Cópia da nova conta para o novo item
            novoItem->conteudo = *novaConta;

            // Inserção na lista conforme a posição escolhida
            if (posicao == 1) {  // Inserir no início
                novoItem->proximo = L->primeiro;
                L->primeiro = novoItem;
                if (L->ultimo == NULL) {
                    L->ultimo = novoItem; // Se a lista estava vazia
                }
            } else {
                tipoitem* temp = L->primeiro;
                int count = 1;

                // Verifica se a posição é válida
                while (temp != NULL && count < posicao - 1) {
                    temp = temp->proximo;
                    count++;
                }

                // Se temp for NULL ou a posição for maior que o número de itens, insere no final
                if (temp == NULL && count != posicao - 1) {
                    gotoxy(7, 27);
                    printf("Posicao invalida! A lista nao tem tantas contas.\n");
                    free(novoItem);  // Libera a memória do novo item
                    continue;  // Volta ao início do loop
                } else {
                    // Se a posição for válida, insere a conta no local especificado
                    novoItem->proximo = temp->proximo;
                    temp->proximo = novoItem;

                    // Se a conta foi inserida no final, atualiza o último item da lista
                    if (novoItem->proximo == NULL) {
                        L->ultimo = novoItem;
                    }
                }
            }

            gotoxy(7, 27);
            printf("Conta cadastrada com sucesso!");
        }

        // Libera a memória da conta temporária após a inserção
        free(novaConta);

        // Pergunta se deseja cadastrar outra conta
        gotoxy(7, 26);
        printf("Deseja cadastrar outra conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);
    } while (resposta == 1);  // Repete o loop se a resposta for 1 (Sim)
}




// Funcao para remover conta no final
void removerContaFinal(tipolista_conta *L) {
    int resposta = 0;
    do {
        tela();
        telaContaBancaria();
            gotoxy(34, 4);
            printf("REMOVER CONTA NO FINAL");
        // Verifica se a lista esta vazia
        if (L->primeiro == NULL) {
            gotoxy(7, 26);
            printf("Lista vazia! Nenhuma conta para remover.");
            getch();
            return;
        }

        // Percorrer a lista para encontrar o ultimo item (conta a ser removida)
        tipoitem *item = L->primeiro;
        tipoitem *anterior = NULL;
        // Encontra o ultimo item da lista
        while (item->proximo != NULL) {
            anterior = item;
            item = item->proximo;
        }

        // Exibir os dados da conta a ser removida
        gotoxy(24, 7);
        printf("%d", item->conteudo.codigo_conta);
        gotoxy(24, 9);
        printf("%s", item->conteudo.banco);
        gotoxy(24, 11);
        printf("%s", item->conteudo.agencia);
        gotoxy(24, 13);
        printf("%s", item->conteudo.numero_conta);
        gotoxy(24, 15);
        printf("%s", item->conteudo.tipo_conta);
        // Se o tipo da conta for 1, 2 ou 3, exibe o tipo de conta de forma mais detalhada
        if (item->conteudo.tipo_conta[0] == '1'){
        gotoxy(24, 15);
        printf("1-Corrente");
        } else if (item->conteudo.tipo_conta[0] == '2'){
        gotoxy(24, 15);
        printf("2-Poupanca");
        } else if (item->conteudo.tipo_conta[0] == '3'){
        gotoxy(24, 15);
        printf("3-Cartao Credito");
        } 
        gotoxy(24, 17);
        printf("%.2lf", item->conteudo.vl_saldo);
        gotoxy(24, 19);
        printf("%.2lf", item->conteudo.vl_limite);
         item->conteudo.status = 1;

        gotoxy(24, 21);  
        printf("%d", item->conteudo.status);

        // Perguntar ao usuario se deseja remover esta conta
        gotoxy(7, 26);
        printf("Deseja remover esta conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);

        // Se o usuario escolher 1 (Sim), remove a conta
        if (resposta == 1) {
            // Se a conta for a unica na lista
            if (anterior == NULL) {
                L->primeiro = NULL;
                L->ultimo = NULL;
            } else {
                // Remover o ultimo item
                anterior->proximo = NULL;
                L->ultimo = anterior;
            }

            free(item); // Libera a memoria da conta removida
            gotoxy(7, 26);
            printf("Conta removida com sucesso!");

        }

        // Perguntar se deseja remover outra conta
        gotoxy(7, 26);
        printf("Deseja remover outra conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);

    } while (resposta == 1); // Repete o processo se a resposta for 1 (Sim)
}

// Funcao remover conta no Inicio
void removerContaInicio(tipolista_conta *L){
    int resposta = 0;  

    do {
        tela();  
        telaContaBancaria();  
        gotoxy(34, 4);  
        printf("REMOVER CONTA NO INICIO");  

        // Verifica se a lista esta vazia
        if (L->primeiro == NULL) {
            gotoxy(7, 26);  
            printf("Lista vazia! Nenhuma conta para remover.");  
            getch();  
            return;  
        }

        tipoitem* item = L->primeiro;  // Inicia o ponteiro item apontando para o primeiro elemento da lista

        // Exibe as informacoes da conta a ser removida (primeiro item da lista)
        gotoxy(24, 7);  
        printf("%d", item->conteudo.codigo_conta);  
        gotoxy(24, 9);  
        printf("%s", item->conteudo.banco);  
        gotoxy(24, 11);  
        printf("%s", item->conteudo.agencia);  
        gotoxy(24, 13);  
        printf("%s", item->conteudo.numero_conta);  
        gotoxy(24, 15);  
        printf("%s", item->conteudo.tipo_conta);  

        // Se o tipo da conta for 1, 2 ou 3, exibe o tipo de conta de forma mais detalhada
        if (item->conteudo.tipo_conta[0] == '1') {
            gotoxy(24, 15);  
            printf("1-Corrente");
        } else if (item->conteudo.tipo_conta[0] == '2') {
            gotoxy(24, 15);  
            printf("2-Poupanca");
        } else if (item->conteudo.tipo_conta[0] == '3') {
            gotoxy(24, 15);  
            printf("3-Cartao Credito");
        }

        // Exibe o saldo e limite da conta
        gotoxy(24, 17);  
        printf("%.2lf", item->conteudo.vl_saldo);  
        gotoxy(24, 19);  
        printf("%.2lf", item->conteudo.vl_limite); 

        item->conteudo.status = 1;
        gotoxy(24, 21);  
        printf("%d", item->conteudo.status);  // Exibe o status da conta (1 = ativo)

        // Pergunta ao usuario se deseja remover esta conta
        gotoxy(7, 26);  
        printf("Deseja remover esta conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);  

        // Se o usuario quiser remover a conta (resposta 1)
        if (resposta == 1) {
            // Remove o primeiro item da lista
            L->primeiro = item->proximo;  

            // Se a lista ficou vazia, atualiza o ponteiro ultimo para NULL
            if (L->primeiro == NULL) {
                L->ultimo = NULL;  
            }

            // Libera a memoria ocupada pelo item removido
            free(item);  
            gotoxy(7, 26);  
            printf("Conta removida com sucesso!");  
        }

        // Pergunta se deseja remover outra conta
        gotoxy(7, 26);  
        printf("Deseja remover outra conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);  

    } while (resposta == 1);  // Repete o processo se a resposta for 1 (Sim)
}


//Funcao para remover conta em uma posicao
void removerContaPosicao(tipolista_conta *L) {
    int posicao, resposta; 

    do {
        tela();  
        telaContaBancaria();  
        gotoxy(34, 4);  
        printf("REMOVER CONTA EM POSICOES");  

        // Verifica se a lista esta vazia
        if (L->primeiro == NULL) {
            gotoxy(7, 26);  
            printf("Lista vazia! Nenhuma conta para remover.");
            getch();  
            return;  
        }

        // Solicita ao usuario a posicao da conta que ele deseja remover
        gotoxy(7, 26);  
        printf("Digite a posicao para remover: ");
        scanf("%d", &posicao);  

        // Verifica se a posicao e valida (não pode ser menor que 1)
        if (posicao < 1) {
            gotoxy(7, 26);  
            printf("Posição invalida!");
            getch();  
            return;  
        }

        tipoitem *item = L->primeiro;  // Ponteiro para percorrer a lista de contas
        tipoitem *anterior = NULL;  // Ponteiro para o item anterior ao que esta sendo removido

        // Percorre a lista ate encontrar a posicao desejada
        for (int contador = 1; contador < posicao; contador++) {
            anterior = item;  // Atualiza o ponteiro anterior
            item = item->proximo;  // Avanca para o proximo item

            // Verifica se a posicao fornecida e maior que o numero de elementos na lista
            if (item == NULL) {
                gotoxy(7, 26);  
                printf("Posicao Invalida!");
                getch();  
                return;  
            }
        }

        // Exibe as informacoes da conta que sera removida
        gotoxy(24, 7);  
        printf("%d", item->conteudo.codigo_conta);  
        gotoxy(24, 9);  
        printf("%s", item->conteudo.banco);  
        gotoxy(24, 11);  
        printf("%s", item->conteudo.agencia);  
        gotoxy(24, 13);  
        printf("%s", item->conteudo.numero_conta);  
        gotoxy(24, 15);  
        printf("%s", item->conteudo.tipo_conta);  

        // Se o tipo da conta for 1, 2 ou 3, exibe o tipo de conta de forma mais detalhada
        if (item->conteudo.tipo_conta[0] == '1') {
            gotoxy(24, 15);  
            printf("1-Corrente");
        } else if (item->conteudo.tipo_conta[0] == '2') {
            gotoxy(24, 15);  
            printf("2-Poupanca");
        } else if (item->conteudo.tipo_conta[0] == '3') {
            gotoxy(24, 15);  
            printf("3-Cartao Credito");
        }

        gotoxy(24, 17);  
        printf("%.2lf", item->conteudo.vl_saldo);  
        gotoxy(24, 19);  
        printf("%.2lf", item->conteudo.vl_limite);  
        item->conteudo.status = 1;  
        gotoxy(24, 21);  
        printf("%d", item->conteudo.status);  

        // Pergunta ao usuario se ele deseja remover a conta
        gotoxy(7, 26);  
        printf("Deseja remover esta conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta); 

        // Se o usuario desejar remover a conta (resposta = 1)
        if (resposta == 1) {
            // Caso a conta a ser removida seja a primeira da lista
            if (anterior == NULL) {
                L->primeiro = item->proximo;  // O ponteiro primeiro agora aponta para o proximo item

                // Se a lista estiver vazia apos remocao, atualiza o ponteiro ultimo para NULL
                if (L->primeiro == NULL) {
                    L->ultimo = NULL;  
                }
            } else {
                // Se a conta a ser removida nao for a primeira, ajusta o ponteiro proximo do item anterior
                anterior->proximo = item->proximo;

                // Se a conta removida for a ultima da lista, atualiza o ponteiro ultimo
                if (item->proximo == NULL) {
                    L->ultimo = anterior;  // O ultimo item passa a ser o anterior ao item removido
                }
            }

            free(item); 
            gotoxy(7, 26);  
            printf("                                                 ");  
            gotoxy(7, 26);  
            printf("Conta removida com sucesso!"); 
        } else {
            // Se o usuario nao desejar remover a conta
            gotoxy(7, 26);  
            printf("                                                 ");  
            gotoxy(7, 26);  
            printf("Remocao cancelada.");  
        }

        getch();  

        // Pergunta se o usuario deseja remover outra conta
        gotoxy(7, 26);  
        printf("Deseja remover outra conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);  

    } while (resposta == 1);  // Repete o processo se a resposta for 1 (Sim)

}

// Funcao para alterar conta bancaria
void alterarConta(tipolista_conta *L) {
    int codigo;     
    int campo;      
    int resposta;   

    tipoitem* item = L->primeiro;  // Ponteiro para percorrer a lista de contas

    // Verifica se a lista esta vazia
    if (L->primeiro == NULL) {
        gotoxy(7, 26);  
        printf("Lista vazia! Nenhuma conta para alterar.");
        getch();  
        return;   
    }

    tela();  
    telaContaBancaria();  
    gotoxy(39, 4);  
    printf("ALTERACAO DE CONTA");
    gotoxy(7, 26);  
    printf("Digite 0 para sair\n");
    gotoxy(24, 7);  
    scanf("%d", &codigo); 

    // Se o usuario digitar 0, a funcao e encerrada
    if (codigo == 0) {
        return;  
    }

    // Chama a funcao pesquisarConta para procurar a conta pelo codigo
    item = pesquisarConta(L, codigo);

    // Se a conta nao for encontrada, exibe uma mensagem e retorna
    if (item == NULL) {
        gotoxy(7, 26);  
        printf("Conta nao encontrada!");
        getch();  
        return;  
    }

    // Exibe as informacoes da conta encontrada
    gotoxy(24, 7);  
    printf("%d", item->conteudo.codigo_conta);  
    gotoxy(24, 9);  
    printf("%s", item->conteudo.banco); 
    gotoxy(24, 11);  
    printf("%s", item->conteudo.agencia);  
    gotoxy(24, 13);  
    printf("%s", item->conteudo.numero_conta);  
    gotoxy(24, 15);  
    printf("%s", item->conteudo.tipo_conta);  

    // Se o tipo da conta for 1, 2 ou 3, exibe o tipo de conta de forma mais detalhada
    if (item->conteudo.tipo_conta[0] == '1') {
        gotoxy(24, 15);  
        printf("1-Corrente");
    } else if (item->conteudo.tipo_conta[0] == '2') {
        gotoxy(24, 15);  
        printf("2-Poupanca");
    } else if (item->conteudo.tipo_conta[0] == '3') {
        gotoxy(24, 15);  
        printf("3-Cartao Credito");
    }

    gotoxy(24, 17);  
    printf("%.2lf", item->conteudo.vl_saldo);  
    gotoxy(24, 19);  
    printf("%.2lf", item->conteudo.vl_limite);  
    gotoxy(24, 21);  
    printf("%d", item->conteudo.status);  

    do {
        do {
            // Pergunta qual campo deseja alterar
            gotoxy(7, 26);  
            printf("                                                    ");
            gotoxy(7, 26);  
            printf("Deseja alterar qual campo? (0-sair): ");
            scanf("%d", &campo);  

            // Se o campo informado for invalido, repete a solicitacao
            if (campo < 0 || campo > 7) {
                gotoxy(7, 26);  
                printf("Campo invalido. Digite um valor entre 0 e 7.");
                getch();  
            }
        } while (campo < 0 || campo > 7);  // Enquanto o campo for invalido, solicita novamente

        // Se o campo escolhido for 0, sai do loop
        if (campo == 0) {
            break;  
        }

        // Solicita a alteracao do campo escolhido
        switch (campo) {
            case 1:
                gotoxy(24, 9);  
                printf("               ");  
                gotoxy(24, 9);  
                scanf("%s", item->conteudo.banco); 
                break;
            case 2:
                gotoxy(24, 11);  
                printf("                ");  
                gotoxy(24, 11);  
                scanf("%s", item->conteudo.agencia);  
                break;
            case 3:
                gotoxy(24, 13);  
                printf("                 ");  
                gotoxy(24, 13);  
                scanf("%s", item->conteudo.numero_conta);  
                break;
            case 4:
                gotoxy(24, 15);  
                printf("                 ");  
                gotoxy(24, 15);  
                scanf("%s", item->conteudo.tipo_conta);  
                break;
            case 5:
                gotoxy(24, 17);  
                printf("                  ");  
                gotoxy(24, 17);  
                scanf("%lf", &item->conteudo.vl_saldo); 
                break;
            case 6:
                gotoxy(24, 19);  
                printf("                  ");  
                gotoxy(24, 19);  
                scanf("%lf", &item->conteudo.vl_limite);  
                break;
            case 7:
                gotoxy(24, 21);  
                printf("                  ");  
                gotoxy(24, 21);  
                scanf("%d", &item->conteudo.status);  
                break;
        }

        // Pergunta ao usuario se deseja confirmar a alteracao
        do {
            gotoxy(7, 26);  
            printf("                                                            ");
            gotoxy(7, 26);  
            printf("Deseja confirmar a alteracao? (1-Sim / 2-Nao): ");
            scanf("%d", &resposta);  

            // Se a resposta nao for 1 ou 2, repete a solicitacao
            if (resposta != 1 && resposta != 2) {
                gotoxy(7, 26); 
                printf("Opcao invalida! Digite 1 para Sim ou 2 para Nao.");
                getch();  
            }
        } while (resposta != 1 && resposta != 2);  // Enquanto a resposta nao for valida, solicita novamente

        // Se a resposta for 1, confirma a alteração
        if (resposta == 1) {
            gotoxy(7, 27);  
            printf("                                                            ");
            gotoxy(7, 27);  
            printf("Alteracao realizada com sucesso!");  
        } else {
            gotoxy(7, 27);  
            printf("                                                            ");
            gotoxy(7, 27);  
            printf("Alteracao cancelada!");  // Exibe a mensagem de cancelamento
        }

        getch();  
        // Pergunta se o usuario deseja alterar outro campo
        gotoxy(7, 26);  
        printf("                                                            ");
        gotoxy(7, 26);  
        printf("Deseja alterar outro campo? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);  
    } while (resposta == 1);  // Repete o processo se a resposta for 1 (Sim)
}


void ConsultarTodasContaBancarias(tipolista_conta *L) {


    if (L->primeiro == NULL) {
        gotoxy(7, 26);
        printf("Lista esta vazia. Nenhuma conta para consultar.");
        getch();
        return;
    }

    tipoitem* item = L->primeiro;

    while (item != NULL) {
    tela();
    telaContaBancaria();
    gotoxy(39, 4);
    printf("CONSULTA DE CONTAS ");
    gotoxy(24, 7);
    printf("%d", item->conteudo.codigo_conta);
    gotoxy(24, 9);
    printf("%s", item->conteudo.banco);
    gotoxy(24, 11);
    printf("%s", item->conteudo.agencia);
    gotoxy(24, 13);
    printf("%s", item->conteudo.numero_conta);
    gotoxy(24, 15);
    printf("%s", item->conteudo.tipo_conta);
    if (item->conteudo.tipo_conta[0] == '1'){
    gotoxy(24, 15);
    printf("1-Corrente");
    } else if (item->conteudo.tipo_conta[0] == '2'){
    gotoxy(24, 15);
    printf("2-Poupanca");
    } else if (item->conteudo.tipo_conta[0] == '3'){
    gotoxy(24, 15);
    printf("3-Cartao credito");
    } 
    gotoxy(24, 17);
    printf("%.2lf", item->conteudo.vl_saldo);
    gotoxy(24, 19);
    printf("%.2lf", item->conteudo.vl_limite);

     item->conteudo.status = 1;

    gotoxy(24, 21);  
    printf("%d", item->conteudo.status);
    

    gotoxy(7, 26);
    printf("Pressione uma tecla para continuar...");
    getch();
    item = item->proximo;
    }
  
}

void ConsultarContaPorCodigo(tipolista_conta *L) {
    tipoitem* item;
    int codigo, encontrado, resposta;

    do {
        tela();  
        telaContaBancaria(); 
        gotoxy(34, 4);
        printf("CONSULTAR CONTAS POR POSICAO"); 

        gotoxy(7, 26);
        printf("Digite 0 para sair\n");

        // Solicitar código da conta
        gotoxy(5, 7);
        printf("Codigo da Conta..: ");
        scanf("%d", &codigo);

        // Se o código for 0, sai da função
        if (codigo == 0) {
            return;
        }

        // Inicializar a busca e resetar a variável encontrado
        encontrado = 0;
        item = L->primeiro;  // Resetar o ponteiro para o início da lista

        // Buscar pela conta com o codigo informado
        while (item != NULL) {
            if (item->conteudo.codigo_conta == codigo) {
                tela();  
                telaContaBancaria(); 

                // Exibe os dados da conta encontrada
                gotoxy(24, 7);
                printf("%d", item->conteudo.codigo_conta);
                gotoxy(24, 9);
                printf("%s", item->conteudo.banco);
                gotoxy(24, 11);
                printf("%s", item->conteudo.agencia);
                gotoxy(24, 13);
                printf("%s", item->conteudo.numero_conta);
                gotoxy(24, 15);
                printf("%s", item->conteudo.tipo_conta);

                if (item->conteudo.tipo_conta[0] == '1') {
                    gotoxy(24, 15);
                    printf("1-Corrente");
                } else if (item->conteudo.tipo_conta[0] == '2') {
                    gotoxy(24, 15);
                    printf("2-Poupanca");
                } else if (item->conteudo.tipo_conta[0] == '3') {
                    gotoxy(24, 15);
                    printf("3-Cartao Credito");
                }

                gotoxy(24, 17);
                printf("%.2lf", item->conteudo.vl_saldo);
                gotoxy(24, 19);
                printf("%.2lf", item->conteudo.vl_limite);
                item->conteudo.status = 1;

                gotoxy(24, 21);
                printf("%d", item->conteudo.status);

                encontrado = 1;
                break;  
            }
            item = item->proximo;
        }

        // Se a conta nao for encontrada
        if (!encontrado) {
            gotoxy(7, 27);
            printf("Conta com codigo %d nao encontrada.\n", codigo);
        }

        // Perguntar se o usuario quer consultar outra conta
        gotoxy(7, 26);
        printf("Deseja Consultar outra conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);

        // Caso a resposta seja invalida, repete a solicitacao
        while (resposta != 1 && resposta != 2) {
            gotoxy(7, 26);
            printf("Resposta invalida! Digite 1 para Sim ou 2 para Nao.\n");
            gotoxy(7, 26);
            printf("Deseja Consultar outra conta? (1-Sim / 2-Nao): ");
            scanf("%d", &resposta);
        }

    } while (resposta == 1);  // Continua o loop se a resposta for 1 (Sim)
}


void telaConsultaContas(){

gotoxy(39, 4);
printf("CONSULTA DE CONTAS");
gotoxy(2, 7);
printf("---------------------------------------------------------------------------------------------------");
gotoxy(2, 6);
printf("Cd");
gotoxy(5, 6);
printf("Banco");
gotoxy(25, 6);
printf("Agenc");
gotoxy(31, 6);
printf("Conta");
gotoxy(40, 6);
printf("Tipo Conta");
gotoxy(55, 6);
printf("Saldo");
gotoxy(67, 6);
printf("Limite");
gotoxy(78, 6);
printf("St");

}


void OrdenarContasPorCodigo(tipolista_conta *L) {
    if (L->primeiro == NULL) {
        gotoxy(7, 26);
        printf("Lista esta vazia. Nenhuma conta para consultar.");
        getch();
        return;
    }

    // Ordenar as contas pelo código da conta (ordem crescente)
    int trocado;
    tipoitem *item, *item2;
    Reg_conta temp;


    // Ordenação das contas por código (ordem crescente)
    do {
        trocado = 0;
        item = L->primeiro;

        while (item->proximo != NULL) {
            item2 = item->proximo;
            if (item->conteudo.codigo_conta > item2->conteudo.codigo_conta) {
                // Trocar os conteúdos das contas
                temp = item->conteudo;
                item->conteudo = item2->conteudo;
                item2->conteudo = temp;
                trocado = 1;
            }
            item = item->proximo;
        }
    } while (trocado);  // Continuar até que não haja mais trocas

    // Exibir cabeçalho da tela de consulta
    tela();
    telaConsultaContas();
    gotoxy(34, 4);
    printf("CONTAS ORDENADAS PRO CODIGO");

    // Variáveis para somar o saldo e limite
    double totalSaldo = 0.0;
    double totalLimite = 0.0;

    // Exibir as contas ordenadas
    item = L->primeiro;  // Resetar item para o início da lista

    int linha = 9;  // Iniciar na linha 9 para começar a exibir as contas abaixo do cabeçalho
    while (item != NULL) {
        gotoxy(2, linha);  // Ajuste a posição para cada item
        printf("%d", item->conteudo.codigo_conta);
        gotoxy(5, linha);
        printf("%s", item->conteudo.banco);
        gotoxy(25, linha);
        printf("%s", item->conteudo.agencia);
        gotoxy(31, linha);
        printf("%s", item->conteudo.numero_conta);
        gotoxy(40, linha);
        printf("%s", item->conteudo.tipo_conta);
        if (item->conteudo.tipo_conta[0] == '1'){
            gotoxy(40, linha);
            printf("Corrente");
        } else if (item->conteudo.tipo_conta[0] == '2'){
            gotoxy(40, linha);
            printf("Poupanca");
        } else if (item->conteudo.tipo_conta[0] == '3'){
            gotoxy(40, linha);
            printf("Cartao Credito");
        }      
        gotoxy(55, linha);
        printf("R$ %.2lf", item->conteudo.vl_saldo);
        gotoxy(67, linha);
        printf("R$ %.2lf", item->conteudo.vl_limite);
        gotoxy(78, linha);
        printf("%d", item->conteudo.status);

        // Atualizar a soma total dos saldos e limites
        totalSaldo += item->conteudo.vl_saldo;
        totalLimite += item->conteudo.vl_limite;

        // Atualiza o status da conta
        item->conteudo.status = 1;

        item = item->proximo;  // Avançar para o próximo item
        linha++;  // Incrementar a linha para a próxima conta
    }

    // Exibir a soma total dos saldos e limites após a exibição das contas
    linha++;  // Pular uma linha para exibir os totais
    gotoxy(43, linha + 1);  
    printf("Saldo Total: R$ %.2lf R$ %.2lf ", totalSaldo, totalLimite);

    gotoxy(7, 26);
    printf("Pressione uma tecla para continuar...");
    getch();
}




// Funcao Ordenar contas bancarias por ordem alfabetica
void OrdenarContasPorAlfabeto(tipolista_conta *L) {
    if (L->primeiro == NULL) {
        gotoxy(7, 26);
        printf("Lista esta vazia. Nenhuma conta para consultar.");
        getch();
        return;
    }

    // Ordenar as contas por ordem alfabetica 
    int trocado;
    tipoitem *item, *item2;
    Reg_conta temp;

    // Ordenação por nome do banco (alfabetica)
    do {
        trocado = 0;
        item = L->primeiro;

        while (item != NULL && item->proximo != NULL) {
            item2 = item->proximo;
            if (strcmp(item->conteudo.banco, item2->conteudo.banco) > 0) {
                // Trocar os conteudos das contas
                temp = item->conteudo;
                item->conteudo = item2->conteudo;
                item2->conteudo = temp;
                trocado = 1;
            }
            item = item->proximo;
        }
    } while (trocado); 

    // Exibir cabecalho da tela de consulta
    tela();
    telaConsultaContas();
    gotoxy(34, 4);
    printf("CONTAS ORDENADAS EM ONDER ALFABETICA");

    // Variaveis para somar o saldo e limite
    double totalSaldo = 0.0;
    double totalLimite = 0.0;

    // Exibir as contas ordenadas
    int linha = 9;
    item = L->primeiro;
    while (item != NULL) {
        gotoxy(2, linha);  
        printf("%d", item->conteudo.codigo_conta);
        gotoxy(5, linha);
        printf("%s", item->conteudo.banco);
        gotoxy(25, linha);
        printf("%s", item->conteudo.agencia);
        gotoxy(31, linha);
        printf("%s", item->conteudo.numero_conta);
        gotoxy(40, linha);
        printf("%s", item->conteudo.tipo_conta);
        if (item->conteudo.tipo_conta[0] == '1'){
            gotoxy(40, linha);
            printf("Corrente");
        } else if (item->conteudo.tipo_conta[0] == '2'){
            gotoxy(40, linha);
            printf("Poupanca");
        } else if (item->conteudo.tipo_conta[0] == '3'){
            gotoxy(40, linha);
            printf("Cartao Credito");
        } 
        gotoxy(55, linha);
        printf("R$ %.2lf", item->conteudo.vl_saldo);
        gotoxy(67, linha);
        printf("R$ %.2lf", item->conteudo.vl_limite);
        gotoxy(78, linha);
        printf("%d", item->conteudo.status);

        // Atualizar a soma total dos saldos e limites
        totalSaldo += item->conteudo.vl_saldo;
        totalLimite += item->conteudo.vl_limite;

        // Atualiza o status da conta
        item->conteudo.status = 1;

        item = item->proximo;
        linha ++;
    }

     // Exibir a soma total dos saldos e limites apos a exibicao das contas
    linha++;  
    gotoxy(43, linha + 1);  
    printf("Saldo Total: R$ %.2lf R$ %.2lf ", totalSaldo, totalLimite);

    gotoxy(7, 26);
    printf("Pressione uma tecla para continuar...");
    getch();
}

void ConsultarContas(tipolista_conta *L) {
    int consultaOpcao;
    do {
        tela();
        gotoxy(35, 4);
        printf("CONSULTA DE CONTAS BANCARIAS\n");
        gotoxy(33, 10);
        printf("1. Consulta Geral Contas Bancarias\n");
        gotoxy(33, 12);
        printf("2. Consultar por Codigo Contas Bancarias\n");
        gotoxy(33, 14);
        printf("3. Consulta Ordem Codigo Contas Bancarias\n");
        gotoxy(33, 16);
        printf("4. Consultar Ordem Alfabetica Contas Bancarias\n");
        gotoxy(33, 18);
        printf("5. Retornar ao Menu Anterior\n");
        gotoxy(7, 26);
        printf("Escolha uma opcao: ");
        scanf("%d", &consultaOpcao);

        switch (consultaOpcao) {
            case 1:
                ConsultarTodasContaBancarias(L);
                break;
            case 2:
                ConsultarContaPorCodigo(L);
                break;
            case 3:
                OrdenarContasPorCodigo(L);
                break;
            case 4:
                OrdenarContasPorAlfabeto(L);
                break;
            case 5:
                break;  
            default:
                gotoxy(7, 26);
                printf("Opcao invalida!\n");
                getch();  
        }
    } while (consultaOpcao != 5);  
}



// Movimentação ---------------------------------------------------------------------------------------------------------------------

void TelaCadastroMovimentacao(){

    gotoxy(39, 4);
    printf("CADASTRAR MOVIMENTACAO BANCARIA");
    gotoxy(16, 8);
    printf("Sequencia Movimentacao.:");
    gotoxy(16, 9);
    printf("Codigo da Conta........:");
    gotoxy(16, 10);
    printf("Banco..................:");
    gotoxy(16, 11);
    printf("Agencia................:");
    gotoxy(16, 12);
    printf("Numero da Conta........:");
    gotoxy(16, 13);
    printf("Tipo da Conta..........:");
    gotoxy(16, 14);
    printf("Saldo..................:");
    gotoxy(16, 15);
    printf("Limite.................:");
    gotoxy(16, 16);
    printf("Total Saldo + Limite...:");
    gotoxy(2, 17);
    printf("---------------------------------------------------------------------------------------------------");
    gotoxy(16, 18);
    printf("1-Data Movimentacao....:");
    gotoxy(16, 19);
    printf("2-Tipo Movimentacao....:");
    gotoxy(16, 20);
    printf("3-Favorecido...........:");
    gotoxy(16, 21);
    printf("4-Valor Movimentacao...:");
    gotoxy(16, 22);
    printf("5-Novo Saldo...........:");
}

void Tela_Transacao(){

gotoxy(35, 4);
printf("TRANSFERENCIA ENTRE CONTAS BANCARIAS");
gotoxy(2, 9);
printf("-----------C O N T A  O R I G E M------------------+---------C O N T A  D E S T I N O--------------");
gotoxy(12, 10);
printf("Conta de origem:                         | Conta de destino:");
gotoxy(12, 11);
printf("Banco..........:                         | Banco...........:");
gotoxy(12, 12);
printf("Agencia........:                         | Agencia.........:");
gotoxy(12, 13);
printf("Numero da conta:                         | Numero da conta.:");
gotoxy(12, 14);
printf("Tipo da Conta..:                         | Tipo da Conta...:");
gotoxy(12, 15);
printf("Saldo..........:                         | Saldo...........:");
gotoxy(12, 16);
printf("Limite.........:                         | Limite..........:");
gotoxy(12, 17);
printf("Saldo + Limite.:                         | Saldo + Limite..:");
gotoxy(12, 18);
printf("Novo Saldo.....:                         | Novo Saldo......:");
gotoxy(2, 19);
printf("---------------------------------------------------+-----------------------------------------------");
gotoxy(27, 20);
printf("Valor a Ser Transferido:");
gotoxy(27, 21);
printf("Data Da Transferencia..:");

}

void TelaConsultaMovimentacao(){

gotoxy(39, 4);
printf("LISTA MOVIMENTACAOS BANCARIAS");
gotoxy(2, 7);
printf("---------------------------------------------------------------------------------------------------");
gotoxy(2, 6);
printf("Codigo:");
gotoxy(2, 8);
printf("Dt.Movim");
gotoxy(2, 9);
printf("---------------------------------------------------------------------------------------------------");
gotoxy(13, 8);
printf("Favorecido");
gotoxy(43, 8);
printf("TpMovim");
gotoxy(57, 8);
printf("Vl.Movim");
gotoxy(69, 8);
printf("Saldo");

}

// Função para receber a data do movimento (formato dd/mm/aaaa)
char* le_movimento_data() {
    static char data[11];
    gotoxy(41, 18);
    scanf("%s", data);
    return data;
}

// Função para receber o tipo de movimento (Débito ou Crédito)
char* le_movimento_tipo() {
    static char tipo[15];
    gotoxy(41, 19);
    scanf("%s", tipo);
    return tipo;
}

// Função para receber o favorecido do movimento
char* le_movimento_favorecido() {
    static char favorecido[50];
    gotoxy(41, 20);
    scanf(" %s", favorecido);
    return favorecido;
}

// Função para receber o valor do movimento
float le_movimento_valor() {
    float valor;
    gotoxy(41, 21);
    scanf("%f", &valor);
    return valor;
}

// Função para adicionar uma movimentação na lista
void adicionarMovimentacao(tipolista_movimentacao *M, Reg_movimentacao movimento) {
    tipoapontador_movimentacao novo = (tipoapontador_movimentacao)malloc(sizeof(tipoitem_movimentacao));
    novo->conteudo = movimento;
    novo->proximo = NULL;
    novo->anterior = M->ultimo;

    if (M->ultimo == NULL) {
        M->primeiro = novo;
    } else {
        M->ultimo->proximo = novo;
    }
    M->ultimo = novo;
}

// Função para cadastrar movimentação
void cadastroMovimentacao( tipolista_movimentacao *M) {
    Reg_conta conta;
    Reg_movimentacao movimento;
    tipoapontador_conta aux2;
    int resposta;

    do {
        do {
            
            tela(); 
            TelaCadastroMovimentacao();
            if (M->primeiro == NULL) {
                movimento.sequencial = 1;
            } else {
                movimento.sequencial = M->ultimo->conteudo.sequencial + 1;
            }
            gotoxy(40, 8);
            printf(" %d", movimento.sequencial);
            gotoxy(7, 26);
            printf("Digite 0 para sair.");
            gotoxy(41, 9);
            scanf("%d", &conta.codigo_conta);
            getch();

            aux2 = NULL; 
            if (aux2 == NULL && conta.codigo_conta != 0) {
                gotoxy(7, 26);
                printf("Conta Bancaria nao Cadastrada!");
                getch();
            }
        } while (aux2 == NULL && conta.codigo_conta != 0);

        if (conta.codigo_conta != 0) {
            conta = aux2->conteudo;
            gotoxy(41, 10);
            printf("%s", conta.banco);
            gotoxy(41, 11);
            printf("%s", conta.agencia);
            gotoxy(41, 12);
            printf("%s", conta.numero_conta);
            gotoxy(41, 13);
            printf("%s", conta.tipo_conta);
            gotoxy(41, 14);
            printf("R$%9.2f", conta.vl_saldo);
            gotoxy(41, 15);
            printf("R$%9.2f", conta.vl_limite);
            gotoxy(41, 16);
            printf("R$%9.2f", conta.vl_saldo + conta.vl_limite);
        }

        movimento.codigoConta = conta.codigo_conta;
        strcpy(movimento.dt_Movimento, le_movimento_data()); 
        strcpy(movimento.tp_movimentacao, le_movimento_tipo()); 
        strcpy(movimento.ds_favorecido, le_movimento_favorecido());
        movimento.vl_movimento = le_movimento_valor();

        if (strcmp(movimento.tp_movimentacao, "Debito") == 0) {
            movimento.vl_saldo = conta.vl_saldo - movimento.vl_movimento;
            conta.vl_saldo = conta.vl_saldo - movimento.vl_movimento;
        } else if (strcmp(movimento.tp_movimentacao, "Credito") == 0) {
            movimento.vl_saldo = conta.vl_saldo + movimento.vl_movimento;
            conta.vl_saldo = conta.vl_saldo + movimento.vl_movimento;
        }

        gotoxy(41, 22);
        printf("R$%9.2f", movimento.vl_saldo);
        gotoxy(7, 26);
        printf("Confirma Gravacao do Movimento (1-Sim / 2-Nao)? ");
        scanf("%d", &resposta);
        if (resposta == 1) {
            
            adicionarMovimentacao(M, movimento);
            gotoxy(7, 26);
            printf("Movimento gravado com sucesso!");
            getch();
        }
    } while (conta.codigo_conta != 0);
}

/*void transferir(tipolista_conta *L, tipolista_movimentacao *M, int codigoContaOrigem, int codigoContaDestino, float valor) {
    
    tipoapontador_conta contaOrigem = pesquisarConta(L, codigoContaOrigem);
    tipoapontador_conta contaDestino = pesquisarConta(L, codigoContaDestino);

    if (contaOrigem != NULL && contaDestino != NULL) {
        if (contaOrigem->conteudo.vl_saldo >= valor) {
            // Realizando o débito na conta de origem
            contaOrigem->conteudo.vl_saldo -= valor;
            registrarMovimentacao(M, codigoContaOrigem, 'D', valor, contaOrigem->conteudo.vl_saldo);

            // Realizando o crédito na conta de destino
            contaDestino->conteudo.vl_saldo += valor;
            registrarMovimentacao(M, codigoContaDestino, 'C', valor, contaDestino->conteudo.vl_saldo);

            gotoxy(7, 27);
            printf("Transferencia realizada com sucesso!");
        } else {
            gotoxy(7, 27);
            printf("Saldo insuficiente para transferencia!");
        }
    } else {
        gotoxy(7, 27);
        printf("Uma ou ambas as contas nao foram encontradas.");
    }
}

void consultarMovimentacoes(tipolista_movimentacao *L, int codigoConta) {
    tipoapontador_movimentacao item = L->primeiro;
    int found = 0;

    while (item != NULL) {
        if (item->conteudo.codigoConta == codigoConta) {
            found = 1;
            gotoxy(7, 27);
            printf("Seq: %d  Data: %s  Tipo: %c  Valor: %.2f  Saldo: %.2f",
                   item->conteudo.sequencial, item->conteudo.dt_Movimento,
                   item->conteudo.tp_movimentacao, item->conteudo.vl_movimento,
                   item->conteudo.vl_saldo);
            gotoxy(7, 28);
        }
        item = item->proximo;
    }

    if (!found) {
        gotoxy(7, 27);
        printf("Nao ha movimentacoes para esta conta.");
    }
}
*/

// Funcao principal
int main() {
    tipolista_conta L = {NULL, NULL};
    tipolista_movimentacao M = {NULL, NULL};
    int opcao;

//  Repete ate que a opcao de sair seja escolhida
    do {
        tela();
        gotoxy(35, 6);
        printf("MENU PRINCIPAL\n");
        gotoxy(33, 13);
        printf("1. Cadastro de Contas\n");
        gotoxy(33, 15);
        printf("2. Movimentacao Financeira\n");
        gotoxy(33, 17);
        printf("3. Sair\n");
        gotoxy(7, 26);
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Inicia switch para processar a opcao escolhida
        switch (opcao) {

            // Cadastro de Contas
            case 1: {
                int subOpcao;
        do{       
                tela();
                gotoxy(35, 6);
                printf("CADASTRO DE CONTAS\n");
                gotoxy(33, 11);
                printf("1. Cadastrar Contas Bancarias no Final\n");
                gotoxy(33, 12);
                printf("2. Cadastrar Contas Bancarias no Inicio\n");
                gotoxy(33, 13);
                printf("3. Cadastrar Contas Bancarias na Posicao\n");
                gotoxy(33, 14);
                printf("4. Remover Contas Bancarias no Final\n");
                gotoxy(33, 15);
                printf("5. Remover Contas Bancarias no Inicio\n");
                gotoxy(33, 16);
                printf("6. Remover Contas Bancarias na Posicao\n");
                gotoxy(33, 17);
                printf("7. Alteracao de Contas Bancarias\n");
                gotoxy(33, 18);
                printf("8. Consultar Contas Bancarias\n");
                gotoxy(33, 19);
                printf("9. Retornar ao Menu Anterior\n");
                gotoxy(7, 26);
                printf("Escolha uma opcao: ");
                scanf("%d", &subOpcao);

                // Inicia switch para processar a sub-opcao escolhida
                switch (subOpcao) {
                    case 1:
                        CadastrarContaFinal(&L);
                        break;
                    case 2:
                        CadastrarContaInicio(&L);
                        break;
                    case 3:
                        CadastrarContaPosicao(&L);
                        break;
                    case 4:
                        removerContaFinal(&L);
                        break;
                    case 5:
                        removerContaInicio(&L);
                         break;
                    case 6:
                        removerContaPosicao(&L);
                        break;
                    case 7:
                        alterarConta(&L);
                        break;
                    case 8:
                        ConsultarContas(&L);
                        break;
                    case 9:
                        break;
                    default:
                        gotoxy(7, 26); 
                        printf("Opcao invalida!\n");
                        getch();
                }
        }while (subOpcao != 9);
                break;
            }

            // Movimentacao Financeira
            case 2: {
                int movOpcao;
            do{
                
                tela();
                gotoxy(35, 6);
                printf("TELA DE MOVIMENTACAO FINANCEIRA:\n");
                gotoxy(33, 12);
                printf("1. Movimentacao de Debito e Credito\n");
                gotoxy(33, 14);
                printf("2. Transferencia entre Contas Bancarias\n");
                gotoxy(33, 16);
                printf("3. Consulta Movimentacao Bancarias\n");
                gotoxy(33, 18);
                printf("4. Retornar ao Menu Anterior\n");
                gotoxy(7, 26);
                printf("Escolha uma opcao: ");
                scanf("%d", &movOpcao);

                // Inicia switch para processar a opcao de movimentacao
                switch (movOpcao) {
                    case 1:
                       cadastroMovimentacao(&M);
                        break;
                    case 2:
                        
                        break;
                    case 3:
                        
                        break;
                    case 4:
                        break;
                    default:
                        gotoxy(7, 26);
                        printf("Opcao invalida!\n");
                        getch();
                }
            }while (movOpcao !=4);
                break;
            }
            case 3:
                gotoxy(7, 26);
                printf("Saindo do sistema...\n");
                break;
            default:
                gotoxy(7, 26);
                printf("Opcao invalida!\n");
                getch();
        }
    } while (opcao != 3);

    return 0;
}


/*
 // Incluindo a biblioteca
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>

#include "funcoes.h"



// Define uma estrutura chamada 'Conta' para representar uma conta bancaria e 
typedef struct Conta {
    int codigo_conta;
    char banco[50];
    char agencia[10];
    char numero_conta[20];
    char tipo_conta[10];
    double vl_saldo;
    double vl_limite;
    char status[10];
} Conta;

// Declara um tipo de ponteiro 'tipoapontador' para 'tipoitem'.
typedef struct tipoitem *tipoapontador;

// Define uma estrutura chamada 'tipoitem' para os nós da lista encadeada.
typedef struct tipoitem {
    Conta conteudo;
    tipoapontador proximo;
} tipoitem;

// Define uma estrutura para uma lista encadeada que contem nos do tipo 'tipoitem'.
typedef struct {
    tipoapontador primeiro;
    tipoapontador ultimo;
} tipolista;

 // Define uma estrutura chamada 'Movimentacao' para registros de transacaes.
typedef struct Movimentacao {
    int sequencial;
    int codigoConta;
    char dt_Movimento[11];
    char tp_movimentacao;
    float vl_movimento;
    float vl_saldo;
    struct Movimentacao* prox;
} Movimentacao;

tipolista listaContas = {NULL, NULL}; // Inicializa a lista encadeada
Movimentacao* listaMovimentacoes = NULL;

// Move o cursor para a posicao (x, y) na tela do console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Funcao que desenha a tela inicial do sistema
void tela() {
    system("cls");
    for (int linha = 1; linha < 29; linha++) {
        gotoxy(1, linha);
        printf("|");
        gotoxy(101, linha);
        printf("|");
    }
    gotoxy(1, 1);
    printf("+---------------------------------------------------------------------------------------------------+");
    gotoxy(1, 5);
    printf("+---------------------------------------------------------------------------------------------------+");
    gotoxy(1, 25);
    printf("+---------------------------------------------------------------------------------------------------+");
    gotoxy(1, 29);
    printf("+---------------------------------------------------------------------------------------------------+");
    gotoxy(2, 2);
    printf("UNICV");
    gotoxy(83, 2);
    printf("Estrutura de Dados");
    gotoxy(2, 3);
    printf("SISTEMA CONTROLE BANCARIO");
    gotoxy(86, 3);
    printf("Aluno: Lucas P.");
    gotoxy(86, 4);
    printf("Aluno: Jhonatan");
    gotoxy(2, 26);
    printf("MSG:");
}

// Funcao que exibe o formulario para dados da conta bancaria
void telaContaBancaria() {
    gotoxy(5, 7);
    printf("Codigo da Conta..: ");
    gotoxy(5, 9);
    printf("Banco............: ");
    gotoxy(5, 11);
    printf("Agencia..........: ");
    gotoxy(5, 13);
    printf("Numero da Conta..: ");
    gotoxy(5, 15);
    printf("Tipo de Conta....: ");
    gotoxy(5, 17);
    printf("Saldo............: ");
    gotoxy(5, 19);
    printf("Limite...........: ");
    gotoxy(5, 21);
    printf("Status...........: ");
}

// Funcao para pesquisar uma conta na lista de contas
tipoapontador pesquisarConta(int codigo) {
    tipoitem* item = listaContas.primeiro;

    while (item != NULL) {
        if (item->conteudo.codigo_conta == codigo) {
            return item; 
        }
        item = item->proximo;
    }
    return NULL; 
}

// Funcao que conta o numero total de contas na lista
int contador() {
    int count = 0;
    tipoapontador item = listaContas.primeiro;

    while (item != NULL) {
        count++;
        item = item->proximo;
    }
    return count;
}

// Funcao para cadastrar uma conta no Final
void CadastrarContaFinal() {
    int resposta = 0;

    do {
        Conta* novaConta = (Conta*)malloc(sizeof(Conta));
    tipoitem* item;
       // Loop para garantir que o codigo da conta seja unico
        do {
            tela();
            telaContaBancaria();
            gotoxy(35, 6);
            printf("CADASTRAR FUNCIONARIO NO FINAL");
            gotoxy(67, 6);
            printf("              ");
            gotoxy(24, 7);
            scanf("%d", &novaConta->codigo_conta);
            item = pesquisarConta(novaConta->codigo_conta);
            if (item != NULL) {
                gotoxy(7, 26);
                printf("Codigo da conta ja cadastrado!\n");
                free(novaConta);
                getch();
            }
        } while (item != NULL);

// Le os dados da conta do usuario
        gotoxy(24, 9);
        getchar();
        fgets(novaConta->banco, 50, stdin);
        gotoxy(24, 11);
        fflush(stdin);
        fgets(novaConta->agencia, 10, stdin);
        gotoxy(24, 13);
        fflush(stdin);
        fgets(novaConta->numero_conta, 20, stdin);
        gotoxy(24, 15);
        fflush(stdin);
        fgets(novaConta->tipo_conta, 10, stdin);
        gotoxy(24, 17);
        fflush(stdin);
        scanf("%lf" , &novaConta->vl_saldo);
        gotoxy(24, 19);
        fflush(stdin);
        scanf("%lf", &novaConta->vl_limite);
        gotoxy(24, 21);
        fflush(stdin);
        fgets(novaConta->status, 10, stdin);

        // Pergunta ao usuario se deseja gravar os dados
        gotoxy(7, 26);
        printf("Deseja gravar os dados? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);

        if (resposta == 1) {
            tipoitem* novoItem = (tipoitem*)malloc(sizeof(tipoitem));
            novoItem->conteudo = *novaConta; 
            novoItem->proximo = NULL;

            if (listaContas.primeiro == NULL) {
                listaContas.primeiro = novoItem;
                listaContas.ultimo = novoItem;
            } else {
                listaContas.ultimo->proximo = novoItem;
                listaContas.ultimo = novoItem;
            }

            gotoxy(7, 27);
            printf("Conta cadastrada com sucesso!\n");
        }

        free(novaConta); 

        // Pergunta se deseja cadastrar outra conta
        gotoxy(7, 26);
        printf("Deseja cadastrar outra conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);
    } while (resposta == 1);
}

// Funcao para cadastrar no Inicio
void CadastrarContaInicio() {
    int resposta = 0;
    do {
        Conta* novaConta = (Conta*)malloc(sizeof(Conta));
        tipoitem* novoItem = (tipoitem*)malloc(sizeof(tipoitem)); 
        tipoitem* item;

        do {
            tela();
            telaContaBancaria();
            gotoxy(35, 6);
            printf("CADASTRAR CONTA NO INICIO");
            gotoxy(67, 6);
            printf("              ");
            gotoxy(24, 7);
            scanf("%d", &novaConta->codigo_conta);
            item = pesquisarConta(novaConta->codigo_conta);
            if (item != NULL) {
                gotoxy(7, 26);
                printf("Codigo da conta ja cadastrado!\n");
                free(novaConta);
                getch();
                
            }
        } while (item != NULL); 

        // Coletando informacoes da nova conta
        gotoxy(24, 9);
        getchar();
        fgets(novaConta->banco, 50, stdin);
        gotoxy(24, 11);
        fflush(stdin);
        fgets(novaConta->agencia, 10, stdin);
        gotoxy(24, 13);
        fflush(stdin);
        fgets(novaConta->numero_conta, 20, stdin);
        gotoxy(24, 15);
        fflush(stdin);
        fgets(novaConta->tipo_conta, 10, stdin);
        gotoxy(24, 17);
        fflush(stdin);
        scanf("%lf" , &novaConta->vl_saldo);
        gotoxy(24, 19);
        fflush(stdin);
        scanf("%lf", &novaConta->vl_limite);
        gotoxy(24, 21);
        fflush(stdin);
        fgets(novaConta->status, 10, stdin);

        // Pergunta ao usuário se deseja gravar os dados
        gotoxy(7, 26);
        printf("Deseja gravar os dados? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);

        if (resposta == 1) {
            novoItem->conteudo = *novaConta;
            novoItem->proximo = listaContas.primeiro; 
            listaContas.primeiro = novoItem; 

            if (listaContas.ultimo == NULL) { 
                listaContas.ultimo = novoItem; 
            }

            gotoxy(7, 27);
            printf("Conta cadastrada com sucesso!\n");
        } else {
            free(novoItem); 
        }

        free(novaConta); 

        // Pergunta se deseja cadastrar outra conta
        gotoxy(7, 26);
        printf("Deseja cadastrar outra conta? (1-Sim / 2-Nao): ");
        scanf("%d", &resposta);
    } while (resposta == 1);
}

// Funcao para consultar contas bancarias
void ConsultarConta() {

    // Verifica se a lista de contas esta vazia
    if (listaContas.primeiro == NULL) {
        gotoxy(7, 26);
        printf("Lista esta vazia. Nenhuma conta para consultar.\n");
        getch();
        return;
    }

    tipoitem* item = listaContas.primeiro; // Ponteiro para percorrer a lista de contas

// Loop que percorre cada item na lista de contas
    while (item != NULL) {
    tela();
    telaContaBancaria();
    gotoxy(35, 6);
    printf("CONSULTA DE FUNCIONARIO");
    gotoxy(24, 7);
    printf("%d", item->conteudo.codigo_conta);
    gotoxy(24, 9);
    printf("%s", item->conteudo.banco);
    gotoxy(24, 11);
    printf("%s", item->conteudo.agencia);
    gotoxy(24, 13);
    printf("%s", item->conteudo.numero_conta);
    gotoxy(24, 15);
    printf("%s", item->conteudo.tipo_conta);
    gotoxy(24, 17);
    printf("%.2lf", item->conteudo.vl_saldo);
    gotoxy(24, 19);
    printf("%.2lf", item->conteudo.vl_limite);
    gotoxy(24, 21);
    printf("%s", item->conteudo.status);

// Solicita ao usuario que pressione uma tecla para continuar
    gotoxy(7, 26);
    printf("Pressione uma tecla para continuar...");
    getch();
    item = item->proximo; // Avança para o proximo na lista de contas
    }
  
}


// Funcao principal
int main() {
    int opcao;

 //  Um loop que sera executado até que a opcao de sair seja escolhida
    do {
        tela();
        gotoxy(35, 6);
        printf("MENU PRINCIPAL\n");
        gotoxy(10, 10);
        printf("1. Cadastro de Contas\n");
        gotoxy(10, 12);
        printf("2. Movimentacao Financeira\n");
        gotoxy(10, 14);
        printf("3. Sair\n");
        gotoxy(7, 26);
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

// Inicia switch para processar a opcao escolhida
        switch (opcao) {
        
            // Cadastro de Contas
            case 1: {
                int subOpcao;
                
                do{
                
                tela();
                gotoxy(35, 6);
                printf("Submenu Cadastro de Contas:\n");
                gotoxy(10, 8);
                printf("1. Cadastrar Contas Bancarias no Final\n");
                gotoxy(10, 10);
                printf("2. Cadastrar Contas Bancarias no Inicio\n");
                gotoxy(10, 12);
                printf("3. Cadastrar Contas Bancarias na Posicao\n");
                gotoxy(10, 14);
                printf("4. Remover Contas Bancarias no Final\n");
                gotoxy(10, 16);
                printf("5. Remover Contas Bancarias no Inicio\n");
                gotoxy(10, 18);
                printf("6. Remover Contas Bancarias na Posicao\n");
                gotoxy(10, 20);
                printf("7. Alteracao de Contas Bancarias\n");
                gotoxy(10, 22);
                printf("8. Consultar Contas Bancarias\n");
                gotoxy(10, 24);
                printf("9. Retornar ao Menu Anterior\n");
                gotoxy(7, 26);
                printf("Escolha uma opcao: ");
                scanf("%d", &subOpcao);

// Inicia switch para processar a sub-opcao escolhida
                switch (subOpcao) {
                    case 1:
                        CadastrarContaFinal();
                        break;
                    case 2:
                        CadastrarContaInicio();
                        break;
                    case 3:
                        
                        break;
                    case 4:
                        
                        break;
                    case 5:

                         break;
                    case 6:

                        break;
                    case 7:

                        break;
                    case 8:
                        ConsultarConta();
                        break;
                    case 9:
                        break;
                    default: 
                        printf("Opcao invalida!\n");
                }
            }while(subOpcao != 9);
                break;
            }
        
            // Movimentacao Financeira
            case 2: {
                int movOpcao;

                gotoxy(35, 5);
                printf("TELA DE MOVIMENTACAO FINANCEIRA:\n");
                gotoxy(10, 10);
                printf("1. Registrar Entrada\n");
                gotoxy(10, 12);
                printf("2. Registrar Saida\n");
                gotoxy(10, 14);
                printf("3. Consultar Movimentacao\n");
                gotoxy(7, 26);
                printf("Escolha uma opcao: ");
                scanf("%d", &movOpcao);

// Inicia switch para processar a opcao de movimentacao
                switch (movOpcao) {
                    case 1:
                       
                        break;
                    case 2:
                        
                        break;
                    case 3:
                        
                        break;
                    default:
                        printf("Opcao invalida!\n");
                }
                break;
            }
            case 3:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 3);

    return 0;
}


// Função para ler as contas do arquivo
void lerContasDoArquivo(Conta **listaContas) {
    FILE *arquivo = fopen("contas.dat", "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de contas.\n");
        return;
    }

    Conta conta;
    while (fread(&conta, sizeof(Conta), 1, arquivo)) {
        // Adicionar à lista de contas
    }

    fclose(arquivo);
}

// Função para salvar as contas no arquivo
void salvarContasNoArquivo(Conta *listaContas) {
    FILE *arquivo = fopen("contas.dat", "wb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de contas.\n");
        return;
    }

    Conta *temp = listaContas;
    while (temp != NULL) {
        fwrite(temp, sizeof(Conta), 1, arquivo);
        temp = temp->prox;
    }

    fclose(arquivo);
}



Movimentação----------------------------------------------------------------------------------------------------------

typedef struct {
    int codigo_conta;
    char data[20]; // Formato da data: dd/mm/aaaa
    char tipo_movimentacao[10]; // "Credito" ou "Debito"
    double valor_movimentacao;
    double saldo_atual; // Saldo após a movimentação
} Movimentacao;

typedef struct tipoitem_movimento *tipoapontador_movimento;

typedef struct tipoitem_movimento {
    Movimentacao conteudo;
    tipoapontador_movimento anterior;
    tipoapontador_movimento proximo;
} tipoitem_movimento;

typedef struct {
    tipoapontador_movimento primeiro;
    tipoapontador_movimento ultimo;
} tipolista_movimento;


void registrarMovimentacao(tipolista_conta *L, tipolista_movimentacao *movimentos, int codigo_conta, double valor, char tipo) {
    // Encontra a conta com o código fornecido
    tipoapontador_conta conta = pesquisarConta(L, codigo_conta);
    
    if (conta == NULL) {
        printf("Conta não encontrada!\n");
        return;
    }

    // Verifica se a movimentação é válida (Crédito ou Débito)
    if (tipo == 'D') { // Débito
        // Verifica se o valor de débito não ultrapassa o saldo + limite da conta
        if (conta->conteudo.vl_saldo + conta->conteudo.vl_limite < valor) {
            printf("Saldo insuficiente para realizar o débito.\n");
            return;
        }
        // Atualiza o saldo da conta
        conta->conteudo.vl_saldo -= valor;
    } else if (tipo == 'C') { // Crédito
        // Atualiza o saldo da conta
        conta->conteudo.vl_saldo += valor;
    } else {
        printf("Tipo de movimentação inválido.\n");
        return;
    }

    // Cria a movimentação
    tipoitem_movimentacao* novaMovimentacao = (tipoitem_movimentacao*)malloc(sizeof(tipoitem_movimentacao));
    novaMovimentacao->conteudo.codigoConta = codigo_conta;
    
    // Definir a data de movimentação (Aqui, usamos uma data fixa como exemplo)
    strcpy(novaMovimentacao->conteudo.dt_Movimento, "22/11/2024"); 
    
    novaMovimentacao->conteudo.vl_movimento = valor;
    novaMovimentacao->conteudo.vl_saldo = conta->conteudo.vl_saldo;
    novaMovimentacao->conteudo.tp_movimentacao[0] = tipo;
    novaMovimentacao->conteudo.tp_movimentacao[1] = '\0'; // Finaliza a string

    // Insere a nova movimentação na lista
    novaMovimentacao->anterior = movimentos->ultimo;
    novaMovimentacao->proximo = NULL;

    if (movimentos->primeiro == NULL) {
        movimentos->primeiro = novaMovimentacao;
        movimentos->ultimo = novaMovimentacao;
    } else {
        movimentos->ultimo->proximo = novaMovimentacao;
        movimentos->ultimo = novaMovimentacao;
    }

    printf("Movimentação registrada com sucesso! Saldo atual: %.2f\n", conta->conteudo.vl_saldo);
}

void relatorioMovimentacoes(tipolista_movimento *movimentos, int codigo_conta) {
    tipoapontador_movimento movimento = movimentos->primeiro;
    
    while (movimento != NULL) {
        if (movimento->conteudo.codigo_conta == codigo_conta) {
            printf("Data: %s | Tipo: %s | Valor: %.2f | Saldo apos movimentacao: %.2f\n", 
                   movimento->conteudo.data, 
                   movimento->conteudo.tipo_movimentacao, 
                   movimento->conteudo.valor_movimentacao, 
                   movimento->conteudo.saldo_atual);
        }
        movimento = movimento->proximo;
    }
}

void menuMovimentacao(tipolista_conta *L, tipolista_movimento *movimentos) {
    int codigo_conta, tipo_movimentacao;
    double valor;
    
    do {
        tela();
        gotoxy(5, 7);
        printf("Digite o codigo da conta: ");
        scanf("%d", &codigo_conta);
        
        gotoxy(5, 9);
        printf("Digite 1 para Credito ou 2 para Debito: ");
        scanf("%d", &tipo_movimentacao);

        gotoxy(5, 11);
        printf("Digite o valor da movimentacao: ");
        scanf("%lf", &valor);

        if (tipo_movimentacao == 1) {
            registrarMovimentacao(L, movimentos, codigo_conta, valor, 'C'); // Crédito
        } else if (tipo_movimentacao == 2) {
            registrarMovimentacao(L, movimentos, codigo_conta, valor, 'D'); // Débito
        } else {
            printf("Tipo de movimentacao invalido!\n");
        }
        
        gotoxy(7, 26);
        printf("Deseja realizar outra movimentacao? (1-Sim / 2-Nao): ");
        scanf("%d", &tipo_movimentacao);
    } while (tipo_movimentacao == 1);
}

*/