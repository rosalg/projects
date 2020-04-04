package CharacterModels;
import java.awt.Color;

import acm.graphics.GCompound;
import acm.graphics.GLabel;

public class PlayerInstructions extends GCompound{
	
	GLabel playerDeclaration;
	GLabel moveUpInstruction;
	GLabel moveLeftInstruction;
	GLabel moveDownInstruction;
	GLabel moveRightInstruction;
	GLabel punchLeftInstruction;
	GLabel punchRightInstruction;
	GLabel shootProjectileInstruction;
	GLabel shootProjectileInstruction2;
	GLabel shootProjectileInstruction3;
	
	public PlayerInstructions(int playerNumber, String moveUpChar, String moveLeftChar, 
			String moveDownChar, String moveRightChar, String punchLeftChar, String punchRightChar, String shootProj, double sf) {
		playerDeclaration = new GLabel ("Player " + playerNumber + " controls");
		moveUpInstruction = new GLabel ("Press " + moveUpChar.toUpperCase() + " to jump.");
		moveLeftInstruction = new GLabel ("Press " + moveLeftChar.toUpperCase() + " to move left.");
		moveDownInstruction = new GLabel ("Press " + moveDownChar.toUpperCase() + " to fall through platforms.");
		moveRightInstruction = new GLabel ("Press " + moveRightChar.toUpperCase() + " to move right.");
		punchLeftInstruction = new GLabel ("Press " + punchLeftChar.toUpperCase() + " to punch left.");
		punchRightInstruction = new GLabel ("Press " + punchRightChar.toUpperCase() + " to punch right.");
		shootProjectileInstruction = new GLabel ("Press " + shootProj.toUpperCase() + " to shoot a projectile when walking left or right.");
		shootProjectileInstruction2 = new GLabel ("You only have 5 shots.");
		shootProjectileInstruction3 = new GLabel("You can only have 1 shot on screen at a time.");
		
		playerDeclaration.setFont("SansSerif-"+Math.round(sf*30));
		moveUpInstruction.setFont("SansSerif-"+Math.round(sf*15));
		moveLeftInstruction.setFont("SansSerif-"+Math.round(sf*15));
		moveDownInstruction.setFont("SansSerif-"+Math.round(sf*15));
		moveRightInstruction.setFont("SansSerif-"+Math.round(sf*15));
		punchLeftInstruction.setFont("SansSerif-"+Math.round(sf*15));
		punchRightInstruction.setFont("SansSerif-"+Math.round(sf*15));
		shootProjectileInstruction.setFont("SansSerif-"+Math.round(sf*15));
		shootProjectileInstruction2.setFont("SansSerif-"+Math.round(sf*15));
		shootProjectileInstruction3.setFont("SansSerif-"+Math.round(sf*15));
		
		playerDeclaration.setColor(Color.white);
		moveUpInstruction.setColor(Color.white);
		moveLeftInstruction.setColor(Color.white);
		moveDownInstruction.setColor(Color.white);
		moveRightInstruction.setColor(Color.white);
		punchLeftInstruction.setColor(Color.white);
		punchRightInstruction.setColor(Color.white);
		shootProjectileInstruction.setColor(Color.white);
		shootProjectileInstruction2.setColor(Color.white);
		shootProjectileInstruction3.setColor(Color.white);
		
		double y = playerDeclaration.getAscent();
		add(playerDeclaration, playerDeclaration.getWidth()/4, y);
		y += moveUpInstruction.getAscent();
		add(moveUpInstruction, 0, y);
		y += moveLeftInstruction.getAscent();
		add(moveLeftInstruction, 0, y);
		y += moveDownInstruction.getAscent();
		add(moveDownInstruction, 0, y);
		y += moveRightInstruction.getAscent();
		add(moveRightInstruction, 0, y);
		y += punchLeftInstruction.getAscent();
		add(punchLeftInstruction, 0, y);
		y += punchRightInstruction.getAscent();
		add(punchRightInstruction, 0, y);
		y += shootProjectileInstruction.getAscent();
		add(shootProjectileInstruction, 0, y);
		y += shootProjectileInstruction2.getAscent();
		add(shootProjectileInstruction2, 0 , y);
		y += shootProjectileInstruction.getAscent();
		add(shootProjectileInstruction3, 0, y);
	}
	
	public void updateFontSize(double sf) {
		playerDeclaration.setFont("SansSerif-"+Math.round(sf*30));
		moveUpInstruction.setFont("SansSerif-"+Math.round(sf*15));
		moveLeftInstruction.setFont("SansSerif-"+Math.round(sf*15));
		moveDownInstruction.setFont("SansSerif-"+Math.round(sf*15));
		moveRightInstruction.setFont("SansSerif-"+Math.round(sf*15));
		punchLeftInstruction.setFont("SansSerif-"+Math.round(sf*15));
		punchRightInstruction.setFont("SansSerif-"+Math.round(sf*15));
		shootProjectileInstruction.setFont("SansSerif-"+Math.round(sf*15));
		shootProjectileInstruction2.setFont("SansSerif-"+Math.round(sf*15));
		shootProjectileInstruction3.setFont("SansSerif-"+Math.round(sf*15));
		
		double y = playerDeclaration.getAscent();
		add(playerDeclaration, getWidth()/4, y);
		y += moveUpInstruction.getAscent();
		add(moveUpInstruction, 0, y);
		y += moveLeftInstruction.getAscent();
		add(moveLeftInstruction, 0, y);
		y += moveDownInstruction.getAscent();
		add(moveDownInstruction, 0, y);
		y += moveRightInstruction.getAscent();
		add(moveRightInstruction, 0, y);
		y += punchLeftInstruction.getAscent();
		add(punchLeftInstruction, 0, y);
		y += punchRightInstruction.getAscent();
		add(punchRightInstruction, 0, y);
		y += shootProjectileInstruction.getAscent();
		add(shootProjectileInstruction, 0, y);
		y += shootProjectileInstruction2.getAscent();
		add(shootProjectileInstruction2, 0 , y);
		y += shootProjectileInstruction.getAscent();
		add(shootProjectileInstruction3, 0, y);
	}
}
