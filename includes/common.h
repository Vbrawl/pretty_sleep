#ifndef PRETTY_SLEEP_COMMON_H
#define PRETTY_SLEEP_COMMON_H

#include <stdbool.h>
#include <stdint.h>


struct CommandArgs {
	const char* prog_name;
	bool help;
	bool version;
	bool quiet;
	unsigned int ui_update_interval;
	uint64_t sleep_for;
};


#endif
