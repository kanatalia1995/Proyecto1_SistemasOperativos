/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tools;

import java.io.InputStream;
import model.*;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


/**
 *
 * @author kanat
 */
public class JSON {
    
    
    public static String userString(String pUser, String pPassword){
      JSONObject json   = new JSONObject();
      json.put("user", pUser);
      json.put("password",pPassword);
      
      return json.toString();
    }

    public static String loginString(String pUser, String pPassword) {
        JSONObject json   = new JSONObject();
        json.put("command", "LOGIN");
        json.put("user", pUser);
        json.put("password",pPassword);
      
        return json.toString();
    }
    //
    public static void jsonToUser(User user, String json) throws ParseException {
        JSONParser parser = new JSONParser();
        JSONObject userJson = (JSONObject) parser.parse(json);
        user.name = (String) userJson.get("name");
        user.path = (String) userJson.get("path");
        user.id = (long)userJson.get("id");
        
        JSONArray playListArray = (JSONArray) userJson.get("playListArray");
        for(int i = 0;i<playListArray.size();i++){
            JSONObject playListJson  = (JSONObject) playListArray.get(i);
            String name = (String) playListJson.get("name");
            long id =  (long)playListJson.get("id");
            JSONArray musicArray = (JSONArray) playListJson.get("musicList");
            
            PlayList playList = new PlayList(id,name);
            for(int index = 0;index<musicArray.size();index++){
                JSONObject musicJson = (JSONObject) musicArray.get(index);
                long  idMusic = (long)musicJson.get("id");
                String title = (String) musicJson.get("title");
                String artist = (String) musicJson.get("artist");
                String path = (String) musicJson.get("path");
                String duration = (String) musicJson.get("duration");
                Music music = new Music(idMusic,title,artist,path,duration);
                System.out.print(music.toString());
                playList.insertMusic(music);
            }
            user.playlist.add(playList);
        }
    }
//    "{\"command\": \"GET_AUDIO\",\"path\":\"database/music/kissing_strangers.mp3\"}"
    public static String mp3File(String path) {
        JSONObject json   = new JSONObject();
        json.put("command", "GET_AUDIO");
        json.put("path", path);
   
        return json.toString();
    }

    public static String createPlayList(String name, String path) {
        JSONObject json   = new JSONObject();
        json.put("command", "CREATE_PLAYLIST");
        json.put("playListName", name);
        json.put("path", path);
   
        return json.toString();
    }

    public static PlayList jsonToPlayList(String json) throws ParseException {
        JSONParser parser = new JSONParser();
        JSONObject playListJson = (JSONObject) parser.parse(json);
        String name = (String) playListJson.get("name");
        long id =  (long)playListJson.get("id");
//        JSONArray musicArray = (JSONArray) playListJson.get("musicList"); 
        return new PlayList(id,name);
    }

    public static String getAllSong() {
        JSONObject json   = new JSONObject();
        json.put("command", "GET_ALL_SONGS");
        return json.toString();
    }

    public static PlayList jsonToMusicArray(String json) throws ParseException {
        JSONParser parser = new JSONParser();
        JSONObject musicJson = (JSONObject) parser.parse(json);
        JSONArray songs = (JSONArray)  musicJson.get("musicList");
//        Music[] songsArray = new Music[songs.size()];
        PlayList playList = new PlayList(0,"no name");
        
        for(int index = 0;index<songs.size();index++){
                JSONObject song = (JSONObject) songs.get(index);
                long  idMusic = (long) song.get("id");
                String title = (String) song.get("title");
                String artist = (String) song.get("artist");
                String path = (String) song.get("path");
                String duration = (String) song.get("duration");
                Music music = new Music(idMusic,title,artist,path,duration);
//                System.out.print(music.toString());
                playList.insertMusic(music);
        }
        return playList;
    }
    public static String musicToJson(Music music) {
        JSONObject json   = new JSONObject();
        json.put("id", music.id);
        json.put("title", music.title);
        json.put("artist", music.artist);
        json.put("path", music.path);
        json.put("duration", music.duration);
        return json.toString();
    }

    public static String connectMusic(long  music,String user,long id) {
        JSONObject json   = new JSONObject();
        json.put("command", "MATCH_MUSIC_PLAYLIST");
        json.put("musicId",music);
        json.put("path", user);
        json.put("playListId", id);
   
        return json.toString();
    }
}
