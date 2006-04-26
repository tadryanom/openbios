/* 
 *   Creation Date: <2002/10/19 21:05:07 samuel>
 *   Time-stamp: <2002/10/22 22:29:18 samuel>
 *   
 *	<misc.c>
 *	
 *	Miscellaneous
 *   
 *   Copyright (C) 2002, 2003 Samuel Rydh (samuel@ibrium.se)
 *   
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation
 *   
 */

#include "openbios/config.h"
#include "libc/string.h"

int errno;

void
qsort( void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void*) )
{
	int worked, i, j;

	/* even more inefficient than the glibc variant :-) */
	do {
		char *p = base;
		worked = 0;
		for( i=0; i<nmemb-1; i++, p+= size ) {
			if( compar( p, p + size ) > 0 ) {
				worked = 1;
				for( j=0; j<size; j++ ) {
					char ch = p[j];
					p[j] = p[j+size];
					p[j+size] = ch;
				}
			}
		}
	} while( worked );
}


long int
strtol( const char *nptr, char **endptr, int base )
{
	int sum, n, sign=1;
	while( isspace(*nptr) )
		nptr++;

	if( *nptr == '-' || *nptr == '+' )
		sign = (*nptr++ == '-') ? -1 : 1;

	if( base == 16 || base == 0) {
		if( !base )
			base = (nptr[0] == '0')? 8 : 10;
		if( nptr[0] == '0' && nptr[1] == 'x' ) {
			nptr += 2;
			base = 16;
		}
	}
	for( sum=0 ;; nptr++ ) {
		char ch = *nptr;
		if( !isalnum(ch) )
			break;
		n = isdigit(ch) ? ch - '0' : toupper(ch) - 'A' + 10;
		if( n >= base || n < 0 )
			break;
		sum *= base;
		sum += n;
	}
	if( endptr )
		*endptr = (char*)nptr;

	return sum * sign;
}
