/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tools;

import org.json.simple.JSONObject;

/**
 *
 * @author kanat
 */
public class JSON {
    
    
    static public String userString(String pUser, String pPassword){
      JSONObject json   = new JSONObject();
      json.put("user", pUser);
      json.put("password",pPassword);
      
      return json.toString();
    }
    
}
