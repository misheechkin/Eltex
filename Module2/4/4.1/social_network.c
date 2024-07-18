#include <stdio.h>
#include "social_network.h"
#include <string.h>

void social_network_init(SocialNetwork *social_network, char *name, char *profile_name, char *link)
{
    if (social_network == NULL) return;
    if (name != NULL) {
        strcpy(social_network->name, name);
    }
    if (profile_name != NULL) {
        strcpy(social_network->profile_name, profile_name);
    }
    if (link != NULL) {
        strcpy(social_network->link, link);
    }
}

void social_network_print(const SocialNetwork* social_network){
    if(social_network!=NULL){
        printf("Название соц сети: %s\t", social_network->name);
        printf("Имя профиля: %s\t", social_network->profile_name);
        printf("Cсылка: %s\n", social_network->link);
    }
}