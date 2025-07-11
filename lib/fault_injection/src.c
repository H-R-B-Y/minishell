/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:17:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/11 17:59:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <time.h>
#include <unistd.h>
#include <execinfo.h>

static void	*(*real_malloc)(size_t) = NULL;

static int	initialized = 0;
static int	fail_rate = 10; // percent
static int	verbose = 0;

void print_backtrace(void) {
	void *buffer[20];
	int nptrs = backtrace(buffer, 20);
	backtrace_symbols_fd(buffer, nptrs, STDERR_FILENO);
}

void print_malloc_caller(void) {
	
}

static void	init()
{
	if (initialized)
		return;
	initialized = 1;
	srand(time(NULL) ^ getpid());
	const char *env_rate = getenv("MALLOC_FAIL_RATE");
	if (env_rate)
		fail_rate = atoi(env_rate);
	const char *env_verbose = getenv("MALLOC_FAIL_VERBOSE");
	if (env_verbose)
		verbose = atoi(env_verbose);
	real_malloc = dlsym(RTLD_NEXT, "malloc");
	if (!real_malloc)
	{
		fprintf(stderr, "Failed to load real malloc/calloc/realloc\n");
		exit(1);
	}
}

void *malloc(size_t size) {
	void *ptr;
	static int in_malloc = 0;
	init();
	if (in_malloc) {
		return real_malloc(size);
	}
	in_malloc = 1;
	if (verbose)
	{
		Dl_info info;
		void *caller = __builtin_return_address(0);

		if (dladdr(caller, &info) && info.dli_sname) {
			fprintf(stderr, "[fail_malloc] called from %s (%p)\n", info.dli_sname, caller);
		} else {
			fprintf(stderr, "[fail_malloc] caller address: %p\n", caller);
		}
		print_backtrace();
	}
	int p = rand();
	if ((p % 100) < fail_rate)
		ptr = NULL;
	else
		ptr = real_malloc(size);
	if (verbose)
			fprintf(stderr, "[fail_malloc] malloc(%zu) => %p\n", size, ptr);
	printf("\n");
	in_malloc = 0;
	return ptr;
}

