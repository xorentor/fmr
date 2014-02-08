/*
 Copyright (C) Free Mind Foundation 2013
 www.fmf-base.org
 
 authors:
 xorentor

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef TYPES_H_
#define TYPES_H_

#ifndef IS_LITTLE_ENDIAN
#define IS_LITTLE_ENDIAN 	1
#endif

#undef ARCH64
#undef ARCH32
#if _WIN64 || __x86_64__ || __ppc64__
#define FLOAT64
#define	ARCH64	
#else
#define ARCH32	
#endif

typedef signed long 		slong;
typedef unsigned long    	ulong;
typedef long long		int64;
typedef unsigned long long	uint64;
typedef int			int32;
typedef unsigned int		uint32;
typedef short			int16;
typedef unsigned short		uint16;
typedef signed char		int8;
typedef unsigned char		uint8;

#define PTR_SIZE (sizeof(void *))

#if _WIN32 || _WIN64
#define INLINE _inline
#if _WIN64
typedef ulong 	ptr;
#else
typedef ulong 	ptr;
#endif
#elif __GNUC__
#define INLINE inline
#if __x86_64__ || __ppc64__
typedef ulong	ptr;
#else
typedef uint32	ptr;
#endif
#endif

#ifndef TYPEDEF_FLOAT32
#define TYPEDEF_FLOAT32
typedef float           float32;
#endif

#ifndef TYPEDEF_FLOAT64
#define TYPEDEF_FLOAT64
typedef double          float64;
#endif

#if _WIN64 || __x86_64__ || __ppc64__
typedef float64 float_t;
#else 
typedef float32 float_t;
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1  
#endif

#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif

#define ARRAY_SIZE(a)    (sizeof(a)/sizeof(a[0]))
#define MAXINT_32  0x7FFFFFFFL

#endif
