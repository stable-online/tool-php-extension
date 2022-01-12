/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: 赵巍
  | email: 2426595849@qq.com
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_tools.h"
#include "tool_lib.c"
#include "ext/standard/php_string.h"

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("tools.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_tools_globals, tools_globals)
    STD_PHP_INI_ENTRY("tools.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_tools_globals, tools_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_tools_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_tools_init_globals(zend_tools_globals *tools_globals)
{
	tools_globals->global_value = 0;
	tools_globals->global_string = NULL;
}
*/
/* }}} */
zend_function_entry string_function[] = {
        ZEND_ME(String, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        ZEND_ME(String, dd, NULL, ZEND_ACC_PUBLIC)
        ZEND_ME(String, substr, NULL, ZEND_ACC_PUBLIC)
        ZEND_FE_END
};

zend_class_entry *String_Object_Tools;

ZEND_METHOD(String, __construct) {
    zend_string *string;
    int len;
    ZEND_PARSE_PARAMETERS_START(1, 1);
            Z_PARAM_STR(string);
    ZEND_PARSE_PARAMETERS_END();
    zend_update_property_string(String_Object_Tools, getThis(), "property", sizeof("property") - 1, ZSTR_VAL(string));
}

/**
 * print string
 * @param execute_data
 * @param return_value
 */
ZEND_METHOD(String, dd){
    zval *Object = getThis();
    zval *msg = stringProperty(Object,"property",sizeof("property")-1);
    RETVAL_STR(Z_STR_P(msg));
}

/**
 * get current property value from object
 * @param object
 * @return
 */
zval *stringProperty(zval *object,char method[],size_t len) {
    zval *msg, rv;
    msg = zend_read_property(Z_OBJCE_P(object), object, method, len, 0, &rv);
    return msg;
}

ZEND_METHOD(String, substr) {
    zend_long  start;
    zend_long  end;

    ZEND_PARSE_PARAMETERS_START(1,2);
        Z_PARAM_LONG(start)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(end)
    ZEND_PARSE_PARAMETERS_END();

    zval tmp_soap;
    object_init_ex(&tmp_soap, String_Object_Tools);

    zval *Object = getThis();
    zval *msg = stringProperty(Object,"property",sizeof("property")-1);
    zend_string *property = Z_STR_P(msg);

    zval c_ret, constructor, parameter,substr,c_ret_2,param[3];
    zend_string *result = strpprintf(0, "%s", property->val);

    ZVAL_STRING(&param[0],property->val);
    ZVAL_LONG(&param[1],start);
    ZVAL_LONG(&param[2],end);
    ZVAL_STRING(&substr,"substr");

    call_user_function_ex(EG(function_table), NULL,&substr, &c_ret_2, 3, param, 1,NULL);

    ZVAL_STRING(&parameter, c_ret_2.value.str->val);
    ZVAL_STRING(&constructor, ZEND_CONSTRUCTOR_FUNC_NAME);
    call_user_function(NULL, &tmp_soap, &constructor, &c_ret, 1, &parameter);

    RETURN_OBJ(Z_OBJ_P(&tmp_soap));
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION (tools) {
    //String tools
    zend_class_entry String_Object;
    INIT_CLASS_ENTRY(String_Object, "String", string_function);
    String_Object_Tools = zend_register_internal_class(&String_Object);
    zend_declare_property_string(String_Object_Tools, "property", sizeof("property") - 1, "", ZEND_ACC_PRIVATE);

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION (tools) {
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION (tools) {
#if defined(COMPILE_DL_TOOLS) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION (tools) {
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION (tools) {
    php_info_print_table_start();
    php_info_print_table_header(2, "tools support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */

/* {{{ tools_functions[]
 *
 * Every user visible function must have an entry in tools_functions[].
 */
const zend_function_entry tools_functions[] = {
        PHP_FE_END    /* Must be the last line in tools_functions[] */
};
/* }}} */

/* {{{ tools_module_entry
 */
zend_module_entry tools_module_entry = {
        STANDARD_MODULE_HEADER,
        "tools",
        tools_functions,
        PHP_MINIT(tools),
        PHP_MSHUTDOWN(tools),
        PHP_RINIT(tools),        /* Replace with NULL if there's nothing to do at request start */
        PHP_RSHUTDOWN(tools),    /* Replace with NULL if there's nothing to do at request end */
        PHP_MINFO(tools),
        PHP_TOOLS_VERSION,
        STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TOOLS
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(tools)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
