/* 
 * timeFunctions.c
 * 
 * Functions for measuring time in programs
 *
 * Created by Sally Goldin, 28 October 2011
 *
 */

#include <stdio.h>
#include <sys/time.h>

/* Measure an interval in microseconds
 * Argument
 *   bStart      -  If true, record starting time
 *                  If false, return difference in microseconds
 * Return 0 if bStart is true, difference between
 * starting and ending calls in microseconds if bStart is false.
 */  
unsigned long recordTime(int bStart)
{
/* Structure definition from system header time.h */
/* A time value that is accurate to the nearest
   microsecond but also has a range of years.  */
//struct timeval
//  {
//    __time_t tv_sec;		/* Seconds.  */
//    __suseconds_t tv_usec;	/* Microseconds.  */
//  };
   static struct timeval startTime;  /* record starting time */
   struct timeval now;               /* time now */
   gettimeofday(&now,NULL);
   unsigned long intervalMS = 0;     /* interval in microseconds */ 
   if (bStart)
      {
      startTime = now;
      }
   else
      {
      long diffSeconds = now.tv_sec - startTime.tv_sec;
      long diffMicroSeconds = now.tv_usec - startTime.tv_usec;
      intervalMS = (diffSeconds*1000000 + diffMicroSeconds);
      } 
   return intervalMS;
}
