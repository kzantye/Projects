/*
 Program Name: Map.hpp
 Author: Kunal Zantye
 Program Intent: Implement a Map Container in C++
 Input Data: Test File
 Output Data: Console
 Compile Note: Use g++ to compile.
 */
#include<iostream>
#include<initializer_list>
#include<stdexcept>
#include<assert.h>
#include<limits>
#include<utility>


#define MAX_HEIGHT 32
namespace cs540{

#ifndef MAP_H
#define MAP_H

	template <typename Key_T , typename Mapped_T>
	class SkipList;
		template <typename Key_T , typename Mapped_T>
	class Map;

	template <typename Key_T , typename Mapped_T>
	class SNode{
		private:
			SNode *next[MAX_HEIGHT+1];
			SNode *prev[MAX_HEIGHT+1];
			std::pair < const Key_T, Mapped_T> ValueType;
			friend class SkipList<Key_T,Mapped_T>;
			friend class Map<Key_T,Mapped_T>;
		public:
		
		SNode(){}

		SNode(int max, std::pair < const Key_T, Mapped_T> temp) : ValueType(temp){
			int i;
			int height=max+1;
			for (i = 1; i <= MAX_HEIGHT; i++) {
				next[i] = NULL;
				prev[i] = NULL;
			}
		}

		~SNode(){}
	};

	//Class for SkipList 
	template <typename Key_T , typename Mapped_T>
	class SkipList{
		private:
			SNode<Key_T,Mapped_T> *head;
			SNode<Key_T,Mapped_T> *tail;
			std:: size_t size;
			int level;
			friend class Map<Key_T,Mapped_T>;

		protected:
    		int rand_Level() {
        	int lvl = 1;
        	double p = 0.5;
        	while ( (rand() / double(RAND_MAX))< p && level < MAX_HEIGHT ) {
            	lvl++;
        		}
        	return lvl;
    		}
		public:

		SkipList(){	}


		void printList() {

		std::cout<<"Printing\n";
		//std::cout<<head->next[1]->ValueType.first<<"\t"<<head->next[1]->ValueType.second<<"\n";
		SNode<Key_T,Mapped_T> *trav = head->next[1];
		
		while (trav && trav != tail) {
				std::cout<<trav->ValueType.first<<"[ "<< trav->ValueType.second<<"]->\n";
				trav = trav->next[1];
			}
		}
		
		size_t get_size(void) const{
			return size;
		}

		bool is_empty() const{
		if(size == 0)
			return true;
		return false;
		}

		SNode<Key_T,Mapped_T> *update[MAX_HEIGHT + 1];
		

		SNode<Key_T,Mapped_T>* Search_key(const Key_T & keypair)
		{
			
			int i;
			SNode<Key_T,Mapped_T> *temp_node = head;
			
			for (i = level; i >= 1; i--) {
				while (temp_node->next[i]->ValueType.first < keypair)
					{
					
						temp_node = temp_node->next[i];}
				update[i] = temp_node;
			}
			temp_node = temp_node->next[1];
			if (keypair == temp_node->ValueType.first) {
		
				return temp_node;
				
			}
			else
				return NULL;

		}//find



		std::pair<SNode<Key_T,Mapped_T>*,bool> insert(std::pair<const Key_T, Mapped_T> keypair){
			SNode<Key_T, Mapped_T> *temp[MAX_HEIGHT];
			SNode<Key_T, Mapped_T> *insert_node = this->head;
			int i, newlevel;
		
			for (i = this->level; i >= 1; i--) {
				while (insert_node->next[i] && insert_node->next[i]->ValueType.first < keypair.first)
					insert_node = insert_node->next[i];
				temp[i] = insert_node;
			}
		
			if (insert_node->next[1] && keypair.first == insert_node->next[1]->ValueType.first) {
				return std::make_pair(insert_node, true);
			}
			else {
				newlevel = this->rand_Level();
				if (newlevel > this->level) {
					for (i = this->level + 1; i <= newlevel; i++) {
						temp[i] = this->head;
					}
					this->level = newlevel;
				}
				insert_node = new SNode<Key_T,Mapped_T>(newlevel,keypair);
				
				for (i = 1; i <= newlevel; i++) {
					insert_node->next[i] = temp[i]->next[i];
					temp[i]->next[i]->prev[i] = insert_node;
					temp[i]->next[i] = insert_node;
					insert_node->prev[i] = temp[i];
				}
				this->size++;
				//this->printList();
				return std::make_pair(insert_node, false);
			}
		}

		void remove(const Key_T & keypair)
		{
			
			int i;
			SNode<Key_T,Mapped_T> *temp_node=Search_key(keypair);
			if(temp_node)	
			{
				for ( i = 1; i<= level; i++ ) {
                if ( update[i]->next[i] != temp_node ) {
                    break;
                }
                update[i]->next[i] = temp_node->next[i];
                update[i]->next[i]->prev[i] = update[i];
            	}
           
            	delete temp_node;
            	size--;
           
            	while ( level > 1 && head->next[level] == NULL ) {
                level--;
           		 }
			}
			//this->printList();

		}//remove

		
		~SkipList()
		{
			 
			SNode<Key_T,Mapped_T>* it = head->next[1];
        	while ( it && it != tail ) {
	           remove(it->ValueType.first);
	            it = it->next[1];
        	}
			delete head;
			delete tail;
		}
	};
//*****************************************************************************************************************************************************************

	template <typename Key_T , typename Mapped_T>
	class Map{
	private:
		SkipList<Key_T, Mapped_T>  sl;

	public:
		//*****************************************************************************************************************************************************************
		class Iterator{
			public:
				SNode<Key_T,Mapped_T> *curr_node;

			public:
				
    			
				Iterator(){};
				Iterator(const Iterator &it):curr_node(it.curr_node){}
				Iterator(SNode<Key_T,Mapped_T> *node):curr_node(node){}
				~Iterator(){curr_node=nullptr;}
				Iterator& operator=(const Iterator &);
				Iterator& operator++(){
					curr_node=curr_node->next[1];
					return *this;
				}
				Iterator operator++(int){
					Iterator ptr=*this;
					curr_node=curr_node->next[1];
					return ptr;	
				}
				Iterator& operator--(){
					curr_node=curr_node->prev[1];
					return *this;	
				}
				Iterator operator--(int){
					Iterator ptr=*this;
					curr_node=curr_node->prev[1];
					return ptr;	
				}

				std::pair < const Key_T, Mapped_T >& operator*() const{
					return (curr_node->ValueType);
				}
				std::pair < const Key_T, Mapped_T >& operator->() const{
					return (curr_node->ValueType);
				}
		};
	public:
		class ConstIterator{
			public:
				SNode<Key_T,Mapped_T> *curr_node;

			public:
				ConstIterator(){};
				ConstIterator(const Iterator &it):curr_node(it.curr_node){}
				ConstIterator(SNode<Key_T,Mapped_T> *node):curr_node(node){}
				~ConstIterator(){curr_node=nullptr;}
				ConstIterator& operator=(const ConstIterator &);
				ConstIterator& operator++(){
					curr_node=curr_node->next[1];
					return *this;
				}
				ConstIterator operator++(int){
					ConstIterator ptr=*this;
					curr_node=curr_node->next[1];
					return ptr;	
				}
				ConstIterator& operator--(){
					curr_node=curr_node->prev[1];
					return *this;	
				}
				ConstIterator operator--(int){
					ConstIterator ptr=*this;
					curr_node=curr_node->prev[1];
					return ptr;	
				}
				const std::pair < const Key_T, Mapped_T >& operator *()const{
					return (curr_node->ValueType);
				}
				const std::pair < const Key_T, Mapped_T >& operator->() const{
					return (curr_node->ValueType);
				}
		};

	public:
		class ReverseIterator{
			public:
				SNode<Key_T,Mapped_T> *curr_node;

			public:
				
    			
				ReverseIterator(){};
				ReverseIterator(const ReverseIterator &it):curr_node(it.curr_node){}
				ReverseIterator(SNode<Key_T,Mapped_T> *node):curr_node(node){}
				~ReverseIterator(){curr_node=nullptr;}
				ReverseIterator& operator=(const Iterator &);
				ReverseIterator& operator++(){
					curr_node=curr_node->prev[1];
					return *this;
				}
				ReverseIterator operator++(int){
					ReverseIterator ptr=*this;
					curr_node=curr_node->prev[1];
					return ptr;	
				}
				ReverseIterator& operator--(){
					curr_node=curr_node->next[1];
					return *this;	
				}
				ReverseIterator operator--(int){
					ReverseIterator ptr=*this;
					curr_node=curr_node->next[1];
					return ptr;	
				}

				std::pair < const Key_T, Mapped_T >& operator*() const{
					return (curr_node->ValueType);
				}
				std::pair < const Key_T, Mapped_T >& operator->() const{
					return (curr_node->ValueType);
				}
		};
		public:
		

		Map(){init_map();}

			Map(std::initializer_list<std::pair<const Key_T, Mapped_T>> list){ 		
				
				init_map();
			for (auto i=list.begin(); i !=list.end(); ++i)
			{	
				std::pair< Iterator,bool> node=sl.insert((*i));
			}		
		}

		Map(const Map & cp_map){
			init_map();

            SNode<Key_T, Mapped_T> *new_map ;
            for(new_map = cp_map.sl.head;new_map != cp_map.sl.tail;new_map = new_map->next[1]){
                this->sl.insert(new_map->ValueType);
            }
        }

		Map &operator=(const Map & cp_map){
			            SNode<Key_T, Mapped_T> *new_map ;
            for(new_map = cp_map.sl.head;new_map != cp_map.sl.tail;new_map = new_map->next[1]){
                this->sl.insert(new_map->ValueType);
            }
            return *this;
		}
		~Map(){}

		void init_map(){
			int i;
			const auto invalid_pair = std::make_pair(std::numeric_limits<int>::max(),std::numeric_limits<int>::max());
			sl.head = new SNode<Key_T,Mapped_T>(MAX_HEIGHT,invalid_pair);
			sl.tail = new SNode<Key_T,Mapped_T>(MAX_HEIGHT,invalid_pair);
			for (i = 1; i <= MAX_HEIGHT; i++) {
				sl.head->next[i] = sl.tail;
				sl.head->prev[i] = NULL;
				sl.tail->next[i] = NULL;
				sl.tail->next[i] = sl.head;
			}
			sl.level =1;
			sl.size = 0;
		}
		Iterator begin(){
			Iterator itr=sl.head->next[1];
			return itr;
		}
		Iterator end(){
			Iterator itr=sl.tail;
			return itr;
		}

		ConstIterator begin() const{
			ConstIterator itr=sl.head->next[1];
			return itr;
		}
		ConstIterator end() const{
			ConstIterator itr=sl.tail;
			return itr;
		}

		ReverseIterator rbegin(){
			ReverseIterator itr=sl.tail;
			return itr;

		}
		ReverseIterator rend(){
			ReverseIterator itr=sl.head->next[1];
			return itr;	
		}
		friend bool operator==(const Iterator &itr1,const Iterator &itr2){
		return itr1.curr_node == itr2.curr_node;}
    
    	friend bool operator==(const ConstIterator &itr1,const ConstIterator &itr2){
    	return itr1.curr_node == itr2.curr_node;}
    
    	friend bool operator==(const Iterator &itr1,const ConstIterator &itr2){
    	return itr1.curr_node == itr2.curr_node;}
    
    	friend bool operator==(const ConstIterator &itr1,const Iterator &itr2){
    	return itr1.curr_node == itr2.curr_node;}
    
    	friend bool operator!=(const Iterator &itr1,const Iterator &itr2){
    	return itr1.curr_node != itr2.curr_node;}
    
    	friend bool operator!=(const ConstIterator &itr1,const ConstIterator &itr2){
    	return itr1.curr_node != itr2.curr_node;}
    
    	friend bool operator!=(const Iterator &itr1,const ConstIterator &itr2){
    	return itr1.curr_node != itr2.curr_node;}
    
    	friend bool operator!=(const ConstIterator &itr1,const Iterator &itr2){
    	return itr1.curr_node == itr2.curr_node;}

    	friend bool operator==(const ReverseIterator &itr1,const ReverseIterator &itr2){
    	return itr1.curr_node == itr2.curr_node;}
    
    	friend bool operator!=(const ReverseIterator &itr1,const ReverseIterator &itr2){
    	return itr1.curr_node != itr2.curr_node;}

    



//*****************************************************************************************************************************************************************

			
	
	
		bool empty() const{
			bool ret=sl.is_empty();
			return ret;
		}
		size_t size() const{
			sl.get_size();
		}

		Iterator find (const Key_T & key){
			Iterator itr;
			itr.curr_node=sl.Search_key(key);
			
			if (itr.curr_node)
				return itr;
			else
			{
				itr.curr_node=sl.tail;
				return itr;
			}
			
		}
		/*
		ConstIterator find (const Key_T & key) const {
			ConstIterator itr;
			itr.curr_node=sl.Search_key(key);
			if (itr.curr_node)
				return itr;
			else
			{
				itr.curr_node=sl.tail;
				return itr;
			}
			
		}*/
		Mapped_T & at(const Key_T & key){
			SNode<Key_T,Mapped_T>* temp_node=sl.Search_key(key);
			if (temp_node)
			{
			
				return temp_node->ValueType.second;
			}
			throw std::out_of_range("Search out_of_range for at");
		}//at

		const Mapped_T & at(const Key_T & key) const{
			SNode<Key_T,Mapped_T>* temp_node=sl.head;
			for (int i = sl.level; i >= 1; i--) {
				while (temp_node->next[i]->ValueType.first < key)
						temp_node = temp_node->next[i];}
			
			temp_node = temp_node->next[1];
			if (key == temp_node->ValueType.first) {
				
				return temp_node->ValueType.second;
				
			}
			throw std::out_of_range("Search out_of_range for at");
		}//const at


		Mapped_T &operator[](const Key_T & key)
		{
			SNode<Key_T,Mapped_T>* temp_node=sl.Search_key(key);
			if (temp_node)
				return temp_node->ValueType.second;
			else
			{
				
				std::pair< Iterator,bool> node = sl.insert(std::make_pair(key, Mapped_T{}));
				Iterator it=node.first;
				return it.curr_node->ValueType.second;
			}

		}

		std::pair< Iterator,bool> insert(const std::pair< Key_T,Mapped_T>& val){
			
			std::pair< Iterator,bool> node = sl.insert(val);	
			return node;
		}//insert

		
    	template <typename IT_T>
    	void insert(IT_T range_beg, IT_T range_end){
        	auto i = range_beg;
        	while(i != range_end){
            	insert(*i);
            	++i;
        	}
        	sl.printList();
    	}	

		void erase(Iterator pos){
			sl.remove(pos.curr_node->ValueType.first);
			sl.printList();
		}

		void erase(const Key_T & key){
			sl.remove(key);
			
		}//key_erase testing remaining

		void clear(){
			SNode<Key_T,Mapped_T> *it = sl.head;
			while (it && it->next[1] != sl.head) {
				sl.remove(it->next[1]->ValueType.first);
			}

		}

	};
		template <typename Key_T, typename Mapped_T>
		bool operator == ( const Map<Key_T, Mapped_T> &map1, const Map<Key_T, Mapped_T> &map2)
		{
			if(map1.size()!=map2.size())
				return false;
			else
			{
				auto m1=map1.begin(), m2=map2.begin();
				while(m1!=map1.end() && m2!=map2.end())
				{
					if(*m1 != *m2)
						return false;
					++m1;
					++m2;
				}
				return true;
			}

		}

		template <typename Key_T, typename Mapped_T>
		 bool operator != (const  Map<Key_T, Mapped_T> &map1, const  Map<Key_T, Mapped_T> &map2){
			return !(map1==map2);
		}

		template <typename Key_T, typename Mapped_T>
   		 bool operator<(const Map<Key_T, Mapped_T> &map1, const Map<Key_T, Mapped_T> &map2){
        if(map1.size()<map2.size())
        	return true;
        if(map1.size()>map2.size())
        	return false;
        //same size
        auto m1= map1.begin(), m2= map2.begin();
        while(m1 != map1.end() && m2 != map2.end()){
            if ((*m1).first < (*m2).first)
            {
 				return true;
            }
            if ((*m1).first > (*m1).first)
            {
            	return false;
            }
            m1++;
            m2++;
        }
        //maps are same
        return false;
    }
	
#endif
}