#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <git2.h>
#include <git2/clone.h>

#ifdef UNUSED
#elif defined(__GNUC__)
#define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
#define UNUSED(x) /*@unused@*/ x
#else
#define UNUSED(x) x
#endif

int readln(char *line, size_t size);
int get_input(const char *message, char *line, size_t size);

int cred_aquire_cb(git_cred **out,
		const char *UNUSED(url),
		const char *UNUSED(username),
		unsigned int UNUSED(types),
		void *UNUSED(payload))
{
	char username[128] = {0};
	char password[128] = {0};

	(void)get_input("Enter your username: ", username, sizeof username);
	(void)get_input("Enter your password: ", password, sizeof password);

	return git_cred_userpass_plaintext_new(out, username, password);
}

int getrepo(const char *url, const char *path)
{
	git_repository *repo = NULL;
	git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
	int error;

	clone_opts.fetch_opts.callbacks.credentials = cred_aquire_cb;
	error = git_clone(&repo, url, path, &clone_opts);
	if (error < 0) {
		const git_error *err = giterr_last();
		if (err) printf("ERROR %d: %s\n", err->klass, err->message);
		else printf("ERROR %d: no detailed info\n", error);
	}
	else if (repo) git_repository_free(repo);
	return error;
}

int main(int argc, char *argv[])
{
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
			if (error != 0)
				break;
		}
		argc -= 2;
	}

	git_libgit2_shutdown();
	return error;
}

int readln(char *line, size_t limit)
{
	int c, chars_remain = 1;
	char *p = line;
	while (chars_remain) {
		c = getchar();
		if (c == '\n' || c == EOF) {
			chars_remain = 0;
			*p = '\0';
		} else if (--limit > 1)
			*p++ = c;
	}
	return p-line;
}

int get_input(const char *message, char *line, size_t size)
{
	int len = 0;
	printf("%s", message);
	len = readln(line, size);
	return len;
}


