//строгая мама запрещает общаться сыну с доброй бабушкой
struct Granny {
    private:
    int x;
    friend struct Son;
};
struct Mom : private Granny {
    int y;
};
struct Son : Mom {
    int z;
    void foo() {
        x++;//CE
    }
};
