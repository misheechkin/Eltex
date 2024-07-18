#ifndef WORK_INFO_H
#define WORK_INFO_H

#define MAX_LENGTH_STRING 40

typedef struct WorkInfo
{
    char post[MAX_LENGTH_STRING];
    char workplace[MAX_LENGTH_STRING];
} WorkInfo;

void work_info_init(WorkInfo *work_info, char *workplace, char *post);

void work_info_print(WorkInfo* work_info);

#endif
