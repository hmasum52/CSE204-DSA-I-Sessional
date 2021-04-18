public class Player {
    private int id;
    private int reflexTime;

    public Player(int id, int reflexTime) {
        this.id = id;
        this.reflexTime = reflexTime;
    }

    public int getId() {
        return id;
    }

    public int getReflexTime() {
        return reflexTime;
    }

    @Override
    public String toString() {
        return id + ":" + reflexTime;
    }
}
