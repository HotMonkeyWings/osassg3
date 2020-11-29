#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main(){
    key_t key[5];
    int msg_id[5];

    for(int i = 1; i < 6; i++){
        key[i-1] = ftok("progfile", i);
        int msg_id_temp = msgget(key[i-1], 0666 | IPC_CREAT);
        msgctl(msg_id_temp, IPC_RMID, NULL);
    }
    
    pid_t pid;
    pid = fork();
    if (pid == 0){
        //Child 1, 2, 3
        pid_t pidd = fork();
        if (pidd == 0){
            //Child 1, 2
            pid_t piddd = fork();
            if(piddd == 0){
                //Child 1
                msg_id[0] = msgget(key[0], 0666 | IPC_CREAT);
                msgrcv(msg_id[0], &message, sizeof(message), 1, 0);
                printf("Data received is : %s \n", message.mesg_text);

                msgctl(msg_id[0], IPC_RMID, NULL);
            } else{
                //Child 2
                wait(NULL);
                msg_id[1] = msgget(key[1], 0666 | IPC_CREAT);
                msgrcv(msg_id[1], &message, sizeof(message), 1, 0);
                printf("Data received is : %s \n", message.mesg_text);

                msgctl(msg_id[1], IPC_RMID, NULL);
            }
        } else{
            //Child 3
            wait(NULL);
            msg_id[2] = msgget(key[2], 0666 | IPC_CREAT);
            msgrcv(msg_id[2], &message, sizeof(message), 1, 0);
            printf("Data received is : %s \n", message.mesg_text);

            msgctl(msg_id[2], IPC_RMID, NULL);
        }

    } else {
        wait(NULL);
        //Child 4 and 5
        pid_t pidd = fork();
        if (pidd == 0){
            //Child 4
            msg_id[3] = msgget(key[3], 0666 | IPC_CREAT);
            msgrcv(msg_id[3], &message, sizeof(message), 1, 0);
            printf("Data received is : %s \n", message.mesg_text);

            msgctl(msg_id[3], IPC_RMID, NULL);
        } else {
            wait(NULL);
            //Child 5
            msg_id[4] = msgget(key[4], 0666 | IPC_CREAT);
            msgrcv(msg_id[4], &message, sizeof(message), 1, 0);
            printf("Data received is : %s \n", message.mesg_text);

            msgctl(msg_id[4], IPC_RMID, NULL);
        }
    }


    // printf("Data received is : %s \n", message.mesg_text);

    // msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}