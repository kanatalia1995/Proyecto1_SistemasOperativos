/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package client;

import java.io.*;
import java.nio.file.Files;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

/**
 *
 * @author edisson
 */
public class ToBytes {
    
    MediaPlayer player;
    Media pick;
    //Media pick;
    
    public static byte[] getBytes(File f) throws FileNotFoundException, IOException{
        byte[] buffer = new byte[1024];
        ByteArrayOutputStream os = new ByteArrayOutputStream();
        FileInputStream fis = new FileInputStream(f); 
        int read;
        int n = 0;
        while ((read = fis.read(buffer)) != -1 && n<4000){
            if (n>3000){
                os.write(buffer, 0, read);
            }
            n++;
        }
        fis.close();
        os.close();
        return os.toByteArray(); 
    }
    
    
    public static byte[] getBytesMp3() throws IOException{
        File f = new File("/home/edisson/NetBeansProjects/Client/Brillas.mp3");
        byte[] bytesFromFile = getBytes(f);
        return bytesFromFile;
    }
    
    public static void myMain() throws IOException{
        File f = new File("/home/edisson/NetBeansProjects/Client/Brillas.mp3");
        byte[] bytesFromFile = getBytes(f);
        // for (int i = 0 ; i < 200 ; i++){
        //     System.out.println((byte)bytesFromFile[i]);
        // }
        String url = "data:audio/mp3;base64,"+bytesFromFile;
        Media pick = new Media(url);
        MediaPlayer player = new MediaPlayer(pick);
        player.play();
        //player.set
        //player.setDataSource(url);
        //player.prepare();
        //player.start();
        
    }
    
}
