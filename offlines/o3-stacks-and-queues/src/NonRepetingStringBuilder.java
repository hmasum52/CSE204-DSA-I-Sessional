
public class NonRepetingStringBuilder {
    // this array counts how many times a char repeats 
    // this help us to check is a string is repeated or not in O(1) 
    int[] counter = new int[26];

    //this queue will help to get the 1st non repeating character
    //we will enqueue all characters in this ques
    //and dequeue from the front if it is not repeating
    Queue<Character> queue = new Queue<>();

    public String generate(String old) {
        // old = getTestCase();
        String ans = "";

        //traverse every character of old string
        for (char ch : old.toCharArray()) {

            //if the character is not enqueued yet enqueue it
            if (counter[ch - 'a'] == 0) {
                queue.equeue(ch);
            }

            //count how many times the character repeats
            counter[ch - 'a']++;

            //if enqueued character in the queue are not non-repeating dequeue them
            while (!queue.isEmpty() && counter[queue.front() - 'a'] != 1) {
                queue.dequeue();
            }

            //at this point the queue is not empty
            //so the front character is non-repeating for sure
            if (!queue.isEmpty())
                ans += queue.front();
            else //is queue is empty which means there is not non-repeating character
                ans += '#';
        }

        // RETURN THE ANSWER ==============
        return ans;
    }

    /**
     * this testcase are for debugging
     * @return
     */
    public String getTestCase() {
        String test = "abcabc"; // aaabc#
        // test = "aabc"; // a#bb
        // test = "aac"; //a#c
        // test = "abadbc"; // aabbdd
        // test = "aabbcccaaa"; // a#b#c#####
        // test = "abacbad"; //aabbccc
        // test = "jyhrcwuengcbnuchctluxjgtxqtfvrebveewgasluuwooupcyxwgl"; //
        // jjjjjjjjjjjjjjjjjjjjjyyyyyyyyyyyyyyyyyyyyyyyyyyyqqqqq
        test = "aaaaa"; // a####
        // test = "gibblegabbler"; // ggggggiiiiiii
        return test;
    }
}