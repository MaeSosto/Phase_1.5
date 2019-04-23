#include <umps/libumps.h>
#include <umps/cp0.h>
#include "lib/utils.h"
#include "lib/pcb.h"
#include "lib/scheduler.h"
#include "lib/const.h"
#include "lib/listx.h"

#define NEW_STATUS 

/*Inizializzare strutture dati di Phase1*/
    LIST_HEAD(ready_queue);
    //struct list_head* Proc = &ready_queue;

void main	(int argc, char * argv[]){
    /*popolazione delle NEW AREAS*/
    setAreas();
    addokbuf("Aree settate \n");
    
    
    initPcbs(); //inizializziamo la pcbFree
    addokbuf("init pcb \n");
    mkEmptyProcQ(&ready_queue);
    addokbuf("mkEmptyProcQ \n");
    setCODA(&ready_queue);
    
    /*Inizializzazione dei pcb e li buttiamo dentro la ready queue*/

  
    pcb_t* proc1=NEW_PCB(1);
    pcb_t* proc2=NEW_PCB(2);
    pcb_t* proc3=NEW_PCB(3);
    addokbuf("PCB 1-2-3 FATTO \n");

    
    insertProcQ(&(ready_queue), proc1);
    insertProcQ(&(ready_queue), proc2);
    insertProcQ(&(ready_queue), proc3); 
    addokbuf("HO SETTATO LE STRUTTURE DATI");

    setCODA(&ready_queue);
    addokbuf("coda settata");
    


    //Inizializzo status processore
    setTIMER(3000000);
    addokbuf("timer settato \n");
    setSTATUS(getSTATUS() | STATUS_TE | STATUS_IEc | STATUS_IM(1));
    addokbuf("status settato \n");

    //Carico il primo processo nel processore
    Load_New_Proc();







}