/*
 * Copyright 2004, 2005 PathScale, Inc.  All Rights Reserved.
 */

/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan

*/

struct quad {
double hi;
double lo;
};
typedef struct quad quad;

#define	DMANTWIDTH	52
#define	DBL2LL(x, l)	l = *(long long *)&x
#define	LL2DBL(l, x)	x = *(double *)&l

typedef union
{
	struct
	{
		unsigned int hi;
		unsigned int lo;
	} word;

	double	d;
} du;


static const	du	infinity =
{0x7ff00000,	0x00000000};

static const	du	twop63 =
{0x43e00000,	0x00000000};

static const	du	m_twop63 =
{0xc3e00000,	0x00000000};

static const	du	twop62 =
{0x43d00000,	0x00000000};

static const du		twop52 =
{0x43300000,	0x00000000};

static const du		twop914 =
{0x79100000,	0x00000000};

static const du		inf =
{0x7ff00000,	0x00000000};


quad __qnint(quad u);
quad __q_add(quad x, quad y);
quad __q_sub(quad x, quad y);
quad __qint(quad u);
long long __ki_qint(quad x );
quad __c_q_trunc(quad x );
int __q_ge(quad x, quad y);
int __q_le(quad x, quad y);
double __trunc( double arg );


quad
__q_max1( quad u, quad v )
{
quad	result;

	if ( u.hi != u.hi )
	{
		result.hi = u.hi;
		result.lo = u.lo;

		return ( result );
	}

	if ( v.hi != v.hi )
	{
		result.hi = v.hi;
		result.lo = v.lo;

		return ( result );
	}

	if ( __q_ge(u, v) )
	{
		result.hi = u.hi;
		result.lo = u.lo;
	}
	else
	{
		result.hi = v.hi;
		result.lo = v.lo;

	}

	return ( result );
}

quad
__q_min1(quad u, quad v)
{
quad	result;

	if ( u.hi != u.hi )
	{
		result.hi = u.hi;
		result.lo = u.lo;

		return ( result );
	}

	if ( v.hi != v.hi )
	{
		result.hi = v.hi;
		result.lo = v.lo;

		return ( result );
	}

	if ( __q_le(u, v) )
	{
		result.hi = u.hi;
		result.lo = u.lo;
	}
	else
	{
		result.hi = v.hi;
		result.lo = v.lo;

	}

	return ( result );
}

	/* intrinsic KIQNNT */

	/* by value version */

	/* computes the nearest int64_t to a long double */

long long
__kiqnnt( quad u )
{
quad	x;
long long result;

	x = __qnint(u);	/* find nearest whole number */

	result = __ki_qint(x); /* convert to a int64_t */

	return  ( result );
}


	/* intrinsic JIQNNT */

	/* by value version */

	/* computes the nearest int to a long double */

int
__jiqnnt( quad u )
{
quad	x;
int	result;

	x = __qnint(u);	/* find nearest whole number */

	result = (int)x.hi;	/* convert to an int */

	return  ( result );
}


	/* intrinsic QNINT */

	/* by value version */

	/* computes the nearest whole number to a long double */

quad
__qnint(quad u)
{
quad	result, y;
quad point5 = {0.5, 0.0};
double uhi, ulo;

    uhi = u.hi;
	ulo = u.lo;


	if ( u.hi != u.hi )
	{
		result.hi = u.hi;
		result.lo = u.lo;

		return ( result );
	}

	if ( u.hi >= 0.0 )
	{
		y = __q_add(u, point5);	/* y = arg + 0.5 */
	}
	else
	{
		y = __q_sub(u, point5); /* y = arg - 0.5 */
	}

	result = __qint(y);

	return (result);
}


	/* intrinsic QINT */

	/* by value version */

	/* truncates a long double, i.e. computes the integral part of
	   a long double
	*/

quad
__qint(quad u)
{
quad	result;
double uhi, ulo;

    uhi = u.hi;
	ulo = u.lo;


	if ( uhi != uhi )
	{
		result.hi = uhi;
		result.lo = ulo;

		return ( result );
	}

	if ( uhi >= 0.0 )
	{
		if ( uhi < twop52.d )
		{
			/* binary point occurs in uhi; truncate uhi to an integer
			*/

			result.hi = __trunc(uhi);

			result.lo = 0.0;

			if ( result.hi < uhi )
				return ( result );

			/* must adjust result by one if ulo < 0.0 */

			if ( ulo < 0.0 )
			{
				result.hi -= 1.0;

				return ( result );
			}

			return ( result );
		}
		else if ( fabs(ulo) < twop52.d )
		{
			/* binary point occurs in ulo; truncate ulo to an integer
			*/

			result.hi = uhi;

			result.lo = __trunc(ulo);

			if ( result.lo > ulo )
			{
				result.lo -= 1.0;
			}

			return ( result );
		}

		/* arg is an integer */

		result.hi = uhi;
		result.lo = ulo;

		return ( result );
	}
	else
	{
		if ( fabs(uhi) < twop52.d )
		{
			/* binary point occurs in uhi; truncate uhi to an integer
			*/

			result.hi = __trunc(uhi);

			result.lo = 0.0;

			if ( result.hi > uhi )
				return ( result );

			/* must adjust result by one if ulo > 0.0 */

			if ( ulo > 0.0 )
			{
				result.hi += 1.0;

				return ( result );
			}

			return ( result );
		}
		else if ( fabs(ulo) < twop52.d )
		{
			/* binary point occurs in ulo; truncate ulo to an integer
			*/

			result.hi = uhi;

			result.lo = __trunc(ulo);

			if ( result.lo < ulo )
			{
				result.lo += 1.0;
			}

			return ( result );
		}

		/* arg is an integer */

		result.hi = uhi;
		result.lo = ulo;

		return ( result );
	}

}


/* note that this routine must be kept in sync with the corresponding libc
 * routine, q_add.
 */



quad
__q_add(quad x, quad y)
{
int	ixhi, iyhi;
int	xptxhi, xptyhi;
long long	iz, iw, iqulp;
double	w, ww;
double	u, uu;
double	qulp;
quad	z;
double	tmp1, tmp2, lo, rem;
double xhi, xlo, yhi, ylo;

	/* adapted from T. J. Dekker's add2 subroutine */

	xhi = x.hi; xlo = x.lo;
	yhi = y.hi; ylo = y.lo;

	iyhi = *(int *)&yhi;
	xptyhi = (iyhi >> 20);
	xptyhi &= 0x7ff;

	ixhi = *(int *)&xhi;
	xptxhi = (ixhi >> 20);
	xptxhi &= 0x7ff;

#ifdef QUAD_DEBUG
	printf("c_q_add: xhi = %08x%08x\n", *(INT32 *)&xhi, *((INT32 *)&xhi + 1));
	printf("c_q_add: xlo = %08x%08x\n", *(INT32 *)&xlo, *((INT32 *)&xlo + 1));
	printf("c_q_add: yhi = %08x%08x\n", *(INT32 *)&yhi, *((INT32 *)&yhi + 1));
	printf("c_q_add: ylo = %08x%08x\n", *(INT32 *)&ylo, *((INT32 *)&ylo + 1));
#endif

	if ( xptxhi < xptyhi )
	{
		tmp1 = xhi;
		xhi = yhi;
		yhi = tmp1;
		xptxhi = xptyhi;
	}

	if ( fabs(xlo) < fabs(ylo) )
	{
		tmp2 = xlo;
		xlo = ylo;
		ylo = tmp2;
	}

	if ( xptxhi < 0x7fd )
	{
		z.hi = xhi + yhi;
		z.lo = xhi - z.hi + yhi;

		u = xlo + ylo;
		uu = xlo - u + ylo;

		lo = z.lo + u;

		w =  z.hi + lo;
		ww = z.hi - w + lo;

		rem = z.lo - lo + u;

		ww += rem + uu;
		z.hi = w + ww;
		DBL2LL( z.hi, iz );
		z.lo = w - z.hi + ww;

		/* if necessary, round z.lo so that the sum of z.hi and z.lo has at most
		   107 significant bits
		*/

		/* first, compute a quarter ulp of z */

		iw = (iz >> DMANTWIDTH);
		iqulp = (iw & 0x7ff);
		iqulp -= 54;
		iqulp <<= DMANTWIDTH;

		if ( iqulp > 0 )
		{
			LL2DBL( iqulp, qulp );
			iw <<= DMANTWIDTH;

			/* Note that the size of an ulp changes at a
			 * power of two.
			 */

			if ( iw == iz )
				goto fix;

			if ( fabs(z.lo) >= qulp )
			{
				qulp = 0.0;
			}
			else if ( z.lo < 0.0 )
				qulp = -qulp;

			z.lo += qulp;
			z.lo -= qulp;
		}


#ifdef QUAD_DEBUG
	printf("q_add: z.hi = %08x%08x\n", *(INT32 *)&z.hi, *((INT32 *)&z.hi + 1));
	printf("q_add: z.lo = %08x%08x\n", *(INT32 *)&z.lo, *((INT32 *)&z.lo + 1));
#endif

		return ( z );
	}
	else if ( xptxhi == 0x7ff )
	{
		z.hi = xhi + yhi;
		z.lo = 0.0;

#ifdef QUAD_DEBUG
	printf("q_add: z.hi = %08x%08x\n", *(INT32 *)&z.hi, *((INT32 *)&z.hi + 1));
	printf("q_add: z.lo = %08x%08x\n", *(INT32 *)&z.lo, *((INT32 *)&z.lo + 1));
#endif

		return ( z );
	}
	else
	{
		if ( fabs(yhi) < twop914.d )
		{
			z.hi = xhi;
			z.lo = xlo;

#ifdef QUAD_DEBUG
	printf("q_add: z.hi = %08x%08x\n", *(INT32 *)&z.hi, *((INT32 *)&z.hi + 1));
	printf("q_add: z.lo = %08x%08x\n", *(INT32 *)&z.lo, *((INT32 *)&z.lo + 1));
#endif

			return ( z );
		}

		/*	avoid overflow in intermediate computations by 
			computing 4.0*(.25*x + .25*y)
		*/

		xhi *= 0.25;
		xlo *= 0.25;
		yhi *= 0.25;
		ylo *= 0.25;

		z.hi = xhi + yhi;
		z.lo = xhi - z.hi + yhi;

		u = xlo + ylo;
		uu = xlo - u + ylo;

		lo = z.lo + u;

		w =  z.hi + lo;
		ww = z.hi - w + lo;

		rem = z.lo - lo + u;

		ww += rem + uu;
		z.hi = w + ww;
		DBL2LL( z.hi, iz );
		z.lo = w - z.hi + ww;

		/* if necessary, round z.lo so that the sum of z.hi and z.lo has at most
		   107 significant bits
		*/

		/* first, compute a quarter ulp of z */

		iw = (iz >> DMANTWIDTH);
		iqulp = (iw & 0x7ff);
		iqulp -= 54;
		iqulp <<= DMANTWIDTH;

		if ( iqulp > 0 )
		{
			LL2DBL( iqulp, qulp );
			iw <<= DMANTWIDTH;

			/* Note that the size of an ulp changes at a
			 * power of two.
			 */

			if ( iw == iz )
				goto fix2;

			if ( fabs(z.lo) >= qulp )
			{
				qulp = 0.0;
			}
			else if ( z.lo < 0.0 )
				qulp = -qulp;

			z.lo += qulp;
			z.lo -= qulp;
		}

		z.hi *= 4.0;

		if ( fabs(z.hi) == inf.d )
		{
			z.lo = 0.0;
			return ( z );
		}

		z.lo *= 4.0;

		return ( z );

	}

fix:
	if ( ((z.hi > 0.0) && (z.lo < 0.0)) || ((z.hi < 0.0) && (z.lo > 0.0)) )
		qulp *= 0.5;

	if ( fabs(z.lo) >= qulp )
	{
		qulp = 0.0;
	}
	else if ( z.lo < 0.0 )
		qulp = -qulp;

	z.lo += qulp;
	z.lo -= qulp;

	return ( z );

fix2:
	if ( ((z.hi > 0.0) && (z.lo < 0.0)) || ((z.hi < 0.0) && (z.lo > 0.0)) )
		qulp *= 0.5;

	if ( fabs(z.lo) >= qulp )
	{
		qulp = 0.0;
	}
	else if ( z.lo < 0.0 )
		qulp = -qulp;

	z.lo += qulp;
	z.lo -= qulp;

	z.hi *= 4.0;

	if ( fabs(z.hi) == inf.d )
	{
		z.lo = 0.0;
		return ( z );
	}

	z.lo *= 4.0;

	return ( z );
}

quad
__q_sub(quad x, quad y)
{
int	ixhi, iyhi;
int	xptxhi, xptyhi;
long long	iz, iw, iqulp;
double	w, ww;
double	u, uu;
double	qulp;
quad	z;
double	tmp1, tmp2, lo, rem;
double xhi, xlo, yhi, ylo;

	/* adapted from T. J. Dekker's add2 subroutine */

	xhi = x.hi; xlo = x.lo;
	yhi = y.hi; ylo = y.lo;

	iyhi = *(int *)&yhi;
	xptyhi = (iyhi >> 20);
	xptyhi &= 0x7ff;

	ixhi = *(int *)&xhi;
	xptxhi = (ixhi >> 20);
	xptxhi &= 0x7ff;

#ifdef QUAD_DEBUG
	printf("c_q_sub: xhi = %08x%08x\n", *(INT32 *)&xhi, *((INT32 *)&xhi + 1));
	printf("c_q_sub: xlo = %08x%08x\n", *(INT32 *)&xlo, *((INT32 *)&xlo + 1));
	printf("c_q_sub: yhi = %08x%08x\n", *(INT32 *)&yhi, *((INT32 *)&yhi + 1));
	printf("c_q_sub: ylo = %08x%08x\n", *(INT32 *)&ylo, *((INT32 *)&ylo + 1));
#endif

	yhi = -yhi;
	ylo = -ylo;

	if ( xptxhi < xptyhi )
	{
		tmp1 = xhi;
		xhi = yhi;
		yhi = tmp1;
		xptxhi = xptyhi;
	}

	if ( fabs(xlo) < fabs(ylo) )
	{
		tmp2 = xlo;
		xlo = ylo;
		ylo = tmp2;
	}

	if ( xptxhi < 0x7fd )
	{
		z.hi = xhi + yhi;
		z.lo = xhi - z.hi + yhi;

		u = xlo + ylo;
		uu = xlo - u + ylo;

		lo = z.lo + u;

		w =  z.hi + lo;
		ww = z.hi - w + lo;

		rem = z.lo - lo + u;

		ww += rem + uu;
		z.hi = w + ww;
		DBL2LL( z.hi, iz );
		z.lo = w - z.hi + ww;

		/* if necessary, round z.lo so that the sum of z.hi and z.lo has at most
		   107 significant bits
		*/

		/* first, compute a quarter ulp of z */

		iw = (iz >> DMANTWIDTH);
		iqulp = (iw & 0x7ff);
		iqulp -= 54;
		iqulp <<= DMANTWIDTH;

		if ( iqulp > 0 )
		{
			LL2DBL( iqulp, qulp );
			iw <<= DMANTWIDTH;

			/* Note that the size of an ulp changes at a
			 * power of two.
			 */

			if ( iw == iz )
				goto fix;

			if ( fabs(z.lo) >= qulp )
			{
				qulp = 0.0;
			}
			else if ( z.lo < 0.0 )
				qulp = -qulp;

			z.lo += qulp;
			z.lo -= qulp;
		}


#ifdef QUAD_DEBUG
	printf("q_add: z.hi = %08x%08x\n", *(INT32 *)&z.hi, *((INT32 *)&z.hi + 1));
	printf("q_add: z.lo = %08x%08x\n", *(INT32 *)&z.lo, *((INT32 *)&z.lo + 1));
#endif

		return ( z );
	}
	else if ( xptxhi == 0x7ff )
	{
		z.hi = xhi + yhi;
		z.lo = 0.0;

#ifdef QUAD_DEBUG
	printf("q_add: z.hi = %08x%08x\n", *(INT32 *)&z.hi, *((INT32 *)&z.hi + 1));
	printf("q_add: z.lo = %08x%08x\n", *(INT32 *)&z.lo, *((INT32 *)&z.lo + 1));
#endif

		return ( z );
	}
	else
	{
		if ( fabs(yhi) < twop914.d )
		{
			z.hi = xhi;
			z.lo = xlo;

#ifdef QUAD_DEBUG
	printf("q_add: z.hi = %08x%08x\n", *(INT32 *)&z.hi, *((INT32 *)&z.hi + 1));
	printf("q_add: z.lo = %08x%08x\n", *(INT32 *)&z.lo, *((INT32 *)&z.lo + 1));
#endif

			return ( z );
		}

		/*	avoid overflow in intermediate computations by 
			computing 4.0*(.25*x + .25*y)
		*/

		xhi *= 0.25;
		xlo *= 0.25;
		yhi *= 0.25;
		ylo *= 0.25;

		z.hi = xhi + yhi;
		z.lo = xhi - z.hi + yhi;

		u = xlo + ylo;
		uu = xlo - u + ylo;

		lo = z.lo + u;

		w =  z.hi + lo;
		ww = z.hi - w + lo;

		rem = z.lo - lo + u;

		ww += rem + uu;
		z.hi = w + ww;
		DBL2LL( z.hi, iz );
		z.lo = w - z.hi + ww;

		/* if necessary, round z.lo so that the sum of z.hi and z.lo has at most
		   107 significant bits
		*/

		/* first, compute a quarter ulp of z */

		iw = (iz >> DMANTWIDTH);
		iqulp = (iw & 0x7ff);
		iqulp -= 54;
		iqulp <<= DMANTWIDTH;

		if ( iqulp > 0 )
		{
			LL2DBL( iqulp, qulp );
			iw <<= DMANTWIDTH;

			/* Note that the size of an ulp changes at a
			 * power of two.
			 */

			if ( iw == iz )
				goto fix2;

			if ( fabs(z.lo) >= qulp )
			{
				qulp = 0.0;
			}
			else if ( z.lo < 0.0 )
				qulp = -qulp;

			z.lo += qulp;
			z.lo -= qulp;
		}

		z.hi *= 4.0;

		if ( fabs(z.hi) == inf.d )
		{
			z.lo = 0.0;
			return ( z );
		}

		z.lo *= 4.0;

		return ( z );

	}

fix:
	if ( ((z.hi > 0.0) && (z.lo < 0.0)) || ((z.hi < 0.0) && (z.lo > 0.0)) )
		qulp *= 0.5;

	if ( fabs(z.lo) >= qulp )
	{
		qulp = 0.0;
	}
	else if ( z.lo < 0.0 )
		qulp = -qulp;

	z.lo += qulp;
	z.lo -= qulp;

	return ( z );

fix2:
	if ( ((z.hi > 0.0) && (z.lo < 0.0)) || ((z.hi < 0.0) && (z.lo > 0.0)) )
		qulp *= 0.5;

	if ( fabs(z.lo) >= qulp )
	{
		qulp = 0.0;
	}
	else if ( z.lo < 0.0 )
		qulp = -qulp;

	z.lo += qulp;
	z.lo -= qulp;

	z.hi *= 4.0;

	if ( fabs(z.hi) == inf.d )
	{
		z.lo = 0.0;
		return ( z );
	}

	z.lo *= 4.0;

	return ( z );
}


long long
__ki_qint(quad x )
{
quad	xi;
long long	t;


	if ( x.hi != x.hi )
	{
		return ( (long long)x.hi );
	}

	if ( fabs(x.hi) == infinity.d )
	{
		return ( (long long)x.hi );
	}

	xi = __c_q_trunc(x);

	if ( (xi.hi > twop63.d) ||
	     ((xi.hi == twop63.d) && (xi.lo >= 0.0))
	   )
	{
		/* we get overflow here, so just let the hardware do it */

		return ( (long long)xi.hi );
	}

	if ( (xi.hi < m_twop63.d) ||
	     ((xi.hi == m_twop63.d) && (xi.lo < 0.0))
	   )
	{
		/* we get overflow here, so just let the hardware do it */

		if ( xi.hi == m_twop63.d )
		{
			xi.hi *= 2.0;
		}

		return ( (long long)xi.hi );
	}

	if ( fabs(xi.hi) > twop62.d )
	{
		/* add things up very carefully to avoid overflow */

		t = 0.5*xi.hi;
		return ( ((long long)xi.lo) + t + t );
	}

	/* just do it */

	return ( (long long)xi.hi + (long long)xi.lo );
}

quad
__c_q_trunc(quad x )
{
double	uhi, ulo;
quad	result;

	uhi = x.hi;
	ulo = x.lo;

	if ( uhi != uhi )
	{
		result.hi = uhi;
		result.lo = ulo;

		return ( result );
	}

	if ( uhi >= 0.0 )
	{
		if ( uhi < twop52.d )
		{
			/* binary point occurs in uhi; truncate uhi to an integer
			*/

			result.hi = __trunc(uhi);

			result.lo = 0.0;

			if ( result.hi < uhi )
				return ( result );

			/* must adjust result by one if ulo < 0.0 */

			if ( ulo < 0.0 )
			{
				result.hi -= 1.0;

				return ( result );
			}

			return ( result );
		}
		else if ( fabs(ulo) < twop52.d )
		{
			/* binary point occurs in ulo; truncate ulo to an integer
			*/

			result.hi = uhi;

			result.lo = __trunc(ulo);

			if ( result.lo > ulo )
			{
				result.lo -= 1.0;
			}

			return ( result );
		}

		/* arg is an integer */

		result.hi = uhi;
		result.lo = ulo;

		return ( result );
	}
	else
	{
		if ( fabs(uhi) < twop52.d )
		{
			/* binary point occurs in uhi; truncate uhi to an integer
			*/

			result.hi = __trunc(uhi);

			result.lo = 0.0;

			if ( result.hi > uhi )
				return ( result );

			/* must adjust result by one if ulo > 0.0 */

			if ( ulo > 0.0 )
			{
				result.hi += 1.0;

				return ( result );
			}

			return ( result );
		}
		else if ( fabs(ulo) < twop52.d )
		{
			/* binary point occurs in ulo; truncate ulo to an integer
			*/

			result.hi = uhi;

			result.lo = __trunc(ulo);

			if ( result.lo < ulo )
			{
				result.lo += 1.0;
			}

			return ( result );
		}

		/* arg is an integer */

		result.hi = uhi;
		result.lo = ulo;

		return ( result );
	}
}

int
__q_ge(quad x, quad y)
{

	if ( x.hi > y.hi )
		return ( 1 );

	if ( (x.hi == y.hi) && (x.lo >= y.lo) )
		return ( 1 );

	return ( 0 );
}

int __q_le(quad x, quad y)
{
	if ( x.hi < y.hi )
		return ( 1 );

	if ( (x.hi == y.hi) && (x.lo <= y.lo) )
		return ( 1 );

	return ( 0 );
}


#define	DMANTWIDTH	52
#define	DEXPWIDTH	11
#define	DSIGNMASK	0x7fffffffffffffffll
#define	DEXPMASK	0x800fffffffffffffll
#define	DQNANBITMASK	0xfff7ffffffffffffll

#define	MANTWIDTH	23
#define	EXPWIDTH	8
#define	SIGNMASK	0x7fffffff
#define	EXPMASK		0x807fffff
#define	QNANBITMASK	0xffbfffff

typedef union
{
	long long lword;
        double  d;
} du2;

static const du2 Quiet_nan = 
{
0x7ff8000000000000ll,
};

double
__trunc( double arg )
{
unsigned long long	ll, exp, mantissa;
int	sign;
int	shift_count;
double	result;


	ll = *(unsigned long long *)&arg;

	exp = (ll >> DMANTWIDTH);
	sign = (exp >> DEXPWIDTH);
	exp &= 0x7ff;
	mantissa = (ll & (DSIGNMASK & DEXPMASK));

	if ( exp == 0x7ff )
	{
		/* arg is an infinity, or a NaN */

		if ( mantissa == 0 )
			return ( arg );
		else 
		{
			return ( Quiet_nan.d );
		}
	}

	if ( exp >= 0x433 )
		return ( arg );

	if ( fabs(arg) < 1.0 )
		return ( (sign == 0) ? 0.0 : -0.0 );

	shift_count = 0x433 - exp;

	ll >>= shift_count;
	ll <<= shift_count;

	*(long long *)&result = ll;

	return ( result );
}

