import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.StringTokenizer;


public class uppg5 {
	HashSet<String> table; //Här sparas alla positioner som redan har behandlats, detta för att slippa behandla samma fall flera gånger.
	static final int offset = '0';
	String solved = "123456780"; //Detta är positionen som vi vill komma fram till.
	LinkedList<State> queue; //Det första elementet i kön är nästa position som ska behandlas. Nya element läggs till i början och nya hämtas i slutet, 
									// vilket gör att varje position nås med så få drag som möjligt.
	
	//Inmatning
	public static void main(String[] args) {
		Kattio io = new Kattio(System.in);
		String state = "";
		
		for(int i=0; i<9; i++) {
			state += (char)(io.getInt()+offset);
		}
		
		new uppg5(state);
	}


	public uppg5(String firststate) {
		//Om spelet redan är löst behöver man inte göra några drag.
		if(firststate.equals(solved)) {
			System.out.println("0");
			System.exit(0);
		}
		
		
		queue = new LinkedList<State>();
		table = new HashSet<String>();
		
		queue.add(new State(firststate, 0)); //Lägger till den ursprungliga positionen i kön.
		
		//Fortsätter så länge det finns fler positioner att testa.
		while(!queue.isEmpty()) {			
			State current = queue.pollLast(); //Hämtar positionen som ska kontrolleras - och tar bort den ur kön.
			char[] chararr = current.state.toCharArray();
			int row0 = 0, col0 = 0;
			
			//Om antalet gjorda drag är större än 31 så finns det enligt uppgiftstexten ingen lösning.
			//Detta är dock bortkommenterat för säkerhets skull, eftersom det aldrig kommer ske i korrekt indata.
			/*if(current.moves > 31) {
				System.out.println("PROBLEM");
				System.exit(1);
			}*/
			
			//Omvandlar state-strängen till en tvådimensionell array för enklare hantering.
			//Sätter row0 och rol0 till koordinaterna för hålet.
			int[][] grid = new int[3][3];
			
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					grid[i][j] = current.state.charAt(i*3+j) - offset;
					if(grid[i][j] == 0) {
						row0 = i;
						col0 = j;
					}
				}
			}
			
			//Flyttar brickan till vänster om hålet - om det finns någon.
			if(col0 > 0) {
				newmove(current.moves, row0*3 + col0-1, row0*3 + col0, chararr.clone());
			}	
			
			//Flyttar brickan till höger om hålet - om det finns någon.
			if(col0 < 2) {
				newmove(current.moves, row0*3 + col0+1, row0*3 + col0, chararr.clone());
			}	
			
			//Flyttar brickan ovanför hålet - om det finns någon.
			if(row0 > 0) {
				newmove(current.moves, (row0-1)*3 + col0, row0*3 + col0, chararr.clone());
			}	
			
			//Flyttar brickan under hålet - om det finns någon.
			if(row0 < 2) {
				newmove(current.moves, (row0+1)*3 + col0, row0*3 + col0, chararr.clone());
			}	
		}
	}
	
	//Gör ett nytt drag. moves är antalet drag hittills, a och b är positionen för brickorna som ska byta plats och c2 positionen på char[]-form.
	void newmove(int moves, int a, int b, char[] c2) {
		swap(c2, a, b);
		String newstate = String.valueOf(c2);
		
		if(!table.contains(newstate)) {
			table.add(newstate);
			
			if(newstate.equals(solved)) {
				System.out.println((moves+1));
				System.exit(0);
			}
			
			queue.push(new State(newstate, moves+1));
		}
	}
	
	//Byter plats på två element i en char-array.
	void swap(char[] arr, int i, int j) {
		char ch = arr[i];
		arr[i] = arr[j];
		arr[j] = ch;
	}

}

//Enkel klass som motsvarar en position (state). Innehåller brickornas plats i strängen state och antalet drag hittills i heltalet moves.
class State {
	String state;
	int moves;
	
	State(String s, int m) {
		state = s;
		moves = m;
	}
}


//Input/output-klass.
class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
	super(new BufferedOutputStream(System.out));
	r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
	super(new BufferedOutputStream(o));
	r = new BufferedReader(new InputStreamReader(i));
    }
 
    public boolean hasMoreTokens() {
	return peekToken() != null;
    }
 
    public int getInt() {
	return Integer.parseInt(nextToken());
    }
 
    public double getDouble() { 
	return Double.parseDouble(nextToken());
    }
 
    public long getLong() {
	return Long.parseLong(nextToken());
    }
 
    public String getWord() {
	return nextToken();
    }
 
 
 
    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;
 
    private String peekToken() {
	if (token == null) 
	    try {
		while (st == null || !st.hasMoreTokens()) {
		    line = r.readLine();
		    if (line == null) return null;
		    st = new StringTokenizer(line);
		}
		token = st.nextToken();
	    } catch (IOException e) { }
	return token;
    }
 
    private String nextToken() {
	String ans = peekToken();
	token = null;
	return ans;
    }
}
