#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint32_t ConvertToUInt32(char *ip)
{
    uint32_t address = 0;
    char *ptr;
    for (int i = 3; i > -1; i--)
    {
        uint8_t actet = strtoul(ip, &ptr, 10);
        ip = ++ptr;
        address |= actet << (8 * i);
    }
    return address;
}

uint32_t GetSubnet(uint32_t ip, uint32_t mask)
{
    return (ip & mask);
}

int CompareSubnets(uint32_t ip_subnet1, uint32_t ip_subnet2)
{
    return ip_subnet1 == ip_subnet2;
}

int Start(char *ip_gateway, char *ip_mask, int numbers_packet)
{
    int counter = 0;
    uint32_t mask = ConvertToInt32(ip_mask);
    uint32_t subnet = GetSubnet(ConvertToUInt32(ip_gateway), mask);
    for (int i = 0; i < numbers_packet; i++)
    {
         uint32_t ip_destination = rand() << 16;
        if (CompareSubnets(subnet, GetSubnet(ip_destination, mask)))
            counter++;
    }
    return counter;
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (argc != 4)
    {
        printf("Не правильно введены аргументы, введите <IP_адресс> <маска> <количество пакетов>\n");
        return 1;
    }
   
    int numbers_package = strtoul(argv[3], NULL, 10);
    if (numbers_package != 0)
    {
        int same_subnet_count = Start(argv[1], argv[2], numbers_package);
        int different_subnet_count = numbers_package - same_subnet_count;
        printf("Количество адресов подсети шлюза: %d\n", same_subnet_count);
        printf("Количество адресов других сетей: %d\n", different_subnet_count);
        printf("Процентов: %.1f \% \n", (float)same_subnet_count *100 / numbers_package);
    }

    return 0;
}