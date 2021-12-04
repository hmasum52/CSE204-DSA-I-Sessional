/**
 * Doubly circular linked list
 */
public class DCLinkedList<T> {
    public static final String DEBUG = "DCLinkedList->";
    public static final int PREV = -1;
    public static final int NEXT = 1;

    /**
     * doubly circular linked list node
     */
    public class ListNode {
        T value;
        ListNode prev;
        ListNode next;

        // Constructor to create a new node
        // next and prev is by default initialized as null
        ListNode(T value) {
            this.value = value;
        }
    }

    private ListNode head;
    private ListNode tail; //for appending in O(1)
    private int length;

    public DCLinkedList() {
        length = 0;
    }

    /**
     * append a new object in O(1)
     */
    public void append(T value) {
        ListNode newNode = new ListNode(value);

        // if the list is empty
        if (head == null) {
            head = newNode;
            head.prev = newNode;
            head.next = newNode;
            tail = head; // head and tail are same
            length++; // increase the length by 1
            
            return;
        }

        // connect tail node and new node
        // link tail-->newNode
        tail.next = newNode;
        // link tail<--newNode
        newNode.prev = tail;

        // set newNode as tail
        tail = newNode;

        // connect new tail node and root
        // to make it circular
        // link newNode-->head
        newNode.next = head;
        // link newNode<--head
        head.prev = newNode;

        // increase the length by 1
        length++;
    }

    /**
     * search a node in O(n) time
     * 
     * make sure you override equals method in {@link T}
     * 
     * @param object to be searched
     * @return resturn a ListNode is found else return null
     */
    public ListNode getListNode(T object) {
        ListNode cur = head;
        while (true) {
            if (cur.value.equals(object))
                return cur;
            cur = cur.next;
            if (cur == head)
                break;
        }
        return null;
    }

    /**
     * insert a node left of the specified node in O(1) time
     * 
     * @param node is the current node after which we will insert the new node
     * @param value object to inserted
     */
    public void insertLeftOf(ListNode node, T value) {
        //make a ListNode from the object
        ListNode newPlayer = new ListNode(value);

        // connect new player with previous player
        newPlayer.prev = node.prev;
        node.prev.next = newPlayer;

        // connect new player with current player
        newPlayer.next = node;
        node.prev = newPlayer;

        //increase the length of the list
        length++;
    }

    /**
     * insert a Player right in O(1) time
     * 
     * @param playerId
     * @param value
     */
    public void insertRightOf(ListNode node, T value) {
        ListNode newPlayer = new ListNode(value);

        // connect new player with next player
        newPlayer.next = node.next;
        node.next.prev = newPlayer;

        // connect new player with current player
        newPlayer.prev = node;
        node.next = newPlayer;

        length++;
    }

    /**
     * 
     * @return the value of 1st inserted or appended node
     */
    public T front() {
        return head.value;
    }

    /**
     * 
     * @return the 1st inserted or appened node in the list
     */
    public ListNode frontNode() {
        return head;
    }

    /**
     * delete a node with the value in O(n) time
     * 
     * @param value to be deleted
     */
    public void delete(T value) {
        ListNode node = getListNode(value); //search the value in O(n) time

        if (node == null)
            throw new RuntimeException("Object doesn't exist");

        System.out.println("delete: " + node.value);

        // make link prev-->next
        node.prev.next = node.next;

        // make linke prev<--next
        node.next.prev = node.prev;

        length--;
    }


    /**
     * delete a node in O(1) time
     * 
     * @param playerId
     */
    public void delete(ListNode node) {
        // make link prev-->next
        node.prev.next = node.next;

        // make link prev<--next
        node.next.prev = node.prev;

        length--;
    }

    public int length() {
        return length;
    }

    public static final int LEFT_TO_RIGHT = 1; // clockwise
    public static final int RIGHT_TO_LEFT = -1; // anti-clockwise

    
    public T next(T object, int direction) {
        if (direction == LEFT_TO_RIGHT) {
            ListNode temp = getListNode(object);
            return temp.next.value;
        } else {
            ListNode temp = getListNode(object);
            return temp.prev.value;
        }
    }

    public ListNode next(ListNode node,int direction) {
        if (direction == NEXT) {
            return node.next;
        } else {
            return node.prev;
        }
    }
}
