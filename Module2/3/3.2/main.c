#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t getSubnet(char *ip_gateway, char *ip_mask)
{
    uint32_t address = 0;
    char *ptr;
    for (int i = 3; i > -1; i--)
    {
        uint8_t actet = strtoul(ip_gateway, &ptr, 10);
        ip_gateway = ++ptr;
        uint8_t actet_mask = strtoul(ip_mask, &ptr, 10);
        ip_mask = ++ptr;
        address |= (actet & actet_mask) << (8 * i);
    }
    return address;
}

int CompareSubnet(uint32_t ip_subnet1, uint32_t ip_subnet2)
{
    return ip_subnet1 == ip_subnet2;
}



int main()
{
    uint32_t a =getSubnet("001.108.004.40", "255.255.255.0");
    uint32_t b =getSubnet("192.108.0.250", "255.255.255.0");
     if (a,b)
    {
        printf("da");
    }
    else
        printf("no");
    return 0;
}