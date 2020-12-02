#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


struct message1
{
    long mesg_type;
    int mark;
};

struct message2
{
    long mesg_type;
    int marks[5];
    int grades[5];
};

int main()
{
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct message2 ci;
    
    struct message1 stud;
    pid_t pid = fork();
    if (pid == 0)
    {
        //Stud 1, 2 ,3
        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            //Stud 1

            msgrcv(msgid, &stud, sizeof(struct message1), (long)3, 0);
            printf("\nStudent 1 received: %d/50\n", stud.mark);
        }
        else
        {
            wait(NULL);
            pid_t pid3 = fork();
            if (pid3 == 0)
            {

                //Stud 2
                // struct message1 stud;
                msgrcv(msgid, &stud, sizeof(struct message1), (long)6, 0);
                printf("\nStudent 2 received: %d/50\n", stud.mark);
            }
            else
            {
                wait(NULL);
                //Stud 3
                // struct message1 stud;
                msgrcv(msgid, &stud, sizeof(struct message1), (long)9, 0);
                printf("\nStudent 3 received: %d/50\n", stud.mark);
            }
        }
    }
    else
    {
        wait(NULL);
        //Stud 4, 5 and TA
        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            //Stud 4
            // struct message1 stud;
            msgrcv(msgid, &stud, sizeof(struct message1), (long)12, 0);
            printf("\nStudent 4 received: %d/50\n", stud.mark);
        }
        else
        {
            wait(NULL);
            pid_t pid3 = fork();
            if (pid3 == 0)
            {
                //Stud 5
                // struct message1 stud;
                msgrcv(msgid, &stud, sizeof(struct message1), (long)15, 0);
                printf("\nStudent 5 received: %d/50\n", stud.mark);
            }
            else
            {
                wait(NULL);
                msgrcv(msgid, &ci, sizeof(struct message2), 10, 0);
                printf("\nTA has received the marks.\n");
                int avg = 0;
                for(int i = 0; i < 5; i++){
                    avg += ci.marks[i];
                    if(ci.marks[i] <= 50 && ci.marks[i] >= 40){
                        ci.grades[i] = 'S';
                    }
                    else if(ci.marks[i] <= 39 && ci.marks[i] >= 30){
                        ci.grades[i] = 'A';
                    }
                    else if(ci.marks[i] <= 29 && ci.marks[i] >= 20){
                        ci.grades[i] = 'B';
                    } 
                    else if(ci.marks[i] <= 19){
                        ci.grades[i] = 'E';
                    }
                }
                printf("\nThe Class Average is %f\n",avg/5.0);
                ci.mesg_type = 100;

                msgsnd(msgid, &ci, sizeof(struct message2), 0);
                //Stud 3
                // msgrcv(msgid, &stud, sizeof(struct message1), 18, 0);
                // printf("\nTA received: %d/50", stud.mark);
            }
        }
    }

    // msgctl(msgid, IPC_RMID, NULL);
}