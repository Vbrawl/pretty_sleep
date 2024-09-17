#include "utils.h"
#include <errno.h>
#include <stdlib.h>



bool str_to_uint64(const char* str, uint64_t* val) {
	char* endptr;
	*val = strtoll(str, &endptr, 10);

	return !(errno != 0 || endptr == str || *endptr != '\0' || (*val) < 0);
}

bool str_to_seconds(const char* str, uint64_t* val) {
	int multiplier = 0;

	char* endptr;
	*val = strtoll(str, &endptr, 10);

	switch(*endptr) {
	case '\0':
	case 's':
		multiplier = 1;
		break;
	case 'm':
		multiplier = 60;
		break;
	case 'h':
		multiplier = 60 * 60;
		break;
	case 'd':
		multiplier = 60 * 60 * 24;
		break;
	}

	(*val) *= multiplier;
	return !(errno != 0 || endptr == str || multiplier == 0 || (*val) < 0);
}

bool str_to_interval(const char* str, unsigned int* val) {
	int multiplier = 0;

	char* endptr;
	*val = strtol(str, &endptr, 10);

	switch(*endptr) {
	case '\0':
	case 's':
		multiplier = 1;
		break;
	case 'm':
		multiplier = 60;
		break;
	case 'h':
		multiplier = 60 * 60;
		break;
	case 'd':
		multiplier = 60 * 60 * 24;
		break;
	}

	(*val) *= multiplier;
	return !(errno != 0 || endptr == str || multiplier == 0 || (*val) < 0);
}

void time_sort(uint64_t duration, uint64_t* days, uint64_t* hours, uint64_t* minutes, uint64_t* seconds) {
	*days = duration / (60*60*24);
	duration -= (*days) * (60*60*24);

	*hours = duration / (60*60);
	duration -= (*hours) * (60*60);

	*minutes = duration / 60;
	duration -= (*minutes) * 60;

	*seconds = duration;
}
