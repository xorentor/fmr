#ifndef MAPS_H_
#define MAPS_H_

// always pow of 2
#define THREAD_WORKERS	4

#undef HEAP_ONLY
#define HEAP_ONLY

enum {
	REGION_READ = (1<<0),
	REGION_WRITE = (1<<1),
	REGION_EXEC = (1<<2),
	REGION_SHARED = (1<<3),
	REGION_PRIVATE = (1<<4), 
};

struct user_input {
	char buffer[ 256 ];
	int32 length;
};

struct results {
	struct results *next;
	pe_t *e;
	char buffer[ 256 ];
	int32 length;
	void *addr;
	// something else here
};

struct section {
	struct section *next;
	pe_t *e;
	int32 worker_id;
	// this could be ll as well
	void *start;		
	ulong size;
};

struct region {
	struct region_s *next;
	pe_t *e;
	void *start;
	ulong size;
	uint32 flags;
};

struct maps {
	pe_t *e;
	list_t *regions;
	list_t *sections;
};

struct maps *read_maps( pid_t pid );

#endif
