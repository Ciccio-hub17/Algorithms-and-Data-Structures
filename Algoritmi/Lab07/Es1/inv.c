#include "inv.h"

/* Lettura statistiche da file */
void stat_read(FILE *fp, stat_t *statp) {
    fscanf(fp, "%d %d %d %d %d %d", 
           &statp->hp, &statp->mp, &statp->atk, 
           &statp->def, &statp->mag, &statp->spr);
}

/* Stampa statistiche con soglia minima */
void stat_print(FILE *fp, stat_t *statp, int soglia) {
    fprintf(fp, "%d %d %d %d %d %d",
            (statp->hp < soglia) ? soglia : statp->hp,
            (statp->mp < soglia) ? soglia : statp->mp,
            (statp->atk < soglia) ? soglia : statp->atk,
            (statp->def < soglia) ? soglia : statp->def,
            (statp->mag < soglia) ? soglia : statp->mag,
            (statp->spr < soglia) ? soglia : statp->spr);
}

/* Lettura oggetto da file */
void inv_read(FILE *fp, inv_t *invp) {
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp, &invp->stat);
}

/* Stampa oggetto */
void inv_print(FILE *fp, inv_t *invp) {
    fprintf(fp, "%s %s ", invp->nome, invp->tipo);
    stat_print(fp, &invp->stat, 0); /* no soglia per oggetti */
    fprintf(fp, "\n");
}

/* Ritorna le statistiche di un oggetto */
stat_t inv_getStat(inv_t *invp) {
    return invp->stat;
}