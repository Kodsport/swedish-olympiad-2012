#include <cstdio>
#include <iostream>

using namespace std;

const bool SIDE_1 = false;
const bool SIDE_2 = true;

double table[101][101][2][2];
bool isset[101][101][2][2];

int N;
double P1, P2;

int max(int a, int b) {
	return (a>b)?a:b;
}

//Returnerar sannolikheten för att lag 1 vinner från det state som beskrivs i parametrarna.
//
//g1 = antalet mål hittills för lag 1 (g1 är förkortning för goals 1)
//g2 = antalet mål hittills för lag 2
//
//bool side = vilken sida som lag 1 är på (är antingen SIDE_1 eller SIDE_2)
//
//bool justchanged är true om lagen precis bytte sida, och används för att förhindra ett felaktigt beteende
// då lagen fortsätter byta sida flera gånger i rad.
double rek(int g1, int g2, bool side, bool justchanged) {
	
	//Om detta state redan har behandlats returneras värdet som togs fram den gången.
	if(isset[g1][g2][side][justchanged]) {
		return table[g1][g2][side][justchanged];
	}
	
	//Om lag 1 har gjort N mål har lag 1 vunnit. Sannolikheten att lag 1 vinner är därmed 1.
	if(g1 == N) {
		return 1.0;
	} else if(g2 == N) { //Om istället lag 2 har gjort N mål så vinner lag 2, och sannolikheten att lag 1 vinner är alltså 0.
		return 0.0;
	}
	
	//result - sannolikheten att lag 1 vinner från denna position. Beräknas på detta vis:
	//P(lag 1 vinner från denna position) = P(lag 1 gör mål och vinner sedan ELLER lag 2 gör mål men lag 1 vinner ändå) = 
	// P(lag 1 gör mål och vinner sedan) + P(lag 2 gör mål men lag 1 vinner ändå)
	double result = 0.0;
	
	if(side == SIDE_1) {  //Om lag 1 är på sida 1:
		//Lag 1 gör mål:
		
		//Byter sida om den högsta poängen är delbar med 5 och de inte precis har bytt sida.
		bool newside = side; //Nytt värde på side som ska in i nästa anrop till rek()
		bool newchanged = justchanged; //Nytt värde på justchanged som ska in i nästa anrop till rek()
		if(max(g1+1, g2)%5 == 0) {
			if(!justchanged) {
				newside = ((int)newside+1)%2;
				newchanged = true;
			}
		} else {
			newchanged = false;
		}
		
		//Sannolikheten att lag 1 vinner efter att de har gjort mål är rek(g1+1, g2, newside, newchanged). Sannolikheten att lag 1 gör mål
		// är P1. Multiplikationsprincipen ger då att P(lag 1 gör mål och vinner sedan) är produkten av dessa två sannolikheter.
		result += P1*rek(g1+1, g2, newside, newchanged);
		
		//Lag 2 gör mål:
		
		//Byter sida om den högsta poängen är delbar med 5 och de inte precis har bytt sida.
		newside = side;
		newchanged = justchanged;
		if(max(g1, g2+1)%5 == 0) {
			if(!justchanged) {
				newside = ((int)newside+1)%2;
				newchanged = true;
			}
		} else {
			newchanged = false;
		}
		
		//Sannolikheten att lag 1 vinner efter att lag 2 har gjort mål är rek(g1, g2+1, newside, newchanged). Sannolikheten att lag 2 gör mål
		// är (1-P1). Samma resonemang som ovan ger följande formel för P(lag 2 gör mål men lag 1 vinner ändå):
		result += (1-P1)*rek(g1, g2+1, newside, newchanged);
	} else {
		//Analogt fast med lag 1 på planhalva 2. Enda skillnaden är att sannolikheten P2 används istället för P1.
		
		//Lag 1 gör mål:
		bool newside = side;
		bool newchanged = justchanged;
		if(max(g1+1, g2)%5 == 0) {
			if(!justchanged) {
				newside = ((int)newside+1)%2;
				newchanged = true;
			}
		} else {
			newchanged = false;
		}
		result += P2*rek(g1+1, g2, newside, newchanged);
		
		//Lag 2 gör mål:
		newside = side;
		newchanged = justchanged;
		if(max(g1, g2+1)%5 == 0) {
			if(!justchanged) {
				newside = ((int)newside+1)%2;
				newchanged = true;
			}
		} else {
			newchanged = false;
		}
		result += (1-P2)*rek(g1, g2+1, newside, newchanged);
	}
	
	//Lagrar och returnerar resultatet:
	table[g1][g2][side][justchanged] = result;
	isset[g1][g2][side][justchanged] = true;
	return result;
}

int main() {
	scanf("%d", &N);
	scanf("%lf", &P1);
	scanf("%lf", &P2);
	
	printf("%.8lf\n", rek(0, 0, SIDE_1, false)); //Skriver ut svaret. Svaret fås genom att anropa rekursionsfunktionen med
															// den ursprungliga positionen, dvs båda lagen har 0 mål och lag 1 är på sida 1.
	return 0;
}
