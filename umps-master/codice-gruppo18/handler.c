#include "const.h"
#include "listx.h"
#include <umps/libumps.h>
#include <umps/arch.h>
#include "pcb.h"

void interrupt_handler(){
    
    //resetto il timer
	setTIMER(3000);
    //log dei content switch
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
}
