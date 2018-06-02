/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.lang.instrument.Instrumentation;

/**
 *
 * @author edisson
 */

public class Connection {
    static int PORT = 8080;
    static String IP = "127.0.0.1";
    static Socket socket;
    
    public static boolean ConnectToServer(){
        try {
            socket = new Socket(IP, PORT);
            
            return true;
        } catch (IOException ex) {
            System.out.println("Client not connected");
            //Logger.getLogger(Connection.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }
    
    public static void sendData(){
        
    }
    public static boolean sendData(int number){
        try{
            PrintWriter out;
            out = new PrintWriter(new DataOutputStream(getSocket().getOutputStream()));
            out.write(number);

            out.flush();
            out.close();
            System.out.println("The text \"" + number + "\" was sent to server");
            return true;
        }catch(Exception e){
            System.out.println("The text \"" + number + "\" was NOT sent to server");
            return false;
        }
    }
    
    public static boolean sendData(String text){
        try{
            PrintWriter out;
            out = new PrintWriter(new DataOutputStream(getSocket().getOutputStream()));
            out.write(text);

            out.flush();
            out.close();
            System.out.println("The text \"" + text + "\" was sent to server");
            return true;
        }catch(Exception e){
            System.out.println("The text \"" + text + "\" was NOT sent to server");
            return false;
        }
    }
    public static boolean sendDataLogin(String username, String password){
        String dataInfo = "{\"user\": \"" + username + "\" ,\"password\": \"" + password + "\" }";
        // String dataInfo = "{\"user\": \"User1\" ,\"password\": \"pass1\" }";
        String size = Integer.toString(100);
        sendData(100);
        sendData(dataInfo);
        if (sendData(100) && sendData(dataInfo)){
            return true;
        }else{
            return false;
        }
    }
    
    
    
    public static Socket getSocket(){
        return Connection.socket;
    }
    
}
