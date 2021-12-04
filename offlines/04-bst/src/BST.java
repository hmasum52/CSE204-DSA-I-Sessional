/**
 * binary search tree of integer
 * 
 * height of the tree h = log2(n+1)
 * 
 * It is assumed integers all the items in the tree are distinct, i.e. there is no repetition
 */
public class BST{
    class Node {
        int value;
        Node left;
        Node right;

        public Node(int value) {
            this.value = value;
        }
    }

    private Node root;

    public boolean isEmpty() {
        return root == null;
    }

    public boolean isLeaf(Node node) {
        return node.left == null && node.right == null;
    }
    
    /**
     * 
     * This function inserts a new item in the binary search tree.
     * complexity: O(h), where h is height of the tree
     * 
     * @return true is the value inserted successfully and false if the value
     *         already exist
     */
    public boolean insertItem(int value) {
        //tree is empty
        //so create a root node
        if (isEmpty()) {
            root = new Node(value);
            return true;
        }
        //insert a child
        return insertItem(root, value);
    }

    /**
     * complexity: O(h) , where h is height of the tree
     * 
     * helper recursive method to insert a node
     * 
     * @param root is the parent of a sub-tree
     * @param value is the value to be inserted.
     * 
     * @return true if the value is inserted successfully and false if the value
     *        already exist
     */
    private boolean insertItem(Node root, int value) {
        //expected unique vlaues
        //still we check and ingore the value
        //if it already exist
        if (root.value == value) {
            return false; //already exist
        }
        
        //check is the value is less then parent node
        //if so then search for a place to insert in left sub-tree
        if (value < root.value) {
            //if left child is empty. So insert there
            if (root.left == null) {
                root.left = new Node(value);
                return true;
            }
            //else go to left sub-tree and search a spot
            return insertItem(root.left, value);
        } else { //value is greater than root value. So insert item is right sub-tree

            //check for if right child is empty
            if (root.right == null) {
                //if so then insert as the right child.
                root.right = new Node(value);
                return true;
            }
            //else go to right sub-tree and search for a spot.
            return insertItem(root.right, value);
        }
    }
    

    /**
     * 
     * 
     * This function searches for an item in the binary search tree. If the item,
     * say 52, is found, the function prints “52 has been found”; otherwise the
     * function prints “52 has not been found”.
     * complexity: O(h) , where h is height of the tree
     */
    public void searchItem(int value) {
        if (searchItem(root, value)) {
            System.out.println(value + " has been found");
        } else
            System.out.println(value + " has not been found");
    }

    /**
     * complexity: O(h) , where h is height of the tree
     * 
     * recursive helper method to search a item in the tree
     * 
     * recursively search a value in the tree.
     * 
     * @param root  is the root of sub-tree in recursive calls
     * @param value is the value to be searched
     * @return true if the value is found and false otherwise.
     */
    private boolean searchItem(Node root, int value) {
        //tree is empty or node is a leaf
        if (isEmpty())
            return false;

        //check is the value is matched with this node
        if (root.value == value)
            return true;

        //check is serach item is less then current root value
        //if so then search left sub-tree 
        if (value<root.value)
            return searchItem(root.left, value);

        //else search in right sub-tree
        return searchItem(root.right, value);
    }
    
    /**
     * complexity: O(h) , where h is height of the tree
     * 
     * This function returns the in-order successor of an item in the binary search
     * tree. When there is no successor, it return an invalid number(INT_MIN) to
     * indicate it.
     * 
     * The in-order successor of a node is the node that is processed next (not
     * visited!) in the in-order traversal of the binary search tree.
     * 
     * In other word, in-order successor of a node is the node
     * whose value is minimum among all nodes that are larger than the node.
     * It is the next node in ascending sorted order of the items in the tree.
     * 
     */
    public int getInOrderSuccessor(int value) {
        Node node = findInOrderSuccessor(root, value);
        return node != null ? node.value : Integer.MIN_VALUE;
    }

    /**
     * complexity: O(h) , where h is height of the tree
     * 
     * recursive helper method of getInOrderSuccessor of parameter value
     * 
     * @param root is the root of sub-tree is recursive call
     * @return the predecessor node if found and null otherwise
     */
    private Node findInOrderSuccessor(Node root, int value) {
        if(root == null)
            return null;

        Node successor = null;

        //check is value is found ======================================
        if (root.value == value) {
            // set the value-node as successor though it is not
            // we will return this if the successor is not found in right sub-tree
            // and this will indicate the ancestors that 
            // the value is found but the successor is not found yet.
            successor = root;

            //check is right sub-tree exist.
            //because the successor is the leftmost node in right sub-tree.
            // CASE-1: right sub-tree exist
            if (root.right != null) {

                // track the successor
                // set the root of right sub-tree as successor.
                successor = root.right;

                // successor will be leftmost child of this tree
                // so go to the leftmost child this node
                // if there is no left child then successor will be root of right sub-tree.
                while (successor.left != null) {
                    successor = successor.left;
                }
            }

            //return the successor if found
            //return null if not found
            // return value's node if value is found and successor is not found
            return successor;
        }

        //value is not found yet at this point ================================

        //check if the value may exist is left sub-tree =======================
        if (value < root.value) {
            //call for successor in left sub-tree
            successor = findInOrderSuccessor(root.left, value);

            // check if the value is found but not the successor
            if (successor.value == value) {
                // successor is not found in left sub-tree
                // but the value is found
                // and current node is an ansestor is greater then the value
                // so it is the successor
                successor = root;
            }
                
        } else { 
            //check if the value may exist is right sub-tree ==============
            successor = findInOrderSuccessor(root.right, value);
        }
        
        // value was found but no successor was found.
        // an example of node like this is the last node in in-order traversal.(rightmost node)
        if (root == this.root && successor.value == value)
            successor = null;

        return successor;
    }
    
    /**
     * This function returns the in-order predecessor of an item in the binary
     * search tree. When there is no predecessor, it returns an invalid
     * number(INT_MIN) to indicate it.
     *
     * In-order predecessor of a node is the node whose value is the maximum among
     * all nodes that are smaller than the node. 
     * It is the previous node in ascending sorted order of the items
     */
    public int getInOrderPredecessor(int value) {
        Node node = findInOrderPredecessor(root, value);
        return node != null ? node.value : Integer.MIN_VALUE;
    }

    /**
     * complexity: O(h) , where h is height of the tree
     * 
     * recursive helper method to find in-order predecessor of parameter value
     * 
     * @param root is the root of the full tree(root of sub-tree is recursive call)
     * @return the predecessor node if found and null otherwise
     */
    private Node findInOrderPredecessor(Node root, int value) {

        //base case
        if (root == null)
            return null;

        Node predecessor = null;

        // check is value is found ===========================================
        if (root.value == value) {
            // set the value-node as predecessor though it is not
            // we will return this if the predecessor is not found in right sub-tree
            // and this will indicate the ancestors that the value is found
            // but the predecessor is not found yet.
            predecessor = root;

            // check is left sub-tree is null
            // as predecessor is the rightmost value of left sub-tree
            if (root.left != null) {
                // track the predecessor
                // set the root of left sub-tree as predecessor.
                // as if there is no right child then successor is root of the sub-tree itself
                predecessor = root.left;

                // predecessor will be rightmost child of this right sub-tree
                // so go to the rightmost child of this sub-tree from root
                while (predecessor.right != null) {
                    predecessor = predecessor.right;
                }
            } 

            // return the predecessor if found
            // return null if not found
            // return value's node if value is found and predecessor is not found
            return predecessor;
        }

        // value is not found yet at this point===============

        // check for the value in the left sub-tree ============================
        else if (value < root.value) {
            // call for successor in left sub-tree
            predecessor = findInOrderPredecessor(root.left, value);
        }
        // check the value in in right sub-tree ============================ 
        else {
            predecessor = findInOrderPredecessor(root.right, value);

            //check if the value is found but the predecessor was not found
            if (predecessor.value == value) {
                // predecessor is not found in right sub-tree
                // but the value is found
                // and current root is an ansestor and less than the value
                // so it is the predecessor
                predecessor = root;
            }
        }

        //value was found but no predecessor was found.
        //an example of node like this is the 1st node in in-order traversal
        if (root == this.root && predecessor.value == value)
            predecessor = null;

        return predecessor;
    }

    /**
     * complexity: O(h) , where h is height of the tree
     * 
     * The function will delete an existing item from the binary search tree. tree
     * is re-structured after deletion In case of deletion of a node where both of
     * its children exist, the next largest node(successor) in the tree is used for
     * replacement. If the item is not in the tree, it does nothing.
     */
    public void deleteItem(int value) {
        root = findAndDelete(root, value);
    }


    /**
     * recursive helper method of deleteItem method
     * @param root of the sub-tree in recursive calls
     * @param value to be deleted
     * @return Node to re-structure the tree after deletion
     */
    private Node findAndDelete(Node root, int value) {

        //base case for leaf 
        if (root == null) {
            return null;
        }

        if (root.value == value) {
            // case-1: value-node has one or no children
            // if it is leaf node then simply return a null which is used to disconnect with its parent
            // if it has one child then return it's pointer which is used to connect with the parent.
            if(root.left == null)
                return root.right;
            else if(root.right== null)
                return root.left;

            // case-2: value-node has both left and right children
            // we will search for next max value in right sub-tree
            // we used successor here , but predecessor can also be used.
            
            //track successorRoot
            Node successorRoot = root;
            //track successor
            Node successor = root.right;
            while (successor.left != null) {
                successorRoot = successor;
                successor = successor.left;
            }
            
            //set value-node as successor value
            root.value = successor.value;
            
            // finally delete the successor by disconnecting it
            // from its parent and garbage collector will delete the successor node
            // successor will be leaf node in this case for sure
            if(successorRoot.left == successor) //check if successor it a left child
                successorRoot.left = null;
            else //check if successor is a right child.
                successorRoot.right = null;
            
            //return root which will be connected to its parent node
            return root;
        }


        // check if value-node may exist in left subtree
        if (value < root.value) {
            root.left = findAndDelete(root.left, value);
        } else {
            root.right = findAndDelete(root.right, value);
        }
        
        // return root which will be connected to its parent node
        return root;
    }
    
    /**
     * complexity: O(h) , where h is height of the tree
     * 
     * This function returns the depth of an item in the binary search tree. It is
     * assumed that the root has a depth of 0, the nodes at the next level have a
     * depth of 1 and so on. If the item is not in the tree, it returns an invalid
     * number(INT_MIN) to indicate it
     */
    public int getItemDepth(int value) {
        return findItemDepth(root, value);
    }

    /**
     * complexity: O(h) , where h is height of the tree
     * 
     * recursive helper method of getItemDepth
     * 
     * @return the depth if the value is found and return INT_MIN if the value is
     *         not found
     */
    private int findItemDepth(Node root, int value) {
        //value doesn't exist in the tree
        //so return a invalid number
        //base case for leaf nodes
        if(root == null)
            return Integer.MIN_VALUE;
        
        //value is found
        if (root.value == value) {
            return 0;
        }

        //check if the value is in left sub-tree
        if (value < root.value) {
            int depth = findItemDepth(root.left, value);
            return depth == Integer.MIN_VALUE ? depth : 1 + depth;
        }
        
        //check if the value is right sub-tree
        int depth = findItemDepth(root.right, value);
        return depth == Integer.MIN_VALUE ? depth : 1 + depth;
    }

    /**
     * This function finds and returns the maximum item of the binary search tree.
     * complexity: O(h) , where h is height of the tree.
     * 
     * @return the maximum value if the tree is not empty and returns invalid number
     *         INT_MIN if the tree is empty.
     */
    public int getMaxItem() {
        Node maxNode = root;
        if(maxNode == null)
            return Integer.MIN_VALUE;
        //max value is the rightmost value in the tree
        while (maxNode.right != null) {
            maxNode = maxNode.right;
        }
        return maxNode.value;
    }

    public Node getMax(Node root){
        if(root == null)
            return null;

        // rightmost node is the max node
        while(root.right != null)
            root = root.right;

        return root;
    }
    
    /**
     * This function finds and returns the minimum item of the binary search tree.
     * complexity: O(h) , where h is height of the tree.
     * 
     * @return the minimum value if the tree is not empty and return invalid number
     *         INT_MIN if the tree is empty.
     */
    public int getMinItem() {
        Node minNode = root;
        if (minNode == null)
            return Integer.MIN_VALUE;

        // it is the leftmost value in the tree
        while (minNode.left != null) {
            minNode = minNode.left;
        }
        return minNode.value;
    }

    public Node getMin(Node root){
        if(root == null)
            return null;

        // leftmost node is the min node
        while(root.left != null)
            root = root.left;
            
        return root;
    }
    
    /**
     * 
     * The height of a tree is defined as the maximum depth of any node within the
     * tree.
     * 
     * @return the height of the binary search tree .
     */
    public int getHeight() {
        //tree is empty
        if (root == null)
            return Integer.MIN_VALUE;

        return findHeight(root);
    }
    
    /**
     * complexity: O(n), where n is the number of nodes in tree
     * 
     * recursive helper method to find the height of the tree
     * @param root is the root of sub-tree in recursive calls
     * @return the height of three
     */
    private int findHeight(Node root) {
        int leftH = 0;
        if(root.left !=null)
            leftH = 1 + findHeight(root.left);

        int rightH = 0;
        if(root.right != null){
            rightH = 1 + findHeight(root.right);
        }
    
        return leftH > rightH ? leftH : rightH;
    }
    
    /**
     * complexity: O(n), where n is the number of nodes in tree
     * 
     * 
     * This function prints the in-order traversal of the binary search tree.
     * 
     * in-order traversal : print current node after printing its left sub-tree and
     * before printing its right sub-tree. In short : left->root->right
     */
    public void printInOrder() {
        String seq = getInOrderSequence(root, "->");
        if (seq.equals("")) {
            System.out.println("Tree is empty.");
            return;
        }
        seq = seq.substring(0, seq.lastIndexOf("->"));
        System.out.println(seq); 
    }

    /**
     * complexity: O(n), where n is the number of nodes in tree
     * 
     * helper method of printInOrder to print the values recursively
     * 
     * @param root is root of sub-tree in recursive call
     */
    private String getInOrderSequence(Node root,String separator) {
        if(root == null)
            return "";
        String seq = getInOrderSequence(root.left, separator);
        seq += root.value + separator;
        seq += getInOrderSequence(root.right, separator);

        return seq;
    }
    
    /**
     * complexity: O(n), where n is the number of nodes in tree
     * 
     * This function prints the pre-order traversal of the binary search tree.
     * 
     * pre-order traversal : print the current node 1st. then print its left and
     * right sub-tree. In short: root->left->right
     * 
     */
    public void printPreOrder() {
        String seq = getPreOrderSequence(root, "->");
        if (seq.equals("")) {
            System.out.println("Tree is empty.");
            return;
        }
        seq = seq.substring(0, seq.lastIndexOf("->"));
        System.out.println(seq);
    }


    /**
     * recursive helper method of pre-order traversal
     * @return a string of pre-order traversal sequence
     */
    private String getPreOrderSequence(Node root,String separator) {
        if (root == null)
            return "";
        String seq = root.value + separator;
        seq += getPreOrderSequence(root.left, separator);
        seq += getPreOrderSequence(root.right, separator);
        return seq;
    }
    
    /**
     * complexity: O(n), where n is the number of nodes in tree
     * 
     * This function prints the post-order traversal of the binary search tree.
     * 
     * post-order traversal: print left and right-subtrees 1st then print the
     * current node In short: left->right->root
     */
    public void printPostOrder() {
        String seq = getPostOrderSequence(root, "->");
        if (seq.equals("")) {
            System.out.println("Tree is empty.");
            return;
        }
        seq = seq.substring(0, seq.lastIndexOf("->"));
        System.out.println(seq);
    }

    private String getPostOrderSequence(Node root, String separator) {
        if (root == null)
            return "";
        String seq = getPostOrderSequence(root.left, separator);
        seq += getPostOrderSequence(root.right, separator);
        seq += root.value + separator;

        return seq;
    }

    /**
     * This function returns the current size of the binary search tree. The size of
     * a tree is the number of nodes in the tree.
     * 
     * @return the size of the tree
     * 
     */
    public int getSize() {
        return findSize(root);
    }
    
    /**
     * recursive helper function to get the size 
     * runtime O(n), n is the number of node in the tree
     * 
     * @param root is the current node
     * @return size of the BST
     */
    public int findSize(Node root) {
        if(root == null)
            return 0;
        int size = 1 + findSize(root.left);
        size += findSize(root.right);
        return size;
    }

}