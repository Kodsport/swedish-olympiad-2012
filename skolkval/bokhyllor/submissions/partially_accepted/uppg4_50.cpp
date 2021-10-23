#include <cstdio>
#include <cassert>

int hyllstorlek;
int best_result = 99999999;

//Egentligen ska det bara behövas [61][280][21][21][21], men ett testexempel hade 30 små böcker trots att maxantalet var 20 - så jag ändrade till 31
// för säkerhets skull. Om något går snett pga detta lägger jag över ansvaret för detta till 100% på den som gjorde misstaget.
bool table[61][180][31][31][31];

//Behandlar fallet när man hittills har hyllor antal hyllor, platser platser kvar i den senaste samt left[0] små böcker,
// left[1] mellanstora böcker och left[2] stora böcker kvar.
void rek(int hyllor, int platser, int left[]) {
	//Om detta fall redan har behandlats behöver inget göras.
	if(table[hyllor][platser][left[0]][left[1]][left[2]])
		return;
	
	bool done = true; //Om done är true efter for-loopen så har alla böcker placerats.
	
	//Vilken bok ska placeras härnäst? Testar alla möjliga alternativ.
	for(int i=0; i<3; i++) {
		if(left[i] == 0) { //Om det är slut av den här bokstorleken, gå vidare till nästa.
			continue;
		}
		if(left[i] > 0)
			done = false;
		
		if(platser - (i+1) >= 0) { //Om den nuvarande hyllan räcker till.
			//Kopierar arrayen left (som beskriver hur många böcker av respektive sort som finns kvar), och ändra så det finns en
			// mindre kvar av den boken vi ska placera nu.
			int newleft[3];
			for(int j=0;j<3; j++) {
				if(j == i)
					newleft[j] = left[j]-1;
				else
					newleft[j] = left[j];
			}
			
			rek(hyllor, platser - (i+1), newleft); //Anropar den här funktionen för det nya fallet som vi nu har fått.
		} else {
			//Motsvarande, fast skapar en ny hylla också.
			int newleft[3];
			for(int j=0;j<3; j++) {
				if(j == i)
					newleft[j] = left[j]-1;
				else
					newleft[j] = left[j];
			}
			
			rek(hyllor+1, hyllstorlek - (i+1), newleft);
		}
	}
	
	//Det här fallet har nu behandlats och behöver inte behandlas igen.
	table[hyllor][platser][left[0]][left[1]][left[2]] = true;
	
	//Om alla böcker har placerats, kolla om det är bättre än det bästa resultatet hittills, och ersätt isåfall det.
	if(done) {
		if(hyllor < best_result) {
			best_result = hyllor;
		}
	}
}

int main() {
	int size[3];
	scanf("%d", size);
	scanf("%d", size+1);
	scanf("%d", size+2);
	scanf("%d", &hyllstorlek);
    assert(size[0] + size[1] + size[2] <= 25);
    assert(hyllstorlek <= 10);
	
	//Anropar rekursionsfunktionen för det första fallet, det vill säga vi har en hylla och alla böcker är kvar.
	rek(1, hyllstorlek, size);
	
	//Skriver ut det bästa resultatet.
	printf("%d\n", best_result);
	//while(true);
	return 0;
}
