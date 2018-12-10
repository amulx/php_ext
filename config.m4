PHP_ARG_ENABLE(amu, whether to enable amu support,
dnl Make sure that the comment is aligned:
[  --enable-amu          Enable amu support], no)

if test "$PHP_AMU" != "no"; then
  AC_DEFINE(HAVE_AMU, 1, [ Have amu support ])
  PHP_NEW_EXTENSION(amu, amu.c, $ext_shared)
fi