#include <stdio.h>

int f(int x) {
	return x + 5;
}

int main() {
	int x;
	scanf("%i", &x);
	printf("%i", f(x));
}
