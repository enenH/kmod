#ifndef KALLSYMS_H
#define KALLSYMS_H

#include <stdint.h>

typedef struct {
    uint64_t address;
    char type;
    char name[256];
} Symbol;

void load_kallsyms(const char *filename);
const Symbol* find_symbol_by_name(const char *name);

#endif // KALLSYMS_H
