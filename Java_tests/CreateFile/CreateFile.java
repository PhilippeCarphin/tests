// REF : https://beginnersbook.com/2014/01/how-to-create-a-file-in-java/

import java.io.File;
import java.io.IOException;

public class CreateFile
{
	public static void main(String[] args)
	{

		try {

			File f = new File("created_file.txt");

			boolean fileCreated = f.createNewFile();

			if( fileCreated ){
				System.out.println("File has been created");
			}
			else {
				System.out.println("File already there");
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}

