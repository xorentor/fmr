#include <assert.h>
#include <unistd.h>

#include "types.h"
#include "log.h"
#include "string.h"
#include "pool.h"
#include "list.h"
#include "util.h"
#include "maps.h"

#define THREAD_INC\
	if( thread_no == (THREAD_WORKERS-1) ) { \
		thread_no = 0;\
	} else { \
		thread_no++;\
	}\

struct maps *init_maps()
{
	pool_t *p;
	pe_t *e;
	struct maps *m;

	POOL_G( p, sizeof( struct maps ), 0, e, m );
	
	return m;
}

// based on regions we create sections
// section is always accessed by one thread only
list_t *worker_sections( struct region *r )
{
	ulong size = 0, section_size = 0, region_size = 0;
	int32 thread_no = 0;
	struct region *tmp;	
	list_t *llsections;
	struct section *sections;
	int32 x, offset;

	tmp = r;
	while( tmp ) {
		size += tmp->size;
		tmp = tmp->next;
	}

	//printf( "total size: %lx\n", size );
	// this is naturally alligned
	section_size = size / THREAD_WORKERS;

	llsections = ll_create( sizeof(struct section) );

	tmp = r;
	while( tmp ) {
		if( tmp->size  > section_size ) {
			for( offset = 0, region_size = tmp->size; 
				region_size > 0 && region_size <= tmp->size; 
				region_size -= section_size, offset++ ) 
			{
				sections = llsections->getnew( llsections );
				sections->start = tmp->start + offset*section_size;
				sections->size = (( x = region_size-section_size ) > 0 ) ? section_size : region_size;
				sections->worker_id = thread_no;
				llsections->add( llsections, sections );

				THREAD_INC;
			} 
		} else {
			sections = llsections->getnew( llsections );
			sections->start = tmp->start;
			sections->size = tmp->size;
			sections->worker_id = thread_no;
			llsections->add( llsections, sections );
			THREAD_INC;
		}
		tmp = tmp->next;
	}

	return llsections;
}

struct maps *read_maps( pid_t pid )
{
	FILE *maps;
	char name[ 128 ], *line = NULL;
	uint32 len = 0;
	list_t *regions;
	char filename[ 256 ];
	struct region *reg;
	struct maps *mp;

	ulong start, end;
        char read, write, exec, cow;
        int32 offset, dev_major, dev_minor, inode;

	if( pid  == 0 )
		return NULL;

        snprintf( name, sizeof(name), "/proc/%u/maps", pid );


        if ((maps = fopen(name, "r")) == NULL) {
            LOG( ERROR, "failed to open maps file %s.\n", name);
        }

	regions = ll_create( sizeof( struct region ) );

	while( getline( &line, &len, maps ) != -1 ) {
		fmf_memset( filename, 0, sizeof( filename ) );
	
		if( sscanf(line, "%lx-%lx %c%c%c%c %x %x:%x %u %s", &start, &end, &read, &write, &exec, 
		&cow, &offset, &dev_major, &dev_minor, &inode, filename ) >= 6) {
			if( (write == 'w') && (read == 'r') && ((end - start) > 0) ) {
				reg = regions->getnew( regions );
#ifdef HEAP_ONLY
				if( fmf_strcmp( filename, "[heap]") != 0 )
					continue;
#endif	
				reg->start = (void *)start;
				reg->size = (ulong)(end - start);
				reg->flags |= ( REGION_READ | REGION_WRITE );
				if( exec == 'x' )
					reg->flags |= REGION_EXEC;
				if( exec == 's' )
					reg->flags |= REGION_SHARED;
				if( exec == 'p' )
					reg->flags |= REGION_PRIVATE;
				regions->add( regions, reg );
			}
		}
	}

	fclose( maps );

	mp = init_maps();
	mp->regions = regions;	
	mp->sections = worker_sections( (void *)regions->data );

	return mp;
}
