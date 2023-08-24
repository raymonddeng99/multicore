#include "multicore.h"
#include <atomic>

// test-and-set lock
struct TASLock {
	atomic<bool> lock_stream = ATOMIC_VAR_INIT(false);
	void lock() {
		while lock_stream.exchange(true);
	}
	void unlock() {
		state.store(false);
	}
}