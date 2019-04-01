#include "p15test_rikaya_v0.h"


void main	(int argc, char * argv[]){


    /*POPOLAZIONE DELLE NEW AREAS*/
    /*Inizializzare il PC all’indirizzo dell’handler del nucleo che gestisce quell’eccezione.*/
    
    /*Inizializzare $SP a RAMPTOP*/

    /*Inizializzare il registro di status:
        - mascherare interrupt
        - disabilitare virtual memory
        - settare kernel mode ON
        - abilitare un timer 
    */

    /*Inizializzare strutture dati di Phase1*/
    initPcbs();

    /*Inizializzare variabili del kernel:*/
    LIST_HEAD(ready_queue);

    /*Instanziare il PCB e lo stato dei 3 processi di test
        - Interrupt abilitati
        - Virtual Memory OFF
        - Processor Local Timer abilitato
        - Kernel-Mode ON
        - $SP=RAMTOP-FRAMESIZE*n
        - priorita’ = n
        - Settare PC all’entry-point dei test pstate.pc_epc=(memaddr) testn
    */

    /*Inseririre i processi nella Ready Queue*/







}
