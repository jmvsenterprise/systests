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
#ifndef POLYMORPHIC_TYPES
#define POLYMORPHIC_TYPES

#include <numbers>

namespace polymorphic {

double random_double();

/**
 * @brief The base class for the polymorphic types
 */
struct shape {
	virtual ~shape() = default;

	virtual double area() const = 0;
};

struct square : public shape {
	constexpr square(const double side_length) : side{side_length} {}

	double area() const override
	{
		return side * side;
	}
private:
	double side;
};

struct rectangle : public shape {
	constexpr rectangle(const double side1_len, const double side2_len) :
		side1{side1_len}, side2{side2_len}
	{}

	double area() const override
	{
		return side1 * side2;
	}
private:
	double side1;
	double side2;
};

struct circle : public shape {
	constexpr circle(const double radius_len) : radius{radius_len} {}

	double area() const override
	{
		return std::numbers::pi * radius * radius;
	}

private:
	double radius;
};

/**
 * This function will build an array of shapes cycling through each of the
 * shapes in turn until it has the same number of shapes as the count provided.
 *
 * Then it will time how long it takes to compute the area for all of the
 * shapes and print the results to the screen.
 */
void test(const int count);

} // End namespace polymorphic

#endif // POLYMORPHIC_TYPES
