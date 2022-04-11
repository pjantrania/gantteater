#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "task.h"
#include "chart.h"

struct Chart* createChartWithTasks(time_t startDate, time_t endDate, uint32_t taskCount, struct Task* tasks);

struct Chart* createEmptyChart(time_t startDate, time_t endDate) {

  struct Task* emptyTasksList = (struct Task*)calloc(CHART_MAX_TASKS, sizeof(struct Task));
  return createChartWithTasks(startDate, endDate, 0, emptyTasksList);
}

struct Chart* createChartWithTasks(time_t startDate, time_t endDate, uint32_t taskCount, struct Task* tasks) {
  struct Chart* chart = (struct Chart*)calloc(1, sizeof(struct Chart));
  chart->startDate = startDate;
  chart->endDate = endDate;
  chart->taskCount = taskCount;
  chart->tasks = tasks;

  return chart;
}

void updateChartTimes(struct Chart* chart, time_t startDate, time_t endDate) {
  chart->startDate = startDate;
  chart->endDate = endDate;
}

void addChartTask(struct Chart* chart, struct Task* task) {
  if (chart->taskCount >= CHART_MAX_TASKS) {
    fprintf(stderr, "Chart already has %d elements & is full!", CHART_MAX_TASKS);
    return;
  }

  memcpy(&chart->tasks[chart->taskCount++], task, sizeof(struct Task));
  return;
}

void destroyChart(struct Chart* chart) {
  free(chart->tasks);
  free(chart);
  return;
}
