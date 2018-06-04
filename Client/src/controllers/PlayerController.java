/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controllers;

import model.User;

/**
 *
 * @author kmolina
 */
public class PlayerController {
    public User user;
    public PlayerController(User pUser) {
        this.user = pUser;
    }
}
