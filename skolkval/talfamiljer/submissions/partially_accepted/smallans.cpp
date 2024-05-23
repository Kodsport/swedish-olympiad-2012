#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;
	
	int list[n]; //Här lagras de talen som ska gillas av svarets familj.
	
	for(int i=0; i<n; i++) {
		cin >> list[i];
	}
	
	//Testar tal i stigande ordning. Det första talet vars familj gillar alla talen i list är svaret.
	for(int i=1; i<=99; i++) {		
		//Omvandlar talet i till strängform och lagrar i variabeln stal (förkortning av strängtal).
		string stal;
		stringstream ss;
		ss << i;
		ss >> stal;
		
		//::::::::::::::::::::
		//Om familjen till i är densamma som ett tal vi redan har gått igenom är det onödigt att testa samma familj igen.
		//Eftersom vi går igenom talen i stigande ordning så gäller detta om följande är sant för två siffror a och b där
		//b ligger efter a i talet: 0 < a < b >= 9
		//Koden nedan tar även itu med de fall där siffran noll ingår, men jag orkar inte beskriva det. Det fungerar, tro mig.
		char latest_nonzero = 0;
		int n_nonfirst_nonzero = 0;
		bool okay = true;
		for(int j=0; j<stal.length(); j++) {
			
			if(stal[j] != '0') {
				if(j != 0)
					n_nonfirst_nonzero++;
				
				if(stal[j] < latest_nonzero) {
					okay = false;
					break;
				}
				
				latest_nonzero = stal[j];
			}
			else if(n_nonfirst_nonzero > 0) {
				okay = false;
				break;
			}
		}
		
		if(!okay)
			continue;
		//::::::::::::::::::::
		
		//Sorterar strängen i lexiografisk ordning, för att vi senare ska kunna gå igenom alla permutationer på ett enkelt sätt.
		sort(stal.begin(), stal.end());
		
		//likes[k]==true betyder att familjen till i gillar talet list[k]. Alla värden sätts till false som standard, och listan
		//uppdateras i do-while-loopen nedan.
		bool likes[n];
		for(int j=0; j<n; j++)
			likes[j] = false;
		
		//För varje permutation:
		do {
			//Om första siffran är noll ingår den här permutationen inte i familjen.
			if(list[0] == '0')
				continue;
			
			//Omvandlar den här permutationen av stal till ett heltal och lagra i variabeln tal.
			stringstream ss;
			int tal;
			ss << stal;
			ss >> tal;
			
			//Kolla vilka av talen i list[] som tal är delbart med, och uppdatera likes[] i enlighet med resultatet.
			for(int j=0; j<n; j++) {
				if(tal % list[j] == 0) {
					likes[j] = true;
				}
			}
		} while(next_permutation(stal.begin(), stal.end()));  //Ändra stal till nästa permutation. Efter den sista avslutas loopen.
		
		//Kollar om familjen gillar alla tal i list[], och skriver isåfall ut talet i som svar.
		bool ok = true;
		for(int j=0; j<n; j++) {
			//cout << likes[j] << endl;
			if(!likes[j]) {
				ok = false;
				break;
			}
		}
		
		if(ok) {
			cout << i << endl;
			return 0;
		}
	}
}
