Id$
dnl config.m4 for extension hello

PHP_ARG_ENABLE(hello, for hello support,
[  --enable-hello            Include hello support])

dnl Check whether the extension is enabled at all
if test "$PHP_HELLO" != "no"; then
  dnl Finally, tell the build system about the extension and what files are needed
  PHP_NEW_EXTENSION(hello, hello.c, $ext_shared)
  PHP_SUBST(HELLO_SHARED_LIBADD)
fi