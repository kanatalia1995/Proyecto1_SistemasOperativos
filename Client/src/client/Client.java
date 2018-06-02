package client;

import static client.Connection.ConnectToServer;
import client.Interfaces.Login;
import java.io.IOException;

/**
 *
 * @author edisson
 */
public class Client {

    /**
     * @param args the command line arguments
     */
    
    public static void OpenInterfaz(){
        // new Interfaz().setVisible(true); // descomment and comment next line if u want skip the Login Window
        new Login().setVisible(true);
    }
    
    public static void main(String[] args) throws IOException {
        // TODO code application logic here
        ConnectToServer();
        OpenInterfaz();
        
        // System.out.println("Listo :)");
        
    }
    
}
