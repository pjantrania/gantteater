#ifndef PRINTER_H
#define PRINTER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "task.h"

#define BLOCK_WIDTH 7

int getDateDifference(time_t laterDate, time_t earlierDate);
void printBlocks(int count, char filler, int inclusive);
void printTask(struct Task* task, time_t chartStartDate, time_t chartEndDate);
void printDate(time_t time);
void printDates(time_t chartStartTime, time_t chartEndTime);


#endif
