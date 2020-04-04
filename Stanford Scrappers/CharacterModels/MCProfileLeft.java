package CharacterModels;
import java.awt.Color;

import acm.graphics.GArc;
import acm.graphics.GCompound;
import acm.graphics.GOval;
import acm.graphics.GPolygon;
import acm.graphics.GRect;

public class MCProfileLeft extends GCompound implements BodyConstants{
	
	public MCProfileLeft(double width, double height, Color pantsColor, Color shirtColor, Color shoeColor) {
		
		
		leftPantLeg = new GRect(FOOT_WIDTH - PANT_W, -PANT_L - FOOT_LENGTH, PANT_W, PANT_L);
		leftPantLeg.setFilled(true);
		leftPantLeg.setFillColor(pantsColor);
		add(leftPantLeg);
		
		body = new GRect(BODY_WIDTH/2-PANT_W, height-PANT_L-BODY_HEIGHT-FOOT_LENGTH, BODY_WIDTH/2, BODY_HEIGHT);
		body.setFilled(true);
		body.setFillColor(shirtColor);
		add(body);
		
		rightFoot = new GRect(0, height-FOOT_LENGTH, FOOT_WIDTH, FOOT_LENGTH);
		rightFoot.setFilled(true);
		rightFoot.setFillColor(shoeColor);
		add(rightFoot);
		
		Color skin = new Color(242, 218, 145);
		neck = new GRect(BODY_WIDTH/2-PANT_W, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH, NECK_WIDTH, NECK_LENGTH);
		neck.setFilled(true);
		neck.setFillColor(skin);
		add(neck);
		
		arm = new GRect(FOOT_LENGTH/2 + FOOT_WIDTH - PANT_W, -FOOT_LENGTH-PANT_L-BODY_HEIGHT+ARM_OFFSET, ARM_WIDTH, ARM_LENGTH);
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
		add(head, -JAW_LINE_W*2 + BODY_WIDTH/2-PANT_W, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH);
		
		eye = new GOval(BODY_WIDTH/2-PANT_W, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH-head.getHeight()/1.5, EYE_RADIUS, EYE_RADIUS);
		eye.setFilled(true);
		add(eye);
		mouth = new GArc(SMILE_W, SMILE_H, 0, -55);
		add(mouth, -NECK_LENGTH-JAW_LINE_W+BODY_WIDTH/2-PANT_W, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH-head.getHeight()/2.25);
	}
	
	private GRect leftPantLeg;
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
