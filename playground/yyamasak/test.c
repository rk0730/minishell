# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>

// シグナルハンドラ関数
void handle_signal(int signal) {
    if (signal == SIGINT) {
        printf("\nSIGINTを受け取りました。プログラムを終了します。\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    char *input;

    // シグナルハンドラを設定
    signal(SIGINT, handle_signal);

    while (1) {
        // ユーザー入力を読み込み
        input = readline("入力> ");
        
        // 入力がNULLの場合（Ctrl+DでEOF）
        if (input == NULL) {
            printf("\nEOFを受け取りました。プログラムを終了します。\n");
            break;
        }

        // 空の入力でなければ履歴に追加
        if (*input) {
            add_history(input);
        }

        // ユーザー入力を出力
        printf("あなたの入力: %s", input);

        // メモリを解放
        free(input);
    }

    return 0;
}
