#include <umps/libumps.h>
#include <umps/cp0.h>
#include "lib/utils.h"
#include "lib/pcb.h"
#include "lib/scheduler.h"
#include "lib/const.h"
#include "lib/listx.h"


void main	(int argc, char * argv[]){
    /*popolazione delle NEW AREAS*/
    setAreas();
    
    /*Inizializzare strutture dati di Phase1*/
    struct list_head* ready_queue;
    mkEmptyProcQ(ready_queue);
    setCODA(ready_queue);
    initPcbs(); //inizializziamo la pcbFree
        
    /*Inizializzazione dei pcb*/
    setPCB();

    //Inizializzo status processore
    setSTATUS(getSTATUS() | STATUS_TE | STATUS_IEc | STATUS_IM(1));
    
    //Carico il primo processo nel processore
    Load_New_Proc();
}