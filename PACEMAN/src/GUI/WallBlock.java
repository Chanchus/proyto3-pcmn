package GUI;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;



public class WallBlock extends Entity{
	
	
	
	
	public WallBlock(int x, int y) throws IOException {
		
		currentImage = ImageIO.read(getClass().getResourceAsStream("/block.png"));
		posX = x;
		posY = y;
		
	}
	
	
	public void draw(Graphics g)
	{
		
		g.drawImage(currentImage, posX*30, posY*30, 30, 30, null);
		
		
	}
	
	

}
