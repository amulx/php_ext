/* amu extension for PHP */

#ifndef PHP_AMU_H
# define PHP_AMU_H

extern zend_module_entry amu_module_entry;
# define phpext_amu_ptr &amu_module_entry

# define PHP_AMU_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_AMU)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_AMU_H */

