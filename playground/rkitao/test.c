#include <stdio.h>
#include <unistd.h>

int main() {
	char *argv_p[] = {"/bin/ls", ">", "out", NULL};
	char *envp_p[] = {
		"HOME=/",
		// "PATH=/Users/kitaoryoma/.pyenv/shims:/Users/kitaoryoma/.pyenv/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Library/Apple/usr/bin:/Library/TeX/texbin:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/Applications/iTerm.app/Contents/Resources/utilities",
		NULL};

	// int i = -1;
	// while (envp[++i])
	// 	envp[i] = NULL;
	// execve関数を使用して新しいプログラムを実行
	if (execve("/bin/ls", argv_p, envp_p) == -1) {
		// perror("execve");
		write(2, "command not found\n", 18);
		return 1;
	}

	// この行はexecveが成功した場合には実行されない
	printf("This line will not be printed if execve is successful.\n");

	return 0;
}