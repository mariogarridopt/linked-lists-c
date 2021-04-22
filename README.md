# Linked lists

This project ("ALGORITMIA - LIC. EM BIOENGENHARIA") was requested by [UTAD](https://www.utad.pt/en/).

## The Problem 

Face às circunstâncias sanitárias atuais, desenvolva um programa, em linguagem C, baseado em listas genéricas para
gerir um stock de vacinas COVID-19. Cada registo de entrada em stock deverá ser definido da seguinte forma: No de
receção (valor numérico único), nome da farmacêutica (PFizer, Moderna, AstraZeneca, J&J, Sanofi, ,...), No do Lote,
Quantidade recebida, Quantidade disponível, Data de validade e lista das saídas de stock para cada No de receção com
os seguintes dados: N.o requisição e Quantidade de saída de stock.

Nota: o valor disponível tem de ser igual a [Quantidade recebida] – a soma das [quantidades de saída de stock].

## The Requirements

O programa deverá ter, pelo menos, as seguintes funções/procedimentos permitindo:

- Registar uma nova entrada de stock, verificando sempre a unicidade do [N.o de receção];
- Alterar os dados de um registo de entrada de stock no caso de existir um erro no mesmo,
garantindo sempre a unicidade do [N.o de receção] e a veracidade da [Quantidade disponível];
- Registar uma saída de stock de uma determinada quantidade de uma entrada de stock especificada
pelo seu [N.o de receção];
- Eliminar um registo de saída de stock, garantindo a consistência da quantidade disponível do [N.o
de receção] correspondente;
- Apresentar a quantidade total de vacinas disponíveis em stock;
- Pesquisar e apresentar os dados referentes: 1) a um determinado [N.o de receção], 2) a um [N.o de
Lote] (pode existir lotes com entregas faseadas);
- Procurar e apresentar todas as vacinas disponíveis: 1) de uma determinada [Farmacêutica], 2) até
uma determinada [data de validade];
- Apresentar a listagem da quantidade de vacinas disponíveis nos próximos 6 meses, indicando a
quantidade disponível para cada mês, por exemplo: “Março: 755 Abril: 935 ...”;
- Exportar para um ficheiro todos os registos com vacinas disponíveis e respetivos dados.

O programa deverá apresentar um sistema de menu(s) que permita aceder a todas as opções mencionadas anteriormente.

## Repository

This repository is closed, and unsuported. Pls use this code just as a reference.

This has not been peer-reviewed, this is just my interpretation and solution to the problem, better more complete
soluctions might be advisable.