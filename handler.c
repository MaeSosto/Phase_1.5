#include "include/p15test_rikaya_v0.h"
#include "include/const.h"
#include "include/listx.h"
#include <umps/libumps.h>
#include <umps/types.h>
#include "include/pcb.h"

void interrupt_handler(){
    proc=PROCESSO_ATTIVO;
    testa=QUEUE;

    
    //log dei content switch -> (int process) fa riferimento al numero del test
    log_process_order(proc->original_priority);    

    //FASE DI AGING 
    /*modifico la priorità*/
    pcb_t* temp = testa->p_next;
    while(temp->p_next != NULL){
        temp->priority = (temp->priority + 1);
        temp = temp->p_next;
    }

    proc->priority = proc->original_priority;
    insertProcQ(testa, proc);


    pcb_t* proc= removeProcQ();
    PROCESSO_ATTIVO=proc;
    setTIMER(TIME_SLICE);
    LDST(proc->p_s); 

     //resetto il timer
	setTIMER(3000);
}

void systemcall_handler(){
    //Cause.ExcCode (SYS=8, BP=9)
    proc=PROCESSO_ATTIVO;
    testa=QUEUE;

    if(proc->p_s.cause==8){ //SYS
        freePcb(proc);
        pcb_t* proc= removeProcQ();
        PROCESSO_ATTIVO=proc;
        setTIMER(TIME_SLICE);
        LDST(proc->p_s); 

        //resetto il timer
        setTIMER(3000);
    }
}

void tlb_handler(){
}

void trap_handler(){
}
