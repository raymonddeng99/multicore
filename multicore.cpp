#include "multicore.h"
#include <atomic>

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