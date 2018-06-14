/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.util.ArrayList;
import org.json.simple.parser.ParseException;
import tools.JSON;

/**
 *
 * @author kmolina
 */
public class User {
    
    public String name;
    public long id;
    public ArrayList<PlayList> playlist ;
    public String path;
    
    public User(String json) throws ParseException{
        this.playlist  = new ArrayList<>();
        JSON.jsonToUser(this,json);
    }

    @Override
    public String toString() {
        return "User{" + "name=" + name + ", id=" + id + ", playlist=" + playlist.toString() + '}';
    }
}
