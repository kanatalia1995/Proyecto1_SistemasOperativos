package controllers;

import java.io.IOException;
import model.Connection;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author kanat
 */
public class LoginController {
    
   
    public static Connection server;
    
    public void login(String pUser,String pPassword) throws IOException{
        this.server =  new Connection(pUser, pPassword);
        
    }
}
