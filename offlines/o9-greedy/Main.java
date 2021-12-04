import java.util.regex.Pattern;

public class Main {
    static String sample 
    = "Select the piece(s) such that it matches to the following diagram to form a square.\n\n"
    + "![](https://buet-edu-1.s3.amazonaws.com/auto_upload/sDCgfAyDqYhCWzPhpyCXj8aU0b63/1620514779297.PNG\n)\n\nA:"
    + "  \n![](https://buet-edu-1.s3.amazonaws.com/auto_upload/sDCgfAyDqYhCWzPhpyCXj8aU0b63/1620514842290.PNG)  \n  \n\nB:  \n"
    + "![](https://buet-edu-1.s3.amazonaws.com/auto_upload/sDCgfAyDqYhCWzPhpyCXj8aU0b63/1620514851093.PNG)  \n  \n\nC:  \n![](https://buet-edu-1.s3.amazonaws.com/auto_upload/sDCgfAyDqYhCWzPhpyCXj8aU0b63/1620514859803.PNG)  \n\nD:  \n![](https://buet-edu-1.s3.amazonaws.com/auto_upload/sDCgfAyDqYhCWzPhpyCXj8aU0b63/1620514869337.PNG)\n";

    public static void main(String[] args) {
        

        // ![]()
        // "!\\[]\\(([^)]+)\\)"
        String temp = "(!\\[.*?\\])\\((.*?)\\)";
        String tempN = "(!\\[.*?\\])\\((.*?)\n\\)";
        Pattern pattern = Pattern.compile(temp);
        Pattern patternN = Pattern.compile(tempN);
        sample = patternN.matcher(sample).replaceAll("<img src='$2' width='90%' >");
        sample = pattern.matcher(sample).replaceAll("<img src='$2' width='90%' >");
        System.out.println(sample);
    }
}