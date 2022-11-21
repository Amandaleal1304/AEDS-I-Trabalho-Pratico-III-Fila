#include <iostream>
#include <windows.h>
#include "fila.cpp"
#include "fila.hpp"
#include <time.h>
#include <ctime>

using namespace std;

void atualizar(TipoFila *filaPacientes, TipoFila *filaPacientesAtendidos, TipoFila *filamedicos, TipoFila *filaMedicosDisponiveis);

int main()
{
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
    TipoFila filamedicos;
    TipoFila filaMedicosDisponiveis;
    TipoFila filaPacientes;
    TipoFila filaPacientesAtendidos;
    TipoFila listafila;
    TipoItemPaciente paciente;
    TipoItemPaciente paciente2;
    TipoItemMedico medico;

    CriaFilaVazia(&filamedicos);
    CriaFilaVazia(&filaMedicosDisponiveis);
    CriaFilaVazia(&listafila);
    CriaFilaVazia(&filaPacientes);
    CriaFilaVazia(&filaPacientesAtendidos);

    int opcao;
    do
    {
        system("cls");
        Menu();
        while ((cout << "Escolha a opção: ") && !(cin >> opcao))
        {
            cout << "Digite uma opção válida.\n\n";
            cin.clear();
            cin.ignore();
        }
        system("cls");
        switch (opcao)
        {
        case 1:
            system("cls");

            cout << "Quantidade de Pacientes Cadastrados: " << Tamanho(&filaPacientes) << "\n";
            cout << "Quantidade de Pacientes Atendidos: " << Tamanho(&filaPacientesAtendidos) << "\n";
            cout << "Quantidade de Medicos Cadastrados: " << Tamanho(&filamedicos) << "\n";
            cout << "Quantidade de Medicos Disponíveis: " << Tamanho(&filaMedicosDisponiveis) << "\n";
            cout << "Lista de Pacientes: \n";
            ImprimeFilaPacientes(&filaPacientesAtendidos);
            ImprimeFilaPacientes(&filaPacientes);

            cout << "Lista de Medicos: \n";
            ImprimeFilaMedicos(&filamedicos);
            system("PAUSE");

            break;
        case 2:

            if (Tamanho(&filamedicos) > 4)
            {

                cout << "Maximo de medicos cadastrados\n";
                system("PAUSE");
            }
            else
            {

                cout << "***********************************\n";
                cout << "        CADASTRO DE MEDICOS       \n";
                cout << "***********************************\n\n";
                InsereMedico(&medico);
                EnfileiraMedico(&filamedicos, medico);
            }

            break;
        case 3:
            char ret, retornoTriagem, vet[18];
            int valor;
            do
            {
                retornoTriagem = Triagem();
                InserePaciente(&paciente, retornoTriagem);
                EnfileiraPrioridade(&filaPacientes, paciente);
                cout << "Triagem realizada com sucesso\n";
                cout << "Deseja adicionar mais alguma triagem? S-sim N-nao\n";
                cin >> ret;
           } while (ret != 'n');

            system("PAUSE");
            break;
        case 4:

            char opcao;
            if (Tamanho(&filaPacientes) == 0)
            {
                cout << "nao existem pacientes para ser atendidos\n";
            }
            else if (Tamanho(&filamedicos) == 0)
            {
                cout << "nao existem medicos cadastrados para atender, cadastre no minimo 1 medico\n";
            }
            else
            {

                atualizar(&filaPacientes, &filaPacientesAtendidos, &filamedicos, &filaMedicosDisponiveis);

                cout << "deseja atualizar\n";
                cin >> opcao;

                while (opcao == 's')
                {
                    if (Tamanho(&filaPacientesAtendidos) == Tamanho(&filaPacientes))
                    {
                        cout << "Todos os pacientes foram atendidos\n";
                        break;
                    }
                    else
                    {
                        atualizar(&filaPacientes, &filaPacientesAtendidos, &filamedicos, &filaMedicosDisponiveis);
                        cout << "deseja atualizar\n";
                        cin >> opcao;
                    }
                    break;
                }
            }

            system("PAUSE");
            break;
        }

    } while (opcao != 5);

    return 0;
}

void atualizar(TipoFila *filaPacientes, TipoFila *filaPacientesAtendidos, TipoFila *filamedicos, TipoFila *filaMedicosDisponiveis)
{

    Apontador aux = filaPacientes->inicio;
    Apontador aux2 = filamedicos->inicio;
    aux2->medico.disponivel = true;

    for (int i = 0; i < filamedicos->tamanho; i++)
    {

        aux->paciente.h_saida = time(NULL);
        aux->paciente.tempo = aux->paciente.h_saida - aux->paciente.h_chegada;

        cout << "Paciente:  " << aux->paciente.nome << " foi atendido em: " << aux->paciente.tempo << "   minutos"
             << "  pelo medico   " << aux2->medico.nome << "\n\n";

        cout << "Paciente atendido com sucesso!\n";
        aux->paciente.atendido = true;
        aux2->medico.disponivel = false;

        if (aux->paciente.atendido == true)
        {
            EnfileiraPrioridade(filaPacientesAtendidos, aux->paciente);
            DesenfileiraPaciente(filaPacientes, &aux->paciente);
        }
        if (filaPacientes->tamanho == filaPacientesAtendidos->tamanho)
        {
            if (aux2->medico.disponivel == true)
            {

                EnfileiraMedico(filaMedicosDisponiveis, aux2->medico);
            }

            break; // se todos os pacientes forem atendidos e sobrar medico, volta para o menu
        }
        aux2 = aux2->prox;
        aux = aux->prox;
        Sleep(1000);
    }
}