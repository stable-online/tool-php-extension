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
