/* --------------------------------------------------------------------------
   Silgy Web App Engine
   Jurek Muszynski
   silgy.com
-----------------------------------------------------------------------------
   General purpose library
-------------------------------------------------------------------------- */

#ifndef SILGY_LIB_H
#define SILGY_LIB_H

#define MAX_URI_VAL_LEN         255             /* max value length received in URI -- sufficient for 99% cases */
#define MAX_LONG_URI_VAL_LEN    65535           /* max long value length received in URI -- 64 kB - 1 B */

#define QSBUF                   MAX_URI_VAL_LEN+1
#define QS_BUF                  QSBUF

#define ALWAYS(s, ...)          log_write(LOG_ALWAYS, s, ##__VA_ARGS__)
#define ERR(s, ...)             log_write(LOG_ERR, s, ##__VA_ARGS__)
#define WAR(s, ...)             log_write(LOG_WAR, s, ##__VA_ARGS__)
#define INF(s, ...)             log_write(LOG_INF, s, ##__VA_ARGS__)
#define DBG(s, ...)             log_write(LOG_DBG, s, ##__VA_ARGS__)

#define QS_HTML_ESCAPE(l, v)    get_qs_param_html_esc(ci, l, v)
#define QS_SQL_ESCAPE(l, v)     get_qs_param_sql_esc(ci, l, v)
#define QS_DONT_ESCAPE(l, v)    get_qs_param(ci, l, v)
#define QS_RAW(l, v)            get_qs_param_raw(ci, l, v, MAX_URI_VAL_LEN)

#ifdef QS_DEF_HTML_ESCAPE
#define QS(l, v)                QS_HTML_ESCAPE(l, v)
#endif
#ifdef QS_DEF_SQL_ESCAPE
#define QS(l, v)                QS_SQL_ESCAPE(l, v)
#endif
#ifdef QS_DEF_DONT_ESCAPE
#define QS(l, v)                QS_DONT_ESCAPE(l, v)
#endif

#define LOREM_IPSUM             "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."

#define PARAM(p)                (0==strcmp(label,p))

/* Query String Value */

typedef char                    QSVAL[QSBUF];
//typedef struct QSVAL          { char x[QSBUF]; } QSVAL;


#ifdef __cplusplus
extern "C" {
#endif
    void lib_get_app_dir(void);
    double lib_elapsed(struct timespec *start);
    long lib_get_memory(void);
    void lib_log_memory(void);
    char *lib_filter_strict(const char *src);
    char *lib_add_spaces(const char *src, int len);
    char *lib_add_lspaces(const char *src, int len);
    void lib_send_ajax_msg(int ci, int errcode);
    char get_res_type(const char *fname);
    void date_str2rec(const char *str, date_t *rec);
    void date_rec2str(char *str, date_t *rec);
    time_t time_http2epoch(const char *str);
    time_t time_db2epoch(const char *str);
    char *time_epoch2http(time_t epoch);
    void lib_set_datetime_formats(const char *lang);
    void amt(char *stramt, long in_amt);
    void amtd(char *stramt, double in_amt);
    void lib_amt(char *stramt, long in_amt);
    void lib_amtd(char *stramt, double in_amt);
    void samts(char *stramt, const char *in_amt);
    void lib_normalize_float(char *str);
    void ftm(char *strtm, long in_tm);
    bool get_qs_param_html_esc(int ci, const char *fieldname, char *retbuf);
    bool get_qs_param_sql_esc(int ci, const char *fieldname, char *retbuf);
    bool get_qs_param(int ci, const char *fieldname, char *retbuf);
    bool get_qs_param_raw(int ci, const char *fieldname, char *retbuf, int maxlen);
    bool get_qs_param_long(int ci, const char *fieldname, char *retbuf);
    bool get_qs_param_multipart_txt(int ci, const char *fieldname, char *retbuf);
    char *get_qs_param_multipart(int ci, const char *fieldname, long *retlen, char *retfname);
    char const *san(const char *str);
    char *san_long(const char *str);
    char *silgy_sql_esc(const char *str);
    char *silgy_html_esc(const char *str);
    char *silgy_html_unesc(const char *str);
    char *uri_encode(const char *str);
    char *upper(const char *str);
    char *stp_right(char *str);
    bool strdigits(const char *src);
    char *nospaces(char *dst, const char *src);
    void silgy_random(char *dest, int len);
    void msleep(long n);
    void get_byteorder(void);
    time_t db2epoch(const char *str);
    bool sendemail(int ci, const char *to, const char *subject, const char *message);
    int silgy_minify(char *dest, const char *src);
    void add_script(int ci, const char *fname, bool first);
    void add_css(int ci, const char *fname, bool first);
    void date_inc(char *str, int days, int *dow);
    int date_cmp(const char *str1, const char *str2);
    bool lib_read_conf(const char *file);
    bool silgy_read_param(const char *param, char *dest);
    char *lib_create_pid_file(const char *name);
	bool lib_shm_create(long bytes);
	void lib_shm_delete(long bytes);
    bool log_start(const char *prefix, bool test);
    void log_write_time(int level, const char *message, ...);
    void log_write(int level, const char *message, ...);
    void log_long(const char *str, long len, const char *desc);
    void log_finish(void);
    char *lib_convert(char *src, const char *cp_from, const char *cp_to);

    int Base64encode_len(int len);
    int Base64encode(char * coded_dst, const char *plain_src,int len_plain_src);
    int Base64decode_len(const char * coded_src);
    int Base64decode(char * plain_dst, const char *coded_src);

#ifdef _WIN32   /* Windows */
    int getpid(void);
    int clock_gettime(int dummy, struct timespec *spec);
#ifndef stpcpy
    char *stpcpy(char *dest, const char *src);
#endif 
#ifndef stpncpy
    char *stpncpy(char *dest, const char *src, int len);
#endif 
#endif  /* _WIN32 */

#ifdef __cplusplus
}   // extern "C"
#endif


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t state[5];
    uint32_t count[2];
    uint8_t  buffer[64];
} SHA1_CTX;

#define SHA1_DIGEST_SIZE 20

void libSHA1(unsigned char *ptr, unsigned int size, unsigned char *outbuf);

void digest_to_hex(const uint8_t digest[SHA1_DIGEST_SIZE], char *output);


#ifdef __cplusplus
}
#endif

#endif  /* SILGY_LIB_H */
