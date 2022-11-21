#ifndef FILA_H
#define FILA_H
#include <time.h>//Biblioteca de tempo
#include <ctime>//Biblioteca de tempo
#include <iostream>
#include <windows.h>

using namespace std;

typedef struct TipoItemMedico//Armazena os dados dos medicos
{
    char nome[20];
    char especialidade[100];
    char CRM[15];
    bool disponivel = true;
} TipoItemMedico;

typedef struct TipoItemPaciente//Armazena os dados dos pacientes
{
    char nome[40];
    char Endereco[100];
    char idade[50];
    char sexo[20];
    char triagem[18];
    int prioridade;
    bool atendido = false;
    time_t h_chegada;
    time_t h_saida;
    double tempo;//tempo de atendimento
};

// Ponteiro para o elemento da fila
typedef struct TipoElemento *Apontador;

// Elemento (célula) da fila
typedef struct TipoElemento
{
    TipoItemMedico medico;
    TipoItemPaciente paciente;
    Apontador prox;
} TipoElemento;

// Estrutura da fila
typedef struct TipoFila
{
    Apontador inicio, fim;
    int tamanho;
} TipoFila;

// Funções da fila
void CriaFilaVazia(TipoFila *fila);//Cria uma fila vazia
bool VerificaFilaVazia(TipoFila *fila);//Verifica se a fila esta vazia
int Tamanho(TipoFila *fila);//Retorna o tamanho de qual fila quiser
void EnfileiraMedico(TipoFila *fila, TipoItemMedico medico);//Enfileira os medicos na fila de medicos
void EnfileiraPaciente(TipoFila *fila, TipoItemPaciente paciente);//Enfileira os pacientes na fila
void InserePacientePrimeiro(TipoFila *fila, TipoItemPaciente paciente);//Insere o paciente na primeira posicao da fila
void InsereApos(Apontador anterior, Apontador aux, TipoFila *fila);//Insere apos um elemento procurado na fila
void EnfileiraPrioridade(TipoFila *fila, TipoItemPaciente paciente);//Enfileira de acordo com a prioridade
void DesenfileiraMedico(TipoFila *fila, TipoItemMedico *medico);//Desenfileira um medico da fila
void DesenfileiraPaciente(TipoFila *fila, TipoItemPaciente *paciente);//Desenfileira um paciente da fila ja organizada
void ImprimeFilaMedicos(TipoFila *fila);//Imprime a fila de medicos
void ImprimeFilaPacientes(TipoFila *fila);//Imprime a fila de pacientes
void Menu();//Exibe o menu de opcoes
int Triagem();//Exibe o menu de triagem
void InsereMedico(TipoItemMedico *medico);//Insere um medico na fila
void InserePaciente(TipoItemPaciente *paciente, int Ret_Triagem);//Insere um paciente na fila
bool PesquisaPaciente(TipoFila fila, char nome[]);//Pesquisa um paciente de acordo com o nome
void AtualizaUltimo(TipoFila *fila);//Atualiza o ultimo
void RemovePacienteNome(TipoFila *fila, char nome[]);//Remove um paciente por nome
void atualizar(TipoFila *filaPacientes, TipoFila *filaPacientesAtendidos, TipoFila *filamedicos, TipoFila *filaMedicosDisponiveis);
//Mostra o atendimento de pacientes e atualiza

#endif