/*
   Copyright (c) 2001, 2012, Oracle and/or its affiliates.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

/* Common defines for all clients */

#include <my_global.h>
#include <my_sys.h>
#include <m_string.h>
#include <mysql.h>
#include <errmsg.h>
#include <my_getopt.h>

#ifndef WEXITSTATUS
# ifdef __WIN__
#  define WEXITSTATUS(stat_val) (stat_val)
# else
#  define WEXITSTATUS(stat_val) ((unsigned)(stat_val) >> 8)
# endif
#endif

enum options_client
{
  OPT_CHARSETS_DIR=256, OPT_DEFAULT_CHARSET,
  OPT_PAGER, OPT_TEE,
  OPT_LOW_PRIORITY, OPT_AUTO_REPAIR, OPT_COMPRESS,
  OPT_DROP, OPT_LOCKS, OPT_KEYWORDS, OPT_DELAYED, OPT_OPTIMIZE,
  OPT_FTB, OPT_LTB, OPT_ENC, OPT_O_ENC, OPT_ESC, OPT_TABLES,
  OPT_MASTER_DATA, OPT_AUTOCOMMIT, OPT_AUTO_REHASH,
  OPT_LINE_NUMBERS, OPT_COLUMN_NAMES, OPT_CONNECT_TIMEOUT,
  OPT_MAX_ALLOWED_PACKET, OPT_NET_BUFFER_LENGTH,
  OPT_SELECT_LIMIT, OPT_MAX_JOIN_SIZE, OPT_SSL_SSL,
  OPT_SSL_KEY, OPT_SSL_CERT, OPT_SSL_CA, OPT_SSL_CAPATH,
  OPT_SSL_CIPHER, OPT_SHUTDOWN_TIMEOUT, OPT_LOCAL_INFILE,
  OPT_DELETE_MASTER_LOGS, OPT_COMPACT,
  OPT_PROMPT, OPT_IGN_LINES,OPT_TRANSACTION,OPT_MYSQL_PROTOCOL,
  OPT_SHARED_MEMORY_BASE_NAME, OPT_FRM, OPT_SKIP_OPTIMIZATION,
  OPT_COMPATIBLE, OPT_RECONNECT, OPT_DELIMITER, OPT_SECURE_AUTH,
  OPT_OPEN_FILES_LIMIT, OPT_SET_CHARSET, OPT_SERVER_ARG,
  OPT_STOP_POSITION, OPT_START_DATETIME, OPT_STOP_DATETIME,
  OPT_SIGINT_IGNORE, OPT_HEXBLOB, OPT_ORDER_BY_PRIMARY, OPT_COUNT,
  OPT_FLUSH_TABLES,
  OPT_TRIGGERS,
  OPT_MYSQL_ONLY_PRINT,
  OPT_MYSQL_LOCK_DIRECTORY,
  OPT_USE_THREADS,
  OPT_IMPORT_USE_THREADS,
  OPT_MYSQL_NUMBER_OF_QUERY,
  OPT_IGNORE_TABLE,OPT_INSERT_IGNORE,OPT_SHOW_WARNINGS,OPT_DROP_DATABASE,
  OPT_TZ_UTC, OPT_CREATE_SLAP_SCHEMA,
  OPT_MYSQLDUMP_SLAVE_APPLY,
  OPT_MYSQLDUMP_SLAVE_DATA,
  OPT_MYSQLDUMP_INCLUDE_MASTER_HOST_PORT,
  OPT_SLAP_CSV, OPT_SLAP_CREATE_STRING,
  OPT_SLAP_AUTO_GENERATE_SQL_LOAD_TYPE, OPT_SLAP_AUTO_GENERATE_WRITE_NUM,
  OPT_SLAP_AUTO_GENERATE_ADD_AUTO,
  OPT_SLAP_AUTO_GENERATE_GUID_PRIMARY,
  OPT_SLAP_AUTO_GENERATE_EXECUTE_QUERIES,
  OPT_SLAP_AUTO_GENERATE_SECONDARY_INDEXES,
  OPT_SLAP_AUTO_GENERATE_UNIQUE_WRITE_NUM,
  OPT_SLAP_AUTO_GENERATE_UNIQUE_QUERY_NUM,
  OPT_SLAP_PRE_QUERY,
  OPT_SLAP_POST_QUERY,
  OPT_SLAP_PRE_SYSTEM,
  OPT_SLAP_POST_SYSTEM,
  OPT_SLAP_COMMIT,
  OPT_SLAP_DETACH,
  OPT_SLAP_NO_DROP,
  OPT_MYSQL_REPLACE_INTO, OPT_BASE64_OUTPUT_MODE, OPT_SERVER_ID,
  OPT_FIX_TABLE_NAMES, OPT_FIX_DB_NAMES, OPT_SSL_VERIFY_SERVER_CERT,
  OPT_AUTO_VERTICAL_OUTPUT,
  OPT_DEBUG_INFO, OPT_DEBUG_CHECK, OPT_COLUMN_TYPES, OPT_ERROR_LOG_FILE,
  OPT_WRITE_BINLOG, OPT_DUMP_DATE,
  OPT_INIT_COMMAND,
  OPT_PLUGIN_DIR,
  OPT_DEFAULT_AUTH,
  OPT_ABORT_SOURCE_ON_ERROR,
  OPT_REWRITE_DB,
  OPT_REPORT_PROGRESS,
  OPT_SKIP_ANNOTATE_ROWS_EVENTS,
  OPT_MAX_CLIENT_OPTION /* should be always the last */
};

/**
  First mysql version supporting the information schema.
*/
#define FIRST_INFORMATION_SCHEMA_VERSION 50003

/**
  Name of the information schema database.
*/
#define INFORMATION_SCHEMA_DB_NAME "information_schema"

/**
  First mysql version supporting the performance schema.
*/
#define FIRST_PERFORMANCE_SCHEMA_VERSION 50503

/**
  Name of the performance schema database.
*/
#define PERFORMANCE_SCHEMA_DB_NAME "performance_schema"

