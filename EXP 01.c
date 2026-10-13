/* DFA: strings over {a,b} that start with 'a' and end with 'a'
   States: q0 start, q1 = started with a, last char a (ACCEPT),
           q2 = started with a, last char b, qd = dead (started with b)  */
#include <stdio.h>
#include <string.h>

enum { Q0, Q1, Q2, QD };

int next(int s, char c) {
    switch (s) {
    case Q0: return c == 'a' ? Q1 : QD;
    case Q1: return c == 'a' ? Q1 : Q2;
    case Q2: return c == 'a' ? Q1 : Q2;
    default: return QD;
    }
}

int main(void) {
    char str[1000];
    printf("Enter a string over {a,b}: ");
    if (scanf("%999s", str) != 1) return 1;

    int s = Q0;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] != 'a' && str[i] != 'b') {
            printf("Invalid symbol '%c'. Alphabet is {a,b}.\n", str[i]);
            return 1;
        }
        s = next(s, str[i]);
    }
    printf("%s\n", s == Q1 ? "String ACCEPTED (starts and ends with a)"
                           : "String REJECTED");
    return 0;
}
