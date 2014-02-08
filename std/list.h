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

#ifndef LIST_H
#define LIST_H

struct list_s;

typedef void (*add)( struct list_s *l, void *node );
typedef void (*del)( struct list_s *l, void *node );
typedef void* (*getnew)( struct list_s *l );
typedef void (*do_count)( struct list_s *l );

typedef struct list_s {
	pe_t *e;
       	int32 count;
	pool_t *pool;
	int32 size;
	add add;
	del del;
	getnew getnew;
	do_count do_count;
        void *data;
} list_t;

list_t *ll_create( const int32 size  );

#endif
