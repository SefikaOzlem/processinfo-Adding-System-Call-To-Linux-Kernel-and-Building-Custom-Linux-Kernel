#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        long int sysId = syscall(335, 0, -1);
        printf("System call sys_file returned %ld\n", sysId);
    }

    else if (argc == 2)
    {
        if (strcmp(argv[1], "-all") == 0)
        {
            long int sysId = syscall(335, 1, -1);
            printf("System call sys_file returned %ld\n", sysId);
        }
    }

    else if (argc == 3)
    {
        int three;
        three = atoi(argv[2]);
        if (strcmp(argv[1], "-p") == 0)
        {
            long int sysId = syscall(335, 2, three);
            printf("System call sys_file returned %ld\n", sysId);
        }
        else if (strcmp(argv[1], "-k") == 0)
        {
            long int sysId = syscall(335, 3, three);
            printf("System call sys_file returned %ld\n", sysId);
        }
    }
    else
    {
        printf("Wrong entry input");
    }
    return 0;
}
