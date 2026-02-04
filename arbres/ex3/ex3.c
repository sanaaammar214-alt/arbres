#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int data;
    struct Noeud *fg;
    struct Noeud *fd;
} Noeud;

// Création d’un nœud
Noeud* creerNoeud(int valeur) {
    Noeud *nv = (Noeud*)malloc(sizeof(Noeud));
    nv->data = valeur;
    nv->fg = NULL;
    nv->fd = NULL;
    return nv;
}

// Insertion BST
void insererNoeud(Noeud**R, int val) {
    Noeud* NV,*tmp;
    NV=creerNoeud(val);
if(*R==NULL){
     *R=NV;
     return;
    }
tmp=*R;
while(1)
{
if(NV->data>tmp->data){
         if(tmp->fd==NULL){
             tmp->fd=NV; 
             break;
            }
         else tmp=tmp->fd;
}else{
if(tmp->fg==NULL){ 
    tmp->fg=NV; 
    break;
}
else tmp=tmp->fg;
}
}
}
void afficher90(Noeud* r, int espace) {
    if (r == NULL) return;

    espace += 5;

    // d'abord le fils droit (en haut)
    afficher90(r->fd, espace);

    // afficher la racine
    printf("\n");
    for (int i = 5; i < espace; i++)
        printf(" ");
    printf("%d\n", r->data);

    // puis le fils gauche (en bas)
    afficher90(r->fg, espace);
}


// Parcours Préfixe
void prefixe(Noeud* R) {
    if (R==NULL) return;
    printf("%d ", R->data);
    prefixe(R->fg);
    prefixe(R->fd);
}

// Parcours Infixe
void infixe(Noeud* R) {
    if (R==NULL) return;
    infixe(R->fg);
    printf("%d ", R->data);
    infixe(R->fd);
}

// Parcours Postfixe
void postfixe(Noeud* R) {
    if (R==NULL) 
    return;
    postfixe(R->fg);
    postfixe(R->fd);
    printf("%d ", R->data);
}
// Declaration du file de parcours BFS
typedef struct File {
    Noeud *n;
    struct File *suiv;
} File;

File* enfiler(File *F, Noeud *n) {
    File *nv = (File*)malloc(sizeof(File));
    nv->n = n;
    nv->suiv = NULL;

    if (!F) return nv;
    File *tmp = F;
    while (tmp->suiv) tmp = tmp->suiv;
    tmp->suiv = nv;
    return F;
}

Noeud* defiler(File **F) {
    if (!(*F)) return NULL;
    File *tmp = *F;
    Noeud *n = tmp->n;
    *F = (*F)->suiv;
    free(tmp);
    return n;
}

// Parcours BFS
void largeur(Noeud* r) {
    if (!r) return;
    File *F = NULL;
    Noeud *cur = r;

    while (cur != NULL) {
        if (cur->fg) F = enfiler(F, cur->fg);
        if (cur->fd) F = enfiler(F, cur->fd);
        printf("%d ", cur->data);
        cur = defiler(&F);
    }
}
Noeud* supprimerNoeud(Noeud* r, int val) {
    if (r == NULL) return r;

    // Recherche de la clé
    if (val < r->data)
        r->fg = supprimerNoeud(r->fg, val);
    else if (val > r->data)
        r->fd = supprimerNoeud(r->fd, val);

    // Trouvé : r->data == val
    else {
        // Cas 1 : aucun fils
        if (r->fg == NULL && r->fd == NULL) {
            free(r);
            return NULL;
        }

        // Cas 2 : un seul fils (droit)
        else if (r->fg == NULL) {
            Noeud* temp = r->fd;
            free(r);
            return temp;
        }

        // Cas 2 : un seul fils (gauche)
        else if (r->fd == NULL) {
            Noeud* temp = r->fg;
            free(r);
            return temp;
        }

        // Cas 3 : deux fils
        // Trouver le successeur : petit du sous-arbre droit
        Noeud* succ = r->fd;
        while (succ->fg != NULL)
            succ = succ->fg;

        r->data = succ->data; // Remplacer

        // Supprimer le successeur dans le sous-arbre droit
        r->fd = supprimerNoeud(r->fd, succ->data);
    }

    return r;
}



// *************** MAIN *************************


int main() {

    Noeud* R = NULL;

       int valeurs[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(valeurs) / sizeof(valeurs[0]);

    for (int i = 0; i < n; i++) {

        insererNoeud(&R, valeurs[i]);   // insertion

        printf("\nApres insertion de %d :\n", valeurs[i]);
        afficher90(R, 0);               // affichage en rotation 90°
        printf("\n--------------------------------\n");
    }
    printf("\n=== Parcours Prefixe ===\n");
    prefixe(R);
    printf("\n");

    printf("\n=== Parcours Infixe ===\n");
    infixe(R); 
    printf("\n");

    printf("\n=== Parcours Postfixe ===\n");
    postfixe(R);
    printf("\n");
    printf("\n=== Parcours en Largeur ===\n");
    largeur(R); printf("\n");
     // Suppression 1 : supprimer 20
    printf("\n\nSuppression de 20 :\n");
    R = supprimerNoeud(R, 20);
    afficher90(R, 0);

    // Suppression 2 : supprimer 30
    printf("\n\nSuppression de 30 :\n");
    R = supprimerNoeud(R, 30);
    afficher90(R, 0);

    // Suppression 3 : supprimer 50
    printf("\n\nSuppression de 50 :\n");
    R = supprimerNoeud(R, 50);
    afficher90(R, 0);




    return 0;
}