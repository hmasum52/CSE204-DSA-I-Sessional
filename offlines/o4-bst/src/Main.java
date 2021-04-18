import java.util.Scanner;

public class Main {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_BRIGHT_RED = "\u001B[91m";
    public static final String ANSI_BRIGHT_GREEN = "\u001B[92m";
    public static final String ANSI_BRIGHT_YELLOW = "\u001B[93m";
    public static final String ANSI_BRIGHT_BLUE = "\u001B[94m";
    public static final String ANSI_BRIGHT_MAGENTA = "\u001B[95m";
    public static final String ANSI_BRIGHT_CYAN = "\u001B[96m";

    public static void main(String[] args) {
        // debug();
       menu();
    }

    public static void menu() {
        Scanner scanner = new Scanner(System.in);
        try {
            BST bst = new BST();
            while (true) {
                printInstructions();
                System.out.println(ANSI_BRIGHT_GREEN+"Enter a number or press q to exit: "+ANSI_RESET);
                String userInput = scanner.next();
                if (userInput.equals("q"))
                    break;

                int input = Integer.parseInt(userInput);
                switch (input) {
                case 1:
                    System.out.print(ANSI_YELLOW + "Enter a integer to insert: " +ANSI_RESET);
                    int value = scanner.nextInt();
                    bst.insertItem(value);
                    System.out.println(ANSI_GREEN+"Inseration completes"+ANSI_RESET);
                    break;
                case 2:
                    System.out.print(ANSI_YELLOW+"Enter a number to search: "+ANSI_RESET);
                    value = scanner.nextInt();
                    System.out.print(ANSI_GREEN+"Status: "+ANSI_BRIGHT_CYAN);
                    bst.searchItem(value);
                    System.out.println(ANSI_RESET);
                    break;
                case 3:
                    System.out.print(ANSI_YELLOW +"Enter a integer to delete: " + ANSI_RESET);
                    value = scanner.nextInt();
                    bst.deleteItem(value);
                    System.out.println(ANSI_RED +"Deletion completes"+ANSI_RESET);
                    break;
                case 4:
                    System.out.print(ANSI_YELLOW +"Enter a integer to find Successor: " + ANSI_RESET);
                    value = scanner.nextInt();
                    System.out.println(ANSI_GREEN + "In-order successor of " + value + ": " + ANSI_BRIGHT_CYAN
                            + bst.getInOrderSuccessor(value));
                    System.out.println(ANSI_RESET);
                    break;
                case 5:
                    System.out.print(ANSI_YELLOW +"Enter a integer to find Predecessor: " + ANSI_RESET);
                    value = scanner.nextInt();
                    System.out.println(ANSI_GREEN + "In-order predecessor of " + value + ": " + ANSI_BRIGHT_CYAN
                            + bst.getInOrderPredecessor(value)+ANSI_RESET);
                    break;
                case 6:
                    System.out.print(ANSI_YELLOW +"Enter a integer to find depth:" + ANSI_RESET);
                    value = scanner.nextInt();
                    System.out.println(ANSI_GREEN + "Depth of " + value + ": " + ANSI_BRIGHT_CYAN
                            + bst.getItemDepth(value) + ANSI_RESET);
                    break;
                case 7:
                    System.out.println(ANSI_GREEN +"Maximum value: " + ANSI_BRIGHT_CYAN + bst.getMaxItem() + ANSI_RESET);
                    break;
                case 8:
                    System.out.println(ANSI_GREEN +"Minimum value: " + ANSI_BRIGHT_CYAN + bst.getMinItem() + ANSI_RESET);
                    break;
                case 9:
                    System.out.println(ANSI_GREEN +"Size of the tree: " + ANSI_BRIGHT_CYAN + bst.getSize() + ANSI_RESET);
                    break;
                case 10:
                    System.out.println(ANSI_GREEN +"Height of the tree: " + ANSI_BRIGHT_CYAN + bst.getHeight() + ANSI_RESET);
                    break;
                case 11:
                    System.out.print(ANSI_GREEN + "In-order traversal: " + ANSI_BRIGHT_CYAN);
                    bst.printInOrder();
                    System.out.println(ANSI_RESET);
                    break;
                case 12:
                    System.out.print(ANSI_GREEN +"Pre-order traversal: " + ANSI_BRIGHT_CYAN);
                    bst.printPreOrder();
                    System.out.println(ANSI_RESET);
                    break;
                case 13:
                    System.out.print(ANSI_GREEN +"Post-order traversal: " + ANSI_BRIGHT_CYAN);
                    bst.printPostOrder();
                    System.out.println(ANSI_RESET);
                    break;
                default:
                    System.out.println(ANSI_RED+"Input out of range. only 1 to 13 is allowed."+ANSI_RESET);
                }

            }
            scanner.close();
        } catch (Exception e) {
            System.out.println("Invalid user input");
            scanner.close();
        }
    }
    
    public static void printInstructions() {
        System.out.println(ANSI_BLUE+" ====================================INSTRUSTIONS====================================");
        System.out.println("||        1-insert          |         2-search           |          3-delete        ||");
        System.out.println("|| 4-Get in-order successor | 5-get in-order predecessor |       6-get item depth   ||");
        System.out.println("||        7-get max         |      8-get min    | 9-get size |    10-get height     ||");
        System.out.println("||     11-print in-order    |     12- print pre-order    |    13-print post-order   ||");
        System.out.println(" ===================================================================================="+ANSI_RESET);
    }
    
    public static void debug() {
        BST bst = new BST();
        //level 0
        bst.insertItem(42);

        //level 1
        bst.insertItem(25);
        bst.insertItem(70);

        //level 2
        bst.insertItem(20);
        bst.insertItem(35);
        bst.insertItem(52);
        bst.insertItem(97);

        //level 3
        bst.insertItem(11);
        bst.insertItem(28);
        bst.insertItem(39);
        bst.insertItem(47);
        bst.insertItem(57);

        //level 4
        bst.insertItem(26);
        bst.insertItem(30);

        System.out.println("Size: " + bst.getSize());
        System.out.println("max : " + bst.getMaxItem());
        System.out.println("min: " + bst.getMinItem());
        System.out.println("tree height: " + bst.getHeight());

        System.out.print("In order: ");
        bst.printInOrder();
        System.out.print("Pre order: ");
        bst.printPreOrder();
        System.out.print("Post order: ");
        bst.printPostOrder();

        int value = 47;
        System.out.println("in-order successor of " + value + ": " + bst.getInOrderSuccessor(value));
        System.out.println("in-order predecessor of " + value + ": " + bst.getInOrderPredecessor(value));
        System.out.println("Depth of " + value + " is " + bst.getItemDepth(value));

        System.out.print("In order: ");
        bst.printInOrder();
        bst.deleteItem(2200);
        System.out.print("In order: ");
        bst.printInOrder();
        bst.deleteItem(200);
        System.out.print("In order: ");
        bst.printInOrder();
    }
}
