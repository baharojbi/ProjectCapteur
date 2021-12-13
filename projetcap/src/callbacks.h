#include <gtk/gtk.h>


void
on_ajout_cap_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_button_aj_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeview_capteur_row_activated      (GtkTreeView     *treeview_capteur,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_modifier_cap_clicked                (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_rechercher_caop_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_afficher_cap_clicked                (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_mod_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_check_id_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_retour1_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_retour2_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_retour3_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_chercher_cap_clicked                (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_defectueux_cap_clicked              (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeview_defectueux_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_refrech_def_clicked                 (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_retour4_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);



void
on_treeview_capteur1_row_activated     (GtkTreeView     *treeview_capteur1,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_refresh_capteur_clicked             (GtkWidget       *objet,
                                        gpointer         user_data);
