#pragma once

#include <ostream>
#include <list>
#include <stdlib.h>
#include <unordered_map>
#include <functional>

namespace caches {

namespace dflt {

using DataType = double;

double dataGetter(size_t id) {
  double valueFromId = static_cast<double>(id);
  return valueFromId;
}

} // dflt

template <typename Data = dflt::DataType>
class LFU final {
public:
  explicit LFU(size_t size,
               std::function<Data(size_t)> dataGetter = dflt::dataGetter):
    sz_(size), valueFromIdFunc(dataGetter) {}

public:
  void dump(std::ostream& OS) const {
    OS << "LFU {id: fr}: {";
    bool firstElem = true;
    for (const auto& it : idToElem) {
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
    size_t initialFrequency = 1;

    freqToElems[initialFrequency].emplace_front(id, initialFrequency,
                                                valueFromIdFunc(id));
    idToElem[id] = freqToElems[initialFrequency].begin();
    minFreq = initialFrequency;
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
    Elem() {}
    Elem(size_t id, size_t fr, Data val) : id(id), freq(fr), value(val) {}

    size_t id;
    size_t freq;
    Data value;
  };
  
  const size_t sz_;
  size_t minFreq = 0;
  std::unordered_map<size_t, typename std::list<Elem>::iterator> idToElem;
  std::unordered_map<size_t, std::list<Elem>> freqToElems;

  std::function<Data(size_t)> valueFromIdFunc;
};

} // caches
