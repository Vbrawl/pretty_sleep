#include "common.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MIN(a, b) ((a < b) ? a : b)

int set_default_args(struct CommandArgs* args) {
	args->prog_name = "<error>";
	args->help = false;
	args->quiet = false;
	args->ui_update_interval = 1;
	args->sleep_for = 0;
}

bool parse_command_line_arguments(unsigned int argc, char** argv, struct CommandArgs* args) {
	bool error = false;

	unsigned int uint_val;
	uint64_t uint64_val;
	bool convert_success = false;

	int opt;
	while((opt = getopt(argc, argv, "hqi:")) != -1 && !error) {
		switch(opt) {
		case 'q':
			args->quiet = true;
			break;

		case 'i':
			convert_success = str_to_interval(optarg, &uint_val);
			if(!convert_success) {
				fprintf(stderr, "Invalid UI Update Interval duration\n");
				error = true;
			} else { args->ui_update_interval = uint_val; }
			break;
		case 'h':
			args->help = true;
			break;
		}
	}

	if(!args->help && optind < argc) {
		optarg = argv[optind];
		convert_success = str_to_seconds(optarg, &uint64_val);
		if(!convert_success) {
			fprintf(stderr, "Invalid sleep duration\n");
			error = true;
		}
		else { args->sleep_for = uint64_val; }
	}


	if(error) { args->help = true; }
	return error;
}

void print_help(struct CommandArgs* args) {
	printf( "Usage: %s [OPTIONS] SLEEP_DURATION[SUFFIX]\n"
		"Pause for SLEEP_DURATION seconds, must be an integer.\n"
		"SUFFIX may be 's' for seconds (default), 'm' for minutes, 'h' for hours\n"
		"and 'd' for days.\n"
		"The output format is dd:hh:mm:ss"
		"\n"
		"    -h             Display the help and exit\n"
		"    -q             Quiet, don't display anything while sleeping\n"
		"    -i INTERVAL    Set the interval between each interface update\n", args->prog_name);
}


void pretty_sleep(struct CommandArgs* args) {
	uint64_t duration = args->sleep_for;

	uint64_t days, rem_days;
	uint64_t hours, rem_hours;
	uint64_t minutes, rem_minutes;
	uint64_t seconds, rem_seconds;

	time_sort(duration, &days, &hours, &minutes, &seconds);

	while(duration != 0) {
		unsigned int chunk = MIN(duration, UINT_MAX);
		if(!args->quiet) {
			chunk = MIN(chunk, args->ui_update_interval);
			time_sort(duration, &rem_days, &rem_hours, &rem_minutes, &rem_seconds);

			printf("\rTotal: %02lu:%02lu:%02lu:%02lu | Remaining: %02lu:%02lu:%02lu:%02lu", days, hours, minutes, seconds, rem_days, rem_hours, rem_minutes, rem_seconds);
			fflush(stdout);
		}

		unsigned int remaining = sleep(chunk);
		duration -= (chunk - remaining);
	}
}


int main(unsigned int argc, char** argv) {
	struct CommandArgs args;
	set_default_args(&args);

	bool arg_status = parse_command_line_arguments(argc, argv, &args);

	if(args.help) {
		print_help(&args);
		return arg_status;
	}

	pretty_sleep(&args);
	return 0;
}
