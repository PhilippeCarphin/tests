import java.util.Random;

public class Main {
	public static void main(String[] args){
		for(int i = 0; i < 100; ++i){
			Random rand = new Random();
			Random randWithSeed = new Random(0);
			int r = rand.nextInt(4001);
			int r_seed = randWithSeed.nextInt(4001);
			System.out.println("r      = " + String.valueOf(r));
			System.out.println("r_seed = " + String.valueOf(r_seed));
		}
	}
}


