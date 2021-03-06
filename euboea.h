
/* EUBOEA
 * Copyright (C) Kamila Palaiologos Szewczyk, 2019.
 * License: MIT
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _EUBOEA_H
#define _EUBOEA_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stddef.h>
#include <stdarg.h>

#include "codegen.h"

extern void * jit_buf;
extern size_t jit_sz;
extern int npc;
extern dasm_State * d;
extern dasm_State ** Dst;

enum { IN_GLOBAL = 0, IN_FUNC };
enum { BLOCK_LOOP = 1, BLOCK_FUNC };
enum { V_LOCAL, V_GLOBAL };
enum { T_INT, T_STRING, T_DOUBLE };

typedef struct {
    int address, args, espBgn;
    char name[0xFF];
} func_t;

typedef struct {
    char name[32];
    unsigned int id;
    int type;
    int loctype;
} var_t;

typedef struct {
    char val[128];
    int nline;
} token_t;

struct {
    token_t * tok_t;
    int size, pos;
} tok_t;

struct {
    unsigned int * addr;
    int count;
} brks_t, rets_t;

struct {
    uint32_t addr[0xff];
    int count;
} memory;

int error(char *, ...);
int lex(char *, int32_t);
int32_t skip(char *);
void asmexpr();
int isassign();
int assignment();
int expression(int, int);
int (*parser())(int *, void **);
char * getstr();
func_t * getfn(char *);
var_t * getvar(char *);
void cmpexpr();
int execute(char * , int32_t);
void add_mem(int32_t);
void freeadd();

extern unsigned int w;

#endif
