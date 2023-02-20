#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SIZE 1000

/**
 * @brief
 *
 * @param n              //Nombre de disques
 * @param depart        //emplacement de depart
 * @param arrive        //emplacement d'arrivée
 * @param intermediaire         // emplacement intermédiaire.
 */

// algorithme  recursif 1
void tourDeHanoi(int n, char depart, char arrive, char intermediaire)
{
    if (n > 0)
    {
        if (n == 1)
        {
            printf("\n Déplacer 1 de %c à  %c", depart, arrive);
            return;
        }
        tourDeHanoi(n - 1, depart, intermediaire, arrive);
        printf("\n Déplacer %d de %c à  %c", n, depart, arrive);
        tourDeHanoi(n - 1, intermediaire, arrive, depart);
    }
}

// algorithme  recursif généralisé
void tourDeHanoi_gen(int n, int depart, int intermediaire, int arrive)
{
    if (n != 0)
    {
        if (n == 1)
        {
            printf("Déplacer le disque de P%d vers P%d\n", depart, arrive);
        }
        else
        {
            tourDeHanoi_gen(n - 1, depart, arrive, intermediaire);
            printf("Déplacer le disque de P%d vers P%d\n", depart, arrive);
            tourDeHanoi_gen(n - 1, intermediaire, depart, arrive);
        }
    }
}

/****
 *
 *
 * algorithme itératif
 *
 * */

// Structure pour représenter une pile
struct Stack
{
    int taille;
    int top;
    int *tab;
};

struct Stack *createStack(int taille)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->taille = taille;
    stack->top = -1;
    stack->tab = (int *)malloc(sizeof(int) * taille);
    return stack;
}

int isFull(struct Stack *stack)
{
    return stack->top == stack->taille - 1;
}

int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

void push(struct Stack *stack, int item)
{
    if (isFull(stack))
    {
        return;
    }
    stack->tab[++stack->top] = item;
}

int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        return -1;
    }
    return stack->tab[stack->top--];
}

void moveDisk(char fromRod, char toRod, int disk)
{
    printf("Move disk %d from rod %c to rod %c\n", disk, fromRod, toRod);
}

void iterativeTowerOfHanoi(int numDisks)
{
    int i, totalMoves;
    char fromRod = 'A', toRod = 'C', auxRod = 'B';

    struct Stack *s1 = createStack(numDisks);
    struct Stack *s2 = createStack(numDisks);
    struct Stack *s3 = createStack(numDisks);

    totalMoves = pow(2, numDisks) - 1;

    for (i = numDisks; i >= 1; i--)
    {
        push(s1, i);
    }

    if (numDisks % 2 == 0)
    {
        struct Stack *temp = s2;
        s2 = s3;
        s3 = temp;
    }

    for (i = 1; i <= totalMoves; i++)
    {
        if (i % 3 == 1)
        {
            if (isEmpty(s1))
            {
                push(s1, pop(s2));
                moveDisk('B', 'A', s1->tab[s1->top]);
            }
            else if (isEmpty(s2))
            {
                push(s2, pop(s1));
                moveDisk('A', 'B', s2->tab[s2->top]);
            }
            else if (s1->tab[s1->top] < s2->tab[s2->top])
            {
                push(s2, pop(s1));
                moveDisk('A', 'B', s2->tab[s2->top]);
            }
            else
            {
                push(s1, pop(s2));
                moveDisk('B', 'A', s1->tab[s1->top]);
            }
        }
        else if (i % 3 == 2)
        {
            if (isEmpty(s1))
            {
                push(s1, pop(s3));
                moveDisk('C', 'A', s1->tab[s1->top]);
            }
            else if (isEmpty(s3))
            {
                push(s3, pop(s1));
                moveDisk('A', 'C', s3->tab[s3->top]);
            }
            else if (s1->tab[s1->top] < s3->tab[s3->top])
            {
                push(s3, pop(s1));
                moveDisk('A', 'C', s3->tab[s3->top]);
            }
            else
            {
                push(s1, pop(s3));
                moveDisk('C', 'A', s1->tab[s1->top]);
            }
        }
        else if (i % 3 == 0)
        {
            if (isEmpty(s2))
            {
                push(s2, pop(s3));
                moveDisk('C', 'B', s2->tab[s2->top]);
            }
            else if (isEmpty(s3))
            {
                push(s3, pop(s2));
                moveDisk('B', 'C', s3->tab[s3->top]);
            }
            else if (s2->tab[s2->top] < s3->tab[s3->top])
            {
                push(s3, pop(s2));
                moveDisk('B', 'C', s3->tab[s3->top]);
            }
            else
            {
                push(s2, pop(s3));
                moveDisk('C', 'B', s2->tab[s2->top]);
            }
        }
    }
}

int main()
{
    int n; // le nombre de disques
    printf("Nombre de disques: ");
    scanf("%d", &n);
    tourDeHanoi(n, 'A', 'C', 'B'); // A, B et C sont les noms des emplacements
    iterativeTowerOfHanoi(n);
    return 0;
}
