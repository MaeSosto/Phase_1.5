#ifndef P15TEST_RIKAYA_V0_H
#define P15TEST_RIKAYA_V0_H

#define RAMBASE *((unsigned int *)0x10000000)
#define RAMSIZE *((unsigned int *)0x10000004)
#define RAMTOP (RAMBASE + RAMSIZE)

    void addokbuf(char *strp);
    void adderrbuf(char *strp);
    void log_process_order(int process);
    void test1();
    void test2();
    void test3();

    
#endif