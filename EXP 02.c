/* CFG membership check by recursive descent
       S -> 0 A 1
       A -> 0 A | 1 A | epsilon
   Language: all binary strings that start with 0 and end with 1 (length >= 2).
   A can generate any binary string, so after consuming the leading 0 the
   parser lets A consume symbols and then requires the last symbol to be 1;
   A must therefore leave exactly one character '1' for S to match. */
#include <stdio.h>
#include <string.h>

static const char *in;   /* input string */
static size_t pos, len;

/* A -> 0A | 1A | epsilon  : consume symbols but keep the final one for S */
int A(void) {
    if (pos < len - 1 && (in[pos] == '0' || in[pos] == '1')) {
        pos++;           /* A -> 0A or A -> 1A */
        return A();
    }
    return 1;            /* A -> epsilon */
}

int S(void) {
    if (len < 2 || in[pos] != '0') return 0;   /* S -> 0 ...  */
    pos++;
    if (!A()) return 0;
    if (pos < len && in[pos] == '1') { pos++; return 1; }  /* ... 1 */
    return 0;
}

int main(void) {
    char str[1000];
    printf("Enter a string over {0,1}: ");
    if (scanf("%999s", str) != 1) return 1;
    for (size_t i = 0; str[i]; i++)
        if (str[i] != '0' && str[i] != '1') {
            printf("Invalid symbol '%c'.\n", str[i]);
            return 1;
        }
    in = str; len = strlen(str); pos = 0;
    if (S() && pos == len) printf("String BELONGS to the language of the CFG\n");
    else                   printf("String does NOT belong to the language of the CFG\n");
    return 0;
}
