#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "git2.h"

int main(int argc, char *argv[])
{
	int getrepo(const char*, const char*);
	int error;
	--argc;
	if (argc < 2 || (argc % 2) != 0) {
		fprintf(stderr, "Usage: %s <url> <lpath> [...]\n", argv[0]);
		return 1;
	}
	git_libgit2_init();
	while (argc > 0) {
		if ((argc % 2) == 0) {
			error = getrepo(argv[argc-1], argv[argc]);
			if (error < 0) {
				const git_error *e = giterr_last();
				printf("Error: %d/%d: %s\n", error,
					e->klass, e->message);
				goto error;
			}
		}
		argc -= 2;
	}

error:
	git_libgit2_shutdown();
	return error;
}

int getrepo(const char* url, const char* path)
{
	git_repository *repo = NULL;
	int ret = git_clone(&repo, url, path, NULL);
	git_repository_free(repo);
	return ret;
}
