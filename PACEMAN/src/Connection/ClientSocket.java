package Connection;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;



public class ClientSocket {

	private int number;
	private String temp;
	

	
	public ClientSocket(){
	
	}
	
	
	
	
	
	
	public String sendMessage(String msg)
	{
		
		Socket sock = null;
		
		String message = null;
		
		
		///////////////////////////////////////////////////////////////////////////////////////////////////
			
		
		try {
			sock = new Socket("localhost", 9000);
			
			BufferedReader sc1 = new BufferedReader(new InputStreamReader(sock.getInputStream()));
			
			OutputStream output = null;
			output = sock.getOutputStream();
			output.flush();
			
			
			//salida
			
			PrintWriter writer = new PrintWriter(output, true);
			
			System.out.println("enviando mensaje");
					
			
			writer.println(msg);
			
			output.flush();
			
			
			System.out.println("mensaje enviado");
			
			
			//entrada
			

			InputStream input = null;
			input = sock.getInputStream();
			
			
			//output.flush();
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(input));
			
			
			
			String line;	

			message = "";
			
			while( (line = reader.readLine()) != null) {
				

				message += line;
				
				if(line == "\n")
					sock.close();
					break;
			}
			
			
			System.out.println("mensaje recibido: " + message);
		

			
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return message;
		
		

	}
	
	
}