// REF : https://beginnersbook.com/2014/01/how-to-create-a-file-in-java/

import java.io.File;
import java.io.IOException;

public class FileExists
{
	public static void main(String[] args)
	{

		String filename = null;
		if( args.length == 1){
			filename = args[0];
		}
		else {
			System.out.println("Filename must be provided on command line");
			System.exit(1);
		}

		if(fileExists(filename))
			System.out.println("File " + filename + " exists");
		else
			System.out.println("File " + filename + " does not exist");

	}

	private static boolean fileExists(String filename)
	{
		return new File(filename).exists();
	}
}

