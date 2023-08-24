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

#endif