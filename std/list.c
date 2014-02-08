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
#include "types.h"
#include "log.h"
#include "pool.h"
#include "list.h"

static void *ll_new( list_t *l );

static INLINE int32 ll_node_del( list_t *list, void *node )
{
        void *current, *prev;
		pool_t *p;

        prev = NULL;
        current = list->data;

        while( current ) {
                if( current == node ) {
                        if( prev == NULL )
                                *(ptr *)(list->data) = *(ptr *)current;
                        else
                                *(ptr *)prev = *(ptr *)current; // prev->next = current->next					
			p = pool_get( list->size );
			if( p != NULL ) 
				pool_freenode( p, (pe_t *)((ptr)current+PTR_SIZE) );

                        return 0;
                }

                prev = current;
                current = (void*)(*(ptr *)current); // current = current->next
        }

        return -1;
}

/*
 * public
 * delete a node from the list
 * it does NOT return memory back to the pool
 */
static void ll_del( list_t *l, void *node )
{
        if( ll_node_del( l, node ) == 0 )
                (l->count)--;
}

#define LL_NODE_ADD( dst, src )\
        *(ptr *)dst = *(ptr *)src;\
        *(ptr *)src = (ptr)dst;

/*
 * public
 * add structure to the linked list
 * *next pointer within the structre MUST be at first position; this one does NOT allocate space for node
 */  
static void ll_add( list_t *l, void *node ) 
{
        LL_NODE_ADD( node, &l->data );
        (l->count)++;
}

static int32 ll_count( list_t *l )
{
        return l->count;
}

/*
 * public
 * create a linked list
 */
list_t *ll_create( const int32 size )
{
        pool_t *p;
        list_t *l;
	pe_t *e;
		
	p = pool_get( sizeof( list_t ) );

	POOL_G( p, sizeof( list_t ), 0, e, l );
	l->pool = p;
	l->size = size;
	l->add = &ll_add;
	l->del = &ll_del;
	l->getnew = &ll_new;
	//l->do_count = &ll_count;
	l->count = 0;
	l->data = NULL;

        return l;
}

static void *ll_new( list_t *l )
{
	pool_t *p;
	pe_t *e;
	void *re;
	void *r;

	
	if( l == NULL )
		return NULL;

	p = pool_get( l->size );
	if( p == NULL ) p = pool_create( l->size, 0 );
	if( p != NULL ) {
		e = pool_getnode( p );
		r = e->data;
		re = (void *)( (ptr)r+PTR_SIZE );
		*(ptr *)re = (ptr)((ptr *)e);
	}

	return r;			
}

/*
 * destroy a linked list
 */
static void ll_destroy( const int32 pool, pe_t *e )
{
	pool_t *p;
	POOL_F( p, pool, e );
}
