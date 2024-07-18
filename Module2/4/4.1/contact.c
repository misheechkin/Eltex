#include <string.h>
#include "contact.h"

void contact_init(Contact *contact, Person person, char *email, char *phone_number, SocialNetwork social_network, WorkInfo work_info)
{
    if (contact == NULL)
        return;
    contact->person = person;
    if (email != NULL) {
        strcpy(contact->email,email);
    }
    if (phone_number != NULL) {
        strcpy(contact->phone_number,phone_number);
    }
    contact->social_network_list[0]=social_network;
    contact->work_info=work_info;

}

void print_contact(const Contact *contact, int length_social_list)
{
    if (contact == NULL)
        return;
   printf("Id: %d\t", contact->id);
   person_print(&(contact->person));
   printf("Email: %s\t", contact->email);
   printf("Номер: %s\t", contact->phone_number);
   for (int i = 0; i < length_social_list; i++) {
    social_network_print(&(contact->social_network_list[i]));
   }
   work_info_print(&(contact->work_info));
   
}


