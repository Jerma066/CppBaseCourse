#pragma once

#include <ostream>
#include <list>
#include <stdlib.h>
#include <unordered_map>

namespace caches {

class LFU final {
public:
  explicit LFU(size_t size): sz_(size), minFreq(0) {}

public:
  void dump(std::ostream& OS) {
    OS << "LFU {id: fr}: {";
    bool firstElem = true;
    for (auto it = idToElem.begin(), end = idToElem.end(); it != end; ++it) {
      std::string sep = firstElem ? "" : ", ";
      OS << sep << it->second->id << ":" << it->second->freq;
      firstElem = false;
    }
    OS << "}";
  }

  bool lookup(size_t id) {
    auto elemIt = idToElem.find(id);    
    if (elemIt == idToElem.end()) {
      // Cache is full: should erase Last Frequently Used element
      if (idToElem.size() == sz_)
        EraseLFUElement();

      // Insert element with initial frequency
      InsertNewElement(id);
      return false;
    }

    // Update element frequency
    UpdateElemFreq(id);    
    return true;
  }

private:
  void EraseLFUElement() {
    int eraseId = freqToElems[minFreq].back().id;    
    idToElem.erase(eraseId);
    freqToElems[minFreq].pop_back();
  }

  void InsertNewElement(size_t id) {
    minFreq = 1;
    freqToElems[1].push_front(Elem{id, 1});
    idToElem[id] = freqToElems[1].begin();
  }

  void UpdateElemFreq(size_t id) {
    auto Elem = *idToElem[id];
    freqToElems[Elem.freq].erase(idToElem[id]); 
    if(freqToElems[minFreq].size() == 0)
      minFreq++;
    
    Elem.freq++;
    freqToElems[Elem.freq].push_front(Elem);
    idToElem[id] = freqToElems[Elem.freq].begin();
  }
private:
  struct Elem {
    size_t id;
    size_t freq;
  };
  
  const size_t sz_;
  size_t minFreq = 0;
  std::unordered_map<size_t, std::list<Elem>::iterator> idToElem;
  std::unordered_map<size_t, std::list<Elem>> freqToElems;
};

} // caches
