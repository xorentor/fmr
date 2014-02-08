#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <pthread.h>

#include "types.h"
#include "log.h"
#include "string.h"
#include "pool.h"
#include "list.h"
#include "util.h"
#include "maps.h"

#define BUF_OFFSET	2
#define ENDLESS 	(1==1)
#define GET_BUFFER 	(ui.buffer+BUF_OFFSET)

static pid_t pid;
static struct maps *maps;
static struct user_input ui;
static pthread_mutex_t mutex_ui = PTHREAD_MUTEX_INITIALIZER; 

int32 attach( pid_t target )
{
	int32 status;

	if( ptrace(PTRACE_ATTACH, target, NULL, NULL) == -1L ) {
        	return 1;
	}

	if (waitpid(target, &status, 0) == -1 || !status) {
 		return 2;
	}

	return 0;
}

int32 detach( pid_t target )
{
	return ptrace(PTRACE_DETACH, target, 1, 0) == 0;
}

void *readline( void *data )
{
	int32 len;
	list_t *r = (list_t *)data;
	struct results *res;

	res = r->data;

	while( 1 == 1 ) {
		fmf_memset( ui.buffer, 0, sizeof( ui.buffer ) );
		scanf( "%s", ui.buffer );

		if( fmf_memcmp( ui.buffer, "2:", BUF_OFFSET ) == 0 )
			ui.length = 2;
		else if( fmf_memcmp( ui.buffer, "4:", BUF_OFFSET ) == 0 )
			ui.length = 4;
		else if( fmf_memcmp( ui.buffer, "8:", BUF_OFFSET ) == 0 )
			ui.length = 8;
		else if( fmf_memcmp( ui.buffer, "s:", BUF_OFFSET ) == 0 ) {
			len = fmf_strlen( ui.buffer+2 );
			ui.length = ROUND2( len );
		} else if ( fmf_memcmp( ui.buffer, "list", 4 ) == 0 ) {
			while( res ) {
				printf( "found\n" );
				res = res->next;
			}

		} else
			continue;
	}
	
	pthread_exit(0);

	return NULL;
}


void *worker( void *data )
{
	
	struct section *sections;
	struct region *reg;
	short result;	
	struct user_regs_struct regs;
	char *tmp;
	int32 iter;
	list_t *r;
	struct results *res;

	r = (list_t *)data;

	while( ENDLESS ) {
		if( *(GET_BUFFER) == 0 || ui.length == 0 )
			continue;

		sections = (struct section *)( maps->sections->data );
		while( sections ) {
		tmp = sections->start;

		while( sections->start+sections->size > tmp ) {
			attach( pid );
			result = ptrace( PTRACE_PEEKDATA, pid, tmp, NULL );
			detach( pid );

			if( result == atoi(GET_BUFFER) ) {
				res = r->getnew( r );
				fmf_memcpy( res->buffer, &result, 2 );
				res->length += 2;
				res->addr = (void *)tmp;
				r->add( r, res );
				printf( "adding\n" );
			}

			tmp += 2;	// + word
		}

		next:
		sections = sections->next;
		}
		fmf_memset( ui.buffer, 0, sizeof( ui.buffer ) );
	}
	
	pthread_exit(0);

	return NULL;
}

int main( int argc, char **argv )
{
	int32 i;
	pthread_t tid[ THREAD_WORKERS ];	
	list_t *r;

	if( argc != 2 )	{
		printf("error 2 args\n");
		exit( 0 );
	}

	pid = atoi( argv[ 1 ] );

	fmf_memset( ui.buffer, 0, sizeof( ui.buffer ) );
	
	maps = read_maps( pid );

	r = ll_create( sizeof( struct results ) );

	// TODO: more thread workers here as we will replace ptrace()
	pthread_create( &tid[ 0 ], NULL, &readline, r );
	pthread_create( &tid[ 1 ], NULL, &worker, r );

	for( i = 0; i < 2; i++ ) {	
		pthread_join( tid[ 0 ], NULL );
		pthread_join( tid[ 1 ], NULL );	
	}

	return 0;
}
