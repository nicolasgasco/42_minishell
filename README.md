# Minishell (February 2022)
> The objective of this project is for you to create a simple shell. Yes, your little bash or zsh. You will learn a lot about processes and file descriptors.

This is a group project done together with [@adelcor](https://github.com/adelcor).

The shell must:
- interpret quotes correctly
- expand environment variables, including `$?`
- detect syntax errors
- have a prompt with a working history
- execute builtins, such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`
- interpret simple and double quotes
- execute redirections (`<`, `>`, `<<`, `>>`)
- execute pipes
- Catch `ctrl-C`, `ctrl-D`, and `ctrl-\` signals
