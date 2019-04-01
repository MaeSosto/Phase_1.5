#include "p15test_rikaya_v0.h"


void main	(int argc, char * argv[]){

    /*POPOLAZIONE DELLE NEW AREAS*/
    /*AREE DA POPOLARE:
        SYS/BP New Area
        SYS/BP Old Area
        Trap New Area
        Trap Old Area
        TLB New Area
        TLB Old Area
        Interrupt New Area
        Interrupt Old Area
    */

    /*Inizializzare il PC all’indirizzo dell’handler del nucleo che gestisce quell’eccezione.
        Cause is a CP0 register containing information about the current exception and/or 
        pending device interrupts.
    */
    
    /*Inizializzare $SP a RAMPTOP
        The function _start(), whose code can be found in the file CRTSO.S, sets the $SP to RAMTOP
         (stacks in μMPS2 grow “downward” from high memory to low memory), and calls main()
    */

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
