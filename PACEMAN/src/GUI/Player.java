package GUI;


import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

import Connection.ClientSocket;

public class Player extends Entity implements Runnable{

	
	public BufferedImage imageRight;
	public BufferedImage imageLeft;
	public BufferedImage imageUp;
	public BufferedImage imageDown;
	
	
	
	
	
	public Player(int x, int y, ClientSocket psocket, int[][] pmap, JFrame pwindow) throws IOException {
		
		imageRight = ImageIO.read(getClass().getResourceAsStream("/pacmanright.png"));
		imageLeft = ImageIO.read(getClass().getResourceAsStream("/pacmanleft.png"));
		imageUp = ImageIO.read(getClass().getResourceAsStream("/pacmanup.png"));
		imageDown = ImageIO.read(getClass().getResourceAsStream("/pacmandown.png"));
		
		currentImage = imageRight;
		posX = x;
		posY = y;
		
		socket = psocket;
		map = pmap;
		window = pwindow;
		
	}
	
	
	public void draw(Graphics g)
	{
		
		g.drawImage(currentImage, posX*30, posY*30, 30, 30, null);
		
		
	}


	@Override
	public void run() {
		
		while(true) {
			
			try {
				
				move();
				System.out.println("me muevo soy el jugador");
				Thread.sleep(500);
				
			} catch (InterruptedException e) {
				
				e.printStackTrace();
			}
			
		}
		
	}
	
	
	public void moveRight() {
		
		direction = "right";
		currentImage = imageRight;
		
	}
	
	public void moveLeft() {
		
		direction = "left";
		currentImage = imageLeft;
		
	}
	
	
	public void moveUp() {
		
		direction = "up";
		currentImage = imageUp;
		
	}
	
	
	public void moveDown() {
		
		direction = "down";
		currentImage = imageDown;
		
	}
	
	
	
	public void move() {
		
		
		if (direction.equals("right"))
		{
			String movement = socket.sendMessage("player move " + Integer.toString(posX) + " " + Integer.toString(posY));
			
			
			System.out.println("movement: " + movement);
			
			String[] parts = movement.split(" ");
			
			map[posY][posX] = 0;
			
			map[Integer.parseInt(parts[2])][Integer.parseInt(parts[3])] = 3;
			
			posX = Integer.parseInt(parts[2]);
			posY = Integer.parseInt(parts[3]);
			
			window.repaint();
			window.invalidate();
			
			//Thread.sleep(1000);
			
		}
		if (direction.equals("left"))
		{
			String movement = socket.sendMessage("player move " + Integer.toString(posX) + " " + Integer.toString(posY));
			
			
			System.out.println("movement: " + movement);
			
			String[] parts = movement.split(" ");
			
			map[posY][posX] = 0;
			
			map[Integer.parseInt(parts[2])][Integer.parseInt(parts[3])] = 3;
			
			posX = Integer.parseInt(parts[2]);
			posY = Integer.parseInt(parts[3]);
			
			window.repaint();
			window.invalidate();
		}
		if (direction.equals("up"))
		{
			String movement = socket.sendMessage("player move " + Integer.toString(posX) + " " + Integer.toString(posY));
			
			
			System.out.println("movement: " + movement);
			
			String[] parts = movement.split(" ");
			
			map[posY][posX] = 0;
			
			map[Integer.parseInt(parts[2])][Integer.parseInt(parts[3])] = 3;
			
			posX = Integer.parseInt(parts[2]);
			posY = Integer.parseInt(parts[3]);
			
			window.repaint();
			window.invalidate();
		}
		if (direction.equals("down"))
		{
			String movement = socket.sendMessage("player move " + Integer.toString(posX) + " " + Integer.toString(posY));
			
			
			System.out.println("movement: " + movement);
			
			String[] parts = movement.split(" ");
			
			map[posY][posX] = 0;
			
			map[Integer.parseInt(parts[2])][Integer.parseInt(parts[3])] = 3;
			
			posX = Integer.parseInt(parts[2]);
			posY = Integer.parseInt(parts[3]);
			
			window.repaint();
			window.invalidate();
		}
		
	}
	
}
