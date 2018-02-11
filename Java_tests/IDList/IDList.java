import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;

public class IDList {

	public static final String idFilename = "idFile";
	public static ArrayList ids = new ArrayList<Integer>(0);

	public static void main(String[] args)
	{
		BufferedWriter idWriter = null;
		FileWriter idFile = null;
		try {
			// The true here says we're in append mode
			idFile = new FileWriter(idFilename, true);
			idWriter = new BufferedWriter(idFile);
			int ID = 1234567;
			idWriter.append(String.valueOf(ID) + "\n");
			idWriter.close();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try{
				idWriter.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public static boolean fileContainsID()
	{
		return false;
	}
}
