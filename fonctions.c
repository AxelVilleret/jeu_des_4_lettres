#include "conio.h"

int x(int t[15][15])
{
    int position;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (t[i][j] == 1)
            {
                position = i;
            }
        }
    }
    return position;
}
// Permet d'obtenir la ligne sur laquelle est le joueur dans le labyrinthe (entre 0 et 14).

int y(int t[15][15])
{
    int position;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (t[i][j] == 1)
            {
                position = j;
            }
        }
    }
    return position;
}
// Permet d'obtenir la colonne sur laquelle est le joueur dans le labyrinthe (entre 0 et 14).

void aff_carte(int t[15][15])
{
    int i, j;
    gotoxy(38, 4);
    printf("%c", 201);
    for (i = 0; i < 15; i++)
    {
        printf("%c", 205);
        printf("%c", 205);
    }
    printf("%c", 187);
    for (i = 0; i < 15; i++)
    {
        gotoxy(38, i + 5);
        printf("%c", 186);
        for (j = 0; j < 15; j++)
        {
            printf("%c", t[i][j]);
            printf("%c", t[i][j]);
        }
        printf("%c", 186);
    }

    gotoxy(38, 20);
    printf("%c", 200);
    for (int i = 0; i < 15; i++)
    {
        printf("%c", 205);
        printf("%c", 205);
    }
    printf("%c", 188);
}
// Permet d'afficher un labyrinthe 15*15. On veut que ce labyrinthe s'affiche à côté de la vue du joueur sur le labyrinthe, donc on utilise gotoxy initialisé avec 38 en abscisse pour chaque ligne.
// Les caractères affichés correspondent à des valeurs précises du code ascii (voir main() pour les correspondances).
// On affiche à chaque fois le caractère en double pour obtenir un rendu "carré".

void aff_vue_joueur(int t[15][15])
{
    int i = x(t);
    int j = y(t);
    int k, l;
    printf("%c", 201);
    for (k = 0; k < 30; k++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    for (k = 0; k < 5; k++)
    {
        printf("%c", 186);
        for (l = 0; l < 10; l++)
        {
            printf("%c", t[i - 1][j - 1]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", t[i - 1][j]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", t[i - 1][j + 1]);
        }
        printf("%c", 186);
        printf("\n");
    }
    for (k = 0; k < 5; k++)
    {
        printf("%c", 186);
        for (l = 0; l < 10; l++)
        {
            printf("%c", t[i][j - 1]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", t[i][j]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", t[i][j + 1]);
        }
        printf("%c", 186);
        printf("\n");
    }
    for (k = 0; k < 5; k++)
    {
        printf("%c", 186);
        for (l = 0; l < 10; l++)
        {
            printf("%c", t[i + 1][j - 1]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", t[i + 1][j]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", t[i + 1][j + 1]);
        }
        printf("%c", 186);
        printf("\n");
    }
    printf("%c", 200);
    for (k = 0; k < 30; k++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    printf("\n");
}
// On commence par récupérer la ligne et la colonne du joueur dans le labyrinthe avec les fonctions initialisées précédemment.
// La vue du joueur constitue une matrice 3*3. Pour la rendre "carrée", l'affichage de chaque caractère est doublé. Ensuite, pour avoir 2 écrans de même taille pour la vue du joueur et l'affichage du labyrinthe, je multiplie par 5 l'affichage de chaque case en colonne et en ligne d'ou des boucles de 5 et 10.
// Je fais trois double boucle correpondant respectivement aux 3 lignes de cette matrice.

int action_valide(int t[15][15], char action)
{
    int i = x(t);
    int j = y(t);
    if (action == 'z')
    {
        if (t[i - 1][j] != 219)
        {
            return 1;
        }
    }
    if (action == 's')
    {
        if (t[i + 1][j] != 219)
        {
            return 1;
        }
    }
    if (action == 'q')
    {
        if (t[i][j - 1] != 219)
        {
            return 1;
        }
    }
    if (action == 'd')
    {
        if (t[i][j + 1] != 219)
        {
            return 1;
        }
    }
    return 0;
}
// Une fonction qui permet de voir si la touche sur laquelle le joueur a appuyée lui permet de se déplacer dans le labyrinthe.

void maj_carte_decouverte(int t1[15][15], int t2[15][15])
{
    int i = x(t1);
    int j = y(t1);
    t2[i][j] = 176;
}
// Permet de mettre à jour un labyrinthe de murs en affichant un chemin au même emplacement que le joueur que dans le labyrinthe.

void maj_arrivee(int t1[15][15], int t2[15][15])
{
    int i, j;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            if (t1[i][j] == 178)
            {
                t2[i][j] = 178;
            }
        }
    }
}
// Permet de mettre à jour un labyrinthe de murs en affichant la sortie au même emplacement que dans le labyrinthe.

int compareChaines(const char *chaine1, const char *chaine2)
{
    int i = 0;
    int continuer;
    char caractereActuel1 = 0, caractereActuel2 = 0;
    do
    {
        caractereActuel1 = chaine1[i];
        caractereActuel2 = chaine2[i];
        if (caractereActuel1 == caractereActuel2)
        {
            i++;
            continuer = 1;
        }
        else
            continuer = 0;
    } while (continuer == 1 && caractereActuel1 != '\0');
    if (continuer)
        return 1;
    else
        return 0;
}
// Permet de comparer 2 chaines de caractères pour savoir si elles sont rigoureusement identiques.

void aff_position_approximative(int t[15][15])
{
    int cpt = 0, k, l;
    int i = x(t);
    int j = y(t);
    int tab[3][3] = {{219, 219, 219}, {219, 219, 219}, {219, 219, 219}};
    if (i <= 4)
    {
        if (j <= 4)
        {
            tab[0][0] = 176;
        }
        else if (j > 4 && j <= 10)
        {
            tab[0][1] = 176;
        }
        else
        {
            tab[0][2] = 176;
        }
    }
    else if (i > 4 && i <= 10)
    {
        if (j <= 4)
        {
            tab[1][0] = 176;
        }
        else if (j > 4 && j <= 10)
        {
            tab[1][1] = 176;
        }
        else
        {
            tab[1][2] = 176;
        }
    }
    else
    {
        if (j <= 4)
        {
            tab[2][0] = 176;
        }
        else if (j > 4 && j <= 10)
        {
            tab[2][1] = 176;
        }
        else
        {
            tab[2][2] = 176;
        }
    }

    gotoxy(38, 4);
    printf("%c", 201);
    for (int k = 0; k < 15; k++)
    {
        printf("%c", 205);
        printf("%c", 205);
    }
    printf("%c", 187);
    for (k = 0; k < 5; k++)
    {
        gotoxy(38, 5 + cpt);
        printf("%c", 186);
        for (l = 0; l < 10; l++)
        {
            printf("%c", tab[0][0]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", tab[0][1]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", tab[0][2]);
        }
        printf("%c", 186);
        cpt += 1;
    }
    for (k = 0; k < 5; k++)
    {
        gotoxy(38, 5 + cpt);
        printf("%c", 186);
        for (l = 0; l < 10; l++)
        {
            printf("%c", tab[1][0]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", tab[1][1]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", tab[1][2]);
        }
        printf("%c", 186);
        cpt += 1;
    }
    for (k = 0; k < 5; k++)
    {
        gotoxy(38, 5 + cpt);
        printf("%c", 186);
        for (l = 0; l < 10; l++)
        {
            printf("%c", tab[2][0]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", tab[2][1]);
        }
        for (l = 0; l < 10; l++)
        {
            printf("%c", tab[2][2]);
        }
        printf("%c", 186);
        cpt += 1;
    }
    gotoxy(38, 20);
    printf("%c", 200);
    for (k = 0; k < 30; k++)
    {
        printf("%c", 205);
    }
    printf("%c", 188);
}
// On initialise une matrice 3*3 composée de murs et correspondant aux 9 zones du labyrinthe. Chaque zone correspond à une zone 5*5 dans le labyrinthe pour qu'elles aient toutes la même taille.
// On remplace pour la zone dans laquelle se situe le joueur le mur par un chemin.
// De la même manière que pour la vue du joueur, on aggrandit l'affichage par un zoom *5 pour obtenir 2 écrans de même taille.
// Cette fonction n'est pas utilisée dans mon programme, je l'ai remplacée par la carte du chemin découvert, plus pratique pour le joueur.