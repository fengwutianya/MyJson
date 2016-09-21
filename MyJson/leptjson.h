/*
C����Ϊ�˷�ֹ�ļ��ظ����������ظ�������
���ú����include������
#ifndef...#define...#endif
*/

/*
����ļ�����Ŀ¼�Ļ�����������Ŀ��_Ŀ¼��_�ļ���_H__
*/
#ifndef LEPTJSON_H__
#define LEPTJSON_H__

/*
json���������������ͣ�����
1. null: null
2. boolean: true, false
3. number; ����
4. string: "..."
5. array: [...]
6. object: {...}
����true��false��һ���������ݽṹ�����ֿ��ܣ�����ö��enum����
ö��ֵ��д�����ͼ�����Сд��C����û�������ռ䣬��Ŀ��дΪ��ʶ��ǰ׺
*/
typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE,
		LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY,
		LEPT_OBJECT}lept_type;
/*
json���������ṹ�����Ľڵ�϶���struct��ʾ����
struct�������Ҫ���ݾ�������������ö������
*/
typedef struct {
	lept_type type;
}lept_value;

/*
����json��API�������������Ϊ��
1. Ҫ������json�ַ����������޸� const char* json
2. Ҫ���ɵ���״�ṹ, ���ĸ��ڵ����û�ָ��lept_value* v
����ֵΪ������ִ��״̬��ҲӦ����ö������enum
*/
int lept_parse(lept_value* v, const char* json);

/*
Ҫ�����json�﷨�Ӽ�
JSON-text = ws value ws
ws = *(%x20 / %x09 / %x0A / %x0D) ���� �ո� tab ���� �س�
null	= "null"
false	= "false"
true	= "true"
*/

/*
1. �ɹ���LEPT_PARSE_OK
2. ������
	1) ֻ���հ�LEPT_PARSE_EXPECT_VALUE
	2) һ��ֵ�Ժ󣬿հ�֮���������ַ�LEPT_PARSE_ROOT_NOT_SINGULAR
	3) �������ڴ������������ֵ������LEPT_PARSE_INVALID_VALUE
*/
enum {
	LEPT_PARSE_OK = 0,
	LEPT_PARSE_EXPECT_VALUE,
	LEPT_PARSE_INVALID_VALUE,
	LEPT_PARSE_ROOT_NOT_SINGULAR
};

/*
���ʽ���ĺ�������ʱֻҪ��ȡ����ֵ
*/
lept_type lept_get_type(const lept_value* v);

#endif
