/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
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
//        send.println(message.length());
//        System.out.print(message.length());
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

    public static byte[] readAudioMessage() throws IOException {
        ByteArrayOutputStream buffer = new ByteArrayOutputStream();
        byte bufferArray[] = new byte[512];
        DataInputStream  read1 = new DataInputStream(socket.getInputStream());
        for(int s; (s=read1.read(bufferArray)) != -1; )
        {
          buffer.write(bufferArray, 0, s);
//          System.out.println(s);
        }
//        System.out.print(buffer.toString());
        return buffer.toByteArray();
//        int numRead;
//        String line ;
//        while ((numRead = read.read(bytes, 0, buf.length)) >= 0) {
//            int offset = 0;
//            while (offset < numRead) {
//              offset += line.write(buf, offset, numRead - offset);
//            }
//         }
//        return response ; 
        
        
    }
    
}
