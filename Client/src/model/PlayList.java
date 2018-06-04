/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.util.ArrayList;

/**
 *
 * @author kmolina
 */
public class PlayList {
    public long id;
    public String name;
    public ArrayList<Music> musicList; 

    @Override
    public String toString() {
        return name;
    }

    public PlayList(long id, String name) {
        this.id = id;
        this.name = name;
        this.musicList =  new ArrayList<Music>();
    }
    
    public void insertMusic(Music pMusic){
        this.musicList.add(pMusic);
    }
    
}
