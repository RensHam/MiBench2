#include <stdio.h>
#include "snipmath.h"
#include <math.h>
#include "pulpino.h"
#include "int.h"
#include "timer.h"
#include "event.h"

//#include "../bareBench.h"

/* The printf's may be removed to isolate just the math calculations */

int main(void)
{
   ECP = 0xFFFFFFFF;
   IER = 1 << 29;
   int_enable();


   TPRA = 0x0;
   TIRA = 0x0;
   TOCRA = 1200000; 
   TPRA = 0x1;

  double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
  double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
  double  a3 = 1.0, b3 = -3.5, c3 = 22.0, d3 = -31.0;
  double  a4 = 1.0, b4 = -13.7, c4 = 1.0, d4 = -35.0;
  double  x[3];
  double X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  struct int_sqrt q;

  /* solve soem cubic functions */
  printf("********* CUBIC FUNCTIONS ***********\n\r");
  /* should get 3 solutions: 2, 6 & 2.5   */
  SolveCubic(a1, b1, c1, d1, &solutions, x);  
  printf("Solutions:");
  for(i=0;i<solutions;i++)
    printf(" %f",x[i]);
  printf("\n\r");
  /* should get 1 solution: 2.5           */
  SolveCubic(a2, b2, c2, d2, &solutions, x);  
  printf("Solutions:");
  for(i=0;i<solutions;i++)
    printf(" %f",x[i]);
  printf("\n\r");
  SolveCubic(a3, b3, c3, d3, &solutions, x);
  printf("Solutions:");
  for(i=0;i<solutions;i++)
    printf(" %f",x[i]);
  printf("\n\r");
  SolveCubic(a4, b4, c4, d4, &solutions, x);
  printf("Solutions:");
  for(i=0;i<solutions;i++)
    printf(" %f",x[i]);
  printf("\n\r");
  /* Now solve some random equations */
  for(a1=1;a1<10;a1++) {
    for(b1=10;b1>0;b1--) {
      for(c1=5;c1<15;c1+=0.5) {
	for(d1=-1;d1>-11;d1--) {
	  SolveCubic(a1, b1, c1, d1, &solutions, x);  
	  printf("Solutions:");
	  for(i=0;i<solutions;i++)
	    printf(" %f",x[i]);
	  printf("\n\r");
          d1-=2;
	}
        c1+=2;
      }
      b1-=2;
    }
    a1+=2;
  }
  
  printf("********* INTEGER SQR ROOTS ***********\n\r");
  /* perform some integer square roots */
  for (i = 0; i < 101; ++i)
    {
      usqrt(i, &q);
			// remainder differs on some machines
     // printf("sqrt(%3d) = %2d, remainder = %2d\n\r",
     printf("sqrt(%3d) = %2d\n\r",
	     i, q.sqrt);
    }
  usqrt(l, &q);
  //printf("\n\rsqrt(%lX) = %X, remainder = %X\n\r", l, q.sqrt, q.frac);
  printf("\n\rsqrt(%lX) = %X\n\r", l, q.sqrt);


  printf("********* ANGLE CONVERSION ***********\n\r");
  /* convert some rads to degrees */
  for (X = 0.0; X <= 360.0; X += 1.0)
    printf("%3.0f degrees = %.12f radians\n\r", X, deg2rad(X));
  printf("\n\r");
  for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 180))
    printf("%.12f radians = %3.0f degrees\n\r", X, rad2deg(X));
  
   // disable timer
   TPRA = 0x0;
   ECP = 0x1;
   int_disable();
for(int runs = 0; runs < 176; runs++) //526
ISR_TA_CMP();
  return 0;
}

void __attribute__((optimize("O0"))) ISR_TA_CMP(void) { 
 ICP = (1 << 29); 
static int i = 1048572; 
for (int x = 0; x < 32; x++) {
i += 4; 
 asm volatile ( 
 "mv	x5, %0\n" // should be x5 = i; 
"lw	x6, 0(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 0(x5)\n" // * i = a;
"lw	x6, 4(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 4(x5)\n" // * i = a;
"lw	x6, 8(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 8(x5)\n" // * i = a;
"lw	x6, 12(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 12(x5)\n" // * i = a;
"lw	x6, 16(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 16(x5)\n" // * i = a;
"lw	x6, 20(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 20(x5)\n" // * i = a;
"lw	x6, 24(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 24(x5)\n" // * i = a;
"lw	x6, 28(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 28(x5)\n" // * i = a;
"lw	x6, 32(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 32(x5)\n" // * i = a;
"lw	x6, 36(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 36(x5)\n" // * i = a;
"lw	x6, 40(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 40(x5)\n" // * i = a;
"lw	x6, 44(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 44(x5)\n" // * i = a;
"lw	x6, 48(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 48(x5)\n" // * i = a;
"lw	x6, 52(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 52(x5)\n" // * i = a;
"lw	x6, 56(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 56(x5)\n" // * i = a;
"lw	x6, 60(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 60(x5)\n" // * i = a;
"lw	x6, 64(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 64(x5)\n" // * i = a;
"lw	x6, 68(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 68(x5)\n" // * i = a;
"lw	x6, 72(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 72(x5)\n" // * i = a;
"lw	x6, 76(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 76(x5)\n" // * i = a;
"lw	x6, 80(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 80(x5)\n" // * i = a;
"lw	x6, 84(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 84(x5)\n" // * i = a;
"lw	x6, 88(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 88(x5)\n" // * i = a;
"lw	x6, 92(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 92(x5)\n" // * i = a;
"lw	x6, 96(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 96(x5)\n" // * i = a;
"lw	x6, 100(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 100(x5)\n" // * i = a;
"lw	x6, 104(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 104(x5)\n" // * i = a;
"lw	x6, 108(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 108(x5)\n" // * i = a;
"lw	x6, 112(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 112(x5)\n" // * i = a;
"lw	x6, 116(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 116(x5)\n" // * i = a;
"lw	x6, 120(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 120(x5)\n" // * i = a;
"lw	x6, 124(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 124(x5)\n" // * i = a;
"lw	x6, 0(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 0(x5)\n" // * i = a;
"lw	x6, 4(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 4(x5)\n" // * i = a;
"lw	x6, 8(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 8(x5)\n" // * i = a;
"lw	x6, 12(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 12(x5)\n" // * i = a;
"lw	x6, 16(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 16(x5)\n" // * i = a;
"lw	x6, 20(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 20(x5)\n" // * i = a;
"lw	x6, 24(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 24(x5)\n" // * i = a;
"lw	x6, 28(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 28(x5)\n" // * i = a;
"lw	x6, 32(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 32(x5)\n" // * i = a;
"lw	x6, 36(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 36(x5)\n" // * i = a;
"lw	x6, 40(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 40(x5)\n" // * i = a;
"lw	x6, 44(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 44(x5)\n" // * i = a;
"lw	x6, 48(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 48(x5)\n" // * i = a;
"lw	x6, 52(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 52(x5)\n" // * i = a;
"lw	x6, 56(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 56(x5)\n" // * i = a;
"lw	x6, 60(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 60(x5)\n" // * i = a;
"lw	x6, 64(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 64(x5)\n" // * i = a;
"lw	x6, 68(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 68(x5)\n" // * i = a;
"lw	x6, 72(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 72(x5)\n" // * i = a;
"lw	x6, 76(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 76(x5)\n" // * i = a;
"lw	x6, 80(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 80(x5)\n" // * i = a;
"lw	x6, 84(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 84(x5)\n" // * i = a;
"lw	x6, 88(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 88(x5)\n" // * i = a;
"lw	x6, 92(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 92(x5)\n" // * i = a;
"lw	x6, 96(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 96(x5)\n" // * i = a;
"lw	x6, 100(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 100(x5)\n" // * i = a;
"lw	x6, 104(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 104(x5)\n" // * i = a;
"lw	x6, 108(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 108(x5)\n" // * i = a;
"lw	x6, 112(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 112(x5)\n" // * i = a;
"lw	x6, 116(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 116(x5)\n" // * i = a;
"lw	x6, 120(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 120(x5)\n" // * i = a;
"lw	x6, 124(x5)\n" // Load i a = *i;
"not	x6, x6\n" // a = ~a;
"sw	x6, 124(x5)\n" // * i = a;
:"=r"(i) : : "x5", "x6", "x7");
i += 124; 
}
if (i > 1073151) { i = 1048572;} //Flip arround memory should not be 2047 because of +4 at beginning 
TIRA = 0x0;
}
