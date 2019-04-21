#include "include/handler.h"


void interrupt_handler(){
    pcb_t* proc = getPROC();
    //log dei content switch -> (int process) fa riferimento al numero del test
    log_process_order(proc->original_priority);    

    //FASE DI AGING 
    /*modifico la priorità*/
    struct list_head* testa = getCODA();

    aging();

    insertProcQ(testa, proc);
    
    proc = removeProcQ(testa);
    PROCESSO_ATTIVO = proc;
    setTIMER(TIME_SLICE);
    LDST(&(proc->p_s)); 

     //resetto il timer
	setTIMER(3000);
}

void systemcall_handler(){
    pcb_t* proc = getPROC();
     struct list_head* testa=getCODA();
    //Cause.ExcCode (SYS=8, BP=9)
    proc = PROCESSO_ATTIVO;

    if(proc->p_s.cause == 8){ //SYS
        freePcb(proc);
        pcb_t* proc= removeProcQ(testa);
        PROCESSO_ATTIVO=proc;
        setTIMER(TIME_SLICE);
        LDST(&(proc->p_s)); 

        //resetto il timer
        setTIMER(3000);
    }
}

void tlb_handler(){
}

void trap_handler(){
}
