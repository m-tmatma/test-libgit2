#include <stdio.h>
#include <git2.h>

int main()
{
	git_repository *repo = NULL;
	int ret;
	
	git_libgit2_init();

	ret = git_repository_open_ext(&repo, ".", 0, NULL);
	printf("git_repository_open_ext() returns %d\n", ret);

	git_repository_free(repo);
	git_libgit2_shutdown();
	return 0;
}
