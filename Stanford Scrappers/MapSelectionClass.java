/*
 * File: GraphicsClass.java
 * Name: Gilbert Rosal
 * Section Leader: Jabari Hastings
 * ------------------
 * This class creates and keeps track of the interface. It also returns the music, background, and map number (for stage
 * creation) for the user.
 *  
 * DISCLAIMER: I TAKE TO CREDIT FOR THE BACKGROUND ART FOR ANY OF THE STAGES OR MUSIC USED AT ANY POINT. ALL 
 * OF THAT MATERIAL WAS DOWNLOADED ONLINE.
 */

import java.applet.AudioClip;
import java.awt.GridLayout;

import javax.swing.JButton;

import acm.graphics.GCanvas;
import acm.graphics.GImage;
import acm.program.Program;
import acm.util.MediaTools;

public class MapSelectionClass extends Program{
	private JButton map1 = new JButton("Map 1: Nightinggale");
	private JButton map2 = new JButton("Map 2: Forbidden Desert");
	private JButton map3 = new JButton("Map 3: Howling Forest");
	private JButton map4 = new JButton("Map 4: The Pirate's Cove");
	private JButton map5 = new JButton("Map 5: Break of Light");
	private JButton map6 = new JButton("Map 6: Forsaken Plains");
	public static GCanvas map1Canvas = new GCanvas();
	public static GCanvas map2Canvas = new GCanvas();
	public static GCanvas map3Canvas = new GCanvas();
	public static GCanvas map4Canvas = new GCanvas();
	public static GCanvas map5Canvas = new GCanvas();
	public static GCanvas map6Canvas = new GCanvas();
	private static GraphicsClass container;
	private GImage selectedMap;
	
	public MapSelectionClass(GraphicsClass newContainer) {
		container = newContainer;
		container.setLayout(new GridLayout(2, 6));
	}
	
	public void addAllButtons() {
		container.add(map1);
		addImageToCanvas("Map1.jpg", map1Canvas);
		container.add(map1Canvas);
		
		container.add(map2);
		addImageToCanvas("Map2.jpg", map2Canvas);
		container.add(map2Canvas);
		
		container.add(map3);
		addImageToCanvas("Map3.jpg", map3Canvas);
		container.add(map3Canvas);
		
		container.add(map4);
		addImageToCanvas("Map4.jpg", map4Canvas);
		container.add(map4Canvas);
		
		container.add(map5);
		addImageToCanvas("Map5.jpg", map5Canvas);
		container.add(map5Canvas);
		
		container.add(map6);
		addImageToCanvas("Map6.jpg", map6Canvas);
		container.add(map6Canvas);
	}
	
	private void removeAllButtons() {
		container.remove(map1);
		container.remove(map1Canvas);
		container.remove(map2);
		container.remove(map2Canvas);
		container.remove(map3);
		container.remove(map3Canvas);
		container.remove(map4);
		container.remove(map4Canvas);
		container.remove(map5);
		container.remove(map5Canvas);
		container.remove(map6);
		container.remove(map6Canvas);
		container.setLayout(null);
	}

	public GImage getMapChoice(String buttonClicked) {
		int map = 0;
		AudioClip temp = MediaTools.loadAudioClip("music.au");
		if (buttonClicked.equals("Map 1: Nightinggale")) {
			selectedMap = new GImage("Map1.jpg");
			map = 1;
			temp = MediaTools.loadAudioClip("map1music.au");
		} else if (buttonClicked.equals("Map 2: Forbidden Desert")) {
			selectedMap = new GImage("Map2.jpg");
			map = 2;
			temp = MediaTools.loadAudioClip("map2music.au");
		} else if (buttonClicked.equals("Map 3: Howling Forest")) {
			selectedMap = new GImage("Map3.jpg");
			map = 3;
			temp = MediaTools.loadAudioClip("map3music.au");
		} else if (buttonClicked.equals("Map 4: The Pirate's Cove")) {
			selectedMap = new GImage("Map4.jpg");
			map = 4;
			temp = MediaTools.loadAudioClip("map4Music.wav"); 
		} else if (buttonClicked.equals("Map 5: Break of Light")) {
			selectedMap = new GImage("Map5.jpg");
			map = 5;
			temp = MediaTools.loadAudioClip("map5music.au");
		} else if (buttonClicked.equals("Map 6: Forsaken Plains")) {
			selectedMap = new GImage("Map6.jpg");
			map = 6;
		}
		container.setMapNumber(map);
		container.setGameMusic(temp);
		removeAllButtons();
		return selectedMap;
	}
	
	public static void addImageToCanvas(String image, GCanvas canvas) {
		canvas.removeAll();
		double iWidth = container.getWidth()/6;
		double iHeight = container.getHeight()/2;
		GImage temp = new GImage(image);
		temp.setSize(iWidth, iHeight);
		canvas.add(temp);
	}
}
