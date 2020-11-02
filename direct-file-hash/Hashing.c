#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, N;
    unsigned char *auxiliar = (unsigned char*)malloc(sizeof(unsigned char));
    unsigned char *valido = (unsigned char*)malloc(sizeof(unsigned char));
    unsigned char *auxiliar_leitura = (unsigned char*)malloc(sizeof(unsigned char));
    *auxiliar = '\0';
    *valido = 0x01;


    //gerando arquivo binario "pessoas.dat" com tamanho de 1Mb
    FILE *fp = fopen("pessoas.dat", "wb");
    fseek(fp, (1024*1000)-1, SEEK_SET);
    fwrite(auxiliar, sizeof(unsigned char), 1, fp);
    fclose(fp);

    //abrindo o arquivo no modo "r+b" e inicializando todas as flags para 0x00
    FILE * arquivo = fopen("pessoas.dat", "r+b");
    for(i=1; i<=1000; i++)
    {
        *auxiliar = 0x00;
        fwrite(auxiliar, sizeof(unsigned char), 1, arquivo);
        fseek(arquivo, 1024*i, SEEK_SET);
    }

    //inserindo registros
    char *nome = (char*)malloc(1000 * sizeof(char));
    fseek(arquivo, 1, SEEK_SET);
    scanf("%d", &N);

    for(i=0; i<N; i++)
    {
        //le entradas
        scanf("%d", auxiliar);
        scanf("%s", nome);

        //funcao hash:
        //(soma dos caracteres do nome + idade) % 1021
        int soma = *auxiliar;
        for(j=0; nome[j]!='\0'; j++)
            soma = soma + nome[j];
        int valor_hash = soma % 1021;

        fseek(arquivo, 1024*valor_hash, SEEK_SET);
        fread(auxiliar_leitura, sizeof(unsigned char), 1, arquivo);

        //se o registro for valido, resolve colisao por sondagem linear e depois insere registro
        //k define quantos registros foram "pulados" até chegar num registro vazio
        int k = 0;
        int pos = ftell(arquivo);

        while(*auxiliar_leitura != 0)
        {
            //resolvendo sondagem linear para quando o ultimo registro do arquivo ja existir
            if(pos >= 0xF9C00)
            {
                fseek(arquivo, 0, SEEK_SET);
                fread(auxiliar_leitura, sizeof(unsigned char), 1, arquivo);
                continue;
            }

            k++;
            fseek(arquivo, 1024*(valor_hash+k), SEEK_SET);
            fread(auxiliar_leitura, sizeof(unsigned char), 1, arquivo);
        }

        fseek(arquivo, 1024*(valor_hash+k), SEEK_SET);
        fwrite(valido, sizeof(unsigned char), 1, arquivo);
        fwrite(auxiliar, sizeof(unsigned char), 1, arquivo);
        fwrite(nome, sizeof(char), j, arquivo);
    }

    printf("Escolhi esta funcao hash porque: (1)a soma dos caracteres do nome está aproveitando uma iteração que era usada somente para calcular o tamanho do nome; (2)a funcao hash utiliza a soma dos caracteres do nome com a idade e calcula o resto da divisao - não faz necessidade de muitas operações; (3)o valor de M é primo, próximo a uma potencia de 2 e do valor de registros - isso ajuda a evitar colisões.");

    fclose(arquivo);
    free(auxiliar);
    free(valido);
    free(auxiliar_leitura);
    free(nome);

    return(0);
}
