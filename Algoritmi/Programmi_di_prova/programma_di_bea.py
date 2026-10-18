#la metto come costante in km
DIST = 50 #km

#mi faccio dare in input la distanza totale in chilometri (\n serve per andare a capo quando visualizzi)
#int mi serve per traformare il valore restituito dalla funzione input (che di default restituisce una stringa)
#in un intero (dato che dopo farò un divisione)
contachilometri = int (input ("Dammi la distanza che hai percorso in chilometri\n"))

tempo = int (input ("Dammi il tempo in giorni\n"))

#moltiplico la distanza che farei per andare a lavoro per due (andata e ritorno) e poi
#per i giorni in cui sono andato a lavoro

chilometri_per_lavoro = 2*DIST*tempo

#a questo punto calcolo la percentuale

percentuale_lavoro = chilometri_per_lavoro/contachilometri * 100

#printo il risultato (:.2f serve per stampare solo 2 cifre decimali)
print (f"La percentuale dell'uso dell'auto per lavoro e' stata {percentuale_lavoro:.2f}%")

print (f"Uso della macchina personale {100-percentuale_lavoro:.2f}%")
