#include "lib/pcb.h"
#include "lib/utils.h"
#include "lib/handler.h"
#include <umps/cp0.h>
#include <umps/types.h>
#include <umps/libumps.h>
#include "lib/p15test_rikaya_v0.h"

#define SYSCALL_NEWAREA 0x200003D4
#define TRAP_NEWAREA 0x200002BC
#define TLB_NEWAREA 0x200001A4
#define INTERRUPT_NEWAREA 0x2000008C

#define FRAMESIZE 1024

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
    CODA = coda;
}


void setAreas(){
    ((state_t*)SYSCALL_NEWAREA)->status = ((state_t*)SYSCALL_NEWAREA)->status | STATUS_IEc;
    ((state_t*)SYSCALL_NEWAREA)->status = ((state_t*)SYSCALL_NEWAREA)->status & ~STATUS_KUc;
    ((state_t*)SYSCALL_NEWAREA)->status = ((state_t*)SYSCALL_NEWAREA)->status & ~STATUS_IM_MASK;
    ((state_t*)SYSCALL_NEWAREA)->status = ((state_t*)SYSCALL_NEWAREA)->status & ~STATUS_VMc;
    ((state_t*)SYSCALL_NEWAREA)->status = ((state_t*)SYSCALL_NEWAREA)->status | STATUS_TE;
    ((state_t*)SYSCALL_NEWAREA)->reg_sp = RAMTOP;
    ((state_t*)SYSCALL_NEWAREA)->pc_epc = (memaddr) systemcall_handler;
    
    ((state_t*)TRAP_NEWAREA)->status = ((state_t*)TRAP_NEWAREA)->status | STATUS_IEc;
    ((state_t*)TRAP_NEWAREA)->status = ((state_t*)TRAP_NEWAREA)->status & ~STATUS_KUc;
    ((state_t*)TRAP_NEWAREA)->status = ((state_t*)TRAP_NEWAREA)->status & ~STATUS_IM_MASK;
    ((state_t*)TRAP_NEWAREA)->status = ((state_t*)TRAP_NEWAREA)->status & ~STATUS_VMc;
    ((state_t*)TRAP_NEWAREA)->status = ((state_t*)TRAP_NEWAREA)->status | STATUS_TE;
    ((state_t*)TRAP_NEWAREA)->reg_sp= RAMTOP;
    ((state_t*)TRAP_NEWAREA)->pc_epc= (memaddr) trap_handler;
    
    ((state_t*)TLB_NEWAREA)->status = ((state_t*)TLB_NEWAREA)->status | STATUS_IEc;
    ((state_t*)TLB_NEWAREA)->status = ((state_t*)TLB_NEWAREA)->status & ~STATUS_KUc;
    ((state_t*)TLB_NEWAREA)->status = ((state_t*)TLB_NEWAREA)->status & ~STATUS_IM_MASK;
    ((state_t*)TLB_NEWAREA)->status = ((state_t*)TLB_NEWAREA)->status & ~STATUS_VMc;
    ((state_t*)TLB_NEWAREA)->status = ((state_t*)TLB_NEWAREA)->status | STATUS_TE;
    ((state_t*)TLB_NEWAREA)->reg_sp= RAMTOP;
    ((state_t*)TLB_NEWAREA)->pc_epc= (memaddr) tlb_handler;
    
    ((state_t*)INTERRUPT_NEWAREA)->status = ((state_t*)INTERRUPT_NEWAREA)->status | STATUS_IEc;
    ((state_t*)INTERRUPT_NEWAREA)->status = ((state_t*)INTERRUPT_NEWAREA)->status & ~STATUS_KUc;
    ((state_t*)INTERRUPT_NEWAREA)->status = ((state_t*)INTERRUPT_NEWAREA)->status & ~STATUS_IM_MASK;
    ((state_t*)INTERRUPT_NEWAREA)->status = ((state_t*)INTERRUPT_NEWAREA)->status & ~STATUS_VMc;
    ((state_t*)INTERRUPT_NEWAREA)->status = ((state_t*)INTERRUPT_NEWAREA)->status | STATUS_TE;
    ((state_t*)INTERRUPT_NEWAREA)->reg_sp= RAMTOP;
    ((state_t*)INTERRUPT_NEWAREA)->pc_epc= (memaddr) interrupt_handler;
    
}

pcb_t* NEW_PCB(int i){
    pcb_t* tmp;
    tmp = allocPcb();
    tmp->p_s.status= tmp->p_s.status | STATUS_IEp;
    tmp->p_s.status= tmp->p_s.status | STATUS_TE;
    tmp->p_s.status= tmp->p_s.status & ~STATUS_KUp;
    tmp->p_s.status= tmp->p_s.status & ~STATUS_VMp;
    tmp->p_s.status= tmp->p_s.status & STATUS_IM(1);
    tmp->original_priority = i;
    tmp->priority = i;
    tmp->p_s.reg_sp = RAMTOP-FRAMESIZE * i;
    
    if(i==1)  tmp->p_s.pc_epc=(memaddr) test1;
    if(i==2)  tmp->p_s.pc_epc=(memaddr) test2;
    if(i==3)  tmp->p_s.pc_epc=(memaddr) test3;

    addokbuf("HO SETTATO IL PCB \n");
    return tmp;
}
