#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>

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
    
    struct message1 studs[5];

    struct message2 CI;


    for (int i = 0; i < 5; i++)
    {
        printf("Enter marks for Student %d: ",i+1);
        studs[i].mark = 0;
        scanf(" %d", &studs[i].mark);
        studs[i].mesg_type = (long)(i+1)*3;
        CI.marks[i] = studs[i].mark;
        msgsnd(msgid, &studs[i], sizeof(struct message1), 0);
    }

    CI.mesg_type = 10;
    msgsnd(msgid, &CI, sizeof(struct message2), 0);

    struct message2 CI2;
    msgrcv(msgid, &CI2, sizeof(struct message2), 100, 0);
    for (int i = 0; i < 5; i++){
        printf("\nGrade for Student %d: %c\n", i+1, CI2.grades[i]);
    }

    msgctl(msgid, IPC_RMID, NULL);
    printf("\nMessage queue terminated. Process complete.\n");

}