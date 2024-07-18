#include <string.h>
#include "work_info.h"

void work_info_init(WorkInfo *work_info, char *workplace, char *post)
{
    if (work_info == NULL) return;
    if (workplace != NULL) {
        strcpy(work_info->workplace, workplace);
    }
    if (post != NULL) {
        strcpy(work_info->post, post);
    }
}

void work_info_print(WorkInfo* work_info){
    if(work_info!=NULL){
        printf("Место работы: %s\t", work_info->workplace);
        printf("Должность: %s\t", work_info->post);
    }
}