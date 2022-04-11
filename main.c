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

struct Task* addTask() {
  struct Task* nextTask = (struct Task*)calloc(1, sizeof(struct Task));
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
  return nextTask;
}

int main(int argc, char** argv) {
  // initialize data & enter repl
  printf("welcome to gantteater. give us your gantts.\n\n");  
  time_t chartStartTime = 1647743364 + (2 * 24 * 60 * 60);
  time_t taskEndTime  = 1648607369;
  time_t taskStartTime = 1648175364;
  time_t chartEndTime = 1648866564;

  struct Chart* chart = createEmptyChart(chartStartTime, chartEndTime);
  struct Task firstTask;
  strcpy(firstTask.title, "first actual task");
  firstTask.start_date = taskStartTime;
  firstTask.end_date = taskEndTime;
  addChartTask(chart, &firstTask);

  // repl process
  while(1) {
    // show current gantt
    printDates(chart->startDate, chart->endDate);
    int currentTaskCount = 0;
    for(int i = 0; i < chart->taskCount; i++) {
      struct Task* currentTask = &chart->tasks[i];
      if (strlen(currentTask->title) != 0) {
	++currentTaskCount;
	printTask(currentTask, chartStartTime, chartEndTime);
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
      updateChartTimes(chart, chartStartTime, chartEndTime);
    }

    int addTaskInput = strcmp(command, "add-task");
    if (addTaskInput == 0) {
      struct Task* newTask = addTask();
      addChartTask(chart, newTask);
      free(newTask);
    }
  }

  destroyChart(chart);
  return 0;
}
