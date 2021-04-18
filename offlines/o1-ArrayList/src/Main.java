public class Main {
    public static void main(String[] args) {
        try {
            String[] temp = { "1", "2", "3" };
            String[] temp1 = { "2", "4", "10", "22" };
            Array ar = new Array();
            System.out.println("length: " + ar.length());
            System.out.println("isEmpty? : " + ar.isEmpty() + "\n");

            ar.merge(temp, temp1);

            System.out.println("Initial elements: ");
            for (int i = 0; i < ar.length(); i++) {
                System.out.print(ar.getAnElement(i) + " ");
            }
            System.out.println("\n" + "length: " + ar.length() + "\n");

            ar.add("app");
            System.out.println("Elements after appending an element: ");
            for (int i = 0; i < ar.length(); i++) {
                System.out.print(ar.getAnElement(i) + " ");
            }
            System.out.println("\n" + "length: " + ar.length() + "\n");

            ar.add(2, "ins");
            System.out.println("Elements after inserting an element at idx 2: ");
            for (int i = 0; i < ar.length(); i++) {
                System.out.print(ar.getAnElement(i) + " ");
            }
            System.out.println("\n" + "length: " + ar.length() + "\n");

            System.out.println("Subarray from index 1 to 5: ");
            Array subAr = ar.subArray(1, 5);
            for (int i = 0; i < subAr.length(); i++) {
                System.out.print(subAr.getAnElement(i) + " ");
            }
            System.out.println("\n\n");

            System.out.println("Index's of '2': ");
            for (int i : ar.findIndex("2")) {
                System.out.print("i: " + i + "  ");
            }
            System.out.println("\n\n");

            ar.remove("2");
            System.out.println("Elements after removing all 2s: ");
            for (int i = 0; i < ar.length(); i++) {
                System.out.print(ar.getAnElement(i) + " ");
            }
            System.out.print("\n" + "length: " + ar.length() + "\n");

        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
