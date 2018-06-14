/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.*;
import java.nio.file.Files;

/**
 *
 * @author edisson
 */
public class ToFile {
    public static void ToFile(byte[] data, File destination){
        try(FileOutputStream fos = new FileOutputStream(destination)){
            fos.write(data);
            fos.close();
        }catch(Exception e){
            System.out.println("Catch de ToFile");
        }
    }
    public static void myMain(){
        String text = "Este es mi texto";
        byte[] data = text.getBytes();
        File destination = new File("archive.mp3");
        ToFile(data, destination);
    }
    public static void ToFileMp3() throws IOException{
        byte[] data = ToBytes.getBytesMp3();
        File destination = new File("archive.mp3");
        ToFile(data, destination);
    }
    
}
