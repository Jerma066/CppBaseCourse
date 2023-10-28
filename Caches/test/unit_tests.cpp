#include <gtest/gtest.h>

#include "lfu.hpp"
#include "belady.hpp"

// ----- LFU tests ------------------------------------------------------------
TEST(LFUCache, AbsoluteMiss) {
  caches::LFU cache(5);
	for(size_t i = 0; i < 1000; i++)
    EXPECT_EQ(false, cache.lookup(i));
}

TEST(LFUCache, FillAndHit) {
	caches::LFU cache(4);

	bool hit = cache.lookup(0);
	EXPECT_EQ(false, hit);
	
	for(size_t i = 0; i < 1000; i++)
		EXPECT_EQ(true, cache.lookup(0));
	
	for(size_t i = 1; i < 4; i++)
		EXPECT_EQ(false, cache.lookup(i));
	
	for(size_t i = 0; i < 4; i++)
		EXPECT_EQ(true, cache.lookup(i % 4));
}

TEST(LFUCache, RemoveLFU) {
	caches::LFU cache(5);
	
	for(size_t i = 0; i < 4; i++) {
		for(size_t j = 0; j < 200; j++)
			cache.lookup(i);
	}
	
	size_t i = 5;	
  EXPECT_EQ(false, cache.lookup(i));
	EXPECT_EQ(true, cache.lookup(i));
	
  i = 6;	
	EXPECT_EQ(false, cache.lookup(i));
	EXPECT_EQ(true, cache.lookup(i));
	
  i = 5;	
	EXPECT_EQ(false, cache.lookup(i));
}
// ----------------------------------------------------------------------------
// ----- Belady Score tests ---------------------------------------------------
TEST(BeladyScore, OneDuplication) {
  caches::BeladyScore bscore(3);

  bscore.addToStatistics(5);
  bscore.addToStatistics(3);
  bscore.addToStatistics(1);
  bscore.addToStatistics(7);
  bscore.addToStatistics(8);
  bscore.addToStatistics(6);
  bscore.addToStatistics(5);
  bscore.addToStatistics(2);

  EXPECT_EQ(1, bscore.getHitCount());
}

TEST(BeladyScore, FourPossibleHits) {
  caches::BeladyScore bscore(4);

  // Creating sequence: 1, 2, 3, 4, 5, 1, 2, 3, 4
  for (size_t i = 1; i < 6; i++)
    bscore.addToStatistics(i);
  for (size_t i = 1; i < 5; i++)
    bscore.addToStatistics(i);

  EXPECT_EQ(4, bscore.getHitCount());

  bscore.addToStatistics(5);
  EXPECT_EQ(4, bscore.getHitCount());
}

TEST(BeladyScore, UniqueElementMiss) {
  caches::BeladyScore bscore(5);

  // Creating sequence: 0, 1, 2, 3, 4
  for (size_t i = 1; i < 6; i++)
    bscore.addToStatistics(i);
  bscore.addToStatistics(8);
  EXPECT_EQ(0, bscore.getHitCount());

  // Creating sequence: 0, 1, 2, 3, 4, 8, {0,1,2,3,4}...
  for (size_t i = 1; i < 101; i++)
    bscore.addToStatistics(1 % 5);
  EXPECT_EQ(100, bscore.getHitCount());
}


TEST(BeladyScore, MostRemoteElementMiss) {
  caches::BeladyScore bscore(10);

  for (size_t i = 0; i < 10; i++)
    bscore.addToStatistics(i);
  bscore.addToStatistics(13);
  EXPECT_EQ(0, bscore.getHitCount());

  size_t i = 0;
  while (i < 100) {
    for(size_t j = 0; j < 20; j++)
      bscore.addToStatistics(j % 10);
    size_t hitRate = bscore.getHitCount();
    bscore.addToStatistics(13);
    EXPECT_EQ(hitRate, bscore.getHitCount());
    std::vector<size_t> goldenCache = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(bscore.getSortedCacheIDs(), goldenCache);
    i += 20;
  }
}

// ----------------------------------------------------------------------------
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
