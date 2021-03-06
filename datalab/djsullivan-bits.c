// Danny Sullivan - djsullivan

/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
	int x, shift8;
	x=0xaa; //make 8bit int
	shift8=x|x<<8; //switch bit not set to 1
	return shift8|shift8<<16;//return final num
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
	return !(x+x)&!!(x);//return true if minimum value, 0 if any other case
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return (~(~x&~y)&~(x&y));//De Morgan's law, XOR
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	int a, b;
	a=!!x;//reverse logical state twice of x
	b=(~a)+1;//invert bits of a, add 1
  	return (b&y)|(~b&z);//return if case exists for both b and or if the inverted b and z is true
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
	int y;
	y=x|(x>>1);//set y to the compared x and x shifted right 1
	y=y|y>>1;//if not equal, shift 1 bit right
	y=y|y>>2;//if not equal, shift 2 bit right
	y=y|y>>4;//if not equal, shift 4 bit right
	y=y|y>>8;//if not equal, shift 8 bit right
	y=y|y>>16;//if not equal, shift 16 bit right
	
  	return ((y^(y>>1))|(0x80<<24))&y;//set all bits to right to 1, set other bits and compare to y
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	int mask, round, div, zeroMask;
	mask=(x>>31);//if neg, all 1's, if pos, all 0's
	round=((0x01<<n)+(~0x00))&mask;//round towards 0
	div=((x+round)>>n);//adjust round to zero if x >= 0
	zeroMask=(~(!n)<<31)>>31;//covers negative round to zero
	return (div&zeroMask)|(x&(~zeroMask));//case for 0 and not 0
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  return !(x>>31);//shift bits to right see leading value
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
	int Tmin, Tmax, mul2, overflow, sat;
	Tmin=0x1<<31;//set Tmin
	Tmax=x>>31;//set Tmax
	mul2 = x+x;//2*x
	overflow=(x^mul2)>>31;//check overflow
	sat=overflow&(Tmax^~Tmin);//saturate to Tmin or Tmax in case of overflow
 	return (sat|(~overflow&mul2));//cases for legal value or overflow
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
	int case1,case2,checkSign;
	case1=x&(~y);//x<0 & y>=0
	checkSign=x+(~y+1);//check signs
	case2=(~(x^y))&checkSign;//signs are same
  	return (case1|case2)>>31&1;//covers both cases
}
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
	int checkSign, up, upX, low, lowX;
	checkSign=1<<31;//check sign
	up=~(checkSign|0x39);//go neg if 0x39 added
	upX=(up+x)>>31;//check sign after add x
	up=checkSign&(upX);//update up
	low=(~0x30);//go neg if 0x30 added
	lowX=(low+1+x)>>31;//check sign after add x
	low=checkSign&(lowX);//update low
 	return !(up|low);//return if positive
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
	int three, shiftX1, shiftX2, frac;
	three=x&0x3;//number 3
	shiftX2=x>>2;//shift x value right 2
	shiftX1=shiftX2<<1;//shift x value left 1
	frac=((three+three+three+((shiftX2>>0x1F)&0x3))>>2);//create fraction
	return shiftX1+shiftX2+frac;//add shifts and fraciton
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int a = 0;
	int b=0;
	int c=0;
	int d=0;
	int e=0;
	x=x|(x>>1);//most sig bit to least sig bit
	x=x|(x>>2);//most sig bit to least sig bit
	x=x|(x>>4);//most sig bit to least sig bit
	x=x|(x>>8);//most sig bit to least sig bit
	x=x|(x>>16);//most sig bit to least sig bit
	
	//set masks, compare & adjust bits
	a=0x55|(0x55<<8);
	a=a|(a<<16);
	b=0x33|(0x33<<8);
	b=b|(b<<16);
	c=0x0f|(0x0f<<8);
	c=c|(c<<16);
	d=0xff|(0xff<<16);
	e=0xff|(0xff<<8);

	//apply masks
	x=(x&a)+((x>>1)&a);
	x=(x&b)+((x>>2)&b);
	x=(x&c)+((x>>4)&c);
	x=(x&d)+((x>>8)&d);
	x=(x&e)+((x>>16)&e);

	x=x+(~0);

	return x;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	int shift = ((uf>>23) & 0xFF);//shift float right
	int frac = (uf&((1<<23)+~0));//float to fraction value
	if(shift==0xFF&&frac){//return if all 1's
		return uf;
	}
	else{
 		return uf=(uf^(1u<<31));//flip bits
	}
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	unsigned xNeg, countShift, bit32, bit32shift, exp, bitGuard, final;
	int Tmin, temp, round;
	Tmin=0x80000000;//set Tmin
	countShift = 0;//shift counter
	if(x<0){//if x is neg
		xNeg=Tmin;//set xNeg to minimum val
	}
	else{
		xNeg=0;
	}
	if(!x){//if not x
		return 0;
	}
	if(xNeg){
		x=-x;//set xNeg to -x
	}
	while(!((Tmin)&(x))){//shift Tmin and x while not equal
		x=x<<1;//shift left 1 bit
		countShift++;//increment countShift
	}
	bit32=x<<1;//shift left 1 bit
	exp=158-countShift;//determine exponent
	bitGuard=(bit32&(0x200))>>9;//set guard
	round=bit32&0x000001ff;//round to nearest num
	bit32shift=bit32>>9;//shift right 9 bits
	final=(xNeg+(exp<<23)+bit32shift);//determine final unsigned float
	if(round>0x00000100||((round==0x00000100)&&bitGuard)){//find rounding for final value
		temp=((exp<<23)+bit32shift);
		return xNeg+(1+temp);
	}
  	return final;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	unsigned exp, getSign, denormFrac;
	exp=((uf>>23)&0xFF);//get exponent
	getSign=(uf&0x80000000);//determine sign
	denormFrac=(uf&0x007FFFFF);//denormalize fraction
	
	if(exp==255||(exp==0&&denormFrac==0)){//if number is invalid, return
		return uf;
	}
	if(exp){//if valid, increment exponent
		exp=exp+1;
	}else if(denormFrac==0x007FFFFF){//subtract 1 from denormalized fraction, increment exponent
		denormFrac=denormFrac-1;
		exp=exp+1;
	}else{//shift bits left
		denormFrac<<=1;
	}
	return getSign|exp<<23|denormFrac;
}
