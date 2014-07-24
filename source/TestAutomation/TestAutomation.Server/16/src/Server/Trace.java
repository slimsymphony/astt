package Server;

/***
 * Class for writing trace messages into shell, which is again redirected to client
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 */
public class Trace {
	
	/***
	 * Writes the trace message into shell
	 * 
	 * @param 		message		A message to write
	 * @since		1.0.0.0
	 */
	public static void writeLine(String message) {
		
		if (message != null) {
			System.out.println(message);
			System.out.flush();
		}
	}
	
	/***
	 * Writes the error message into shell
	 * 
	 * @param 	e	Exception
	 * @since		1.0.0.0
	 */
	public static void writeLine(Throwable e) {

		if (e != null)
		{
			String msg = e.getMessage();
			if (msg != null && !msg.equals("null")) {
				writeLine(msg);
			}
			e.printStackTrace(System.out);
			System.out.flush();
		}
	}
}
