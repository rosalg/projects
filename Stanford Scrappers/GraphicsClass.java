

import java.applet.AudioClip;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

import CharacterModels.BodyConstants;
import CharacterModels.PlayerInstructions;
import Characters.PlayableCharacter;
import maps.MapConstants;
import acm.graphics.GImage;
import acm.graphics.GLabel;
import acm.graphics.GOval;
import acm.io.IODialog;
import acm.program.GraphicsProgram;
import acm.util.*;
import acm.graphics.*;

public class GraphicsClass extends GraphicsProgram implements ComponentListener, MapEnnumerations, MapConstants, BodyConstants {
	
	PlayableCharacter player1;
	PlayableCharacter player2;
	MapSelectionClass mapSelection;
	String[] names = new String[2];
	String testChange = "Yes";	
	
	double pauseTime = 4;
	GImage mapChoice;
	int gameStage;
	int mapNumber;
	int loopTracker;
	
	/**
	 * All the instance variables to properly scale objects in the canvas.
	 */
	double updatingWidth;
	double updatingHeight;
	double initWidth;
	double initHeight;
	double scaleFactor = 1;
	GLabel welcome;
	double welcomeFontSize = 19;
	double gameNameFontSize = 30;
	private GLabel gameName;
	private GLabel clickToContinue;
	private PlayerInstructions player1Instructions;
	private PlayerInstructions player2Instructions;
	private GImage logo;
	private GImage menuScreen;
	private GLabel playGame;
	private GLabel credits;
	private GLabel mainMenu;
	private GLabel tutorial;
	private GOval playGameDot;
	private GOval creditsDot;
	private GOval instructionsDot;
	private GLabel back;
	private GLabel imageThanks;
	private GLabel musicThanks;
	
	private int colorSelect;
	private Color player1ShirtColor;
	private Color player1PantsColor;
	private Color player1ShoeColor;
	private Color player2ShirtColor;
	private Color player2PantsColor;
	private Color player2ShoeColor;
	
	
	AudioClip gameMusic;
	AudioClip mapSelectMusic = MediaTools.loadAudioClip("mapselect.wav");
	
	public void setGameMusic(AudioClip selectedMapMusic) {
		gameMusic = selectedMapMusic;
	}
	
	public void keyPressed(KeyEvent e) {
		switch(e.getKeyCode()) {
			case KeyEvent.VK_D:
				player1.setSpeedUpRightCheck(true);
				break;
			case KeyEvent.VK_A:
				player1.setSpeedUpLeftCheck(true);
				break;
			case KeyEvent.VK_W:
				if (player1.getvy() <= 0) {
					player1.setJumpCheck(true);
				}
				break;
			case KeyEvent.VK_S:
				player1.setFallThroughCheck(true);
				break;
			case KeyEvent.VK_L:
				player2.setSpeedUpRightCheck(true);
				break;
			case KeyEvent.VK_J:
				player2.setSpeedUpLeftCheck(true);
				break;
			case KeyEvent.VK_I:
				if (player2.getvy() <= 0) {
					player2.setJumpCheck(true);
				}
				break;
			case KeyEvent.VK_K:
				player2.setFallThroughCheck(true);
				break;
		}
	}
	
	public void keyReleased(KeyEvent e) {
		switch(e.getKeyCode()) {
			case KeyEvent.VK_D:
				player1.setSpeedUpRightCheck(false);
				player1.setSlowDownRightCheck(true);
				break;
			case KeyEvent.VK_A:
				player1.setSpeedUpLeftCheck(false);
				player1.setSlowDownLeftCheck(true);
				break;
			case KeyEvent.VK_L:
				player2.setSpeedUpRightCheck(false);
				player2.setSlowDownRightCheck(true);
				break;
			case KeyEvent.VK_J:
				player2.setSpeedUpLeftCheck(false);
				player2.setSlowDownLeftCheck(true);
		}
	}
	
	public void keyTyped(KeyEvent e) {
		Character c = e.getKeyChar();
		if (c == 'v') {
			player1.setPunchRightCheck(true);
		}
		if (c == '/') {
			player2.setPunchRightCheck(true);
		}
		if (c == 'x') {
			player1.setPunchLeftCheck(true);
		}
		if (c == ',') {
			player2.setPunchLeftCheck(true);
		}
		if (c == 'c') {
			player1.setRangedAttackCheck(true);
		}
		if (c == '.') {
			player2.setRangedAttackCheck(true);
		}
		if (c == ' ') {
			loopTracker = 0;
		}
	}
	
	public void mousePressed(MouseEvent e) {
		loopTracker = 0;
		if (getElementAt(e.getX(), e.getY()) == playGame) {
			gameStage = STAGE_SELECTION;
		} else if (getElementAt(e.getX(), e.getY()) == credits) {
			gameStage = CREDITS;
		} else if (getElementAt(e.getX(), e.getY()) == back) {
			gameStage = MENU;
		} else if (getElementAt(e.getX(), e.getY()) == tutorial) {
			gameStage = INSTRUCTIONS;
		}
	}
	
	public void mouseMoved(MouseEvent e) {
		if (gameStage == MENU) {
			if (getElementAt(e.getX(), e.getY()) == playGame) {
				playGame.setColor(Color.black);
			} else {
				playGame.setColor(Color.white);
			}
		}
		if (gameStage == MENU) {
			if (getElementAt(e.getX(), e.getY()) == credits) {
				credits.setColor(Color.black);
			} else {
				credits.setColor(Color.white);
			}
		}
		if (gameStage == CREDITS || gameStage == INSTRUCTIONS) {
			if (getElementAt(e.getX(), e.getY()) == back) {
				back.setColor(Color.black);
			} else {
				back.setColor(Color.white);
			}
		}
		if (gameStage == MENU) {
			if (getElementAt(e.getX(), e.getY()) == tutorial) {
				tutorial.setColor(Color.black);
			} else {
				tutorial.setColor(Color.white);
			}
		}
	}
	
 	public void actionPerformed(ActionEvent e) {
		String cmd = e.getActionCommand();
		mapChoice = mapSelection.getMapChoice(cmd);
		add(getGCanvas());
		repaint();
		getGCanvas().setBounds(0, 0, getWidth(), getHeight());
	}
	
	public void init() {
		addComponentListener(this);
	}
	
	public void run() {
		initWidth = getWidth();
		initHeight = getHeight();
		updatingWidth = getWidth();
		updatingHeight= getHeight();
		boolean continuePlaying = true;
		showTitleScreen();
		while(continuePlaying) {
			showMenu();
			if (gameStage == STAGE_SELECTION) {
				mapSelectionProcess();
				getPlayerNames();
				addPlatforms();
				initializeGameConditions();
				mapSelectMusic.stop();
				gameMusic.loop();
				addKeyListeners(player1);
				countdown();
				while(true) {
					allMethodsDuringGame();
					if (player1.getHealth() <= 0 || player2.getHealth() <= 0) break;
				}
				String labelSize = Integer.toString(getWidth()/40);
				add(player1.updateHealthBar(getWidth(), getHeight()), 0, player1.getPlayerLabel(labelSize).getAscent());
				add(player2.updateHealthBar(getWidth(), getHeight()), getWidth()-player2.updateHealthBar(getWidth(), getHeight()).getWidth(), player1.getPlayerLabel(labelSize).getAscent());
				winnerScreen();
				IODialog dialog = getDialog();
				continuePlaying = dialog.readBoolean("Return to main menu?", "Yes", "No");
				removeAll();
				if (continuePlaying) gameMusic.stop();
			} else if (gameStage == CREDITS) {
				showCredits();
			} else if (gameStage == INSTRUCTIONS) {
				showTutorial();
			}
			
		}
		showEndScreen(player1, player2);
	}
	
	private void displayDuringGame() {
		getGCanvas().setBounds(0, 0, getWidth(), getHeight());
		mapChoice.setSize(getWidth(), getHeight());
		add(mapChoice);
		mapChoice.sendToBack();
	}
	
	private void playerDuringGame(PlayableCharacter player, PlayableCharacter opponent, double healthBarX, double healthBarY, double nameX, double nameY) {
		player.checkPlayerActions(opponent, getHeight(), getWidth());
		player.move();
		String labelSize = Integer.toString(getWidth()/40);
		add(player.getPlayerLabel(labelSize), nameX, nameY);
		add(player.updateHealthBar(getWidth(), getHeight()), healthBarX, healthBarY);
		if (player.getProjectile() != null) {
			player.getProjectile().moveProjectile();
			player.getProjectile().checkProjectileCollision(getGCanvas(), mapChoice, opponent);
		}
	}
	
	private void allMethodsDuringGame() {
		String labelSize = Integer.toString(getWidth()/40);
		displayDuringGame();
		playerDuringGame(player1, player2, 0, player1.getPlayerLabel(labelSize).getAscent(), 0, player1.getPlayerLabel(labelSize).getAscent());
		playerDuringGame(player2, player1, getWidth()-player2.updateHealthBar(getWidth(), getHeight()).getWidth(), player2.getPlayerLabel(labelSize).getAscent(), getWidth()-player2.getPlayerLabel(labelSize).getWidth(), player2.getPlayerLabel(labelSize).getAscent());
		pause(pauseTime);
	}
	
	private void getPlayerNames() {
		IODialog dialog = getDialog();
		for (int i = 0; i <= 1; i ++) {
			names[i] = dialog.readLine("Please enter the name of player " + (i + 1) +".").toUpperCase();
		}
	}

	public void update() {
		if (getWidth() != updatingWidth && gameStage == PLAYING_GAME) {
			updateGame();
		}
		if (gameStage == WELCOME && getWidth() != updatingWidth) {
			updateTitleScreen();
		}
		if (player1 != null && player2 != null) {
			player1.getCharacterModel(STATIONARY_MODEL).setLocation(player1.getCharacterModel(STATIONARY_MODEL).getX()*getWidth()/initWidth, player1.getCharacterModel(STATIONARY_MODEL).getY()*getHeight()/initHeight);
			player2.getCharacterModel(STATIONARY_MODEL).setLocation(player2.getCharacterModel(STATIONARY_MODEL).getX()*getWidth()/initWidth, player2.getCharacterModel(STATIONARY_MODEL).getY()*getHeight()/initHeight);
		}
		if (gameStage == STAGE_SELECTION) {
			MapSelectionClass.addImageToCanvas("Map1.jpg", MapSelectionClass.map1Canvas);
			MapSelectionClass.addImageToCanvas("Map2.jpg", MapSelectionClass.map2Canvas);
			MapSelectionClass.addImageToCanvas("Map3.jpg", MapSelectionClass.map3Canvas);
			MapSelectionClass.addImageToCanvas("Map4.jpg", MapSelectionClass.map4Canvas);
			MapSelectionClass.addImageToCanvas("Map5.jpg", MapSelectionClass.map5Canvas);
			MapSelectionClass.addImageToCanvas("Map6.jpg", MapSelectionClass.map6Canvas);
		}
		if (gameStage == CREDITS) {
			menuScreen.setSize(getWidth(), getHeight());
			back.setFont("SansSerif-Bold-"+Math.round(40*getWidth()/initWidth));
			back.setLocation(0, back.getAscent());
			imageThanks.setFont("SansSerif-Bold-"+Math.round(20*getWidth()/initWidth));
			imageThanks.setLocation(getWidth()/2-imageThanks.getWidth()/2, imageThanks.getY()*getHeight()/initHeight);
			musicThanks.setFont("SansSerif-Bold-"+Math.round(20*getWidth()/initWidth));
			musicThanks.setLocation(getWidth()/2-musicThanks.getWidth()/2, musicThanks.getY()*getHeight()/initHeight);
		}
		if (gameStage == INSTRUCTIONS) {
			menuScreen.setSize(getWidth(), getHeight());
			back.setFont("SansSerif-Bold-"+Math.round(40*getWidth()/initWidth));
			back.setLocation(0, back.getAscent());
			player1Instructions.updateFontSize(getWidth()/initWidth);
			player2Instructions.updateFontSize(getWidth()/initWidth);
			player1Instructions.setLocation(getWidth()/4-player1Instructions.getWidth()/2, getHeight()/2-player1Instructions.getHeight()/2);
			player2Instructions.setLocation(getWidth()*3/4-player2Instructions.getWidth()/2, getHeight()/2-player1Instructions.getHeight()/2);
		}
		getGCanvas().setBounds(0, 0, getWidth(), getHeight());
		validate();
	}
	
	private void mapSelectionProcess() {
		mapChoice = null;
		mapSelectMusic.play();
		mapSelection = new MapSelectionClass(this);
		remove(getGCanvas());
		mapSelection.addAllButtons();
		addActionListeners();
		repaint();
		validate();
		while(mapChoice == null) {
			pause(0);
		}
	}		
	
	private void checkCharacterModelSize() {
		pauseTime = Math.round(4*initWidth/getWidth());
		scaleFactor = getWidth()/initWidth;
		player1.setVerticalScaleFactor(getHeight()/initHeight);
		player2.setVerticalScaleFactor(getHeight()/initHeight);
		player1.setHorizontalScaleFactor(getWidth()/initWidth);
		player2.setHorizontalScaleFactor(getWidth()/initWidth);
		pauseTime = pauseTime*(1/scaleFactor);
		for (int i = 0; i <= 5; i++) {
			player1.getCharacterModel(i).scale(getWidth()/initWidth, getHeight()/initHeight);
		}
		for (int i = 0; i <= 5; i++) {
			player2 .getCharacterModel(i).scale(getWidth()/initWidth, getHeight()/initHeight);
		}
		updatingWidth = getWidth();
		updatingHeight = getHeight();
	}
	
	private void initializeGameConditions() {
		player1 = new PlayableCharacter(Color.green, Color.blue, Color.black, getGCanvas(), 0, getHeight(), names[0], mapChoice, scaleFactor, getHeight()/initHeight);
		player2 = new PlayableCharacter(Color.red, Color.gray, Color.black, getGCanvas(), getWidth()-player1.getCharacterModel(STATIONARY_MODEL).getWidth(), getHeight(), names[1], mapChoice, scaleFactor, getHeight()/initHeight);
		player1.getProjectile().setProjectileRadius(getWidth()/initWidth);
		player2.getProjectile().setProjectileRadius(getWidth()/initWidth);
		gameStage = PLAYING_GAME;
		checkCharacterModelSize();
		addKeyListeners();
	}

	private void addPlatforms() {
		if (mapNumber == 1) {
			createMapOne();
		} else if (mapNumber == 2) {
			createMapTwo();
		} else if (mapNumber == 3) {
			createMapThree();
		} else if (mapNumber == 4) {
			createMapFour();
		} else if (mapNumber == 5) {
			createMapFive();
		} else if (mapNumber == 6) {
			createMapSix();
		} 
	}
	
	private void createMapOne() {
		double largePlatformWidth = 200*getWidth()/initWidth;
		double platformHeight = 10*getHeight()/initHeight;
		double mediumPlatformWidth = 100*getWidth()/initWidth;
 		
		LARGE_PLATFORM.setFilled(true);
		LARGE_PLATFORM.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM, 0, (initHeight-70)*getHeight()/initHeight);

		LARGE_PLATFORM_1.setFilled(true);
		LARGE_PLATFORM_1.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_1, getWidth()-largePlatformWidth, (initHeight-70)*getHeight()/initHeight);
	
		LARGE_PLATFORM_2.setFilled(true);
		LARGE_PLATFORM_2.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_2, getWidth()/2-largePlatformWidth/2, getHeight()/1.5);
		
		MEDIUM_PLATFORM.setFilled(true);
		MEDIUM_PLATFORM.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM, largePlatformWidth/4, getHeight()/2);
		
		MEDIUM_PLATFORM_1.setFilled(true);
		MEDIUM_PLATFORM_1.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM_1, getWidth()-mediumPlatformWidth-largePlatformWidth/4, getHeight()/2);
	}
	
	private void createMapTwo() {
		double largePlatformWidth = 200*getWidth()/initWidth;
		double platformHeight = 10*getHeight()/initHeight;
		double mediumPlatformWidth = 100*getWidth()/initWidth;
		double smallPlatformWidth = 50*getWidth()/initWidth;
		
		LARGE_PLATFORM.setFilled(true);
		LARGE_PLATFORM.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM, (getWidth()-largePlatformWidth)/2, getHeight()*3/4);
		
		LARGE_PLATFORM_1.setFilled(true);
		LARGE_PLATFORM_1.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_1, (getWidth()-largePlatformWidth)/2, getHeight()*2/4);
		
		SMALL_PLATFORM.setFilled(true);
		SMALL_PLATFORM.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM, 0, getHeight()*4/5);
		
		SMALL_PLATFORM_2.setFilled(true);
		SMALL_PLATFORM_2.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_2, getWidth()-smallPlatformWidth, getHeight()*4/5);
		
		MEDIUM_PLATFORM.setFilled(true);
		MEDIUM_PLATFORM.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM, smallPlatformWidth, getHeight()*3/5);
		
		MEDIUM_PLATFORM_1.setFilled(true);
		MEDIUM_PLATFORM_1.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM_1, getWidth()-mediumPlatformWidth-smallPlatformWidth, getHeight()*3/5);
		
		SMALL_PLATFORM_1.setFilled(true);
		SMALL_PLATFORM_1.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_1, MEDIUM_PLATFORM.getX()+smallPlatformWidth, getHeight()*4/5);
		
		SMALL_PLATFORM_3.setFilled(true);
		SMALL_PLATFORM_3.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_3, getWidth()-3*smallPlatformWidth, getHeight()*4/5);
	}
	
	private void createMapThree() {
		double largePlatformWidth = 200*getWidth()/initWidth;
		double platformHeight = 10*getHeight()/initHeight;
		double mediumPlatformWidth = 100*getWidth()/initWidth;
		double smallPlatformWidth = 50*getWidth()/initWidth;
		
		LARGE_PLATFORM.setFilled(true);
		LARGE_PLATFORM.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM, 0, getHeight()*3/4);
		
		LARGE_PLATFORM_1.setFilled(true);
		LARGE_PLATFORM_1.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_1, getWidth()-largePlatformWidth, getHeight()*3/4);
		
		LARGE_PLATFORM_2.setFilled(true);
		LARGE_PLATFORM_2.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_2, (getWidth()-largePlatformWidth)/2, getHeight()*3/4);
		
		LARGE_PLATFORM_3.setFilled(true);
		LARGE_PLATFORM_3.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_3, (getWidth()-largePlatformWidth)/2, getHeight()*2/4);
		
		MEDIUM_PLATFORM.setFilled(true);
		MEDIUM_PLATFORM.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM, smallPlatformWidth, getHeight()*3/5);

		MEDIUM_PLATFORM_1.setFilled(true);
		MEDIUM_PLATFORM_1.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM_1, getWidth()-mediumPlatformWidth-smallPlatformWidth, getHeight()*3/5);
		
		SMALL_PLATFORM.setFilled(true);
		SMALL_PLATFORM.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM, largePlatformWidth, getHeight()*3/5);
		
		SMALL_PLATFORM_1.setFilled(true);
		SMALL_PLATFORM_1.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_1, getWidth()-smallPlatformWidth-largePlatformWidth, getHeight()*3/5);
	}
	
	private void createMapFour() {
		double largePlatformWidth = 200*getWidth()/initWidth;
		double platformHeight = 10*getHeight()/initHeight;
		double mediumPlatformWidth = 100*getWidth()/initWidth;
		double smallPlatformWidth = 50*getWidth()/initWidth;
		
		SMALL_PLATFORM.setFilled(true);
		SMALL_PLATFORM.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM, getWidth()/4-smallPlatformWidth, getHeight()*4/5);
		
		SMALL_PLATFORM_1.setFilled(true);
		SMALL_PLATFORM_1.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_1, getWidth()/2-smallPlatformWidth, getHeight()*4/5);
		
		SMALL_PLATFORM_2.setFilled(true);
		SMALL_PLATFORM_2.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_2, getWidth()*3/4-smallPlatformWidth, getHeight()*4/5);
		
		SMALL_PLATFORM_3.setFilled(true);
		SMALL_PLATFORM_3.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_3, getWidth()-smallPlatformWidth, getHeight()*4/5);
		
		SMALL_PLATFORM_4.setFilled(true);
		SMALL_PLATFORM_4.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_4, 0, getHeight()*4/5);

		MEDIUM_PLATFORM.setFilled(true);
		MEDIUM_PLATFORM.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM, getWidth()/4, getHeight()*3/5);
		
		MEDIUM_PLATFORM_1.setFilled(true);
		MEDIUM_PLATFORM_1.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM_1, getWidth()-getWidth()/4-mediumPlatformWidth, getHeight()*3/5);

		MEDIUM_PLATFORM_2.setFilled(true);
		MEDIUM_PLATFORM_2.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM_2, getWidth()-mediumPlatformWidth, getHeight()*3/5);
		
		MEDIUM_PLATFORM_3.setFilled(true);
		MEDIUM_PLATFORM_3.setSize(mediumPlatformWidth, platformHeight);
		add(MEDIUM_PLATFORM_3, 0, getHeight()*3/5);

		LARGE_PLATFORM.setFilled(true);
		LARGE_PLATFORM.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM, 0, getHeight()*2/5);
		
		LARGE_PLATFORM_1.setFilled(true);
		LARGE_PLATFORM_1.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_1, getWidth()-largePlatformWidth, getHeight()*2/5);
		
		LARGE_PLATFORM_2.setFilled(true);
		LARGE_PLATFORM_2.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_2, getWidth()/2-largePlatformWidth/2, getHeight()*2/5);
	}
	
	private void createMapFive() {
		double largePlatformWidth = 200*getWidth()/initWidth;
		double platformHeight = 10*getHeight()/initHeight;
		double smallPlatformWidth = 50*getWidth()/initWidth;
		
		SMALL_PLATFORM.setFilled(true);
		SMALL_PLATFORM.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM, 0, getHeight()*4/5);
		
		SMALL_PLATFORM_1.setFilled(true);
		SMALL_PLATFORM_1.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_1, 0, getHeight()*3/5);
		
		SMALL_PLATFORM_2.setFilled(true);
		SMALL_PLATFORM_2.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_2, 0, getHeight()*2/5);

		SMALL_PLATFORM_3.setFilled(true);
		SMALL_PLATFORM_3.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_3, getWidth()-smallPlatformWidth, getHeight()*2/5);
		
		SMALL_PLATFORM_4.setFilled(true);
		SMALL_PLATFORM_4.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_4, getWidth()-smallPlatformWidth, getHeight()*3/5);

		SMALL_PLATFORM_5.setFilled(true);
		SMALL_PLATFORM_5.setSize(smallPlatformWidth, platformHeight);
		add(SMALL_PLATFORM_5, getWidth()-smallPlatformWidth, getHeight()*4/5);

		LARGE_PLATFORM.setFilled(true);
		LARGE_PLATFORM.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM, getWidth()/2-largePlatformWidth, getHeight()*2/5);

		LARGE_PLATFORM_1.setFilled(true);
		LARGE_PLATFORM_1.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_1, getWidth()/2, getHeight()*3/5);
		
		LARGE_PLATFORM_2.setFilled(true);
		LARGE_PLATFORM_2.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM_2, getWidth()/2-largePlatformWidth, getHeight()*4/5);
		
	}
	
	private void createMapSix() {
		double largePlatformWidth = 200*getWidth()/initWidth;
		double platformHeight = 10*getHeight()/initHeight;
		
		LARGE_PLATFORM.setFilled(true);
		LARGE_PLATFORM.setSize(largePlatformWidth, platformHeight);
		add(LARGE_PLATFORM, getWidth()/2-largePlatformWidth/2, getHeight()*3/4);
	}
	
	public void setMapNumber(int newMapNumber) {
		mapNumber = newMapNumber;
	}
	
	private void winnerScreen() {
		player1.checkModelRemove();
		player2.checkModelRemove();
		int winningPlayer = 0;
		if (player1.getHealth() <= 0) {
			add(player2.getCharacterModel(STATIONARY_MODEL), getWidth()/2-player2.getCharacterModel(STATIONARY_MODEL).getWidth()/2, getHeight());
			winningPlayer = 2;
		} else {
			add(player1.getCharacterModel(STATIONARY_MODEL), getWidth()/2-player2.getCharacterModel(STATIONARY_MODEL).getWidth()/2, getHeight());
			winningPlayer = 1;
		}
		addMouseListeners();
		loopTracker = 1;
		GLabel celebrationText = new GLabel("Congratulations player "+ winningPlayer + ", you won! Click to continue.");
		celebrationText.setFont("SansSerif-Bold-25");
		while (loopTracker == 1) {
			add(celebrationText, getWidth()/2-celebrationText.getWidth()/2, getHeight()/2+celebrationText.getAscent());
			celebrationText.setColor(rgen.nextColor());
			if (winningPlayer == 1) {
				celebration(player1, player2);
			} else {
				celebration(player2, player1);
			}
		}
	}
	
	private void countdown() {
		for (int i = 3; i >= 1; i--) {
			mapChoice.setSize(getWidth(), getHeight());
			add(mapChoice);
			mapChoice.sendToBack();
			GLabel countdown = new GLabel("Starting in " + i + "...");
			countdown.setFont("SansSerif-Bold-" + Math.round((30*getHeight()/initHeight)));
			countdown.setColor(Color.white);
			add(countdown, getWidth()/2-countdown.getWidth()/2, getHeight()/2+countdown.getAscent()/2);
			pause(1000);
			remove(countdown);
			if (i == 1) {
				countdown = new GLabel("Go!");
				countdown.setColor(Color.white);
				countdown.setFont("SansSerif-Bold-" + Math.round((30*getHeight()/initHeight)));
				add(countdown, getWidth()/2-countdown.getWidth()/2, getHeight()/2+countdown.getAscent()/2);
				pause(1000);
				remove(countdown);
			}
		}
	}
	
	private void celebration(PlayableCharacter player, PlayableCharacter opponent) {
		add(opponent.getCharacterModel(STATIONARY_MODEL));
		opponent.getCharacterModel(STATIONARY_MODEL).setLocation(getWidth()/2-opponent.getCharacterModel(STATIONARY_MODEL).getWidth()/2, getHeight()+opponent.getCharacterModel(STATIONARY_MODEL).getHeight()-2*HEAD_HEIGHT*getHeight()/initHeight);
		player.getCharacterModel(STATIONARY_MODEL).move(0, -(initHeight/30)*getHeight()/initHeight);
		pause(100);
		player.getCharacterModel(STATIONARY_MODEL).move(0, (initHeight/30)*getHeight()/initHeight);
		pause(100);
	}
	
	private void showEndScreen(PlayableCharacter player1, PlayableCharacter player2) {
		while(true) {
			mapChoice.setSize(getWidth(), getHeight());
			add(mapChoice);
			GLabel thanks = new GLabel("Thanks for playing!");
			thanks.setFont("SansSerif-Bold-"+Math.round(40*getWidth()/initWidth));
			thanks.setColor(Color.white);
			add(thanks, getWidth()/2-thanks.getWidth()/2, getHeight()/2+thanks.getAscent()/2);
			add(player1.getCharacterModel(STATIONARY_MODEL), getWidth()/4,getHeight());
			add(player2.getCharacterModel(STATIONARY_MODEL), getWidth()*3/4, getHeight());
			player1.getCharacterModel(STATIONARY_MODEL).move(0, -(initHeight/30)*getHeight()/initHeight);
			player2.getCharacterModel(STATIONARY_MODEL).move(0, -(initHeight/30)*getHeight()/initHeight);
			pause(100);
			player1.getCharacterModel(STATIONARY_MODEL).move(0, (initHeight/30)*getHeight()/initHeight);
			player2.getCharacterModel(STATIONARY_MODEL).move(0, (initHeight/30)*getHeight()/initHeight);
			pause(100);
		}
	}
	
	private void updateGame() {
		scaleFactor = getWidth()/updatingWidth;
		player1.setVerticalScaleFactor(getHeight()/initHeight);
		player2.setVerticalScaleFactor(getHeight()/initHeight);
		player1.setHorizontalScaleFactor(getWidth()/initWidth);
		player2.setHorizontalScaleFactor(getWidth()/initWidth);
		pauseTime = Math.round(4*(initWidth/getWidth()));
		addPlatforms();
		for (int i = 0; i <= 5; i++) {
			player1.getCharacterModel(i).scale(getWidth()/updatingWidth, getHeight()/updatingHeight);
		}
		for (int i = 0; i <= 5; i++) {
			player2 .getCharacterModel(i).scale(getWidth()/updatingWidth, getHeight()/updatingHeight);
		}
		player1.getProjectile().setProjectileRadius(getWidth()/initWidth);
		player2.getProjectile().setProjectileRadius(getWidth()/initWidth);
		updatingWidth = getWidth();
		updatingHeight = getHeight();
	}
	
	private void updateTitleScreen() {
		scaleFactor = getWidth()/updatingWidth;
		logo.setSize(getWidth()/1.5, getHeight());
		add(logo, getWidth()/2-logo.getWidth()/2, 0);
		logo.sendToBack();
		welcomeFontSize = welcomeFontSize * scaleFactor;
		int temp = (int) welcomeFontSize;
		welcome.setFont("SansSerif-Bold-"+temp );
		gameNameFontSize = gameNameFontSize * scaleFactor;
		clickToContinue.setFont("SansSerif-Bold-"+Math.round(20*getWidth()/initWidth));
		temp = (int) gameNameFontSize;
		gameName.setFont("SansSerif-Bold-"+temp);
		gameName.setLocation(getWidth()/2-gameName.getWidth()/2, getHeight()/2+gameName.getAscent()/2);
		welcome.setLocation(gameName.getX(), gameName.getY()-gameName.getAscent());
		clickToContinue.setLocation(getWidth()/2-clickToContinue.getWidth()/2, getHeight()-clickToContinue.getAscent());
		updatingWidth = getWidth();
		updatingHeight = getHeight();
	}
	
	private void showTitleScreen() {
		AudioClip titleScreen = MediaTools.loadAudioClip("titlescreen.au");
		titleScreen.loop();
		welcome = new GLabel("Welcome to");
		welcome.setFont("SansSerif-Bold-"+ Math.round(19*scaleFactor));
		gameName = new GLabel("STANFORD SCRAPPERS");
		gameName.setFont("SanSerif-Bold-"+ Math.round(40*scaleFactor));
		clickToContinue = new GLabel("Click to continue to the menu");
		clickToContinue.setFont("SansSerif-Bold-"+Math.round(20*scaleFactor));
		logo = new GImage("StanfordLogo.jpg");
		logo.setSize(getWidth()/1.5, getHeight());
		add(logo, getWidth()/2-logo.getWidth()/2, 0);
		add(gameName, getWidth()/2-gameName.getWidth()/2, getHeight()/2);
		add(welcome, gameName.getX(), gameName.getY()-gameName.getAscent());
		add(clickToContinue, getWidth()/2-clickToContinue.getWidth()/2, getHeight()-clickToContinue.getAscent());
		gameStage = WELCOME;
		loopTracker = 1; 
		addMouseListeners();
		while (loopTracker != 0) {
			clickToContinue.setColor(Color.white);
			pause(500);
			clickToContinue.setColor(Color.black);
			pause(500);
		}
		titleScreen.stop();
		removeAll();
	}
	
	private void showMenu() {
		AudioClip menuMusic = MediaTools.loadAudioClip("map1music.au");
		menuMusic.loop();
		loopTracker = 1;
		menuScreen = new GImage("menuArt.png");
		mainMenu = new GLabel("Main Menu");
		playGame = new GLabel("Play game");
		credits = new GLabel("Credits");
		tutorial = new GLabel("Instructions");
		
		playGameDot = new GOval(0,0);
		creditsDot = new GOval(0,0);
		instructionsDot = new GOval(0,0);
		
		tutorial.setColor(Color.white);
		playGame.setColor(Color.white);
		mainMenu.setColor(Color.white);
		credits.setColor(Color.white);
		
		playGameDot.setFilled(true);
		playGameDot.setColor(Color.white);
		creditsDot.setFilled(true);
		creditsDot.setColor(Color.white);
		instructionsDot.setFilled(true);
		instructionsDot.setColor(Color.white);
		
		add(menuScreen);
		add(mainMenu);
		add(playGame);
		add(credits);
		add(playGameDot);
		add(creditsDot);
		add(tutorial);
		add(instructionsDot);
		addMouseListeners();
		gameStage = MENU;
		while (gameStage == MENU) {
			menuScreen.setSize(getWidth(), getHeight());
			mainMenu.setFont("SansSerif-Bold-"+Math.round(50*getWidth()/initWidth));
			mainMenu.setLocation(getWidth()/4-mainMenu.getWidth()/2, getHeight()/4+mainMenu.getAscent());
			playGame.setFont("SansSerif-Bold-"+Math.round(25*getWidth()/initWidth));
			playGame.setLocation(mainMenu.getX(), mainMenu.getY()+playGame.getAscent()*2);
			tutorial.setFont("SansSerif-Bold-"+Math.round(25*getWidth()/initWidth));
			tutorial.setLocation(credits.getX(), playGame.getY()+tutorial.getAscent()*2);
			credits.setFont("SansSerif-Bold-"+Math.round(25*getWidth()/initWidth));
			credits.setLocation(playGame.getX(), tutorial.getY()+tutorial.getAscent()*2);
			double r = playGame.getAscent()/2;
			playGameDot.setSize(r, r);
			playGameDot.setLocation(playGame.getX()-r*2,playGame.getY()-r*1.25);
			creditsDot.setSize(r, r);
			creditsDot.setLocation(credits.getX()-r*2, credits.getY()-r*1.25);
			instructionsDot.setSize(r, r);
			instructionsDot.setLocation(tutorial.getX()-r*2, tutorial.getY()-r*1.25);
		}
		remove(mainMenu); 
		remove(playGame);
		remove(credits);
		remove(playGameDot);
		remove(creditsDot);
		remove(tutorial);
		remove(instructionsDot);
		if (gameStage == STAGE_SELECTION) {
			menuMusic.stop();
			removeAll();
		}
	}
	
	private void showCredits() {
		menuScreen.setSize(getWidth(), getHeight());
		back = new GLabel("Back");
		back.setColor(Color.white);
		add(back);
		back.setFont("SansSerif-Bold-"+Math.round(40*getWidth()/initWidth));
		back.setLocation(0, back.getAscent());
		
		imageThanks = new GLabel("Thanks to Google images for providing all the images.");
		imageThanks.setColor(Color.white);
		add(imageThanks);
		imageThanks.setFont("SansSerif-Bold-"+Math.round(20*getWidth()/initWidth));
		imageThanks.setLocation(getWidth()/2-imageThanks.getWidth()/2, getHeight());
		
		musicThanks = new GLabel("Thanks to Jeremy LeveGood, YourRapBeatsTV, and N114 for the music");
		musicThanks.setColor(Color.white);
		add(musicThanks);
		musicThanks.setFont("SansSerif-Bold-"+Math.round(20*getWidth()/initWidth));
		musicThanks.setLocation(getWidth()/2-musicThanks.getWidth()/2, getHeight()+musicThanks.getAscent());
		while(gameStage == CREDITS) {
			double vy = -2*getWidth()/initWidth;
			if (imageThanks.getY() > 0) {
				imageThanks.move(0, vy);
				pause(40);
				if (imageThanks.getY() < getHeight()*4/5) {
					musicThanks.move(0, vy);
				}
			} else {
				remove(imageThanks);
				if (musicThanks.getY() > 0) {
					musicThanks.move(0, vy);
					pause(40);
				} else {
					remove(musicThanks);
				}
			}
		}
	}
	
	private void showTutorial() {
		back = new GLabel("Back");
		back.setColor(Color.white);
		add(back);
		back.setFont("SansSerif-Bold-"+Math.round(40*getWidth()/initWidth));
		back.setLocation(0, back.getAscent());
		
		player1Instructions = new PlayerInstructions(1, "w", "a", "s", "d", "x", "v", "c", getWidth()/initWidth);
		add(player1Instructions, getWidth()/4-player1Instructions.getWidth()/2, getHeight()/2-player1Instructions.getHeight()/2);
		player2Instructions = new PlayerInstructions(2, "i", "j", "k", "l", ",", "/", ".", getWidth()/initWidth);
		add(player2Instructions, getWidth()*3/4-player2Instructions.getWidth()/2, getHeight()/2+-player1Instructions.getHeight()/2);
		
		while(gameStage == INSTRUCTIONS) {
			pause(0);
		}
	}
	
	private void showCharacterSelect() {
		gameStage = CHARACTER_SELECT;
		removeAll();
		GLabel header = new GLabel("CHARACTER SELECT");
		header.setFont("SansSerif-Bold-40");
		header.setLocation(getWidth()/2-header.getWidth()/2, header.getAscent());
		add(header);
		
		GRect red = new GRect(getWidth()/10, getHeight()/4);
		red.setFilled(true);
		red.setColor(Color.red);
		add(red, getWidth()/4, getHeight()/4);
		
		loopTracker = 1;
		GLabel prompt = new GLabel("");
		while (player1ShirtColor == null) {
			prompt.setLabel("Player 1, select a shirt color.");
			prompt.setFont("SansSerif-Bold-20");
			prompt.setLocation(header.getX() + header.getWidth()/2 - prompt.getWidth()/2, header.getY()+prompt.getAscent());
			add(prompt);
		}
		while (player1PantsColor == null) {
			prompt.setLabel("Player 1, select a pants color.");
			prompt.setLocation(header.getX() + header.getWidth()/2 - prompt.getWidth()/2, header.getY()+prompt.getAscent());
		}
		while (player1ShoeColor == null) {
			prompt.setFont("Player1, select a shoe color.");
			prompt.setLocation(header.getX() + header.getWidth()/2 - prompt.getWidth()/2, header.getY()+prompt.getAscent());
		}
		while (loopTracker == 1) {
			pause(0);
		}
	}
	
	RandomGenerator rgen = RandomGenerator.getInstance();
	public void componentHidden(ComponentEvent e) { }
	public void componentMoved(ComponentEvent e) { }
	public void componentResized(ComponentEvent e) { update(); }
	public void componentShown(ComponentEvent e) { }
}
