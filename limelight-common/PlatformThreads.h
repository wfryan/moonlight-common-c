#pragma once

#include "Platform.h"

typedef void (*ThreadEntry)(void *context);

#if defined(LC_WINDOWS) || defined(LC_WINDOWS_PHONE)
typedef struct _PLT_THREAD {
	HANDLE handle;
	int cancelled;
} PLT_THREAD;
typedef HANDLE PLT_MUTEX;
typedef HANDLE PLT_EVENT;
#elif defined (LC_POSIX)
typedef pthread_t PLT_THREAD;
typedef pthread_mutex_t PLT_MUTEX;
typedef struct _PLT_EVENT {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int signalled;
} PLT_EVENT;
#else
#error Unsupported platform
#endif

int PltCreateMutex(PLT_MUTEX *mutex);
void PltDeleteMutex(PLT_MUTEX *mutex);
void PltLockMutex(PLT_MUTEX *mutex);
void PltUnlockMutex(PLT_MUTEX *mutex);

int PltCreateThread(ThreadEntry entry, void* context, PLT_THREAD *thread);
void PltCloseThread(PLT_THREAD *thread);
void PltInterruptThread(PLT_THREAD *thread);
int PltIsThreadInterrupted(PLT_THREAD *thread);
void PltJoinThread(PLT_THREAD *thread);

int PltCreateEvent(PLT_EVENT *event);
void PltCloseEvent(PLT_EVENT *event);
void PltSetEvent(PLT_EVENT *event);
void PltClearEvent(PLT_EVENT *event);
int PltWaitForEvent(PLT_EVENT *event);

#define PLT_WAIT_SUCCESS 0
#define PLT_WAIT_INTERRUPTED 1

int PltSleepMs(int ms);