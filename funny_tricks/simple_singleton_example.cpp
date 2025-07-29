struct Singleton{
    private:
    static Singleton* ptr;
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    public:
    static Singleton& getObject() {
        if (ptr == nullptr) {
            ptr = new Singleton();
        }
        return *ptr;
    }
    ~Singleton() {
        delete ptr;
        ptr = nullptr;
    }
};  
