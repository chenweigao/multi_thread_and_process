#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>

#define FIFO_FILE "MYFIFO"

int main()
{
    FILE *fp;
    char readbuf[80];

    if((mkfifo(FIFO_FILE, 0666) < 0))
    {
        printf("mkfido: File Exists.\n");
    }
    else
    {
        printf("mkfifo: succssed.\n");
    }

    printf("Server is waiting...\n");

    while(1)
    {
        if((fp = fopen(FIFO_FILE, "r")) == NULL)
        {
            printf("fopem failed.\n");
            return -1;
        }
        fgets(readbuf, 80, fp);
        printf("Received string: %s\n", readbuf);
        fclose(fp);
    }
}
