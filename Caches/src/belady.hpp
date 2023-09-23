#pragma once

#include <stdlib.h>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>

namespace caches {

class BeladyScore {
public: 
  explicit BeladyScore(size_t size):
    sz_(size), hc_(0),
    currentStateWasChanged(false) {}
  
public:
  std::vector<size_t> getSortedCacheIDs() {
    std::vector<size_t> cacheIDs = std::vector(cache.begin(), cache.end());
    std::sort(cacheIDs.begin(), cacheIDs.end());
    return cacheIDs;
  }

  void addToStatistics(size_t id){
    inputData.push_back(id);
    currentStateWasChanged = true;
  }

  size_t getHitCount() {
    if (currentStateWasChanged) {
      hc_ = 0;
      cache.clear();
      beladyRemoteness.clear();

      for (size_t i = 0, end = inputData.size(); i < end; i++) {
        UpdateCacheElements(i);
        if (lookup(inputData[i], i))
          hc_++;
      }
    }

    return hc_;
  }

private:
  void UpdateCacheElements(size_t pos) {
    std::map<int, std::unordered_set<size_t>::iterator> newBeladyRemoteness;
    for (auto it = cache.begin(); it != cache.end(); it++) {
      // TODO: Algorithm can be improved with counting distances as
      //       distance = oldDistance - 1, where oldDistance != 0;

      auto nextItemEntry =
        std::find(inputData.begin() + pos + 1, inputData.end(), *it);
      size_t distance = nextItemEntry - (inputData.begin() + pos);
      newBeladyRemoteness[distance] = it;
    }

    beladyRemoteness = newBeladyRemoteness;
  }

  void EraseMostRemoteElement() {
    auto delIter = std::prev(beladyRemoteness.end());

    cache.erase(delIter->second);
    beladyRemoteness.erase(delIter); 
  }

  void InsertElement(size_t id, int distance) {
    auto [cacheIter, _] = cache.insert(id);
    beladyRemoteness[distance] = cacheIter;
  }

  bool lookup(const size_t id, const size_t pos) {
    if (cache.find(id) == cache.end()) {
      auto nextIdEntry =
        std::find(inputData.begin() + pos + 1, inputData.end(), id);
      auto distance = nextIdEntry - (inputData.begin() + pos);
      if (cache.size() == sz_) {
        auto mostRemoteDist = beladyRemoteness.rbegin()->first;
        if (distance < mostRemoteDist) {
          EraseMostRemoteElement();
          InsertElement(id, distance);
        }
      } else {
        InsertElement(id, distance);
      }

      return false;
    }

    return true; 
  }


private:
  const size_t sz_;
  std::vector<size_t> inputData;

  size_t hc_;
  bool currentStateWasChanged;

  std::unordered_set<size_t> cache;
  std::map<int, std::unordered_set<size_t>::iterator> beladyRemoteness;
};

} // caches
