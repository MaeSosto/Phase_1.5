#include "include/pcb.h"
#include "include/const.h"
#include "include/listx.h"
#include <umps/libumps.h>
#include <umps/types.h>
#include <include/types_rikaya.h>

struct list_head* CODA;

pcb_t* PROCESSO_ATTIVO;

pcb_t* getPROC(){
    return PROCESSO_ATTIVO;
}

void setPROC(pcb_t* proc){
    PROCESSO_ATTIVO=proc;
}

struct list_head* getCODA(){
    return CODA;
}

void setCODA(struct list_head coda){
    CODA= &coda;
}


void aging(){
    pcb_t* temp = CODA->next;
    while(&temp->p_next != NULL){
        temp->priority = temp->priority +1;
        temp = &temp->p_next;
    }
    PROCESSO_ATTIVO->priority = PROCESSO_ATTIVO->original_priority;
}
