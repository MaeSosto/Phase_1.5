#ifndef UTILS_H
#define UTILS_H

#include "types_rikaya.h"
#include "const.h"
#include "listx.h"

pcb_t* getPROC();
void setPROC(pcb_t* proc);
struct list_head* getCODA();
void setCODA(struct list_head* coda);

void setAreas();
pcb_t* NEW_PCB(int i);

#endif
