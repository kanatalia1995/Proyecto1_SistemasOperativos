/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tools;

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

    public static void jsonToUser(User user, String json) throws ParseException {
        JSONParser parser = new JSONParser();
        JSONObject userJson = (JSONObject) parser.parse(json);
        user.name = (String) userJson.get("name");
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
}
