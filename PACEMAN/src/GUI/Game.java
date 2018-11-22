package GUI;
import Connection.ClientSocket;


import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Game extends JPanel implements KeyListener{

	
	
	ClientSocket socket;
	Player player;
	Ghost redGhost;
	
	public JFrame window = new JFrame();
	private int map[][] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	           		       {1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1},
			               {1,2,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,2,1},
			               {1,2,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,2,1},
			               {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
			               {1,2,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,2,1},
			               {1,2,2,2,2,2,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,2,2,2,2,2,1},
			               {1,2,1,1,1,2,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,2,1,1,1,2,1},
			               {1,2,1,1,1,2,1,1,0,0,0,0,0,0,4,0,0,0,0,0,0,1,1,2,1,1,1,2,1},
			               {1,2,2,2,2,2,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,2,2,2,2,2,1},
			               {1,2,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,2,1},
			               {1,2,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,2,1},
			               {1,2,1,1,1,2,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,2,1,1,1,2,1},
			               {1,2,2,2,2,2,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,2,2,2,2,2,1},
			               {1,2,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,2,1},
			               {1,2,1,1,1,2,2,2,2,2,2,2,2,2,3,2,2,2,2,2,2,2,2,2,1,1,1,2,1},
			               {1,2,1,1,1,2,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,2,1,1,1,2,1},
			               {1,2,1,1,1,2,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,2,1,1,1,2,1},
			               {1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1},
			               {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
			           
	
	
	public Game() throws IOException {
		
		
		
		socket = new ClientSocket();
			

		
		
		
		
		
		
		
		this.setFocusable(true);
		this.addKeyListener(this);
		
		window.add(this);
		
		window.setSize(1000,630);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setVisible(true);
		window.setBackground(new Color(0,0,0));
		
		
		
		
			
			player = new Player(15, 14, socket, map, window);
			redGhost = new Ghost(8, 14, "red", socket, map, window);
			
			
			
			Thread playerThread = new Thread(player);
			Thread redGhostThread = new Thread(redGhost);
			
			System.out.println("este es el player: " + player);
			System.out.println("este es el ghost: " + redGhost);
			
			
			playerThread.start();
			redGhostThread.start();
			

		
		
		
		
	
		
		
		
	}
	
	public void paint(Graphics g)
	{
		
		System.out.println("estoy pintando el mapa");
		
		try {
		for(int i = 0; i<20; i++) {
			
			for (int j = 0; j<29; j++) {
				
				if(map[i][j] == 1) {
				
					WallBlock wall = new WallBlock(j,i);
			
					wall.draw(g);
				}
				
				if(map[i][j] == 2) {
					
					Dot dot = new Dot(j,i);
			
					dot.draw(g);
				}
				if(map[i][j] == 3) {
					
					System.out.println("player is here " + i + ", " + j);
					
					player.setPosX(j);
					player.setPosY(i);
				}
				if(map[i][j] == 4) {
					
					System.out.println("red ghost is here " + i + ", " + j);
					
					//redGhost.setPosX(j);
					//redGhost.setPosY(i);
				}
	
				
			}
		}
		player.draw(g);
		//redGhost.draw(g);
		
		
        
		} catch (IOException e) {
			
			e.printStackTrace();
		}
		
		

	}

	@Override
	public void keyPressed(KeyEvent e) {
		int keyCode = e.getKeyCode();
		
		System.out.println("moving");
		
		if(keyCode == KeyEvent.VK_RIGHT){
			
			
			//redGhost.isMoving = true;
			
			int currentX = player.getPosX();
			int currentY = player.getPosY();
			
			
			
			if( map[currentY][currentX + 1] != 1)
			{
				
				String msg = socket.sendMessage("player direction r");
			
				
				
				
				System.out.println("moving right");
				player.moveRight();
				

				window.repaint();
				window.revalidate();
				
			}
			
		}
		
		if(keyCode == KeyEvent.VK_LEFT){
			
			
			
			//redGhost.isMoving = true;
			int currentX = player.getPosX();
			int currentY = player.getPosY();
			
			
			
			if( map[currentY][currentX - 1] != 1)
			{
				
				String msg = socket.sendMessage("player direction l");
			
				
				
				
				System.out.println("moving left");
				player.moveLeft();
				

				window.repaint();
				window.revalidate();
				
			}
			
		
			
		}
		
		if(keyCode == KeyEvent.VK_UP){
			
			
			//redGhost.isMoving = true;
			
			int currentX = player.getPosX();
			int currentY = player.getPosY();
			
			
			
			if( map[currentY - 1][currentX] != 1)
			{
				
				String msg = socket.sendMessage("player direction u");
			
				
			
				
				System.out.println("moving up");
				player.moveUp();
				

				window.repaint();
				window.revalidate();
				
			}
			
		}
		
		if(keyCode == KeyEvent.VK_DOWN){
			
			
			//redGhost.isMoving = true;
			
			int currentX = player.getPosX();
			int currentY = player.getPosY();
			
			
			
			if( map[currentY + 1][currentX] != 1)
			{
				
				String msg = socket.sendMessage("player direction d");
			
				
				
				
				System.out.println("moving down");
				player.moveDown();
				

				window.repaint();
				window.revalidate();
				
			}
			
		}
		
	}

	@Override
	public void keyReleased(KeyEvent e) {
		
		
	}

	@Override
	public void keyTyped(KeyEvent e) {
		
		
	}
	
	
	
}
