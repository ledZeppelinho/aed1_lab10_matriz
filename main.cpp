/**
* PUC Minas - Instituto de Ciencias Exatas e Informatica
* Ciencia da Computacao - LAB. 10
*/


import IO.*;
import java.util.*;
import java.util.Formatter;
import java.util.Scanner;
import java.io.File;

class Lab10
{
	public static void main(String[] args)
	{
		Matriz mtr = new Matriz(5,5);
		mtr.lerMatriz();
		mtr.salvar();
		
		mtr.ler();
		mtr.printMatrizEmGrid();
	}

}

class Matriz{
	private int[][] matriz;
	
	public Matriz(int x, int y)
	{
		matriz = new int[x][y];
	}
	
	public void lerMatriz()
	{
		for(int x = 0; x < matriz.length; x++)
		{
			for(int y = 0; y < matriz[x].length; y++)
			{
				matriz[x][y] = IO.readint("Digite o valor para matriz[" + x + "][" + y + "]: ");
			} 
		}
	}
	
	public int getElemento(int x, int y)
	{
		return matriz[x][y];
	}
	
	public void setElemento(int x, int y, int value)
	{
		matriz[x][y] = value;
	}
	
	public int GetLength(int dimensao)
	{
		if(dimensao == 0) return matriz.length;
		else return matriz[0].length;
	}
	
	public Matriz soma(Matriz mat1, Matriz mat2)
	{
		Matriz mtrz = new Matriz(mat1.GetLength(0), mat1.GetLength(1));
		for(int x = 0; x < mat1.GetLength(0); x++)
		{
			for(int y = 0; y < mat1.GetLength(1); y++)
			{
				int res = mat1.getElemento(x, y) + mat2.getElemento(x, y);
				mtrz.setElemento(x, y, res);
			} 
		}
		return mtrz;
	}
	
	public Matriz multiplicar(Matriz mat1, Matriz mat2)
	{
		Matriz mtrz = new Matriz(mat1.GetLength(1), mat2.GetLength(0));
		for(int l = 0; l < mat1.GetLength(0); l++)
		{
			for(int k = 0; k < mat2.GetLength(1); k++)
			{
				for(int m = 0; m < mat1.GetLength(1); m++ )
				{
					int res = mat1.getElemento(l, m) * mat2.getElemento(m, k);
					mtrz.setElemento(l, k, res);			
				}
			}
		}
		return mtrz;
	}
	
	public Matriz getTransposta()
	{
		Matriz mtrz = new Matriz(matriz[0].length, matriz.length);
		for(int x = 0; x < matriz.length; x++)
		{
			for(int y = 0; y < matriz[x].length; y++)
			{
				mtrz.setElemento(x, y, matriz[y][x]);
			} 
		}
		return mtrz;
	}

	public void printMatriz()
	{
		for(int x = 0; x < matriz.length; x++)
		{
			for(int y = 0; y < matriz[x].length; y++)
			{
				IO.print(" " + matriz[x][y]);
			} 
		}
	}

	public void printMatrizEmGrid()
	{
		for(int x = 0; x < matriz.length; x++)
		{
			for(int y = 0; y < matriz[x].length; y++)
			{
				IO.print(" " + matriz[x][y]);
			} 
			IO.print("\n");
		}
	}
	
	public void salvar(){
		Arq.openWrite("mat.xml");
		Arq.print("<matriz>");
		
		Arq.print("<length1>");
		Arq.print(matriz.length);
		Arq.print("</length1>");
		
		Arq.print("<length2>");
		Arq.print(matriz[0].length);
		Arq.print("</length2>");
		
		Arq.print("<dados>");
		for(int x = 0; x < matriz.length; x++)
		{
			for(int y = 0; y < matriz[x].length; y++)
			{
				Arq.print("<column" + x + "_row" + y + ">");
				Arq.print(matriz[x][y]);
				Arq.print("</column" + x + "_row" + y + ">");
			} 
			
		}
		
		Arq.print("</dados>");
		Arq.print("</matriz>");
		Arq.close();		
	}
	
	public void ler(){
		Arq.openRead("mat.xml");
		String xml = Arq.readLine();
		
		int len1 = xml.indexOf("<length1>");
		int len1C = xml.indexOf("</length1>", len1);
      int len1Val = Integer.parseInt(xml.substring(len1 + 9, len1C));
		
		int len2 = xml.indexOf("<length2>", len1C);
		int len2C = xml.indexOf("</length2>", len2);
		int len2Val = Integer.parseInt(xml.substring(len2 + 9, len2C));
		
		matriz = new int[len1Val][len2Val];
		
		for(int x = 0; x < matriz.length; x++)
		{
			for(int y = 0; y < matriz[x].length; y++)
			{
				String rowOpen = "<column" + x + "_row" + y + ">";
				String rowClose = "</column" + x + "_row" + y + ">";
			
				int col1 = xml.indexOf(rowOpen) + rowOpen.length();
				int col1C = xml.indexOf(rowClose);
		      int col1Val = Integer.parseInt(xml.substring(col1, col1C));
				
				matriz[x][y] = col1Val;
			
				Arq.print("<row>");
				Arq.print(matriz[x][y]);
				Arq.print("</row>");
			} 
		}
		
		Arq.close();
		
	}
}


class Arq
{
   private static boolean write = false;
   private static boolean read = false;
   private static Formatter saida = null;
   private static Scanner entrada = null;

	public static void openWrite(String nomeArq) {
      close();

		try{
		   saida = new Formatter(nomeArq);
         write = true;
		}  catch (Exception e) {}
   }

	public static void openRead(String nomeArq) {
      close();

		try{
         entrada = new Scanner(new File(nomeArq));
         read = true;
		}  catch (Exception e) {}
   }

	public static void close() {
      if(write == true){
         saida.close();
         write = false;
      }
      if(read == true){
         entrada.close();
         read = false;
      }
	}

   public static void print(int x){
      if(write == true){
		   saida.format( "%d", x);
      }
   }

   public static void print(double x){
      if(write == true){
	   	saida.format( "%f", x);
      }
   }

   public static void print(String x){
      if(write == true){
   		saida.format( "%s", x);
      }
   }

   public static void print(boolean x){
      if(write == true){
		   saida.format( "%s", ((x) ? "true" : "false"));
      }
   }

   public static void print(char x){
      if(write == true){
	   	saida.format( "%c", x);
      }
   }

   public static void println(int x){
      if(write == true){
   		saida.format( "%d\n", x);
      }
   }

   public static void println(double x){
      if(write == true){
		   saida.format( "%f\n", x);
      }
   }

   public static void println(String x){
      if(write == true){
	   	saida.format( "%s\n", x);
      }
   }

   public static void println(boolean x){
      if(write == true){
   		saida.format( "%s\n", ((x) ? "true" : "false"));
      }
   }

   public static void println(char x){
      if(write == true){
		   saida.format( "%c\n", x);
      }
   }

   public static int readInt(){
      int resp = -1;
		try{
         resp = entrada.nextInt();
		}  catch (Exception e) {}
      return resp;
   }

   public static char readChar(){
      char resp = ' ';
		try{
         resp = entrada.next().charAt(0);
		}  catch (Exception e) {}
      return resp;
   }

   public static double readDouble(){
      double resp = -1;
		try{
         resp = entrada.nextDouble();
		}  catch (Exception e) {}
      return resp;
   }

   public static String readString(){
      String resp = "";
		try{
         resp = entrada.next();
		}  catch (Exception e) {}
      return resp;
	}

   public static boolean readBoolean(){
      boolean resp = false;
		try{
         resp = (entrada.next().equals("true")) ? true : false;
		}  catch (Exception e) {}
      return resp;
	}

   public static String readLine(){
      String resp = "";
		try{
         resp = entrada.nextLine();
		}  catch (Exception e) {}
      return resp;
	}


   public static boolean hasNext(){
      return entrada.hasNext();
   }
}
