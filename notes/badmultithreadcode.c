#include <stdio.h>

int cnt;

int main() {
    for (int i = 0; i < n; i++) //n is unique per thread
        cnt++; //global counter

}

/*
 * one thread could have n = 3,
 * another thread could have n = 6
 * but a compiler would just optimize it to say something like
 * addl n, cnt
 * How do we prevent compiler from doing this?
 * int volatile cnt;
 * machine code has to access RAM in the same pattern that the source code does
 * every load from a volatile variable should require a move. 
 * compiler has to loop away
 * movl $cnt %eax
 * addl $1, %eax
 * movl %eax, cnt
