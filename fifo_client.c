#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO_FILE "MYFIFO"

int main()
{   
    while(1) {
    FILE *fp;
    char *client_text;
    printf("some text you send to server:\n");
    // gets(client_text); gets() should not be used!
    fgets(client_text, 80, stdin);

    if((fp = fopen(FIFO_FILE, "w")) == NULL)
    {
        printf("fopen: failed to open FIFO!\n");
        return -1;
    }
    fputs(client_text, fp);
    fclose(fp);
    }
    
    return 0;
}