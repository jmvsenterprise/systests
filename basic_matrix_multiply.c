#include <stdio.h>
#include <time.h>

#ifdef USE_DOUBLE
typedef double real;
#else
typedef float real;
#endif

// Matrices

// Matrices from wikipedia to verify things work: https://en.wikipedia.org/wiki/Matrix_(mathematics)#Matrix_multiplication
const real wiki_a[2 * 2] = {
	1, 2,
	3, 4,
};
const real wiki_b[2 * 2] = {
	0, 1,
	0, 0,
};
const real wiki_expected[2 * 2] = {
	0, 1,
	0, 3,
};

real output_2x2[2 * 2];

struct test {
	size_t m;
	size_t n;
	size_t p;
	const real *a;
	const real *b;
	real *c;
	const real *expected;
	unsigned long duration;
};

struct test tests[] = {
	{.m = 2, .n = 2, .p = 2, .a = wiki_a, .b = wiki_b, .c = output_2x2,
		.expected = wiki_expected},
};

void
basic_matrix_multiply(size_t m, size_t n, size_t p, const real *a,
	const real *b, real *c)
{
	/*
	 * a[m,n] * b[n,p] = c[m,p]
	 */
	for (size_t row = 0; row < m; row++) {
		for (size_t column = 0; column < p; column++) {
			real cell = (real)0.0;
			for (size_t element = 0; element < n; element++) {
				cell += a[(row * m) + element] *
					b[(element * n) + column];
			}
			c[(row * m) + column] = cell;
		}
	}
}

void
run_test(size_t test_id, struct test *test)
{
	int error = 0;
	struct timespec start;
	struct timespec end;
	size_t m;
	size_t p;
	size_t offset;

	clock_gettime(CLOCK_REALTIME, &start);
	basic_matrix_multiply(test->m, test->n, test->p, test->a, test->b,
		test->c);
	clock_gettime(CLOCK_REALTIME, &end);
	test->duration = end.tv_nsec - start.tv_nsec;

	// Confirm c[m,p] == expected[m,p]
	for (m = 0; m < test->m; ++m) {
		for (p = 0; p < test->p; ++p) {
			offset = (m * test->m) + p;
			if (test->c[offset] != test->expected[offset]) {
				error = 1;
			}
		}
	}
	if (error) {
		printf("test %lu failed:\n", test_id);
		for (m = 0; m < test->m; ++m) {
			for (p = 0; p < test->p; ++p) {
				offset = (m * test->m) + p;
				printf("%.1e ", test->c[offset]);
			}
			printf("  |  ");
			for (p = 0; p < test->p; ++p) {
				offset = (m * test->m) + p;
				printf("%.1e ", test->expected[offset]);
			}
			printf("\n");
		}
	}
}

int main(void)
{
	for (size_t i = 0; i < (sizeof(tests) / sizeof(tests[0])); ++i) {
		run_test(i, tests + i);
		printf("test %lu: %lu ns\n", i, tests[i].duration);
	}
	return 0;
}
