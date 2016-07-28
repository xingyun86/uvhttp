#ifndef UVHTTP_H__
#define UVHTTP_H__
#include "uvhttp_util.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef void* uvhttp_obj;
typedef void* uvhttp_loop;

typedef enum {
    UVHTTP_SRV_OPT_USER_DATA,
    UVHTTP_SRV_OPT_REQUEST_CB,
    UVHTTP_SRV_OPT_END_CB,
    UVHTTP_SRV_SESSION_OPT_USER_DATA,
    UVHTTP_SRV_SESSION_OPT_READ_CB,
    UVHTTP_SRV_SESSION_OPT_END_CB,
    UVHTTP_CLT_OPT_USER_DATA,
    UVHTTP_CLT_OPT_RESPONSE_CB,
    UVHTTP_CLT_OPT_READ_CB,
    UVHTTP_CLT_OPT_WRITE_CB,
    UVHTTP_CLT_OPT_END_CB
} uvhttp_opt_type;

typedef enum {
    UVHTTP_SRV_INFO_USER_DATA,
    UVHTTP_SRV_INFO_UVTCP,
    UVHTTP_SRV_INFO_LOOP,
    UVHTTP_SESSION_INFO_USER_DATA,
    UVHTTP_SESSION_INFO_UVTCP,
    UVHTTP_SESSION_INFO_LOOP,
    UVHTTP_SESSION_INFO_SRV,
    UVHTTP_CLT_INFO_USER_DATA,
    UVHTTP_CLT_INFO_UVTCP,
    UVHTTP_CLT_INFO_LOOP
} uvhttp_info_type;

//这些可以都通过info获取
struct uvhttp_request{
    struct uvhttp_str method;
    struct uvhttp_str uri;
    struct uvhttp_str proto;
    struct uvhttp_slist* headers;
};

//这些可以都通过info获取
struct uvhttp_response {
    int resp_code;
    struct uvhttp_str resp_status;
    struct uvhttp_slist* headers;
};

typedef void (*uvhttp_request_cb)(
    uvhttp_obj obj,
    struct uvhttp_request* req
    );

typedef void (*uvhttp_read_cb)(
    uvhttp_obj obj,
    struct uv_buf_t data
    );

typedef void (*uvhttp_end_cb)(
    uvhttp_obj obj,
    int status
    );

typedef void (*uvhttp_write_cb)(
    uvhttp_obj obj
    );

typedef void (*uvhttp_response_cb)(
    uvhttp_obj obj,
    struct uvhttp_response* resp
    );

int uvhttp_obj_setopt( 
    uvhttp_obj obj,
    uvhttp_opt_type opt_type,
    ...
    );

int uvhttp_obj_getinfo( 
    uvhttp_obj obj,
    uvhttp_info_type info_type,
    ...
    );

uvhttp_loop uvhttp_loop_new( );

void uvhttp_loop_delete( 
    uvhttp_loop loop
    );

int uvhttp_run( 
    uvhttp_loop loop
    );

void uvhttp_stop(
    uvhttp_loop loop
    );

uvhttp_obj uvhttp_srv_new(
    uvhttp_loop loop
    );

void uvhttp_srv_delete(
    uvhttp_obj obj
    );

int uvhttp_srv_listen(
    uvhttp_obj obj,
    int port
    );

int uvhttp_srv_abort(
    uvhttp_obj obj
    );

int uvhttp_srv_session_abort(
    uvhttp_obj obj
    );

uvhttp_obj uvhttp_clt_new(
    uvhttp_loop loop
    );

struct uvhttp_slist* uvhttp_slist_append(
    struct uvhttp_slist* list, const char* string
    );

void uvhttp_slist_free_all( 
    struct uvhttp_slist* list
    );

    //需要修改为setoption方式填入参数
int uvhttp_clt_request(
    uvhttp_obj obj
    );

void uvhttp_clt_delete(
    uvhttp_obj obj
    );

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif // UVHTTP_H__