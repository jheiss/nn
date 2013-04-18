#include <stdlib.h>
#include "config.h"
#include "global.h"
#include "execute.h"

/* prefix.c */

static void     make_nn_prefix(int flag, FILE * f);


extern char    *home_directory;
extern char    *news_directory;
extern char    *news_lib_directory;
extern char    *master_directory;
extern char    *help_directory;
extern char    *bin_directory;
extern char    *db_directory;
extern char    *db_data_directory;
extern char    *tmp_directory;
extern char    *log_file;

#define SHELL_PREFIX	0x01
#define FULL_PREFIX	0x02
#define CONF_PREFIX	0x04

static void
make_nn_prefix(int flag, FILE * f)
{
    char            nl;

    nl = (flag & CONF_PREFIX) ? TAB : NL;

    if (flag & SHELL_PREFIX) {

#ifdef AVOID_SHELL_EXEC
	fprintf(f, ":\n");
#else
	fprintf(f, "#!%s\n", SHELL);
#endif

#ifdef PUT_TIMESTAMP_IN_SCRIPTS
	fprintf(f, "\n# Generated by nn release %s at %s\n\n",
		version_id, date_time((time_t) 0));
#else
	fprintf(f, "\n# Generated by nn release %s\n\n", version_id);
#endif
    }
    fprintf(f, "VERSION=\"%s\"\n", version_id);

#ifndef OLD_AWK
#define OLD_AWK "awk"
#endif

    fprintf(f, "AWK=\"%s\"\n", OLD_AWK);

#ifdef NOV
    fprintf(f, "NOV=true%c", nl);
#else
    fprintf(f, "NOV=false%c", nl);
#endif

#ifdef NNTP
    fprintf(f, "NNTP=true%c", nl);
    fprintf(f, "ACTIVE=%s/ACTIVE\n", db_directory);

#ifndef CACHE_DIRECTORY
#define CACHE_DIRECTORY ""
#endif

    fprintf(f, "NNTPCACHE=%s\n", CACHE_DIRECTORY);
#else
    fprintf(f, "NNTP=false%c", nl);
    fprintf(f, "ACTIVE=%s/active\n", news_lib_directory);
#endif

    fprintf(f, "LOG=%s\n", log_file);
    fprintf(f, "TMP=${TMPDIR-%s}\n", tmp_directory);
    fprintf(f, "DB=%s\n", db_directory);
    fprintf(f, "BIN=%s\n", bin_directory);
    fprintf(f, "LIB=%s\n", lib_directory);

    if (flag & (FULL_PREFIX | CONF_PREFIX)) {
	fprintf(f, "RECMAIL=\"%s\"\n", REC_MAIL);
	fprintf(f, "SPOOL=%s\n", news_directory);
	fprintf(f, "NLIB=%s\n", news_lib_directory);
	fprintf(f, "MASTER=%s\n", master_directory);
	fprintf(f, "HELP=%s\n", help_directory);
	fprintf(f, "DBDATA=\"%s\"\n", db_data_directory ? db_data_directory : "");

#ifdef DB_LONG_NAMES
	fprintf(f, "DBSHORTNAME=false\n");
#else
	fprintf(f, "DBSHORTNAME=true\n");
#endif

	fprintf(f, "OWNER=%s%c", OWNER, nl);
	fprintf(f, "GROUP=%s\n", GROUP);
    }

#ifdef AUTHORIZE
    fprintf(f, "AUTH=true\n");
#else
    fprintf(f, "AUTH=false\n");
#endif

    if (flag & FULL_PREFIX) {
	fprintf(f, "UMAN_DIR=\"%s\"\n", USER_MAN_DIR);
	fprintf(f, "UMAN_SECT=\"%s\"\n", USER_MAN_SECTION);

	fprintf(f, "SMAN_DIR=\"%s\"\n", SYS_MAN_DIR);
	fprintf(f, "SMAN_SECT=\"%s\"\n", SYS_MAN_SECTION);

	fprintf(f, "DMAN_DIR=\"%s\"\n", DAEMON_MAN_DIR);
	fprintf(f, "DMAN_SECT=\"%s\"\n", DAEMON_MAN_SECTION);
    }
    if (flag & SHELL_PREFIX)
	fprintf(f, "\n# ---- end of prefix\n\n");
}

int
main(int argc, char *argv[])
{
    if (argc != 2)
	exit(2);

    /* init_global(I_AM_MASTER); */
    init_global();

    switch (argv[1][0]) {
	case 'f':
	    make_nn_prefix(SHELL_PREFIX | FULL_PREFIX, stdout);
	    break;
	case 'p':
	    make_nn_prefix(SHELL_PREFIX, stdout);
	    break;
	case 'c':
	    make_nn_prefix(CONF_PREFIX, stdout);
	    break;
	default:
	    exit(1);
    }
    exit(0);
}

void
nn_exit(int n)
{
    exit(n);
}

void
nn_exitmsg(void)
{
    exit(0);
}

#ifdef HAVE_JOBCONTROL
int
suspend_nn(void)
{
    return 0;
}

#endif

/* dummy function */
void
msg(void)
{
}
