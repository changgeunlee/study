#include <stdio.h>
#include <syslog.h>

void main()
{
	syslog(LOG_INFO|LOG_LOCAL0,"syslog test");
	
}
