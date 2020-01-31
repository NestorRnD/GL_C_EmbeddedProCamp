#include "pt.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#define NTASKS 4
static int pt_task_flag=0;

#define UNSETFLAG pt_task_flag=0

static inline void RandNextTask(){
    pt_task_flag=rand()%NTASKS+1;
}

static PT_THREAD(myThread1(struct pt *pt))
{
    PT_BEGIN(pt);
    while(1) {
	PT_WAIT_UNTIL(pt, pt_task_flag == 1);
	printf("Now is running: Task 1.\n");
	UNSETFLAG;
    }
    PT_END(pt);
}

static PT_THREAD(myThread2(struct pt *pt))
{
    PT_BEGIN(pt);
    while(1) {
	PT_WAIT_UNTIL(pt, pt_task_flag == 2);
	printf("Now is running: Task 2.\n");
	UNSETFLAG;
    }
    PT_END(pt);
}

static PT_THREAD(myThread3(struct pt *pt))
{
    PT_BEGIN(pt);
    while(1) {
	PT_WAIT_UNTIL(pt, pt_task_flag == 3);
	printf("Now is running: Task 3.\n");
	UNSETFLAG;
    }
    PT_END(pt);
}

static PT_THREAD(myThread4(struct pt *pt))
{
    PT_BEGIN(pt);
    while(1) {
	PT_WAIT_UNTIL(pt, pt_task_flag == 4);
	printf("Now is running: Task 4.\n");
	UNSETFLAG;
    }
    PT_END(pt);
}

static PT_THREAD(tasksDriver(struct pt *pt))
{
    static struct pt pt1, pt2, pt3, pt4;

    RandNextTask();

    PT_BEGIN(pt);

    PT_INIT(&pt1);
    PT_INIT(&pt2);
    PT_INIT(&pt3);
    PT_INIT(&pt4);

    PT_WAIT_THREAD(pt,
	myThread1(&pt1) &
	myThread2(&pt2) &
	myThread3(&pt3) &
	myThread4(&pt4)
	);

    PT_END(pt);
}

int main(void)
{
    struct pt ptTasksDriver;

    PT_INIT(&ptTasksDriver);

    while(PT_SCHEDULE(tasksDriver(&ptTasksDriver))) {
#ifdef _WIN32
	Sleep(0);
#else
	usleep(10);
#endif
    }
    return 0;
}
