#include <stdio.h>

#define MAX_LENGHT_STRING 20
#define MAX_SOCIAL_LIST 5
#define MAX_LENGHT_LIST 100

Person contactList[MAX_LENGHT_LIST];
int counter;

typedef struct {
    char profileName [MAX_LENGHT_STRING];
    char link [MAX_LENGHT_STRING];
    char name[MAX_LENGHT_STRING];
}SocialNetwork;

typedef struct {
    char post [MAX_LENGHT_STRING];
    char workplace [MAX_LENGHT_STRING];
}WorkInfo;


typedef struct {
    int id;
    char name [MAX_LENGHT_STRING];
    char surname [MAX_LENGHT_STRING];
    char patronymic [MAX_LENGHT_STRING];
    char mail [MAX_LENGHT_STRING];
    SocialNetwork socialNetworkList [MAX_SOCIAL_LIST];
    WorkInfo workInfo;
}Person;