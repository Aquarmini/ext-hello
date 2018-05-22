//
// Created by 李铭昕 on 2018/5/22.
//

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
        ZEND_ME(hello, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        ZEND_ME(hello, say, NULL, ZEND_ACC_PUBLIC)
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
        PHP_FOOLSOCK_VERSION, /* Replace with version number for your extension */
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
    /* 注册全局变量 */
//    REGISTER_INI_ENTRIES();
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Hello",hello_methods);

    hello_ce = zend_register_internal_class(&ce TSRMLS_CC);
    return SUCCESS;
}
/* }}} */

/* 模块关闭时调用
*/
PHP_MSHUTDOWN_FUNCTION(hello)
{
    /* 释放全局变量 */
//    UNREGISTER_INI_ENTRIES();

    return SUCCESS;
}

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
PHP_MINFO_FUNCTION(test)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "hello support", "enabled");
    php_info_print_table_end();

    /* 是否输出php.ini中的配置信息
    DISPLAY_INI_ENTRIES();
    */
}

PHP_METHOD(hello,__construct)
{

}

PHP_METHOD(hello,say)
{
    RETURN_TRUE;
}




