import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;

import java.io.FileReader;
import java.io.BufferedReader;

public class IDList {

	public static final String idFilename = "idFile";
	public static ArrayList<Integer> ids = new ArrayList<Integer>(0);

	public static void main(String[] args)
	{
		try {
			readIDs();
		} catch (IOException e) {
			e.printStackTrace();
		}
		addId(1231231);
		addId(9999999);
		addId(8);
		showIds();
		fileContainsID(1234);
		fileContainsID(1231231);
	}

	public static void addId(int id)
	{
		BufferedWriter idWriter = null;
		FileWriter idFile = null;
		try {
			// The true here says we're in append mode
			idFile = new FileWriter(idFilename, true);
			idWriter = new BufferedWriter(idFile);
			idWriter.append(String.valueOf(id) + "\n");
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
		ids.add(id);
	}

	public static void readIDs() throws IOException
	{
		FileReader fr = new FileReader(idFilename);
		BufferedReader br = new BufferedReader(fr);
		StringBuffer sb = new StringBuffer();
		String line;
		while( (line = br.readLine()) != null){
			try
			{
				ids.add(Integer.parseInt(line));
			}
			catch (NumberFormatException e)
			{
				e.printStackTrace();
				return;
			}
		}
	}

	public static boolean fileContainsID(Integer id)
	{
		boolean cont = ids.contains(id);
		if(cont)
			System.out.println("The id " + String.valueOf(id) + " is contained");
		else
			System.out.println("The id " + String.valueOf(id) + " is NOT contained");
		return ids.contains(id);
	}

	public static void showIds()
	{
		for(Integer i : ids){
			System.out.println("Id : " + String.valueOf(i));
		}
	}

}
