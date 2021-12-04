public class Stack<T> {
    class Node {
        T data;
        Node next;

        public Node(T data) {
            this.data = data;
        }
    }

    private Node top;
    private int length;
    
    public void push(T data) {
        Node node = new Node(data);

        //increase the length of stack
        length++;

        //if the stack is empty
        if (isEmpty()) {
            top = node;
            return;
        }

        //connect new node with top
        node.next = top;
        //set new node as top
        top = node;
    }

    /**
     * 
     * @return the top element of the stack
     * and remove it from the stack
     * and return null if the stack is empty
     */
    public T pop() {
        if (!isEmpty()) {
            length--;

            //store the top value to return
            T value = top.data;
            //set new top value
            top = top.next;

            return value;
        }
        return null;
    }

    public T top() {
        return top.data;
    }

    public int length() {
        return length;
    }

    public boolean isEmpty() {
        return top == null;
    }
}