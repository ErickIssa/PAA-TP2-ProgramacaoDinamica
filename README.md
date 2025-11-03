Trabalho Prático 2 - Projeto e Análise de Algoritmos
Integrantes do Grupo
Erick Vinicius Issa Silva — Matrícula: 05936

Helom Felipe Marques Alves — Matrícula: 05892

Júlio César de Souza Oliveira — Matrícula: 05903

Heitor Porto Jardim de Oliveira — Matrícula: 05895

Abordagem de Programação Dinâmica
Problema
O problema consiste em encontrar o caminho ótimo através de dois mapas (presente e passado) onde a tripulação deve:

Sempre se mover da esquerda para a direita

Minimizar o desgaste de forças

Considerar a possibilidade de viagem temporal através de âncoras

Chegar ao destino com força suficiente para derrotar Nikador

Vantagens da Abordagem PD
Optimalidade: Garante encontrar o caminho com força máxima

Eficiência: Evita recompuração de subproblemas

Simplicidade: Estrutura tabular fácil de implementar e depurar

A programação dinâmica é particularmente adequada para este problema devido à natureza sequencial do movimento (sempre para direita) e à propriedade de subestrutura ótima, onde a solução ótima para uma coluna depende apenas das soluções ótimas da coluna anterior.
