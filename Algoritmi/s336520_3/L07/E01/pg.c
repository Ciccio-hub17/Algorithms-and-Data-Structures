#include "pg.h"

/* Lettura personaggio da file (ritorna 1 se successo, 0 altrimenti) */
int pg_read(FILE *fp, pg_t *pgp) {
    if (fp == NULL || pgp == NULL) return 0;
    
    if (fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe) != 3) {
        return 0;
    }
    
    stat_read(fp, &pgp->b_stat);
    
    /* Inizializza statistiche equipaggiamento a zero */
    pgp->eq_stat.hp = 0;
    pgp->eq_stat.mp = 0;
    pgp->eq_stat.atk = 0;
    pgp->eq_stat.def = 0;
    pgp->eq_stat.mag = 0;
    pgp->eq_stat.spr = 0;
    
    /* Crea equipaggiamento vuoto */
    pgp->equip = equipArray_init();
    
    return 1;
}

/* Pulizia personaggio (dealloca equipaggiamento) */
void pg_clean(pg_t *pgp) {
    if (pgp == NULL) return;
    if (pgp->equip != NULL) {
        equipArray_free(pgp->equip);
        pgp->equip = NULL;
    }
}

/* Calcola statistiche totali (base + equipaggiamento) */
static void pg_calcStats(pg_t *pgp, invArray_t invArray) {
    if (pgp == NULL || invArray == NULL) return;
    
    /* Reset statistiche equipaggiamento */
    pgp->eq_stat.hp = 0;
    pgp->eq_stat.mp = 0;
    pgp->eq_stat.atk = 0;
    pgp->eq_stat.def = 0;
    pgp->eq_stat.mag = 0;
    pgp->eq_stat.spr = 0;
    
    /* Somma i modificatori di ogni oggetto equipaggiato */
    for (int i = 0; i < EQUIP_SLOT; i++) {
        int idxObj = equipArray_getEquipByIndex(pgp->equip, i);
        if (idxObj != -1) {
            inv_t *obj = invArray_getByIndex(invArray, idxObj);
            if (obj != NULL) {
                stat_t objStat = inv_getStat(obj);
                pgp->eq_stat.hp += objStat.hp;
                pgp->eq_stat.mp += objStat.mp;
                pgp->eq_stat.atk += objStat.atk;
                pgp->eq_stat.def += objStat.def;
                pgp->eq_stat.mag += objStat.mag;
                pgp->eq_stat.spr += objStat.spr;
            }
        }
    }
}

/* Stampa personaggio */
void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    if (fp == NULL || pgp == NULL) return;
    
    fprintf(fp, "\n=== PERSONAGGIO ===\n");
    fprintf(fp, "Codice: %s\n", pgp->cod);
    fprintf(fp, "Nome: %s\n", pgp->nome);
    fprintf(fp, "Classe: %s\n", pgp->classe);
    
    fprintf(fp, "Statistiche base: ");
    stat_print(fp, &pgp->b_stat, 0);
    fprintf(fp, "\n");
    
    /* Calcola e stampa statistiche totali */
    pg_calcStats(pgp, invArray);
    
    stat_t totStat;
    totStat.hp = pgp->b_stat.hp + pgp->eq_stat.hp;
    totStat.mp = pgp->b_stat.mp + pgp->eq_stat.mp;
    totStat.atk = pgp->b_stat.atk + pgp->eq_stat.atk;
    totStat.def = pgp->b_stat.def + pgp->eq_stat.def;
    totStat.mag = pgp->b_stat.mag + pgp->eq_stat.mag;
    totStat.spr = pgp->b_stat.spr + pgp->eq_stat.spr;
    
    fprintf(fp, "Statistiche totali: ");
    stat_print(fp, &totStat, MIN_STAT);  /* applica soglia minima */
    fprintf(fp, "\n");
    
    /* Stampa equipaggiamento */
    if (invArray != NULL) {
        equipArray_print(fp, pgp->equip, invArray);
    }
}

/* Modifica equipaggiamento personaggio */
void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
    if (pgp == NULL || invArray == NULL) return;
    equipArray_update(pgp->equip, invArray);
}