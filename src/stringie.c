/*
 * stringie.c -- a brain-freezingly pedantic implementation of Underload in C
 * (with all the limitations that that implies)
 * Chris Pressey, September 2010
 * August 2017: bug fix to avoid memory overrun in (). Thanks to @stasoid for finding and suggesting fix.
 * Summer 2018: own implementation of strdup to avoid warnings; ability to read from file; AUTOFLUSH; 1.0.
 * This work is in the public domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    char *string;
    struct stack *next;
} *root;

void run(char *);

char *strdupe(const char *s)
{
    char *t = malloc(strlen(s) + 1);
    strcpy(t, s);
    return t;
}

char *pop(void)
{
    char *r;
    struct stack *old;
    r = root->string;
    old = root;
    root = root->next;
    free(old);
    return r;
}

void push(char *string)
{
    struct stack *s;
    s = malloc(sizeof(struct stack));
    s->next = root;
    s->string = string;
    root = s;
}

void dup(void)
{
    char *e, *f;
    e = pop();
    f = strdupe(e);
    push(e);
    push(f);
}

void swap(void)
{
    char *e, *f;
    e = pop();
    f = pop();
    push(e);
    push(f);
}

void eval(void)
{
    char *e;
    e = pop();
    run(e);
}

void concat(void)
{
    char *e, *f, *g;
    e = pop();
    f = pop();
    g = malloc(strlen(e) + strlen(f) + 1);
    strcpy(g, f);
    strcat(g, e);
    push(g);
    free(f);
    free(e);
}

void enclose(void)
{
    char *e, *g;
    e = pop();
    g = malloc(strlen(e) + 3);
    sprintf(g, "(%s)", e);
    push(g);
    free(e);
}

void output(void)
{
    char *e;
    e = pop();
    printf("%s", e);
#ifdef AUTOFLUSH
    fflush(stdout);
#endif
    free(e);
}

void dumpstack(void)
{
    struct stack *s;
    
    fprintf(stderr, "STACK: ");
    for (s = root; s != NULL; s = s->next)
    {
        fprintf(stderr, "(%s)", s->string);
    }
    fprintf(stderr, "!\n");
}

void run(char *program)
{
    int i = 0;
    int last_pos = strlen(program) - 1;
    for (i = 0; program[i] != '\0'; i++) {
        switch (program[i]) {
            case ':': dup(); break;
            case '!': pop(); break;
            case '^':
              {
                /* tail recursion */
                if (i == last_pos) {
                    i = -1;
                    free(program);
                    program = pop();
                    continue;
                } else {
                    eval();
                }
              }
              break;
            case '~': swap(); break;
            case '*': concat(); break;
            case 'S': output(); break;
            case 'a': enclose(); break;
            case '(':
              {
                int level = 0;
                int j = 0;
                int size = 256;
                char *t = malloc(size);

                i++;
                level++;
                while (level > 0) {
                    if (program[i] == '(')
                        level++;
                    else if (program[i] == ')')
                        level--;
                    if (level > 0) {
                        t[j] = program[i];
                        j++;
                        if (j >= size) {
                            size *= 2;
                            t = realloc(t, size);
                        }
                    }
                    i++;
                }
                i--;
                t[j] = '\0';
                push(t);
              }
              break;
        }
        /*dumpstack();*/
    }
    free(program);
}

char *readfile(FILE *f)
{
    char chunk[256];
    char *buffer;
    int size = 256;
    int len = 0;
    int n;

    buffer = malloc(size);

    n = fread(chunk, 1, 256, f);
    while (n > 0) {
        if (len + n > size) {
            size *= 2;
            buffer = realloc(buffer, size);
        }
        memcpy(buffer + len, chunk, n);
        len += n;
        n = fread(chunk, 256, 1, f);
    }

    /* NUL-terminate the buffer; but first, make sure the NUL can fit! */
    if (len + 1 > size) {
        size *= 2;
        buffer = realloc(buffer, size);
    }
    buffer[len + 1] = '\0';

    return buffer;
}

int main(int argc, char **argv)
{
    char *program;
    FILE *f;

    if (argc >= 1) {
        if (!strcmp(argv[1], "from") && argc >= 2) {
            if ((f = fopen(argv[2], "r")) == NULL) {
                exit(1);
            }
            program = readfile(f);
            fclose(f);
        } else {
            program = strdupe(argv[1]);
        }
    }
    root = NULL;
    run(program);
    exit(0);
}
