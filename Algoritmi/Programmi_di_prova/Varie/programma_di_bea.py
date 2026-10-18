
N = 9

def ricerca_indice (parcheggio):
    posizione = 0
    best_conta = 0
    conta = 0
    i = 0
    while (i < N):
        while (i < N and parcheggio[i] == False):
            conta = conta+1
            i = i+1

        if (conta > best_conta):
            best_conta = conta
            j = i-conta-1
            posizione = int ((i+j) / 2)

        conta = 0
        i = i+1

    return posizione

def main ():
    parcheggio = [False] * N
    
    #metto la prima macchina a meta 
    punt_medio = int ((N-1) / 2)
    parcheggio[punt_medio] = True

    print (f"Passo 1\n")
    for m in range (N):
        if (parcheggio[m] == False):
            print ("_", end = " ")
        else:
            print ("X", end = " ")
    print ("\n")

    #ciclo sui posti rimanenti
    for k in range (N-1):
        
        posizione = ricerca_indice (parcheggio)
        parcheggio[posizione] = True
        print (f"Passo {k+2}\n")
        for m in range (N):
            if (parcheggio[m] == False):
                print ("_", end = " ")
            else:
                print ("X", end = " ")
        print ("\n")


main ()