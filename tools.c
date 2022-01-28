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
  | Author: zhaowei
  | email:  2426595849@qq.com
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
#include "ext/standard/php_string.h"
#include "tool_string.c"
#include "tool_thread.c"
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

        //region String Class
        ZEND_ME(String, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        ZEND_ME(String, value, NULL, ZEND_ACC_PUBLIC)
        ZEND_ME(String, substr, NULL, ZEND_ACC_PUBLIC)
        ZEND_ME(String, replace, NULL, ZEND_ACC_PUBLIC)
        ZEND_ME(String, insert_tail, NULL, ZEND_ACC_PUBLIC)
        ZEND_ME(String, insert_head, NULL, ZEND_ACC_PUBLIC)
        ZEND_ME(String, lower, NULL, ZEND_ACC_PUBLIC)
        ZEND_ME(String, upper, NULL, ZEND_ACC_PUBLIC)
        //endregion
        ZEND_FE_END
};


zend_class_entry *String_Object_Tools;

ZEND_METHOD(String, upper) {
    zval rv;
    zend_class_entry *ce;
    ce = Z_OBJCE_P(getThis());
    zval c_ret, constructor, parameter;
    zval *pStructProperty = zend_read_property(ce, getThis(), "property", strlen("property"), 1, &rv);

    zend_string *pString = strtoupper(pStructProperty);

    zval_dtor(pStructProperty);
    zend_update_property_string(ce, getThis(), "property", strlen("property"), pString->val TSRMLS_CC);

    efree(pString);
    RETURN_OBJ(zend_objects_clone_obj(getThis()));
}

ZEND_METHOD(String, lower) {
    zval rv;
    zend_class_entry *ce;
    ce = Z_OBJCE_P(getThis());
    zval c_ret, constructor, parameter;

    zval *pStruct = zend_read_property(ce, getThis(), "property", strlen("property"), 1, &rv);
    zend_string *string = zval_get_string(pStruct);
    zval_dtor(pStruct);

    zend_string *pString = strtolower(string);
    zend_update_property_string(ce, getThis(), "property", strlen("property"), pString->val TSRMLS_CC);

    efree(pString);
    RETURN_OBJ(zend_objects_clone_obj(getThis()));
}

/**
 * __construct
 * @param execute_data
 * @param return_value
 */
ZEND_METHOD(String, __construct) {
    zval *string;
    int len;

    ZEND_PARSE_PARAMETERS_START(1, 1);
            Z_PARAM_ZVAL(string);
    ZEND_PARSE_PARAMETERS_END();

    if (Z_TYPE_P(string) != IS_STRING) {
        php_error(E_ERROR, "parameter must is string");
    }

    zend_update_property_string(String_Object_Tools, getThis(), "property", strlen("property"), Z_STRVAL_P(string));
}

/**
 * print string
 * @param execute_data
 * @param return_value
 */
ZEND_METHOD(String, value) {
    zval *msg, rv;
    zval *object = getThis();

    zend_class_entry *ce;
    ce = Z_OBJCE_P(getThis());
    zend_string *string = zval_get_string(zend_read_property(ce, getThis(), "property", strlen("property"), 1, &rv));

    RETURN_STR(string);
}

ZEND_METHOD(String, replace) {

    zend_string *search;
    zend_string *replace;
    zval rv;
    zend_class_entry *ce;
    ce = Z_OBJCE_P(getThis());
    zval c_ret, constructor, parameter;

    ZEND_PARSE_PARAMETERS_START(2, 2)
            Z_PARAM_STR(search)
            Z_PARAM_STR(replace)
    ZEND_PARSE_PARAMETERS_END();

    zval *pStructProperty = zend_read_property(ce, getThis(), "property", strlen("property"), 1, &rv);
    zend_string *string = zval_get_string(pStructProperty);
    zval_dtor(pStructProperty);

    zend_string *pString = str_replace(search, replace, string);
    zend_update_property_string(ce, getThis(), "property", strlen("property"), pString->val TSRMLS_CC);
    efree(pString);

    RETURN_OBJ(zend_objects_clone_obj(getThis()));
}

ZEND_METHOD(String, insert_tail) {

    zend_string *user_string;

    zval rv;
    zend_class_entry *ce;
    ce = Z_OBJCE_P(getThis());
    zval c_ret, constructor, parameter;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(user_string)
    ZEND_PARSE_PARAMETERS_END();

    zval substr, c_ret_2, param[3];
    zval *pStruct = zend_read_property(ce, getThis(), "property", strlen("property"), 1, &rv);

    zend_string *pString = insert_tail(user_string, pStruct);

    zend_update_property_string(ce, getThis(), "property", strlen("property"), pString->val TSRMLS_CC);
    efree(pString);
    RETURN_OBJ(zend_objects_clone_obj(getThis()));
}

ZEND_METHOD(String, insert_head) {
    zend_string *user_string;

    zval rv;
    zend_class_entry *ce;
    ce = Z_OBJCE_P(getThis());
    zval c_ret, constructor, parameter;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(user_string)
    ZEND_PARSE_PARAMETERS_END();

    zval *pStruct = zend_read_property(ce, getThis(), "property", strlen("property"), 1, &rv);
    zend_string *string = zval_get_string(pStruct);
    zval_dtor(pStruct);

    zend_string *pString = insert_head(user_string, string);

    zend_update_property_string(ce, getThis(), "property", strlen("property"), pString->val TSRMLS_CC);
    efree(pString);
    RETURN_OBJ(zend_objects_clone_obj(getThis()));
}

ZEND_METHOD(String, substr) {
    zend_long start;
    zend_long end;
    zval rv;
    zend_class_entry *ce;
    ce = Z_OBJCE_P(getThis());
    zval c_ret, constructor, parameter;

    ZEND_PARSE_PARAMETERS_START(1, 2);
            Z_PARAM_LONG(start)
            Z_PARAM_OPTIONAL
            Z_PARAM_LONG(end)
    ZEND_PARSE_PARAMETERS_END();

    zval *pStruct = zend_read_property(ce, getThis(), "property", strlen("property"), 1, &rv);
    zend_string *string = zval_get_string(pStruct);
    zval_dtor(pStruct);

    zend_string *pString = substr(start, end, string);

    zend_update_property_string(ce, getThis(), "property", strlen("property"), pString->val TSRMLS_CC);

    efree(pString);
    RETURN_OBJ(zend_objects_clone_obj(getThis()));
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION (tools) {
    //String tools
    zend_class_entry String_Object;
    INIT_CLASS_ENTRY(String_Object, "String", string_function);
    String_Object_Tools = zend_register_internal_class(&String_Object);
    zend_declare_property_string(String_Object_Tools, "property", strlen("property"), "", ZEND_ACC_PRIVATE);

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
/**
 *
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (thread_run) {
    zend_long number;
    ZEND_PARSE_PARAMETERS_START(1,1);
        Z_PARAM_LONG(number);
    ZEND_PARSE_PARAMETERS_END();
    run(number);
//    zend_string *str = zend_string_init("hello world");
    RETVAL_STRING("hello world");
}

/* {{{ tools_functions[]
 *
 * Every user visible function must have an entry in tools_functions[].
 */
const zend_function_entry tools_functions[] = {
        PHP_FE(thread_run, NULL)
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
