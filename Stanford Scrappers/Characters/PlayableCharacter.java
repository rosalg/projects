package Characters;


import java.applet.AudioClip;
import java.awt.Color;
import java.awt.event.KeyEvent;

import CharacterModels.*;
import acm.graphics.*;
import acm.program.GraphicsProgram;
import acm.util.MediaTools;

public class PlayableCharacter extends GraphicsProgram implements BodyConstants{

	public PlayableCharacter (Color pantsColor, Color shirtColor, Color shoeColor, GCanvas canvas, double startingX,
			double startingY, String newPlayerName, GImage map, double initialHorizontalScaleFactor, double initialVerticalScaleFactor) {
		stationaryPlayer = new MainCharacter(0, 0, pantsColor, shirtColor, shoeColor);
		stationaryPunch = new MainCharacterMovePos1(0, 0, pantsColor, shirtColor, shoeColor);
		profileRight = new MCProfileRight(0, 0, pantsColor, shirtColor, shoeColor);
		profileLeft = new MCProfileLeft(0, 0, pantsColor, shirtColor, shoeColor);
		profileRightPunch = new MCProfileRightPunch(0, 0, pantsColor, shirtColor, shoeColor);
		profileLeftPunch = new MCProfileLeftPunch(0, 0, pantsColor, shirtColor, shoeColor);
		activeCanvas = canvas;
		activeCanvas.add(stationaryPlayer, startingX, startingY);
		playerName = new GLabel(newPlayerName);
		selectedMap = map;
		horizontalScaleFactor = initialHorizontalScaleFactor;
		verticalScaleFactor = initialVerticalScaleFactor;
		projectile = new RangedAttackProjectile(shirtColor);
	}

	
	
	private GCompound stationaryPlayer;
	private GCompound profileRight;
	private GCompound stationaryPunch;
	private GCompound profileLeft;
	private GCompound profileRightPunch;
	private GCompound profileLeftPunch;
	private GRect healthBar = new GRect(0, 0);
	private GImage selectedMap;
	
	private boolean speedUpRightCheck;
	private boolean speedUpLeftCheck;
	private boolean slowDownRightCheck;
	private boolean slowDownLeftCheck;
	private boolean jumpCheck;
	private boolean fallThroughCheck;
	private boolean punchRightCheck;
	private boolean punchLeftCheck;
	private boolean rangedAttackCheck;
	
	private double health = MAX_HEALTH;
	private double vx;
	private double vy;
	private int positionTracker;
	private double pauseTime = 5;
	private double horizontalScaleFactor;
	private double verticalScaleFactor;
	private GCanvas activeCanvas;
	private GLabel playerName;
	private double knockback = 40;
	private double rangedAttackCounter = 5;
	private RangedAttackProjectile projectile;
	
	AudioClip punch = MediaTools.loadAudioClip("punch.au");
	AudioClip missedPunch = MediaTools.loadAudioClip("missedPunch.au");
	AudioClip jump = MediaTools.loadAudioClip("jump.wav");
	AudioClip hit = MediaTools.loadAudioClip("hit.wav");
	
 	public GCompound getCharacterModel(int modelNumber) {
		if (modelNumber == STATIONARY_MODEL) {
			return stationaryPlayer;
		} else if (modelNumber == STATIONARY_PUNCH_MODEL) {
			return stationaryPunch; 
		} else if (modelNumber == LEFT_PROFILE_MODEL) {
			return profileLeft;
		} else if (modelNumber == LEFT_PROFILE_PUNCH_MODEL) {
			return profileLeftPunch;
		} else if (modelNumber == RIGHT_PROFILE_MODEL) {
			return profileRight;
		} else if (modelNumber == RIGHT_PROFILE_PUNCH_MODEL) {
			return profileRightPunch;
		}
		return profileRightPunch;
		
	}
	
	public GLabel getPlayerLabel(String size) {
		playerName.setFont("SansSerif-Bold-"+size);
		playerName.setColor(Color.white);
		return playerName;
	}
	
	public void setPlayerLabel(GLabel name) {
		playerName = name;
	}
	
	public GRect updateHealthBar(double windowWidth, double windowHeight) {
		double healthBarWidth = 0;
		for (double i = MAX_HEALTH; i >= 0; i--) {
			if (i == health) {
				healthBarWidth = windowWidth/2.25*(i/MAX_HEALTH);
			}
		}
		healthBar.setFilled(true);
		healthBar.setFillColor(Color.yellow);
		healthBar.setSize(healthBarWidth, windowHeight/10);
		return healthBar;
	}

	public void setHealth(double newHealth) {
		health = newHealth;
	}

	public double getHealth() {
		return health;
	}
	
	public double getvy() {
		return vy;
	}
	
	public void setRangedAttackCheck(boolean check) {
		rangedAttackCheck = check;
	}
	
	public void setSpeedUpRightCheck(boolean check) {
		speedUpRightCheck = check;
	}
	
	public void setSpeedUpLeftCheck(boolean check) {
		speedUpLeftCheck = check;
	}
	
	public void setSlowDownRightCheck(boolean check) {
		slowDownRightCheck = check;
	}
	
	public void setSlowDownLeftCheck(boolean check) {
		slowDownLeftCheck = check;
	}
	
	public void setJumpCheck(boolean check) {
		jumpCheck = check;
	}
	
	public void setFallThroughCheck(boolean check) {
		fallThroughCheck = check;
	}
	
	public boolean getRangedAttackCheck() {
		return rangedAttackCheck;
	}
	
	public boolean getSpeedUpRightCheck() {
		return speedUpRightCheck;
	}
	
	public boolean getSpeedUpLeftCheck() {
		return speedUpLeftCheck;
	}
	
	public boolean getSlowDownRightCheck() {
		return slowDownRightCheck;
	}
	
	public boolean getSlowDownLeftCheck() {
		return slowDownLeftCheck;
	}
	
	public boolean getJumpCheck() {
		return jumpCheck;
	}
	
	public boolean getFallThroughCheck() {
		return fallThroughCheck;
	}

	public boolean getPunchRightCheck() {
		return punchRightCheck;
	}
	
	public void setPunchRightCheck(boolean check) {
		punchRightCheck = check;
	}
	
	public boolean getPunchLeftCheck() {
		return punchLeftCheck;
	}
	
	public RangedAttackProjectile getProjectile() {
		return projectile;
	}
	
	public void setPunchLeftCheck(boolean check) {
		punchLeftCheck = check;
	}
	
	public void setHorizontalScaleFactor(double newScaleFactor) {
		horizontalScaleFactor = newScaleFactor;
	}
	
	public void setVerticalScaleFactor(double newScaleFactor) {
		verticalScaleFactor = newScaleFactor;
	}
	
	public void checkPlayerActions(PlayableCharacter opponent, double height, double width) {
		fallDown(height, width, opponent);
		edgeCheck();
		if (slowDownLeftCheck && positionTracker != RIGHT_WALK) {
			slowDownLeft();
		}
		if (slowDownRightCheck && positionTracker != LEFT_WALK) {
			slowDownRight();
		}
		if (speedUpRightCheck && vx != MAX_SPEED && positionTracker == STATIONARY) {
			speedUpRight();
		}
		if (speedUpLeftCheck && vx != -MAX_SPEED && positionTracker == STATIONARY) {
			speedUpLeft();
		}
		if (fallThroughCheck) {
			fallThrough();
			fallThroughCheck = false;
		}
		if (jumpCheck) {
			jump();
		}
		if (punchRightCheck) {
			rightPunch(opponent);
		}
		if (punchLeftCheck) {
			leftPunch(opponent);
		}
		if (health <= 0) {
			activeCanvas.remove(stationaryPlayer);
			activeCanvas.remove(profileLeft);
			activeCanvas.remove(profileRight);
		}
		if (rangedAttackCheck && rangedAttackCounter >= 0) {
			rangedAttack(opponent);
		}
	}
 	
	private void jump() {
		jump.play();
		vy = -7.5;
		for (int i = 0; i < 20*verticalScaleFactor; i++) {
			move();
		 	pause(pauseTime/4/verticalScaleFactor);
		 	if (stationaryPlayer.getY()-stationaryPlayer.getHeight() < healthBar.getHeight()+playerName.getAscent()) break;
		}
		jumpCheck = false;
	}
	
	private void speedUpRight() {
		activeCanvas.add(profileRight, stationaryPlayer.getX(), stationaryPlayer.getY());
		activeCanvas.remove(stationaryPlayer);
		for (double i = 0; i <= MAX_SPEED; i += 0.5) {
			vx = i;
			move();
			pause(pauseTime/2);
		}
		positionTracker = RIGHT_WALK;
	}

	private void speedUpLeft() {
		if (vy == 0) {
		}
		activeCanvas.remove(stationaryPlayer);
		activeCanvas.add(profileLeft, stationaryPlayer.getX(), stationaryPlayer.getY());
		for (double i = 0; i >= -MAX_SPEED; i -= 0.5) {
			vx = i;
			move();
			pause(pauseTime/2);
		}
		positionTracker = LEFT_WALK;
		speedUpLeftCheck = false;
	}
	
	private void slowDownLeft() {
		for (double i = -MAX_SPEED; i <= 0; i += 0.5) {
			vx = i;
			move();
			pause(pauseTime/2);
		}
		activeCanvas.add(stationaryPlayer);
		activeCanvas.remove(profileLeft);
		positionTracker = STATIONARY;
		slowDownLeftCheck = false;
		vx = 0;
	}
	
	private void slowDownRight() {
		for (double i = MAX_SPEED; i >= 0; i -= 0.5) {
			vx = i;
			move();
			pause(pauseTime/2);
		}
		activeCanvas.add(stationaryPlayer);
		activeCanvas.remove(profileRight);
		slowDownRightCheck = false;
		positionTracker = STATIONARY;
		vx = 0;
	}
	
	private void fallThrough() {
		if ((bottomLeftCollider() != selectedMap || bottomRightCollider() != selectedMap) && (bottomLeftCollider() != null || bottomRightCollider() != null)) {
			vy = GRAVITY;
			while ((bottomLeftCollider() != selectedMap || bottomRightCollider() != selectedMap) && bottomLeftCollider() != null && bottomRightCollider() != null) {
				move();
			}
		}
	}
	
	private void fallDown(double height, double width, PlayableCharacter opponent) {
		if ((bottomLeftCollider() == selectedMap || bottomLeftCollider() == null || bottomLeftCollider() == opponent.getCharacterModel(STATIONARY_MODEL)) && (bottomRightCollider() == selectedMap || bottomRightCollider() == null || bottomRightCollider() == opponent.getCharacterModel(STATIONARY_MODEL)) && stationaryPlayer.getY() < height) {
			vy = GRAVITY*verticalScaleFactor;
		} else {
			vy = 0;
		}
		if (stationaryPlayer.getY() > height) {
			setLocation(stationaryPlayer.getX(), height);
			vy = 0;
		} 
	}
	
	private void rangedAttack(PlayableCharacter opponent) {
		if (projectile.getCheckBallOut() == 0 && rangedAttackCounter > 0) {
			if (positionTracker == RIGHT_WALK) {
				projectile.addProjectile(activeCanvas, stationaryPlayer.getX()+profileRightPunch.getWidth(), stationaryPlayer.getY() + (-FOOT_LENGTH-PANT_L-BODY_HEIGHT+5)*verticalScaleFactor);
				projectile.setvx(2);
				rangedAttackCounter--;
				projectile.setCheckBallOut(1);
			} else if (positionTracker == LEFT_WALK) {
				projectile.addProjectile(activeCanvas, stationaryPlayer.getX()+(-ARM_LENGTH+7)*horizontalScaleFactor, stationaryPlayer.getY() + (-PANT_L-BODY_HEIGHT)*verticalScaleFactor);
				projectile.setvx(-2);
				rangedAttackCounter--;
				projectile.setCheckBallOut(1);
			}
		}
		rangedAttackCheck = false;
	}
	
	private void rightPunch(PlayableCharacter opponent) {
		if (checkRPForOpponent(opponent)) {
			hit.play();
			punch.play();
			opponent.setHealth(opponent.getHealth()-1);
			if (opponent.getHealth() == 0) {
				activeCanvas.remove(rightPunchCollider());
			}
			opponent.getCharacterModel(STATIONARY_MODEL).move(knockback*horizontalScaleFactor, opponent.getvy());
			opponent.getCharacterModel(LEFT_PROFILE_MODEL).move(knockback*horizontalScaleFactor, opponent.getvy());
			opponent.getCharacterModel(RIGHT_PROFILE_MODEL).move(knockback*horizontalScaleFactor, opponent.getvy());
		} else {
			missedPunch.play();
		}
		checkModelRemove();
		activeCanvas.add(profileRightPunch, stationaryPlayer.getX(), stationaryPlayer.getY());
		pause(40);
		checkModelAdd();
		activeCanvas.remove(profileRightPunch);
		punchRightCheck = false;
	}
	
	private void leftPunch(PlayableCharacter opponent) {
		if (checkLPForOpponent(opponent)) {
			punch.play();
			hit.play();
			opponent.setHealth(opponent.getHealth()-1);
			if (opponent.getHealth() == 0) {
				activeCanvas.remove(leftPunchCollider());
			}
			opponent.getCharacterModel(STATIONARY_MODEL).move(-knockback*horizontalScaleFactor, opponent.getvy());
			opponent.getCharacterModel(LEFT_PROFILE_MODEL).move(-knockback*horizontalScaleFactor, opponent.getvy());
			opponent.getCharacterModel(RIGHT_PROFILE_MODEL).move(-knockback*horizontalScaleFactor, opponent.getvy());
		} else {
			missedPunch.play();
		}
		checkModelRemove();
		activeCanvas.add(profileLeftPunch, stationaryPlayer.getX(), stationaryPlayer.getY());
		pause(40);
		checkModelAdd();
		activeCanvas.remove(profileLeftPunch);
		punchLeftCheck = false;
	}
	
	public GObject bottomLeftCollider() {
		return activeCanvas.getElementAt(stationaryPlayer.getX(), stationaryPlayer.getY()+1);
	}
	
	private GObject bottomRightCollider() {
		return activeCanvas.getElementAt(stationaryPlayer.getX()+stationaryPlayer.getWidth(), stationaryPlayer.getY()+1);
	}
	
 	private GObject rightPunchCollider() {
		return activeCanvas.getElementAt(stationaryPlayer.getX()+profileRightPunch.getWidth(), stationaryPlayer.getY() + (-FOOT_LENGTH-PANT_L-BODY_HEIGHT+5)*verticalScaleFactor);
	}
	
	private GObject leftPunchCollider() {
		return activeCanvas.getElementAt(stationaryPlayer.getX()+(-ARM_LENGTH+7)*horizontalScaleFactor, stationaryPlayer.getY() + (-PANT_L-BODY_HEIGHT)*verticalScaleFactor);
	}
	
	private void edgeCheck() {
		if (stationaryPlayer.getX() < 0) {
			setLocation(0, stationaryPlayer.getY());
		}
		if (stationaryPlayer.getX()+profileLeft.getWidth() > activeCanvas.getWidth()) {
			setLocation(activeCanvas.getWidth()-profileLeft.getWidth(), stationaryPlayer.getY());
		}
		if (stationaryPlayer.getY()-stationaryPlayer.getHeight() < healthBar.getHeight()+playerName.getAscent()) {
			setLocation(stationaryPlayer.getX(), healthBar.getHeight()+playerName.getAscent()+stationaryPlayer.getHeight());
		}
	}
	
	public void setLocation(double x, double y) {
		stationaryPlayer.setLocation(x, y);
		profileLeft.setLocation(x, y);
		profileRight.setLocation(x, y);
	}
	
	public void move() {
		stationaryPlayer.move(vx, vy);
		profileRight.move(vx, vy);
		profileLeft.move(vx, vy);
	}
	
	private void checkModelAdd() {
		if (positionTracker == STATIONARY) {
			activeCanvas.add(stationaryPlayer);
		} else if (positionTracker == RIGHT_WALK) {
			activeCanvas.add(profileRight);
		} else if (positionTracker == LEFT_WALK) {
			activeCanvas.add(profileLeft);
		}
	}
	
	private boolean checkRPForOpponent(PlayableCharacter opponent) {
		if(rightPunchCollider() == opponent.getCharacterModel(STATIONARY_MODEL)) return true;
		if(rightPunchCollider() == opponent.getCharacterModel(RIGHT_PROFILE_MODEL)) return true;
		if(rightPunchCollider() == opponent.getCharacterModel(LEFT_PROFILE_MODEL)) return true;
		return false;
	}
	
	private boolean checkLPForOpponent(PlayableCharacter opponent) {
		if(leftPunchCollider() == opponent.getCharacterModel(STATIONARY_MODEL)) return true;
		if(leftPunchCollider() == opponent.getCharacterModel(RIGHT_PROFILE_MODEL)) return true;
		if(leftPunchCollider() == opponent.getCharacterModel(LEFT_PROFILE_MODEL)) return true;
		return false;
	}
	
	public void checkModelRemove() {
		if (positionTracker == STATIONARY) {
			activeCanvas.remove(stationaryPlayer);
		} else if (positionTracker == RIGHT_WALK) {
			activeCanvas.remove(profileRight);
		} else if (positionTracker == LEFT_WALK) {
			activeCanvas.remove(profileLeft);
		}
	}

} 