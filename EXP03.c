/* DFA: strings over {0,1} that start with 0 and end with 1
   States: q0 start, q1 = started with 0, last char 0,
           q2 = started with 0, last char 1 (ACCEPT), qd = dead (started with 1) */
#include <stdio.h>
#include <string.h>

enum { Q0, Q1, Q2, QD };

int next(int s, char c) {
    switch (s) {
    case Q0: return c == '0' ? Q1 : QD;
    case Q1: return c == '0' ? Q1 : Q2;
    case Q2: return c == '0' ? Q1 : Q2;
    default: return QD;
    }
}

int main(void) {
    char str[1000];
    printf("Enter a binary string: ");
    if (scanf("%999s", str) != 1) return 1;

    int s = Q0;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] != '0' && str[i] != '1') {
            printf("Invalid symbol '%c'. Alphabet is {0,1}.\n", str[i]);
            return 1;
        }
        s = next(s, str[i]);
    }
    printf("%s\n", s == Q2 ? "String ACCEPTED (starts with 0 and ends with 1)"
                           : "String REJECTED");
    return 0;
}
