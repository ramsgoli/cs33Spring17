//
//  main.c
//  homework1
//
//  Created by Ram Goli on 4/7/17.
//  Copyright © 2017 Ram Goli. All rights reserved.
//

#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y) {
    
    int sum=x+y;
 
    int msbX = x >> ((sizeof(int) <<3) - 1);
    int msbY = y >> ((sizeof(int) <<3) - 1);
    int msbSum = sum >> ((sizeof(int) <<3) - 1) & 0x01;
    
    int didPositiveOverflow = (~(msbX ^ msbY) && ~msbSum) << ((sizeof(int) <<3) - 1) >> ((sizeof(int) <<3) - 1);
    int didNegativeOverflow = ((msbX ^ msbY) && ~msbSum) << ((sizeof(int) <<3) - 1) >> ((sizeof(int) <<3) - 1);
    
    return (didPositiveOverflow & INT_MAX) + (didNegativeOverflow & INT_MIN) + (((~didPositiveOverflow) & (~didNegativeOverflow)) & sum);
}

int main(int argc, const char * argv[]) {
    printf("%d\n", saturating_add(2000000000, 2000000000));
    
    int x = -500;
    
    
    
    printf("%d\n", ((x >> 2) << 2) <= x);
    printf("%d\n", ~5+~8+1 == ~(5+8));
    return 0;
}
