#ifndef THREADREADWRITELOCK_H
#define THREADREADWRITELOCK_H

class ThreadReadWriteLock
{
	public:
		ThreadReadWriteLock();
		~ThreadReadWriteLock();

		bool SetReadLock();
		bool SetWriteLock();
		void UnLock();

	private:
		pthread_rwlock_t readWriteLock;
};

#endif
