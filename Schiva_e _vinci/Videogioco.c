/*
author: Arrigoni Simone
date
es.
*/
#include <conio.h>      //kbhit getc
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "./Informatica/grafica/graficaArrigoni.h"

//dichiarazione tasti
#define FUNZ 224
#define SU 72
#define GIU 80
#define DX 77
#define SX 75
#define ESC 27
#define FINE 79

//dichiarazione posizione iniziale personaggio
#define POSX 82
#define POSY 35

//dichiarazione dei colori
#define RED 12
#define REDOST 204
#define ORANGE 102

//dichiarazione delle righe e colonne dei quadrati e del personaggio
#define RIGHE 3
#define COLONNE 5

#define RIGHEOST_MED 8
#define COLONNEOST_MED 4

//dichiarazione delle velocit�
#define VELOCITA350 350
#define VELOCITA300 300
#define VELOCITA250 250
#define VELOCITA200 200
#define VELOCITA150 150
#define VELOCITA100 100
#define VELOCITA75 75
#define VELOCITA50 50

typedef struct {
    int x;
    int y;
} PosizioneOgg;

typedef struct {
    int x;
    int y;
} Posizione;

typedef struct {
    char p[RIGHE][COLONNE];//personaggio
    char o2[RIGHEOST_MED][COLONNEOST_MED];//quadrato 1
    char o3[RIGHEOST_MED][COLONNEOST_MED];//quadrato 2
} Carattere;

typedef struct {
    Carattere car;//carattere per gli oggetti
    Posizione pos;//posizione personaggio
    PosizioneOgg posOgg;//posizione oggetti
    unsigned short colore;//colore personaggio
    unsigned short coloreOsta2;//colore ostacolo 1
    unsigned short coloreOsta3;//colore ostacolo 2
} Oggetto;

void creaOggetto(Oggetto *p, int x, int y, unsigned short colore) {
    //scorro la matrice
    for(int r=0; r< RIGHE; r++) {
        for(int c=0; c<COLONNE ; c++) {
            //alla posizione desiderata di riga e colonna scrivo il carattere occorrente
            if(r == 0 && c == 2) {
                p->car.p[r][c] = '_';
            }

            if(r == 1 && c == 1) {
                p->car.p[r][c] = '/';
            }

            if(r == 1 && c == 2) {
                p->car.p[r][c] = '_';
            }

            if(r == 1 && c == 3) {
                p->car.p[r][c] = '\\';
            }

            if(r == 2 && c == 0) {
                p->car.p[r][c] = '0';
            }

            if(r == 2 && c == 4) {
                p->car.p[r][c] = '0';
            }

        }
    }

    //passo la posizione iniziale di x  e y alla struttura del personaggio
    p->pos.x = x;
    p->pos.y = y;

    //imposto il colore
    p->colore = colore;
}

void creaOstacolo(Oggetto *p2, int orange) {
    //scorro la tabella
    for(int r=0; r<RIGHEOST_MED; r++) {
        for (int c=0; c<COLONNEOST_MED; c++) {
            //riempio tutta la tabella con asterischi per formare il quadrato
            p2->car.o2[r][c] = '*';
        }
    }
    //imposto il colore
    p2->coloreOsta2 = orange;
}

void creaOstacolo1(Oggetto *p3, int red) {
    //scorro la tabella
    for(int r=0; r<RIGHEOST_MED; r++) {
        for (int c=0; c<COLONNEOST_MED; c++) {
            //riempio tutta la tabella con asterischi per formare il quadrato
            p3->car.o3[r][c] = '*';
        }
    }
    //imposto il colore
    p3->coloreOsta3 = red;
}

void disegnaOggetto(Oggetto p) {
    unsigned short oldColor = getTextColor(); //salvo il colore attuale
    //scorro la tabella
    for(int r=0; r< RIGHE; r++) {
        for(int c=0; c<COLONNE ; c++) {
            //in posizione corretta ovvero x + le colonne e y + le righe
            gotoxy(p.pos.x + c, p.pos.y + r);

            if(r == 0 && c == 2) {
                setTextColor(p.colore);//inserisco il colore
                printf("%c", p.car.p[r][c]);//stampo la cella interessata
                setTextColor(oldColor);//reinserisco il colore precedente
            }

            if(r == 1 && c == 1) {
                setTextColor(p.colore);
                printf("%c", p.car.p[r][c]);
                setTextColor(oldColor);
            }

            if(r == 1 && c == 2) {
                setTextColor(p.colore);
                printf("%c", p.car.p[r][c]);
                setTextColor(oldColor);
            }

            if(r == 1 && c == 3) {
                setTextColor(p.colore);
                printf("%c", p.car.p[r][c]);
                setTextColor(oldColor);
            }

            if(r == 2 && c == 0) {
                setTextColor(p.colore);
                printf("%c", p.car.p[r][c]);
                setTextColor(oldColor);
            }

            if(r == 2 && c == 4) {
                setTextColor(p.colore);
                printf("%c", p.car.p[r][c]);
                setTextColor(oldColor);
            }


        }
    }
}

void cancellaOstacolo2(Oggetto *o2) {
    //scorro la tabella
    for(int r=0; r<RIGHEOST_MED; r++) {
        for (int c=0; c<COLONNEOST_MED; c++) {
            //in posizione corretta ovvero x + le colonne e y + le righe
            gotoxy(o2->posOgg.x + r, o2->posOgg.y + c);

            setTextColor(0);//imposto il colore nero ovvero  lo sfondo
            printf("%c", o2->car.o2[r][c]);//stampo la cella
        }
    }

}

void disegnaOstacoli(Oggetto *o2) {
    unsigned short oldColor = getTextColor();//salvo il colore precedente

    //scorro la tabella
    for(int r=0; r<RIGHEOST_MED; r++) {
        for (int c=0; c<COLONNEOST_MED; c++) {
            //in posizione corretta ovvero x + le colonne e y + le righe
            gotoxy(o2->posOgg.x + r, o2->posOgg.y + c);

            setTextColor(o2->coloreOsta2);//imposto il colore
            printf("%c", o2->car.o2[r][c]);//stampo la cella
            setTextColor(oldColor);//reimposto il colore precedente
        }
    }
}

void spostaOstacolo(Oggetto *o2, int score) {
    int lim_min = 53, lim_max = 92, x, lim_miny = 0, lim_maxy = 10, y;//dichiaro il limite massimo e minimo per la x e il limite massimo e minimo per la y

    srand(time(NULL));

    o2->posOgg.y = o2->posOgg.y + 1;//sposto il quadrato di uno in gi�

    if(o2->posOgg.y == 34) {//controllo se il quadrato ha toccato terra

        if(score < 15) {//se il punteggio � minore di 15

            //genero nuove coordinate per x e y
            x = lim_min + rand() % (lim_max - lim_min + 1);
            y = lim_miny + rand() % (lim_maxy - lim_miny + 1);

            o2->posOgg.x = x;
            o2->posOgg.y = y;

        } else {

            if(score >= 15 && score < 25) {//se il punteggio � maggiore o uguale a 15 e minore di 25
                //modifico il limite massimo e minimo della y
                lim_miny = 10;
                lim_maxy = 25;

                //genero nuove coordinate per x e y
                x = lim_min + rand() % (lim_max - lim_min + 1);
                y = lim_miny + rand() % (lim_maxy - lim_miny + 1);

                o2->posOgg.x = x;
                o2->posOgg.y = y;

            } else {

                if(score >= 25 ) {//se il punteggio � maggiore o uguale a 25
                    //modifico il limite massimo e minimo della y e anchhe il limite minimo della x
                    int meta = 77;
                    lim_miny = 5;
                    lim_maxy = 20;

                    //genero nuove coordinate per x e y
                    x = meta + rand() % (lim_max - meta + 1);
                    y = lim_miny + rand() % (lim_maxy - lim_miny + 1);

                    o2->posOgg.x = x;
                    o2->posOgg.y = y;
                }
            }
        }
    }
    disegnaOstacoli(o2);//chiamo la procedura per far disegnare i quadrati
}

void spostaOstacolo1(Oggetto *o3, int score) {
    int lim_min = 53, lim_max = 72, x, lim_miny = 15, lim_maxy = 25, y;//dichiaro i limiti massimi e minimi per la x e la y

    o3->posOgg.y = o3->posOgg.y + 1;//sposto il quadrato di uno in gi�

    if(o3->posOgg.y == 34) {//controllo se il quadrato ha toccato terra

        if(score >= 25) {//se il punteggio � maggiore o uguale a 25

            //genero nuove coordinate per x e y
            srand(time(NULL));
            x = lim_min + rand() % (lim_max - lim_min + 1);
            y = lim_miny + rand() % (lim_maxy - lim_miny + 1);

            o3->posOgg.x = x;
            o3->posOgg.y = y;

        }
    }

    disegnaOstacoli(o3);//chiamo la procedura per far disegnare i quadrati
}

void cancella(Oggetto *p) {
    //scorro la matrice
    for(int r=0; r< RIGHE; r++) {
        for(int c=0; c<COLONNE ; c++) {
            //in posizione corretta ovvero x + le colonne e y + le righe
            gotoxy(p->pos.x + c, p->pos.y+r);
            setTextColor(0);//imposto il colore nero dello sfondo
            printf("%c", p->car.p[r][c]);//stampo la casella
        }
    }
}

void destraOggetto(Oggetto *p) {
    if(p->pos.x < 94) {//controllo che il personaggio non vada oltre il bordo destro
        cancella(p);//se non va oltre cancello
        p->pos.x = p->pos.x + 4;//lo sposto
    }
}

void sinistraOggetto(Oggetto *p) {
    if(p->pos.x > 54) {//controllo che il personaggio non vada oltre il bordo sinistro
        cancella(p);//se non va oltre cancello
        p->pos.x = p->pos.x - 4;//lo sposto
    }
}

int calcoloPunteggio(int score, Oggetto o2, Oggetto o3, Oggetto o1, bool *colpito) {

    if(o2.posOgg.y == 33  || o3.posOgg.y == 33) {//controllo se ono dei due quadrati ha toccato il terreno

        score += 5;//se ha toccato aggiungo 5 punti
    } else {
        //controllo se il primo quadrato ha toccato il personaggio
        if(o2.posOgg.y + 3 == o1.pos.y && (o2.posOgg.x == o1.pos.x + 4 || o2.posOgg.x + 7 == o1.pos.x ||
                                           o2.posOgg.x + 6 == o1.pos.x || o2.posOgg.x + 5 == o1.pos.x ||
                                           o2.posOgg.x + 4 == o1.pos.x || o2.posOgg.x + 3 == o1.pos.x ||
                                           o2.posOgg.x + 2 == o1.pos.x || o2.posOgg.x + 1 == o1.pos.x ||
                                           o2.posOgg.x == o1.pos.x || o2.posOgg.x == o1.pos.x + 1 ||
                                           o2.posOgg.x == o1.pos.x + 2 || o2.posOgg.x == o1.pos.x + 3 ||
                                           o2.posOgg.x == o1.pos.x + 3 || o2.posOgg.x + 1 == o1.pos.x + 1 ||
                                           o2.posOgg.x + 2 == o1.pos.x + 2 || o2.posOgg.x + 3 == o1.pos.x + 3||
                                           o2.posOgg.x + 4 == o1.pos.x + 4)) {
            *colpito = true;//se viene colpito imposto a true la variabile "colpito" passata per valore
        } else {
            //controllo se il secondo quadrato ha toccato il personaggio
            if(o3.posOgg.y + 3 == o1.pos.y && (o3.posOgg.x == o1.pos.x + 4 || o3.posOgg.x + 7 == o1.pos.x
                                               || o3.posOgg.x + 6 == o1.pos.x || o3.posOgg.x + 5 == o1.pos.x
                                               || o3.posOgg.x + 4 == o1.pos.x || o3.posOgg.x + 3 == o1.pos.x
                                               || o3.posOgg.x + 2 == o1.pos.x || o3.posOgg.x + 1 == o1.pos.x
                                               || o3.posOgg.x == o1.pos.x + 4 || o3.posOgg.x == o1.pos.x + 3
                                               || o3.posOgg.x == o1.pos.x + 2 || o3.posOgg.x == o1.pos.x + 1
                                               || o3.posOgg.x == o1.pos.x + 3 || o2.posOgg.x + 1 == o1.pos.x + 1
                                               || o2.posOgg.x + 2 == o1.pos.x + 2 || o2.posOgg.x + 3 == o1.pos.x + 3
                                               || o2.posOgg.x + 4 == o1.pos.x + 4)) {

                *colpito = true;//se viene colpito imposto a true la variabile "colpito" passata per valore
            }
        }
    }

    return score;//ritorno il valore del punteggio
}

void calcoloPunteggioMaxRec(int score, bool *colpito) {
    int puntMax, puntRec;//creo due variabili per il punteggio massimo e recente

    //dichiaro le variabili per la scrittura e la lettura dai file
    FILE *fp;
    FILE *fp1;
    FILE *fp2;

    fp1 = fopen("record.txt", "r");//apro il file per il punteggio massimo in lettura

    if(fp1 == NULL) {//controllo che il file esiste

        *colpito = true;//se non esiste termino il gioco

    } else {
        fscanf(fp1,"%d", &puntMax);//leggo il contenuto del file

        if(puntMax < score) {//controllo il punteggio con quello letto dal file

            fp = fopen("record.txt", "w");//se � maggiore apro il file in scrittura

            if(fp == NULL) {//controllo che il file esiste

                *colpito = true;//se non esiste termino il gioco

            } else {
                fprintf(fp,"%d", score);//se il file esiste stampo il punteggio
                fclose(fp);//chiudo il file per il punteggio massimo in scrittura
            }
        }
    }
    fclose(fp1);//chiudo il file per il punteggio massimo in lettura

    fp2 = fopen("precedente.txt", "w");//apro il file per il punteggio recente in lettura

    if(fp2 == NULL) {//controllo che il file esiste

        *colpito = true;//se non esiste termino il gioco

    } else {

        fprintf(fp2,"%d", score);//se il file esiste stampo il punteggio recente
    }

    fclose(fp2);
}

bool isTastoFunzione(unsigned char c) {
    return (c == 224 || c == 0); //224 per tasti frecce e Fine, 0 per tasti F1, F2,...
}

int menu() {
    clrscr();//pulisco lo  schermo

    int scelta;
    //stampo le varie possibilit�
    gotoxy(63, 10);
    printf("|-------------------------------------|");
    gotoxy(63, 11);
    printf("|1| - Nuova partita -                 |\n");
    gotoxy(63, 12);
    printf("|-------------------------------------|");
    gotoxy(63, 13);
    printf("|2| - Regolamento -                   |\n");
    gotoxy(63, 14);
    printf("|-------------------------------------|");
    gotoxy(63, 15);
    printf("|3| - Punteggio record e precedente - |\n");
    gotoxy(63, 16);
    printf("|-------------------------------------|");
    gotoxy(63, 17);
    printf("|4| - Esci -                          |\n");
    gotoxy(63, 18);
    printf("|-------------------------------------|");
    gotoxy(63, 19);
    printf("|Scelta:                              |");
    scanf("%d", &scelta);

    clrscr();//pulisco lo  schermo dalla stampa del menu
    //ritorno la scelta
    return scelta;
}

int main() {
    Oggetto arma; //personaaggio che si  sposta
    Oggetto p2, p3; //quadrati che sis spostano

    int posX = POSX; //posizione x iniziale personaggio
    int posY = POSY; //posizione y iniziale personaggio
    int scelta; //variabile menu

    FILE *fp;//dichiarazione file p unteggio massimo
    FILE *fp1;//dichiarazione  file punteggio precedente
    int puntMax, puntRec; //variabili per la lettura dei punteggi dal file

    int lim_min = 53, lim_max = 92, x, lim_miny = 0, lim_maxy = 10, y, meta = 76;  //limite minimo iniziale della posizione del  quadrato

    creaOggetto(&arma, posX, posY, RED); //creazione del personaggio
    //creazione dei due quadrati
    creaOstacolo(&p2, ORANGE);
    creaOstacolo(&p3, REDOST);

    unsigned char a; //codice ASCII tasto premuto
    bool esci, chiudi, colpito; //per uscire dal ciclo lettura tasti, e terminare il gioco

    cursor_hide();//nasconde il cursore

    do {
        //imposto tutte le variabili di termine a false
        esci= false;
        chiudi = false;
        colpito = false;

        int score = 0; //punteggio

        //creazione del  punto casuale usando i limiti per entrambi i quadrati
        srand(time(NULL));
        p2.posOgg.x = lim_min + rand() % (lim_max - lim_min + 1);
        p2.posOgg.y = lim_miny + rand() % (lim_maxy - lim_miny + 1);

        p3.posOgg.x = lim_min + rand() % (meta - lim_min + 1);
        p3.posOgg.y = lim_miny + rand() % (lim_maxy - lim_miny + 1);

        setTextColor(15);
        scelta = menu();//chiamo la funzione menu

        switch(scelta) {
        case 1://caso 1 parte il gioco

            while (!colpito && !esci) {//controllo con il while se si viene colpiti o se si esce dal gioco

                /*gotoxy(30, 1);
                printf("%d", score);//stampa punteggio
                gotoxy(30, 1);*/

                rettangoloPienoColore(52, 0, 1, 40, '*', 153); //bordo SX
                rettangoloPienoColore(100, 0, 1, 40, '*', 153); //bordo DX
                rettangoloPienoColore(53, 38, 47, 2, '*', 170); //terren

                disegnaOggetto(arma);//disegno il personaggio

                cancellaOstacolo2(&p2);//cancello il  quadrato
                spostaOstacolo(&p2, score);//sposto l'ostacolo a seconda del punteggio corrente


                if(score >= 25) {//se il punteggio � maggiore o uguale a 25
                    cancellaOstacolo2(&p3);//cancello il secondo quadrato
                    spostaOstacolo1(&p3, score);//sposto il secondo l'ostacolo
                }

                score = calcoloPunteggio(score, p2, p3, arma, &colpito);//chiamo la funzione per il calcolo del punteggio

                //controllo il punteggio pi� aumenta, pi� la velocit� della caduta dei quadrati aumenta
                if(score < 15) {
                    delay(VELOCITA350);
                } else {
                    if(score >= 15 && score < 25) {
                        delay(VELOCITA300);
                    } else {
                        if(score >= 25 && score < 50) {
                            delay(VELOCITA250);
                        } else {
                            if(score >= 50 && score < 75) {
                                delay(VELOCITA200);
                            } else {
                                if(score >= 75 && score < 150) {
                                    delay(VELOCITA150);
                                } else {
                                    if(score >= 150 && score < 250) {
                                        delay(VELOCITA100);
                                    } else {
                                        if(score >= 250 && score <= 375) {
                                            delay(VELOCITA75);
                                        } else {
                                            if(score > 375) {
                                                delay(VELOCITA50);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }


                calcoloPunteggioMaxRec(score, &colpito);//chiamo la procedura per il calcolo del punteggio massimo e recente


                if (kbhit() == true)    {
                    a = getch();
                    // se e' un tasto funzione come F1, F2 o sono le frecce o Home e End sono composto da 2 byte
                    //rimane il secondo byte che viene letto nella if successiva
                    if (isTastoFunzione(a)) {//� un tasto funzione
                        //leggo il secondo byte contenente il tipo di tasto funzione premuto
                        a = getch();

                        switch (a) {

                        case SX: // freccia sx
                            sinistraOggetto(&arma);//chiamo la procedura per lo spostamento a sinistra

                            break;

                        case DX: // freccia dx
                            destraOggetto(&arma);//chiamo la procedura per lo spostamento a destra

                            break;
                        }

                    } else { //non � un tasto funzione
                        switch (a) {
                        case ESC:  //tasto ESC
                            esci = true;
                            break;
                        }
                    }
                }
                gotoxy(30, 1);
                printf("%d", score);
                gotoxy(30, 1);
            }


            break;

        case 2:

            //stampo le regole del gioco
            gotoxy(72, 0);
            printf("|REGOLE|");

            //mi spoposto in posizione x;y e stampo i tasti da utilizzare
            gotoxy(52, 2);
            printf("TASTI:");
            gotoxy(52, 3);
            printf("Destra = freccia destra");
            gotoxy(52, 4);
            printf("Sinistra = freccia sinistra");

            //mi spoposto in posizione x;y e stampo il funzionamento del punteggio
            gotoxy(52, 7);
            printf("PUNTEGGIO:");
            gotoxy(52, 8);
            printf("Per segnare punti bisogna schivare i cubi e fargli toccare terra,");
            gotoxy(52, 9);
            printf("in questo modo si acquisiranno 5 punti.");
            gotoxy(52, 10);
            printf("Se si viene colpiti da un cubo HAI PERSO.");

            //mi spoposto in posizione x;y e stampo il funzionamento della grafica
            gotoxy(52, 13);
            printf("GRAFICA:");
            gotoxy(52, 14);
            printf("PER GIOCARE BISOGNA IMPOSTARE LA FINESTRA A SCHERMO INTERO");

            gotoxy(105, 35);
            printf("Sciacciare 2 volte ESC per tornare in dientro");

            while(esci == false) {//controllo se l'utente esce dalla sezione regole

                if (kbhit() == true)    {
                    a = getch();
                    // se e' un tasto funzione come F1, F2 o sono le frecce o Home e End sono composto da 2 byte
                    //rimane il secondo byte che viene letto nella if successiva
                    if (!isTastoFunzione(a)) { //� un tasto funzione
                        //leggo il secondo byte contenente il tipo di tasto funzione premuto
                        a = getch();

                        switch (a) {
                        case ESC:  //tasto ESC
                            esci = true;
                            break;
                        }
                    }
                }
            }

            clrscr();

            break;

        case 3://vengono visualizzati il punteggio massimo e recente

            fp = fopen("record.txt", "r");//apro il file con il punteggio massimo
            if(fp == NULL) {//controllo se esiste
                printf("Il file non esiste.");
            } else {
                //leggo il punteggio massimo
                fscanf(fp,"%d", &puntMax);

                //se esiste vado in posizione x;y e stampo il punteggio massimo
                gotoxy(63, 13);
                printf("|IL MASSIMO PUNTEGGIO REGISTRATO E'|");
                gotoxy(78, 15);
                printf("%d", puntMax);
                gotoxy(55, 17);
                printf("------------------------------------------------------");
            }

            fclose(fp);//chiudo il file

            fp1 = fopen("precedente.txt", "r");//apro il file con il punteggio recente

            if(fp1 == NULL) {//controllo se esiste
                printf("Il file non esiste");
            } else {
                //leggo il punteggio massimo
                fscanf(fp1,"%d", &puntRec);

                //se esiste vado in posizione x;y e stampo il punteggio recente
                gotoxy(60, 20);
                printf("|IL PUNTEGGIO DELLA PARTITA PRECEDENTE E'|");
                gotoxy(78, 22);
                printf("%d", puntRec);
            }

            fclose(fp1);//chiudo il file

            gotoxy(105, 35);
            printf("Sciacciare 2 volte ESC per tornare in dientro");


            while(esci == false) {//controllo se l' utente esce dalla sezione punteggi

                if (kbhit() == true)    {
                    a = getch();
                    // se e' un tasto funzione come F1, F2 o sono le frecce o Home e End sono composto da 2 byte
                    //rimane il secondo byte che viene letto nella if successiva
                    if (!isTastoFunzione(a)) { //� un tasto funzione
                        //leggo il secondo byte contenente il tipo di tasto funzione premuto
                        a = getch();

                        switch (a) {
                        case ESC:  //tasto ESC
                            esci = true;
                            break;
                        }
                    }
                }
            }

            clrscr();

            break;
        case 4:
            //chiudo il gioco
            chiudi = true;
            break;
        }
    } while(chiudi == false);//termino il ciclo
}
