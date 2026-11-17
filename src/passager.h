/*
 * Projet C - Carthage Airways
 * Tache 1 : Gestion des passagers
 *
 *  - CRUD + recherche des comptes passagers (unicite CIN / login / e-mail)
 *  - controles de saisie
 *  - liste triee par nom (croissant / decroissant)
 *  - espace passager : consulter / mettre a jour ses coordonnees
 *  - programme de fidelite (Standard, Silver, Gold, Platinum)
 *  - option 1 : statistiques
 *  - option 2 : blocage / reactivation de compte
 */

#ifndef PASSAGER_H_INCLUDED
#define PASSAGER_H_INCLUDED

#include <stdio.h>
#include <gtk/gtk.h>

#define FICHIER_PASSAGERS     "passager.txt"
#define FICHIER_UTILISATEURS  "utilisateurs.txt"
#define MAX_PASSAGERS         500

/* nombre de champs d'une ligne de passager.txt (verifie par fscanf) */
#define NB_CHAMPS_PASSAGER    16

typedef struct
{
    int jour;
    int mois;
    int annee;
} Date;

typedef struct
{
    char  cin[9];           /* 8 chiffres, identifiant unique          */
    char  nom[30];
    char  prenom[30];
    Date  naissance;
    char  sexe[10];         /* Homme / Femme                           */
    char  nationalite[30];
    char  tel[9];           /* 8 chiffres                              */
    char  email[60];        /* unique                                  */
    char  login[30];        /* unique, lien avec utilisateurs.txt      */
    int   points;           /* points de fidelite cumules              */
    int   nb_vols;          /* nombre de vols effectues                */
    float total_depense;    /* total depense en DT                     */
    int   bloque;           /* 0 = actif , 1 = bloque                  */
    char  motif[120];       /* motif du blocage ("aucun" si actif)     */
} Passager;

/* niveaux de fidelite */
enum { STANDARD, SILVER, GOLD, PLATINUM };

/* ---------- fichier passager.txt ---------- */
int   lire_passager(FILE *f, Passager *p);
void  ecrire_passager(FILE *f, Passager p);
int   ajouter_passager(Passager p);
int   modifier_passager(char *cin, Passager p);
int   supprimer_passager(char *cin);
int   chercher_passager(char *cin, Passager *p);
int   chercher_passager_login(char *login, Passager *p);
int   email_existe(char *email, char *cin_exclu);
int   charger_passagers(Passager t[], int max);

/* ---------- affichage / tri / recherche ---------- */
void  trier_passagers(Passager t[], int n, int croissant);
int   correspond_filtre(Passager p, char *filtre);
int   afficher_passagers(GtkWidget *liste, char *filtre, int croissant);

/* ---------- controles de saisie ---------- */
int   calculer_age(Date d);
int   verifier_cin(char *cin);
int   verifier_nom(char *nom);
int   verifier_date(Date d);
int   verifier_tel(char *tel);
int   verifier_email(char *email);
int   verifier_login(char *login);
int   controler_passager(Passager p, char *erreur);

/* ---------- utilitaires texte ---------- */
void  nettoyer_texte(char *s);          /* supprime espaces debut/fin, espaces -> '_' */
void  texte_affichage(char *dest, char *src); /* '_' -> ' ' pour l'ecran */

/* ---------- programme de fidelite ---------- */
int   niveau_fidelite(int points);
void  nom_niveau(int niveau, char *nom);
float remise_fidelite(int points);
void  avantages_fidelite(int points, char *texte);
int   seuil_niveau_suivant(int points);
int   calculer_points(float prix_billet);
int   enregistrer_vol(char *cin, float prix_billet, int *points_gagnes, int *ancien_niveau, int *nouveau_niveau);
float prix_apres_remise(char *cin, float prix);

/* ---------- option 2 : blocage ---------- */
int   bloquer_passager(char *cin, char *motif);
int   reactiver_passager(char *cin);

/* ---------- option 1 : statistiques ---------- */
void  afficher_statistiques(GtkWidget *tv_age, GtkWidget *tv_niveau, GtkWidget *tv_top, char *resume);

/* ---------- comptes (utilisateurs.txt : login mdp role) ---------- */
int   verifier_utilisateur(char *login, char *mdp, char *role);
int   login_existe(char *login);
int   ajouter_utilisateur(char *login, char *mdp, char *role);
int   modifier_utilisateur(char *ancien_login, char *nouveau_login, char *nouveau_mdp);
int   supprimer_utilisateur(char *login);

#endif /* PASSAGER_H_INCLUDED */
