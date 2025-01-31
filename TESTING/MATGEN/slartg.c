#include <math.h>
#include <stdbool.h>

/* Subroutine */ int slartg_slu(float *f, float *g, float *cs, float *sn, float *r)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    SLARTG generate a plane rotation so that   

       [  CS  SN  ]  .  [ F ]  =  [ R ]   where CS**2 + SN**2 = 1.   
       [ -SN  CS  ]     [ G ]     [ 0 ]   

    This is a slower, more accurate version of the BLAS1 routine SROTG,   
    with the following other differences:   
       F and G are unchanged on return.   
       If G=0, then CS=1 and SN=0.   
       If F=0 and (G .ne. 0), then CS=0 and SN=1 without doing any   
          floating point operations (saves work in SBDSQR when   
          there are zeros on the diagonal).   

    If F exceeds G in magnitude, CS will be positive.   

    Arguments   
    =========   

    F       (input) REAL   
            The first component of vector to be rotated.   

    G       (input) REAL   
            The second component of vector to be rotated.   

    CS      (output) REAL   
            The cosine of the rotation.   

    SN      (output) REAL   
            The sine of the rotation.   

    R       (output) REAL   
            The nonzero component of the rotated vector.   

    ===================================================================== 
*/
    /* Initialized data */
    static bool first = true;
    /* System generated locals */
    int i__1;
    float r__1, r__2;
    /* Builtin functions */
    double log(double), pow_ri(float *, int *), sqrt(double);
    /* Local variables */
    static int i;
    static float scale;
    static int count;
    static float f1, g1, safmn2, safmx2;
    extern float smach(char *);
    static float safmin, eps;


    if (first) {
	first = false;
	safmin = smach("S");
	eps = smach("E");
	r__1 = smach("B");
	i__1 = (int) (log(safmin / eps) / log(smach("B")) / 2.f);
	safmn2 = pow_ri(&r__1, &i__1);
	safmx2 = 1.f / safmn2;
    }
    if (*g == 0.f) {
	*cs = 1.f;
	*sn = 0.f;
	*r = *f;
    } else if (*f == 0.f) {
	*cs = 0.f;
	*sn = 1.f;
	*r = *g;
    } else {
	f1 = *f;
	g1 = *g;
/* Computing MAX */
	r__1 = fabs(f1), r__2 = fabs(g1);
	scale = fmax(r__1,r__2);
	if (scale >= safmx2) {
	    count = 0;
L10:
	    ++count;
	    f1 *= safmn2;
	    g1 *= safmn2;
/* Computing MAX */
	    r__1 = fabs(f1), r__2 = fabs(g1);
	    scale = fmax(r__1,r__2);
	    if (scale >= safmx2) {
		goto L10;
	    }
/* Computing 2nd power */
	    r__1 = f1;
/* Computing 2nd power */
	    r__2 = g1;
	    *r = sqrt(r__1 * r__1 + r__2 * r__2);
	    *cs = f1 / *r;
	    *sn = g1 / *r;
	    i__1 = count;
	    for (i = 1; i <= count; ++i) {
		*r *= safmx2;
/* L20: */
	    }
	} else if (scale <= safmn2) {
	    count = 0;
L30:
	    ++count;
	    f1 *= safmx2;
	    g1 *= safmx2;
/* Computing MAX */
	    r__1 = fabs(f1), r__2 = fabs(g1);
	    scale = fmax(r__1,r__2);
	    if (scale <= safmn2) {
		goto L30;
	    }
/* Computing 2nd power */
	    r__1 = f1;
/* Computing 2nd power */
	    r__2 = g1;
	    *r = sqrt(r__1 * r__1 + r__2 * r__2);
	    *cs = f1 / *r;
	    *sn = g1 / *r;
	    i__1 = count;
	    for (i = 1; i <= count; ++i) {
		*r *= safmn2;
/* L40: */
	    }
	} else {
/* Computing 2nd power */
	    r__1 = f1;
/* Computing 2nd power */
	    r__2 = g1;
	    *r = sqrt(r__1 * r__1 + r__2 * r__2);
	    *cs = f1 / *r;
	    *sn = g1 / *r;
	}
	if (fabs(*f) > fabs(*g) && *cs < 0.f) {
	    *cs = -(double)(*cs);
	    *sn = -(double)(*sn);
	    *r = -(double)(*r);
	}
    }
    return 0;

/*     End of SLARTG */

} /* slartg_slu */

