#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

int x(int t[15][15]);

int y(int t[15][15]);

void aff_carte(int t[15][15]);

void aff_vue_joueur(int t[15][15]);

int action_valide(int t[15][15], char action);

void maj_carte_decouverte(int t1[15][15], int t2[15][15]);

void maj_arrivee(int t1[15][15], int t2[15][15]);

int compareChaines(const char *chaine1, const char *chaine2);

void aff_position_approximative(int t[15][15]);

#endif