import java.util.*;

public class Talfamiljer
{
	public static void main(String [] klein)
	{
		Scanner scan = new Scanner(System.in);

		final int N = scan.nextInt();

		//Läser in talen.
		int [] v = new int [N];
		for(int i = 0; i<N; i++)
		{
			v[i] = scan.nextInt();
		}

		//id[i] = unikt id för familjen talet i tillhör.
		//id:t för ett tal beräknas på följande sätt, där antal syftar på siffror i talet.
		// [antal nollor]*8^0 + [antal ettor]*8^1 + ... + [antal nior]*8^9
		//Maxvärdet för ett ID är 8^10 - 1 = 2^30 - 1 vilket ryms i en int.
		//Eftersom det max kan förekomma 6 antal av varje siffra kan vi använda 7 som bas,
		// men med bas 8 kan vi använda oss av bitshiftningar istället för multiplikationer = snabbare.
		int [] id = new int [1000000];

		//För varje familj sparar vi en array som markerar vilka av talen,
		// som delar något tal i familjen.
		HashMap <Integer,boolean[]> map = new HashMap <Integer,boolean[]> ();

		//Svaret har högst 6 siffror => bara tal <1000000 är intressanta.
		for(int i = 1; i<1000000; i++)
		{
			//Ex: id[13773] = id[1377] + 8^3
			id[i] = id[i/10] + (1<<3*(i%10)); //1<<3*i == 8^i

			//Om denna familj inte redan finns, så "skapar" vi den.
			if(!map.containsKey(id[i])) map.put(id[i],new boolean [N]);
		}

		//Markerar vilka familjer varje tal delar.
		for(int i = 0; i<N; i++)
		for(int j = v[i]; j<1000000; j+=v[i])
		map.get(id[j])[i] = true;

		//Går igenom alla familjer.
		loop:for(int i = 1; i<1000000; i++)
		{
			boolean [] u = map.get(id[i]); //Hämtar familjen.
			if(u==null) continue; //Vi har redan kollat denna familj.

			for(int j = 0; j<N; j++) //Kollar om den gillas av alla talen.
			if(!u[j]) //Ajdå det fanns ett tal som inte gillade familjen.
			{
				map.remove(id[i]); //Tar bort familjen.
				continue loop;
			}

			//Vi klarade oss igenom ovanstående loop.
			//Alltså gillas i's familj av alla tal.
			System.out.println(i);
			break;
		}
	}
}
