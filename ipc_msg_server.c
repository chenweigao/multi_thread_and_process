#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct my_msg_st {
    long int my_msg_type;
    char some_text[BUFSIZ];
};

int main()
{
    int msgid;
    struct my_msg_st some_data;
    
    msgid = msgget((key_t)1234, 0666|IPC_CREAT);
    if(msgid == -1)
    {
        fprintf(stderr, "message failed.\n");
        exit(EXIT_FAILURE);
    }
    
	printf("Waiting...\n");
    while(1)
    {
        if(msgrcv(msgid, (void*)&some_data, BUFSIZ, 0, 0 ) == -1)
        {
            fprintf(stderr, "megrcv failed");
            exit(EXIT_FAILURE);
        }
        printf("Received: %s \n", some_data.some_text);
    }
    return 0;
}
