

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// DEFININDO O MÁXIMO DE TERRITÓRIOS E OS TAMANHOS DA STRING
#define MAX_TerritorioS 5
#define TAM_STRING 50

// CRIANDO O STRUCT
struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// CRIANDO UMA FUNÇÃO PARA LIMPAR O BUFFER DA ENTRADA
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função cadastrando territórios
void CadastrodeTerritorios(struct Territorio mapa[MAX_TerritorioS]){
    printf("==============================\n\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n");

    // CADASTRANDO OS TERRITÓRIOS
    for (int i = 0; i < MAX_TerritorioS; i++){
        printf("\n----- CADASTRANDO TERRITÓRIO %d -----\n", i + 1);
        printf("Digite o nome do território: ");
        fgets(mapa[i].nome, TAM_STRING, stdin);

        printf("Digite a cor do território (ex: Vermelho, azul): ");
        fgets(mapa[i].cor, TAM_STRING, stdin);
        
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite o número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// Função mostrando territórios
void MostrandoTerritorios(struct Territorio mapa[MAX_TerritorioS]){
    // MOSTRANDO NA TELA OS TERRITÓRIOS
    printf("\n============== MAPA DO MUNDO - ESTADO ATUAL ================\n");
    for (int i = 0; i < MAX_TerritorioS; i++){
        printf("%d. ", i + 1);
        printf("%s         ", mapa[i].nome);
        printf("(Exército: %s   ,   Tropas: %d)\n", mapa[i].cor, mapa[i].tropas);
    }
    printf("\n==============================================================\n");
}

// Função de ataque
void AcaoDeAtaque(struct Territorio mapa[MAX_TerritorioS]){
    // srand para randomizar o rand 
    srand(time(NULL));

    int territorioatacante;
    int territoriodefensor;
// Quem irá atacar
    printf("\n--- FASE DE ATAQUE ---");
    printf("\nEscolha o território atacante [1 a 5 || 0 para sair]: ");
    scanf("%d", &territorioatacante);
    territorioatacante--;
// Quem será atacado
    if (territorioatacante != -1){
        printf("Escolha o território para defender [1 a 5]: ");
        scanf("%d", &territoriodefensor);
            
        territoriodefensor--;
// Randomizando os dados
        int dadoataque = rand() % 10;
        int dadodefesa = rand() % 10;
        printf("\n--- RESULTADO DA BATALHA ---\n");
        printf("O atacante %s rolou um dado e tirou: %d\n", mapa[territorioatacante].nome, dadoataque);
        printf("O defensor %s rolou um dado e tirou: %d\n", mapa[territoriodefensor].nome, dadodefesa);
// Vitória do ataque
        if (dadoataque > dadodefesa){
            printf("VITÓRIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
                // Conquista do ataque
            if (mapa[territoriodefensor].tropas == 1){
                printf("CONQUISTA! O território %s foi dominado pelo exército %s", mapa[territoriodefensor].nome, mapa[territorioatacante].cor);
                // Copiando o exército de "território atacante" para o do defensor
                strcpy(mapa[territoriodefensor].cor, mapa[territorioatacante].cor);
            } else { 
                mapa[territoriodefensor].tropas--;
            }
            // Vitória da defesa
        } else { 
            printf("VITÓRIA DA DEFESA! O atacante perdeu 1 tropa.\n");
            // Conquista da defesa
            if ((mapa[territoriodefensor].tropas) <= 1){
                printf("CONQUISTA! O território %s foi dominado pelo exército %s", mapa[territorioatacante].nome, mapa[territoriodefensor].cor);
                // Copiando o exército de "território defensor" para o do atacante
                strcpy(mapa[territorioatacante].cor, mapa[territoriodefensor].cor);
            } else {
                mapa[territorioatacante].tropas--;
            }
        }

        printf("\nPressione ENTER para continuar...");
        limparBufferEntrada(); 
        getchar();
    }
}

// Função para exibir a missão escolhida
int missaoescolhida(int exercitocacador, int exercitoalvo, struct Territorio mapa[MAX_TerritorioS]) {
    // Verifica se os exércitos são diferentes
    if (strcmp(mapa[exercitoalvo].cor, mapa[exercitocacador].cor) != 0) {
        printf("--- SUA MISSÃO (Exército %s) ---\n", mapa[exercitocacador].cor);
        printf("Destruir o exército %s\n", mapa[exercitoalvo].cor);
        return 0;
    } else {
        // Quando os exércitos são iguais (já completaram a missão)
        printf("A MISSÃO FOI ENCERRADA\n");
        return 1;
    }
}

// Função para mostrar o andamento da missão
void andamentodamissao(int exercitocacador, int exercitoalvo, struct Territorio mapa[MAX_TerritorioS], int terminodamissao) {
    int vivos_alvo = mapa[exercitoalvo].tropas;
    int vivos_cacador = mapa[exercitocacador].tropas;

    // Conta quantos territórios ainda são do exército do caçador e do alvo

    // Verifica resultado da missão
    if (terminodamissao == 1){
        if (vivos_cacador > vivos_alvo) {
            printf(" PARABÉNS! VOCÊ CONCLUIU SUA MISSÃO COM SUCESSO!\n");
        } else if (vivos_alvo > vivos_cacador) {
            printf("VOCÊ FALHOU NA SUA MISSÃO. Seu exército foi eliminado.\n");
    }
    } else {
        printf("A MISSÃO ESTÁ EM ANDAMENTO...\n");
    }

    printf("Aperte ENTER para continuar...");
    getchar();
}

int main(){
    // SETANDO O LOCAL DO MUNDO PARA OS ACENTOS FICAREM VISÍVEIS
    setlocale(LC_ALL, "Portuguese_Brazil");

    // CRIANDO O VETOR DO STRUCT
    struct Territorio *mapa;
    // Liberando espaço com malloc
    mapa = (struct Territorio *) malloc(MAX_TerritorioS * sizeof(struct Territorio));

    // Criação do exército que irá atacar e do exército alvo para as missões
    srand(time(NULL));
    int exercitocacador = rand() % 5;
    int exercitoalvo = rand() % 5;
    int opcao;

// Cadastrando os territórios 
    
    CadastrodeTerritorios(mapa);
    
// Começando o dowhile mostrando as opções disponíveis
    do{
        MostrandoTerritorios(mapa);
        missaoescolhida(exercitocacador, exercitoalvo, mapa);
        printf("--- MENU DE AÇÕES ---\n");
        printf("1 - ATACAR \n2 - VERIFICAR MISSÃO \n0 - SAIR\n");
        printf("Escolha sua ação: \n");
        scanf("%d", &opcao);
        
// Criação das opções escolhidas.
        switch (opcao){
            case 1:
                // chamando o ataque
                AcaoDeAtaque(mapa);
                break;

            case 2:
                // verificando o andamento da missão
                andamentodamissao(exercitocacador, exercitoalvo, mapa, missaoescolhida(exercitocacador, exercitoalvo, mapa));
                break;

            case 0:
                // encerrando o programa
                printf("Encerrando...\n");
                break;
            
            default:
                // Isso ocorre caso apareça algum número diferente
            printf("Essa opção não existe!");
            break;
            
        }
        limparBufferEntrada();
    } while (opcao != 0);
    // Liberando o espaço
    free(mapa);
    printf("Espaço liberado!!");
    return 0;
}
