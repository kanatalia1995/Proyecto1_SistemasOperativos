/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import java.io.IOException;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author edisson
 */

public class Connection {
    static int PORT = 8080;
    static String IP = "127.0.0.1";
    
    public static boolean ConnectToServer(){
        try {
            Socket socket = new Socket(IP, PORT);
            System.out.println("Client connected");
            return true;
        } catch (IOException ex) {
            System.out.println("Client not connected");
            Logger.getLogger(Connection.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }
    
    
    
}
