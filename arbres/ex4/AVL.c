#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int data;
    struct Noeud *fg;
    struct Noeud *fd;
    int hauteur;
} Noeud;

//Fonction utilitaires AVL

int max(int a, int b) {
    return (a > b) ? a : b;
}

int hauteur(Noeud* n) {
    if (n == NULL) return 0;
    return n->hauteur;
}

//Facteur d’équilibre
int facteurEquilibre(Noeud* n) {
    if (n == NULL) return 0;
    return hauteur(n->fg) - hauteur(n->fd);
}

//Création d’un nœud AVL
Noeud* creerNoeud(int val) {
    Noeud* nv = (Noeud*)malloc(sizeof(Noeud));
    nv->data = val;
    nv->fg = NULL;
    nv->fd = NULL;
    nv->hauteur = 1;
    return nv;
}

//Rotation droite 
Noeud* rotationDroite(Noeud* y) {
    Noeud* x = y->fg;
    Noeud* T2 = x->fd;

    x->fd = y;
    y->fg = T2;

    y->hauteur = 1 + max(hauteur(y->fg), hauteur(y->fd));
    x->hauteur = 1 + max(hauteur(x->fg), hauteur(x->fd));

    return x;
}

//Rotation gauche 
Noeud* rotationGauche(Noeud* x) {
    Noeud* y = x->fd;
    Noeud* T2 = y->fg;

    y->fg = x;
    x->fd = T2;

    x->hauteur = 1 + max(hauteur(x->fg), hauteur(x->fd));
    y->hauteur = 1 + max(hauteur(y->fg), hauteur(y->fd));

    return y;
}

//INSERTION AVL
Noeud* inserer(Noeud* noeud, int data) {

    // Insertion BST classique
    if (noeud == NULL)
        return creerNoeud(data);   // Correction ici

    if (data < noeud->data)
        noeud->fg = inserer(noeud->fg, data);
    else if (data > noeud->data)
        noeud->fd = inserer(noeud->fd, data);
    else
        return noeud; // Pas de doublons

    // Mise à jour hauteur
    noeud->hauteur = 1 + max(hauteur(noeud->fg), hauteur(noeud->fd));

    // Facteur d’équilibre
    int fe = facteurEquilibre(noeud);

    // Cas Gauche-Gauche (LL)
    if (fe > 1 && data < noeud->fg->data)
        return rotationDroite(noeud);

    // Cas Droite-Droite (RR)
    if (fe < -1 && data > noeud->fd->data)
        return rotationGauche(noeud);

    // Cas Gauche-Droite (LR)
    if (fe > 1 && data > noeud->fg->data) {
        noeud->fg = rotationGauche(noeud->fg);
        return rotationDroite(noeud);
    }

    // Cas Droite-Gauche (RL)
    if (fe < -1 && data < noeud->fd->data) {
        noeud->fd = rotationDroite(noeud->fd);
        return rotationGauche(noeud);
    }

    return noeud;
}

// Affichage ASCII de l'arbre
void afficherArbre(Noeud *racine, int espace) {
    if (racine == NULL) return;

    espace += 5;
    afficherArbre(racine->fd, espace);

    printf("\n");
    for (int i = 5; i < espace; i++) printf(" ");
    printf("%d\n", racine->data);

    afficherArbre(racine->fg, espace);
}

int main() {

    printf("\n===== SERIE 1 : 50, 40, 30, 20, 10, 5, 1 =====\n");
    int serie1[] = {50, 40, 30, 20, 10, 5, 1};
    int n = sizeof(serie1) / sizeof(serie1[0]);

    Noeud* racine = NULL;
    for (int i = 0; i < n; i++) {
        printf("\n Insertion de %d:\n", serie1[i]);
        racine = inserer(racine, serie1[i]);
        afficherArbre(racine, 0);
        printf("\n----------------------------------------------\n");
    }

    printf("\n\n===== SERIE 2 : 10, 20, 30, 40, 50, 60, 70 =====\n");
    int serie2[] = {10, 20, 30, 40, 50, 60, 70};
    int n2 = sizeof(serie2) / sizeof(serie2[0]);
    racine = NULL;

    for (int i = 0; i < n2; i++) {
        printf("\nInsertion de %d:\n", serie2[i]);
        racine = inserer(racine, serie2[i]);
        afficherArbre(racine, 0);
        printf("\n----------------------------------------------\n");
    }

    printf("\n===== SERIE 3 : 40, 20, 50, 10, 30, 25, 27 =====\n");
    int serie3[] = {40, 20, 50, 10, 30, 25, 27};
    int n3 = sizeof(serie3) / sizeof(serie3[0]);
    racine = NULL;

    for (int i = 0; i < n3; i++) {
        printf("\nInsertion de %d :\n", serie3[i]);
        racine = inserer(racine, serie3[i]);
        afficherArbre(racine, 0);
        printf("\n----------------------------------------------\n");
    }

    printf("\n===== SERIE 4 : 20, 10, 50, 60, 30, 40, 35 =====\n");
    int serie4[] = {20, 10, 50, 60, 30, 40, 35};
    int n4 = sizeof(serie4) / sizeof(serie4[0]);
    racine = NULL;

    for (int i = 0; i < n4; i++) {
        printf("\nInsertion de %d :\n", serie4[i]);
        racine = inserer(racine, serie4[i]);
        afficherArbre(racine, 0);
        printf("\n----------------------------------------------\n");
    }

    printf("\n===== SERIE 5 : 30, 10, 50, 5, 20, 40, 60, 70, 80 =====\n");
    int serie5[] = {30, 10, 50, 5, 20, 40, 60, 70, 80};
    int n5 = sizeof(serie5) / sizeof(serie5[0]);
    racine = NULL;

    for (int i = 0; i < n5; i++) {
        printf("\nInsertion de %d :\n", serie5[i]);
        racine = inserer(racine, serie5[i]);
        afficherArbre(racine, 0);
        printf("\n----------------------------------------------\n");
    }

    printf("\nArbre final équilibré :\n");
    afficherArbre(racine, 0);

    return 0;
}
