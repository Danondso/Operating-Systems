/* formatconvert.c In-memory format conversion using sprintf and sscanf. */
#include <stdio.h>

int main()
{
float x = 7.2;

// From binary to text. Output to a C-style string
char s[100];
sprintf(s, "The square of 7.2 is %f\n", x*x);
printf(s);

// From text to binary. Input from a C-style string.
char *t = "1.136 123";
double y;
int i;
sscanf(t, "%lf %d", &y, &i);
printf("y = %f i = %d\n", y, i);
return 0;
}
 
