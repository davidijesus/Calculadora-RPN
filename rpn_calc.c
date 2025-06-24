#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK 100
#define MAX_INPUT 256

// TAD Pilha
typedef struct {
    double items[MAX_STACK];
    int top;
} Pilha;

void inicializaPilha(Pilha *p) {
    p->top = -1;
}

int estaVazia(Pilha *p) {
    return (p->top == -1);
}

void push(Pilha *p, double valor) {
    if (p->top < MAX_STACK - 1) {
        p->items[++(p->top)] = valor;
    } else {
        printf("Erro: Pilha cheia!\n");
        exit(1);
    }
}

double pop(Pilha *p) {
    if (!estaVazia(p)) {
        return p->items[(p->top)--];
    } else {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
}

// Função para verificar se um token é número
int ehNumero(char *token) {
    if (isdigit(token[0]) || 
        (token[0] == '-' && isdigit(token[1]))) {
        return 1;
    }
    return 0;
}

int main() {
    Pilha pilha;
    char input[MAX_INPUT];

    printf("Digite a expressao em RPN:\n");
    fgets(input, sizeof(input), stdin);

    inicializaPilha(&pilha);

    char *token = strtok(input, " \n");

    while (token != NULL) {
        if (ehNumero(token)) {
            double num = atof(token);
            push(&pilha, num);
        } else if (strlen(token) == 1 && strchr("+-*/", token[0])) {
            if (pilha.top < 1) {
                printf("Erro: Expressao invalida!\n");
                exit(1);
            }
            double b = pop(&pilha);
            double a = pop(&pilha);
            double res;

            switch (token[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Erro: Divisao por zero!\n");
                        exit(1);
                    }
                    res = a / b; 
                    break;
                default:
                    printf("Erro: Operador desconhecido!\n");
                    exit(1);
            }
            push(&pilha, res);
        } else {
            printf("Erro: Token invalido '%s'\n", token);
            exit(1);
        }

        token = strtok(NULL, " \n");
    }

    if (pilha.top != 0) {
        printf("Erro: Expressao mal formada!\n");
        exit(1);
    }

    double resultado = pop(&pilha);
    printf("Resultado: %.2f\n", resultado);

    return 0;
}
