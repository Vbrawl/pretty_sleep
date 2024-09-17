#ifndef PRETTY_SLEEP_UTILS_H
#define PRETTY_SLEEP_UTILS_H

#include <stdbool.h>
#include <stdint.h>


bool str_to_uint64(const char* str, uint64_t* val);
bool str_to_seconds(const char* str, uint64_t* val);
bool str_to_interval(const char* str, unsigned int* val);
void time_sort(uint64_t duration, uint64_t* days, uint64_t* hours, uint64_t* minutes, uint64_t* seconds);


#endif
