#include <gtest/gtest.h>

#include "src/lfu.hpp"
#include "src/belady.hpp"
#include "src/belady.hpp"

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
// ----------------------------------------------------------------------------
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
