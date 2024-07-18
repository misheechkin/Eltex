#ifndef SOCIAL_NETWORK_H
#define SOCIAL_NETWORK_H

#define MAX_LENGTH_STRING 50

typedef struct SocialNetwork
{
    char profile_name[MAX_LENGTH_STRING];
    char link[MAX_LENGTH_STRING];
    char name[MAX_LENGTH_STRING];
} SocialNetwork;

void social_network_init(SocialNetwork *social_network, char *name, char *profile_name, char *link);

void social_network_print(const SocialNetwork* social_network);


#endif