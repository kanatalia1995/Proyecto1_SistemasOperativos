/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import tools.JSON;
/**
 *
 * @author edisson
 */

public class Connection {
    static int PORT = 8080;
    static String IP = "127.0.0.1";
    static Socket socket;
    static  PrintWriter send ;
    static BufferedReader read;

    
    public static  Socket connectToServer() throws IOException{
            socket = new Socket(IP, PORT);
            read = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            send  = new PrintWriter(socket.getOutputStream(),true);
            return socket;
    }

    public static boolean sendMessage(String message) throws IOException {
        send.println(message.length());
        send.println(message);
//        send.flush(); // Send off the data
        return true;   
   }

    public static String readMessage() throws IOException, ClassNotFoundException {
        String response = "";
        String line ;
        while((line = read.readLine())!=null){
            response += line;
        }
        return response ; 
    }
    
    public static void close() throws IOException{
        send.close();
        read.close();
        socket.close(); 
    }
    
}
