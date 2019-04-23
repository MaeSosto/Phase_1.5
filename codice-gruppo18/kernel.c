#include "p15test_rikaya_v0.c"
#include "const.h"
#include "listx.h"
#include <umps/libumps.h>
#include <umps/types.h>
#include <umps/cp0.h>
#include "pcb.h"
#include "utils.c"
#include "handler.h"

#define SYSCALL_NEWAREA 0x200003D4
#define TRAP_NEWAREA 0x200002BC
#define TLB_NEWAREA 0x20000230
#define INTERRUPT_NEWAREA 0x2000008C


#define ANDBIT_STATE 0xFEFFFFFC
#define ORBIT_STATE 0x8000000
#define ANDBIT_PCB 0xFEFFFFFD
#define ORBIT_PCB 0x8000001
#define TIME_SLICE 3000
#define FRAMESIZE 1024



void main	(int argc, char * argv[]){

    /*popolazione delle NEW AREAS*/
    
    ((state_t*)SYSCALL_NEWAREA)->status = ((state_t*)SYSCALL_NEWAREA)->status & ANDBIT_STATE;
    ((state_t*)SYSCALL_NEWAREA)->status = ((state_t*)SYSCALL_NEWAREA)->status | ORBIT_STATE;
    ((state_t*)SYSCALL_NEWAREA)->reg_sp = RAMTOP;
    ((state_t*)SYSCALL_NEWAREA)->pc_epc = (memaddr) systemcall_handler;
    
    ((state_t*)TRAP_NEWAREA)->status= ((state_t*)TRAP_NEWAREA)->status & ANDBIT_STATE;
    ((state_t*)TRAP_NEWAREA)->status= ((state_t*)TRAP_NEWAREA)->status | ORBIT_STATE;
    ((state_t*)TRAP_NEWAREA)->reg_sp= RAMTOP;
    ((state_t*)TRAP_NEWAREA)->pc_epc= (memaddr) trap_handler;
    
    ((state_t*)TLB_NEWAREA)->status= ((state_t*)TLB_NEWAREA)->status & ANDBIT_STATE;
    ((state_t*)TLB_NEWAREA)->status= ((state_t*)TLB_NEWAREA)->status | ORBIT_STATE;
    ((state_t*)TLB_NEWAREA)->reg_sp= RAMTOP;
    ((state_t*)TLB_NEWAREA)->pc_epc= (memaddr) tlb_handler;
    
    ((state_t*)INTERRUPT_NEWAREA)->status= ((state_t*)INTERRUPT_NEWAREA)->status & ANDBIT_STATE;
    ((state_t*)INTERRUPT_NEWAREA)->status= ((state_t*)INTERRUPT_NEWAREA)->status | ORBIT_STATE;
    ((state_t*)INTERRUPT_NEWAREA)->reg_sp= RAMTOP;
    ((state_t*)INTERRUPT_NEWAREA)->pc_epc= (memaddr) interrupt_handler;


    /*Inizializzare strutture dati di Phase1*/
    struct list_head* ready_queue;
    mkEmptyProcQ(ready_queue);
    
    setCODA(ready_queue);
    initPcbs(); //inizializziamo la pcbFree
        


    /*assegnamo i testn ai pcb*/
    for(int i=1; i<4; i=i+1){

        pcb_t* tmp;

        tmp->p_s.status= tmp->p_s.status & ANDBIT_PCB;    //virtual memory + kernel mode
        tmp->p_s.status= tmp->p_s.status | ORBIT_PCB;  //local timer

        
        tmp->original_priority = i;
        tmp->priority = i;
        tmp->p_s.reg_sp = RAMTOP-FRAMESIZE * i;
        
        if(i==1)  tmp->p_s.pc_epc=(memaddr) test1;
        if(i==2)  tmp->p_s.pc_epc=(memaddr) test2;
        if(i==3)  tmp->p_s.pc_epc=(memaddr) test3;
        tmp = allocPcb();

        if(tmp != NULL)
            insertProcQ(ready_queue, tmp);     
    }

    //aggiungere status iniziale processore
    setSTATUS(getSTATUS() | STATUS_TE | STATUS_IEc | STATUS_IM(1));

    
    pcb_t* proc= removeProcQ(ready_queue);
    setPROC(proc);
    setTIMER(TIME_SLICE);
    LDST(&(proc->p_s));    // - carichiamo le info del processo che voglio eseguire dentro il processore
    
}



