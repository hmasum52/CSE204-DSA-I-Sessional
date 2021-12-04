import java.io.*;
import java.util.*;

class Graph {
	private int vertices;
	private LinkedList<Integer> cityNumber[];
	private int piecesdfs[], piecesbfs[];
	int frienddfs[], friendbfs[];
	int total = 0, sum = 0, sumbfs = 0, positionsum = 0, positionsumbfs = 0, position;

	Graph(int v,int w)
	{
		vertices = v;

		cityNumber = new LinkedList[v];
		piecesdfs = new int [v];
		piecesbfs = new int [v];
		frienddfs = new int [w];
		friendbfs = new int [w];

		for (int i = 0; i < v; ++i)
			{
					cityNumber[i] = new LinkedList();
			}
			
	}

	void addEdge(int v, int w)
	{
		cityNumber[v].add(w); 
		cityNumber[w].add(v);
	}

	void addpieces(int v,int w)
	{
		piecesdfs[v] = w;
		piecesbfs[v] = w;
	}

	void set(int t)
	{
		total = t;
	}

	void tour(int v, int w)
	{
		
		position = w;
		sumbfs +=piecesbfs[v];
		DFS(v);
		BFS(v);
	
	}

	void BFS(int s)
    {
		positionsumbfs = piecesbfs[s];
        boolean visited[] = new boolean[vertices];

        LinkedList<Integer> queue = new LinkedList<Integer>();
 
        visited[s]=true;
        queue.add(s);
 
        while (queue.size() != 0)
        {
            s = queue.poll();
            Iterator<Integer> i = cityNumber[s].listIterator();
            while (i.hasNext())
            {
                int n = i.next();
                if (!visited[n])
                {
					sumbfs += piecesbfs[n];
					positionsumbfs += piecesbfs[n];
					piecesbfs[n] = 0;
					friendbfs[position] = positionsumbfs;

                    visited[n] = true;
                    queue.add(n);
                }
            }
        }
    }

	void DFS(int v)
	{
		positionsum = piecesdfs[v];
		boolean visited[] = new boolean[vertices];
		sum += piecesdfs[v];
		piecesdfs[v] = 0;
		DFSUtil(v, visited);
	}

	void DFSUtil(int v, boolean visited[])
	{

		visited[v] = true;

		Iterator<Integer> i = cityNumber[v].listIterator();
		while (i.hasNext())
		{
			int n = i.next();
			if (!visited[n])
			{
				sum += piecesdfs[n];
				positionsum += piecesdfs[n];
				piecesdfs[n] = 0;
				
				frienddfs[position] = positionsum;
				DFSUtil(n, visited);
			}
				
		}
	}

	void printdfs()
	{
		if(total==sum)
			System.out.println("Mission Accomplished");

		else System.out.println("Mission Impossible");

		System.out.println(sum + " out of " + total + " are collected.");
		for(int i = 0 ; i <frienddfs. length;i++)
			System.out.println(i + " collected " + frienddfs[i] + " pieces.");
	}

	void printbfs()
	{
		if(total==sumbfs)
			System.out.println("Mission Accomplished");

		else System.out.println("Mission Impossible");

		System.out.println(sumbfs + " out of " + total + " are collected.");
		for(int i = 0 ; i < friendbfs.length;i++)
			System.out.println(i + " collected " + friendbfs[i] + " pieces.");
	}

	public static void main(String args[])
	{
		Scanner sc = new Scanner(System.in);
		int city = sc.nextInt();

		int road = sc.nextInt();

		int loc = sc.nextInt();

		int friends = sc.nextInt();

		Graph g = new Graph(city,friends);

		for(int i = 0;i<road;i++)
		g.addEdge(sc.nextInt(), sc.nextInt());

		int pieces = 0;

		for(int i = 0;i<loc;i++)
		{
			int pi= sc.nextInt();
			int p = sc.nextInt();
			pieces += p;
			g.addpieces(pi, p);
		}

		g.set(pieces);
			
		
		for(int i = 0;i<friends;i++)
			g.tour(sc.nextInt(), sc.nextInt());

		System.out.println("Press 1 for DFS traversal or 2 for bfs traversal");
		int option = sc.nextInt();

		try{
			PrintStream writer = new PrintStream(new File("test.txt"));
			System.setOut(writer);
			if(option == 2)
				g.printbfs();

			if(option == 1)
				g.printdfs();
			
		} catch (Exception e) {
			
		}
		
		sc.close();
	}
}
