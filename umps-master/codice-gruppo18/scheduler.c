#include <p15test_rikaya_v0.h>
#include "const.h"
#include "listx.h"
#include <umps/libumps.h>
#include "types.h"

#include "pcb.h"
int TIME_SLICE //pizza

void scheduler(list_head testa){
    if(!emptyProcQ(testa)){ //se la lista non è vuota prendo il processo con priorità più alta
    pcb_t* proc= removeProcQ(); //PRENDO IL PRIMO PROCESSO IN LISTA

    
    //carico le info del processo nella cpu
    
    content_switch(proc, testa);
    
    }
    
}


void content_switch(pcb_t* proc, testa){
    //setta il time slice
    
    //log dei content switch
    log_process_order(proc->original_priority);
    aging(proc, testa);
}

//passo l'ultimo processo preso a carico dallo scheduler
void aging(pcb_t* proc, list_head testa){
    
    proc->priority = proc->original_priority;
    insertProcQ(testa, proc);
    
    pcb_t* temp = testa->p_next;
    while(temp->p_next != NULL){
        temp->priority = (temp->priority + 1);
        temp = temp->p_next;
    }
}