
/*
A.
x is stored in %rdi
n is stored in %esi
result is stored in %rax
mask is sored in %rdx

B.
result = 0
mask = 1

C.
mask cannot be equal to 0

D.
mask is arithmetically shifted left by the lower eight bits of n

E.
result = result | (x & mask)

*/
long loop(long x, long n) {
    long result = 0;
    long mask;
    for (mask = 1; mask  != 0; mask <<= n&0xFF) {
        result |= (x & mask);
    }
    return result;
}
