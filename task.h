#ifndef TASK_H
#define TASK_H

struct Task {
  char title[21];
  time_t start_date;
  time_t end_date;
};

#endif
