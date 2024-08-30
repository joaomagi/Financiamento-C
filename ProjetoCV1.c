#include <stdio.h>
#include <locale.h>

#define MAX_CONTRATOS 100  // Define o número máximo de contratos que podem ser inseridos


// https://www.inf.pucrs.br/~pinho/LaproI/Structs/Structs.htm
// https://www.w3schools.com/c/c_structs.php
// https://www.ime.usp.br/~pf/algoritmos/aulas/stru.html
// https://www.feg.unesp.br/Home/PaginasPessoais/profmarcosapereira3168/programacaodecomputadoresi/manual-de-sintaxe-da-linguagem-c.pdf
// Variáveis principais para armazenar informações dos contratos
int tipoFinanciamento;
float valorFinanciamento;
int duracaoFinanciamentoMeses;
int entrada;
int bomHistoricoCredito;
int numeroDoContrato;
int opcao;
int contratosfeitos = 0;  // Contador de contratos inseridos

// Variáveis para armazenar os valores com desconto e juros
float valorFinanciamentoComDesconto;
float valorFinanciamentoComJuros;
int mesesAntecipados;
float valorFinanciamentoSemDesconto;

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
            printf("case3");  // Placeholder
            break;
        case 4:
            printf("case4");  // Placeholder
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
    // Verifica se o número máximo de contratos foi alcançado
    if (contratosfeitos >= MAX_CONTRATOS) {
        printf("Número máximo de contratos alcançado.\n");
        return;
    }

    // Coleta informações do usuário sobre o contrato
    printf("Insira o número do contrato: ");
    scanf("%d",&numeroDoContrato);

    printf("1 para Imobiliário, 2 para Veículos, 3 para Pessoal  \n");
    printf("Insira o tipo de financiamento: ");
    scanf("%d",&tipoFinanciamento);
    if (tipoFinanciamento != 1 && tipoFinanciamento != 2 && tipoFinanciamento != 3){
        printf("Tipo INVÁLIDO.Escolha entre 1,2 ou 3 \n");
        limparVariaveis();
        return;
    }

    printf("Insira o valor financiado: ");
    scanf("%f",&valorFinanciamento);

    printf("Insira a duração do contrato em meses: ");
    scanf("%d",&duracaoFinanciamentoMeses);

    printf("Insira a entrada (em porcentagem do valor total): ");
    scanf("%d",&entrada);

    printf("Deseja antecipar alguns meses? Se sim quantos: ");
    scanf("%d",&mesesAntecipados);

    printf("Bom histórico de crédito (1 para sim, 0 para não): ");
    scanf("%d",&bomHistoricoCredito);

    // Verifica se o número de meses antecipados é maior que a duração do financiamento
    if (mesesAntecipados > duracaoFinanciamentoMeses){
        printf("A quantidade de meses antecipados é maior que a de meses de finaciamento! \n");
        // Reseta todas as variáveis de contrato se a antecipação for inválida
        limparVariaveis();
        return;
    }

    // Calcula juros e descontos aplicáveis
    calculoDoJuros();

    // Incrementa o contador de contratos
    contratosfeitos ++;
}

// Função para calcular juros e descontos no financiamento
void calculoDoJuros(){

    // Define valorFinanciamentoSemDesconto com base no tipo de financiamento
    if (tipoFinanciamento == 1) {
        // Financiamento imobiliário
        printf("FINANCIAMENTO IMOBILIÁRIO\n");
        valorFinanciamentoSemDesconto = valorFinanciamento + (valorFinanciamento * 0.005) * duracaoFinanciamentoMeses;

    } else if (tipoFinanciamento == 2) {
        // Financiamento de veículos
        printf("FINANCIAMENTO DE VEÍCULOS\n");
        valorFinanciamentoSemDesconto = valorFinanciamento + (valorFinanciamento * 0.008) * duracaoFinanciamentoMeses;

    } else if (tipoFinanciamento == 3) {
        // Financiamento pessoal
        printf("FINANCIAMENTO PESSOAL\n");
        valorFinanciamentoSemDesconto = valorFinanciamento + (valorFinanciamento * 0.012) * duracaoFinanciamentoMeses;

    } else {
        // Caso não reconhecido
        printf("Tipo de financiamento inválido.\n");
        valorFinanciamentoSemDesconto = valorFinanciamento;  // Valor padrão
    }

    // Valor do financiamento por mês antes da antecipação
    float valorPorMesOriginal = valorFinanciamentoSemDesconto / duracaoFinanciamentoMeses;

    // Desconto por mês antecipado
    float descontoPorMes = valorPorMesOriginal * 0.05;

    // Valor total antecipado
    float valorTotalAntecipado = (valorPorMesOriginal - descontoPorMes) * mesesAntecipados;

    // Atualiza o valorFinanciamentoComJuros subtraindo o valor total antecipado
    valorFinanciamentoComJuros = valorFinanciamentoSemDesconto - valorTotalAntecipado;

    // PARA FINS DE TESTE
    printf("Valor a ser pago dos meses antecipados: %.2f\n", valorTotalAntecipado);

    // Aplica descontos baseados na entrada e no histórico de crédito
    valorFinanciamentoComDesconto = valorFinanciamentoComJuros;

    if (entrada >= 20 && bomHistoricoCredito == 1) {
        // Se o cliente tiver entrada de 20% ou mais e bom histórico de crédito
        valorFinanciamentoComDesconto -= (valorFinanciamentoComJuros * 0.1) + (valorFinanciamentoComJuros * 0.08);

    } else if (entrada >= 20) {
        // Se o cliente tiver entrada de 20% ou mais
        valorFinanciamentoComDesconto -= valorFinanciamentoComJuros * 0.1;

    } else if (bomHistoricoCredito == 1) {
        // Se o cliente tiver bom histórico de crédito
        valorFinanciamentoComDesconto -= valorFinanciamentoComJuros * 0.08;
    }

    // PARA FINS DE TESTE
    printf("valorFinanciamentoCom desconto %.2f\n", valorFinanciamentoComDesconto);

    // Ajusta para evitar valor negativo pós descontos
    if (valorFinanciamentoComDesconto < 0) {
        valorFinanciamentoComDesconto = 0;
    }
}

void limparVariaveis(){ // função para limpar as variaveis

        numeroDoContrato = 0;
        tipoFinanciamento = 0;
        valorFinanciamento = 0;
        duracaoFinanciamentoMeses = 0;
        entrada = 0;
        bomHistoricoCredito = 0;
        numeroDoContrato = 0;
        mesesAntecipados = 0;
}

// Função para apresentar resultados dos contratos inseridos
void apresentarResultados(){
    if (contratosfeitos == 0){
        printf("Nenhum contrato inserido.\n");
        return;
    }
    printf("Número de contratos inseridos: %d\n", contratosfeitos);
    printf("Número do último contrato: %d\n", numeroDoContrato);
}

// Função principal que inicializa o programa e exibe o menu até que o usuário escolha sair
int main() {
    setlocale(LC_ALL, "Portuguese");  // Define para o português
    do {
        MenuInicial();  // Exibe o menu e processa a opção escolhida
    } while (opcao != 0);  // Continua exibindo o menu até que a opção 0 (sair) seja escolhida
    return 0;
}
