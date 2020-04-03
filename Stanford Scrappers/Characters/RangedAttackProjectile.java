package Characters;
/*
 * File: GraphicsClass.java
 * Name: Gilbert Rosal
 * Section Leader: Jabari Hastings
 * ------------------
 * This class keeps track of any projectiles created by the players
 *  
 * DISCLAIMER: I TAKE TO CREDIT FOR THE BACKGROUND ART FOR ANY OF THE STAGES OR MUSIC USED AT ANY POINT. ALL 
 * OF THAT MATERIAL WAS DOWNLOADED ONLINE.
 */

import java.applet.AudioClip;
import java.awt.Color;

import acm.graphics.GCanvas;
import acm.graphics.GImage;
import acm.graphics.GOval;
import acm.program.GraphicsProgram;
import acm.util.MediaTools;

public class RangedAttackProjectile extends GraphicsProgram {
	
	private double vx;
	private double vy;
	private GOval projectile;
	private double r = 5;
	private int checkBallOut;
	AudioClip hit = MediaTools.loadAudioClip("hit.wav");
	
	public RangedAttackProjectile(Color color) {
		projectile = new GOval(r*2, r*2);
		projectile.setFilled(true);
		projectile.setFillColor(color);
		projectile.setColor(Color.BLACK);
		checkBallOut = 0;
	}
	
	public void addProjectile(GCanvas container, double x, double y) {
		container.add(projectile, x, y);
	}
	
	public void moveProjectile() {
		projectile.move(vx, vy);
	}
	
	public void setvx(double newvx) {
		vx = newvx;
	}
	
	public void setvy(double newvy) {
		vy = newvy;
	}
	
	public void checkProjectileCollision(GCanvas container, GImage currentBackground, PlayableCharacter opponent) {
		double topLeftProjX = projectile.getX();
		double topLeftProjY = projectile.getY();
		if (container.getElementAt(topLeftProjX, topLeftProjY) != null && container.getElementAt(topLeftProjX, topLeftProjY) != currentBackground) {
			checkHit(0, 0, container, opponent);
		} else if (container.getElementAt(topLeftProjX+2*r, topLeftProjY) != null && container.getElementAt(topLeftProjX+2*r, topLeftProjY) != currentBackground) {
			checkHit(2*r, 0, container, opponent);
		} else if (container.getElementAt(topLeftProjX, topLeftProjY+2*r) != null && container.getElementAt(topLeftProjX, topLeftProjY+2*r) != currentBackground) {
			checkHit(0, 2*r, container, opponent);
		} else if (container.getElementAt(topLeftProjX+2*r, topLeftProjY+2*r) != null && container.getElementAt(topLeftProjX+2*r, topLeftProjY+2*r) != currentBackground) {
			checkHit(2*r, 2*r, container, opponent);
		} else if (projectile.getX() > container.getWidth() || projectile.getX() < 0) {
			container.remove(projectile);
			checkBallOut = 0;
		}
	}
	
	public int getCheckBallOut() {
		return checkBallOut;
	}
	
	public void setCheckBallOut(int ballStatus) {
		checkBallOut = ballStatus;
	}
	
	public void setProjectileRadius(double sf) {
		System.out.println(2*r);
		projectile.setSize(2*r, 2*r);
	}
	
	private void checkHit(double x, double y, GCanvas container, PlayableCharacter opponent) {
		double topLeftProjX = projectile.getX();
		double topLeftProjY = projectile.getY();
		for (int i = 0; i <= 4; i += 2) {
			if (container.getElementAt(topLeftProjX+x, topLeftProjY+y) == opponent.getCharacterModel(i)) {
				hit.play();
				opponent.setHealth(opponent.getHealth()-1);
				if (opponent.getHealth() == 0) {
					container.remove(container.getElementAt(topLeftProjX+x, topLeftProjY+y));
				}
			}
		}
		vx = 0;
		projectile.setLocation(0, 0);
		container.remove(projectile);
		checkBallOut = 0;
	}
}
