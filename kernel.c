#include "include/p15test_rikaya_v0.h"
#include "include/const.h"
#include "include/listx.h"
#include <umps/libumps.h>
#include <umps/types.h>
#include "include/pcb.h"
#include "handler.c"

#define SYSCALL_NEWAREA 0x200003D4
#define TRAP_NEWAREA 0x200002BC
#define TLB_NEWAREA 0x20000230
#define INTERRUPT_NEWAREA 0x2000008C

#define PROCESSO_ATTIVO /*var globale che accede al processo in esecuzione*/
#define QUEUE

#define TIME_SLICE 3000

void main	(int argc, char * argv[]){

    /*popolazione delle NEW AREAS*/
    state_t* status_syscall= (struct state) SYSCALL_NEWAREA
    tmp_status->status= AND(tmp_status->status.getStatus,11111110111111111111111111111100);
    tmp_status->status= OR(tmp_status->status.getStatus,00001000000000000000000000000000);
    tmp_status->reg[26]=RAMTOP;
    tmp_status->pc_epc= systemcall_handler();
    
    state_t* status_trap= (struct state) TRAP_NEWAREA
    tmp_status->status= AND(tmp_status->status.getStatus,11111110111111111111111111111100);
    tmp_status->status= OR(tmp_status->status.getStatus,00001000000000000000000000000000);
    tmp_status->reg[26]=RAMTOP;
    tmp_status->pc_epc= trap_handler();
    
    state_t* status_tlb= (struct state) TLB_NEWAREA
    tmp_status->status= AND(tmp_status->status.getStatus,11111110111111111111111111111100);
    tmp_status->status= OR(tmp_status->status.getStatus,00001000000000000000000000000000);
    tmp_status->reg[26]=RAMTOP;
    tmp_status->pc_epc= tlb_handler();
    
    state_t* status_interrupt= (struct state) INTERRUPT_NEWAREA
    tmp_status->status= AND(tmp_status->status.getStatus,11111110111111111111111111111100);
    tmp_status->status= OR(tmp_status->status.getStatus,00001000000000000000000000000000);
    tmp_status->reg[26]=RAMTOP;
    tmp_status->pc_epc= interrupt_handler();

    /*Inizializzare strutture dati di Phase1*/
    initPcbs(); //inizializziamo la pcbFree
    

    /*Inizializzare variabili del kernel->la lista dei processi:*/   

    /*creiamo la testa della lista dei processi*/
    struct list_head ready_queue;
    LIST_HEAD(ready_queue);

    QUEUE= ready_queue;

    /*assegnamo i testn ai pcb*/
    for(int i=1; i<4; i=i+1){
        pcb_t* tmp = allocPcb();

        tmp->p_s.status=AND(tmp->p_s,11111110111111111111111111111101) //virtual memory + kernel mode
        tmp->p_s.status=OR(tmp->p_s,00001000000000000000000000000001)  //local timer
        tmp->original_priority=i;
        tmp->priority=i;
        tmp->p_s.reg[26]=RAMTOP-FRAMESIZE*i
        
        if(i==1)  tmp->p_s.pc_epc=(memaddr) test1;
        if(i==2)  tmp->p_s.pc_epc=(memaddr) test2;
        if(i==3)  tmp->p_s.pc_epc=(memaddr) test3;

        if(tmp != NULL)
            insertProcQ(ready_queue, tmp);     
    }


    //PRENDO IL PRIMO PROCESSO IN CODA E LO CARICO NEL PROCESSORE
    pcb_t* proc= removeProcQ();
    PROCESSO_ATTIVO=proc;
    setTIMER(TIME_SLICE);
    LDST(proc->p_s);    //carichiamo le info del processo che voglio eseguire dentro il processore

    


}
