#include <stdio.h>
#include <stdlib.h>




int main(){
    int tmp = 0;
   for(;;) {
        printf("\n1 - Добавить контакт\t2 - Вывести список контактов\n3 - Удалить контакт\t4 - Редактировать контакт\n5 - Вывести дополнительную информацию о контакте\n6 - Выйти из телефоной книги\n");
        scanf("%d", &tmp);
        switch (tmp)
        {
        case 1:
          
            break;
        case 2:
          
            break;
        case 3:
           
            break;
        case 4:
            
            break;
        case 5:
            break;
        case 6:
           
            return EXIT_SUCCESS;
            break;
        default:
            break;
        }
    }
    return EXIT_SUCCESS;
}