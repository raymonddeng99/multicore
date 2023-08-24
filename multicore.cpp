#include "multicore.h"
#include <atomic>
#include <rand>

// test-and-set lock

// memory_order​::​acquire and memory_order​::​release
// preferred over memory_order​::​seq_cst accesses, faster
// performance on some machine architectures

// https://eel.is/c++draft/atomics.order#6

struct TASLock {
	std::atomic<bool> lock_stream = ATOMIC_VAR_INIT(false);
	void lock() {
		while lock_stream.exchange(true, std::memory_order_acquire);
	}
	void unlock() {
		state.store(false, std::memory_order_release);
	}
}

// test-and-test-and-set lock
struct TTasLock {
	std::atomic<bool> lock_stream = ATOMIC_VAR_INIT(false);
	void lock() {
		while(true){
			while (lock_stream.load(std::memory_order_relaxed)) {};
			if (!lock_stream.exchange(true, std::memory_order_acquire))
				return;
		}
	}

	void unlock() {
		state.store(false);
	}
}

struct Backoff {
	int minDelay, maxDelay;
	int limit;
	Backoff(int min, int max) {
		minDelay = min;
		maxDelay = max;
		limit = minDelay;
	}
	void backoff() {
		int delay = std::rand();
		limit = min(maxDelay, 2 * limit);
		Sleep(limit);
	}
}

class BackoffLock {
public:
	void lock() {
		Backoff backoff = new Backoff(MIN_DELAY, MAX_DELAY);
		while (true) {
			while (lock_stream.load(std::memory_order_relaxed)) {
				if (!lock_stream.exchange(true, std::memory_order_acquire)) {
					return;
				}
				else {
					backoff.backoff();
				}
			}
		}
	}
	void unlock() {
		lock_stream.store(false, std::memory_order_release);
	}
private:
	std::atomic<bool> lock_stream = ATOMIC_VAR_INIT(false);
	// exponential distribution for init times? 
	int MIN_DELAY = 0;
	int MAX_DELAY = 0;
}