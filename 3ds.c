#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int pow;
    struct Node *next;
};

// Create a new node
struct Node* createNode(int coeff, int pow) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;
    return newNode;
}

// Insert node at end
struct Node* insertNode(struct Node* head, int coeff, int pow) {
    struct Node* newNode = createNode(coeff, pow);
    if (head == NULL)
        return newNode;
    
    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    return head;
}

// Add two polynomials
struct Node* addPoly(struct Node* p1, struct Node* p2) {
    struct Node* result = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->pow > p2->pow) {
            result = insertNode(result, p1->coeff, p1->pow);
            p1 = p1->next;
        } 
        else if (p1->pow < p2->pow) {
            result = insertNode(result, p2->coeff, p2->pow);
            p2 = p2->next;
        } 
        else {
            result = insertNode(result, p1->coeff + p2->coeff, p1->pow);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        result = insertNode(result, p1->coeff, p1->pow);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        result = insertNode(result, p2->coeff, p2->pow);
        p2 = p2->next;
    }
    return result;
}

// Subtract two polynomials
struct Node* subPoly(struct Node* p1, struct Node* p2) {
    struct Node* result = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->pow > p2->pow) {
            result = insertNode(result, p1->coeff, p1->pow);
            p1 = p1->next;
        } 
        else if (p1->pow < p2->pow) {
            result = insertNode(result, -p2->coeff, p2->pow);
            p2 = p2->next;
        } 
        else {
            result = insertNode(result, p1->coeff - p2->coeff, p1->pow);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        result = insertNode(result, p1->coeff, p1->pow);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        result = insertNode(result, -p2->coeff, p2->pow);
        p2 = p2->next;
    }
    return result;
}

// Display polynomial
void display(struct Node* head) {
    while (head != NULL) {
        printf("%dx^%d", head->coeff, head->pow);
        head = head->next;
        if (head != NULL && head->coeff >= 0)
            printf(" + ");
    }
    printf("\n");
}

int main() {
    struct Node *poly1 = NULL, *poly2 = NULL, *sum = NULL, *diff = NULL;

    // Example input: P1 = 5x^2 + 4x + 2
    poly1 = insertNode(poly1, 5, 2);
    poly1 = insertNode(poly1, 4, 1);
    poly1 = insertNode(poly1, 2, 0);

    // Example input: P2 = 3x^2 + 2x + 1
    poly2 = insertNode(poly2, 3, 2);
    poly2 = insertNode(poly2, 2, 1);
    poly2 = insertNode(poly2, 1, 0);

    printf("Polynomial 1: ");
    display(poly1);

    printf("Polynomial 2: ");
    display(poly2);

    sum = addPoly(poly1, poly2);
    printf("\nSum: ");
    display(sum);

    diff = subPoly(poly1, poly2);
    printf("Difference: ");
    display(diff);

    return 0;
}

