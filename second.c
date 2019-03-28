#include <stdio.h>

typedef unsigned long long booo;

booo schet (booo n)
{
    if (n != 0)
        return (booo)1 + (booo)schet (n/10);
    else
        return 0;
}

int main(){
    booo n;
    printf ("Vvedite chislo: ");
    scanf ("%llu", &n);
    printf ("Kolichestvo cifr v chisle: %llu", schet (n));
    return 0;
}
