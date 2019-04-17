#include <p15test_rikaya_v0.h>
#include "const.h"
#include "listx.h"
#include <umps/libumps.h>
#include "types.h"


#include "pcb.h"
#define SYSCALL_NEWAREA 0x200003D4
#define TRAP_NEWAREA 0x200002BC
#define TLB_NEWAREA 0x20000230
#define INTERRUPT_NEWAREA 0x2000008C

void main	(int argc, char * argv[]){

 /*POPOLAZIONE DELLE NEW AREAS*/
    /*utilizzare variabile state_t per accedere ai registri per modificare i valori e far partire CP0*/
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


    /*Inizializzare il PC all’indirizzo dell’handler del nucleo che gestisce quell’eccezione. */
   
    /*Inizializzare $SP a RAMPTOP*/
   
     /*Inizializzare il registro di status:
        - mascherare interrupt Status.IEc=0
        - disabilitare virtual memory Status.VMc=0
        - settare kernel mode ON
        - abilitare un timer Status.TE=1 & Timer=0x0000.0000
    */

    /*popolazione delle NEW AREAS*/
    state_t* tmp_status= (struct state) SYSCALL_NEWAREA
    tmp_status->status= AND(tmp_status->status.getStatus,11111110111111111111111111111100);
    tmp_status->status= OR(tmp_status->status.getStatus,00001000000000000000000000000000);
    tmp_status->reg[26]=RAMTOP;
    tmp_status->pc_epc= //pizza
    
    state_t* tmp_status= (struct state) TRAP_NEWAREA
    tmp_status->status= AND(tmp_status->status.getStatus,11111110111111111111111111111100);
    tmp_status->status= OR(tmp_status->status.getStatus,00001000000000000000000000000000);
    tmp_status->reg[26]=RAMTOP;
    tmp_status->pc_epc= //pizza
    
    state_t* tmp_status= (struct state) TLB_NEWAREA
    tmp_status->status= AND(tmp_status->status.getStatus,11111110111111111111111111111100);
    tmp_status->status= OR(tmp_status->status.getStatus,00001000000000000000000000000000);
    tmp_status->reg[26]=RAMTOP;
    tmp_status->pc_epc= //pizza
    
    state_t* tmp_status= (struct state) INTERRUPT_NEWAREA
    tmp_status->status= AND(tmp_status->status.getStatus,11111110111111111111111111111100);
    tmp_status->status= OR(tmp_status->status.getStatus,00001000000000000000000000000000);
    tmp_status->reg[26]=RAMTOP;
    tmp_status->pc_epc= interrupt_handler();

    //void INITCPU(uint32_t cpuid, state_t *start_state, state_t *state_areas);


    /*Inizializzare strutture dati di Phase1*/
    initPcbs(); //inizializziamo la pcbFree
    

    /*Inizializzare variabili del kernel:*/

    /*creiamo la testa della lista dei processi*/
    struct list_head ready_queue;
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
    //controllo pcbfree abbia pcb != NULL
    //tolgo pcb dalla pcbfree
    //aggiungo pcb a ready_queue

    /*assegnamo i testn ai pcb*/
    for(int i=1; i<4; i=i+1){
        pcb_t* tmp = allocPcb();

         /*Instanziare il PCB e lo stato dei 3 processi di test
        - Interrupt abilitati               0  bit = 1
        - Virtual Memory OFF                24 bit = 0
        - Processor Local Timer abilitato   27 bit = 1
        - Kernel-Mode ON                    1  bit = 0
        - $SP=RAMTOP-FRAMESIZE*n
        - priorita’ = n
        - Settare PC all’entry-point dei test pstate.pc_epc=(memaddr) testn
        */

        tmp->p_s->status=AND(tmp->p_s,11111110111111111111111111111101) //virtual memory + kernel mode
        tmp->p_s->status=OR(tmp->p_s,00001000000000000000000000000001)  //local timer
        tmp->original_priority=i;
        tmp->priority=i;
        tmp->p_s->reg[26]=RAMTOP-FRAMESIZE*i
        
        if(i==1)  tmp->p_s->pc_epc=(memaddr) test1;
        if(i==2)  tmp->p_s->pc_epc=(memaddr) test2;
        if(i==3)  tmp->p_s->pc_epc=(memaddr) test3;

        if(tmp != NULL)
            insertProcQ(ready_queue, tmp);      //&, puntatori eh? pizza
    }


    //PRENDO IL PRIMO PROCESSO IN CODA E LO CARICO NEL PROCESSORE
    pcb_t* proc= removeProcQ();
    //funzione che carica il proc nella cpu

    //settare il timer
    setTIMER(3000);


}
