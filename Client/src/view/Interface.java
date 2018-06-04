/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view;


import controllers.PlayerController;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.io.File;
import java.util.ArrayList;
import javax.print.attribute.standard.Media;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;
import model.Music;
import model.PlayList;

/**
 *
 * @author edisson
 */
public class Interface extends javax.swing.JFrame {

    /**
     * Creates new form Interfaz
     */
    boolean pause, playing = false;
//    MediaPlayer player;
//    Media pick;
    float prev_volume = -1;
    Color light_gray_1 = new Color(58,58,58);
    Color light_gray_2 = new Color(68,68,68);
    
    public static PlayerController controller;
    
    
    public Interface() {
        initComponents();
        this.userNameText.setText(Interface.controller.user.name);
        initPlayList();
        ConfigWindow();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        pnl_panels = new javax.swing.JPanel();
        jTabbedPane1 = new javax.swing.JTabbedPane();
        pnl_panels_allSongs = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        songsTable = new javax.swing.JTable();
        pnl_panels_myPlaylist = new javax.swing.JPanel();
        jLabel4 = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        playList = new javax.swing.JList();
        jScrollPane4 = new javax.swing.JScrollPane();
        songsList = new javax.swing.JList();
        jLabel6 = new javax.swing.JLabel();
        pnl_panels_account = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();
        userNameText = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        pnl_song_playing = new javax.swing.JPanel();
        btn_prev = new javax.swing.JButton();
        btn_play = new javax.swing.JButton();
        btn_next = new javax.swing.JButton();
        prg_time = new javax.swing.JProgressBar();
        btn_mute = new javax.swing.JButton();
        sld_volume = new javax.swing.JSlider();
        pnl_song_info = new javax.swing.JPanel();
        lbl_song_artist_name = new javax.swing.JLabel();
        lbl_song_name = new javax.swing.JLabel();
        lbl_song_cover = new javax.swing.JLabel();
        jPanel1 = new javax.swing.JPanel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setMaximumSize(new java.awt.Dimension(1000, 1500));
        setMinimumSize(new java.awt.Dimension(400, 800));
        setPreferredSize(new java.awt.Dimension(800, 900));

        pnl_panels.setPreferredSize(new java.awt.Dimension(700, 400));

        jTabbedPane1.setTabLayoutPolicy(javax.swing.JTabbedPane.SCROLL_TAB_LAYOUT);
        jTabbedPane1.setTabPlacement(javax.swing.JTabbedPane.LEFT);
        jTabbedPane1.setPreferredSize(new java.awt.Dimension(500, 408));

        pnl_panels_allSongs.setBorder(new javax.swing.border.LineBorder(java.awt.Color.lightGray, 0, true));
        pnl_panels_allSongs.setPreferredSize(new java.awt.Dimension(500, 395));

        jLabel1.setFont(new java.awt.Font("Lucida Sans", 1, 24)); // NOI18N
        jLabel1.setText("Song's list");

        songsTable.setBackground(new java.awt.Color(231, 212, 212));
        songsTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "Title", "Artist", "Play", "PlayList"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class
            };
            boolean[] canEdit = new boolean [] {
                false, false, false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        songsTable.setSelectionBackground(new java.awt.Color(0, 0, 0));
        songsTable.setShowHorizontalLines(false);
        jScrollPane2.setViewportView(songsTable);

        javax.swing.GroupLayout pnl_panels_allSongsLayout = new javax.swing.GroupLayout(pnl_panels_allSongs);
        pnl_panels_allSongs.setLayout(pnl_panels_allSongsLayout);
        pnl_panels_allSongsLayout.setHorizontalGroup(
            pnl_panels_allSongsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_panels_allSongsLayout.createSequentialGroup()
                .addGap(21, 21, 21)
                .addGroup(pnl_panels_allSongsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 723, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel1))
                .addContainerGap(192, Short.MAX_VALUE))
        );
        pnl_panels_allSongsLayout.setVerticalGroup(
            pnl_panels_allSongsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_panels_allSongsLayout.createSequentialGroup()
                .addComponent(jLabel1)
                .addGap(32, 32, 32)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 322, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        jTabbedPane1.addTab("Songs", pnl_panels_allSongs);

        pnl_panels_myPlaylist.setBorder(null);
        pnl_panels_myPlaylist.setMaximumSize(new java.awt.Dimension(700, 900));
        pnl_panels_myPlaylist.setPreferredSize(new java.awt.Dimension(400, 400));

        jLabel4.setFont(new java.awt.Font("Lucida Sans", 1, 24)); // NOI18N
        jLabel4.setText("My Play List");

        playList.setModel(new javax.swing.AbstractListModel() {
            String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
            public int getSize() { return strings.length; }
            public Object getElementAt(int i) { return strings[i]; }
        });
        playList.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                playListMouseClicked(evt);
            }
        });
        jScrollPane1.setViewportView(playList);

        songsList.setModel(new javax.swing.AbstractListModel() {
            String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
            public int getSize() { return strings.length; }
            public Object getElementAt(int i) { return strings[i]; }
        });
        jScrollPane4.setViewportView(songsList);

        jLabel6.setText("SONGS");

        javax.swing.GroupLayout pnl_panels_myPlaylistLayout = new javax.swing.GroupLayout(pnl_panels_myPlaylist);
        pnl_panels_myPlaylist.setLayout(pnl_panels_myPlaylistLayout);
        pnl_panels_myPlaylistLayout.setHorizontalGroup(
            pnl_panels_myPlaylistLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_panels_myPlaylistLayout.createSequentialGroup()
                .addGroup(pnl_panels_myPlaylistLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(pnl_panels_myPlaylistLayout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(pnl_panels_myPlaylistLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel4)
                            .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 775, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(pnl_panels_myPlaylistLayout.createSequentialGroup()
                        .addGap(317, 317, 317)
                        .addComponent(jLabel6))
                    .addGroup(pnl_panels_myPlaylistLayout.createSequentialGroup()
                        .addGap(119, 119, 119)
                        .addComponent(jScrollPane4, javax.swing.GroupLayout.PREFERRED_SIZE, 441, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(149, Short.MAX_VALUE))
        );
        pnl_panels_myPlaylistLayout.setVerticalGroup(
            pnl_panels_myPlaylistLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_panels_myPlaylistLayout.createSequentialGroup()
                .addComponent(jLabel4, javax.swing.GroupLayout.PREFERRED_SIZE, 63, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(33, 33, 33)
                .addComponent(jLabel6)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane4, javax.swing.GroupLayout.PREFERRED_SIZE, 172, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 491, Short.MAX_VALUE))
        );

        jTabbedPane1.addTab("My list", pnl_panels_myPlaylist);

        pnl_panels_account.setPreferredSize(new java.awt.Dimension(500, 400));

        jLabel2.setFont(new java.awt.Font("Ubuntu", 1, 36)); // NOI18N
        jLabel2.setText("Welcome!");

        userNameText.setText("User Name");

        jLabel3.setIcon(new javax.swing.ImageIcon(getClass().getResource("/images/image1.png"))); // NOI18N

        javax.swing.GroupLayout pnl_panels_accountLayout = new javax.swing.GroupLayout(pnl_panels_account);
        pnl_panels_account.setLayout(pnl_panels_accountLayout);
        pnl_panels_accountLayout.setHorizontalGroup(
            pnl_panels_accountLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_panels_accountLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(pnl_panels_accountLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_panels_accountLayout.createSequentialGroup()
                        .addComponent(jLabel2, javax.swing.GroupLayout.PREFERRED_SIZE, 309, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(210, 210, 210))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_panels_accountLayout.createSequentialGroup()
                        .addComponent(userNameText)
                        .addGap(360, 360, 360))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_panels_accountLayout.createSequentialGroup()
                        .addComponent(jLabel3, javax.swing.GroupLayout.PREFERRED_SIZE, 410, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(514, 514, 514))))
        );
        pnl_panels_accountLayout.setVerticalGroup(
            pnl_panels_accountLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_panels_accountLayout.createSequentialGroup()
                .addGap(107, 107, 107)
                .addComponent(jLabel2)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(userNameText)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jLabel3, javax.swing.GroupLayout.PREFERRED_SIZE, 434, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(387, 387, 387))
        );

        jTabbedPane1.addTab("Account", pnl_panels_account);

        javax.swing.GroupLayout pnl_panelsLayout = new javax.swing.GroupLayout(pnl_panels);
        pnl_panels.setLayout(pnl_panelsLayout);
        pnl_panelsLayout.setHorizontalGroup(
            pnl_panelsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_panelsLayout.createSequentialGroup()
                .addComponent(jTabbedPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 1012, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, Short.MAX_VALUE))
        );
        pnl_panelsLayout.setVerticalGroup(
            pnl_panelsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jTabbedPane1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pnl_song_playing.setMaximumSize(new java.awt.Dimension(1100, 1000));
        pnl_song_playing.setPreferredSize(new java.awt.Dimension(350, 100));

        btn_prev.setText("⏮");
        btn_prev.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_prevActionPerformed(evt);
            }
        });

        btn_play.setText("⏸");
        btn_play.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_playActionPerformed(evt);
            }
        });

        btn_next.setText("⏭");

        prg_time.addComponentListener(new java.awt.event.ComponentAdapter() {
            public void componentShown(java.awt.event.ComponentEvent evt) {
                prg_timeComponentShown(evt);
            }
        });

        btn_mute.setText("🔊");
        btn_mute.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btn_muteActionPerformed(evt);
            }
        });

        sld_volume.setFont(new java.awt.Font("Ubuntu", 0, 3)); // NOI18N
        sld_volume.setMaximum(10);
        sld_volume.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                sld_volumeStateChanged(evt);
            }
        });

        javax.swing.GroupLayout pnl_song_playingLayout = new javax.swing.GroupLayout(pnl_song_playing);
        pnl_song_playing.setLayout(pnl_song_playingLayout);
        pnl_song_playingLayout.setHorizontalGroup(
            pnl_song_playingLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_song_playingLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(prg_time, javax.swing.GroupLayout.PREFERRED_SIZE, 433, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_song_playingLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(btn_prev)
                .addGap(18, 18, 18)
                .addComponent(btn_play)
                .addGap(18, 18, 18)
                .addComponent(btn_next)
                .addGap(18, 18, 18)
                .addComponent(btn_mute)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(sld_volume, javax.swing.GroupLayout.PREFERRED_SIZE, 83, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(32, 32, 32))
        );
        pnl_song_playingLayout.setVerticalGroup(
            pnl_song_playingLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_song_playingLayout.createSequentialGroup()
                .addGap(0, 32, Short.MAX_VALUE)
                .addGroup(pnl_song_playingLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(pnl_song_playingLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(btn_play)
                        .addComponent(btn_prev)
                        .addComponent(btn_next)
                        .addComponent(btn_mute))
                    .addComponent(sld_volume, javax.swing.GroupLayout.PREFERRED_SIZE, 22, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(prg_time, javax.swing.GroupLayout.PREFERRED_SIZE, 3, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(24, 24, 24))
        );

        pnl_song_info.setMaximumSize(new java.awt.Dimension(32767, 100));
        pnl_song_info.setPreferredSize(new java.awt.Dimension(350, 100));

        lbl_song_artist_name.setFont(new java.awt.Font("Ubuntu", 0, 12)); // NOI18N
        lbl_song_artist_name.setForeground(new java.awt.Color(100, 98, 98));
        lbl_song_artist_name.setText("Single Singer");

        lbl_song_name.setText("Without nothing");

        javax.swing.GroupLayout pnl_song_infoLayout = new javax.swing.GroupLayout(pnl_song_info);
        pnl_song_info.setLayout(pnl_song_infoLayout);
        pnl_song_infoLayout.setHorizontalGroup(
            pnl_song_infoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, pnl_song_infoLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(lbl_song_cover, javax.swing.GroupLayout.PREFERRED_SIZE, 83, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(pnl_song_infoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(lbl_song_name, javax.swing.GroupLayout.PREFERRED_SIZE, 168, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(lbl_song_artist_name, javax.swing.GroupLayout.PREFERRED_SIZE, 129, javax.swing.GroupLayout.PREFERRED_SIZE)))
        );
        pnl_song_infoLayout.setVerticalGroup(
            pnl_song_infoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(pnl_song_infoLayout.createSequentialGroup()
                .addGap(22, 22, 22)
                .addComponent(lbl_song_name, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(lbl_song_artist_name, javax.swing.GroupLayout.PREFERRED_SIZE, 15, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 37, Short.MAX_VALUE))
            .addComponent(lbl_song_cover, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 319, Short.MAX_VALUE)
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 73, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(pnl_panels, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(482, 482, 482)
                        .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(pnl_song_info, javax.swing.GroupLayout.PREFERRED_SIZE, 269, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(pnl_song_playing, javax.swing.GroupLayout.PREFERRED_SIZE, 449, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addComponent(pnl_panels, javax.swing.GroupLayout.PREFERRED_SIZE, 554, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(pnl_song_info, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(pnl_song_playing, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addContainerGap(40, Short.MAX_VALUE))))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void ConfigWindow() {
        Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();
        int x = (int) ((dimension.getWidth() - this.getWidth()) / 2);
        int y = (int) ((dimension.getHeight() - this.getHeight()) / 2);
        this.setLocation(x, y);
        int width =  (int) (dimension.getWidth());                  // Center the window
        int height = (int) (dimension.getHeight());                 // Center the window
        
        
        lbl_song_name.setForeground(light_gray_1);
        lbl_song_artist_name.setForeground(light_gray_2);
        
    }
    private void initPlayList(){
        DefaultListModel listModel = new DefaultListModel();
        ArrayList<PlayList> playListArray = Interface.controller.user.playlist;
        for (PlayList playLista : playListArray){
            listModel.addElement(playLista);
        }
        this.playList.setModel(listModel);
    }
    private void LoadSong(){
//        JFXPanel j = new JFXPanel();
//        if (playing == true) {
//            player.dispose();
//            playing = false;
//        }
//        String name_song = new File("Brillas.mp3").toURI().toString();;
//        pick = new Media(name_song);
//        player = new MediaPlayer(pick);
//        playing = true;
        
    }
    
    
    
    
    
    private void PauseSong() {
//        player.pause();
        btn_play.setText("▶");
//        pause = true;
    }
    
    private void PlaySong() {
//        player.play();
        btn_play.setText("⏸");
//        pause = false;
    }
    
    private void RestartSong() {
//        player.stop();
//        if (!pause){
//            PlaySong();
//        }
    }
    
    private void UpdateBarTime(int progress){
        
    }
    
    public void updateProgressBar(final int j) {
//        SwingUtilities.invokeLater(new Runnable() {
//            @Override
//            public void run() {
//                System.out.println("Runnig by " + player.getTotalDuration());
////                UpdateBarTime(Math.round(player.getTotalDuration()/player.getCurrentTime()));
//            }
//        });            
    }
    
     private void AdjustIconVolume() {
        float value = getVolume();
        if (value == 0.0){
            btn_mute.setText("🔇");
        }else if (value < 0.2){
            btn_mute.setText("🔈");
        }else if (value < 0.6){
            btn_mute.setText("🔉");
        }else if (value <= 1){
            btn_mute.setText("🔊");
        }else{
            btn_mute.setText("XX");
        }
    }
    private void setVolume(float value) {
//        player.setVolume(value);
//        sld_volume.setValue((int) (value*maxVolume()));
        AdjustIconVolume();
    }
    private float getVolume() {
        return sld_volume.getValue()/maxVolume();
    }
    private float maxVolume() {
        return sld_volume.getMaximum();
    }
    private float minVolume() {
        return sld_volume.getMinimum();
    }
    private void MutePlayer() {
        float value = getVolume();
        if (value == 0.0){
            if (prev_volume < 0){
                prev_volume = minVolume();
            }
            setVolume(prev_volume);
        }else{
            prev_volume = value;
            setVolume(minVolume());
        }
    }
    private void prg_timeComponentShown(java.awt.event.ComponentEvent evt) {//GEN-FIRST:event_prg_timeComponentShown
        // TODO add your handling code here:
        System.out.println("Estoy corriendo");
    }//GEN-LAST:event_prg_timeComponentShown

    private void btn_playActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_playActionPerformed
        // TODO add your handling code here:
        if (pause == true){
            PlaySong();
        }else{
            PauseSong();
        }

        //JOptionPane.showMessageDialog(rootPane, name_song);
    }//GEN-LAST:event_btn_playActionPerformed

    private void btn_prevActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_prevActionPerformed
        // TODO add your handling code here:
        RestartSong();
    }//GEN-LAST:event_btn_prevActionPerformed

    private void btn_muteActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btn_muteActionPerformed
        // TODO add your handling code here:
        MutePlayer();
    }//GEN-LAST:event_btn_muteActionPerformed

    private void sld_volumeStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_sld_volumeStateChanged
        // TODO add your handling code here:
        setVolume(getVolume());
    }//GEN-LAST:event_sld_volumeStateChanged

    private void playListMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_playListMouseClicked
        PlayList now = (PlayList) this.playList.getSelectedValue();
        DefaultListModel listModel = new DefaultListModel();
        ArrayList<Music> musicArray = now.musicList;
        for (Music music : musicArray){
            listModel.addElement(music);
        }
        this.songsList.setModel(listModel);
    }//GEN-LAST:event_playListMouseClicked

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Interface.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Interface.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Interface.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Interface.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        new SwingBackgroupWorker().execute();
        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Interface().setVisible(true);
                
            }
        });
    }
    
    
    
    public static class SwingBackgroupWorker extends SwingWorker<Object, Object> {
        @Override
        protected Object doInBackground() throws Exception {
            while (true) {
                System.out.println("working");
                java.awt.EventQueue.invokeLater(new Runnable() {
                    public void run() {
                        System.out.println("executed");
                        // here the swing update
                    }
                });
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btn_mute;
    private javax.swing.JButton btn_next;
    private javax.swing.JButton btn_play;
    private javax.swing.JButton btn_prev;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane4;
    private javax.swing.JTabbedPane jTabbedPane1;
    private javax.swing.JLabel lbl_song_artist_name;
    private javax.swing.JLabel lbl_song_cover;
    private javax.swing.JLabel lbl_song_name;
    private javax.swing.JList playList;
    private javax.swing.JPanel pnl_panels;
    private javax.swing.JPanel pnl_panels_account;
    private javax.swing.JPanel pnl_panels_allSongs;
    private javax.swing.JPanel pnl_panels_myPlaylist;
    private javax.swing.JPanel pnl_song_info;
    private javax.swing.JPanel pnl_song_playing;
    private javax.swing.JProgressBar prg_time;
    private javax.swing.JSlider sld_volume;
    private javax.swing.JList songsList;
    private javax.swing.JTable songsTable;
    private javax.swing.JLabel userNameText;
    // End of variables declaration//GEN-END:variables
}
