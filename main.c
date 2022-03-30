#include <stdio.h>
#include <time.h>


struct Task {
  char* title;
  time_t start_date;
  time_t end_date;
};

void printTask(struct Task* task, struct tm* chartStartDate, struct tm* chartEndDate) {
  printf("|%s|", task->title);
  

  
  //                 |03/22|03/23|03/24|03/25| 
  // This is my task |     |/////|/////|     |
  // This is task    |/////|/////|/////|/////|

}

int getDateDifference(time_t laterDate, time_t earlierDate) {
  time_t d = (time_t)difftime(laterDate, earlierDate);
  return gmtime(&d)->tm_yday;
}

int main(int argc, char** argv) {
  time_t currentTime  = 1648607369;
  time_t previousTime = 1648175364;
  printf("%d", getDateDifference(currentTime, previousTime));
  printf("hi, sup\n");
  return 0;
}
