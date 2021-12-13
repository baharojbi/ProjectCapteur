#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>

typedef struct date {

    int j;
    int m;
    int a;

}datee;

typedef struct Capteur {

        int id;
	int valeur;
        datee d;
	int heure;
	char type[30];
        char etage[30];
	
	
}capteur;

typedef struct temp

{

int jour, heuree, numCap;
float valeurCap;

}capteur_temp;

void ajouter_capteur(capteur e, char *fname);
void supprimer_capteur(capteur e,char *fname);
void afficher_capteur(GtkWidget *liste,char *fname);
void modifier_capteur(capteur e,char *fname);
/*capteur chercher_capteur(int id,char *fname ,int *v);*/
capteur chercher_capteur(int id);
void capteurdeffectueux(GtkWidget *liste, char *fname );
