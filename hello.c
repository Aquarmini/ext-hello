#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_hello.h"

zend_class_entry *hello_ce;

const zend_function_entry hello_functions[] = {
        PHP_FE_END     /* Must be the last line in test_functions[] */
};

const zend_function_entry hello_methods[] = {
    ZEND_ME(hello, __construct, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(hello, rTrue, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(hello, rInt, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(hello, rString, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(hello, hi, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END	/* Must be the last line in foolconf_functions[] */
};

/*
 * 模块结构，声明了startup\shutdown、模块名及phpinfo打印时的函数
 */
zend_module_entry hello_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
        STANDARD_MODULE_HEADER,
#endif
        "hello",
        hello_functions,
        PHP_MINIT(hello),
        PHP_MSHUTDOWN(hello),
        PHP_RINIT(hello),          /* Replace with NULL if there's nothing to do at request start */
        PHP_RSHUTDOWN(hello),     /* Replace with NULL if there's nothing to do at request end */
        PHP_MINFO(hello),
#if ZEND_MODULE_API_NO >= 20010901
        PHP_HELLO_VERSION, /* Replace with version number for your extension */
#endif
        STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_HELLO
ZEND_GET_MODULE(hello)
#endif

/** {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(hello)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Hello",hello_methods);

    hello_ce = zend_register_internal_class(&ce TSRMLS_CC);
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(hello)
{
    return SUCCESS;
}
/* }}} */

/* 每次请求前调用
*/
PHP_RINIT_FUNCTION(hello)
{
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(hello)
{
    return SUCCESS;
}

/* phpinfo()输出扩展信息
*/
PHP_MINFO_FUNCTION(hello)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "hello support", "enabled");
    php_info_print_table_end();
}

PHP_METHOD(hello,__construct)
{

}

PHP_METHOD(hello,rTrue)
{
    RETURN_TRUE;
}

PHP_METHOD(hello,rString)
{
    char *str="hello world!";

    RETURN_STRING(str);
}

PHP_METHOD(hello,rInt)
{
    RETURN_LONG(11521);
}

PHP_METHOD(hello, hi)
{
   zend_string *name,*result;

   #ifndef FAST_ZPP
       /* Get function parameters and do error-checking. */
       if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &name) == FAILURE) {
           return;
       }
   #else
       ZEND_PARSE_PARAMETERS_START(1, 1)
           Z_PARAM_STR(name)
       ZEND_PARSE_PARAMETERS_END();
   #endif

   result = strpprintf(0, "hi, %s!", ZSTR_VAL(name));
   RETURN_STR(result);
}




