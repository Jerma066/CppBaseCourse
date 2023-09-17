#include <gtest/gtest.h>

#include "src/lfu.hpp"

TEST(LFUCache, AbsoluteMissTest) {
  caches::LFU cache(5);
	for(size_t i = 0; i < 1000; i++)
    EXPECT_EQ(false, cache.lookup(i));
}

TEST(LFUCache, TestHit) {
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

TEST(LFUCache, TestRemoveMostLFU){
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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
