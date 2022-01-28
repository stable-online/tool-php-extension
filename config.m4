dnl $Id$
dnl config.m4 for extension tools

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(tools, for tools support,
Make sure that the comment is aligned:
[  --with-tools             Include tools support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(tools, whether to enable tools support,
dnl Make sure that the comment is aligned:
dnl [  --enable-tools           Enable tools support])

if test "$PHP_TOOLS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-tools -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/tools.h"  # you most likely want to change this
  dnl if test -r $PHP_TOOLS/$SEARCH_FOR; then # path given as parameter
  dnl   TOOLS_DIR=$PHP_TOOLS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for tools files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TOOLS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TOOLS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the tools distribution])
  dnl fi

  dnl # --with-tools -> add include path
  dnl PHP_ADD_INCLUDE($TOOLS_DIR/include)

  dnl # --with-tools -> check for lib and symbol presence
  dnl LIBNAME=tools # you may want to change this
  dnl LIBSYMBOL=tools # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TOOLS_DIR/$PHP_LIBDIR, TOOLS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TOOLSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong tools lib version or lib not found])
  dnl ],[
  dnl   -L$TOOLS_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TOOLS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(tools, tools.c tool_thread.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
