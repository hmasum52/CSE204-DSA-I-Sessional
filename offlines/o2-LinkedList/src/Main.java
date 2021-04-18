
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Scanner;


public class Main {
    public static void main(String[] args) {
        PillowGame pillowGame = new PillowGame();
        takeUserInput(pillowGame, System.in);
       /*  try {
            takeUserInput(pillowGame, new FileInputStream("test1.txt"));

        } catch (Exception e) {
            System.out.println("File not found");
        } */
        //test1(pillowGame);
    }
    
    public static void takeUserInput(PillowGame pillowGame, InputStream inputStream) {
        try {
            Scanner scanner = new Scanner(inputStream);
            int n = Integer.parseInt(scanner.nextLine());

            int[] reflexTimeList = new int[n];
            String[] inputs = scanner.nextLine().split(" ");
            for (int i = 0; i < inputs.length; i++) {
                reflexTimeList[i] = Integer.parseInt(inputs[i]);
            }
            pillowGame.addPlayersToTheGame(reflexTimeList);
            pillowGame.startGame();

            inputs = scanner.nextLine().split(" ");
            int time = Integer.parseInt(inputs[0]);
            String instruction = inputs[1];
            while (!instruction.equals("F")) {
                switch (instruction) {
                case "P":
                    pillowGame.printPillowHolderAtTime(time);
                    break;
                case "M":
                    pillowGame.eliminatePlayerAtTime(time);
                    break;
                case "R":
                    pillowGame.reversePillowDirection(time);
                    break;
                // new code
                case "I":
                    pillowGame.insertPlayerAt(time, Integer.parseInt(inputs[2]));
                    break;

                }
                inputs = scanner.nextLine().split(" ");
                time = Integer.parseInt(inputs[0]);
                instruction = inputs[1];
            }

            // new code
            pillowGame.finishGame(time);

            scanner.close();
        } catch (Exception e) {
            System.out.println("invalid input format");
        }
       
    }
    
    public static void test1(PillowGame pillowGame) {
        int[] palyers = { 4, 5, 2 };
        pillowGame.addPlayersToTheGame(palyers);
        pillowGame.startGame();

        pillowGame.printPillowHolderAtTime(0);
        pillowGame.printPillowHolderAtTime(1);
        pillowGame.printPillowHolderAtTime(6);
        pillowGame.eliminatePlayerAtTime(6);
        pillowGame.printPillowHolderAtTime(6);
        pillowGame.printActivePlayers();
        pillowGame.printPillowHolderAtTime(7);
        pillowGame.printPillowHolderAtTime(8);
        pillowGame.printPillowHolderAtTime(9);
        pillowGame.insertPlayerAt(10, 1);
        pillowGame.printPillowHolderAtTime(10);
        pillowGame.printPillowHolderAtTime(11);
        pillowGame.printPillowHolderAtTime(12);
        pillowGame.printPillowHolderAtTime(13);
        pillowGame.printPillowHolderAtTime(14);
        pillowGame.printPillowHolderAtTime(15);
        pillowGame.printPillowHolderAtTime(16);
        pillowGame.printPillowHolderAtTime(17);
        pillowGame.printPillowHolderAtTime(18);
        pillowGame.printPillowHolderAtTime(19);
        pillowGame.printPillowHolderAtTime(20);
        pillowGame.printPillowHolderAtTime(21);
        pillowGame.reversePillowDirection(22);
        pillowGame.printPillowHolderAtTime(22);
        pillowGame.printPillowHolderAtTime(23);
        pillowGame.printPillowHolderAtTime(24);
        pillowGame.finishGame(25);

    }

    public static void test2(PillowGame pillowGame){
        int[] palyers = { 4, 5, 2 };
        pillowGame.addPlayersToTheGame(palyers);
        pillowGame.startGame();

        pillowGame.printPillowHolderAtTime(6);
        pillowGame.eliminatePlayerAtTime(6);
        pillowGame.printPillowHolderAtTime(6);

        pillowGame.finishGame(7);
    }

    public static void test3(PillowGame pillowGame) {
        int[] palyers = { 4, 5, 2 };
        pillowGame.addPlayersToTheGame(palyers);
        pillowGame.startGame();

        pillowGame.reversePillowDirection(5);
        pillowGame.finishGame(6);
    }
    
    public static void test4(PillowGame pillowGame) {
        int[] palyers = { 4, 5, 2 };
        pillowGame.addPlayersToTheGame(palyers);
        pillowGame.startGame();
        
        pillowGame.eliminatePlayerAtTime(1);
        pillowGame.eliminatePlayerAtTime(2);
        pillowGame.insertPlayerAt(3, 5);
        pillowGame.eliminatePlayerAtTime(5);
        pillowGame.finishGame(10);
    }

    public static void test5(PillowGame pillowGame) {
        int[] palyers = { 4, 5, 2 };
        pillowGame.addPlayersToTheGame(palyers);
        pillowGame.startGame();

        pillowGame.printPillowHolderAtTime(1); //P

        pillowGame.printPillowHolderAtTime(4); //P
        pillowGame.reversePillowDirection(4); //R
        pillowGame.reversePillowDirection(4); //R
        pillowGame.printPillowHolderAtTime(7); //P
        pillowGame.eliminatePlayerAtTime(7); //M
        pillowGame.printPillowHolderAtTime(7); //P
        pillowGame.insertPlayerAt(8, 2); //I 2
        pillowGame.reversePillowDirection(8); //R
        pillowGame.insertPlayerAt(8, 3);//I 3
        pillowGame.reversePillowDirection(8); // R
        pillowGame.insertPlayerAt(8, 4);//I 4 
        pillowGame.printPillowHolderAtTime(8); //P
        pillowGame.reversePillowDirection(8); //R

        pillowGame.printPillowHolderAtTime(10); //P

        pillowGame.printPillowHolderAtTime(1610);//P
        pillowGame.eliminatePlayerAtTime(1611);//M
        pillowGame.reversePillowDirection(1611);//R
        pillowGame.eliminatePlayerAtTime(1611);//M
        pillowGame.printPillowHolderAtTime(1611);//P
        pillowGame.finishGame(1611);//F

    }
}

