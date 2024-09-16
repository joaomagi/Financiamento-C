#include <stdio.h>
#include <locale.h>

#define MAX_CONTRATOS 100  // Define o número máximo de contratos que podem ser inseridos

int tipoFinanciamento[MAX_CONTRATOS];
float valorFinanciamento[MAX_CONTRATOS];
int duracaoFinanciamentoMeses[MAX_CONTRATOS];
int entrada[MAX_CONTRATOS];
int bomHistoricoCredito[MAX_CONTRATOS];
int numeroDoContrato[MAX_CONTRATOS];

int opcao;
int contratosfeitos = 0;  // Contador de contratos inseridos

// Variáveis para armazenar os valores com desconto e juros
float valorFinanciamentoComDesconto[MAX_CONTRATOS];
float valorFinanciamentoComJuros[MAX_CONTRATOS];
int mesesAntecipados[MAX_CONTRATOS];
float valorFinanciamentoSemDesconto[MAX_CONTRATOS];

// Função para exibir o menu inicial e processar a escolha do usuário
void MenuInicial(){
    printf("###################################################### \n"
           "0) Sair \n"
           "1) Inserir contratos \n"
           "2) Apresentar resultados \n"
           "3) Ordenar os contratos pelo valor total (decrescente) \n"
           "4) Imprimir registros de contratos \n"
           "###################################################### \n");

    printf("Escolha uma opção => ");
    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            InserirContratos();  // Chama a função para inserir contratos
            break;
        case 2:
            apresentarResultados(); // chama a função para apresentar resultado
            break;
        case 3:
            ordenarContratosDecrescente(); // chama a função para ordenar os resultados ja em ordem decrescente
            break;
        case 4:
            ImprimirRegistrosContratos(); // chama a função para o usuario escolher o registro que deseja imprimir
            break;
        case 0:
            printf("Saindo do Programa....");  // Mensagem de saída do programa
            break;
        default:
            printf("Número inválido \n");  // Mensagem para opção inválida
            break;
    }
}

// Função para inserir um novo contrato
void InserirContratos (){
    limparTela();
    // Verifica se o número máximo de contratos foi alcançado
    if (contratosfeitos >= MAX_CONTRATOS) {
        printf("Número máximo de contratos alcançado.\n");
        return;
    }

    int posicaoContrato = contratosfeitos;
    // Coleta informações do usuário sobre o contrato
    printf("Insira o número do contrato: ");
    scanf("%d",&numeroDoContrato[posicaoContrato]);

    printf("1 para Imobiliário, 2 para Veículos, 3 para Pessoal  \n");
    printf("Insira o tipo de financiamento: ");
    scanf("%d",&tipoFinanciamento[posicaoContrato]);

    if (tipoFinanciamento[posicaoContrato] != 1 && tipoFinanciamento[posicaoContrato] != 2 && tipoFinanciamento[posicaoContrato] != 3){
        printf("Tipo INVÁLIDO.Escolha entre 1,2 ou 3 \n");
        return;
    }

    printf("Insira o valor financiado: ");
    scanf("%f",&valorFinanciamento[posicaoContrato]);

    printf("Insira a duração do contrato em meses: ");
    scanf("%d",&duracaoFinanciamentoMeses[posicaoContrato]);

    printf("Insira a entrada (em porcentagem do valor total): ");
    scanf("%d",&entrada[posicaoContrato]);

    printf("Deseja antecipar alguns meses? Se sim quantos: ");
    scanf("%d",&mesesAntecipados[posicaoContrato]);

    printf("Bom histórico de crédito (1 para sim, 0 para não): ");
    scanf("%d",&bomHistoricoCredito[posicaoContrato]);

    // Verifica se o número de meses antecipados é maior que a duração do financiamento
    if (mesesAntecipados[posicaoContrato] > duracaoFinanciamentoMeses[posicaoContrato]){
        printf("A quantidade de meses antecipados é maior que a de meses de finaciamento! \n");
        return;
    }

    // Calcula juros e descontos aplicáveis
    calculoDoJuros(posicaoContrato);

    // Incrementa o contador de contratos
    contratosfeitos ++;
}

// Função para calcular juros e descontos no financiamento
void calculoDoJuros(int posicaoContrato){

    // Define valorFinanciamentoSemDesconto com base no tipo de financiamento
    if (tipoFinanciamento[posicaoContrato] == 1) {
        // Financiamento imobiliário
        valorFinanciamentoSemDesconto[posicaoContrato] = valorFinanciamento[posicaoContrato] + (valorFinanciamento[posicaoContrato] * 0.005) * duracaoFinanciamentoMeses[posicaoContrato];

    } else if (tipoFinanciamento[posicaoContrato] == 2) {
        // Financiamento de veículos
        valorFinanciamentoSemDesconto[posicaoContrato] = valorFinanciamento[posicaoContrato] + (valorFinanciamento[posicaoContrato] * 0.008) * duracaoFinanciamentoMeses[posicaoContrato];

    } else if (tipoFinanciamento[posicaoContrato] == 3) {
        // Financiamento pessoal
        valorFinanciamentoSemDesconto[posicaoContrato] = valorFinanciamento[posicaoContrato] + (valorFinanciamento[posicaoContrato] * 0.012) * duracaoFinanciamentoMeses[posicaoContrato];

    } else {
        // Caso não reconhecido
        printf("Tipo de financiamento inválido.\n");
        valorFinanciamentoSemDesconto[posicaoContrato] = valorFinanciamento[posicaoContrato];  // Valor padrão
    }

    // Valor do financiamento por mês antes da antecipação
    float valorPorMesOriginal = valorFinanciamentoSemDesconto[posicaoContrato] / duracaoFinanciamentoMeses[posicaoContrato];

    // Desconto por mês antecipado
    float descontoPorMes = valorPorMesOriginal * 0.05;

    // Valor total antecipado
    float valorTotalAntecipado = (valorPorMesOriginal - descontoPorMes) * mesesAntecipados[posicaoContrato];

    // Atualiza o valorFinanciamentoComJuros subtraindo o valor total antecipado
    valorFinanciamentoComJuros[posicaoContrato] = valorFinanciamentoSemDesconto[posicaoContrato] - valorTotalAntecipado;

    // Aplica descontos baseados na entrada e no histórico de crédito
    valorFinanciamentoComDesconto[posicaoContrato] = valorFinanciamentoComJuros[posicaoContrato];

    if (entrada[posicaoContrato] >= 20 && bomHistoricoCredito[posicaoContrato] == 1) {
        // Se o cliente tiver entrada de 20% ou mais e bom histórico de crédito
        valorFinanciamentoComDesconto[posicaoContrato] -= (valorFinanciamentoComJuros[posicaoContrato] * 0.1) + (valorFinanciamentoComJuros[posicaoContrato] * 0.08);

    } else if (entrada[posicaoContrato] >= 20) {
        // Se o cliente tiver entrada de 20% ou mais
        valorFinanciamentoComDesconto[posicaoContrato] -= valorFinanciamentoComJuros[posicaoContrato] * 0.1;

    } else if (bomHistoricoCredito[posicaoContrato] == 1) {
        // Se o cliente tiver bom histórico de crédito
        valorFinanciamentoComDesconto[posicaoContrato] -= valorFinanciamentoComJuros[posicaoContrato] * 0.08;
    }

    // Ajusta para evitar valor negativo pós descontos
    if (valorFinanciamentoComDesconto[posicaoContrato] < 0) {
        valorFinanciamentoComDesconto[posicaoContrato] = 0;
    }
}



// Função para apresentar resultados dos contratos inseridos
void apresentarResultados(){
    limparTela();
    if (contratosfeitos == 0){
        printf("Nenhum contrato inserido.\n");
        return;
    }
    for (int i = 0; i < contratosfeitos; i++) {
        printf("Contrato %d:\n", i + 1);
        printf("Número do contrato: %d\n", numeroDoContrato[i]);
        printf("Tipo de financiamento: %d\n", tipoFinanciamento[i]);
        printf("Valor financiado: %.2f\n", valorFinanciamento[i]);
        printf("Duração em meses: %d\n", duracaoFinanciamentoMeses[i]);
        printf("Entrada: %d%%\n", entrada[i]);
        printf("Bom histórico de crédito: %d\n", bomHistoricoCredito[i]);
        printf("Valor com desconto: %.2f\n", valorFinanciamentoComDesconto[i]);
        printf("------------------------------\n");
    }
}
// Função para Ordenar os contratos e depois imprimir para o usuario
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

                // Trocar os números dos contratos
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

                // Trocar as durações
                int tempDuracao = duracaoFinanciamentoMeses[j];
                duracaoFinanciamentoMeses[j] = duracaoFinanciamentoMeses[j + 1];
                duracaoFinanciamentoMeses[j + 1] = tempDuracao;

                // Trocar as entradas
                int tempEntrada = entrada[j];
                entrada[j] = entrada[j + 1];
                entrada[j + 1] = tempEntrada;

                // Trocar o histórico de crédito
                int tempHistoricoCredito = bomHistoricoCredito[j];
                bomHistoricoCredito[j] = bomHistoricoCredito[j + 1];
                bomHistoricoCredito[j + 1] = tempHistoricoCredito;
            }
        }
    printf("Contratos ordenados por valor total (decrescente):\n");
    for (int i = 0; i < contratosfeitos; i++) {
        printf("Contrato %d:\n", i + 1);
        printf("Número do contrato: %d\n", numeroDoContrato[i]);
        printf("Tipo de financiamento: %d\n", tipoFinanciamento[i]);
        printf("Valor financiado: %.2f\n", valorFinanciamento[i]);
        printf("Duração em meses: %d\n", duracaoFinanciamentoMeses[i]);
        printf("Entrada: %d%%\n", entrada[i]);
        printf("Bom histórico de crédito: %d\n", bomHistoricoCredito[i]);
        printf("Valor com desconto: %.2f\n", valorFinanciamentoComDesconto[i]);
        printf("------------------------------\n");
    }
}

}

// Função para imprimir os registros de um contrato específico baseado no número do contrato
void ImprimirRegistrosContratos() {
    limparTela();
    if (contratosfeitos == 0) {
        printf("Nenhum contrato inserido.\n");
        return;
    }

    int numeroContrato;
    printf("Digite o número do contrato que deseja visualizar: ");
    scanf("%d", &numeroContrato);

    int encontrado = 0;  // Teste para caso ache o contrato

    for (int i = 0; i < contratosfeitos; i++) {
        if (numeroDoContrato[i] == numeroContrato) {
            printf("Contrato %d:\n", i + 1);
            printf("Número do contrato: %d\n", numeroDoContrato[i]);
            printf("Tipo de financiamento: %d\n", tipoFinanciamento[i]);
            printf("Valor financiado: %.2f\n", valorFinanciamento[i]);
            printf("Duração em meses: %d\n", duracaoFinanciamentoMeses[i]);
            printf("Entrada: %d%%\n", entrada[i]);
            printf("Bom histórico de crédito: %d\n", bomHistoricoCredito[i]);
            printf("Valor com desconto: %.2f\n", valorFinanciamentoComDesconto[i]);
            printf("------------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Contrato com número %d não encontrado.\n", numeroContrato);
    }
}
// Função para limpar a tela do cmd seja sistema windowns ou linux
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// Função principal que inicializa o programa e exibe o menu até que o usuário escolha sair
int main() {
    setlocale(LC_ALL, "Portuguese");  // Define para o português
    do {
        MenuInicial();  // Exibe o menu e processa a opção escolhida
    } while (opcao != 0);  // Continua exibindo o menu até que a opção 0 (sair) seja escolhida
    return 0;
}
