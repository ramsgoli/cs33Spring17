/* 
 * CS:APP Data Lab 
 * 
 * Ram Goli - 604751659
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    /* convert x to its negative absolute value and return the opposite of the first bit */
    int negVersion = ((x >> 31) & x) | (~x + 1);
    return (~(negVersion >> 31)) & 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
 /*Suppose each word of size w represents how many 1's are in that word
 * Start with assuming a word of size 1. Add adjacent words together, doubling 
 * the word size, so that each word now contains the new number of 1's in the word
 * Continue adding adjacent words together and doubling the word size so that the 
 * total number of 1's is computed by the time a word size of 16 is reached
 */
    int total = 0;
    int maskAmount = 85;
    maskAmount |= (maskAmount << 8);
    maskAmount |= (maskAmount << 16); 
    total = (x & maskAmount) + ((x >> 1) & maskAmount);
    maskAmount = 51;
    maskAmount |= (maskAmount << 8);
    maskAmount |= (maskAmount << 16); 
    total = (total & maskAmount) + ((total >> 2) & maskAmount);
    maskAmount =15;
    maskAmount |= (maskAmount << 8);
    maskAmount |= (maskAmount << 16); 
    total = (total & maskAmount) + ((total >> 4) & maskAmount);
    maskAmount = 255;
    maskAmount |= (maskAmount << 16);
    total = (total & maskAmount) + ((total >> 8) & maskAmount);
    maskAmount = 255;
    maskAmount |= (maskAmount << 8);
    total = (total & maskAmount) + ((total >> 16) & maskAmount);
    return total;
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
    /* Uses Demorgan's Law */
    return ~((~x) & (~y));
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
 /* Create a mask of 0's followed by n 1's. Apply this mask to x.
 * shift the new masked number by n to the power number of shifts so far,
 * and or the mask number with itself. Before applying the mask again though, check that
 * the shift amount is not more than the word size
*/
    int mask = ~((-1 << (n-1)) << 1);
    int returnNum = x & mask;
    returnNum = returnNum  | ((returnNum << n) & ((n/32)-1));
    returnNum = returnNum  | ((returnNum << (n*2)) & ((n*2/32)-1));
    returnNum = returnNum  | ((returnNum << (n*4)) & ((n*4/32)-1));
    returnNum = returnNum  | ((returnNum << (n*8)) & ((n*8/32)-1));
    returnNum = returnNum  | ((returnNum << (n*16)) & ((n*16/32)-1));
    return returnNum;
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) { 
/*
 * reassign x to it's one's complement if it's positive,
 * or keep it the same if it's negative.
 * check that n'th bit from the right of x is a 0. Otherwise it wouldn't be able to fit
 */
    x = ((x >> 31) & ~x) | (~(x >> 31) & x);
    return !(x >> (n+(~1+1)));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
/*
 * Shift x by n times 8 to the right
 * return the first 8 bits of the shifted vector
 */
    int shit = x >> (n << 3);
    return shit & 0xFF;
    
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
/*
 * Compare the msb of x and y
 * if msb_x is 1 and msb_y is 0, return 1
 * if msb_x is 0 and msb_y is 1, return 0
 * subtract x fom y by adding the two's complement of x to y
 * return the opposite of the sign of the difference
 */
    int msbX = x >> 0x1F;
    int msbY = y >> 0x1F;
    
    int isDifferent = (msbX ^ msbY);
    int diff = !((y + (~x + 1)) >> 31);
    //subtract
    return (isDifferent & !!msbX) | (~isDifferent & diff);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
/*
 * return the opposite of the msb of x, or 1 if x is zero
 */ 
    return !(x >> 31 | !x);
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
/*
 * shift x by n bits to the right
 * create a mask of n 1's followed by 0's
 * return x & mask
 */ 
    int new = x >> n;
    int shiftMask = ((~1+1) << (31+(~n+1)));
    shiftMask = ~(shiftMask << 1);
    return (new & shiftMask);
    
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
/*  INT_MIN is 1 followed by 31 0's so shift the 1 by 31 bits to the left
 */ 
    return 1 << 31;
}
