/*  -- translated by f2c (version 19940927).
*/

double dlarnd_slu(int *idist, int *iseed)
{
    /* System generated locals */
    double ret_val;

    /* Builtin functions */
    double log(double), sqrt(double), cos(double);

    /* Local variables */
    static double t1, t2;
    extern double dlaran_slu(int *);
    extern int input_error(char *, int *);


/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    DLARND returns a random real number from a uniform or normal   
    distribution.   

    Arguments   
    =========   

    IDIST   (input) INTEGER   
            Specifies the distribution of the random numbers:   
            = 1:  uniform (0,1)   
            = 2:  uniform (-1,1)   
            = 3:  normal (0,1)   

    ISEED   (input/output) INTEGER array, dimension (4)   
            On entry, the seed of the random number generator; the array 
  
            elements must be between 0 and 4095, and ISEED(4) must be   
            odd.   
            On exit, the seed is updated.   

    Further Details   
    ===============   

    This routine calls the auxiliary routine DLARAN to generate a random 
  
    real number from a uniform (0,1) distribution. The Box-Muller method 
  
    is used to transform numbers from a uniform to a normal distribution. 
  

    ===================================================================== 
  


       Generate a real random number from a uniform (0,1) distribution   

       Parameter adjustments */
    --iseed;

    /* Function Body */
    t1 = dlaran_slu(&iseed[1]);

/*        uniform (0,1) */
    if (*idist == 1) {
	ret_val = t1;

/*        uniform (-1,1) */
    } else if (*idist == 2) {
	ret_val = t1 * 2. - 1.;

/*        normal (0,1) */
    } else if (*idist == 3) {
	t2 = dlaran_slu(&iseed[1]);
	ret_val = sqrt(log(t1) * -2.) * cos(t2 * 
		6.2831853071795864769252867663);
    }

/*        invalid input, *idist must be 1, 2, or 3  */
    else {
        int argument = 0;
        input_error("dlarnd", &argument);
        ret_val = 0;
    }

    return ret_val;

/*     End of DLARND */

} /* dlarnd_slu */

