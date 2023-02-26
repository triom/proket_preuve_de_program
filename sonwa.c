#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

/****
 *
 *
 * algorithme itératif
 *
 * */

// Structure pour représenter une pile
struct Pile
{
    int taille; // taille de la pile
    int top;    // l'élément au dessus de la pile
    int *tab;
};

struct Pile *initPile(int taille)
{
    struct Pile *Pile = (struct Pile *)malloc(sizeof(struct Pile));
    Pile->taille = taille;
    Pile->top = -1;
    Pile->tab = (int *)malloc(sizeof(int) * taille);
    return Pile;
}

int estPleine(struct Pile *pile)
{
    return pile->top == pile->taille - 1;
}

int estVide(struct Pile *pile)
{
    return pile->top == -1;
}

void empiler(struct Pile *pile, int element)
{
    if (estPleine(pile))
    {
        return;
    }
    pile->tab[++pile->top] = element;
}

int depiler(struct Pile *pile)
{
    if (estVide(pile))
    {
        return -1;
    }
    return pile->tab[pile->top--];
}

void deplacer(char depart, char arrive, int disk)
{
    printf("Deplacer le disque %d de %c à %c\n", disk, depart, arrive);
}

void tourDeHanoiIterative(int nbDisque)
{
    int i, totalMoves;
    // char depart = 'A', arrive = 'C', inter = 'B';

    struct Pile *s1 = initPile(nbDisque);
    struct Pile *s2 = initPile(nbDisque);
    struct Pile *s3 = initPile(nbDisque);

    totalMoves = pow(2, nbDisque) - 1;

    for (i = nbDisque; i >= 1; i--)
    {
        empiler(s1, i);
    }

    if (nbDisque % 2 == 0)
    {
        struct Pile *temp = s2;
        s2 = s3;
        s3 = temp;
    }

    for (i = 1; i <= totalMoves; i++)
    {
        if (i % 3 == 1)
        {
            if (estVide(s1))
            {
                empiler(s1, depiler(s2));
                deplacer('B', 'A', s1->tab[s1->top]);
            }
            else if (estVide(s2))
            {
                empiler(s2, depiler(s1));
                deplacer('A', 'B', s2->tab[s2->top]);
            }
            else if (s1->tab[s1->top] < s2->tab[s2->top])
            {
                empiler(s2, depiler(s1));
                deplacer('A', 'B', s2->tab[s2->top]);
            }
            else
            {
                empiler(s1, depiler(s2));
                deplacer('B', 'A', s1->tab[s1->top]);
            }
        }
        else if (i % 3 == 2)
        {
            if (estVide(s1))
            {
                empiler(s1, depiler(s3));
                deplacer('C', 'A', s1->tab[s1->top]);
            }
            else if (estVide(s3))
            {
                empiler(s3, depiler(s1));
                deplacer('A', 'C', s3->tab[s3->top]);
            }
            else if (s1->tab[s1->top] < s3->tab[s3->top])
            {
                empiler(s3, depiler(s1));
                deplacer('A', 'C', s3->tab[s3->top]);
            }
            else
            {
                empiler(s1, depiler(s3));
                deplacer('C', 'A', s1->tab[s1->top]);
            }
        }
        else if (i % 3 == 0)
        {
            if (estVide(s2))
            {
                empiler(s2, depiler(s3));
                deplacer('C', 'B', s2->tab[s2->top]);
            }
            else if (estVide(s3))
            {
                empiler(s3, depiler(s2));
                deplacer('B', 'C', s3->tab[s3->top]);
            }
            else if (s2->tab[s2->top] < s3->tab[s3->top])
            {
                empiler(s3, depiler(s2));
                deplacer('B', 'C', s3->tab[s3->top]);
            }
            else
            {
                empiler(s2, depiler(s3));
                deplacer('C', 'B', s2->tab[s2->top]);
            }
        }
    }
}

int main()
{
    clock_t start, end;
    double temps;
    start = clock();
    int n, choix; // le nombre de disques
    printf("Nombre de disques: ");
    scanf("%d", &n);
    printf("1:Algorihme recursif\n2: Algorithme itératif\n");
    scanf("%d", &choix);
    if (choix == 1)
    {
        printf("Version Recursive\n");
        tourDeHanoi(n, 'A', 'C', 'B');
    }
    else
    {
        printf("Version Iterative\n");
        tourDeHanoiIterative(n);
    }
    end = clock();
    temps = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTemps d'éxécution en secondes : %f seconds\n", temps);
    return 0;
}
