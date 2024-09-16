# Gerenciador de Contratos de Financiamento

Este projeto é um gerenciador de contratos de financiamento escrito em C. Ele permite ao usuário inserir contratos de financiamento, calcular valores com juros e descontos, ordenar contratos por valor total e imprimir registros específicos.

## Funcionalidades

- **Inserir Contratos**: Adiciona um novo contrato ao sistema com detalhes como tipo de financiamento, valor financiado, duração, entrada e histórico de crédito.
- **Apresentar Resultados**: Exibe todos os contratos inseridos com detalhes como valor financiado, duração e valor com desconto.
- **Ordenar Contratos**: Ordena os contratos por valor total (decrescente) e exibe a lista ordenada.
- **Imprimir Registros de Contratos**: Permite ao usuário visualizar detalhes de um contrato específico baseado no número do contrato.

## Requisitos

- Compilador C (como GCC)
- Sistema operacional compatível com comandos `cls` (Windows) ou `clear` (Linux)

## Menu

O programa exibe um menu com as seguintes opções:

- `0) Sair`
- `1) Inserir contratos`
- `2) Apresentar resultados`
- `3) Ordenar os contratos pelo valor total (decrescente)`
- `4) Imprimir registros de contratos`

- **Inserir Contratos**: Escolha a opção `1` e forneça as informações solicitadas sobre o contrato.
- **Apresentar Resultados**: Escolha a opção `2` para visualizar todos os contratos inseridos.
- **Ordenar Contratos**: Escolha a opção `3` para ordenar os contratos por valor total (decrescente).
- **Imprimir Registros de Contratos**: Escolha a opção `4` e digite o número do contrato que deseja visualizar.

## Funções

- **`MenuInicial()`**: Exibe o menu principal e processa a escolha do usuário.
- **`InserirContratos()`**: Coleta informações sobre um novo contrato e calcula juros e descontos aplicáveis.
- **`calculoDoJuros(int posicaoContrato)`**: Calcula os juros e descontos para um contrato específico.
- **`apresentarResultados()`**: Exibe todos os contratos inseridos com seus detalhes.
- **`ordenarContratosDecrescente()`**: Ordena os contratos por valor total (decrescente) e exibe a lista ordenada.
- **`ImprimirRegistrosContratos()`**: Imprime os detalhes de um contrato específico com base no número do contrato.
- **`limparTela()`**: Limpa a tela do console, compatível com Windows e Linux.
- **`main()`**: Função principal que inicializa o programa e exibe o menu até que o usuário escolha sair.
- 
**Nota:** Este projeto é uma atividade para faculdade para fins de estudo
