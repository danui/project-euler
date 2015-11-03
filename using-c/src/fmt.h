#include <stdio.h>
#include <syslog.h>
#include <errno.h>

#ifndef __FMT__
#define __FMT__ "%s:%d "
#endif

#ifndef __OUT__
#define __OUT__ __FILE__,__LINE__
#endif
