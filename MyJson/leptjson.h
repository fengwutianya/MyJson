/*
C语言为了防止文件重复包含导致重复声明，
利用宏加以include防范：
#ifndef...#define...#endif
*/

/*
多个文件或者目录的话，可以用项目名_目录名_文件名_H__
*/
#ifndef LEPTJSON_H__
#define LEPTJSON_H__

/*
json中有六种数据类型，如下
1. null: null
2. boolean: true, false
3. number; 浮点
4. string: "..."
5. array: [...]
6. object: {...}
算上true，false，一共七种数据结构，七种可能，采用枚举enum类型
枚举值大写，类型及函数小写，C语言没有命名空间，项目简写为标识符前缀
*/
typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE,
		LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY,
		LEPT_OBJECT}lept_type;
/*
json解析成树结构，树的节点肯定用struct表示啦，
struct里面的主要数据就是上面声明的枚举类型
*/
typedef struct {
	lept_type type;
}lept_value;

/*
解析json的API函数，传入参数为：
1. 要解析的json字符串，不做修改 const char* json
2. 要生成的树状结构, 树的根节点由用户指定lept_value* v
返回值为函数的执行状态，也应该用枚举类型enum
*/
int lept_parse(lept_value* v, const char* json);

/*
要处理的json语法子集
JSON-text = ws value ws
ws = *(%x20 / %x09 / %x0A / %x0D) 任意 空格 tab 换行 回车
null	= "null"
false	= "false"
true	= "true"
*/

/*
1. 成功码LEPT_PARSE_OK
2. 错误码
	1) 只含空白LEPT_PARSE_EXPECT_VALUE
	2) 一个值以后，空白之后还有其他字符LEPT_PARSE_ROOT_NOT_SINGULAR
	3) 不是现在处理的三种字面值，传回LEPT_PARSE_INVALID_VALUE
*/
enum {
	LEPT_PARSE_OK = 0,
	LEPT_PARSE_EXPECT_VALUE,
	LEPT_PARSE_INVALID_VALUE,
	LEPT_PARSE_ROOT_NOT_SINGULAR
};

/*
访问结果的函数，此时只要获取它的值
*/
lept_type lept_get_type(const lept_value* v);

#endif
