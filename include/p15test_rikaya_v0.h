#ifndef P15TEST_RIKAYA__V0_H
#define P15TEST_RIKAYA__V0_H
#include <umps/types.h>


/*STAMPA UNA STRINGA SUL TEMRINALE E RESTITUISCE TRUE SE E' 
 * STATA STAMPATA CORRETTAMENTE ALTRIMENTI FALSE*/
unsigned int termprint(char *str, unsigned int term);

/*METTE OGNI CARATTERE DELLA STRINGA IN OKBUF E SCRIVE LA STRINGA
 *  SUL TERMINALE*/
void addokbuf(char *strp);

/*METTE OGNI CARATTERE DELLA STRINA SU ERRBUF, SCRIVE LA STRINGA 
 * SUL TERMINALE E SPEGNE IL SISTEMA CON UN MESSAGGIO DI PANIC (ERRORE)*/
void adderrbuf(char *strp);


/*QUESTO NON SO COSA SIA*/
void log_process_order(int process);

/*TEST*/
void test1();
void test2();
void test3();



#endif