/*  -- translated by f2c (version 19940927).
*/

#include "../../SRC/slu_scomplex.h"

/* Complex */ void clarnd_slu(complex * ret_val, int *idist, int *iseed)
{
    /* System generated locals */
    double d__1, d__2;
    complex q__1, q__2, q__3;

    /* Builtin functions */
    double log(double), sqrt(double);
    void c_exp(complex *, complex *);

    /* Local variables */
    static float t1, t2;
    extern double dlaran_sluslu(int *);
    extern int input_error(char *, int *);


/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    CLARND returns a random complex number from a uniform or normal   
    distribution.   

    Arguments   
    =========   

    IDIST   (input) INTEGER   
            Specifies the distribution of the random numbers:   
            = 1:  real and imaginary parts each uniform (0,1)   
            = 2:  real and imaginary parts each uniform (-1,1)   
            = 3:  real and imaginary parts each normal (0,1)   
            = 4:  uniformly distributed on the disc abs(z) <= 1   
            = 5:  uniformly distributed on the circle abs(z) = 1   

    ISEED   (input/output) INTEGER array, dimension (4)   
            On entry, the seed of the random number generator; the array 
  
            elements must be between 0 and 4095, and ISEED(4) must be   
            odd.   
            On exit, the seed is updated.   

    Further Details   
    ===============   

    This routine calls the auxiliary routine SLARAN to generate a random 
  
    real number from a uniform (0,1) distribution. The Box-Muller method 
  
    is used to transform numbers from a uniform to a normal distribution. 
  

    ===================================================================== 
  


       Generate a pair of real random numbers from a uniform (0,1)   
       distribution   

       Parameter adjustments */
    --iseed;

    /* Function Body */
    t1 = dlaran_sluslu(&iseed[1]);
    t2 = dlaran_sluslu(&iseed[1]);

/*        real and imaginary parts each uniform (0,1) */
    if (*idist == 1) {
	q__1.r = t1, q__1.i = t2;
	 ret_val->r = q__1.r,  ret_val->i = q__1.i;

/*        real and imaginary parts each uniform (-1,1) */
    } else if (*idist == 2) {
	d__1 = t1 * 2.f - 1.f;
	d__2 = t2 * 2.f - 1.f;
	q__1.r = d__1, q__1.i = d__2;
	 ret_val->r = q__1.r,  ret_val->i = q__1.i;

/*        real and imaginary parts each normal (0,1) */
    } else if (*idist == 3) {
	d__1 = sqrt(log(t1) * -2.f);
	d__2 = t2 * 6.2831853071795864769252867663f;
	q__3.r = 0.f, q__3.i = d__2;
	c_exp(&q__2, &q__3);
	q__1.r = d__1 * q__2.r, q__1.i = d__1 * q__2.i;
	 ret_val->r = q__1.r,  ret_val->i = q__1.i;

/*        uniform distribution on the unit disc abs(z) <= 1 */
    } else if (*idist == 4) {
	d__1 = sqrt(t1);
	d__2 = t2 * 6.2831853071795864769252867663f;
	q__3.r = 0.f, q__3.i = d__2;
	c_exp(&q__2, &q__3);
	q__1.r = d__1 * q__2.r, q__1.i = d__1 * q__2.i;
	 ret_val->r = q__1.r,  ret_val->i = q__1.i;

/*        uniform distribution on the unit circle abs(z) = 1 */
    } else if (*idist == 5) {
	d__1 = t2 * 6.2831853071795864769252867663f;
	q__2.r = 0.f, q__2.i = d__1;
	c_exp(&q__1, &q__2);
	 ret_val->r = q__1.r,  ret_val->i = q__1.i;
    }

/*        invalid input, *idist must be 1, 2, 3, 4, or 5  */
    else {
        int argument = 0;
        input_error("clarnd", &argument);
        ret_val = 0;
    }

/*     End of CLARND */

} /* clarnd_slu */

