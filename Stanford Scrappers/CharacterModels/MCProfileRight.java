package CharacterModels;
import java.awt.Color;

import acm.graphics.GArc;
import acm.graphics.GCompound;
import acm.graphics.GOval;
import acm.graphics.GPolygon;
import acm.graphics.GRect;

public class MCProfileRight extends GCompound{
	
	public MCProfileRight(double width, double height, Color pantsColor, Color shirtColor, Color shoeColor) {
		
		
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
		
		arm = new GRect(FOOT_LENGTH/2, -FOOT_LENGTH-PANT_L-BODY_HEIGHT+ARM_OFFSET, ARM_WIDTH, ARM_LENGTH);
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
		add(mouth, getWidth()-JAW_LINE_W*2, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH-head.getHeight()/2.25);
	}
	
	private static final double PANT_L = 40;
	private static final double PANT_W = 10;
	private static final double THIGH_GAP = 5;
	private static final double CROTCH_HEIGHT = PANT_L/4;
	private static final double BODY_HEIGHT = 40;
	private static final double BODY_WIDTH = PANT_W*2+THIGH_GAP;
	private static final double ARM_LENGTH = 35;
	private static final double ARM_WIDTH = 5;
	private static final double FOOT_LENGTH = 5;
	private static final double FOOT_WIDTH = 15;
	private static final double NECK_LENGTH = 5;
	private static final double NECK_WIDTH = BODY_WIDTH/2;
	private static final double CHIN = 21;
	private static final double JAW_LINE_H = 10;
	private static final double JAW_LINE_W = 3;
	private static final double STRAIGHT_OF_HEAD_L = 5;
	private static final double TOP_OF_HEAD = CHIN;
	private static final double SMILE_W = 10;
	private static final double SMILE_H = 6;
	private static final double EYE_RADIUS = 2;
	private static final double ARM_OFFSET = 5;
	
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
