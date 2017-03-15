/*
 Program Name: SharedPtr.hpp
 Author: Kunal Zantye
 Program Intent: Implement a non-intrusive, thread-safe, exception-safe, reference-counting smart pointer
 Input Data: Test File
 Output Data: Console
 Compile Note: Use g++ to compile.
 */


#ifndef SHARE_PTR
#define SHARE_PTR

#include <iostream>
#include <assert.h>
#include <mutex>
#include <atomic>
#include <typeinfo>
#include <cxxabi.h>
#include <type_traits>
#include <pthread.h>
#include <stdlib.h>

namespace cs540{

	std::mutex __mutex;

	class Reference
	{
	public:
		int ref_counter;
		Reference(){
			ref_counter=0;
		}
		virtual ~Reference(){}
		
	};
	template <typename T>
	class Ref_count: public Reference
	{
	public:
		T* orignal_ptr;
		//Ref_count():orignal_ptr(nullptr){}
		Ref_count(T* ptr): orignal_ptr(ptr){}
		~Ref_count(){
			delete orignal_ptr;
			orignal_ptr=NULL;
		}
		
	};

	template <typename T> class SharedPtr{
		


		public:
			T *data;
			Reference *ref;
			//std::atomic<u_int>* ref_counter;
			//int *ref_counter;

			//Constructs a smart pointer that points to null.
			SharedPtr(): data(nullptr), ref(nullptr){}

			//Constructs a smart pointer that points to the given object. The reference count is initialized to one.

			template <typename U> explicit SharedPtr(U *obj)
			{
				ref= new Ref_count<U>(obj);
				data = obj;
				//ref_counter = new std::atomic<u_int>();
				//ref_counter=new int;
				__mutex.lock();
				++(ref->ref_counter);
				__mutex.unlock();
				//std::cout<< "Counter"<<(*ref_counter)<<"\n";
			}

			//If p is not null, then reference count of the managed object is incremented. 
			//If U * is not implicitly convertible to T *, use of the second constructor will result in a compile-time error when the compiler attempts to instantiate the member template.
			//copy Ctor

			SharedPtr(const SharedPtr &p){
				ref = p.ref;
				//ref->ref_counter=p.ref->ref_counter;
				if (ref != nullptr && ref->ref_counter >0){
		            __mutex.lock();
		            ++(ref->ref_counter);
		            __mutex.unlock();
					this->data = static_cast<T*>(p.data);
				}
			}
			//templated Copy Constructor,
			template <typename U> 
			SharedPtr(const SharedPtr<U> &p){
					ref = p.ref;
				//ref->ref_counter=p.ref->ref_counter;
				if (ref != nullptr ){//&& ref->ref_counter>0){
		            __mutex.lock();
		            ++(ref->ref_counter);
		            __mutex.unlock();
					this->data = static_cast<T*>(p.data);
				}
			
			}

			//Move constructor 1
			SharedPtr(SharedPtr &&p):data(p.data), ref(p.ref){}
			//Move constructor 2
			template <typename U> 
			SharedPtr(SharedPtr<U> &&p):data(p.data), ref(p.ref){}
			
			
			/*Copy assignment. Must handle self assignment. Decrement reference count of current object, if any, and increment reference count of the given object. 
			If U * is not implicitly convertible to T *, this will result in a syntax error. 
			Note that both the normal assignment operator and a member template assignment operator must be provided for proper operation.
			*/

			SharedPtr &operator=(const SharedPtr &obj){
				if (this == &obj)
					return *this;
				__mutex.lock();
				if (ref != nullptr && --(ref->ref_counter) == 0){//check
	            delete ref;
	            //delete ref_counter;
		        }
		        __mutex.unlock();
				ref = obj.ref;
				//ref->ref_counter=obj.ref->ref_counter;
				//if (ref->ref_counter >0){ 
				if(ref!=nullptr){
					__mutex.lock();
					++(ref->ref_counter);
					__mutex.unlock();
				}
				data=obj.data;
		        return *this;

			}

			
			template <typename U>
			SharedPtr<T> &operator=(const SharedPtr<U> &obj){
				if (this == (SharedPtr<T>*)&obj)
					return *this;
				__mutex.lock();
				if (ref != nullptr && --(ref->ref_counter) == 0){//check
	            delete ref;
	            //delete ref_counter;
		        }
		        __mutex.unlock();
				ref = obj.ref;
				//ref->ref_counter=obj.ref->ref_counter;
				//if (ref->ref_counter >0){ 
				if(ref!=nullptr){
					__mutex.lock();
					++(ref->ref_counter);
					__mutex.unlock();
				}
				data=obj.data;
		        return *this;
			}


			/*Move assignment. After this operation, p must be null. 
			The reference count associated with the object (if p is not null before the operation) will remain the same after this operation.
			This must compile and run correctly if U * is implicitly convertible to T *, otherwise, it must be a syntax error.*/

			SharedPtr &operator=(SharedPtr &&p){
				__mutex.lock();
				if (ref != nullptr && --(ref->ref_counter) == 0){//check
	            delete ref;
	            //delete ref_counter;
		        }
		        __mutex.unlock();
				this->ref = p.ref;
				this->data = p.data;
		        return * this;
			}


			template <typename U> 
			SharedPtr &operator=(SharedPtr<U> &&p){
			__mutex.lock();
			if (ref != nullptr && --(ref->ref_counter) == 0){//check
	            delete ref;
	            //delete ref_counter;
		        }
		    __mutex.unlock();
				this->ref = p.ref;
				this->data = p.data;
		        return * this;
			}
				
			

			//The smart pointer is set to point to the null pointer. The reference count for the currently pointed to object, if any, is decremented.
			void reset(){
				__mutex.lock();
				if (ref != nullptr && --(ref->ref_counter) == 0){//check
	            delete ref;
	            //delete ref_counter;
		        }
		        __mutex.unlock();
		        ref=nullptr;
		        data=nullptr;
		        //ref_counter=NULL;
		        

			}
			
			/*Replace owned resource with another pointer. If the owned resource has no other references, it is deleted. 
			If p has been associated with some other smart pointer, the behavior is undefined.*/
			template <typename U> void reset(U *p){

				if (ref != nullptr)
				{
					__mutex.lock();
					if(--(ref->ref_counter) == 0) {//check
		            delete ref;
		            //delete ref_counter;
			        }
			        __mutex.unlock();
			        ref=nullptr;
			        data=nullptr;
			        //ref_counter=NULL;
			    }
			    this->ref= new Ref_count<U>(p);
				this->data = static_cast<U*>(p);
				//this->ref_counter = new std::atomic<u_int>();
				//this->ref_counter = new int;
				__mutex.lock();
				++(ref->ref_counter);
				__mutex.unlock();
			}

			explicit operator bool() const{
				return (data != nullptr);

			}

			T *get() const{
				return data;
			}

			T &operator*() const{
				return *data;
			}

			T *operator->() const{
				return data;
			}

			///Decrement reference count of managed object. If the reference count is zero, delete the object.
			~SharedPtr(){
				__mutex.lock();
				//std::cout<<"Destructor Called"<<(*ref_counter)<<"\n";
				if (this->ref != nullptr && --(ref->ref_counter) == 0)//check
				{
				//std::cout<<"\nDestructor Called\n";//<<(*ref_counter)<<"\n";
	            delete ref;
		        }
		        __mutex.unlock();
			}


	};
//Returns true if the two smart pointers point to the same object or if they are both null. Note that implicit conversions may be applied.
	template <typename T1, typename T2>
	bool operator==(const SharedPtr<T1> &sp1, const SharedPtr<T2> &sp2)
	{
		if (sp1 == nullptr && sp2 == nullptr)
			return true;
		else
			return (sp1.data == sp2.data);
	}


	//Compare the SharedPtr against nullptr.
		template <typename T>
	bool operator==(const SharedPtr<T> &sp1, std::nullptr_t sp2)
	{
		if (sp2 == nullptr)
			return (! sp1);
		
	}

	template <typename T>
	bool operator==(std::nullptr_t sp1, const SharedPtr<T> &sp2)
	{
		if (sp1 == nullptr)
			return(! sp2);

	}

	//True if the SharedPtrs point to different objects, or one points to null while the other does not.
	template <typename T1, typename T2>
	bool operator!=(const SharedPtr<T1>&sp1, const SharedPtr<T2> &sp2)
	{
		return(!(sp1 == sp2));
	}

	//Compare the SharedPtr against nullptr.
	template <typename T>
	bool operator!=(const SharedPtr<T> &sp1, std::nullptr_t sp2)
	{
		return(!(sp1 == sp2));
	}
	template <typename T>
	bool operator!=(std::nullptr_t sp1, const SharedPtr<T> &sp2)
	{
		return(!(sp1 == sp2));
	}


	//Convert sp by using static_cast to cast the contained pointer. 
	//It will result in a syntax error if static_cast cannot be applied to the relevant types.
	template <typename T, typename U>
	SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp){
		SharedPtr<T> static_sp(sp);
		static_sp.data = static_cast<T*>(sp.data);
		return static_sp;
	}


	//Convert sp by using dynamic_cast to cast the contained pointer. 
	//It will result in a syntax error if dynamic_cast cannot be applied to the relevant types, and will result in a smart pointer to null if the dynamic type of the pointer in sp is not T *.
	template <typename T, typename U>
	SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp)
	{
		SharedPtr<T> dynamic_sp(sp);
		dynamic_sp.data = dynamic_cast<T*>(sp.data);
		return dynamic_sp;
	}

}

#endif