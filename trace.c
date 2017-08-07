#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

void die(int nSignal);
static void dump_backtrace(void);

void main(void)
{
	die(1);
	return 0;
}

static void dump_backtrace(void)
{
	/* gcc need compile option "-fno-omit-frame-pointer"
	   gcc optional linker optinon "-rdynamic"
	*/ 
	int *s_priority;
	void *s_backtrace_buffer[16];
	char **s_backtrace_symbols;
	int s_backtrace_size;
	int s_backtrace_index;
	s_priority = LOG_DEBUG;
	s_backtrace_size = backtrace(
			(void **)(&s_backtrace_buffer[0]),
			(int)(sizeof(s_backtrace_buffer) / sizeof(void *))
			);
	if (s_backtrace_size <= 0){
		s_backtrace_symbols = (char **)0;
	}
	else{
		s_backtrace_symbols = backtrace_symbols(
				(void * const *)(&s_backtrace_buffer[0]),
				s_backtrace_size
				);

	}
	(void)fprintf(stderr,"backtrace() returned %d address\n",s_backtrace_size);
	syslog(s_priority,"backtrace() returned %d address\n",s_backtrace_size);
	for(s_backtrace_index=0;s_backtrace_index<s_backtrace_size;s_backtrace_index++)
	{
		(void)fprintf(stderr,"%02d-%p-%s\n",
				s_backtrace_index+1,
				s_backtrace_buffer[s_backtrace_index],
				(s_backtrace_symbols==((char**)0))?"<unknown symbols>":s_backtrace_symbols[s_backtrace_index]
			     );
		syslog(s_priority,"%02d-%p-%s",
				s_backtrace_index+1,
				s_backtrace_buffer[s_backtrace_index],
				(s_backtrace_symbols==((char**)0))?"<unknown symbols>":s_backtrace_symbols[s_backtrace_index]
		      );

	
	}
	if(s_backtrace_symbols !=((void*)0)){
		free((void*)s_backtrace_symbols);
}
}



void die(int nSignal)
{
	(void)fprintf(stderr,"test : Signal happened(%d)\n", nSignal);
	openlog("flogs", LOG_CONS|LOG_PID|LOG_NDELAY,LOG_LOCAL1);
#if 0L
	syslog();
#else
	dump_backtrace();
#endif
	closelog();
	exit(0);
}
