#include "lib/types_rikaya.h"
#include "lib/scheduler.h"

#define TIME_SLICE 3000

void Load_New_Proc(){
    addokbuf("CARICO UN PROCESSO \n");
    struct list_head* ready_queue;
    ready_queue=getCODA();

    pcb_t* proc= removeProcQ(ready_queue);
    setPROC(proc);

    setTIMER(TIME_SLICE);
    addokbuf("settato il time_slice \n");
    LDST(&(proc->p_s));   
}

void Aging(){
    struct list_head* CODA = getCODA();
    pcb_t* PROCESSO_ATTIVO = getPROC();
    pcb_t* temp;

	list_for_each_entry(temp, CODA, p_next){
		temp->priority = temp->priority +1;
	}

    setCODA(CODA);
    
    PROCESSO_ATTIVO->priority = PROCESSO_ATTIVO->original_priority;
    setPROC(PROCESSO_ATTIVO);
}