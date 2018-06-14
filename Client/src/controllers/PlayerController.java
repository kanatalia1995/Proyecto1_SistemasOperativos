/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controllers;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import javax.print.attribute.standard.Media;
import javax.sound.sampled.AudioFileFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import static javax.sound.sampled.AudioSystem.getAudioFileFormat;
import javax.sound.sampled.Clip;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineEvent;
import javax.sound.sampled.LineListener;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import javazoom.jl.decoder.JavaLayerException;
import javazoom.jl.player.Player;
import model.Connection;
import model.Music;
import model.PlayList;
import model.User;
import org.json.simple.parser.ParseException;
import tools.JSON;
import view.Interface;

/**
 *
 * @author kmolina
 */
public class PlayerController {
    public User user;
    public Player player;
    public PlayerController(User pUser) {
        this.user = pUser;
    }
    public InputStream getAudio(String path) throws IOException, ClassNotFoundException, JavaLayerException, LineUnavailableException, UnsupportedAudioFileException{
        String message = JSON.mp3File(path);
        System.out.print(message);
        Connection.connectToServer();
        Connection.sendMessage(message);
        byte[] audio = Connection.readAudioMessage();
        Connection.close();
        InputStream song = new ByteArrayInputStream(audio);
        return song ;
//        
//        AudioInputStream audioIn = AudioSystem.getAudioInputStream(song);  
//        Clip clip = AudioSystem.getClip();
//        clip.open(audioIn);
//        clip.start();
//        player.play();
//        BasicPlayer pbac =  BasicPlayer();  
    }

    public InputStream playSong(Interface gui, Music music) throws IOException, ClassNotFoundException, JavaLayerException, LineUnavailableException, UnsupportedAudioFileException {
        return this.getAudio(music.path);
    }

    public PlayList createPlayList(String name) throws IOException, ClassNotFoundException, ParseException {
        String message = JSON.createPlayList(name, user.path);
        System.out.print(message);
        Connection.connectToServer();
        Connection.sendMessage(message);
        String response = Connection.readMessage();
        Connection.close();
        PlayList newPlay = JSON.jsonToPlayList(response);
        this.user.playlist.add(newPlay);
        return newPlay;
    }

    public PlayList getAllMusic() throws IOException, ClassNotFoundException, ParseException {
        String message = JSON.getAllSong();
        System.out.print(message);
        Connection.connectToServer();
        Connection.sendMessage(message);
        String response = Connection.readMessage();
//        System.out.print(" MUSIC RESPONSE "+response);
        Connection.close();
        return  JSON.jsonToMusicArray(response);
    }

    public String matchMusicPlayList(Music music, PlayList play) throws IOException, ClassNotFoundException {
        String message = JSON.connectMusic(music.id,user.path,play.id);
        System.out.print(message);
        Connection.connectToServer();
        Connection.sendMessage(message);
        String response = Connection.readMessage();
        Connection.close();
        play.insertMusic(music);
        System.out.print(" MAtch RESPONSE "+response);
        Connection.close();
        return  response;
    }
}
