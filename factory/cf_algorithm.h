/* emacs edit mode for this file is -*- C++ -*- */
/* $Id: cf_algorithm.h,v 1.8 1997-11-19 17:42:11 schmidt Exp $ */

#ifndef INCL_CF_ALGORITHM_H
#define INCL_CF_ALGORITHM_H

//{{{ docu
//
// cf_algorithm.h - declarations of higher level algorithms.
//
// This header file collects declarations of most of the
// functions in factory which implement higher level algorithms
// on canonical forms (factorization, gcd, etc.).
//
// This header file corresponds to:
//
// cf_algorithms.cc, cf_chinese.cc, cf_factor.cc, cf_linsys.cc,
// cf_resultant.cc
//
//}}}

#include <config.h>

#include "canonicalform.h"
#include "variable.h"

/*BEGINPUBLIC*/

//{{{ function declarations from cf_algorithm.cc
CanonicalForm psr ( const CanonicalForm & f, const CanonicalForm & g, const Variable & x );

CanonicalForm psq ( const CanonicalForm & f, const CanonicalForm & g, const Variable & x );

void psqr ( const CanonicalForm & f, const CanonicalForm & g, CanonicalForm & q, CanonicalForm & r, const Variable & x );

CanonicalForm common_den ( const CanonicalForm & f );
//}}}

//{{{ function declarations from cf_chinese.cc
void chineseRemainder ( const CanonicalForm & x1, const CanonicalForm & q1, const CanonicalForm & x2, const CanonicalForm & q2, CanonicalForm & xnew, CanonicalForm & qnew );

void chineseRemainder ( const CFArray & x, const CFArray & q, CanonicalForm & xnew, CanonicalForm & qnew );
//}}}

//{{{ function declarations from cf_factor.cc
CFFList factorize ( const CanonicalForm & f, bool issqrfree = false );

CFFList factorize ( const CanonicalForm & f, const Variable & alpha );

CFFList sqrFree ( const CanonicalForm & f, bool sort = false );

bool isSqrFree ( const CanonicalForm & f );
//}}}

//{{{ function declarations from cf_linsys.cc
bool linearSystemSolve ( CFMatrix & M );

CanonicalForm determinant ( const CFMatrix & M, int n );
//}}}

//{{{ function declarations from cf_resultant.cc
CFArray subResChain ( const CanonicalForm & f, const CanonicalForm & g, const Variable & x );

CanonicalForm resultant ( const CanonicalForm & f, const CanonicalForm & g, const Variable & x );
//}}}

/*ENDPUBLIC*/

#endif /* ! INCL_CF_ALGORITHM_H */
