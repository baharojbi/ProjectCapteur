#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdbool.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "capteur.h"


void
on_ajout_cap_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj_capteur, *gestion_capteur;


gestion_capteur=lookup_widget(objet,"gestion_capteur");

gtk_widget_destroy(gestion_capteur);
aj_capteur=lookup_widget(objet,"aj_capteur");
aj_capteur=create_aj_capteur();

gtk_widget_show(aj_capteur);
}






void
on_button_aj_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj1, *aj2, *aj3, *aj4, *bloc1, *bloc2, *bloc3;
GtkCalendar *ajc;
capteur e;
int c;
guint day, month, year;
aj1=lookup_widget(objet,"aj1");
aj2=lookup_widget(objet,"aj2");
aj3=lookup_widget(objet,"aj3");
ajc=lookup_widget(objet,"ajc");
bloc1=lookup_widget(objet,"ajA");
bloc2=lookup_widget(objet,"ajB");
bloc3=lookup_widget(objet,"ajC");
aj4=lookup_widget(objet,"aj4");

e.id=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aj1));
e.valeur=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aj2));
e.heure=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aj3));

gtk_calendar_get_date(GTK_CALENDAR(ajc), &day, &month, &year);
e.d.j=year;
e.d.m=month+1;
e.d.a=day;
strcpy(e.type,gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(bloc1))==1?"Debit":gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(bloc2))==1?"Dechet":"Temperature");
strcpy(e.etage,gtk_combo_box_get_active_text(GTK_COMBO_BOX(aj4)));

ajouter_capteur(e,"capteur.txt");
}


void
on_treeview_capteur_row_activated      (GtkTreeView     *treeview_capteur,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	gint id;
	capteur e;
	GtkWidget *pInfo;
	GtkTreeModel *model=gtk_tree_view_get_model(treeview_capteur);
	if(gtk_tree_model_get_iter(model,&iter,path)){
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,-1);
	e.id=id; pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Voulez-vous vraiment\nsupprimer ce capteur?");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_YES:
	gtk_widget_destroy(pInfo);
	supprimer_capteur(e,"capteur.txt");
	afficher_capteur(treeview_capteur,"capteur.txt");
	break;
	case GTK_RESPONSE_NO:
	gtk_widget_destroy(pInfo);
	break;
}	
}
}


void
on_modifier_cap_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *modifier_cap, *gestion_capteur;


gestion_capteur=lookup_widget(objet,"gestion_capteur");

gtk_widget_destroy(gestion_capteur);
modifier_cap=lookup_widget(objet,"modifier_cap");
modifier_cap=create_modifier_cap();

gtk_widget_show(modifier_cap);
}


void
on_rechercher_caop_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *recherche_cap, *gestion_capteur;


gestion_capteur=lookup_widget(objet,"gestion_capteur");

gtk_widget_destroy(gestion_capteur);
recherche_cap=lookup_widget(objet,"recherche_cap");
recherche_cap=create_recherche_cap();

gtk_widget_show(recherche_cap);
}


void
on_afficher_cap_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *affichage_cap1, *gestion_capteur;


gestion_capteur=lookup_widget(objet,"gestion_capteur");

//gtk_widget_destroy(gestion_capteur);
affichage_cap1=lookup_widget(objet,"affichage_cap1");
affichage_cap1=create_affichage_cap1();

gtk_widget_show(affichage_cap1);

treeview=lookup_widget(affichage_cap1,"treeview_capteur1");

afficher_capteur(treeview,"capteur.txt");
}


void
on_button_mod_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1,*mod2,*mod3, *mod4,*mod5,*mod6,*mod7, *bloc1, *bloc2, *bloc3;
GtkWidget *pInfo;
capteur e;
int c;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
bloc1=lookup_widget(objet,"modA");
bloc2=lookup_widget(objet,"modB");
bloc3=lookup_widget(objet,"modC");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");


e.id=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mod1));

strcpy(e.type,gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(bloc1))==1?"Debit":gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(bloc2))==1?"Dechet":"Temperature");
e.d.j=atoi(gtk_entry_get_text(GTK_ENTRY(mod2)));
e.d.m=atoi(gtk_entry_get_text(GTK_ENTRY(mod3)));
e.d.a=atoi(gtk_entry_get_text(GTK_ENTRY(mod4)));
e.heure=atoi(gtk_entry_get_text(GTK_ENTRY(mod5)));
e.valeur=atoi(gtk_entry_get_text(GTK_ENTRY(mod7)));
strcpy(e.etage,gtk_entry_get_text(GTK_ENTRY(mod6)));

modifier_capteur(e,"capteur.txt");
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Capteur modifié avec succès");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}





void
on_check_id_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1,*mod2,*mod3, *mod4,*mod5,*mod6,*mod7 ,*pInfo, *bloc1, *bloc2, *bloc3;
capteur p;
int a=0;
char ch[20],ch1[20],ch2[20],ch3[20],ch4[20];
FILE *f;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
bloc1=lookup_widget(objet,"modA");
bloc2=lookup_widget(objet,"modB");
bloc3=lookup_widget(objet,"modC");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");


int id=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mod1));
f = fopen("capteur.txt","r");
if(f!=NULL){
while(fscanf(f,"%d %d %d %d %d %d %s %s\n",&(p.id),&(p.valeur),&(p.d.j),&(p.d.m),&(p.d.a),&(p.heure),p.type,p.etage)!=EOF)
	{
		if(p.id==id){
			a=1;
			break;
                 }
	}
fclose(f);
}
if(a==1){
fflush(stdin);
sprintf(ch1,"%d",p.d.j);
gtk_entry_set_text(GTK_ENTRY(mod2),ch1);
sprintf(ch2,"%d",p.d.m);
gtk_entry_set_text(GTK_ENTRY(mod3),ch2);
sprintf(ch3,"%d",p.d.a);
gtk_entry_set_text(GTK_ENTRY(mod4),ch3);
sprintf(ch4,"%d",p.heure);
gtk_entry_set_text(GTK_ENTRY(mod5),ch4);

gtk_entry_set_text(GTK_ENTRY(mod6),p.etage);
sprintf(ch,"%d",p.valeur);
gtk_entry_set_text(GTK_ENTRY(mod7),ch);
strcmp(p.type,"Debit")==0?gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(bloc1),TRUE):strcmp(p.type,"Dechet")==0?gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(bloc2),TRUE):gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(bloc3),TRUE);
//gtk_combo_box_set_active(GTK_COMBO_BOX(mod4),p.etage-1);

}
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Capteur introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
}


void
on_retour1_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj_capteur, *gestion_capteur;


aj_capteur=lookup_widget(objet,"aj_capteur");

gtk_widget_destroy(aj_capteur);
gestion_capteur=lookup_widget(objet,"gestion_capteur");
gestion_capteur=create_gestion_capteur();

gtk_widget_show(gestion_capteur);
}


void
on_retour2_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *modifier_cap, *gestion_capteur;


modifier_cap=lookup_widget(objet,"modifier_cap");

gtk_widget_destroy(modifier_cap);
gestion_capteur=lookup_widget(objet,"gestion_capteur");
gestion_capteur=create_gestion_capteur();

gtk_widget_show(gestion_capteur);
}


void
on_retour3_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *recherche_cap, *gestion_capteur;


recherche_cap=lookup_widget(objet,"recherche_cap");

gtk_widget_destroy(recherche_cap);
gestion_capteur=lookup_widget(objet,"gestion_capteur");
gestion_capteur=create_gestion_capteur();

gtk_widget_show(gestion_capteur);
}


void
on_chercher_cap_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{

GtkWidget *r1, *r2, *r3, *r4, *r5, *r7,*r8, *pInfo;
char date_capteur[30];


FILE *f;
int x=-1;
capteur p;
char heure[20];
char valeur[20];

r1=lookup_widget(objet,"r1");

int id=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(r1));
r2=lookup_widget(objet,"r2");
r3=lookup_widget(objet,"r3");
r4=lookup_widget(objet,"r4");
r5=lookup_widget(objet,"r5");
r7=lookup_widget(objet,"r7");
r8=lookup_widget(objet,"r8");

//int iddd = stoi(idd);

f = fopen ("capteur.txt", "r");


  if (f!=NULL)
 {
  while (fscanf (f,"%d %d %d %d %d %d %s %s\n",&(p.id),&(p.valeur),&(p.d.j),&(p.d.m),&(p.d.a),&(p.heure),p.type,p.etage) != EOF)
  {
  
    if (id==p.id )
      
      x=1;
  }
    
    fclose (f);
 }





if (x==-1){

gtk_label_set_text(GTK_LABEL(r8),"l'id n'existe pas ");
gtk_label_set_text(GTK_LABEL(r2)," ");
gtk_label_set_text(GTK_LABEL(r3)," ");
gtk_label_set_text(GTK_LABEL(r4)," ");
gtk_label_set_text(GTK_LABEL(r5)," ");
gtk_label_set_text(GTK_LABEL(r7)," ");




}
else{capteur e = chercher_capteur(id);
fflush(stdin);
sprintf(date_capteur,"%d/%d/%d",e.d.j,e.d.m,e.d.a);
gtk_label_set_text(GTK_LABEL(r2),date_capteur);
sprintf(heure,"%d",e.heure);
gtk_label_set_text(GTK_LABEL(r3),heure);
gtk_label_set_text(GTK_LABEL(r4),e.type);
gtk_label_set_text(GTK_LABEL(r5),e.etage);
sprintf(valeur,"%d",e.valeur);
gtk_label_set_text(GTK_LABEL(r7),valeur);



}
}




void
on_defectueux_cap_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *gestion_capteur, *Defectueux;


gestion_capteur=lookup_widget(objet,"gestion_capteur");

//gtk_widget_destroy(gestion_capteur);
Defectueux=lookup_widget(objet,"Defectueux");
Defectueux=create_Defectueux();

gtk_widget_show(Defectueux);

treeview=lookup_widget(Defectueux,"treeview_defectueux");

capteurdeffectueux(treeview,"temperature.txt");
}


void
on_treeview_defectueux_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_refrech_def_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data)
{

}


void
on_retour4_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *Defectueux, *gestion_capteur;


Defectueux=lookup_widget(objet,"Defectueux");

gtk_widget_destroy(Defectueux);
gestion_capteur=lookup_widget(objet,"gestion_capteur");
gestion_capteur=create_gestion_capteur();

gtk_widget_show(gestion_capteur);
}





void
on_treeview_capteur1_row_activated      (GtkTreeView     *treeview_capteur1,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	gint id;
	capteur e;
	GtkWidget *pInfo;
	GtkTreeModel *model=gtk_tree_view_get_model(treeview_capteur1);
	if(gtk_tree_model_get_iter(model,&iter,path)){
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,-1);
	e.id=id; pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Voulez-vous vraiment\nsupprimer ce capteur?");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_YES:
	gtk_widget_destroy(pInfo);
	supprimer_capteur(e,"capteur.txt");
	afficher_capteur(treeview_capteur1,"capteur.txt");
	break;
	case GTK_RESPONSE_NO:
	gtk_widget_destroy(pInfo);
	break;
}	
}
}

void
on_refresh_capteur_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *affichage_cap1;


affichage_cap1=lookup_widget(objet,"affichage_cap1");

gtk_widget_destroy(affichage_cap1);
affichage_cap1=lookup_widget(objet,"affichage_cap1");
affichage_cap1=create_affichage_cap1();

gtk_widget_show(affichage_cap1);

treeview=lookup_widget(affichage_cap1,"treeview_capteur1");

afficher_capteur(treeview,"capteur.txt");
}

