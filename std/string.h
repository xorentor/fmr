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

#ifndef STRING
#define	STRING	

/*-----------------------------------------------------------------------------
 *  memcpy
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_memcpy_linuxkernel_nasm
extern 	void *nasm_memcpy_s( void *, const void *, uint16 );
//extern void 	*nasm_memcpy_b( void *, const void *, uint16 );
#elif LIBSTR_memcpy_prefetch
extern 	void *nasm_memcpy_prefetch( void *, const void *, uint16 );
#elif LIBSTR_memcpy_linuxkernel_att
#elif LIBSTR_all_memcpy_compressed
#elif LIBSTR_memcpy_sse2vector
#else
#endif
void 	*fmf_memcpy(void *, const void *, uint32);

/*-----------------------------------------------------------------------------
 *  strlen
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_strlen_sse42_nasm
extern 	uint16  	nasm_strlen_pcmp( const char * );
#elif LIBSTR_strlen_sse42_att
#elif LIBSTR_strlen_x86_32
#else
#endif
uint32   fmf_strlen(const char *);

/*-----------------------------------------------------------------------------
 *  strcmp
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_strcmp_sse42_nasm
extern int32	strcmp_sse42(const char *, const char *);
#elif LIBSTR_strcmp_x86_32
#else
#endif
int32    fmf_strcmp(const char *, const char *);

/*-----------------------------------------------------------------------------
 * strstr
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_strstr
#elif LIBSTR_s390_strstr
#else
#endif
char 	*fmf_strstr(const char *, const char *);

/*-----------------------------------------------------------------------------
 *  memcmp
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_memcmp
#else
#endif
int32   fmf_memcmp(const void *, const void *, uint32);

/*-----------------------------------------------------------------------------
 *  memchr 
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_memchr
#else
#endif
void 	*fmf_memchr(const void *, int32, uint32);

/*-----------------------------------------------------------------------------
 *  memmove
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_memmove
#else
#endif
void 	*fmf_memmove(void *, const void *, uint32);

/*-----------------------------------------------------------------------------
 *  memset
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_memset
#else
#endif
void 	*fmf_memset(void *, int32, uint32);

/*-----------------------------------------------------------------------------
 *  strcat
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_strcat
#else
#endif
char 	*fmf_strcat(char *, const char *);

/*-----------------------------------------------------------------------------
 *  strxfrm
 *-----------------------------------------------------------------------------*/
uint32	fmf_strxfrm(char *, const char *, uint32);

/*-----------------------------------------------------------------------------
 *  strchr
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_strchr_x86_32
#else
#endif
char 	*fmf_strchr(const char *, int32);

/*-----------------------------------------------------------------------------
 *  strcspn
 *-----------------------------------------------------------------------------*/
uint32	fmf_strcspn(const char *, const char *);

/*-----------------------------------------------------------------------------
 *  strspn
 *-----------------------------------------------------------------------------*/
uint32  fmf_strspn(const char *, const char *);

/*-----------------------------------------------------------------------------
 *  strncat
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_strncat
#else
#endif
char 	*fmf_strncat(char *, const char *, uint32);

/*-----------------------------------------------------------------------------
 *  strrchr
 *-----------------------------------------------------------------------------*/
char 	*fmf_strrchr(const char *, int32);

/*-----------------------------------------------------------------------------
 *  strncmp
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_strncmp
#else
#endif
int32    fmf_strncmp(const char *, const char *, uint32);

/*-----------------------------------------------------------------------------
 *  strtok_r
 *-----------------------------------------------------------------------------*/
char 	*fmf_strtok_r(char *, const char *, char **);

/*-----------------------------------------------------------------------------
 *  strcpy
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_strcpy
#else
#endif
char 	*fmf_strcpy(char *, const char *);

/*-----------------------------------------------------------------------------
 *  strncpy
 *-----------------------------------------------------------------------------*/
#ifdef LIBSTR_x86_32_strncpy
#else
#endif
char 	*fmf_strncpy(char *, const char *, uint32);

int32	fmf_itoa( int32, unsigned char*, int32, int32 );
int32	fmf_strncasecmp( const char *ct, const char *cs, uint32 count );
int32	fmf_strcasecmp( const char *string1, const char *string2 );

#endif
