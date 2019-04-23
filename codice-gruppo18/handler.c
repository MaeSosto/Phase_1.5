#include "include/handler.h"

#define OLD_AREA_SYS 0x2000348
#define TIME_SLICE 3000

void interrupt_handler(){
    pcb_t* proc = getPROC();
    struct list_head* testa = getCODA();

    log_process_order(proc->original_priority);    
 
    aging();
    proc=getPROC();
    insertProcQ(testa, proc);
    
    if(emptyProcQ(testa)){
        HALT()
    }
    else{
        proc = removeProcQ(testa);
        setPROC(proc);
        setTIMER(TIME_SLICE);
        LDST(&(proc->p_s)); 
    }
}

void systemcall_handler(){
    pcb_t* proc = getPROC();
    struct list_head* testa=getCODA();
    //Cause.ExcCode (SYS=8, BP=9)

    struct state* old_area=(struct state*) OLD_AREA_SYS; 

    if(CAUSE_GET_EXCCODE(old_area->cause)==8){ //allora avviene una sys
        if(old_area->reg_a3==3){ //allora è stata sollevata SYS3
            if(emptyProcQ(testa)){
                HALTED();
            }
            else{
                
                log_process_order(proc->priority);
                aging();                
                freePcb(proc);

                pcb_t* proc= removeProcQ(testa);
                setPROC(proc);
                setTIMER(TIME_SLICE);
                LDST(&(proc->p_s)); 
            }
        }

        
    }
}

void tlb_handler(){
}

void trap_handler(){
}
