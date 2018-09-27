// From: admin\n
// Subject: hi\n
// Sender: admin\0
#include <stdio.h>
#include <string.h>


int main(void) {
    char str[100];
    // scanf("%s", str);
    // strcpy(str ,"From: admin\nSubject: hi\nSender: admin\0");

    fgets(str, 100, stdin);

    printf("out = %s", str);
    return 0;
}

