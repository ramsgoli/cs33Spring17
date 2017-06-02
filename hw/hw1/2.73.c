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
