/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2006-2011 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Georg Richter <georg@mysql.com>                             |
  |          Andrey Hristov <andrey@mysql.com>                           |
  |          Ulf Wendel <uwendel@mysql.com>                              |
  +----------------------------------------------------------------------+
*/

/* $Id: mysqlnd_priv.h 306939 2011-01-01 02:19:59Z felipe $ */

#ifndef MYSQLND_PRIV_H
#define MYSQLND_PRIV_H

#ifndef Z_ADDREF_P
/* PHP 5.2, old GC */
#define Z_ADDREF_P(pz)				(++(pz)->refcount)
#define Z_DELREF_P(pz)				(--(pz)->refcount)
#define Z_REFCOUNT_P(pz)			((pz)->refcount)
#define Z_SET_REFCOUNT_P(pz, rc)	((pz)->refcount = rc)
#define Z_REFCOUNT_PP(ppz)			Z_REFCOUNT_P(*(ppz))
#define Z_DELREF_PP(ppz)			Z_DELREF_P(*(ppz))
#endif

#if PHP_MAJOR_VERSION >= 6
#define MYSQLND_UNICODE 1
#else
#define MYSQLND_UNICODE 0
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifndef pestrndup
#define pestrndup(s, length, persistent) ((persistent)?zend_strndup((s),(length)):estrndup((s),(length)))
#endif

#define MYSQLND_CLASS_METHOD_TABLE_NAME(class) mysqlnd_##class##_methods
#define MYSQLND_CLASS_METHODS_START(class)	struct st_##class##_methods MYSQLND_CLASS_METHOD_TABLE_NAME(class) = {
#define MYSQLND_CLASS_METHODS_END			}

#if MYSQLND_UNICODE
#define mysqlnd_array_init(arg, field_count) \
{ \
	ALLOC_HASHTABLE_REL(Z_ARRVAL_P(arg));\
	zend_u_hash_init(Z_ARRVAL_P(arg), (field_count), NULL, ZVAL_PTR_DTOR, 0, 0);\
	Z_TYPE_P(arg) = IS_ARRAY;\
}
#else
#define mysqlnd_array_init(arg, field_count) \
{ \
	ALLOC_HASHTABLE_REL(Z_ARRVAL_P(arg));\
	zend_hash_init(Z_ARRVAL_P(arg), (field_count), NULL, ZVAL_PTR_DTOR, 0); \
	Z_TYPE_P(arg) = IS_ARRAY;\
}
#endif


#define MYSQLND_DEBUG_DUMP_TIME				1
#define MYSQLND_DEBUG_DUMP_TRACE			2
#define MYSQLND_DEBUG_DUMP_PID				4
#define MYSQLND_DEBUG_DUMP_LINE				8
#define MYSQLND_DEBUG_DUMP_FILE				16
#define MYSQLND_DEBUG_DUMP_LEVEL			32
#define MYSQLND_DEBUG_APPEND				64
#define MYSQLND_DEBUG_FLUSH					128
#define MYSQLND_DEBUG_TRACE_MEMORY_CALLS	256
#define MYSQLND_DEBUG_PROFILE_CALLS			512


/* Client Error codes */
#define CR_UNKNOWN_ERROR		2000
#define CR_CONNECTION_ERROR		2002
#define CR_SERVER_GONE_ERROR	2006
#define CR_OUT_OF_MEMORY		2008
#define CR_SERVER_LOST			2013
#define CR_COMMANDS_OUT_OF_SYNC	2014
#define CR_CANT_FIND_CHARSET	2019
#define CR_MALFORMED_PACKET		2027
#define CR_NOT_IMPLEMENTED		2054
#define CR_NO_PREPARE_STMT		2030
#define CR_PARAMS_NOT_BOUND		2031
#define CR_INVALID_PARAMETER_NO	2034
#define CR_INVALID_BUFFER_USE	2035

#define MYSQLND_EE_FILENOTFOUND	 7890

#define UNKNOWN_SQLSTATE		"HY000"

#define MAX_CHARSET_LEN			32


#define SET_ERROR_AFF_ROWS(s)	(s)->upsert_status.affected_rows = (uint64_t) ~0

/* Error handling */
#define SET_NEW_MESSAGE(buf, buf_len, message, len, persistent) \
	{\
		if ((buf)) { \
			mnd_pefree((buf), (persistent)); \
		} \
		if ((message)) { \
			(buf) = mnd_pestrndup((message), (len), (persistent)); \
		} else { \
			buf = NULL; \
		} \
		(buf_len) = (len); \
	}

#define SET_EMPTY_MESSAGE(buf, buf_len, persistent) \
	{\
		if ((buf)) { \
			mnd_pefree((buf), (persistent)); \
			(buf) = NULL; \
		} \
		(buf_len) = 0; \
	}


#define SET_EMPTY_ERROR(error_info) \
	{ \
		error_info.error_no = 0; \
		error_info.error[0] = '\0'; \
		strlcpy(error_info.sqlstate, "00000", sizeof(error_info.sqlstate)); \
	}

#define SET_CLIENT_ERROR(error_info, a, b, c) \
	{ \
		error_info.error_no = (a); \
		strlcpy(error_info.sqlstate, (b), sizeof(error_info.sqlstate)); \
		strlcpy(error_info.error, (c), sizeof(error_info.error)); \
	}

#define SET_OOM_ERROR(error_info) SET_CLIENT_ERROR(error_info, CR_OUT_OF_MEMORY, UNKNOWN_SQLSTATE, mysqlnd_out_of_memory)


#define SET_STMT_ERROR(stmt, a, b, c)	SET_CLIENT_ERROR(stmt->error_info, a, b, c)


#ifdef ZTS
#define CONN_GET_STATE(c)		(c)->m->get_state((c) TSRMLS_CC)
#define CONN_SET_STATE(c, s)	(c)->m->set_state((c), (s) TSRMLS_CC)
#else
#define CONN_GET_STATE(c)		((c)->state)
#define CONN_SET_STATE(c, s)	((c)->state = s)
#endif


/* PS stuff */
typedef void (*ps_field_fetch_func)(zval *zv, const MYSQLND_FIELD * const field,
									unsigned int pack_len, zend_uchar **row,
									zend_bool everything_as_unicode TSRMLS_DC);
struct st_mysqlnd_perm_bind {
	ps_field_fetch_func func;
	/* should be signed int */
	int					pack_len;
	unsigned int		php_type;
	zend_bool			is_possibly_blob;
	zend_bool			can_ret_as_str_in_uni;
};

extern struct st_mysqlnd_perm_bind mysqlnd_ps_fetch_functions[MYSQL_TYPE_LAST + 1];

PHPAPI extern const char * const mysqlnd_old_passwd;
PHPAPI extern const char * const mysqlnd_out_of_sync;
PHPAPI extern const char * const mysqlnd_server_gone;
PHPAPI extern const char * const mysqlnd_out_of_memory;

enum_func_status mysqlnd_handle_local_infile(MYSQLND *conn, const char *filename, zend_bool *is_warning TSRMLS_DC);



void _mysqlnd_init_ps_subsystem();/* This one is private, mysqlnd_library_init() will call it */
void _mysqlnd_init_ps_fetch_subsystem();

void ps_fetch_from_1_to_8_bytes(zval *zv, const MYSQLND_FIELD * const field,
								unsigned int pack_len, zend_uchar **row, zend_bool as_unicode,
								unsigned int byte_count TSRMLS_DC);

#endif	/* MYSQLND_PRIV_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
