Considere uma tabela com campos de idade (inteiro) e nome (string). Escreva um
programa em C que gera em disco um arquivo direto (binário, chamado pessoas.dat) contendo
registros desta tabela.

- O arquivo gerado deve ter capacidade para até 1024 registros. Cada registro deve ocupar
exatamente 1024 bytes (1 Kb), sendo 1 byte para a flag (0x00 para registro inválido, 0x01
para registro válido), 1 byte para a idade, e 1022 bytes para o nome. Note que o arquivo
gerado deve ter exatamente 1024 × 1Kb = 1 Mb de tamanho.

- O programa deve criar um arquivo inicialmente sem registros, ler do usuário um inteiro N
seguido de uma sequência de N registros, e inserı́-los no arquivo na ordem dada na entrada.
Como exemplo, se a entrada for

3
10 Ash
12 Brock
11 Misty

o arquivo gerado deve conter (apenas) os registros {(10, Ash), (12, Brock), (11, M isty)}. Você
pode assumir que nenhum nome conterá espaços nem terá mais de 1000 caracteres, e também
que N ≤ 1024;

- Escolha como função hash a função que julgar ser a mais adequada. Justifique sua escolha
na saı́da padrão do programa (printf("Escolhi esta funcao hash porque ... ");). Sua
função deve “levar em conta” os dois campos do registro, e não apenas um;
- Resolva colisões com sondagem linear;
- Faça leituras e escritas no arquivo a cada registro informado pelo usuário. Não construa uma
matriz em memória principal para apenas escrevê-la inteira no disco ao final do programa!
