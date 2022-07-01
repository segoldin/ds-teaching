/* 
 * timeFunctions.h
 * 
 * Declaration of functions for measuring time in programs
 *
 * Created by Sally Goldin, 28 October 2011
 *
 */
#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H

/* Measure an interval in microseconds
 * Argument
 *   bStart      -  If true, record starting time
 *                  If false, return difference in microseconds
 * Return 0 if bStart is true, difference between
 * starting and ending calls in microseconds if bStart is false.
 */  
unsigned long recordTime(int bStart);

#endif
