public class Queue<T> {
    class Node {
        T value;
        Node next;

        public Node(T value){
            this.value = value;
        }
    }

    Node front;
    Node back;
    int length = 0;

    /**
     * 
     * @param value
     */
    public void equeue(T value) {
        length++;
        Node node = new Node(value);
        if (front == null) {
            front = node;
            back = node;
            return;
        }

        //connect new node with back node
        back.next = node;
        //make new node back node
        back = node;
    }
    
    /**
     * 
     * @return
     */
    public T dequeue() {
        if (back != null) {
            length--;
            // get the value of current front
            T value = front.value;
            // disconnect front from the list
            front = front.next;
            return value;
        }
        return null;
    }
    
    /**
     * 
     */
    public boolean isEmpty() {
        return front == null;
    }
    
    /**
     * 
     * @return the value at the front 
     */
    public T front() {
        return front.value;
    }
    
    public T back() {
        return back.value;
    }

    public int length() {
        return length;
    }

    public void debugPrint() {
        Node temp = front;
        while (temp.next != null) {
            System.out.print(temp.value + " ");
            temp = temp.next;
        }
        System.out.println();
    }
}