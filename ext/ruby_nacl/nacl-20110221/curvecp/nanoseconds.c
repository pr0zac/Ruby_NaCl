#include <time.h>
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
#include <mach/clock.h>
#include <mach/mach.h>
#endif
#include "nanoseconds.h"

/* XXX: Y2036 problems; should upgrade to a 128-bit type for this */
/* XXX: nanosecond granularity limits users to 1 terabyte per second */

long long nanoseconds(void)
{
  struct timespec t;

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  t.tv_sec = mts.tv_sec;
  t.tv_nsec = mts.tv_nsec;
#else
  if (clock_gettime(CLOCK_REALTIME,&t) != 0) return -1;
#endif
  return t.tv_sec * 1000000000LL + t.tv_nsec;
}
