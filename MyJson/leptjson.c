#include "leptjson.h"
#include <assert.h>

/*still donnot get it*/
typedef struct {
	const char* json;
}lept_context;

static void lept_parse_whitespace(lept_context* c);
static int lept_parse_null(lept_context* c, lept_value* v);
static int lept_parse_value(lept_context* c, lept_value* v);

int lept_parse(lept_value* v, const char* json) {
	lept_context c;
	int ret;
	assert(v != NULL);
	c.json = json;
	v->type = LEPT_NULL;
	lept_parse_whitespace(&c);
	/* json形式： JSON-text = ws value ws 前面去除了前面的ws，
	解析完值后，判断后面是否符合形式*/
	if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK) {
		lept_parse_whitespace(&c);
		if (*c.json != '\0') {
			ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
		}
	}
	return ret;
}

/*
定义宏如果多行用do{...}while(0)
*/
#define EXPECT(c, ch) \
	do {\
		assert(*c->json == (ch));\
		c->json++;\
	}while(0)

static void lept_parse_whitespace(lept_context* c) {
	const char* p = c->json;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
		p++;
	}
	c->json = p;
}

static int lept_parse_null(lept_context* c, lept_value* v) {
	EXPECT(c, 'n');
	if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
		return LEPT_PARSE_INVALID_VALUE; 
	}
	c->json += 3;
	v->type = LEPT_NULL;
	return LEPT_PARSE_OK;
}

static int lept_parse_false(lept_context* c, lept_value* v) {
	EXPECT(c, 'f');
	if (c->json[0] != 'a' || c->json[1] != 'l' ||
		c->json[2] != 's' || c->json[3] != 'e') {
		return LEPT_PARSE_INVALID_VALUE;
	}
	c->json += 4;
	v->type = LEPT_FALSE;
	return LEPT_PARSE_OK;
}

static int lept_parse_true(lept_context* c, lept_value* v) {
	EXPECT(c, 't');
	if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e') {
		return LEPT_PARSE_INVALID_VALUE;
	}
	c->json += 3;
	v->type = LEPT_TRUE;
	return LEPT_PARSE_OK;
}

static int lept_parse_value(lept_context* c, lept_value* v) {
	switch (*c->json) {
		/* because of return, break is not needed. */
	case 'n':	return lept_parse_null(c, v); break;
	case 'f':	return lept_parse_false(c, v); break;
	case 't':	return lept_parse_true(c, v); break;
	case '\0':	return LEPT_PARSE_EXPECT_VALUE; break;
	default:	return	LEPT_PARSE_INVALID_VALUE; break;
	}
}

lept_type lept_get_type(const lept_value* v) {
	/*
	断言(assertion)是C语言中常用的防御式编程方式，减少编程错误。
	<assert.h> assert() release时(ndef NDEBUG) assert()不做检测
						debug时 assert()失败会导致程序崩溃
		基于以上原因，assert不应该有副作用，否则导致release和debug行为不一致
	常用：
	1. 函数开始处，检测参数是否正确
	2. 函数结束后，检测上下文是否正确
	*/
	assert(v != NULL);
	return v->type;
}