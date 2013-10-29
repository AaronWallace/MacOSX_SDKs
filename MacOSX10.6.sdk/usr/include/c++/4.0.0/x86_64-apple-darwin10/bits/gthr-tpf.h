/* Threads compatibility routines for libgcc2 and libobjc.
   Compile this one with gcc.
   Copyright (C) 2004 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */


/* TPF needs its own version of gthr-*.h because TPF always links to 
   the thread library.  However, for performance reasons we still do not
   want to issue thread api calls unless a check is made to see that we
   are running as a thread.  */

#ifndef _GLIBCXX_GCC_GTHR_TPF_H
#define _GLIBCXX_GCC_GTHR_TPF_H

/* POSIX threads specific definitions.
   Easy, since the interface is just one-to-one mapping.  */

#define __GTHREADS 1

/* Some implementations of <pthread.h> require this to be defined.  */
#ifndef _REENTRANT
#define _REENTRANT 1
#endif

#include <pthread.h>
#include <unistd.h>

typedef pthread_key_t __gthread_key_t;
typedef pthread_once_t __gthread_once_t;
typedef pthread_mutex_t __gthread_mutex_t;
typedef pthread_mutex_t __gthread_recursive_mutex_t;

#if defined(PTHREAD_RECURSIVE_MUTEX_INITIALIZER)
#define __GTHREAD_RECURSIVE_MUTEX_INIT PTHREAD_RECURSIVE_MUTEX_INITIALIZER
#elif defined(PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP)
#define __GTHREAD_RECURSIVE_MUTEX_INIT PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP
#endif

#define __GTHREAD_MUTEX_INIT PTHREAD_MUTEX_INITIALIZER
#define __GTHREAD_ONCE_INIT PTHREAD_ONCE_INIT

#define NOTATHREAD   00
#define ECBBASEPTR (unsigned long int) *(unsigned int *)0x00000514u
#define ECBPG2PTR  ECBBASEPTR + 0x1000
#define CE2THRCPTR *((unsigned char *)(ECBPG2PTR + 208))
#define __tpf_pthread_active() (CE2THRCPTR != NOTATHREAD)

#if __GXX_WEAK__ && _GLIBCXX_GTHREAD_USE_WEAK

#pragma weak pthread_once
#pragma weak pthread_key_create
#pragma weak pthread_key_delete
#pragma weak pthread_getspecific
#pragma weak pthread_setspecific
#pragma weak pthread_create

#pragma weak pthread_mutex_lock
#pragma weak pthread_mutex_trylock
#pragma weak pthread_mutex_unlock

#endif /* __GXX_WEAK__ */

static inline int
__gthread_active_p (void)
{
  return 1;
}

static inline int
__gthread_once (__gthread_once_t *once, void (*func) (void))
{
  if (__tpf_pthread_active ())
    return pthread_once (once, func);
  else
    return -1;
}

static inline int
__gthread_key_create (__gthread_key_t *key, void (*dtor) (void *))
{
  if (__tpf_pthread_active ())
    return pthread_key_create (key, dtor);
  else
    return -1;
}

static inline int
__gthread_key_delete (__gthread_key_t key)
{
  if (__tpf_pthread_active ())
    return pthread_key_delete (key);
  else
    return -1;
}

static inline void *
__gthread_getspecific (__gthread_key_t key)
{
  if (__tpf_pthread_active ())
    return pthread_getspecific (key);
  else
    return NULL;
}

static inline int
__gthread_setspecific (__gthread_key_t key, const void *ptr)
{
  if (__tpf_pthread_active ())
    return pthread_setspecific (key, ptr);
  else
    return -1;
}

static inline int
__gthread_mutex_lock (__gthread_mutex_t *mutex)
{
  if (__tpf_pthread_active ())
    return pthread_mutex_lock (mutex);
  else
    return 0;
}

static inline int
__gthread_mutex_trylock (__gthread_mutex_t *mutex)
{
  if (__tpf_pthread_active ())
    return pthread_mutex_trylock (mutex);
  else
    return 0;
}

static inline int
__gthread_mutex_unlock (__gthread_mutex_t *mutex)
{
  if (__tpf_pthread_active ())
    return pthread_mutex_unlock (mutex);
  else
    return 0;
}

static inline int
__gthread_recursive_mutex_lock (__gthread_recursive_mutex_t *mutex)
{
  if (__tpf_pthread_active ())
    return __gthread_mutex_lock (mutex);
  else
    return 0;
}

static inline int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *mutex)
{
  if (__tpf_pthread_active ())
    return __gthread_mutex_trylock (mutex);
  else
    return 0;
}

static inline int
__gthread_recursive_mutex_unlock (__gthread_recursive_mutex_t *mutex)
{
  if (__tpf_pthread_active ())
    return __gthread_mutex_unlock (mutex);
  else
    return 0;
}

#endif /* ! _GLIBCXX_GCC_GTHR_TPF_H */
