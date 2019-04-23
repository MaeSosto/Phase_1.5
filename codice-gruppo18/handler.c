#include "lib/scheduler.h"
#include "lib/utils.h"
#include "lib/pcb.h"
#include <umps/cp0.h>
#include "lib/p15test_rikaya_v0.h"


#define OLD_AREA_SYS 0x2000348
#define TIME_SLICE 3000

void interrupt_handler(){
    addokbuf("STA AVVENENDO UN INTERRUPT \n");
    pcb_t* proc = getPROC();
    struct list_head* testa = getCODA();

    log_process_order(proc->original_priority);    
 
    Aging();
    insertProcQ(testa, proc);
    setCODA(testa);

    if(emptyProcQ(testa)){
        HALT();
    }
    else{
        Load_New_Proc();
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
                HALT();
            }
            else{
                log_process_order(proc->priority);
                Aging();                
                freePcb(proc);
                setCODA(testa);
                Load_New_Proc();
            }
        }

        
    }
}

void tlb_handler(){
}

void trap_handler(){
}
