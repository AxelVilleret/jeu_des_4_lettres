#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fonctions.h"
#include "conio.h"

int main()
{
    int lettres=0;  //Le nombre de lettres du joueur est initialisé à 0.
    textcolor(0);
    textbackground(7);
    system("cls");

    printf("[%c%c Jeu Des 4 Lettres %c%c]\n\nLe but du jeu est tres simple : il vous faudra obtenir une a une 4 lettres qui constituent un mot mystere.\n\nPour cela, vous devrez prouver votre valeur a 4 reprises lors d'epreuves !\n\nJe vais a present vous devoiler de precieux indices pour la reussite de ces epreuves.\n\nSouvenez-vous en bien, car je n'ai pas pour habitude de repeter !\n\n", 3, 4, 5, 6);
    system("Pause");
    system("cls");
    printf("[1ere lettre] Avez-vous l'ame d'un leader ?\n\nPour obtenir cette lettre, vous devrez savoir diriger par vos propres moyens...\n\n");
    system("Pause");
    system("cls");
    printf("[2eme lettre] Etes-vous audacieux ?\n\nPour obtenir cette lettre, vous devrez d'abord inscrire votre nom dans le LivreDesLegendes, puis reecrire l'histoire de la legende en remplacant ['''l_eleve_a_surpasse_le_maitre!'''] par [''''l_eleve_a_surpasse_le_maitre!''''].\n\nOn me dit souvent que cette epreuve est trop dur donc faites particulierement attention a cet indice !\n\n");
    system("Pause");
    system("cls");
    printf("[3eme lettre] Etes-vous deja revenu a vos origines ?\n\nPour obtenir cette lettre, vous devrez faire appel a vos souvenirs...\n\n");
    system("Pause");
    system("cls");
    printf("[4eme lettre] Etes-vous un bon detective ?\n\nPour obtenir cette lettre, vous devrez exploiter les indices a votre disposition...\n\n");
    system("Pause");
    system("cls");

    int premiere_fois = 1;  //Variable initialisée pour qu'un bloc ne s'exécute qu'une fois (la 1ère) dans une boucle tant que.
    char NomDuBest[255];    //On initialise une chaine de caractères qui va contenir le pseudo de celui qui aura réalisé le meilleur score sur le labyrinthe (le moins de tentatives utilisées).
    char nom_cle[255]="''l_eleve_a_surpasse_le_maitre!''";  //On définit le pseudo que le joueur doit adopter pour obtenir la 2ème lettre.
    while(compareChaines(NomDuBest, nom_cle)!=1){   //Tant que le meilleur joueur n'a pas le pseudo attendu...
        int m=219, c=176, a=178, p=1;   //On associe les codes ascii qui vont nous interesser à des variables pour créer plus confortablement le labyrinthe (m=mur, c=chemin, a=arrivée, p=player)
        char aide;  //Le joueur l'initialise à o ou n, permet de savoir s'il veut bénéficier de l'aide de la carte du chemin découvert.
        char action;    //Le joueur la remplit avec z, q, s, d en fonction de la direction dans laquelle il souhaite se déplacer.
        int tentatives=50;  //On initialise à 50 le nombre de tentatives du joueur.
        if(lettres==1){
            tentatives=30;  //Quand la première lettre est obtenue, on passe à 30 tentatives (plus le droit à l'erreur).
        }
        int car;    //Utilisé plus bas dans l'optique d'obtenir le nombre de lignes d'un fichier.
        char NomActuel[255];    //On va prendre un par un les noms contenus dans le fichier et les stocker dans cette variable.
        int ScoreDuBest, ScoreActuel;   //On stocke les scores dans score actuel et on les compare au score du meilleur. S'ils sont meilleurs on actualise la valeur du score du meilleur par cette valeur.
        int nLignes = 0;    //Nombre de lignes du fichier.
        char NewGagnant[255];   //Va contenir le nom du joueur qui aura réussi le labyrinthe sans aide.
        FILE* fichier;

        int lab[15][15]= {
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, c, c, m, m, c, c, c, m, m, c, c, m, c, m},
        {m, c, m, c, c, c, m, m, c, c, c, m, m, c, m},
        {m, c, m, c, m, c, c, c, c, m, c, c, c, c, m},
        {m, c, m, c, m, c, m, m, c, m, m, c, m, m, m},
        {m, c, m, m, c, c, c, m, m, m, m, m, c, a, m},
        {m, c, c, c, c, m, c, c, c, c, m, m, c, m, m},
        {m, m, m, m, c, m, m, c, m, c, m, m, c, m, m},  //Création du Labyrinthe.
        {m, c, c, c, c, m, m, c, m, c, m, m, c, m, m},
        {m, m, m, c, m, m, c, c, m, c, m, m, c, m, m},
        {m, c, c, c, c, m, m, c, m, c, c, c, c, m, m},
        {m, c, m, c, m, m, c, c, m, m, m, c, m, c, m},
        {m, c, m, c, m, m, c, m, m, c, c, c, c, c, m},
        {m, p, m, c, c, c, m, m, c, c, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m}};

        int murs[15][15]= {
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},  //Initialisation d'une matrice de murs qui va être mise à jour au fur et à mesure pour afficher la carte du chemin découvert.
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m}};



        if (premiere_fois==1){
            fichier = fopen("LivreDesLegendes.txt", "w");
            fprintf(fichier, "'l_eleve_a_surpasse_le_maitre!' 30\n");   //On initialise le fichier qui va contenir les noms de ceux qui réussissent le labyrinthe sans aide.
            fclose(fichier);
            premiere_fois=0;    //On ne le fait évidemment qu'une fois.
        }

        fichier = fopen("LivreDesLegendes.txt", "r");
        while((car=fgetc(fichier)) != EOF)  //Tant que le caractère lu n'est pas celui qui signe la fin d'un fichier...
        {
            if(car=='\n')
                nLignes++;  //On récupère le nombre de lignes du fichier.
        }
        fseek(fichier, 0, SEEK_SET);    //On remet le curseur au début du fichier pour pouvoir le reparcourir
        fscanf(fichier, "%s %i", &NomDuBest, &ScoreDuBest);
        for (int k=0; k<nLignes-1; k++){
            fscanf(fichier, "%s %i", &NomActuel, &ScoreActuel);
            if (ScoreActuel<=ScoreDuBest){
                ScoreDuBest=ScoreActuel;
                for (int j=0; j<255; j++){
                    NomDuBest[j]=NomActuel[j];  //On récupère le meilleur joueur ainsi que son score pour pouvoir les afficher.
                }
            }
        }
        fclose(fichier);
        printf("[%c BIENVENUE DANS LABYLAND %c]\n\n", 1, 1);
        printf("L'objectif est d'aider vos troupes a sortir d'un labyrinthe.\n\nAttention, elles ne peuvent se deplacer que %d fois avant de s'ecrouler, alors n'allez pas trop vite !\n\nVous verrez les 9 cases qui entourent la votre dans un labyrinthe 15x15.\n\n", tentatives);
        printf("L'histoire de la legende raconte qu'un certain ''%s'' dote d'un sens de l'orientation exceptionnel a su diriger ses troupes vers la sortie en seulement %i deplacements !\n\n", NomDuBest, ScoreDuBest);
        printf("%c COMMANDES %c\n%c Z\n%c S\n%c Q\n%c D\n\n", 17, 16, 24, 25, 27, 26);
        system("Pause");
        system("cls");

        printf("Souhaitez-vous etre aide ? ('o' pour oui et 'n' pour non)\n\nA noter que si vous souhaitez inscrire votre nom dans le livreDesLegendes, vous devrez reussir sans aide !\n\n");
        printf("Faites donc votre choix :\n\n");
        aide=getch();
        while(aide!='o' && aide!='n'){
            aide=getch();   //Le joueur choisit s'il veut être aidé ou non.
        }
        system("Pause");
        system("cls");
        printf("C'est note ! Amusez vous bien !!! C'est parti !!!\n\n");
        system("Pause");
        system("cls");

        while (tentatives!=0 && lab[5][13]==178) {  //Tant que que le joueur a encore des tentatives et qu'il n'est pas sur la case de sortie...
            printf("Plus que %d deplacements avant que vos troupes ne s'ecroulent.\n", tentatives);
            printf("Elles attendent vos ordres !\n\n");
            aff_vue_joueur(lab);    //Affichage de la vue du joueur.
            if (aide=='o'){
                maj_carte_decouverte(lab, murs);
                maj_arrivee(lab, murs);
                aff_carte(murs);
                gotoxy(38, 21);
                printf("Le chemin s'illumine et votre objectif approche ! ne decouragez pas !");
                gotoxy(1, 21);  //Si l'aide est active, on met à jours la matrice de murs et on l'affichage en tant que carte du chemin découvert.
            }

            action=getch(); //Le joueur indique la direction dans laquelle il souhaite se déplacer.
            printf("\n");
            int xp=x(lab);
            int yp=y(lab);  //On récupère ses coordonnées.
            int ActionValide=action_valide(lab, action);
            if (ActionValide==1){
                if (action=='z'){
                    lab[xp-1][yp]=1;
                    lab[xp][yp]=176;
                }
                if (action=='s'){
                    lab[xp+1][yp]=1;
                    lab[xp][yp]=176;
                }
                if (action=='q'){
                    lab[xp][yp-1]=1;
                    lab[xp][yp]=176;
                }
                if (action=='d'){
                    lab[xp][yp+1]=1;
                    lab[xp][yp]=176;    //Après avoir vérifié que la saisie est cohérente avec les déplacements possibles, on actualise sa position dans le labyrinthe.
                }
                tentatives-=1;  //On diminue de 1 ses tentatives.
            }
            system("cls");
        }

        if (lab[5][13]==p){ //Si le joueur est sur la case de la ligne d'arrivée...
            int score;
            if(lettres==0){
                score = 50 - tentatives;
            }
            else{
                score = 30 - tentatives;    //Le score va évidemment dépendre du nombre de tentatives que le joueur avait au départ.
            }

            if(lettres==0 && aide=='n'){    //Le joueur obtient sa première lettre s'il réussit sans aide le labyrinthe.
                lettres=1;
                printf("Avec cette 1ere victoire, vous etes a present bien lance !\n\nJe vous attribue donc cette 1ere lettre en guise de recompense :\n\n");
                system("Pause");
                system("cls");
                printf("[A___]\n\n");
                system("Pause");
                system("cls");
                printf("Courage cher joueur, la route est encore longue !\n\nBien, vous avez combien de lettres ? 1 ? Je vais donc apporter 1 modification au jeu.\n\n");
                system("Pause");
                system("cls");
                printf("Je me suis permis de reduire le nombre de deplacements total de vos troupes.\n\n");
                system("Pause");
                system("cls");
                printf("Il ne me reste qu'a vous souhaiter BONNE CHANCE pour la suite !!!\n\n");
                system("Pause");
                system("cls");
            }

            printf("Felicitation, vos troupes vous en seront a jamais reconnaissantes !!!\n\nIl leur aura fallu %d deplacements !\n\n", score);
            system("Pause");
            system("cls");
            if (aide=='n'){
                printf("Aujourd'hui nous allons ecrire une nouvelle page du LivreDesLegendes !\n\n");
                printf("Au fait, comment dois-je vous appeler ?\n\n");
                fgets(NewGagnant, 255, stdin);  //S'il réussit sans aide, le joueur saisit son nom.
                for (int i=0; i<3; i++){
                    printf(".");
                    sleep(1);
                    printf(".");
                    sleep(1);
                    printf(".\n");
                    sleep(1);

                }
                for (int i=0; i<255; i++){
                    if (NewGagnant[i]==' '){
                        NewGagnant[i]='_';
                    }
                    if (NewGagnant[i]=='\n'){
                        NewGagnant[i]='\0'; //On remplace les caractères qui nous embêtent lors de la lecture du fichier.
                    }
                }
                system("Pause");
                system("cls");
                printf("Pardonnez ma lenteur nouvelle legende c'est que les pages vierges se font rares !\n\nC'est que je commence a me faire vieux !\n\nHum pourquoi j'ai l'impression d'avoir deja prononce cette phrase, ma memoire me jouerait-elle des tours ?\n\n");
                system("Pause");
                system("cls");
                printf("C'est note %s ! Au plaisir de vous revoir !\n\n", NewGagnant);
                system("Pause");
                system("cls");
                fichier = fopen("LivreDesLegendes.txt", "a");
                fprintf(fichier, "%s %i\n", NewGagnant, score); //On écrit son nom et son score dans le fichier.
                fclose(fichier);
            }
        }
        else {
            printf("Vos troupes se sont ecroulees sous la fatigue !\n\nVous n'avez pas su les guider correctement !\n\nReprenez-vous, cela ne peut pas se finir aussi rapidement !\n\n");
            system("Pause");
            system("cls");
        }
        fichier = fopen("LivreDesLegendes.txt", "r");
        while((car=fgetc(fichier)) != EOF)
        {
            if(car=='\n')
                nLignes++;
        }
        fseek(fichier, 0, SEEK_SET);
        fscanf(fichier, "%s %i", &NomDuBest, &ScoreDuBest);
        for (int k=0; k<nLignes-1; k++){
            fscanf(fichier, "%s %i", &NomActuel, &ScoreActuel);
            if (ScoreActuel<=ScoreDuBest){
                ScoreDuBest=ScoreActuel;
                for (int j=0; j<255; j++){
                    NomDuBest[j]=NomActuel[j];  //On actualise le meilleur joueur et son score pour poouvoir faire la comparaison des chaines de caractères.
                }
            }
        }
    }



//Dans la suite, on répète ce schéma avec deux autres labyrinthes. Le premier est le même mais l'entrée et la sortie sont inversées et le deuxième est complètement nouveau.
//Les deux autres lettres s'obtiennent en les réussisant.



    while(lettres!=3){
        int m=219, c=176, a=178, p=1;
        char action;
        int tentatives=30;
        int car;
        char NomActuel[255];
        int ScoreDuBest, ScoreActuel;
        int nLignes = 0;
        char NewGagnant[255];
        FILE* fichier;
        int lab[15][15]= {
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, c, c, m, m, c, c, c, m, m, c, c, m, c, m},
        {m, c, m, c, c, c, m, m, c, c, c, m, m, c, m},
        {m, c, m, c, m, c, c, c, c, m, c, c, c, c, m},
        {m, c, m, c, m, c, m, m, c, m, m, c, m, m, m},
        {m, c, m, m, c, c, c, m, m, m, m, m, c, p, m},
        {m, c, c, c, c, m, c, c, c, c, m, m, c, m, m},
        {m, m, m, m, c, m, m, c, m, c, m, m, c, m, m},
        {m, c, c, c, c, m, m, c, m, c, m, m, c, m, m},
        {m, m, m, c, m, m, c, c, m, c, m, m, c, m, m},
        {m, c, c, c, c, m, m, c, m, c, c, c, c, m, m},
        {m, c, m, c, m, m, c, c, m, m, m, c, m, c, m},
        {m, c, m, c, m, m, c, m, m, c, c, c, c, c, m},
        {m, a, m, c, c, c, m, m, c, c, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m}};

        int murs[15][15]= {
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m}};

        if (lettres==1){
            fichier = fopen("LivreDesLegendes.txt", "r");
            while((car=fgetc(fichier)) != EOF)
            {
                if(car=='\n')
                    nLignes++;
            }
            fseek(fichier, 0, SEEK_SET);
            fscanf(fichier, "%s %i", &NomDuBest, &ScoreDuBest);
            for (int k=0; k<nLignes-1; k++){
                fscanf(fichier, "%s %i", &NomActuel, &ScoreActuel);
                if (ScoreActuel<=ScoreDuBest){
                    ScoreDuBest=ScoreActuel;
                    for (int j=0; j<255; j++){
                        NomDuBest[j]=NomActuel[j];
                    }
                }
            }
            fclose(fichier);
            for (int i=0; i<5; i++){
                printf("[%c BIENVENUE DANS LABYLAND %c]\n\n", 1, 1);
                printf("L'objectif est d'aider vos troupes a sortir d'un labyrinthe.\n\nAttention, elles ne peuvent se deplacer que %d fois avant de s'ecrouler, alors n'allez pas trop vite !\n\nVous verrez les 9 cases qui entourent la votre dans un labyrinthe 15x15.\n\n", tentatives);
                printf("L'histoire de la legende raconte qu'un certain '''%s''' dote d'un sens de l'orientation exceptionnel a su diriger ses troupes vers la sortie en seulement %i deplacements !\n\n", NomDuBest, ScoreDuBest);
                printf("%c COMMANDES %c\n%c Z\n%c S\n%c Q\n%c D\n\n", 17, 16, 24, 25, 27, 26);
                sleep(1);
                system("cls");
                gotoxy(48, 9);
                printf("'''%s'''\n\n", NomDuBest);
                sleep(1);
                system("cls");
            }
            printf("(Rires) Vous avez vraiment cru pouvoir me faire dire ce que vous vouliez ?\n\nEt bien sachez que c'est rate !\n\n");
            system("Pause");
            system("cls");
            printf("Neanmoins, pour vous feliciter de votre prouesse, je vais vous accorder une seconde lettre !\n\n");
            system("Pause");
            system("cls");
            printf("L'avez-vous deja devinee ?\n\n");
            system("Pause");
            system("cls");
            lettres=2;
            printf("[AX__]\n\n");
            system("Pause");
            system("cls");
            printf("Bien, vous avez combien de lettres ? 2 ? Je vais donc apporter 2 modifications au jeu.\n\n");
            system("Pause");
            system("cls");
            printf("1) L'entree et la sortie du labyrinthe ont ete deplacees pour occuper des emplacements differents.\n\n2) L'acces a l'aide va etre supprime.\n\n");
            system("Pause");
            system("cls");
            printf("Il ne me reste qu'a vous souhaiter BONNE CHANCE pour la suite !!!\n\n");
            system("Pause");
            system("cls");
        }

        while (tentatives!=0 && lab[13][1]==178) {
            printf("Plus que %d deplacements avant que vos troupes ne s'ecroulent.\n", tentatives);
            printf("Elles attendent vos ordres !\n\n");
            aff_vue_joueur(lab);

            action=getch();
            printf("\n");
            int xp=x(lab);
            int yp=y(lab);
            int ActionValide=action_valide(lab, action);
            if (ActionValide==1){
                if (action=='z'){
                    lab[xp-1][yp]=1;
                    lab[xp][yp]=176;
                }
                if (action=='s'){
                    lab[xp+1][yp]=1;
                    lab[xp][yp]=176;
                }
                if (action=='q'){
                    lab[xp][yp-1]=1;
                    lab[xp][yp]=176;
                }
                if (action=='d'){
                    lab[xp][yp+1]=1;
                    lab[xp][yp]=176;
                }
                tentatives-=1;
            }
            system("cls");
        }
        if (lab[13][1]==p){
            printf("C'est gagne !!! Je savais que vous en etiez capable !\n\n");
            system("Pause");
            system("cls");
            printf("Prenez cette 3eme lettre !\n\nEt n'oubliez pas que la prochaine sera la derniere !!!\n\n");
            system("Pause");
            system("cls");
            lettres=3;
            printf("[AXE_]\n\n");
            system("Pause");
            system("cls");
        }
        else {
            printf("Ressaisissez-vous !\n\nUne bonne partie du chemin a deja ete parcourue !\n\nVotre perseverence portera ses fruits, j'en suis certain !!!\n\n");
            system("Pause");
            system("cls");
        }
    }



    int lecture=0;
    while(lettres!=4){
        int m=219, c=176, a=178, p=1;
        char action;
        int tentatives=20;
        int lab[15][15]= {
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, c, c, m, a, m, c, c, c, c, c, c, c, m},
        {m, c, c, m, m, c, c, c, m, c, m, c, m, c, m},
        {m, c, m, c, c, c, m, m, c, c, c, c, c, c, m},
        {m, c, c, c, m, c, c, c, c, m, c, m, m, c, m},
        {m, c, m, c, m, c, m, c, m, c, c, c, c, c, m},
        {m, c, c, m, c, c, c, c, m, c, m, c, m, c, m},
        {m, m, c, c, m, c, m, c, m, c, m, c, c, c, m},
        {m, c, c, m, c, c, c, m, c, c, m, c, m, c, m},
        {m, m, c, c, m, c, m, m, m, c, m, c, c, c, m},
        {m, c, m, c, m, c, c, m, m, c, m, c, m, c, m},
        {m, c, m, c, c, c, m, c, c, c, m, c, c, c, m},
        {m, c, c, c, m, c, m, c, m, c, m, c, m, c, m},
        {m, m, m, c, c, c, c, c, c, c, c, c, c, p, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m}};

        int murs[15][15]= {
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m},
        {m, m, m, m, m, m, m, m, m, m, m, m, m, m, m}};

        if (lecture==0){
            printf("Vous avez a present 3 lettres en votre possession !\n\nJe n'ai plus les mots pour decrire votre talent !\n\n");
            system("Pause");
            system("cls");
            printf("Nous allons maintenant voir si vous meritez votre 4eme lettre !\n\nVous avez combien de lettres ? 3 ? Je vais donc apporter 3 modifications au jeu.\n\n");
            system("Pause");
            system("cls");
            printf("1) Le labyrinthe va etre revu de A a Z en devenant cauchemardesque.\n\n2) Le nombre de deplacements total de vos troupes va de nouveau etre revu a la baisse.\n\n3) Vous n'aurez plus acces au nombre de deplacements restants.\n\n");
            system("Pause");
            system("cls");
            printf("Bon aller je ne veux pas que vous me detestiez.\n\nJe vais donc vous redonner l'aide que vous aviez au depart qui affiche le chemin decouvert.\n\nVous me remercierez plus tard !\n\nEn esperant que vous en fassiez bon usage...\n\n");
            system("Pause");
            system("cls");
            printf("Il ne me reste qu'a vous souhaiter BONNE CHANCE pour la suite !!!\n\n");
            system("Pause");
            system("cls");
            lecture=1;
        }

        while (tentatives!=0 && lab[1][5]==178) {
            printf("Plus que X deplacements avant que vos troupes ne s'ecroulent.\n");
            printf("Elles attendent vos ordres !\n\n");
            aff_vue_joueur(lab);
            maj_carte_decouverte(lab, murs);
            maj_arrivee(lab, murs);
            aff_carte(murs);
            gotoxy(38, 21);
            printf("ALors que vous vous raprochez de La 4eme Lettre, votre chemin s'iLLumine de pLus beLLe...");
            gotoxy(1, 21);
            action=getch();
            printf("\n");
            int xp=x(lab);
            int yp=y(lab);
            int ActionValide=action_valide(lab, action);
            if (ActionValide==1){
                if (action=='z'){
                    lab[xp-1][yp]=1;
                    lab[xp][yp]=176;
                }
                if (action=='s'){
                    lab[xp+1][yp]=1;
                    lab[xp][yp]=176;
                }
                if (action=='q'){
                    lab[xp][yp-1]=1;
                    lab[xp][yp]=176;
                }
                if (action=='d'){
                    lab[xp][yp+1]=1;
                    lab[xp][yp]=176;
                }
                tentatives-=1;
            }
            system("cls");
        }
        if (lab[1][5]==p){
            maj_carte_decouverte(lab, murs);
            for (int i=0; i<5; i++){
                aff_carte(murs);
                sleep(1);
                system("cls");
                sleep(1);
                system("cls");
            }
            printf("QueLLe beLLe fin, je suis teLLement emu !\n\nJe ne sais pas si vous vous en rendez compte, mais votre genie est sans egal !!!\n\n");
            system("Pause");
            system("cls");
            lettres=4;
            printf("J'imagine que vous connaissez deja la 4eme Lettre...\n\n");
            system("Pause");
            system("cls");
            printf("[AXEL]\n\n");
            system("Pause");
            system("cls");
        }
        else {
            printf("Courage !\n\nVous voyez Le bout du tunneL !\n\nReLevez vous et Liberez vos troupes !\n\n");
            system("Pause");
            system("cls");
        }
    }

    printf("Le jeu est a present termine !\n\nFELICITATION au joueur !!!\n\nEn esperant qu'il vous ait plu  ;) !\n\nDites-moi, votre PC est-il toujours en vie ?\n\n");
    system("Pause");
    return 0;
}
