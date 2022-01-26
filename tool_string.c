//
// Created by zhaowei on 2022/1/26.
//

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_tools.h"
#include "ext/standard/php_string.h"

/**
 * take string exchange to uppercase character
 * @param execute_data
 * @param return_value
 */
zend_string *strtoupper(zval *pStruct);

/**
 * 转化字符串
 * @param pStruct
 * @return
 */
zend_string *strtoupper(zval *pStruct) {
    zend_string *string = zval_get_string(pStruct);
    zval strtoupper,c_ret_2, param[1];
    ZVAL_STRING(&param[0], string->val);
    ZVAL_STRING(&strtoupper, "strtoupper");
    if (call_user_function(NULL, NULL, &strtoupper, &c_ret_2, 1, param) == FAILURE) {
        php_printf("error{1}");
    }
    zval_dtor(&strtoupper);
    zval_dtor(&param[0]);
    zend_string *pString = zval_get_string(&c_ret_2);
    zval_dtor(&c_ret_2);
    return pString;
}

/**
 * take string exchange to Lowercase character
 * @param execute_data
 * @param return_value
 */
zend_string *strtolower(const zend_string *string);


zend_string *strtolower(const zend_string *string) {
    zval strtolower, c_ret_2, param[1];
    ZVAL_STRING(&param[0], string->val);
    ZVAL_STRING(&strtolower, "strtolower");

    if (call_user_function(NULL, NULL, &strtolower, &c_ret_2, 1, param) == FAILURE) {
        php_printf("error{1}");
    }

    zval_dtor(&strtolower);
    zval_dtor(&param[0]);
    zend_string *pString = zval_get_string(&c_ret_2);
    zval_dtor(&c_ret_2);
    return pString;
}

/**
 * string replace behavior
 * @param execute_data
 * @param return_value
 */
zend_string *str_replace(const zend_string *search, const zend_string *replace, const zend_string *string);


zend_string *str_replace(const zend_string *search, const zend_string *replace, const zend_string *string) {
    zval substr, c_ret_2, param[3];
    ZVAL_STRING(&param[0], search->val);
    ZVAL_STRING(&param[1], replace->val);
    ZVAL_STRING(&param[2], string->val);
    ZVAL_STRING(&substr, "str_replace");

    if (call_user_function(NULL, NULL, &substr, &c_ret_2, 3, param) == FAILURE) {
        php_printf("error{1}");
    }
    zval_dtor(&substr);
    zval_dtor(&param[0]);
    zval_dtor(&param[1]);
    zval_dtor(&param[2]);
    zend_string *pString = zval_get_string(&c_ret_2);
    zval_dtor(&c_ret_2);
    return pString;
}


/**
 * string append behavior
 * @param execute_data
 * @param return_value
 */
zend_string *insert_tail( zend_string *user_string,  zval *pStruct);

zend_string *insert_tail( zend_string *user_string,  zval *pStruct) {
    zend_string *string = zval_get_string(pStruct);
    zval_dtor(pStruct);
    zend_string *pString = strpprintf(0, "%s%s", string->val, user_string->val);
    return pString;
}