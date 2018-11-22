package GUI;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

import javax.swing.JFrame;
import javax.swing.JPanel;

import Connection.ClientSocket;



abstract class Entity extends JPanel{

	
	protected int posX, posY;
	private boolean isAlive;
	public BufferedImage currentImage;
	protected String direction = " ";
	
	protected ClientSocket socket;
	public int[][] map;
	protected JFrame window;
	
	
	public void draw(Graphics g)
	{
		
	}
	
	
	
	
	
	
	public int getPosX() {
		return posX;
	}
	public void setPosX(int posX) {
		this.posX = posX;
	}
	public int getPosY() {
		return posY;
	}
	public void setPosY(int posY) {
		this.posY = posY;
	}
	public boolean isAlive() {
		return isAlive;
	}
	public void setAlive(boolean isAlive) {
		this.isAlive = isAlive;
	}






	public String getDirection() {
		return direction;
	}

	
	public void setDirection(String direction) {
		this.direction = direction;
	}
	
	
	
	
	
	
}
