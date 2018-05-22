#define PHP_HELLO_VERSION "0.0.1" /* Replace with version number for your extension */

PHP_MINIT_FUNCTION(hello);
PHP_MSHUTDOWN_FUNCTION(hello);
PHP_RINIT_FUNCTION(hello);
PHP_RSHUTDOWN_FUNCTION(hello);
PHP_MINFO_FUNCTION(hello);

PHP_METHOD(hello,__construct);
PHP_METHOD(hello,say);