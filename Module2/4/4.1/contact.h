#ifndef CONTACT_H_
#define CONTACT_H_

#define MAX_LENGTH_STRING 50
#define MAX_SOCIAL_LIST 5


typedef struct WorkInfo
{
    char post[MAX_LENGTH_STRING];
    char workplace[MAX_LENGTH_STRING];
} WorkInfo;

typedef struct SocialNetwork
{
    char profile_name[MAX_LENGTH_STRING];
    char link[MAX_LENGTH_STRING];
    char name[MAX_LENGTH_STRING];
} SocialNetwork;

typedef struct Contact
{
    int id;
    char name[MAX_LENGTH_STRING];
    char surname[MAX_LENGTH_STRING];
    char patronymic[MAX_LENGTH_STRING];
    char email[MAX_LENGTH_STRING];
    char phone_number[MAX_LENGTH_STRING];
    SocialNetwork social_network_list[MAX_SOCIAL_LIST];
    WorkInfo work_info;
} Contact;

#endif // CONTACT_H_