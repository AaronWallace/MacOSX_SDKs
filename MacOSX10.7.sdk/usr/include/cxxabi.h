//===--------------------------- cxxabi.h ---------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef __CXXABI_H
#define __CXXABI_H 

/*
 * This header provides the interface to the C++ ABI as defined at:
 *       http://www.codesourcery.com/cxx-abi/
 */

#include <stddef.h>
#include <stdint.h>

namespace std {
	class type_info; // forward declaration
}


// runtime routines use C calling conventions, but are in __cxxabiv1 namespace
namespace __cxxabiv1 {  
  extern "C"  {

// 2.4.2 Allocating the Exception Object
extern void * __cxa_allocate_exception(size_t thrown_size) throw();
extern void __cxa_free_exception(void * thrown_exception) throw();

// 2.4.3 Throwing the Exception Object
extern void __cxa_throw(void * thrown_exception, struct std::type_info * tinfo, 
                        void (*dest)(void *));

// 2.5.3 Exception Handlers
extern void * __cxa_get_exception_ptr(void * exceptionObject) throw();
extern void * __cxa_begin_catch(void * exceptionObject) throw();
extern void __cxa_end_catch();
extern std::type_info * __cxa_current_exception_type();

// 2.5.4 Rethrowing Exceptions
extern void __cxa_rethrow();



// 2.6 Auxiliary Runtime APIs
extern void __cxa_bad_cast();
extern void __cxa_bad_typeid();



// 3.2.6 Pure Virtual Function API
extern void __cxa_pure_virtual(void);

// 3.3.2 One-time Construction API
extern int  __cxa_guard_acquire(uint64_t*);
extern void __cxa_guard_release(uint64_t*);
extern void __cxa_guard_abort(uint64_t*);

// 3.3.3 Array Construction and Destruction API
extern void* __cxa_vec_new(size_t element_count, 
						   size_t element_size, 
                           size_t padding_size, 
						   void (*constructor)(void*),
						   void (*destructor)(void*) );

extern void* __cxa_vec_new2(size_t element_count,
 						    size_t element_size, 
                            size_t padding_size,
						    void  (*constructor)(void*),
						    void  (*destructor)(void*),
                            void* (*alloc)(size_t), 
                            void  (*dealloc)(void*) );

extern void* __cxa_vec_new3(size_t element_count,
 						    size_t element_size, 
                            size_t padding_size,
						    void  (*constructor)(void*),
						    void  (*destructor)(void*),
                            void* (*alloc)(size_t), 
                            void  (*dealloc)(void*, size_t) );
  
extern void __cxa_vec_ctor(void*  array_address, 
                           size_t element_count,
                           size_t element_size, 
						   void (*constructor)(void*),
						   void (*destructor)(void*) );


extern void __cxa_vec_dtor(void*  array_address, 
                           size_t element_count,
						   size_t element_size, 
						   void (*destructor)(void*) );


extern void __cxa_vec_cleanup(void* array_address, 
                             size_t element_count,
                             size_t element_size, 
						     void  (*destructor)(void*) );


extern void __cxa_vec_delete(void*  array_address, 
                             size_t element_size, 
                             size_t padding_size, 
						     void  (*destructor)(void*) );


extern void __cxa_vec_delete2(void* array_address, 
                             size_t element_size, 
                             size_t padding_size, 
						     void  (*destructor)(void*),
                             void  (*dealloc)(void*) );
  

extern void __cxa_vec_delete3(void* __array_address, 
                             size_t element_size, 
                             size_t padding_size, 
						     void  (*destructor)(void*),
							 void  (*dealloc) (void*, size_t));


extern void __cxa_vec_cctor(void*  dest_array, 
							void*  src_array, 
							size_t element_count, 
							size_t element_size, 
							void  (*constructor) (void*, void*), 
							void  (*destructor)(void*) );


// 3.3.5.3 Runtime API
extern int __cxa_atexit(void (*f)(void*), void* p, void* d);
extern int __cxa_finalize(void*);


// 3.4 Demangler API
extern char* __cxa_demangle(const char* mangled_name, 
							char*       output_buffer,
							size_t*     length, 
							int*        status);

  } // extern "C"
} // namespace __cxxabiv1
namespace abi = __cxxabiv1;





// Below are Apple extensions to support implementing C++ ABI in a seperate dylib
namespace __cxxabiapple {  
  extern "C"  {

// Apple additions to support multiple STL stacks that share common 
// terminate, unexpected, and new handlers
extern void (*__cxa_terminate_handler)();
extern void (*__cxa_unexpected_handler)();
extern void (*__cxa_new_handler)();

// Apple additions to support C++ 0x exception_ptr class
// These are primitives to wrap a smart pointer around an exception object
extern void * __cxa_current_primary_exception() throw();
extern void __cxa_rethrow_primary_exception(void* primary_exception);
extern void __cxa_increment_exception_refcount(void* primary_exception) throw();
extern void __cxa_decrement_exception_refcount(void* primary_exception) throw();

// Apple addition to support std::uncaught_exception()
extern bool __cxa_uncaught_exception() throw();

  } // extern "C"
} // namespace __cxxabiv1



#endif // __CXXABI_H 
