#pragma once
#include <vector>
#include "SortedMap.h"
std::vector<int> keysInRandomOrder(int cMin, int cMax);
void populateSMEmpty(SortedMap& sm, int cMin, int cMax);
void showMap(const SortedMap& map);
bool increasing(TKey c1, TKey c2);
void testAllExtended();
