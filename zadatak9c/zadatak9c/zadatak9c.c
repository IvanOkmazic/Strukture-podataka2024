#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definicija strukture �vora
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Funkcija za kreiranje novog �vora
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Greska: Nema dovoljno memorije!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Funkcija za umetanje novog elementa u binarno stablo
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    }
    else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Funkcija za inorder prolazak stabla i ispis na standardni izlaz
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

// Funkcija za inorder prolazak stabla i upisivanje u datoteku
void inorderToFile(Node* root, FILE* file) {
    if (root != NULL) {
        inorderToFile(root->left, file);
        fprintf(file, "%d ", root->value);
        inorderToFile(root->right, file);
    }
}

// Funkcija za upisivanje elemenata u datoteku
void writeToFile(Node* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke %s\n", filename);
        return;
    }
    inorderToFile(root, file);
    fclose(file);
}

// Funkcija za zamenu vrednosti svakog �vora sumom elemenata u njegovom levom i desnom podstablu
int replace(Node* root) {
    if (root == NULL) {
        return 0;
    }

    // Suma elemenata levog i desnog podstabla
    int leftSum = replace(root->left);
    int rightSum = replace(root->right);

    // Trenutna vrednost pre zamene
    int currentValue = root->value;

    // Menjamo vrednost trenutnog �vora
    root->value = leftSum + rightSum;

    // Vra�amo staru vrednost �vora + sumu svih potomaka
    return currentValue + root->value;
}

// Glavna funkcija
int main() {
    Node* root = NULL;
    srand(time(0));  // Inicijalizacija generatora slu�ajnih brojeva

    // Dodajemo slu�ajne brojeve u stablo
    for (int i = 0; i < 10; i++) {
        int num = rand() % 81 + 10;  // Generi�e brojeve u opsegu od 10 do 90
        root = insert(root, num);
    }

    // Ispisujemo originalno stablo
    printf("Inorder prolazak originalnog stabla:\n");
    inorder(root);
    printf("\n");

    // Upisujemo originalno stablo u datoteku
    writeToFile(root, "original_tree.txt");

    // Menjamo vrednosti �vorova prema zahtevu
    replace(root);

    // Ispisujemo modifikovano stablo
    printf("Inorder prolazak modificiranog stabla:\n");
    inorder(root);
    printf("\n");

    // Upisujemo modifikovano stablo u datoteku
    writeToFile(root, "modified_tree.txt");

    printf("Originalno i modificirano stablo su upisani u datoteke 'original_tree.txt' i 'modified_tree.txt'.\n");

    return 0;
}
