#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 100

typedef struct Ornek {
    int tip;
    int islenen;
    char islem;
    int oncelik;
} Ornek;

// Stack veri yapısı tanımı
typedef struct {
    Ornek items[STACK_SIZE];
    int top;
} Stack;

// Stack işlemleri
void initialize(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == STACK_SIZE - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, Ornek value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}

Ornek pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

Ornek peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}

// Operatör öncelik kontrolü
int oncelik(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Infix ifadeyi postfix ifadeye dönüştüren fonksiyon
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;
    initialize(&stack);

    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (infix[i] == '(') {
            Ornek parantez;
            parantez.tip = 1; // 1: parantez
            parantez.islenen = 0;
            parantez.islem = '(';
            parantez.oncelik = 0;
            push(&stack, parantez);
            i++;
        }
        else if (infix[i] == ')') {
            while (!isEmpty(&stack) && peek(&stack).islem != '(') {
                postfix[j++] = pop(&stack).islem;
            }
            pop(&stack); // '(' parantezini atla
            i++;
        }
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
            Ornek op;
            op.tip = 0; // 0: operatör
            op.islenen = 0;
            op.islem = infix[i];
            op.oncelik = oncelik(infix[i]);
            while (!isEmpty(&stack) && peek(&stack).tip == 0 && peek(&stack).oncelik >= op.oncelik) {
                postfix[j++] = pop(&stack).islem;
            }
            push(&stack, op);
            i++;
        }
        else if (infix[i] >= '0' && infix[i] <= '9') {
            while (infix[i] >= '0' && infix[i] <= '9') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
        }
        else {
            printf("Geçersiz karakter: %c\n", infix[i]);
            exit(EXIT_FAILURE);
        }
    }

    while (!isEmpty(&stack)) {
        if (peek(&stack).islem == '(') {
            printf("Hata: Parantez eşleşmesi yok!\n");
            exit(EXIT_FAILURE);
        }
        postfix[j++] = pop(&stack).islem;
    }

    postfix[j] = '\0'; // Postfix ifadeyi null karakterle sonlandır
}
int main() {
    char infix[100];
    printf("Infix ifadeyi girin: ");
    scanf("%s", infix);

    char postfix[100];
    infixToPostfix(infix, postfix);

    printf("Postfix ifade: %s\n", postfix);

    return 0;
}
