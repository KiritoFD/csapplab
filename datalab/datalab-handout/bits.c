

#if 0


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {//单独，每一位上，异或就是不同
  //不同，就是x取反=y，或者y取反=x
  //也就是 x & ~y 和 ~x & y都是0
  //所以异或就是这两者的或
  //德摩根定律： ~(x & y) = ~x | ~y
  //（x & ~y） | (~x & y) = ~(~(x & ~y) & ~(~x & y))
  // ~(~(x & ~y) & ~(~x & y));
  int a = ~x & y; // bits in y but not in x
  int b = x & ~y; // bits in x but not in y
  return ~(~a & ~b); // bits in either a or b, but not both
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int x = 1; //二进制的0000 0000 0000 0000 0000 0000 0000 0001
  //最小的二进制数就是最高位为1，其余为0
  //也就是最高位为1，其余为0
  //所以左移31位就是最高位为1，其余为0
  //也就是二进制的1000 0000 0000 0000
  return x << 31; //最小的二进制数就是最高位为1，其余为0

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int tag = x + 1; //如果x是最大值，那么x+1就是最小值
  int tmp1 = ~(x + tag); //Tmax+Tmin = -1
  int flag1 = !tmp1; //如果x是最大值，那么tmp1就是0
  int flag2 = !tag;
  return flag1 & !flag2;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int t = 0xAAAAAAAA; //二进制的1010 1010 1010 1010 1010 1010 1010 1010
  //如果x的奇数位都是1，那么x & t = t
  //也就是x & t == t
  //如果x的奇数位不是1，那么x & t != t
  //也就是x & t != t
  int a = x & t; //取出x的奇数位
  int b = a>>1; //右移一位，变成偶数位
  int c = a|b; //将偶数位和奇数位进行或运算
  return !(c+1); //如果c+1是0，那么c的奇数位都是1,也就是任何一位上，a,b至少有一位是0，也就是X的奇数位不是1
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  //补码：取反加一
  return ~x + 1; //取反加一就是负数
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int flag1 = !((x & 0xa) ^ 0xa);//x & 0xa == 0xa
  //也就是第一位和第三位都是1，大于10
  int flag2 = !((x & 0xc) ^ 0xc);
  //第二位和第三位都是1，大于12
  int flg3 = ((x>>4)^3) ; //如果x的高四位是0011，也就是3
  return !(flag1 | flag2 | flg3); //如果x的高四位是0011，也就是3
  //也就是x的高四位是0011，或者x的第一位和第三位都是1，或者x的第二位和第三位都是1
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int neg = ~0;//-1
  int mask = !!x + neg;//如果x为0，那么mask为-1，如果x不为0，那么mask为0
  return (y & ~mask) | (z & mask);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //符号位
  int s1 = x >> 31;
  int s2 = y >> 31;
  //s1 == s2 ? 1 : 0
  int mask = !(s1 ^ s2);
  int diff = y + (~x) +1;
  int flag2 = !(diff >> 31); //如果diff的符号位是0，那么x <= y
  //如果符号位相同，那么就比较差值的符号位
  //如果符号位不同，那么就比较符号位
  return (mask & flag2) | (!mask & (s1&1));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  //判断是不是0
  int tag = x | (~x + 1); //如果x是0，那么tag就是0;x和-x，只有0会得到-1
  //如果x是最小值，那么tag就是1
  int s = tag >> 31; //如果x是0，那么s就是0，如果x是最小值，那么s就是1

  return s+1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int mask, y, tag16, tag8, tag4, tag2, tag1, has16bit, has8bit, has4bit, has2bit, has1bit;
  mask = x >> 31; //符号位
  y = mask &(~x) | (~mask & x); //如果x是负数，那么y就是-x，如果x是正数，那么y就是x
  return 0;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
