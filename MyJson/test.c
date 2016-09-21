/*
单元测试，回归测试 确保他人修改代码后，原来的功能维持正确
TDD驱动测试开发 
	1. 加入一个测试
	2. 运行所有测试，新的测试应该会失败
	3. 编写实现代码
	4. 运行所有测试，若有失败回到3
	5. 重构代码
	6. 回到1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leptjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

/*
宏的编写技巧：
如果宏是多个语句，do{...}while(0)的形式
*/

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
	do {\
		test_count++;\
		if (equality)\
		{\
			test_pass++;\
		}\
		else {\
			fprintf(stderr, "%s:%d: expect" format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
			main_ret = 1;\
		}\
	} while(0)

#define	EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d");

static void test_parse_null() {
	lept_value v;
	v.type = LEPT_TRUE;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "null"));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_true() {
	lept_value v;
	v.type = LEPT_TRUE;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "true"));
	EXPECT_EQ_INT(LEPT_TRUE, lept_get_type(&v));
}

static void test_parse_false() {
	lept_value v;
	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "false"));
	EXPECT_EQ_INT(LEPT_FALSE, lept_get_type(&v));
}

static void test_parse_expect_value() {
	lept_value v;

	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, ""));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, " "));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_invalid_value() {
	lept_value v;

	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "nu"));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "?"));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_root_not_singular() {
	lept_value v;

	v.type = LEPT_FALSE;
	EXPECT_EQ_INT(LEPT_PARSE_ROOT_NOT_SINGULAR, lept_parse(&v, "null x"));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse() {
	test_parse_null();
	test_parse_true();
	test_parse_false();
	test_parse_expect_value();
	test_parse_invalid_value();
	test_parse_root_not_singular();
}

int main() {
	test_parse();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count,
		test_pass * 100.0 / test_count);
	getchar();
	return main_ret;
}
