#ifndef multicoreH
#define multicoreH

struct TASLock {
	void lock();
	void unlock();
}

struct TTasLock {
	void lock();
	void unlock();
}

struct Backoff {
	int minDelay, maxDelay;
	int limit;
	Backoff(int min, int max);
	vodi backoff();
}

class BackoffLock {
public:
	void lock();
	void unlock();
private:
	std::atomic<bool> lock_stream;
	int MIN_DELAY;
	int MAX_DELAY;
}

class ALock {
public:
    ALock(int capacity);
    void lock();
    void unlock();

private:
    std::atomic<int> tail;
    std::vector<bool> flag;
    int size;
    thread_local int mySlotIndex;
};

class MCSLock {
public:
    MCSLock();
    void Lock();
    void Unlock();

private:
    struct Node {
        bool locked = false;
        Node* next = nullptr;
    };
    alignas(64) std::atomic<Node*> tail_;
};

#endif