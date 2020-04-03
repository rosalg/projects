package maps;
import acm.graphics.GCanvas;
import acm.graphics.GImage;

public class MapOne extends GCanvas implements MapConstants{
	GImage map1;
	
	public MapOne() {
	}
	
	public void addMap1() {
		map1 = new GImage("Map1.jpg");
		add(map1);
	}
	
	public void resizeMap1(double x, double y) {
		map1.setSize(x, y);
	}
	
	public GImage getMap() {
		return map1;
	}
}
