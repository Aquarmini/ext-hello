dnl $Id$
dnl config.m4 for extension example
PHP_ARG_WITH(example, for example support,
[  --with-example[=FILE]       Include example support. File is the optional path to example-config])
PHP_ARG_ENABLE(example-debug, whether to enable debugging support in example,
[  --enable-example-debug        example: Enable debugging support in example], no, no)
PHP_ARG_WITH(example-extra, for extra libraries for example,
[  --with-example-extra=DIR      example: Location of extra libraries for example], no, no)

dnl 检测扩展是否已启用
if test "$PHP_EXAMPLE" != "no"; then

  dnl 检测 example-config。首先尝试所给出的路径，然后在 $PATH 中寻找
  AC_MSG_CHECKING([for example-config])
  EXAMPLE_CONFIG="example-config"
  if test "$PHP_EXAMPLE" != "yes"; then
    EXAMPLE_PATH=$PHP_EXAMPLE
  else
    EXAMPLE_PATH=`$php_shtool path $EXAMPLE_CONFIG`
  fi

  dnl 如果找到可用的 example-config，就使用它
  if test -f "$EXAMPLE_PATH" && test -x "$EXAMPLE_PATH" && $EXAMPLE_PATH --version > /dev/null 2>&1; then
    AC_MSG_RESULT([$EXAMPLE_PATH])
    EXAMPLE_LIB_NAME=`$EXAMPLE_PATH --libname`
    EXAMPLE_INCDIRS=`$EXAMPLE_PATH --incdirs`
    EXAMPLE_LIBS=`$EXAMPLE_PATH --libs`

    dnl 检测扩展库是否工作正常
    PHP_CHECK_LIBRARY($EXAMPLE_LIB_NAME, example_critical_function,
    [
      dnl 添加所需的 include 目录
      PHP_EVAL_INCLINE($EXAMPLE_INCDIRS)
      dnl 添加所需的扩展库及扩展库所在目录
      PHP_EVAL_LIBLINE($EXAMPLE_LIBS, EXAMPLE_SHARED_LIBADD)
    ],[
      dnl 跳出
      AC_MSG_ERROR([example library not found. Check config.log for more information.])
    ],[$EXAMPLE_LIBS]
    )
  else
    dnl 没有可用的 example-config，跳出
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please check your example installation.])
  fi

  dnl 检测是否启用调试
  if test "$PHP_EXAMPLE_DEBUG" != "no"; then
    dnl 是，则设置 C 语言宏指令
    AC_DEFINE(USE_EXAMPLE_DEBUG,1,[Include debugging support in example])
  fi

  dnl 检测额外的支持
  if test "$PHP_EXAMPLE_EXTRA" != "no"; then
    if test "$PHP_EXAMPLE_EXTRA" == "yes"; then
      AC_MSG_ERROR([You must specify a path when using --with-example-extra])
    fi

    PHP_CHECK_LIBRARY(example-extra, example_critical_extra_function,
    [
      dnl 添加所需路径
      PHP_ADD_INCLUDE($PHP_EXAMPLE_EXTRA/include)
      PHP_ADD_LIBRARY_WITH_PATH(example-extra, $PHP_EXAMPLE_EXTRA/lib, EXAMPLE_SHARED_LIBADD)
      AC_DEFINE(HAVE_EXAMPLEEXTRALIB,1,[Whether example-extra support is present and requested])
      EXAMPLE_SOURCES="$EXAMPLE_SOURCES example_extra.c"
    ],[
      AC_MSG_ERROR([example-extra lib not found. See config.log for more information.])
    ],[-L$PHP_EXAMPLE_EXTRA/lib]
    )
  fi

  dnl 最后，将扩展及其所需文件等信息传给构建系统
  PHP_NEW_EXTENSION(example, example.c $EXAMPLE_SOURCES, $ext_shared)
  PHP_SUBST(EXAMPLE_SHARED_LIBADD)
fi