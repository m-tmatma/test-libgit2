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

// https://libgit2.org/libgit2/ex/HEAD/general.html#section-32
static void commit_parsing(git_repository *repo, const char * commitHash)
{
	const git_signature *author, *cmtter;
	git_commit *commit, *parent;
	git_oid oid;
	char oid_hex[GIT_OID_HEXSZ+1];
	const char *message;
	unsigned int parents, p;
	int error;
	time_t time;

	printf("\n*Commit Parsing*\n");

	git_oid_fromstr(&oid, commitHash);

	error = git_commit_lookup(&commit, repo, &oid);
	check_error(error, "looking up commit");

	// Each of the properties of the commit object are accessible via methods, including commonly needed variations, such as git_commit_time which returns the author time and git_commit_message which gives you the commit message (as a NUL-terminated string).

	message  = git_commit_message(commit);
	author   = git_commit_author(commit);
	cmtter   = git_commit_committer(commit);
	time     = git_commit_time(commit);

	// The author and committer methods return [gitsignature] structures, which give you name, email and when, which is a `gittime` structure, giving you a timestamp and timezone offset.

	printf("Author: %s (%s)\nCommitter: %s (%s)\nDate: %s\nMessage: %s\n",
	author->name, author->email,
	cmtter->name, cmtter->email,
	ctime(&time), message);

	// Commits can have zero or more parents. The first (root) commit will have no parents, most commits will have one (i.e. the commit it was based on) and merge commits will have two or more. Commits can technically have any number, though it's rare to have more than two.

	parents  = git_commit_parentcount(commit);
	for (p = 0;p < parents;p++) {
		memset(oid_hex, 0, sizeof(oid_hex));

		git_commit_parent(&parent, commit, p);
		git_oid_fmt(oid_hex, git_commit_id(parent));
		printf("Parent: %s\n", oid_hex);
		git_commit_free(parent);
	}

	git_commit_free(commit);
}

void show_commit_info(const char * repo_path, const char * commithash)
{
	git_repository *repo = NULL;
	int error = git_repository_open(&repo, repo_path);
	commit_parsing(repo, commithash);
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
	show_commit_info(repo_path, commitHash);
	git_libgit2_shutdown();
	return 0;
}
