package GUI;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

import Connection.ClientSocket;

public class Ghost extends Entity implements Runnable{
	
	
	public BufferedImage imageRight;
	public BufferedImage imageLeft;
	public BufferedImage imageScared;

	public boolean isMoving = false;
	public String color;
	
	
	
	
	
	public Ghost(int x, int y, String pcolor, ClientSocket psocket, int[][] pmap, JFrame pwindow) throws IOException {
		
		imageRight = ImageIO.read(getClass().getResourceAsStream("/redghostright.png"));
		imageLeft = ImageIO.read(getClass().getResourceAsStream("/redghostleft.png"));
		
		imageScared = ImageIO.read(getClass().getResourceAsStream("/scaredghost.png"));

		
		currentImage = imageRight;
		posX = x;
		posY = y;
		color = pcolor;
		
		socket = psocket;
		map = pmap;
		window = pwindow;
		
		//direction = "right";
		
	}
	
	
	public void draw(Graphics g)
	{
		
		g.drawImage(currentImage, posX*30, posY*30, 30, 30, null);
		
		
	}


	@Override
	public void run() {
		
		System.out.println("RUN DEL ENEMIGO");

		
		
		while(true) {
			
			try {
				
				
				System.out.println("me muevo soy el enemigo");
				move();
				Thread.sleep(450);
				
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
		
		
	}
	
	
	public void moveDown() {
		
		direction = "down";
		
		
	}
	
	
	
	public void move() {
		
		
		System.out.println("EL MALO SE ESTA MOVIENODOOODODODO");
		
		if (direction.equals("right"))
		{
			String movement = socket.sendMessage("enemy move "+ color + " " + Integer.toString(posX) + " " + Integer.toString(posY));
			
			
			System.out.println("movement: " + movement);
			
			String[] parts = movement.split(" ");
			
			map[posY][posX] = 0;
			
			map[Integer.parseInt(parts[3])][Integer.parseInt(parts[4])] = 4;
			
			posX = Integer.parseInt(parts[3]);
			posY = Integer.parseInt(parts[4]);
			
			window.repaint();
			window.invalidate();
			
			//Thread.sleep(1000);
			
		}
		if (direction.equals("left"))
		{
			String movement = socket.sendMessage("enemy move "+ color + " " + Integer.toString(posX) + " " + Integer.toString(posY));
			
			
			System.out.println("movement: " + movement);
			
			String[] parts = movement.split(" ");
			
			map[posY][posX] = 0;
			
			map[Integer.parseInt(parts[3])][Integer.parseInt(parts[4])] = 4;
			
			posX = Integer.parseInt(parts[3]);
			posY = Integer.parseInt(parts[4]);
			
			window.repaint();
			window.invalidate();
		}
		if (direction.equals("up"))
		{
			String movement = socket.sendMessage("enemy move "+ color + " " + Integer.toString(posX) + " " + Integer.toString(posY));
			
			
			System.out.println("movement: " + movement);
			
			String[] parts = movement.split(" ");
			
			map[posY][posX] = 0;
			
			map[Integer.parseInt(parts[3])][Integer.parseInt(parts[4])] = 4;
			
			posX = Integer.parseInt(parts[3]);
			posY = Integer.parseInt(parts[4]);
			
			window.repaint();
			window.invalidate();
		}
		if (direction.equals("down"))
		{
			String movement = socket.sendMessage("enemy move "+ color + " " + Integer.toString(posX) + " " + Integer.toString(posY));
			
			
			System.out.println("movement: " + movement);
			
			String[] parts = movement.split(" ");
			
			map[posY][posX] = 0;
			
			map[Integer.parseInt(parts[3])][Integer.parseInt(parts[4])] = 4;
			
			posX = Integer.parseInt(parts[3]);
			posY = Integer.parseInt(parts[4]);
			
			window.repaint();
			window.invalidate();
		}
		
	}
	
	
	

}
