#ifndef INV_H
#define INV_H

//voglio usare nel main un puntatore ad inventario, chiamato inventory
typedef struct tblInv_s *inventory;
typedef struct inv_s *p_object;

inventory create_inventory ();  //alloca l'inventario (il wrap di come è fatto)

void inv_read_file (inventory inv, char *filename); //legge il file di un inventario già pronto

p_object search_object_by_name (char *name_to_search, inventory inv);  //cerca un oggetto per nome

void print_object (p_object object); //stampa i dettagli di un oggetto

void free_Inventory (inventory inv); //Libera la memoria dopo aver creato l'inventario

char *extract_object_name (p_object p);

int extract_stat (p_object p, int index);

#endif