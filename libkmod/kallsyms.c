#include "kallsyms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symbol *symbols;
size_t count;
    
void load_kallsyms(const char *filename) {
    char line[512];
    size_t capacity = 1024;
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    symbols = (Symbol *)malloc(capacity * sizeof(Symbol));
    count = 0;

    while (fgets(line, sizeof(line), file)) {
        Symbol *sym;
        if (count >= capacity) {
            capacity *= 2;
            symbols = (Symbol *)realloc(symbols, capacity * sizeof(Symbol));
        }

        sym = &symbols[count];
        if (sscanf(line, "%lx %c %s", &sym->address, &sym->type, sym->name) == 3) {
            count++;
        }
    }

    fclose(file);
}

const Symbol* find_symbol_by_name(const char *name) {
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(symbols[i].name, name) == 0) {
            return &symbols[i];
        }
    }
    return NULL;
}

