class TempScore {
private:
    static int score;
public:
    static void increment_score() {
        score++;
    }
    static int get_score() {
        return score;
    }
};
int TempScore::score = 0;