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
#include <unistd.h>
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
struct parameter {
    zval *return_value;
    zend_array *arrays;
    zval *result;
    zend_fcall_info *fci;
    zend_fcall_info_cache *fci_cache;
};
/**
 *
 * @param execute_data
 * @param return_value
 */
void execute_run(struct parameter *parameter);

/**
 *
 * @param return_value
 * @param arrays
 * @param result
 * @param fci
 * @param fci_cache
 */
void execute_run(struct parameter *parameter) {
    zend_array *arrays = parameter->arrays;
    zval *return_value = parameter->return_value;
    zval *result = parameter->result;
    zend_fcall_info *fci = parameter->fci;
    zend_fcall_info_cache *fci_cache = parameter->fci_cache;

    zend_ulong num_key;
    zend_string *str_key;
    zval *zv, arg;

    ZEND_HASH_FOREACH_KEY_VAL(arrays, num_key, str_key, zv)
            {
                (*fci).retval = result;
                (*fci).param_count = 1;
                (*fci).params = &arg;
                (*fci).no_separation = 0;

                ZVAL_COPY(&arg, zv);

                if (zend_call_function(fci, fci_cache) != SUCCESS || Z_TYPE((*result)) == IS_UNDEF) {
                    zval_dtor(return_value);
                    zval_ptr_dtor(&arg);
                    RETURN_NULL();
                } else {
                    zval_ptr_dtor(&arg);
                }

                if (str_key) {
                    zend_hash_add_new(Z_ARRVAL_P(return_value), str_key, result);
                } else {
                    zend_hash_index_add_new(Z_ARRVAL_P(return_value), num_key, result);
                }

            }ZEND_HASH_FOREACH_END();
}

PHP_FUNCTION(thread_run) {

    zval *arrays = NULL;
    int n_arrays = 0;
    zval result;

    zend_long thread_number = 0 ;

    zend_fcall_info fci = empty_fcall_info;
    zend_fcall_info_cache fci_cache = empty_fcall_info_cache;
    uint32_t k;

    ZEND_PARSE_PARAMETERS_START(2, -1)
            Z_PARAM_FUNC_EX(fci, fci_cache, 1, 0)
            Z_PARAM_LONG(thread_number)
            Z_PARAM_VARIADIC('+', arrays, n_arrays)
    ZEND_PARSE_PARAMETERS_END();

    RETVAL_NULL();

    if (Z_TYPE(arrays[0]) != IS_ARRAY) {
        php_error_docref(NULL, E_WARNING, "Argument #%d should be an array", 2);
        return;
    }

    /* Short-circuit: if no callback and only one array, just return it. */
    if (!ZEND_FCI_INITIALIZED(fci)) {
        ZVAL_COPY(return_value, &arrays[0]);
        return;
    }

    zend_array *pArray = Z_ARRVAL_P(arrays);
    int count = zend_array_count(pArray);
    array_init_size(return_value, zend_hash_num_elements(Z_ARRVAL(arrays[0])));
    int number = ceil(count/thread_number);

    pthread_t thread[thread_number-1];

    for (int j = 0; j < thread_number; ++j) {

        zval array,param[4];

        zval *c_ret_2 = emalloc(sizeof(zval)-1);
        ZVAL_STRING(&array, "array_slice");
        ZVAL_ARR(&param[0], pArray);
        ZVAL_LONG(&param[1], j * number);
        ZVAL_LONG(&param[2], number);
        ZVAL_STRING(&param[3], "true");

        if (call_user_function(NULL, NULL, &array, c_ret_2, 4, param) == FAILURE) {
            php_printf("error{1}");
        }

        zval_dtor(&array);
        zval_dtor(&param[1]);
        zval_dtor(&param[2]);
        zend_array *arraysss = Z_ARRVAL_P(c_ret_2);

        struct parameter *parameter_info = emalloc(sizeof(struct parameter));
        parameter_info->return_value = return_value;
        parameter_info->arrays = arraysss;
        parameter_info->result = &result;
        parameter_info->fci = &fci;
        parameter_info->fci_cache = &fci_cache;

        int ret_thrd1 = pthread_create(&thread[j], NULL, (void *) &execute_run, (void *) parameter_info);
        if (ret_thrd1 != 0) {
            printf("线程1创建失败\n");
        } else {
            printf("线程%d创建成功\n",j);
        }
    }

    for (int i = 0;i  < thread_number; ++i) {
        int tmp1;
        void *retval;
        tmp1 = pthread_join(thread[i], &retval);
        if (tmp1 != 0) {
            printf("cannot join with thread1\n");
        }
    }

    efree(pArray);
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
