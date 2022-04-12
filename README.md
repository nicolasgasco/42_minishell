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


## Examples

- \>\> redirection
<br />

![Screenshot of >> redirection example](https://res.cloudinary.com/ngasco/image/upload/v1649785877/42/minishell/Screenshot_from_2022-04-12_19-49-10_lyhc3p.png "Screenshot of >> redirection example")

- Here doc
![Screenshot of Here doc](https://res.cloudinary.com/ngasco/image/upload/v1649785877/42/minishell/Screenshot_from_2022-04-12_19-45-50_xtmsur.png
 "Screenshot of Here doc")
