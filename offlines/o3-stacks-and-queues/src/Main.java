import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try {
            Scanner scanner = new Scanner(System.in);
            while (true) {
                if(!problem1(scanner))
                    break;

                /* if (!problem2(scanner))
                    break; */
            }
            scanner.close();
        } catch (Exception e) {
            System.out.println("invalid input format or error taking userinput.");
        }
    }

    public static boolean problem1(Scanner scanner) {
        // INPUT ====================================
        System.out.println("\nInput q to exit");
        String exp = scanner.nextLine();
        if (exp.equals("q")) {
            return false;
        }

        // VALIDATE =================================
        ExpressionValidator validator = new ExpressionValidator();

        // PRINT OUTPUT =============================
        if (validator.validate(exp)) {
            System.out.println("Valid expression, Computed value: " + validator.getAnswer());
        } else {
            System.out.println("Not valid.");
        }

        return true;
    }
    
    public static boolean problem2(Scanner scanner) {
        // INPUT =================================
        System.out.println("\nInput -1 to exit");
        String input = scanner.nextLine();
        if (input.equals("-1")) {
            return false;
        }

        // BUILD STRING ==========================
        NonRepetingStringBuilder stringBuilder = new NonRepetingStringBuilder();
        String output = stringBuilder.generate(input);

        // PIRNT OUPUT ===========================
        System.out.println(output);

        return true;
    }
   
}