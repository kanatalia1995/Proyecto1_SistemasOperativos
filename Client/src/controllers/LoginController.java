package controllers;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import model.Connection;
import model.User;
import org.json.simple.parser.ParseException;
import tools.JSON;


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
    public User user;
    
    public  LoginController() throws IOException{
//         this.server = new Connection();
    }
    
    public int login(String pUser,String pPassword) throws IOException, ClassNotFoundException, ParseException{
        String message = JSON.loginString(pUser, pPassword);
        System.out.print(message);
        Connection.connectToServer();
        Connection.sendMessage(message);
        String response = Connection.readMessage();
        Connection.close();
        System.out.print("Response" + response);
        if (response.compareTo("INVALID USER") == 0) return 0;
        this.user = new User(response);
        return 1;
    }
}
