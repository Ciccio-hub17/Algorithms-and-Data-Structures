

int label_to_index (char label[]);
char* index_to_label (int index);

int search_table (char *stringa); //Questa cerca il nome associato a quel vertice che si trova in posizione 0 
                                        //nella stringa data in input. Per fare questo cicla sulla tabella di simboli
                                        //fino a quando non trova un nome la cui strstr(stringa, nome_trovato)
                                        //il carattere che si trova in posizione 0 (e poi ovviamente controlla che combaci), 
                                        //altrimenti ritorna -1.
                                        //Se lo trova, ritorna l'indice del vertice associato.

int search_label_used (char *label); //Questa restituisce l'indice dove è salvata la parola del vertice che si sta cercando