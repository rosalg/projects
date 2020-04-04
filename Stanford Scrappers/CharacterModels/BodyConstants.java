package CharacterModels;

import acm.graphics.GPolygon;

public interface BodyConstants {
	public static final double PANT_L = 40;
	public static final double PANT_W = 10;
	public static final double THIGH_GAP = 5;
	public static final double CROTCH_HEIGHT = PANT_L/4;
	public static final double BODY_HEIGHT = 40;
	public static final double BODY_WIDTH = PANT_W*2+THIGH_GAP;
	public static final double ARM_LENGTH = 35;
	public static final double ARM_WIDTH = 5;
	public static final double FOOT_LENGTH = 5;
	public static final double FOOT_WIDTH = 15;
	public static final double NECK_LENGTH = 5;
	public static final double NECK_WIDTH = BODY_WIDTH/2;
	public static final double CHIN = 21;
	public static final double JAW_LINE_H = 10;
	public static final double JAW_LINE_W = 3;
	public static final double STRAIGHT_OF_HEAD_L = 5;
	public static final double TOP_OF_HEAD = CHIN;
	public static final double SMILE_W = 10;
	public static final double SMILE_H = 6;
	public static final double EYE_RADIUS = 2;
	public static final double ARM_OFFSET = 5;
	public static final double HEAD_HEIGHT = STRAIGHT_OF_HEAD_L+JAW_LINE_H;
	public static final int STATIONARY = 0;
	public static final int RIGHT_WALK = 1;
	public static final int LEFT_WALK = 2;
	public static final int MAX_SPEED = 2;
	public static final double GRAVITY = 1.5;
	
	public static final int STATIONARY_MODEL = 0;
	public static final int STATIONARY_PUNCH_MODEL = 1;
	public static final int LEFT_PROFILE_MODEL = 2;
	public static final int LEFT_PROFILE_PUNCH_MODEL = 3;
	public static final int RIGHT_PROFILE_MODEL = 4;
	public static final int RIGHT_PROFILE_PUNCH_MODEL = 5;
	
	public static final int MAX_HEALTH = 10;
	
	GPolygon HEAD = new GPolygon();
}
