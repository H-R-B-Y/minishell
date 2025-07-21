/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fault_injector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:23:11 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/17 15:10:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <dlfcn.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <execinfo.h>
#include <string.h>

static void	*(*real_malloc)(size_t) = NULL;
static int	(*real_open)(const char *, int, ...) = NULL;
static pid_t (*real_fork)(void) = NULL;

static int	initialized = 0;
static int	malloc_fail_at = 0;
static int	open_fail_at = 0;
static int	fork_fail_at = 0;
static int	verbose = 0;
static char	*blacklist = NULL;

void print_backtrace(void)
{
	void *buffer[20];
	int nptrs;
	
	nptrs = backtrace(buffer, 20);
	backtrace_symbols_fd(buffer, nptrs, STDERR_FILENO);
}

static void	init(void)
{
	char	*stat[] = {
		getenv("MALLOC_FAIL_AT"),
		getenv("OPEN_FAIL_AT"),
		getenv("FORK_FAIL_AT"),
		getenv("FAIL_VERBOSE"),
		getenv("FAULT_BLACKLIST")
	};

	if (initialized)
		return ;
	initialized = 1;
	if (stat[0])
		malloc_fail_at = atoi(stat[0]);
	if (stat[1])
		open_fail_at = atoi(stat[1]);
	if (stat[2])
		fork_fail_at = atoi(stat[2]);
	if (stat[3])
		verbose = atoi(stat[3]);
	real_malloc = dlsym(RTLD_NEXT, "malloc");
	real_fork = dlsym(RTLD_NEXT, "fork");
	real_open = dlsym(RTLD_NEXT, "open");
	if (!real_open)
		real_open = dlsym(RTLD_NEXT, "open64");
	if (!real_malloc || !real_fork || !real_open)
	{
		fprintf(stderr, "Failed to load real symbols\n");
		exit(1);
	}
	if (stat[4])
		blacklist = stat[4]; // later split this into different items
}

static int	check_blacklist(Dl_info *info)
{
	if (strstr(info->dli_fname, blacklist))
		return (0);
	return (1);
}


void	*malloc(size_t size)
{
	void						*ptr;
	static unsigned long int	count = 0;
	static short				in_malloc = 0;
	Dl_info						info;
	void						*caller;
	int							status;

	init();
	if (in_malloc)
		return (real_malloc(size));
	caller = __builtin_return_address(0);
	status = dladdr(caller, &info);
	if (status && !check_blacklist(&info))
		return (real_malloc(size));
	in_malloc = 1;
	count++;
	if (malloc_fail_at && count > malloc_fail_at)
		ptr = NULL;
	else
		ptr = real_malloc(size);
	if (verbose && !ptr)
	{
		if (status && info.dli_sname)
			fprintf(stderr, "[fail_malloc] called from %s (%p)\n", info.dli_sname, caller);
		else
			fprintf(stderr, "[fail_malloc] caller address: %p\n", caller);
		print_backtrace();
		fprintf(stderr, "\n");
	}
	in_malloc = 0;
	return (ptr);
}

int	open(const char *pathname, int flags, ...)
{
	static unsigned long int	count = 0;
	Dl_info						info;
	void						*caller;
	int							status;
	va_list						args;
	mode_t						mode;

	init();
	caller = __builtin_return_address(0);
	status = dladdr(caller, &info);
	if (status && !check_blacklist(&info))
	{
		if (flags & O_CREAT)
		{
			va_start(args, flags);
			mode = va_arg(args, mode_t);
			va_end(args);
			return real_open(pathname, flags, mode);
		}
		return real_open(pathname, flags);
	}
	count++;
	if (open_fail_at && count > open_fail_at)
	{
		if (verbose)
		{
			if (status && info.dli_sname)
				fprintf(stderr, "[fail_open] called from %s (%p)\n", info.dli_sname, caller);
			else
				fprintf(stderr, "[fail_open] caller address: %p\n", caller);
			print_backtrace();
			fprintf(stderr, "\n");
		}
		return (-1);
	}
	if (flags & O_CREAT) 
	{
		va_start(args, flags);
		mode = va_arg(args, mode_t);
		va_end(args);
		return real_open(pathname, flags, mode);
	}
	return real_open(pathname, flags);
}

pid_t	fork(void)
{
	static unsigned long int	count = 0;
	Dl_info						info;
	void						*caller;
	int							status;
	pid_t						pid;

	init();
	caller = __builtin_return_address(0);
	status = dladdr(caller, &info);
	if (status && !check_blacklist(&info))
	{
		pid = real_fork();
		if (pid)
			return (pid);
		else
			return (0);
	}
	count++;
	if (fork_fail_at && count > fork_fail_at)
	{
		if (verbose)
		{
			if (status && info.dli_sname)
				fprintf(stderr, "[fail_fork] called from %s (%p)\n", info.dli_sname, caller);
			else
				fprintf(stderr, "[fail_fork] caller address: %p\n", caller);
			print_backtrace();
			fprintf(stderr, "\n");
		}
		return (-1);
	}
	pid = real_fork();
	if (pid)
		return (pid);
	return (0);
}
