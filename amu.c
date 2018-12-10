#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_amu.h"

int get_num(char *msg, char *numArr)
{
	if (numArr == NULL)
	{ // 判断是否有分配内存空间
		return 1;
	}
	while (*msg != '\0')
	{ // \0 代表结束符
		if (*msg >= '0' && *msg <= '9')
		{ // 如果是数字就存入数组中
			*numArr = *msg;
			numArr++;
		}
		msg++;
	}
	*numArr = '\0';
	return 0;
}
// 提取一串字符串中包含的数字
PHP_FUNCTION(amu_lx)
{
	// 定义字符串
	size_t len = 0; // 字符串长度
	char *str = NULL;
	// 空数组
	char *numArr = NULL;

	int ret = 0; // 欲定义函数调用返回结果
	int argc = ZEND_NUM_ARGS();

	if (zend_parse_parameters(argc, "s", &str, &len) == FAILURE)
	{
		return;
	}
	numArr = (char *)malloc(sizeof(char) * len);

	if (numArr == NULL)
	{
		return;
	}

	ret = get_num(str, numArr);
	if (ret != 0)
	{
		return;
	}
	zend_string *zstr;
	zstr = strpprintf(0, "%s", numArr);

	RETURN_STR(zstr);
}

PHP_RINIT_FUNCTION(amu)
{
#if defined(ZTS) && defined(COMPILE_DL_AMU)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

PHP_MINFO_FUNCTION(amu)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "amu support", "enabled");
	php_info_print_table_end();
}

/* {{{ amu_functions[]
 */
static const zend_function_entry amu_functions[] = {
	PHP_FE(amu_test2, arginfo_amu_test2)
		PHP_FE(amu_lx, NULL)
			PHP_FE_END};
/* }}} */

/* {{{ amu_module_entry
 */
zend_module_entry amu_module_entry = {
	STANDARD_MODULE_HEADER,
	"amu",			 /* Extension name */
	amu_functions,   /* zend_function_entry */
	NULL,			 /* PHP_MINIT - Module initialization */
	NULL,			 /* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(amu),  /* PHP_RINIT - Request initialization */
	NULL,			 /* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(amu),  /* PHP_MINFO - Module info */
	PHP_AMU_VERSION, /* Version */
	STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_AMU
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(amu)
#endif