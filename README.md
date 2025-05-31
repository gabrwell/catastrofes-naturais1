# Sistema de Cadastro e Consulta de Relatos sobre Catástrofes Naturais

Este projeto é uma aplicação em C para cadastro, consulta, organização e armazenamento de relatos sobre catástrofes naturais. O sistema permite registrar informações completas de cada relato, localizar ocorrências próximas, ordenar e persistir os dados em arquivo texto, atendendo aos principais requisitos de um sistema básico de gestão de informações georreferenciadas.

---

## Funcionalidades

- **Cadastro de Relatos**  
  Permite ao usuário registrar um novo relato, informando dados pessoais, tipo e descrição da catástrofe, localização (latitude/longitude) e data do evento.

- **Listagem de Relatos**  
  Exibe todos os relatos cadastrados de forma organizada.

- **Consulta por Raio de 10 km**  
  Permite ao usuário informar uma localização, listando apenas os relatos ocorridos em um raio de até 10 km.

- **Ordenação por Data**  
  Os relatos podem ser ordenados por data para facilitar a análise cronológica.

- **Persistência em Arquivo**  
  Todos os relatos são salvos em um arquivo `.txt` para garantir que nenhuma informação seja perdida entre execuções.

---

## Estrutura de Dados

Cada relato é representado por uma `struct`:

```c
typedef struct {
    char nome[100];
    char cpf[15];
    char telefone[20];
    char email[100];
    char tipo_catastrofe[50];
    char descricao[200];
    float latitude;
    float longitude;
    char data[11]; // formato DD/MM/AAAA
} Relato;
```

Os relatos são armazenados em um vetor (lista) de tamanho dinâmico, carregado do arquivo sempre que o sistema inicia.

---

## Validação de Entradas

- **E-mail:** Verificação simples da presença do caractere `@`.
- **Latitude e Longitude:** Devem ser números reais.  
- **Demais campos:** Recebem validação básica de preenchimento (podem ser aprimorados).

---

## Persistência em Arquivo

Os relatos são gravados e lidos do arquivo `relatos.txt`, com cada campo separado por ponto-e-vírgula.

**Exemplo de linha no arquivo:**
```
João Silva;12345678900;11912345678;joao@email.com;Enchente;Rio transbordou;-23.5505;-46.6333;30/05/2025
```

---

## Exemplo de Uso

### Cadastro de um relato

```
[1] Cadastrar novo relato
Nome: Maria Costa
CPF: 12345678901
Telefone: 11987654321
E-mail: maria@email.com
Tipo de catástrofe: Deslizamento
Descrição: Encosta cedeu após chuva forte.
Latitude: -23.56
Longitude: -46.62
Data (DD/MM/AAAA): 28/05/2025
Relato cadastrado!
```

### Listagem de relatos

```
[2] Listar relatos
1. [Deslizamento] 28/05/2025 - Maria Costa (Encosta cedeu após chuva forte.)
   Local: (-23.560000, -46.620000)
   Contato: 11987654321, maria@email.com, 12345678901
```

### Consulta por raio

```
[3] Consultar relatos num raio de 10km
Informe sua latitude: -23.55
Informe sua longitude: -46.63
Relatos num raio de 10 km:
1. [Deslizamento] 28/05/2025 - Maria Costa (1.43 km)
   Descrição: Encosta cedeu após chuva forte.
```

### Ordenação por data

```
[4] Ordenar relatos por data
Relatos ordenados por data.
```

---



---

---

## Comentários Finais

- O sistema pode ser expandido para projetos acadêmicos ou aplicações reais.

---
