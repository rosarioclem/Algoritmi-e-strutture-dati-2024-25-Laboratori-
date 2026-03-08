#include <stdio.h>

int gcd(int a, int b);

int main(void) {

    int x, y , mcd;
    printf("Inserisci due numeri di cui vuoi calcolare il massimo comune divisore:\n");
    scanf("%d %d", &x, &y);

    if(x > y) mcd = gcd(x, y);
    else mcd = gcd(y, x);

    printf("Ecco il massimo comune divisore: %d\n", mcd);

}

int gcd(int a, int b){

    int temp;
    if(a == b) return a;

    if (b > a){
        temp = a; a = b; b = temp;
    }

    if(a % 2 == 0 && b % 2 == 0){
        return 2 * gcd(a/2, b/2);
    }
    else if(a % 2 == 1 && b % 2 == 0){
        return gcd(a, b/2);
    }
    else if(a % 2 == 0 && b % 2 == 1){
        return gcd(a/2, b);
    }
    else if(a % 2 == 1 && b % 2 == 1){
        return gcd((a - b)/2, b);
    }

    if(a == 1) return b;
    if(b == 1) return a;

}