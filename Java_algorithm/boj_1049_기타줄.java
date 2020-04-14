package first;

import java.util.Arrays;
import java.util.Scanner; //ctrl + shift + o

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		int M = sc.nextInt();
		int[] six = new int[M]; //동적 할당 비슷??
		int[] one = new int[M];
		
		for(int i=0; i<M; i++) {
			six[i]=sc.nextInt();
			one[i]=sc.nextInt();
		}
		int sixsum = 0, onesum1 = 0, onesum2 = 0; 
		
	//	sort(six, six+M); sort(one, one+M);
		Arrays.sort(six); Arrays.sort(one);
		
		int s = N/6, o = N%6; 
		sixsum = six[0]*s; 	onesum2 = Math.min(one[0]*o, six[0]); 
		onesum1 = one[0]*N;
		
		System.out.println(Math.min(onesum1, (sixsum+onesum2)));				
	}

}
