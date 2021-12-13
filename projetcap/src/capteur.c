#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "capteur.h"
#include "callbacks.h"
#include <gtk/gtk.h>

enum
{
	EID,
	EVALEUR,
	EDATE_CAPTEUR,
	EHEURE,
	ETYPE,
	EETAGE,
	COLUMNS
};
enum{
EJOURE,
EHEUREE,
ENUMCAP,
EVALEURCAP,
COLUMNS1
};
////////////////////
void ajouter_capteur(capteur e, char *fname){
GtkWidget *dialog;
capteur p;
int c=0;
FILE *f=fopen(fname,"a+");
gpointer user_data;
if(f!=NULL){
while(fscanf(f,"%d %d %d %d %d %d %s %s\n",&(p.id),&(p.valeur),&(p.d.j),&(p.d.m),&(p.d.a),&(p.heure),p.type,p.etage) !=EOF){
if (p.id==e.id){
c++;
}
}
if (c!=0){
dialog=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Capteur déja existant !");
	switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(dialog);
	break;
	}}
else if (c==0){
fprintf(f,"%d %d %d %d %d %d %s %s\n",e.id,e.valeur,e.d.j,e.d.m,e.d.a,e.heure,e.type,e.etage);
dialog=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Capteur ajouté avec succès !");
	switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(dialog);
	break;
	}}
fclose(f);
}

}
/////////



////////////////////////////////////
void modifier_capteur(capteur e, char *fname){
capteur p;
/*char jour1[20];
char mois1[20];
char annee1[20];
char heure1[20];
char valeur1[20];
char jour2[20];
char mois2[20];
char annee2[20];
char heure2[20];
char valeur2[20];*/
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f==NULL||g==NULL)
{
	return;
}
else{
/*sprintf(jour1,"%d",e.d.j);
sprintf(mois1,"%d",e.d.m);
sprintf(annee1,"%d",e.d.a);
sprintf(heure1,"%d",e.heure);
sprintf(valeur1,"%d",e.valeur);
sprintf(jour2,"%d",p.d.j);
sprintf(mois2,"%d",p.d.m);
sprintf(annee2,"%d",p.d.a);
sprintf(heure2,"%d",p.heure);
sprintf(valeur2,"%d",p.valeur);*/
	while(fscanf(f,"%d %d %d %d %d %d %s %s\n",&(p.id),&(p.valeur),&(p.d.j),&(p.d.m),&(p.d.a),&(p.heure),p.type,p.etage)!=EOF)
{
		if(p.id!=e.id)
			fprintf(g,"%d %d %d %d %d %d %s %s\n",p.id,p.valeur,p.d.j,p.d.m,p.d.a,p.heure,p.type,p.etage);
		else
			fprintf(g,"%d %d %d %d %d %d %s %s\n",p.id,e.valeur,e.d.j,e.d.m,e.d.a,e.heure,e.type,e.etage);
}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Capteur modifié avec succès !");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}

///////////////////////////////////

void afficher_capteur(GtkWidget *liste, char *fname)
{
capteur p;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
gchar date_capteur[30];
FILE *f;


store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Id", renderer,"text",EID, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Valeur", renderer,"text",EVALEUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Date", renderer,"text",EDATE_CAPTEUR, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Heure", renderer,"text",EHEURE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Type", renderer,"text",ETYPE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Etage", renderer,"text",EETAGE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	store=gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
f=fopen(fname,"r");
if(f!=NULL)

{ f = fopen(fname,"a+");
		while(fscanf(f,"%d %d %d %d %d %d %s %s\n",&(p.id),&(p.valeur),&(p.d.j),&(p.d.m),&(p.d.a),&(p.heure),p.type,p.etage)!=EOF)
{
sprintf(date_capteur,"%d/%d/%d",p.d.j,p.d.m,p.d.a);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,EID,p.id,EVALEUR,p.valeur,EDATE_CAPTEUR,date_capteur,EHEURE,p.heure,ETYPE,p.type,EETAGE,p.etage,-1);
	}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}

gtk_tree_view_set_enable_search(GTK_TREE_VIEW(liste),TRUE);

}




////////////////
/*capteur chercher_capteur(int id, char *fname){
capteur p, e;
FILE *f;

f=fopen(fname,"r");
if(f!=NULL){
	while(fscanf(f,"%d %d %d %d %d %d %s %s \n",&(p.id),&(p.valeur),&(p.d.j),&(p.d.m),&(p.d.a),&(p.heure),p.type,p.etage)!=EOF)
	{
		if(p.id==id)
			return p;
	}
	fclose(f);
}
p.id=-1;
return e;
}*/

////////////
capteur chercher_capteur(int id)
{
FILE *f=NULL;

  capteur e;
  capteur p;
f = fopen ("capteur.txt", "r");


  if (f!=NULL)
 { 


    while (fscanf (f,"%d %d %d %d %d %d %s %s\n",&(p.id),&(p.valeur),&(p.d.j),&(p.d.m),&(p.d.a),&(p.heure),p.type,p.etage)
!=EOF)
    if  (id== p.id) 
	{
        
	strcpy(e.type,p.type);
        strcpy(e.etage,p.etage);
        e.valeur=p.valeur;
	e.heure=p.heure;
	e.d.j=p.d.j;
	e.d.m=p.d.m;
        e.d.a=p.d.a;
	
 	
        
    }
    
  fclose (f);
 }
return(e);
}

////////////////////
void capteurdeffectueux(GtkWidget *liste, char *fname )
{capteur_temp a ;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
gchar date[20];
FILE *f;
time_t t;
time(&t);

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Jour", renderer,"text",EJOURE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Heure", renderer,"text",EHEUREE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" NumCap", renderer,"text",ENUMCAP, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ValeurCap", renderer,"text",EVALEURCAP, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	store=gtk_list_store_new(COLUMNS1, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_FLOAT);
f=fopen(fname,"r");
if(f!=NULL)
{ f = fopen(fname,"a+");
		while(fscanf(f,"%d %d %d %f\n",&(a.jour),&(a.heuree),&(a.numCap),&(a.valeurCap))!=EOF)
{
if(a.valeurCap<10||a.valeurCap>30){

gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,ENUMCAP,a.numCap,EJOURE,a.jour,EHEUREE,a.heuree,EVALEURCAP,a.valeurCap,-1);
}
}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
}

void supprimer_capteur(capteur e, char *fname)
{
capteur p;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f!=NULL&&g!=NULL){
	while(fscanf(f,"%d %d %d %d %d %d %s %s\n",&(p.id),&(p.valeur),&(p.d.j),&(p.d.m),&(p.d.a),&(p.heure),p.type,p.etage)!=EOF)
	{
		if(p.id!=e.id)
			fprintf(g,"%d %d %d %d %d %d %s %s\n",p.id,p.valeur,p.d.j,p.d.m,p.d.a,p.heure,p.type,p.etage);
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Capteur supprimé avec succès");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}

