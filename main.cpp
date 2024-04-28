#include "polymorphism.h"

int main()
{
	polymorphic::test(10);
	polymorphic::test(100);
	polymorphic::test(1000);
	polymorphic::test(10000);
	polymorphic::test(100000);
	polymorphic::test(1000000);
	polymorphic::test(10000000);
	polymorphic::test(100000000);
	// Need to figure out how much memory the computer has and make sure
	// we don't explode it before enabling the next test (and actually
	// I shouldn't enable the next test as is. It should be bound to the
	// memory of the computer.
	//polymorphic::test(1000000000);

	return 0;
}
