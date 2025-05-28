#include <stdio.h>
#include <string.h>

int main() {
    char nome_arquivo[100];
    int x, y, width, height;
    char cor[20] = "red"; // Cor padrão

    printf("Digite o nome do arquivo SVG (sem extensão): ");
    scanf("%99s", nome_arquivo);
    
    printf("Digite a posição x do quadrado: ");
    scanf("%d", &x);
    
    printf("Digite a posição y do quadrado: ");
    scanf("%d", &y);
    
    printf("Digite a largura do quadrado: ");
    scanf("%d", &width);
    
    printf("Digite a altura do quadrado: ");
    scanf("%d", &height);
    
    printf("Digite a cor do quadrado (opcional, padrão é red): ");
    scanf("%19s", cor); // Opcional - se quiser pular, pressione Enter

    // Adiciona a extensão .svg se não estiver presente
    char *ext = strstr(nome_arquivo, ".svg");
    if (ext == NULL || (ext - nome_arquivo) != strlen(nome_arquivo) - 4) {
        strcat(nome_arquivo, ".svg");
    }

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "<svg version=\"1.1\"\n");
    fprintf(arquivo, "width=\"%d\" height=\"%d\"\n", width + 2*x, height + 2*y);
    fprintf(arquivo, "xmlns=\"http://www.w3.org/2000/svg\">\n");
    fprintf(arquivo, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\" />\n", 
            x, y, width, height, cor);
    fprintf(arquivo, "</svg>\n");

    fclose(arquivo); // Fecha o arquivo corretamente
    printf("Arquivo %s criado com sucesso!\n", nome_arquivo);
    
    return 0;
}