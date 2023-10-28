#pragma once

#include <algorithm>
#include <map>
#include <queue>
#include <unordered_set>
#include <vector>

#include <iostream>

namespace caches {

class BeladyScore {
public: 
  explicit BeladyScore(size_t size): sz_(size){}
  
public:
  std::vector<size_t> getSortedCacheIDs() {
    std::vector<size_t> cacheIDs = std::vector(cache.begin(), cache.end());
    std::sort(cacheIDs.begin(), cacheIDs.end());
    return cacheIDs;
  }

  void dump(std::ostream &OS) {
    OS << "Cache IDs: ";
    for (auto elem : cache)
      OS << elem << ' ';
    OS << '\n';

    OS << "Remotenes: ";
    for (auto pair : beladyRemoteness)
      OS << '{' << *pair.second << ';' << pair.first << "} ";
    OS << std::endl;
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

      // Initialize elements positions
      for (size_t i = 0, end = inputData.size(); i < end; ++i)
        elementsPositions[inputData[i]].push(i);

      for (size_t i = 0, end = inputData.size(); i < end; ++i) {
        if (lookup(inputData[i], i))
          hc_++;
      }
    }

    return hc_;
  }

private:
  // TODO: Use std::optional instead of std::pair
  std::pair<bool, size_t> GetNextPositionOfElem(size_t pos, size_t elem) {
    std::pair<bool, size_t> nextPos = {false, 0};

    auto it = elementsPositions.find(elem);
    if (it != elementsPositions.end()) {
      std::queue<size_t> &positions = it->second;
      while (!positions.empty() && positions.front() <= pos)
        positions.pop();

      if (!positions.empty()) {
        nextPos = {true, positions.front()};
      } else {
        elementsPositions.erase(it);
      }
    }

    return nextPos;
  }

  void UpdateCacheElements(size_t pos) {
    std::map<size_t, std::unordered_set<size_t>::iterator> newBeladyRemoteness;
    for (auto belRemElem : beladyRemoteness) {
      std::pair<bool, size_t> nextPos =
          GetNextPositionOfElem(pos, *belRemElem.second);

      // Update position of element or remove element from cache
      if (nextPos.first) {
        newBeladyRemoteness[nextPos.second] = belRemElem.second;
      } else {
        cache.erase(cache.find(*belRemElem.second));
      }
    }
    beladyRemoteness = newBeladyRemoteness;
  }

  void EraseMostRemoteElement() {
    auto delIter = std::prev(beladyRemoteness.end());
    cache.erase(delIter->second);
    beladyRemoteness.erase(delIter);
  }

  void InsertElement(size_t id, size_t nextPosition) {
    auto [cacheIter, _] = cache.insert(id);
    beladyRemoteness[nextPosition] = cacheIter;
  }

  bool lookup(const size_t id, const size_t pos) {
    // Update elements remotness if cache is full.
    // Otherwise elements will be just added to cache.

    if (cache.find(id) == cache.end()) {
      std::pair<bool, size_t> nextPos = GetNextPositionOfElem(pos, id);

      if (nextPos.first && cache.size() == sz_)
        UpdateCacheElements(pos);

      // Insert Element only if it will appear in the future
      if (nextPos.first) {
        if (cache.size() == sz_) {
          // Next position of curent elem is less than next position of
          // most remote element in cache
          if (nextPos.second < beladyRemoteness.rbegin()->first) {
            EraseMostRemoteElement();
            InsertElement(id, nextPos.second);
          } else if (beladyRemoteness.empty()) {
            InsertElement(id, nextPos.second);
          }
        } else {
          InsertElement(id, nextPos.second);
        }
      }

      return false;
    }

    return true;
  }

private:
  const size_t sz_;
  std::vector<size_t> inputData;
  std::unordered_set<size_t> cache;
  std::map<size_t, std::unordered_set<size_t>::iterator> beladyRemoteness;
  std::unordered_map<size_t, std::queue<size_t>> elementsPositions;

  size_t hc_ = 0;
  bool currentStateWasChanged = false;
  int distDecrCnt = 1;
};

} // caches
