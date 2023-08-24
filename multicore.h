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

#endif