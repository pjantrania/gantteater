#ifndef CHART_H
#define CHART_H

#include <stdint.h>
#include <time.h>
#include "task.h"

#define CHART_MAX_TASKS 10

struct Chart {
  time_t startDate;
  time_t endDate;
  uint32_t taskCount;
  struct Task* tasks;
};

struct Chart* createEmptyChart(time_t startDate, time_t endDate);

void updateChartTimes(struct Chart* chart, time_t startDate, time_t endDate);

void addChartTask(struct Chart* chart, struct Task* task);

void destroyChart(struct Chart* chart);
#endif
