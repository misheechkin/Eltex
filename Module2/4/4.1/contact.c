#include <stdio.h>
#include <string.h>
#include "contact.h"

void contact_init(Contact *contact, Person person)
{
    if (contact == NULL)
        return;
    contact->person = person;
    memset(contact->email,0,MAX_LENGTH_STRING);
    memset(contact->phone_number,0,MAX_LENGTH_STRING);
    memset(contact->social_network_list,0,MAX_SOCIAL_LIST);
    memset(contact->work_info.post,0,MAX_LENGTH_STRING);
    memset(contact->work_info.workplace,0,MAX_LENGTH_STRING);
}



void print_contact(const Contact *contact)
{
    if (contact == NULL)
        return;
   printf("Id: %d\t", contact->id);
   person_print(&(contact->person));
   printf("Email: %s\t", contact->email);
   printf("Номер: %s\t", contact->phone_number);
   work_info_print(&(contact->work_info));
   
}

int contact_cmp(Contact contact1, Contact contact2)
{
    int tmp = strcmp(contact1.person.name,contact2.person.name);
    if(tmp) 
        return 1;
    if(tmp==0)
        return 0;
    return -1;
}
  
