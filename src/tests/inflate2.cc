/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// vim: ft=cpp:expandtab:ts=8:sw=4:softtabstop=4:
#ident "$Id$"
#ident "Copyright (c) 2007-2012 Tokutek Inc.  All rights reserved."
#ident "The technology is licensed by the Massachusetts Institute of Technology, Rutgers State University of New Jersey, and the Research Foundation of State University of New York at Stony Brook under United States of America Serial No. 11/760379 and to the patents and/or patent applications resulting from it."

/* Idea: inflate a node by 
 *    create a 2-level tree
 *    Nodes are A B C D E F G H
 *    Fill them up sequentially so they'll all be near 4MB.
 *    Close the file
 *    Insert some more to H (buffered in the root)
 *    Delete stuff from G (so that H merges with G)
 *    G ends up too big (but it's not the merge)
 */

#include "test.h"

DB_ENV *env;
DB *db;
const char dbname[] = "foo.db";
const int envflags = DB_INIT_MPOOL|DB_CREATE|DB_THREAD |DB_INIT_LOCK|DB_INIT_LOG|DB_PRIVATE|DB_INIT_TXN;

static void
open_em (void)
{
    int r;
    r = db_env_create(&env, 0);                                         CKERR(r);
    r = env->open(env, ENVDIR, envflags, S_IRWXU+S_IRWXG+S_IRWXO);      CKERR(r);
    r = db_create(&db, env, 0);                                         CKERR(r);
    r = db->open(db, NULL, dbname, NULL, DB_BTREE, DB_CREATE, 0666);    CKERR(r);
}

static void
close_em (void)
{
    int r;
    r = db->close(db, 0);   CKERR(r);
    r = env->close(env, 0); CKERR(r);
}

static void
reopen_em (void)
{
    close_em();
    open_em();
}


static void
setup(void)
{
    int r;
    r = system("rm -rf " ENVDIR);
    CKERR(r);
    toku_os_mkdir(ENVDIR, S_IRWXU+S_IRWXG+S_IRWXO);
    r = db_env_create(&env, 0);                                         CKERR(r);
    r = env->open(env, ENVDIR, envflags, S_IRWXU+S_IRWXG+S_IRWXO);      CKERR(r);
    r = db_create(&db, env, 0);                                         CKERR(r);
    r = db->set_pagesize(db, 8192);                                     CKERR(r);
    r = db->open(db, NULL, dbname, NULL, DB_BTREE, DB_CREATE, 0666);    CKERR(r);
}

char  vdata[150];

static void
insert_n (uint32_t ah) {
    uint32_t an = htonl(ah);
    DBT key;
    dbt_init(&key, &an, 4);
    DBT val;
    dbt_init(&val, vdata, sizeof vdata);
    int r = db->put(db, NULL, &key, &val, 0);
    CKERR(r);
}

static void
get_n (uint32_t ah, int expect_r)
{
    uint32_t an = htonl(ah);
    DBT key;
    dbt_init(&key, &an, 4);
    DBT val;
    dbt_init_malloc(&val);
    int r = db->get(db, NULL, &key, &val, 0);
    assert(r==expect_r);
    if (r==0) toku_free(val.data);
}


static void
delete_n_now (uint32_t ah)
{
    uint32_t an = htonl(ah);
    DBT key;
    dbt_init(&key, &an, 4);
    int r = db->del(db, NULL, &key, DB_DELETE_ANY);
#ifdef USE_BDB
    assert(r==0 || r==DB_NOTFOUND);
#else
    CKERR(r);
#endif
    get_n(ah, DB_NOTFOUND);
}

static void
doit (void)
{
    uint32_t N=46;
    uint32_t BIG=1<<16;
    for (uint32_t i=0; i<2*N; i++) {
	insert_n(i<<8);
    }
    insert_n(BIG);
    insert_n(BIG+1);
    reopen_em();
    for (uint32_t i=0; i<N; i++) {
	insert_n((2*N+i)<<8);
    }
    delete_n_now(BIG+1);
    reopen_em();
    for (uint32_t i=0; i<N; i++) {
	insert_n((48<<8) + i);
    }
    insert_n((48<<8) + N);
    return;
}

int test_main (int argc __attribute__((__unused__)), char * const argv[] __attribute__((__unused__))) {
    setup();
    doit();
    close_em();
    return 0;
}