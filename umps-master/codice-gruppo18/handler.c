#include "p15test_rikaya_v0.c"
#include "const.h"
#include "listx.h"
#include <libumps.h>
#include "types.h"
#include "pcb.h"

void interrupt_handler(){
    proc=PROCESSO_ATTIVO;
    testa=QUEUE;

    //log dei content switch -> (int process) fa riferimento al numero del test
    log_process_order(proc->original_priority);    

    //FASE DI AGING PIZZA
    proc->priority = proc->original_priority;
    insertProcQ(testa, proc);
    
    /*modifico la priorità*/
    pcb_t* temp = testa->p_next;
    while(temp->p_next != NULL){
        temp->priority = (temp->priority + 1);
        temp = temp->p_next;
    }


    pcb_t* proc= removeProcQ();
    PROCESSO_ATTIVO=proc;
    setSTATUS();
    LDST(); 

     //resetto il timer
	setTIMER(3000);
}

void systemcall_handler(){
    //Cause.ExcCode (SYS=8, BP=9)




    
}

void tlb_handler(){
}

void trap_handler(){
}
