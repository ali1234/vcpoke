#include <stdio.h>
#include <stdint.h>

#include "mailbox.h"


#define BUS_TO_PHYS(x) ((x)&~0xC0000000)

int mbox;
unsigned handle;
unsigned ptr;
uint8_t *program;


void setup() {
    mbox = mbox_open();
    handle = mem_alloc(mbox, 64, 8, 4);
    ptr = mem_lock(mbox, handle);
    program = mapmem(BUS_TO_PHYS(ptr), 64);

    // copy code

    program[0] = 0x00;
    program[1] = 0x08;
    program[2] = 0x5a;
    program[3] = 0x00;
}


void cleanup() {
    unmapmem(program, 64);
    mem_unlock(mbox, handle);
    mem_free(mbox, handle);
    mbox_close(mbox);
}


unsigned readmem(unsigned phys) {
    return execute_code(mbox, ptr, phys, 0, 0, 0, 0, 0);
}


int main(int argc, char *argv[]) {
    setup();

    printf("result = 0x%08x\n", readmem(0x7e207080));

    cleanup();

    return 0;
}
