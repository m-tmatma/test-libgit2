/*
	libgit2 "general" example をもとに libgit2 を使ってみる。
	
	https://libgit2.org/libgit2/ex/HEAD/general.html
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "git2.h"

// https://libgit2.org/libgit2/ex/HEAD/general.html#section-4
static void check_error(int error_code, const char *action)
{
	const git_error *error = git_error_last();
	if (!error_code)
	return;

	printf("Error %d %s - %s\n", error_code, action,
		(error && error->message) ? error->message : "???");

	exit(1);
}

// https://libgit2.org/libgit2/ex/HEAD/general.html#section-Revwalking
static void revwalking(git_repository *repo, const char * commithash)
{
	const git_signature *cauth;
	const char *cmsg;
	int error;
	git_revwalk *walk;
	git_commit *wcommit;
	git_oid oid;

	printf("\n*Revwalking*\n");

	git_oid_fromstr(&oid, commithash);

// To use the revwalker, create a new walker, tell it how you want to sort the output and then push one or more starting points onto the walker. If you want to emulate the output of git log you would push the SHA of the commit that HEAD points to into the walker and then start traversing them. You can also 'hide' commits that you want to stop at or not see any of their ancestors. So if you want to emulate git log branch1..branch2, you would push the oid of branch2 and hide the oid of branch1.

	git_revwalk_new(&walk, repo);
	git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_REVERSE);
	git_revwalk_push(walk, &oid);

	while ((git_revwalk_next(&oid, walk)) == 0) {
		error = git_commit_lookup(&wcommit, repo, &oid);
		check_error(error, "looking up commit during revwalk");

		cmsg  = git_commit_message(wcommit);
		cauth = git_commit_author(wcommit);
		printf("%s (%s)\n", cmsg, cauth->email);

		git_commit_free(wcommit);
	}
// Like the other objects, be sure to free the revwalker when you're done to prevent memory leaks. Also, make sure that the repository being walked it not deallocated while the walk is in progress, or it will result in undefined behavior

	git_revwalk_free(walk);
}


void show_revwalking(const char * repo_path, const char * commithash)
{
	git_repository *repo = NULL;
	int error = git_repository_open(&repo, repo_path);
	revwalking(repo, commithash);
	git_repository_free(repo);
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		printf("usage: %s <repo_path> <commitHash>\n", argv[0]);
		return 1;
	}
	
	char * repo_path = argv[1];
	char * commitHash= argv[2];
	
	git_libgit2_init();
	show_revwalking(repo_path, commitHash);
	git_libgit2_shutdown();
	return 0;
}
