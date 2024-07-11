#include <stdio.h>
#include <string.h>

#define MAX_LENGTH_STRING 50
#define MAX_SOCIAL_LIST 5
#define MAX_LENGTH_LIST 40

typedef struct WorkInfo
{
    char post[MAX_LENGTH_STRING];
    char workplace[MAX_LENGTH_STRING];
} WorkInfo;

typedef struct SocialNetwork
{
    char profileName[MAX_LENGTH_STRING];
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
    char phoneNumber[MAX_LENGTH_STRING];
    SocialNetwork socialNetworkList[MAX_SOCIAL_LIST];
    WorkInfo workInfo;
} Contact;

Contact CreateContact()
{
    Contact contact;
    printf("Введите имя: ");
    scanf("%s", contact.name);
    printf("Введите фамилию: ");
    scanf("%s", contact.surname);
    printf("Введите отечество: ");
    scanf("%s", contact.patronymic);
    return contact;
}

void PrintContactList(const Contact *contactList, int lengthList, int lengthSocialList)
{
    for (int i = 0; i < lengthList; i++)
    {
        printf("id: %d\t", contactList[i].id);
        printf("Имя: %s\t", contactList[i].name);
        printf("Фамилия: %s\t", contactList[i].surname);
        printf("Отчество: %s\n", contactList[i].patronymic);
    }
    if (lengthList == 0)
        printf("Телефоная книга пустая\n");
}

void AddContact(Contact *contactList, Contact contact, int *const lengthList)
{

    if (MAX_LENGTH_LIST == *lengthList)
    {
        printf("Телефоная книга переполнена! Нельзя добавить новый контакт\n");
        return;
    }
    if (*lengthList == 0)
    {
        contact.id = 1;
    }
    else
        contact.id = contactList[*lengthList - 1].id + 1;

    contactList[*lengthList] = contact;
    (*lengthList)++;
}

int FindIndexWithId(const Contact *contactList, int lengthList)
{
    int id = 0;
    printf("Введите id контакта: ");
    scanf("%d", &id);
    if (id < 1 || id > MAX_LENGTH_LIST)
    {
        printf("Введен неверный id!\n");
        return -1;
    }
    for (int i = 0; i < lengthList; i++)
    {
        if (contactList[i].id == id)
            return i;
    }
    printf("Такого id не существует!\n");
    return -1;
}

void DeleteContact(Contact *contactList, int *const lengthList)
{
    int index = FindIndexWithId(contactList, *lengthList);
    if (index != -1)
    {
        for (int j = index; j < MAX_LENGTH_LIST - 1; j++)
            contactList[j] = contactList[j + 1];
        (*lengthList)--;
    }
}

int PrintSocialNetwork(const SocialNetwork *socialNetworkList, int lengthSocialList)
{
    printf("Список соц сетей: \n");
    for (int i = 0; i < lengthSocialList; i++)
    {
        printf("Название соц сети: %s\t", socialNetworkList[i].name);
        printf("Имя профиля: %s\t", socialNetworkList[i].profileName);
        printf("Cсылка: %s\n", socialNetworkList[i].link);
    }
    if (lengthSocialList == 0)
    {
        printf("Спиcок пуст\n\n");
        return 0;
    }
    return 1;
}

SocialNetwork CreateSocialNetwork()
{
    SocialNetwork socialNetwork;
    printf("Введите название соц сети: ");
    scanf("%s", socialNetwork.name);
    printf("Введите имя профиля: ");
    scanf("%s", socialNetwork.profileName);
    printf("Введите ссылку: ");
    scanf("%s", socialNetwork.link);
    return socialNetwork;
}

void AddSocialNetwork(SocialNetwork *socialNetworkList, SocialNetwork socialNetwork, int *const lengthSocialList)
{
    if (MAX_SOCIAL_LIST == *lengthSocialList)
    {
        printf("Список соц сетей заполнен!\n");
        return;
    }
    socialNetworkList[*lengthSocialList] = socialNetwork;
    (*lengthSocialList)++;
}

void EditSocialNetwork(SocialNetwork *socialNetworkList, int *const lengthSocialList)
{
    if (*lengthSocialList == 0)
    {
        printf("Cписок соц сетей пуст! Введите данные чтобы добавить\n");
        AddSocialNetwork(socialNetworkList, CreateSocialNetwork(), lengthSocialList);
        return;
    }
    printf("Введите название соц сети которую хотите изменить\n");
    char tmp[MAX_LENGTH_STRING];
    scanf("%s", tmp);
    for (int i = 0; i < *lengthSocialList; i++)
    {
        if (strcmp(tmp, socialNetworkList[i].name) == 0)
        {
            int tmp2 = 0;
            printf("1 - Изменить название соц сети\n2 - Изменить имя профиля\n3 - Изменить ссылку\n");
            scanf("%d", &tmp2);
            printf("Введите новое значение: ");
            switch (tmp2)
            {
            case 1:
                scanf("%s", socialNetworkList[i].name);
                break;
            case 2:
                scanf("%s", socialNetworkList[i].profileName);
                break;
            case 3:
                scanf("%s", socialNetworkList[i].link);
                break;
            default:
                break;
            }
            return;
        }
    }
    printf("Соц сети с таким именем не сущетсвует\n");
}

void PrintContact(const Contact *contactList, int lengthList, int lengthSocialList)
{
    int index = FindIndexWithId(contactList, lengthList);
    if (index != -1)
    {
        printf("\nid: %d\t", contactList[index].id);
        printf("Имя: %s\t", contactList[index].name);
        printf("Фамилия: %s\t", contactList[index].surname);
        printf("Отчество: %s\n", contactList[index].patronymic);
        printf("Email: %s\n", contactList[index].email);
        printf("Телефон: %s\n", contactList[index].phoneNumber);
        printf("Место работы: %s\n", contactList[index].workInfo.workplace);
        printf("Должность: %s\n", contactList[index].workInfo.post);
        PrintSocialNetwork(contactList[index].socialNetworkList, lengthSocialList);
    }
}

void EditContact(Contact *contactList, int lengthList, int *lengthSocialList)
{
    int index = FindIndexWithId(contactList, lengthList);
    if (index != -1)
    {
        int tmp = 0;
        printf("1 - Изменить имя\n2 - Изменить фамилию\n3 - Изменить отчество\n4 - Изменить email\n5 - Изменить место работы\n6 - Изменить должность\n7 - Изменить социальные сети\n8 - Добавить социальные сети\n9 - Изменить номер телефона\n10 - Выйти\n");
        scanf("%d", &tmp);
        if (tmp != 7 && tmp != 8)
            printf("Введите новое значение: ");
        switch (tmp)
        {
        case 1:
            scanf("%s", contactList[index].name);
            break;
        case 2:
            scanf("%s", contactList[index].surname);
            break;
        case 3:
            scanf("%s", contactList[index].patronymic);
            break;
        case 4:
            scanf("%s", contactList[index].email);
            break;
        case 5:
            scanf("%s", contactList[index].workInfo.workplace);
            break;
        case 6:
            scanf("%s", contactList[index].workInfo.post);
            break;
        case 7:
            EditSocialNetwork(contactList[index].socialNetworkList, lengthSocialList);
            break;
        case 8:
            AddSocialNetwork(contactList[index].socialNetworkList, CreateSocialNetwork(), lengthSocialList);
            break;
        case 9:
            scanf("%s", contactList[index].phoneNumber);
            break;
        case 10:
            break;
        default:
            break;
        }
    }
}

int main()
{
    Contact contactList[MAX_LENGTH_LIST];
    int lengthList = 0;
    int lengthSocialList = 0;
    int tmp = 0;
    int flag = 1;
    while (flag)
    {
        printf("\n1 - Добавить контакт\t2 - Вывести список контактов\n3 - Удалить контакт\t4 - Редактировать контакт\n5 - Вывести дополнительную информацию о контакте\n6 - Выйти из телефоной книги\n");
        scanf("%d", &tmp);
        switch (tmp)
        {
        case 1:
            AddContact(contactList, CreateContact(), &lengthList);
            break;
        case 2:
            PrintContactList(contactList, lengthList, lengthSocialList);
            break;
        case 3:
            DeleteContact(contactList, &lengthList);
            break;
        case 4:
            EditContact(contactList, lengthList, &lengthSocialList);
            break;
        case 5:
            PrintContact(contactList, lengthList, lengthSocialList);
            break;
        case 6:
            flag = 0;
            break;
        default:
            break;
        }
    }
    return 0;
}
