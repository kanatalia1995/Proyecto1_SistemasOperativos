/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import tools.JSON;
/**
 *
 * @author edisson
 */

public class Connection {
    int PORT = 8080;
    String IP = "127.0.0.1";
    Socket socket;
    DataOutputStream send;
    DataInputStream read;
    
    public Connection(String pUser, String pPassword) throws IOException{
        this.ConnectToServer();
        String message = JSON.userString(pUser, pPassword);
        this.send.writeByte(message.length());
        this.send.writeUTF(message);
        this.send.flush();
        
        System.out.println(read.readLine());
        
        
    }
    
    public boolean ConnectToServer(){
        try {
            socket = new Socket(IP, PORT);
            send = new DataOutputStream(socket.getOutputStream());
            read = new DataInputStream(socket.getInputStream());
            System.out.println("Client connected");
            return true;
        } catch (IOException ex) {
            System.out.println("Client not connected");
            Logger.getLogger(Connection.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }
    
    
    
}
