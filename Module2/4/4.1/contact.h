#ifndef CONTACT_H
#define CONTACT_H

#include "work_info.h"
#include "social_network.h"
#include "person.h"

#define MAX_LENGTH_STRING 50
#define MAX_SOCIAL_LIST 5

typedef struct Contact
{
    int id;
    Person person;
    char email[MAX_LENGTH_STRING];
    char phone_number[MAX_LENGTH_STRING];
    SocialNetwork social_network_list[MAX_SOCIAL_LIST];
    WorkInfo work_info;
} Contact;

void contact_init(Contact *contact, Person person, char *email, char *phone_number, SocialNetwork social_network, WorkInfo work_info);

void print_contact(const Contact *contact, int length_social_list);


#endif