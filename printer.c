#include "printer.h"
#include "task.h"

int getDateDifference(time_t laterDate, time_t earlierDate) {
  time_t d = (time_t)difftime(laterDate, earlierDate);
  if (d < 0) {
    return -1;
  }
  return gmtime(&d)->tm_yday;
}

void printBlocks(int count, char filler, int inclusive) {
  if (inclusive && count > 0) {
    count++;
  }

  if (count > 0) {
    for (int i = 0; i < count; ++i) {
      for (int j = 0; j < BLOCK_WIDTH; ++j) {
	printf("%c", filler);
      }
      printf("|");
    }
  }
}

// Here's what we're after:
//                 |03/22|03/23|03/24|03/25| 
// This is my task |     |/////|/////|     |
// This is task    |/////|/////|/////|/////|
void printTask(struct Task* task, time_t chartStartDate, time_t chartEndDate) {
  printf("| %-19s|", task->title);
  int initialDateDifference = getDateDifference(task->start_date, chartStartDate);
  printBlocks(initialDateDifference, ' ', 0);
  
  time_t earlierEndDate = task->end_date <= chartEndDate ? task->end_date : chartEndDate;
  time_t laterStartDate = chartStartDate <= task->start_date ? task->start_date : chartStartDate;
  int taskDateDifference = getDateDifference(earlierEndDate, laterStartDate);
  printBlocks(taskDateDifference, '/', 1);
  
  int endDateDifference = getDateDifference(chartEndDate, task->end_date);
  printBlocks(endDateDifference, ' ', 1);
  
  printf("\n");

}

void printDate(time_t time) {
  struct tm* dateTm = gmtime(&time);
  printf(" %02d/%02d |", dateTm->tm_mon + 1, dateTm->tm_mday);
}

void printDates(time_t chartStartTime, time_t chartEndTime) {
  int numberOfDays = getDateDifference(chartEndTime, chartStartTime);
  printf("|%20s|", "");

  for (int i = 0; i <= numberOfDays; ++i) {
    printDate(chartStartTime + (i * 24 * 60 * 60));
  }
  printf("\n");
}
