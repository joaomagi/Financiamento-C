#include <stdio.h>
#include <locale.h>

#define MAX_CONTRATOS 100  // Define o n�mero m�ximo de contratos que podem ser inseridos

int tipoFinanciamento[MAX_CONTRATOS];
float valorFinanciamento[MAX_CONTRATOS];
int duracaoFinanciamentoMeses[MAX_CONTRATOS];
int entrada[MAX_CONTRATOS];
int bomHistoricoCredito[MAX_CONTRATOS];
int numeroDoContrato[MAX_CONTRATOS];

int opcao;
int contratosfeitos = 0;  // Contador de contratos inseridos

// Vari�veis para armazenar os valores com desconto e juros
float valorFinanciamentoComDesconto[MAX_CONTRATOS];
float valorFinanciamentoComJuros[MAX_CONTRATOS];
int mesesAntecipados[MAX_CONTRATOS];
float valorFinanciamentoSemDesconto[MAX_CONTRATOS];

// Fun��o para exibir o menu inicial e processar a escolha do usu�rio
void MenuInicial(){
    printf("###################################################### \n"
           "0) Sair \n"
           "1) Inserir contratos \n"
           "2) Apresentar resultados \n"
           "3) Ordenar os contratos pelo valor total (decrescente) \n"
           "4) Imprimir registros de contratos \n"
           "###################################################### \n");

    printf("Escolha uma op��o => ");
    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            InserirContratos();  // Chama a fun��o para inserir contratos
            break;
        case 2:
            apresentarResultados(); // chama a fun��o para apresentar resultado
            break;
        case 3:
            ordenarContratosDecrescente(); // chama a fun��o para ordenar os resultados ja em ordem decrescente
            break;
        case 4:
            ImprimirRegistrosContratos(); // chama a fun��o para o usuario escolher o registro que deseja imprimir
            break;
        case 0:
            printf("Saindo do Programa....");  // Mensagem de sa�da do programa
            break;
        default:
            printf("N�mero inv�lido \n");  // Mensagem para op��o inv�lida
            break;
    }
}

// Fun��o para inserir um novo contrato
void InserirContratos (){
    limparTela();
    // Verifica se o n�mero m�ximo de contratos foi alcan�ado
    if (contratosfeitos >= MAX_CONTRATOS) {
        printf("N�mero m�ximo de contratos alcan�ado.\n");
        return;
    }

    int posicaoContrato = contratosfeitos;
    // Coleta informa��es do usu�rio sobre o contrato
    printf("Insira o n�mero do contrato: ");
    scanf("%d",&numeroDoContrato[posicaoContrato]);

    printf("1 para Imobili�rio, 2 para Ve�culos, 3 para Pessoal  \n");
    printf("Insira o tipo de financiamento: ");
    scanf("%d",&tipoFinanciamento[posicaoContrato]);

    if (tipoFinanciamento[posicaoContrato] != 1 && tipoFinanciamento[posicaoContrato] != 2 && tipoFinanciamento[posicaoContrato] != 3){
        printf("Tipo INV�LIDO.Escolha entre 1,2 ou 3 \n");
        return;
    }

    printf("Insira o valor financiado: ");
    scanf("%f",&valorFinanciamento[posicaoContrato]);

    printf("Insira a dura��o do contrato em meses: ");
    scanf("%d",&duracaoFinanciamentoMeses[posicaoContrato]);

    printf("Insira a entrada (em porcentagem do valor total): ");
    scanf("%d",&entrada[posicaoContrato]);

    printf("Deseja antecipar alguns meses? Se sim quantos: ");
    scanf("%d",&mesesAntecipados[posicaoContrato]);

    printf("Bom hist�rico de cr�dito (1 para sim, 0 para n�o): ");
    scanf("%d",&bomHistoricoCredito[posicaoContrato]);

    // Verifica se o n�mero de meses antecipados � maior que a dura��o do financiamento
    if (mesesAntecipados[posicaoContrato] > duracaoFinanciamentoMeses[posicaoContrato]){
        printf("A quantidade de meses antecipados � maior que a de meses de finaciamento! \n");
        return;
    }

    // Calcula juros e descontos aplic�veis
    calculoDoJuros(posicaoContrato);

    // Incrementa o contador de contratos
    contratosfeitos ++;
}

// Fun��o para calcular juros e descontos no financiamento
void calculoDoJuros(int posicaoContrato){

    // Define valorFinanciamentoSemDesconto com base no tipo de financiamento
    if (tipoFinanciamento[posicaoContrato] == 1) {
        // Financiamento imobili�rio
        valorFinanciamentoSemDesconto[posicaoContrato] = valorFinanciamento[posicaoContrato] + (valorFinanciamento[posicaoContrato] * 0.005) * duracaoFinanciamentoMeses[posicaoContrato];

    } else if (tipoFinanciamento[posicaoContrato] == 2) {
        // Financiamento de ve�culos
        valorFinanciamentoSemDesconto[posicaoContrato] = valorFinanciamento[posicaoContrato] + (valorFinanciamento[posicaoContrato] * 0.008) * duracaoFinanciamentoMeses[posicaoContrato];

    } else if (tipoFinanciamento[posicaoContrato] == 3) {
        // Financiamento pessoal
        valorFinanciamentoSemDesconto[posicaoContrato] = valorFinanciamento[posicaoContrato] + (valorFinanciamento[posicaoContrato] * 0.012) * duracaoFinanciamentoMeses[posicaoContrato];

    } else {
        // Caso n�o reconhecido
        printf("Tipo de financiamento inv�lido.\n");
        valorFinanciamentoSemDesconto[posicaoContrato] = valorFinanciamento[posicaoContrato];  // Valor padr�o
    }

    // Valor do financiamento por m�s antes da antecipa��o
    float valorPorMesOriginal = valorFinanciamentoSemDesconto[posicaoContrato] / duracaoFinanciamentoMeses[posicaoContrato];

    // Desconto por m�s antecipado
    float descontoPorMes = valorPorMesOriginal * 0.05;

    // Valor total antecipado
    float valorTotalAntecipado = (valorPorMesOriginal - descontoPorMes) * mesesAntecipados[posicaoContrato];

    // Atualiza o valorFinanciamentoComJuros subtraindo o valor total antecipado
    valorFinanciamentoComJuros[posicaoContrato] = valorFinanciamentoSemDesconto[posicaoContrato] - valorTotalAntecipado;

    // Aplica descontos baseados na entrada e no hist�rico de cr�dito
    valorFinanciamentoComDesconto[posicaoContrato] = valorFinanciamentoComJuros[posicaoContrato];

    if (entrada[posicaoContrato] >= 20 && bomHistoricoCredito[posicaoContrato] == 1) {
        // Se o cliente tiver entrada de 20% ou mais e bom hist�rico de cr�dito
        valorFinanciamentoComDesconto[posicaoContrato] -= (valorFinanciamentoComJuros[posicaoContrato] * 0.1) + (valorFinanciamentoComJuros[posicaoContrato] * 0.08);

    } else if (entrada[posicaoContrato] >= 20) {
        // Se o cliente tiver entrada de 20% ou mais
        valorFinanciamentoComDesconto[posicaoContrato] -= valorFinanciamentoComJuros[posicaoContrato] * 0.1;

    } else if (bomHistoricoCredito[posicaoContrato] == 1) {
        // Se o cliente tiver bom hist�rico de cr�dito
        valorFinanciamentoComDesconto[posicaoContrato] -= valorFinanciamentoComJuros[posicaoContrato] * 0.08;
    }

    // Ajusta para evitar valor negativo p�s descontos
    if (valorFinanciamentoComDesconto[posicaoContrato] < 0) {
        valorFinanciamentoComDesconto[posicaoContrato] = 0;
    }
}



// Fun��o para apresentar resultados dos contratos inseridos
void apresentarResultados(){
    limparTela();
    if (contratosfeitos == 0){
        printf("Nenhum contrato inserido.\n");
        return;
    }
    for (int i = 0; i < contratosfeitos; i++) {
        printf("Contrato %d:\n", i + 1);
        printf("N�mero do contrato: %d\n", numeroDoContrato[i]);
        printf("Tipo de financiamento: %d\n", tipoFinanciamento[i]);
        printf("Valor financiado: %.2f\n", valorFinanciamento[i]);
        printf("Dura��o em meses: %d\n", duracaoFinanciamentoMeses[i]);
        printf("Entrada: %d%%\n", entrada[i]);
        printf("Bom hist�rico de cr�dito: %d\n", bomHistoricoCredito[i]);
        printf("Valor com desconto: %.2f\n", valorFinanciamentoComDesconto[i]);
        printf("------------------------------\n");
    }
}
// Fun��o para Ordenar os contratos e depois imprimir para o usuario
void ordenarContratosDecrescente() {
    limparTela();
    if (contratosfeitos < 2){
        printf("Contratos Insuficientes para Ordenar!\n");
        return;
    }
// Bubble Sort
    for (int i = 0; i < contratosfeitos - 1; i++) {
        for (int j = 0; j < contratosfeitos - i - 1; j++) {
            if (valorFinanciamentoComDesconto[j] < valorFinanciamentoComDesconto[j + 1]) {
                // Trocar os valores
                float tempValor = valorFinanciamentoComDesconto[j];
                valorFinanciamentoComDesconto[j] = valorFinanciamentoComDesconto[j + 1];
                valorFinanciamentoComDesconto[j + 1] = tempValor;

                // Trocar os n�meros dos contratos
                int tempNumero = numeroDoContrato[j];
                numeroDoContrato[j] = numeroDoContrato[j + 1];
                numeroDoContrato[j + 1] = tempNumero;

                // Trocar os tipos de financiamento
                int tempTipo = tipoFinanciamento[j];
                tipoFinanciamento[j] = tipoFinanciamento[j + 1];
                tipoFinanciamento[j + 1] = tempTipo;

                // Trocar os valores financiados
                float tempValorFinanciado = valorFinanciamento[j];
                valorFinanciamento[j] = valorFinanciamento[j + 1];
                valorFinanciamento[j + 1] = tempValorFinanciado;

                // Trocar as dura��es
                int tempDuracao = duracaoFinanciamentoMeses[j];
                duracaoFinanciamentoMeses[j] = duracaoFinanciamentoMeses[j + 1];
                duracaoFinanciamentoMeses[j + 1] = tempDuracao;

                // Trocar as entradas
                int tempEntrada = entrada[j];
                entrada[j] = entrada[j + 1];
                entrada[j + 1] = tempEntrada;

                // Trocar o hist�rico de cr�dito
                int tempHistoricoCredito = bomHistoricoCredito[j];
                bomHistoricoCredito[j] = bomHistoricoCredito[j + 1];
                bomHistoricoCredito[j + 1] = tempHistoricoCredito;
            }
        }
    printf("Contratos ordenados por valor total (decrescente):\n");
    for (int i = 0; i < contratosfeitos; i++) {
        printf("Contrato %d:\n", i + 1);
        printf("N�mero do contrato: %d\n", numeroDoContrato[i]);
        printf("Tipo de financiamento: %d\n", tipoFinanciamento[i]);
        printf("Valor financiado: %.2f\n", valorFinanciamento[i]);
        printf("Dura��o em meses: %d\n", duracaoFinanciamentoMeses[i]);
        printf("Entrada: %d%%\n", entrada[i]);
        printf("Bom hist�rico de cr�dito: %d\n", bomHistoricoCredito[i]);
        printf("Valor com desconto: %.2f\n", valorFinanciamentoComDesconto[i]);
        printf("------------------------------\n");
    }
}

}

// Fun��o para imprimir os registros de um contrato espec�fico baseado no n�mero do contrato
void ImprimirRegistrosContratos() {
    limparTela();
    if (contratosfeitos == 0) {
        printf("Nenhum contrato inserido.\n");
        return;
    }

    int numeroContrato;
    printf("Digite o n�mero do contrato que deseja visualizar: ");
    scanf("%d", &numeroContrato);

    int encontrado = 0;  // Teste para caso ache o contrato

    for (int i = 0; i < contratosfeitos; i++) {
        if (numeroDoContrato[i] == numeroContrato) {
            printf("Contrato %d:\n", i + 1);
            printf("N�mero do contrato: %d\n", numeroDoContrato[i]);
            printf("Tipo de financiamento: %d\n", tipoFinanciamento[i]);
            printf("Valor financiado: %.2f\n", valorFinanciamento[i]);
            printf("Dura��o em meses: %d\n", duracaoFinanciamentoMeses[i]);
            printf("Entrada: %d%%\n", entrada[i]);
            printf("Bom hist�rico de cr�dito: %d\n", bomHistoricoCredito[i]);
            printf("Valor com desconto: %.2f\n", valorFinanciamentoComDesconto[i]);
            printf("------------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Contrato com n�mero %d n�o encontrado.\n", numeroContrato);
    }
}
// Fun��o para limpar a tela do cmd seja sistema windowns ou linux
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// Fun��o principal que inicializa o programa e exibe o menu at� que o usu�rio escolha sair
int main() {
    setlocale(LC_ALL, "Portuguese");  // Define para o portugu�s
    do {
        MenuInicial();  // Exibe o menu e processa a op��o escolhida
    } while (opcao != 0);  // Continua exibindo o menu at� que a op��o 0 (sair) seja escolhida
    return 0;
}
