#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BLOCK_WIDTH 7
#define TASK_COUNT 10

struct Task {
  char title[21];
  time_t start_date;
  time_t end_date;
};


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

void updateSettings(time_t* chartStartTime, time_t* chartEndTime) {
  printf("\n> Chart Start Time: ");
  int newChartStartTime;
  scanf("%d", &newChartStartTime);
  *chartStartTime = newChartStartTime;
  printf("\n> Chart End Time: ");
  int newChartEndTime;
  scanf("%d", &newChartEndTime);
  *chartEndTime = newChartEndTime;
}

void addTask(struct Task* tasks, int currentTaskCount) {
  struct Task* nextTask = &tasks[currentTaskCount];
  printf("\n> Task Title: ");
  char taskTitle[21];
  scanf("%20s", taskTitle);
  strncpy(nextTask->title, taskTitle, 20);
  
  printf("\n> Task Start Time: ");
  int newTaskStartTime;
  scanf("%d", &newTaskStartTime);
  nextTask->start_date = newTaskStartTime;

  printf("\n> Task End Time: ");
  int newTaskEndTime;
  scanf("%d", &newTaskEndTime);
  nextTask->end_date = newTaskEndTime;
}

int main(int argc, char** argv) {
  // initialize data & enter repl
  printf("welcome to gantteater. give us your gantts.\n\n");  
  time_t chartStartTime = 1647743364 + (2 * 24 * 60 * 60);
  time_t taskEndTime  = 1648607369;
  time_t taskStartTime = 1648175364;
  time_t chartEndTime = 1648866564;
  
  struct Task* tasks = (struct Task *) calloc(TASK_COUNT, sizeof(struct Task));
  strcpy(tasks[0].title, "first actual task");
  tasks[0].start_date = taskStartTime;
  tasks[0].end_date = taskEndTime;

  // repl process
  while(1) {
    // show current gantt
    printDates(chartStartTime, chartEndTime);
    int currentTaskCount = 0;
    for(int i = 0; i < TASK_COUNT; i++) {
      if (strlen(tasks[i].title) != 0) {
	++currentTaskCount;
	printTask(&tasks[i], chartStartTime, chartEndTime);
      }
    }

    // listen for command
    printf("\n> ");
    char command[100];
    scanf("%s", command);
    printf("> you entered: %s\n", command);

    // process command
    int exit = strcmp(command, "exit");
    if (exit == 0) {
      printf("goodbye!\n");
      break;
    }

    int settings = strcmp(command, "settings");
    if (settings == 0) {
      updateSettings(&chartStartTime, &chartEndTime);
    }

    int addTaskInput = strcmp(command, "add-task");
    if (addTaskInput == 0) {
      addTask(tasks, currentTaskCount);
    }
  }

  free(tasks);
  return 0;
}
