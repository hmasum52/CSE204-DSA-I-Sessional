
public class PillowGame {
    public static final String DEBUG = "PillowGame->";
    /**
     * 1 for direction i --> i+1 (clockwise)
     * and -1 for direction i <-- i+1(anti clockwise)
     * 
     * @param args
     */
    private int direction;
    private boolean isGameRunning = false;
    private DCLinkedList<Player> list;
    /**
     * ListNode to track the the current pillow holder of the game
     */
    private DCLinkedList<Player>.ListNode currentPlayerNode;
    /**
     * time when the current player started holding the pillow
     */
    private int currentPlayerStartTime;
    /**
     * Expected time when the current player will pass the pillow to the next player
     * this is expected becuase a player can eliminated at any moment if the music stops
     */
    private int currentPlayerExpectedFinishTime;
    //assign a player id when a player joins the game
    private int playerNumber;

    public PillowGame() {
        direction = 1; // set direction i-->i+1(clockwise)
        list = new DCLinkedList<>();
        playerNumber = 1;
    }

    /*
     * add players at the start of the game
     */
    public void addPlayersToTheGame(int[] playerReflexTimeList) {

        // adding each player at O(1) time
        for (Integer reflexTime : playerReflexTimeList) {
            list.append(new Player(playerNumber++, reflexTime));
        }

        if (currentPlayerNode == null) {
            currentPlayerNode = list.frontNode();
            currentPlayerStartTime = 0;
            currentPlayerExpectedFinishTime = currentPlayerNode.value.getReflexTime();
        }

       // System.out.println(DEBUG + "addPlayersToTheGame(): total players: " + list.length());
    }

    /**
     * this method should be called after adding players to the game
     */
    public void startGame() {
        isGameRunning = true;

        //check if any player is added to the game
        //if not through a runtime exception
        if (currentPlayerNode != null) {
           // System.out.println(DEBUG+"->startGame(): Starting game with player: " + currentPlayerNode.value.getId());
        } else {
            throw new RuntimeException("Can't start the game as no player is added to game yet");
 
        }     
    }

 
    public void printPillowHolderAtTime(int time) {
        if (!isGameRunning)
            return;

        if (time == 0) {
            System.out.println("t=0. Game has not started yet");
            return;
        }

        refreshAt(time);
        Player player = currentPlayerNode.value;
        System.out.println("Player " + player.getId() + " is holding the pillow at t=" + time);

        //this will need if1 there is only one player started playing the game
        if (list.length() == 1) {
            finishGame(time);
        }
    }

    /**
     * determine which player is currently holding the pillow
     * @param time is the instantaneous time
     */
    private void refreshAt(int time) {

        while (!(time >= currentPlayerStartTime && time <= currentPlayerExpectedFinishTime)) {
            if (direction == 1) {
               // System.out.println(DEBUG+"->refresh():"+direction+" at time: "+time);
                Player player = (Player) currentPlayerNode.value;
                int reflexTime = player.getReflexTime();
                // System.out.println("Player: "+pillowHolderId+" reflexTime: "+reflexTime);
                currentPlayerStartTime += reflexTime;

                currentPlayerNode = currentPlayerNode.next;
               // System.out.println(DEBUG+"refresh(): Next Player: " + currentPlayerNode.value.getId());

                reflexTime = currentPlayerNode.value.getReflexTime();
                currentPlayerExpectedFinishTime = currentPlayerStartTime + reflexTime;
            } else {
                Player player = (Player) currentPlayerNode.value;
                int reflexTime = player.getReflexTime();
                // System.out.println("Player: "+pillowHolderId+" reflexTime: "+reflexTime);
                currentPlayerStartTime += reflexTime;

                currentPlayerNode = currentPlayerNode.prev;
                //System.out.println("Next Player: " + currentPlayerNode.value.getId());

                reflexTime = currentPlayerNode.value.getReflexTime();
                currentPlayerExpectedFinishTime = currentPlayerStartTime + reflexTime;
            }
        }

    }

    public void insertPlayerAt(int time, int reflexTime) {
        if (!isGameRunning)
            return;

        refreshAt(time);
        if (direction == 1)
            list.insertLeftOf(currentPlayerNode, new Player(playerNumber++, reflexTime));
        else
            list.insertRightOf(currentPlayerNode, new Player(playerNumber++, reflexTime));
    }

    public void eliminatePlayerAtTime(int time) {
        if (!isGameRunning)
            return;

        DCLinkedList<Player>.ListNode nextPlayerNode;
        if (direction == 1) {
            nextPlayerNode = currentPlayerNode.next;
        } else
            nextPlayerNode = currentPlayerNode.prev;

        Player removedPlayer = (Player) currentPlayerNode.value;
    
        list.delete(currentPlayerNode);

        System.out.println("Player " + removedPlayer.getId() + " has been eliminated at t=" + time);

        currentPlayerNode = nextPlayerNode;

        currentPlayerStartTime = time;
        currentPlayerExpectedFinishTime = currentPlayerStartTime + nextPlayerNode.value.getReflexTime();

        if (list.length() == 1) {
            finishGame(time);
        }

    }

    public void reversePillowDirection(int time) {
        if (!isGameRunning)
            return;

        refreshAt(time);
        direction *= -1;
    }

    public void printActivePlayers() {
        if (!isGameRunning)
            return;

        //list.printPlayers(pillowHolderId, direction);
    }

    public void finishGame(int time) {
        if (!isGameRunning)
            return;

        refreshAt(time);
        if (list.length() > 1) {
            System.out.print("Gamer over: Player " + currentPlayerNode.value.getId() + " is holding the pillow at t="
                    + time + ", ");
            System.out.print("pillow passing sequence = Player ");
            int currentPlayerId = currentPlayerNode.value.getId();
            DCLinkedList<Player>.ListNode node = currentPlayerNode;
            int cnt = 1;
            while (true) {
                if(cnt == list.length())
                    System.out.println(node.value.getId());
                else
                    System.out.print(node.value.getId() + ", ");

                node = list.next(node, direction);
                if (node.value.getId() == currentPlayerId)
                    break;
                cnt++;
            }
        } else {
            System.out.println("Game over: Player " + currentPlayerNode.value.getId() + " wins!!");
        }
        isGameRunning = false;
        playerNumber = 1;
    }

}
