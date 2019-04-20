#ifndef HANDLER_H
#define HANDLER_H

#include "const.h"
#include "listx.h"
#include <umps/libumps.h>
#include <umps/types.h>
#include "pcb.h"

void interrupt_handler();
void systemcall_handler();
void tlb_handler();
void trap_handler();

#define TIME_SLICE 3000 

#endif
