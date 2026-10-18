#ifndef PG_H
#define PG_H
#include "inv.h"

typedef struct tabPg_s *link_Pg_t; //puntatore al wrapper della lista dei personaggi


link_Pg_t create_pgs_list (); //inizializza il wrapper
void load_pgs_from_file (link_Pg_t tabPg, char *filename);  //usa un filename per caricare i personaggi
void insert_new_pg (link_Pg_t tabPg);//inserisci nuovo personaggio
void remove_pg (link_Pg_t tabPg, char *code);//togli personaggio
void add_new_object (char *code, link_Pg_t tabPg, char *object_name, inventory tabInv);//aggiungi oggetto all'inventario
void remove_object (char *code, link_Pg_t tabPg, char *object_name);//togli oggetto dall'inventario
void calculate_statistic (link_Pg_t tabPg, char *code); //calcola le statistiche di riferimento
void free_list_pg(link_Pg_t tabPg); //libera la memoria dinamica allocata


#endif