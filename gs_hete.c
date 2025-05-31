#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM_NOME 100
#define TAM_EMAIL 100
#define TAM_CPF 15
#define TAM_TELEFONE 20
#define TAM_TIPO 50
#define TAM_DESC 200
#define TAM_DATA 11
#define MAX_RELATOS 1000
#define ARQUIVO "relatos.txt"

// Estrutura que representa um relato de catástrofe natural
typedef struct {
    char nome[TAM_NOME];              // Nome da pessoa que registrou o relato
    char cpf[TAM_CPF];                // CPF da pessoa
    char telefone[TAM_TELEFONE];      // Telefone de contato
    char email[TAM_EMAIL];            // E-mail de contato
    char tipo_catastrofe[TAM_TIPO];   // Tipo de catástrofe (ex: enchente, deslizamento...)
    char descricao[TAM_DESC];         // Descrição do ocorrido
    float latitude;                   // Latitude do local do evento
    float longitude;                  // Longitude do local do evento
    char data[TAM_DATA];              // Data do evento (formato DD/MM/AAAA)
} Relato;

// Função que calcula a distância em KM entre dois pontos geográficos usando a fórmula de Haversine
float calcularDistancia(float lat1, float lon1, float lat2, float lon2) {
    float R = 6371; // Raio da Terra em km
    float dLat = (lat2-lat1)*M_PI/180;
    float dLon = (lon2-lon1)*M_PI/180;
    float a = sin(dLat/2)*sin(dLat/2) +
        cos(lat1*M_PI/180)*cos(lat2*M_PI/180)*
        sin(dLon/2)*sin(dLon/2);
    float c = 2*atan2(sqrt(a), sqrt(1-a));
    return R*c; // Distância em km
}

// Função de validação simples para email (verifica presença de '@')
int validarEmail(const char *email) {
    return strchr(email, '@') != NULL;
}

// Carrega relatos do arquivo texto para o vetor de relatos
int carregarRelatos(Relato *relatos, int max) {
    FILE *arq = fopen(ARQUIVO, "r");
    if (!arq) return 0; // Se não existe arquivo, começa com zero relatos
    int qtd = 0;
    // Leitura de cada linha do arquivo até o fim ou atingir o máximo permitido
    while (fscanf(arq, "%99[^;];%14[^;];%19[^;];%99[^;];%49[^;];%199[^;];%f;%f;%10[^\n]\n", 
        relatos[qtd].nome, relatos[qtd].cpf, relatos[qtd].telefone, relatos[qtd].email,
        relatos[qtd].tipo_catastrofe, relatos[qtd].descricao,
        &relatos[qtd].latitude, &relatos[qtd].longitude, relatos[qtd].data) == 9) {
        qtd++;
        if (qtd >= max) break;
    }
    fclose(arq);
    return qtd;
}

// Salva todos os relatos do vetor no arquivo texto
void salvarRelatos(Relato *relatos, int qtd) {
    FILE *arq = fopen(ARQUIVO, "w");
    for (int i = 0; i < qtd; i++) {
        // Campos separados por ponto e vírgula
        fprintf(arq, "%s;%s;%s;%s;%s;%s;%.6f;%.6f;%s\n",
            relatos[i].nome, relatos[i].cpf, relatos[i].telefone, relatos[i].email,
            relatos[i].tipo_catastrofe, relatos[i].descricao,
            relatos[i].latitude, relatos[i].longitude, relatos[i].data);
    }
    fclose(arq);
}

// Cadastra um novo relato no vetor e salva em arquivo
void cadastrarRelato(Relato *relatos, int *qtd) {
    if (*qtd >= MAX_RELATOS) {
        printf("Limite de relatos atingido!\n");
        return;
    }
    Relato r;
    // Recebe todos os dados do novo relato
    printf("Nome: "); getchar(); fgets(r.nome, TAM_NOME, stdin); r.nome[strcspn(r.nome,"\n")]=0;
    printf("CPF: "); fgets(r.cpf, TAM_CPF, stdin); r.cpf[strcspn(r.cpf,"\n")]=0;
    printf("Telefone: "); fgets(r.telefone, TAM_TELEFONE, stdin); r.telefone[strcspn(r.telefone,"\n")]=0;
    printf("E-mail: "); fgets(r.email, TAM_EMAIL, stdin); r.email[strcspn(r.email,"\n")]=0;
    // Validação simples do e-mail
    if (!validarEmail(r.email)) {
        printf("E-mail inválido!\n");
        return;
    }
    printf("Tipo de catástrofe: "); fgets(r.tipo_catastrofe, TAM_TIPO, stdin); r.tipo_catastrofe[strcspn(r.tipo_catastrofe,"\n")]=0;
    printf("Descrição: "); fgets(r.descricao, TAM_DESC, stdin); r.descricao[strcspn(r.descricao,"\n")]=0;
    printf("Latitude: "); scanf("%f", &r.latitude);
    printf("Longitude: "); scanf("%f", &r.longitude);
    printf("Data (DD/MM/AAAA): "); getchar(); fgets(r.data, TAM_DATA, stdin); r.data[strcspn(r.data,"\n")]=0;
    relatos[(*qtd)++] = r; // Adiciona ao vetor de relatos
    salvarRelatos(relatos, *qtd); // Salva no arquivo
    printf("Relato cadastrado!\n");
}

// Lista todos os relatos registrados
void listarRelatos(Relato *relatos, int qtd) {
    printf("Relatos cadastrados:\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. [%s] %s - %s (%s)\n", i+1, relatos[i].tipo_catastrofe, relatos[i].data, relatos[i].nome, relatos[i].descricao);
        printf("   Local: (%.6f, %.6f)\n", relatos[i].latitude, relatos[i].longitude);
        printf("   Contato: %s, %s, %s\n", relatos[i].telefone, relatos[i].email, relatos[i].cpf);
    }
}

// Consulta relatos em um raio de até 10 km a partir de uma localização informada
void consultarPorRaio(Relato *relatos, int qtd) {
    float lat, lon;
    printf("Informe sua latitude: "); scanf("%f", &lat);
    printf("Informe sua longitude: "); scanf("%f", &lon);
    printf("Relatos num raio de 10 km:\n");
    int achou = 0;
    for (int i = 0; i < qtd; i++) {
        float dist = calcularDistancia(lat, lon, relatos[i].latitude, relatos[i].longitude);
        if (dist <= 10.0) {
            printf("%d. [%s] %s - %s (%.2f km)\n", i+1, relatos[i].tipo_catastrofe, relatos[i].data, relatos[i].nome, dist);
            printf("   Descrição: %s\n", relatos[i].descricao);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum relato encontrado nesse raio.\n");
}

// Ordena os relatos por data (ordem crescente, usando bubble sort)
void ordenarPorData(Relato *relatos, int qtd) {
    for (int i = 0; i < qtd-1; i++)
        for (int j = 0; j < qtd-i-1; j++)
            if (strcmp(relatos[j].data, relatos[j+1].data) > 0) {
                Relato tmp = relatos[j];
                relatos[j] = relatos[j+1];
                relatos[j+1] = tmp;
            }
}

int main() {
    Relato relatos[MAX_RELATOS];        // Vetor dinâmico de relatos
    int qtd = carregarRelatos(relatos, MAX_RELATOS); // Carrega relatos do arquivo, se houver

    int op;
    do {
        printf("\nSistema de Cadastro de Relatos de Catástrofes Naturais\n");
        printf("[1] Cadastrar novo relato\n");
        printf("[2] Listar relatos\n");
        printf("[3] Consultar relatos num raio de 10km\n");
        printf("[4] Ordenar relatos por data\n");
        printf("[0] Sair\nEscolha: ");
        scanf("%d", &op);
        switch (op) {
            case 1: cadastrarRelato(relatos, &qtd); break;
            case 2: listarRelatos(relatos, qtd); break;
            case 3: consultarPorRaio(relatos, qtd); break;
            case 4: ordenarPorData(relatos, qtd); printf("Relatos ordenados por data.\n"); break;
            case 0: break;
            default: printf("Opção inválida!\n");
        }
    } while (op != 0);

    return 0;
}