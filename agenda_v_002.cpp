#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_AGENDAMENTOS 100

typedef struct {
    char nome[100];
    char cpf[12];
    char dataNascimento[11];
    char telefone[15];
    char email[100];
} Cliente;

typedef struct {
    int idCliente;
    char horario[6];
} Agendamento;

Cliente clientes[MAX_CLIENTES];
Agendamento agendamentos[MAX_AGENDAMENTOS];
int totalClientes = 0;
int totalAgendamentos = 0;

void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }

    Cliente novoCliente;

    printf("Nome completo: ");
    fgets(novoCliente.nome, 100, stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

    printf("CPF: ");
    fgets(novoCliente.cpf, 12, stdin);
    novoCliente.cpf[strcspn(novoCliente.cpf, "\n")] = '\0';

    printf("Data de Nascimento (dd/mm/aaaa): ");
    fgets(novoCliente.dataNascimento, 11, stdin);
    novoCliente.dataNascimento[strcspn(novoCliente.dataNascimento, "\n")] = '\0';

    printf("Telefone: ");
    fgets(novoCliente.telefone, 15, stdin);
    novoCliente.telefone[strcspn(novoCliente.telefone, "\n")] = '\0';

    printf("E-mail: ");
    fgets(novoCliente.email, 100, stdin);
    novoCliente.email[strcspn(novoCliente.email, "\n")] = '\0';

    clientes[totalClientes++] = novoCliente;

    printf("Cliente cadastrado com sucesso!\n");
}

void agendarHorario() {
    if (totalAgendamentos >= MAX_AGENDAMENTOS) {
        printf("Limite de agendamentos atingido!\n");
        return;
    }

    int idCliente;
    char horario[6];

    printf("ID do cliente: ");
    scanf("%d", &idCliente);
    getchar();

    if (idCliente < 0 || idCliente >= totalClientes) {
        printf("Cliente não encontrado!\n");
        return;
    }
    
    printf("Horários disponíveis:\n");
	  for (int hora = 9; hora < 18; hora++) {
	    for (int minuto = 0; minuto < 60; minuto += 30) {
	      char horarioDisponivel[6];
	      sprintf(horarioDisponivel, "%02d:%02d", hora, minuto);
	
	      bool isAvailable = true;
	      for (int i = 0; i < totalAgendamentos; i++) {
	        if (strcmp(agendamentos[i].horario, horarioDisponivel) == 0) {
	          isAvailable = false;
	          break;
	        }
	      }
	
	      if (isAvailable) {
	        printf("- %s\n", horarioDisponivel);
	      }
	    }
	  }

    printf("\nEscolha um horário (hh:mm): ");
    fgets(horario, 6, stdin);
    horario[strcspn(horario, "\n")] = '\0';

    
    int hora, minuto;
    sscanf(horario, "%d:%d", &hora, &minuto);

    if ((hora < 9 || hora >= 18) || (hora >= 12 && hora < 14)) {
        printf("Horário fora do intervalo de atendimento!\n");
        return;
    }

    for (int i = 0; i < totalAgendamentos; i++) {
        if (strcmp(agendamentos[i].horario, horario) == 0) {
            printf("Horário já ocupado!\n");
            return;
        }
    }

    Agendamento novoAgendamento;
    novoAgendamento.idCliente = idCliente;
    strcpy(novoAgendamento.horario, horario);

    agendamentos[totalAgendamentos++] = novoAgendamento;

    printf("Horário agendado com sucesso!\n");
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Agendar Horário\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                agendarHorario();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 3);

    return 0;
}
