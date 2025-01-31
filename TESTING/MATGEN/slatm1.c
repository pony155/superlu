/*  -- translated by f2c (version 19940927).
*/

#include <stdlib.h>

/* Subroutine */ int slatm1_slu(int *mode, float *cond, int *irsign,
	int *idist, int *iseed, float *d, int *n, int *info)
{
    /* System generated locals */
    int i__1, i__2;
    double d__1, d__2;

    /* Builtin functions */
    double pow_dd(double *, double *), pow_ri(float *, int *), log(
	    double), exp(double);

    /* Local variables */
    static float temp;
    static int i;
    static float alpha;
    extern int input_error(char *, int *);
    extern double dlaran_sluslu(int *);
    extern /* Subroutine */ int slarnv_slu(int *, int *, int *, float
	    *);


/*  -- LAPACK auxiliary test routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

       SLATM1 computes the entries of D(1..N) as specified by   
       MODE, COND and IRSIGN. IDIST and ISEED determine the generation   
       of random numbers. SLATM1 is called by SLATMR to generate   
       random test matrices for LAPACK programs.   

    Arguments   
    =========   

    MODE   - INTEGER   
             On entry describes how D is to be computed:   
             MODE = 0 means do not change D.   
             MODE = 1 sets D(1)=1 and D(2:N)=1.0/COND   
             MODE = 2 sets D(1:N-1)=1 and D(N)=1.0/COND   
             MODE = 3 sets D(I)=COND**(-(I-1)/(N-1))   
             MODE = 4 sets D(i)=1 - (i-1)/(N-1)*(1 - 1/COND)   
             MODE = 5 sets D to random numbers in the range   
                      ( 1/COND , 1 ) such that their logarithms   
                      are uniformly distributed.   
             MODE = 6 set D to random numbers from same distribution   
                      as the rest of the matrix.   
             MODE < 0 has the same meaning as ABS(MODE), except that   
                the order of the elements of D is reversed.   
             Thus if MODE is positive, D has entries ranging from   
                1 to 1/COND, if negative, from 1/COND to 1,   
             Not modified.   

    COND   - REAL   
             On entry, used as described under MODE above.   
             If used, it must be >= 1. Not modified.   

    IRSIGN - INTEGER   
             On entry, if MODE neither -6, 0 nor 6, determines sign of   
             entries of D   
             0 => leave entries of D unchanged   
             1 => multiply each entry of D by 1 or -1 with probability .5 
  

    IDIST  - CHARACTER*1   
             On entry, IDIST specifies the type of distribution to be   
             used to generate a random matrix .   
             1 => UNIFORM( 0, 1 )   
             2 => UNIFORM( -1, 1 )   
             3 => NORMAL( 0, 1 )   
             Not modified.   

    ISEED  - INTEGER array, dimension ( 4 )   
             On entry ISEED specifies the seed of the random number   
             generator. The random number generator uses a   
             linear congruential sequence limited to small   
             integers, and so should produce machine independent   
             random numbers. The values of ISEED are changed on   
             exit, and can be used in the next call to SLATM1   
             to continue the same random number sequence.   
             Changed on exit.   

    D      - REAL array, dimension ( MIN( M , N ) )   
             Array to be computed according to MODE, COND and IRSIGN.   
             May be changed on exit if MODE is nonzero.   

    N      - INTEGER   
             Number of entries of D. Not modified.   

    INFO   - INTEGER   
              0  => normal termination   
             -1  => if MODE not in range -6 to 6   
             -2  => if MODE neither -6, 0 nor 6, and   
                    IRSIGN neither 0 nor 1   
             -3  => if MODE neither -6, 0 nor 6 and COND less than 1   
             -4  => if MODE equals 6 or -6 and IDIST not in range 1 to 3 
  
             -7  => if N negative   

    ===================================================================== 
  


       Decode and Test the input parameters. Initialize flags & seed.   

       Parameter adjustments */
    --d;
    --iseed;

    /* Function Body */
    *info = 0;

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

/*     Set INFO if an error */

    if (*mode < -6 || *mode > 6) {
	*info = -1;
    } else if (*mode != -6 && *mode != 0 && *mode != 6 && (*irsign != 0 && *
	    irsign != 1)) {
	*info = -2;
    } else if (*mode != -6 && *mode != 0 && *mode != 6 && *cond < 1.f) {
	*info = -3;
    } else if ((*mode == 6 || *mode == -6) && (*idist < 1 || *idist > 3)) {
	*info = -4;
    } else if (*n < 0) {
	*info = -7;
    }

    if (*info != 0) {
	i__1 = -(*info);
	input_error("SLATM1", &i__1);
	return 0;
    }

/*     Compute D according to COND and MODE */

    if (*mode != 0) {
	switch (abs(*mode)) {
	    case 1:  goto L10;
	    case 2:  goto L30;
	    case 3:  goto L50;
	    case 4:  goto L70;
	    case 5:  goto L90;
	    case 6:  goto L110;
	}

/*        One large D value: */

L10:
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
	    d[i] = 1.f / *cond;
/* L20: */
	}
	d[1] = 1.f;
	goto L120;

/*        One small D value: */

L30:
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
	    d[i] = 1.f;
/* L40: */
	}
	d[*n] = 1.f / *cond;
	goto L120;

/*        Exponentially distributed D values: */

L50:
	d[1] = 1.f;
	if (*n > 1) {
	    d__1 = (double) (*cond);
	    d__2 = (double) (-1.f / (float) (*n - 1));
	    alpha = pow_dd(&d__1, &d__2);
	    i__1 = *n;
	    for (i = 2; i <= i__1; ++i) {
		i__2 = i - 1;
		d[i] = pow_ri(&alpha, &i__2);
/* L60: */
	    }
	}
	goto L120;

/*        Arithmetically distributed D values: */

L70:
	d[1] = 1.f;
	if (*n > 1) {
	    temp = 1.f / *cond;
	    alpha = (1.f - temp) / (float) (*n - 1);
	    i__1 = *n;
	    for (i = 2; i <= i__1; ++i) {
		d[i] = (float) (*n - i) * alpha + temp;
/* L80: */
	    }
	}
	goto L120;

/*        Randomly distributed D values on ( 1/COND , 1): */

L90:
	alpha = log(1.f / *cond);
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
	    d[i] = exp(alpha * dlaran_sluslu(&iseed[1]));
/* L100: */
	}
	goto L120;

/*        Randomly distributed D values from IDIST */

L110:
	slarnv_slu(idist, &iseed[1], n, &d[1]);

L120:

/*        If MODE neither -6 nor 0 nor 6, and IRSIGN = 1, assign   
          random signs to D */

	if (*mode != -6 && *mode != 0 && *mode != 6 && *irsign == 1) {
	    i__1 = *n;
	    for (i = 1; i <= i__1; ++i) {
		temp = dlaran_sluslu(&iseed[1]);
		if (temp > .5f) {
		    d[i] = -(double)d[i];
		}
/* L130: */
	    }
	}

/*        Reverse if MODE < 0 */

	if (*mode < 0) {
	    i__1 = *n / 2;
	    for (i = 1; i <= i__1; ++i) {
		temp = d[i];
		d[i] = d[*n + 1 - i];
		d[*n + 1 - i] = temp;
/* L140: */
	    }
	}

    }

    return 0;

/*     End of SLATM1 */

} /* slatm1_slu */

