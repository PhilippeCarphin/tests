// REF : https://beginnersbook.com/2014/01/how-to-create-a-file-in-java/

import java.io.File;
import java.io.IOException;

public class CreateFile
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

		createFile(filename);

	}

	private static boolean createFile(String filename)
	{
		boolean fileCreated = false;
		try {

			File f = new File(filename);

			fileCreated = f.createNewFile();

			if( fileCreated ){
				System.out.println("File has been created");
			}
			else {
				System.out.println("File already there");
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

		return fileCreated;
	}
}

