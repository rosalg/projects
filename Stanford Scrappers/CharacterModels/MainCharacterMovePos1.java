package CharacterModels;
import java.awt.Color;

import acm.graphics.GArc;
import acm.graphics.GCompound;
import acm.graphics.GOval;
import acm.graphics.GPolygon;
import acm.graphics.GRect;

public class MainCharacterMovePos1 extends GCompound implements BodyConstants{
	
	public MainCharacterMovePos1(double width, double height, Color pantsColor, Color shirtColor, Color shoeColor) {
		
		leftPantLeg = new GRect(ARM_WIDTH, height-PANT_L-FOOT_LENGTH, PANT_W, PANT_L);
		leftPantLeg.setFilled(true);
		leftPantLeg.setFillColor(pantsColor);
		add(leftPantLeg);
		rightPantLeg = new GRect(PANT_W+THIGH_GAP+ARM_WIDTH, height-PANT_L-FOOT_LENGTH, PANT_W, PANT_L);
		rightPantLeg.setFilled(true);
		rightPantLeg.setFillColor(pantsColor);
		add(rightPantLeg);
		midSectionPants = new GRect(PANT_W+ARM_WIDTH, height-PANT_L-FOOT_LENGTH, THIGH_GAP, CROTCH_HEIGHT);
		midSectionPants.setFilled(true);
		midSectionPants.setFillColor(pantsColor);
		add(midSectionPants);
		
		body = new GRect(ARM_WIDTH, height-PANT_L-BODY_HEIGHT-FOOT_LENGTH, BODY_WIDTH, BODY_HEIGHT);
		body.setFilled(true);
		body.setFillColor(shirtColor);
		add(body);
		
		leftArm = new GRect(0, height-PANT_L-BODY_HEIGHT-FOOT_LENGTH, ARM_WIDTH, ARM_LENGTH);
		leftArm.setFilled(true);
		leftArm.setFillColor(shirtColor);
		add(leftArm);
		rightArm = new GRect(PANT_W*2+ARM_WIDTH+THIGH_GAP, height-PANT_L-BODY_HEIGHT-FOOT_LENGTH, ARM_LENGTH, ARM_WIDTH);
		rightArm.setFilled(true);
		rightArm.setFillColor(shirtColor);
		add(rightArm);
		
		leftFoot = new GRect(0, height-FOOT_LENGTH, FOOT_WIDTH, FOOT_LENGTH);
		leftFoot.setFilled(true);
		leftFoot.setFillColor(shoeColor);
		add(leftFoot);
		rightFoot = new GRect(FOOT_WIDTH+THIGH_GAP, height-FOOT_LENGTH, FOOT_WIDTH, FOOT_LENGTH);
		rightFoot.setFilled(true);
		rightFoot.setFillColor(shoeColor);
		add(rightFoot);
		
		Color skin = new Color(242, 218, 145);
		neck = new GRect(FOOT_WIDTH-NECK_WIDTH/4, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH, NECK_WIDTH, NECK_LENGTH);
		neck.setFilled(true);
		neck.setFillColor(skin);
		add(neck);
		
		head = new GPolygon();
		head.addVertex(CHIN, 0);
		head.addEdge(JAW_LINE_W, -JAW_LINE_H);
		head.addEdge(0, -STRAIGHT_OF_HEAD_L);
		head.addArc(TOP_OF_HEAD, TOP_OF_HEAD, 0, 180);
		head.addEdge(0, STRAIGHT_OF_HEAD_L);
		head.addEdge(JAW_LINE_W, JAW_LINE_H);
		
		head.setFilled(true);
		head.setFillColor(skin);
		add(head, FOOT_WIDTH-NECK_WIDTH/4-JAW_LINE_W*2, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH);
		
		eye = new GOval(FOOT_WIDTH-NECK_WIDTH/4-JAW_LINE_W*2+head.getWidth()/4+1, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH-head.getHeight()/1.5, EYE_RADIUS, EYE_RADIUS);
		eye.setFilled(true);
		eye2 = new GOval(FOOT_WIDTH-NECK_WIDTH/4-JAW_LINE_W*2+head.getWidth()*3/4+1, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH-head.getHeight()/1.5, EYE_RADIUS, EYE_RADIUS); 
		eye2.setFilled(true);
		add(eye);
		add(eye2);
		mouth = new GArc(SMILE_W, SMILE_H, 0, -180);
		add(mouth,FOOT_WIDTH-NECK_WIDTH/4-JAW_LINE_W*2+head.getWidth()/2-2, height-PANT_L-FOOT_LENGTH-BODY_HEIGHT-NECK_LENGTH-head.getHeight()/2.25);
	}
	
	private GRect leftPantLeg;
	private GRect rightPantLeg;
	private GRect midSectionPants;
	private GRect body;
	private GOval eye;
	private GRect neck;
	private GRect leftArm;
	private GRect rightArm;
	private GRect leftFoot;
	private GRect rightFoot;
	private GOval eye2;
	private GArc mouth;
	public GPolygon head;
}
