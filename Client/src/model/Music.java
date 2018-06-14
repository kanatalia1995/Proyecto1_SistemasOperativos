/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import tools.JSON;

/**
 *
 * @author kmolina
 */
public class Music {
    
    public long id;
    public String title;
    public String artist;
    public String path;

    @Override
    public String toString() {
        return  "id=" + id + "     title=" + title + "    artist=" + artist;
    }
    public String duration;
    
    public Music(long id, String title, String artist, String path, String duration) {
        this.id = id;
        this.title = title;
        this.artist = artist;
        this.path = path;
        this.duration = duration;
    }

}
