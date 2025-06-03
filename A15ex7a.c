#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função para criar um retângulo
void retangulo(FILE *stream, int x, int y, int width, int height, const char *fill) {
    fprintf(stream, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"%s\" />\n", 
            x, y, width, height, fill);
}

// Função para criar um círculo
void circulo(FILE *stream, int cx, int cy, int r, const char *fill) {
    fprintf(stream, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"%s\" />\n", 
            cx, cy, r, fill);
}

// Função para criar uma linha
void linha(FILE *stream, int x1, int y1, int x2, int y2, const char *stroke, int stroke_width) {
    fprintf(stream, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"%s\" stroke-width=\"%d\" />\n", 
            x1, y1, x2, y2, stroke, stroke_width);
}

// Função para criar texto
void texto(FILE *stream, int x, int y, const char *font_family, int font_size, const char *fill, const char *text_content) {
    fprintf(stream, "<text x=\"%d\" y=\"%d\" font-family=\"%s\" font-size=\"%d\" fill=\"%s\">%s</text>\n", 
            x, y, font_family, font_size, fill, text_content);
}

int main() {
    char filename[100];
    char command;
    FILE *svg_file;
    
    printf("Digite o nome do arquivo SVG (ex: desenho.svg): ");
    scanf("%99s", filename);
    
    
    svg_file = fopen(filename, "w");
    if (svg_file == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }
    
    fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(svg_file, "<svg width=\"500\" height=\"500\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    
    printf("\nComandos disponíveis:\n");
    printf("R - Adicionar Retângulo\n");
    printf("C - Adicionar Círculo\n");
    printf("L - Adicionar Linha\n");
    printf("T - Adicionar Texto\n");
    printf("F - Finalizar e salvar o arquivo\n");
    
    while (1) {
        printf("\nDigite um comando (R/C/L/T/F): ");
        scanf(" %c", &command);
        command = toupper(command);
        
        if (command == 'F') {
            break;
        }
        
        switch (command) {
            case 'R': {
                int x, y, width, height;
                char fill[20];
                
                printf("Digite x, y, largura, altura e cor (ex: 20 30 100 100 red): ");
                scanf("%d %d %d %d %19s", &x, &y, &width, &height, fill);
                retangulo(svg_file, x, y, width, height, fill);
                printf("Retângulo adicionado!\n");
                break;
            }
            
            case 'C': {
                int cx, cy, r;
                char fill[20];
                
                printf("Digite centro x, centro y, raio e cor (ex: 50 50 30 blue): ");
                scanf("%d %d %d %19s", &cx, &cy, &r, fill);
                circulo(svg_file, cx, cy, r, fill);
                printf("Círculo adicionado!\n");
                break;
            }
            
            case 'L': {
                int x1, y1, x2, y2, stroke_width;
                char stroke[20];
                
                printf("Digite x1, y1, x2, y2, cor e largura (ex: 10 10 100 100 black 2): ");
                scanf("%d %d %d %d %19s %d", &x1, &y1, &x2, &y2, stroke, &stroke_width);
                linha(svg_file, x1, y1, x2, y2, stroke, stroke_width);
                printf("Linha adicionada!\n");
                break;
            }
            
            case 'T': {
                int x, y, font_size;
                char font_family[20], fill[20], text_content[100];
                
                printf("Digite x, y, fonte, tamanho, cor e texto (ex: 50 50 Arial 16 black \"Hello\"): ");
                scanf("%d %d %19s %d %19s", &x, &y, font_family, &font_size, fill);
                
                scanf(" %99[^\n]", text_content);
                
                if (text_content[0] == '"') {
                    memmove(text_content, text_content+1, strlen(text_content));
                    text_content[strlen(text_content)-1] = '\0';
                }
                texto(svg_file, x, y, font_family, font_size, fill, text_content);
                printf("Texto adicionado!\n");
                break;
            }
            
            default:
                printf("Comando inválido! Tente novamente.\n");
        }
    }
    
    
    fprintf(svg_file, "</svg>\n");
    fclose(svg_file);
    
    printf("\nArquivo SVG salvo com sucesso em %s\n", filename);
    
    return 0;
}