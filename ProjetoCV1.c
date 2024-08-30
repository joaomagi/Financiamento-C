#include <stdio.h>
#include <locale.h>

#define MAX_CONTRATOS 100  // Define o n�mero m�ximo de contratos que podem ser inseridos


// https://www.inf.pucrs.br/~pinho/LaproI/Structs/Structs.htm
// https://www.w3schools.com/c/c_structs.php
// https://www.ime.usp.br/~pf/algoritmos/aulas/stru.html
// https://www.feg.unesp.br/Home/PaginasPessoais/profmarcosapereira3168/programacaodecomputadoresi/manual-de-sintaxe-da-linguagem-c.pdf
// Vari�veis principais para armazenar informa��es dos contratos
int tipoFinanciamento;
float valorFinanciamento;
int duracaoFinanciamentoMeses;
int entrada;
int bomHistoricoCredito;
int numeroDoContrato;
int opcao;
int contratosfeitos = 0;  // Contador de contratos inseridos

// Vari�veis para armazenar os valores com desconto e juros
float valorFinanciamentoComDesconto;
float valorFinanciamentoComJuros;
int mesesAntecipados;
float valorFinanciamentoSemDesconto;

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
            printf("case3");  // Placeholder
            break;
        case 4:
            printf("case4");  // Placeholder
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
    // Verifica se o n�mero m�ximo de contratos foi alcan�ado
    if (contratosfeitos >= MAX_CONTRATOS) {
        printf("N�mero m�ximo de contratos alcan�ado.\n");
        return;
    }

    // Coleta informa��es do usu�rio sobre o contrato
    printf("Insira o n�mero do contrato: ");
    scanf("%d",&numeroDoContrato);

    printf("1 para Imobili�rio, 2 para Ve�culos, 3 para Pessoal  \n");
    printf("Insira o tipo de financiamento: ");
    scanf("%d",&tipoFinanciamento);
    if (tipoFinanciamento != 1 && tipoFinanciamento != 2 && tipoFinanciamento != 3){
        printf("Tipo INV�LIDO.Escolha entre 1,2 ou 3 \n");
        limparVariaveis();
        return;
    }

    printf("Insira o valor financiado: ");
    scanf("%f",&valorFinanciamento);

    printf("Insira a dura��o do contrato em meses: ");
    scanf("%d",&duracaoFinanciamentoMeses);

    printf("Insira a entrada (em porcentagem do valor total): ");
    scanf("%d",&entrada);

    printf("Deseja antecipar alguns meses? Se sim quantos: ");
    scanf("%d",&mesesAntecipados);

    printf("Bom hist�rico de cr�dito (1 para sim, 0 para n�o): ");
    scanf("%d",&bomHistoricoCredito);

    // Verifica se o n�mero de meses antecipados � maior que a dura��o do financiamento
    if (mesesAntecipados > duracaoFinanciamentoMeses){
        printf("A quantidade de meses antecipados � maior que a de meses de finaciamento! \n");
        // Reseta todas as vari�veis de contrato se a antecipa��o for inv�lida
        limparVariaveis();
        return;
    }

    // Calcula juros e descontos aplic�veis
    calculoDoJuros();

    // Incrementa o contador de contratos
    contratosfeitos ++;
}

// Fun��o para calcular juros e descontos no financiamento
void calculoDoJuros(){

    // Define valorFinanciamentoSemDesconto com base no tipo de financiamento
    if (tipoFinanciamento == 1) {
        // Financiamento imobili�rio
        printf("FINANCIAMENTO IMOBILI�RIO\n");
        valorFinanciamentoSemDesconto = valorFinanciamento + (valorFinanciamento * 0.005) * duracaoFinanciamentoMeses;

    } else if (tipoFinanciamento == 2) {
        // Financiamento de ve�culos
        printf("FINANCIAMENTO DE VE�CULOS\n");
        valorFinanciamentoSemDesconto = valorFinanciamento + (valorFinanciamento * 0.008) * duracaoFinanciamentoMeses;

    } else if (tipoFinanciamento == 3) {
        // Financiamento pessoal
        printf("FINANCIAMENTO PESSOAL\n");
        valorFinanciamentoSemDesconto = valorFinanciamento + (valorFinanciamento * 0.012) * duracaoFinanciamentoMeses;

    } else {
        // Caso n�o reconhecido
        printf("Tipo de financiamento inv�lido.\n");
        valorFinanciamentoSemDesconto = valorFinanciamento;  // Valor padr�o
    }

    // Valor do financiamento por m�s antes da antecipa��o
    float valorPorMesOriginal = valorFinanciamentoSemDesconto / duracaoFinanciamentoMeses;

    // Desconto por m�s antecipado
    float descontoPorMes = valorPorMesOriginal * 0.05;

    // Valor total antecipado
    float valorTotalAntecipado = (valorPorMesOriginal - descontoPorMes) * mesesAntecipados;

    // Atualiza o valorFinanciamentoComJuros subtraindo o valor total antecipado
    valorFinanciamentoComJuros = valorFinanciamentoSemDesconto - valorTotalAntecipado;

    // PARA FINS DE TESTE
    printf("Valor a ser pago dos meses antecipados: %.2f\n", valorTotalAntecipado);

    // Aplica descontos baseados na entrada e no hist�rico de cr�dito
    valorFinanciamentoComDesconto = valorFinanciamentoComJuros;

    if (entrada >= 20 && bomHistoricoCredito == 1) {
        // Se o cliente tiver entrada de 20% ou mais e bom hist�rico de cr�dito
        valorFinanciamentoComDesconto -= (valorFinanciamentoComJuros * 0.1) + (valorFinanciamentoComJuros * 0.08);

    } else if (entrada >= 20) {
        // Se o cliente tiver entrada de 20% ou mais
        valorFinanciamentoComDesconto -= valorFinanciamentoComJuros * 0.1;

    } else if (bomHistoricoCredito == 1) {
        // Se o cliente tiver bom hist�rico de cr�dito
        valorFinanciamentoComDesconto -= valorFinanciamentoComJuros * 0.08;
    }

    // PARA FINS DE TESTE
    printf("valorFinanciamentoCom desconto %.2f\n", valorFinanciamentoComDesconto);

    // Ajusta para evitar valor negativo p�s descontos
    if (valorFinanciamentoComDesconto < 0) {
        valorFinanciamentoComDesconto = 0;
    }
}

void limparVariaveis(){ // fun��o para limpar as variaveis

        numeroDoContrato = 0;
        tipoFinanciamento = 0;
        valorFinanciamento = 0;
        duracaoFinanciamentoMeses = 0;
        entrada = 0;
        bomHistoricoCredito = 0;
        numeroDoContrato = 0;
        mesesAntecipados = 0;
}

// Fun��o para apresentar resultados dos contratos inseridos
void apresentarResultados(){
    if (contratosfeitos == 0){
        printf("Nenhum contrato inserido.\n");
        return;
    }
    printf("N�mero de contratos inseridos: %d\n", contratosfeitos);
    printf("N�mero do �ltimo contrato: %d\n", numeroDoContrato);
}

// Fun��o principal que inicializa o programa e exibe o menu at� que o usu�rio escolha sair
int main() {
    setlocale(LC_ALL, "Portuguese");  // Define para o portugu�s
    do {
        MenuInicial();  // Exibe o menu e processa a op��o escolhida
    } while (opcao != 0);  // Continua exibindo o menu at� que a op��o 0 (sair) seja escolhida
    return 0;
}
