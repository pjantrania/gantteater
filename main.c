#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "chart.h"
#include "task.h"
#include "printer.h"

#define TASK_COUNT 10


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
