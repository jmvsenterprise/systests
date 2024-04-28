/**
 * @file
 *
 * This file tests the overhead of runtime polymorphism versus other strategies
 * for dealing with many different kinds of objects.
 *
 * Runtime polymorphism is ideally used for cases where you have several
 * different kinds of objects with similar interfaces, so I will attempt to
 * model that, as well as the use case where all the objects are the same (to
 * analyze if instruction caching helps).
 *
 * I will also test various other strategies for doing the same work that do
 * not use runtime polymorphism.
 */
#include "polymorphism.h"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

namespace polymorphic {

using clock = std::chrono::high_resolution_clock;
using milliseconds = std::chrono::milliseconds;

double random_double()
{
	static std::random_device dev;
	static std::uniform_real_distribution generator;
	return generator(dev);
}

void test(const int count)
{
	const auto setup_start = clock::now();
	std::vector<shape*> shapes(count, nullptr);
	int i = 0;
	for (shape*& s : shapes) {
		switch (i) {
		case 0:
			s = new square(random_double());
			break;
		case 1:
			s = new rectangle(random_double(), random_double());
			break;
		case 2:
			s = new circle(random_double());
			break;
		}
		i++;
		if (i > 2) i = 0;
	}
	const auto setup_end = clock::now();

	// Run the test.
	const auto test_start = clock::now();
	for (const shape* s : shapes) {
		[[maybe_unused]]double area = s->area();
	}
	const auto test_end = clock::now();

	const auto setup_time = std::chrono::duration_cast<milliseconds>(
		setup_end - setup_start);
	const auto test_time = std::chrono::duration_cast<milliseconds>(
		test_end - test_start);

	std::cout << __func__ << ": count=" << count << " times: setup=" <<
		setup_time.count() << " test=" << test_time.count() << "\n";

}

} // End namespace polymorphic
