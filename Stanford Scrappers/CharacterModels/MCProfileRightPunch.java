package CharacterModels;

import java.awt.Color;

import acm.graphics.GArc;
import acm.graphics.GCompound;
import acm.graphics.GOval;
import acm.graphics.GPolygon;
import acm.graphics.GRect;

public class MCProfileRightPunch extends GCompound implements BodyConstants{
	
	public MCProfileRightPunch(double width, double height, Color pantsColor, Color shirtColor, Color shoeColor) {
		
		
		rightPantLeg = new GRect(0, -PANT_L - FOOT_LENGTH, PANT_W, PANT_L);
		rightPantLeg.setFilled(true);
		rightPantLeg.setFillColor(pantsColor);
		add(rightPantLeg);
		
		body = new GRect(0, height-PANT_L-BODY_HEIGHT-FOOT_LENGTH, BODY_WIDTH/2, BODY_HEIGHT);
		body.setFilled(true);
		body.setFillColor(shirtColor);
		add(body);
		
		rightFoot = new GRect(0, height-FOOT_LENGTH, FOOT_WIDTH, FOOT_LENGTH);
		rightFoot.setFilled(true);
		rightFoot.setFillColor(shoeColor);
		add(rightFoot);
		
		Color skin = new Color(242, 218, 145);
		neck = new GRect(0, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH, NECK_WIDTH, NECK_LENGTH);
		neck.setFilled(true);
		neck.setFillColor(skin);
		add(neck);
		
		arm = new GRect(FOOT_LENGTH/2, -FOOT_LENGTH-PANT_L-BODY_HEIGHT+ARM_OFFSET, ARM_LENGTH, ARM_WIDTH);
		arm.setFilled(true);
		arm.setFillColor(shirtColor);
		add(arm);
		
		GPolygon head = new GPolygon();
		head.addVertex(CHIN, 0);
		head.addEdge(JAW_LINE_W, -JAW_LINE_H);
		head.addEdge(0, -STRAIGHT_OF_HEAD_L);
		head.addArc(TOP_OF_HEAD, TOP_OF_HEAD, 0, 180);
		head.addEdge(0, STRAIGHT_OF_HEAD_L);
		head.addEdge(JAW_LINE_W, JAW_LINE_H);
		
		head.setFilled(true);
		head.setFillColor(skin);
		add(head, -JAW_LINE_W*2, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH);
		
		eye = new GOval(FOOT_WIDTH-NECK_WIDTH/4-JAW_LINE_W*2+head.getWidth()/4+1, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH-head.getHeight()/1.5, EYE_RADIUS, EYE_RADIUS);
		eye.setFilled(true);
		add(eye);
		mouth = new GArc(SMILE_W, SMILE_H, -135, -45);
		add(mouth, CHIN-JAW_LINE_W*2, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH-head.getHeight()/2.25);
	}
	
	
	
	private GRect leftPantLeg;
	private GRect rightPantLeg;
	private GRect midSectionPants;
	private GRect body;
	private GOval eye;
	private GRect neck;
	private GRect arm;
	private GRect rightArm;
	private GRect leftFoot;
	private GRect rightFoot;
	private GOval eye2;
	private GArc mouth;
}
