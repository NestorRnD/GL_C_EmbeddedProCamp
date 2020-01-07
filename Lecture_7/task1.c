#include "pt.h"

#include <stdio.h>
#include <stdlib.h>

#define NTASKS 4
static int pt_task_flags=1;

static inline void RandNextTask(){
    pt_task_flags=rand()%NTASKS+1;
}

static PT_THREAD(myThread1(struct pt *pt))
{
  PT_BEGIN(pt);

  while(1) {
    PT_WAIT_UNTIL(pt, pt_task_flags == 1);
    printf("Now is running: Task 1.\n");

    RandNextTask();
  }
  PT_END(pt);
}

static PT_THREAD(myThread2(struct pt *pt))
{
  PT_BEGIN(pt);

  while(1) {
    PT_WAIT_UNTIL(pt, pt_task_flags == 2);
    printf("Now is running: Task 2.\n");

    RandNextTask();
  }
  PT_END(pt);
}

static PT_THREAD(myThread3(struct pt *pt))
{
  PT_BEGIN(pt);

  while(1) {
    PT_WAIT_UNTIL(pt, pt_task_flags == 3);
    printf("Now is running: Task 3.\n");

    RandNextTask();
  }
  PT_END(pt);
}

static PT_THREAD(myThread4(struct pt *pt))
{
  PT_BEGIN(pt);

  while(1) {
    PT_WAIT_UNTIL(pt, pt_task_flags == 4);
    printf("Now is running: Task 4.\n");

    RandNextTask();
  }
  PT_END(pt);
}

static struct pt pt1, pt2, pt3, pt4;
int
main(void)
{
  /* Initialize the protothread state variables with PT_INIT(). */
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
  PT_INIT(&pt4);

  /*
   * Then we schedule the protothreads by repeatedly calling their
   * protothread functions and passing a pointer to the protothread
   * state variables as arguments.
   */
  while(1) {
    myThread1(&pt1);
    myThread2(&pt2);
    myThread3(&pt3);
    myThread4(&pt4);
  }
}
