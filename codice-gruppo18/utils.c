#include "pcb.h"
#include "const.h"
#include "listx.h"
#include <umps/libumps.h>
#include <umps/types.h>

struct list_head* CODA;
pcb_t* PROCESSO_ATTIVO= NULL;

pcb_t* getPROC(){
    return PROCESSO_ATTIVO;
}

void setPROC(pcb_t* proc){
    PROCESSO_ATTIVO=proc;
}

struct list_head* getCODA(){
    return CODA;
}

void setCODA(struct list_head* coda){
    CODA= coda;
}


void aging(){
    pcb_t* temp;
	list_for_each_entry(temp, CODA, p_next){
		temp->priority = temp->priority +1;
	}
    PROCESSO_ATTIVO->priority = PROCESSO_ATTIVO->original_priority;
}
