#include <iostream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include "fila.hpp"

using namespace std;

void CriaFilaVazia(TipoFila *fila)//Cria uma fila vazia
{
    fila->inicio = NULL;//Inicio aponta para null
    fila->fim = NULL;//Fim aponta para null
    fila->tamanho = 0;//O tamanho comeca como 0
}

bool VerificaFilaVazia(TipoFila *fila)//Verifica se a fila esta vazia
{
    return (fila->inicio == NULL);//Retorna se o inicio da fila esta apontando para null
}

int Tamanho(TipoFila *fila)//Retorna o tamanho de alguma fila
{
    return fila->tamanho;//Acessa dentro da struct fila o tamanho e retorna 
}

void EnfileiraMedico(TipoFila *fila, TipoItemMedico medico)//Enfileira um medico na fila de medicos
{
    Apontador novo = new TipoElemento;//Cria um novo elemento

    novo->medico = medico;//Recebe as informacoes do medico
    novo->prox = NULL;//O prox dele aponta para null

    if (VerificaFilaVazia(fila))//Verifica se a fila esta vazia
    {
        fila->inicio = novo;//Se estiver vazia insere no primeiro 
    }
    else
    {
        fila->fim->prox = novo;//Se nao insere no fim da fila
    }

    fila->fim = novo;//Atualiza o ponteiro fim
    fila->tamanho++;//Atualiza o tamanho 
}

void EnfileiraPaciente(TipoFila *fila, TipoItemPaciente paciente)//Enfileira um paciente na fila de pacientes
{
    Apontador aux = new TipoElemento;//Cria um novo elemento
    aux->paciente = paciente;//Que recebe os dados do paciente
    aux->prox = NULL;//O prox dele aponta para null
    if (VerificaFilaVazia(fila))//Verifica se a fila esta vazia
    {
        fila->inicio = aux;//Se estiver insere na primeira posicao da fila
    }
    else
    {
        fila->fim->prox = aux;//Se nao insre no fim da fila
    }

    fila->fim = aux;//Atualiza o ponteiro fim 
    fila->tamanho++;//Atualiza o tamanho 
}

void InserePacientePrimeiro(TipoFila *fila, TipoItemPaciente paciente) // usado para ordenar as prioridades
{
    Apontador aux = new TipoElemento;
    aux->paciente = paciente;
    aux->prox = NULL;

    if (VerificaFilaVazia(fila))
    {
        fila->inicio = aux;
        fila->fim = fila->inicio;
    }
    else
    {
        aux->prox = fila->inicio;
        fila->inicio = aux;
    }
    fila->tamanho++;
}

void InsereApos(Apontador anterior, Apontador aux, TipoFila *fila) // usado para ordenar as prioridades
{
    aux->prox = anterior->prox;
    anterior->prox = aux;
    fila->tamanho++;
}

void EnfileiraPrioridade(TipoFila *fila, TipoItemPaciente paciente)//Enfileira com prioridade os pacientes
{
   
    if (VerificaFilaVazia(fila))    // Se a fila estiver vazia insere o Paciente direto no primeiro.
    {
        InserePacientePrimeiro(fila, paciente);
        return;
    }

    // Se a prioridade do novo Paciente for menor que a do primeiro, insere o Paciente no começo da fila.
    if (paciente.prioridade < fila->inicio->paciente.prioridade)
    {
        InserePacientePrimeiro(fila, paciente);
        return;
    }

    Apontador anterior = fila->inicio;
    Apontador atual = anterior->prox;
    Apontador aux = new TipoElemento;
    aux->paciente = paciente;
    aux->prox = NULL;

    // Insere apos a maior prioridade encontrada, não funciona para o ultimo.
    while (atual != NULL)
    {
        if (aux->paciente.prioridade < atual->paciente.prioridade)
        {
            InsereApos(anterior, aux, fila);//Insere apos o elemento encontrado
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    InsereApos(anterior, aux, fila);//Insere apos o elemento encontrado
    fila->fim = aux;
}

void DesenfileiraMedico(TipoFila *fila, TipoItemMedico *medico)//Desenfileira medico da fila
{
    if (VerificaFilaVazia(fila))//Verifica se a fila esta vazia
    {
        cout << "Fila de medicos vazia!" << endl;//Retorna a mensagem
        return;
    }
    Apontador aux = fila->inicio;//Comeca do inicio

    *medico = aux->medico;
    fila->inicio = aux->prox;//Atualiza o ponteiro inicio para uma posicao a frente
    delete aux;//Deleta o aux que e o primeiro da fila
    fila->tamanho--;//Atualiza o tamanho
}

void DesenfileiraPaciente(TipoFila *fila, TipoItemPaciente *paciente)//Desenfileira da fila de pacientes
{
    if (VerificaFilaVazia(fila))//Verifica se a fila esta vazia
    {
        cout << "Fila de paciente vazia!" << endl;//Retorna a mensagem
        return;
    }
    Apontador aux = fila->inicio;//Comeca do inicio

    *paciente = aux->paciente;
    fila->inicio = aux->prox;//Atualiza o primeiro para uma posicao a frente
    delete aux;//Deleta o aux que e o primeiro da fila
    // fila->tamanho--; //tirei para mostrar o valor total dos pacientes mesmo
    // depoiis de desinfileirar mas poderia ter somado as 2 filas
}

void ImprimeFilaMedicos(TipoFila *fila)//Imprime a fila de medicos
{
    if (VerificaFilaVazia(fila))//Verifica se a fila esta vazia
    {
        cout << "Nenhum médico cadastrado!" << endl;//Retorna a mensagem
        return;
    }
    Apontador aux = fila->inicio;//Aux comeca do inicio
    while (aux != NULL)//Percorre a fila
    {

        cout << "\nNome: " << aux->medico.nome;
        cout << "\nEspecialidade: " << aux->medico.especialidade;
        cout << "\nCRM: " << aux->medico.CRM;
        cout << "\nSituacao: \nDisponivel (0 - SIM | 1 - NAO): " << aux->medico.disponivel
             << endl;
        aux = aux->prox;//Anda uma posicao a frente sempre
    }
    cout << endl;
}

void ImprimeFilaPacientes(TipoFila *fila)//Imprime a fila de pacientes
{

    if (VerificaFilaVazia(fila))//Verifica se a fila esta vazia
    {
        cout << "Nenhum paciente cadastrado!" << endl;//Retorna a mensagem
        return;
    }
    Apontador aux = fila->inicio;//Comeca do inicio 
    while (aux != NULL)//Percorre a fila
    {
        cout << "\nNome: " << aux->paciente.nome;
        cout << "\nEndereço: " << aux->paciente.Endereco;
        cout << "\nIdade: " << aux->paciente.idade;
        cout << "\nSexo: " << aux->paciente.sexo;
        cout << "\nPrioridade: " << aux->paciente.prioridade;
        cout << "\nfoi atendido: 0-NÃO 1-SIM " << aux->paciente.atendido;
        if (aux->paciente.atendido == 1)//Exibe o tempo de atendimento e a hora de chegada
        {
            cout << "\nTempo de Atendimento: " << aux->paciente.tempo
                 << endl;
        }
        cout << "\nHora que chegou: " << ctime(&aux->paciente.h_chegada);

        aux = aux->prox;
    }
    cout << endl;
}

void Menu()
{
    cout << "**************************** UPA ****************************" << endl;
    cout << "****                                                     ****" << endl;
    cout << "**** 1 - Registro da UPA                                 ****" << endl;
    cout << "****                                                     ****" << endl;
    cout << "**** 2 - Cadastro de Medico                              ****" << endl;
    cout << "****                                                     ****" << endl;
    cout << "**** 3 - Novo Atendimento                                ****" << endl;
    cout << "****                                                     ****" << endl;
    cout << "**** 4 - Saida de Dados                                  ****" << endl;
    cout << "****                                                     ****" << endl;
    cout << "**** 5 - Sair                                            ****" << endl;
    cout << "****                                                     ****" << endl;
    cout << "*************************************************************" << endl
         << endl;
}

int Triagem()//Menu de perguntas da triagem
{
    char vet[18];
    TipoItemPaciente teste;
    TipoFila fila;
    
    system("cls");
    
    cout << "\n               TRIAGEM            \n";
    cout << "\n**********************************\n";

    cout << "\n 1 -  Comprometimento das Vias Aerias? ";
    cout << "\n 2 -  Respiração Ineficaz? ";
    cout << "\n 3 -  Choque? ";
    cout << "\n 4 -  Não responde a estimulos? ";
    cout << "\n 5 -  Em convulção? ";
    cout << "\n ************************************";
    cout << "\n 6 -  Dor severa? ";
    cout << "\n 7 -  Grande hemorragia incontrolavel? ";
    cout << "\n 8 -  Alteração do estado de consiencia? ";
    cout << "\n 9 -  Temperatura maior ou igual a 39°? ";
    cout << "\n 10 - Trauma craniano severo? ";
    cout << "\n ************************************";
    cout << "\n 11 - Dor moderada? ";
    cout << "\n 12. 12 - Pequena hemorragia incontrolavel? ";
    cout << "\n 13. 13 - Vomito percistente? ";
    cout << "\n 14 - Temperatura entre 38°  e 39°? ";
    cout << "\n 15 - Idoso ou gravida? ";
    cout << "\n ************************************";
    cout << "\n 16 - Dor leve?";
    cout << "\n 17 - Nausea? ";
    cout << "\n 18 - Temperatura entre 37° e 38°? ";
    cout << "\n ************************************";
    cout << "\n Responda as perguntas de acordo com a ordem acima usando (s - sim | n - não): \n\n";
    cout << "\n *******************************************************************************" << endl;
    for (int i = 1; i <= 5; i++)
    { //vermelho
        cout << "Pergunta " << i << " ";
        cin >> vet[i];
        if (vet[i] == 'S' || vet[i] == 's')
        {
            return i;
        }
    }
    for (int i = 6; i < 18; i++)
    { //outros
        cout << "Pergunta: " << i << " ";
        cin >> vet[i];
    }
    cout << "Lista das Respostas: \n ";
    for (int i = 0; i < 18; i++)
    {
        cout << vet[i] << " | ";
    }
    for (int i = 6; i < 18; i++)
    {
        if (vet[i] == 'S')
        {
            return i;
        }
    }
    system("pause");
    system("cls");
}

void InsereMedico(TipoItemMedico *medico)//Insere medico na fila
{
    cin.ignore();//junta os char sem erro
    cout << "Nome: ";
    cin.getline(medico->nome, 20);
    cout << "Especialidade: ";
    cin.getline(medico->especialidade, 100);
    cout << "CRM: ";
    cin.getline(medico->CRM, 15);

    cout << "\n\nMedico registrado com sucesso!\n\n";
    system("pause");
    system("cls");
}

void InserePaciente(TipoItemPaciente *paciente, int Ret_Triagem)//Insere paciente
{
    int prioridade;
    double Temp_Atendimento;//Armazena o tempo de
    if (Ret_Triagem <= 5)//se a prioridade for 1 
    {
        prioridade = 1;
       Temp_Atendimento = 5; //minutos
    }
    else if (Ret_Triagem > 5 && Ret_Triagem < 11)//se a prioridade for 2
    {
        prioridade = 2;
       Temp_Atendimento = 4; //minutos
    }
    else if (Ret_Triagem > 11 && Ret_Triagem < 16)//se a prioridade for 3
    {
        prioridade = 3;
       Temp_Atendimento = 3; //minutos
    }
    else if (Ret_Triagem > 16 && Ret_Triagem < 18)//se a prioridade for 4
    {
        prioridade = 4;
       Temp_Atendimento = 2; //minutos
    }
    else
    {
        prioridade = 5;//se nao sera 5 
       Temp_Atendimento = 1; //minutos
    }
    cout << "\n";
    
    cout << "                 CADASTRO DE PACIENTES\n";
    cout << "******************************************************\n\n";
    cin.ignore();

    cout << "Nome: ";
    cin.getline(paciente->nome, 40);
    cout << "Endereço: ";
    cin.getline(paciente->Endereco, 100);
    cout << "Idade: ";
    cin.getline(paciente->idade, 50);
    cout << "Sexo: ";
    cin.getline(paciente->sexo, 20);
    paciente->prioridade = prioridade;
    paciente->h_chegada = time(NULL);//pega o tempo de chegada do paciente
    paciente->tempo = Temp_Atendimento;
}


void AtualizaUltimo(TipoFila *fila)//Atualiza o ultimo
{
    Apontador aux;
    aux = fila->inicio;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    fila->fim = aux;
}
