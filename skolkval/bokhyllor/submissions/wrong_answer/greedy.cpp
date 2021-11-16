#include <cstdio>

int hyllstorlek;

void rek(int hyllor, int platser, int left[]) {
    if (left[0] + left[1] + left[2] == 0) {
        printf("%d\n", hyllor);
        return;
    }
    for (int i = 2; i >= 0; --i) {
        if (left[i] && (i + 1) <= platser) {
            left[i]--;
            rek(hyllor, platser - i - 1, left);
            return;
        }
    }
    rek(hyllor + 1, hyllstorlek, left);
}

int main() {
	int size[3];
	scanf("%d", size);
	scanf("%d", size+1);
	scanf("%d", size+2);
	scanf("%d", &hyllstorlek);
	
	//Anropar rekursionsfunktionen för det första fallet, det vill säga vi har en hylla och alla böcker är kvar.
	rek(1, hyllstorlek, size);
	return 0;
}
