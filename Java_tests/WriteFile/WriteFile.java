// REF :
// https://www.mkyong.com/java/how-to-write-to-file-in-java-bufferedwriter-example/

import java.io.FileWriter;
import java.io.IOException;
import java.io.BufferedWriter;

public class WriteFile {

	public static void main(String[] args){

		BufferedWriter bw = null;
		FileWriter fw = null;

		try{

			fw = new FileWriter("new_file.txt");
			bw = new BufferedWriter(fw);
			bw.write("This is the content of the file\n");

		} catch (IOException e) {
			e.printStackTrace();
		} finally {

			try {
				if( bw != null )
					bw.close();
				if( fw != null )
					fw.close();
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
	}
}
