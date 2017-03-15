#include "Map.hpp"

#include <cassert>

int main() {
    cs540::Map<const int, int> m{{3, 5}};
    

    //test for empty
    if(!m.empty()){
          //test for insert
    auto itr=m.insert({{2}, {3}});
    m.insert({{1}, {3}});
    m.insert({{5}, {3}});
    m.insert({{7}, {3}});
  }

    //test for insert with range
  std::cout<<"Map Insertion in range\n";
  cs540::Map<int,int> map_range;
    map_range.insert(m.begin(),m.find(5));
      //test for size
    std::cout<<"Size of Map: ";
     auto size1=m.size();
   std::cout<<size1<<"\n";
    //test for iterators
    auto it1 = m.begin();
    it1++;
    //m.print(it1);
    it1++;
    it1++;
    //m.printIt(it1);
    auto it2 = m.end();
    it2--;
    it2--;
    //std::cout<<"\n";
    assert(it1 == it2);
    it2--;
    it2--;
    it2--;
    //m.printIt(it2);
    assert(m.begin() == it2);
    std::cout<<"Iterator are equal\n";


    //test for reverse Iterator
   
    auto rit=m.rend();
    rit--;
    rit--;
    rit--;
    rit--;
    rit--;
    assert(rit==m.rbegin());
    std::cout<<"Reverse Iterator are equal\n";
   
    cs540::Map<const int, int>::ConstIterator cit = m.begin();
    

    //test for constIterator
    assert(m.begin()==cit);
    std::cout<<"Iterator ConstIterator comparision\n";
    cit++;
    cit++;
    cit++;
    cit++;
    cit++;
    cs540::Map<const int, int>::ConstIterator cit_end = m.end();
    assert(it1 != cit);
    assert(cit_end==cit);
    std::cout<<"ConstIterator are equal\n";
   
   
    
    auto m_copy = m;
    //assert(m_copy == m);
    if(m_copy==m)
      std::cout<<"Map are equal\n";

    
    //test at
   //cout<<"at\t";
   m.at(2);
   assert(m.at(2)==3);
   auto iter = m.find(2);
    std::cout<<"After Erasing\n";
    m.erase(iter);
    assert(m.size()==--size1); //compare size after erase
  if(m_copy!=m)
      std::cout<<"Map are not equal\n";
   //test for find and erase
    if(m<m_copy)
      std::cout<<"Map1 is less\n";      

    assert(m_copy.at(1)==3);

    //m.clear();
    //std::cout<<"\n"<<m.size();
    //assert(m.size()==0);
    //std::cout<<"m_copy at\t";

    //std::cout<<"\n";

    cs540::Map<int, int> m2{{8, 9}};
    m2[10]; // should default construct these values
    m2[15];

    
    return 0;
}