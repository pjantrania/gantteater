#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BLOCK_WIDTH 7

struct Task {
  char* title;
  time_t start_date;
  time_t end_date;
};

time_t parseDate(char* yyyyMmDdDate) {
  char month[2];
  char day[2];
  char year[4];
  sscanf(yyyyMmDdDate, "%[^-]-%[^-]-%s", year, month, day);
  printf("year: %s, month: %s, day: %s\n", year, month, day);
  return 0;
}

int getDateDifference(time_t laterDate, time_t earlierDate) {
  time_t d = (time_t)difftime(laterDate, earlierDate);
  if (d < 0) {
    return -1;
  }
  return gmtime(&d)->tm_yday;
}

void printBlocks(int count, char filler, int inclusive) {
  if (inclusive) {
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

void printTask(struct Task* task, time_t chartStartDate, time_t chartEndDate) {
  printf("| %-19s|", task->title);
  int initialDateDifference = getDateDifference(task->start_date, chartStartDate);
  printBlocks(initialDateDifference, ' ', 0);
  
  time_t earlierEndDate = (task->end_date <= chartEndDate)? task->end_date : chartEndDate;
  int taskDateDifference = getDateDifference(earlierEndDate, task->start_date);
  printBlocks(taskDateDifference, '/', 1);
  
  int endDateDifference = getDateDifference(chartEndDate, task->end_date);
  printBlocks(endDateDifference, ' ', 1);

  printf("\n");
  //                 |03/22|03/23|03/24|03/25| 
  // This is my task |     |/////|/////|     |
  // This is task    |/////|/////|/////|/////|

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

int main(int argc, char** argv) {
  time_t chartStartTime = 1647743364 + (2 * 24 * 60 * 60);
  time_t taskEndTime  = 1648607369;
  time_t taskStartTime = 1648175364;
  time_t chartEndTime = 1648866564;
  
  /*  printf("chart start: %s\n", asctime(gmtime(&chartStartTime)));
  printf("task start: %s\n", asctime(gmtime(&taskStartTime)));
  printf("task end: %s\n", asctime(gmtime(&taskEndTime)));
  printf("chart end: %s\n", asctime(gmtime(&chartEndTime)));*/

  printDates(chartStartTime, chartEndTime);
  struct Task firstTask;
  firstTask.title = "first actual task";
  firstTask.start_date = taskStartTime;
  firstTask.end_date = taskEndTime;
  
  printTask(&firstTask, chartStartTime, chartEndTime);
  return 0;
}
