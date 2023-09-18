#include "src/lfu.hpp"
#include "src/belady.hpp"

#include <iostream>

int main() {
  size_t cacheSize, inputSize;
  std::cin >> cacheSize >> inputSize;

  caches::LFU lfuCache(cacheSize);
  caches::BeladyScore bscore(cacheSize);
  
  size_t hitsNum = 0;
  for (size_t i = 0; i < inputSize; i++) {
    size_t id;
    std::cin >> id;

    if (lfuCache.lookup(id))
      hitsNum++;
    bscore.addToStatistics(id);
  }

  size_t bhitsNum = bscore.getHitCount();
  std::cout << "LFU cache hit rate: " << hitsNum << "\n";
  std::cout << "Belady score: " << bhitsNum << "\n";

  if (bhitsNum > hitsNum) {
    std::cout << "Belady's adnvantage: " << bhitsNum - hitsNum << std::endl;
  } else if (bhitsNum < hitsNum) {
    std::cout << "LFU cache's advanage: " << hitsNum - bhitsNum << std::endl;
  } else {
    std::cout << "Hit rates are equal" << std::endl;
  }

  return 0;
}
