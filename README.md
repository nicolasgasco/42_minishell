# Main
> The objective of this project is for you to create a simple shell. Yes, your little bash or zsh. You will learn a lot about processes and file descriptors.

## Backlog

1. Initializing project
    - Writing Makefile
    - Importing Libft
    - Writing header file

2. Creating a prompt and listening to user input
    - Prompt shows username and hostname
        - Fallback in case there are no variables
    - Prompt has a working history
    - Prompt keeps showing new prompt line if quotes are not closed:
        - Interpreting number of outer quotes
        - Converting ' into \\' when used inside of quotes
            1. Brace expansion ?
            2. Tilde expansion ?
            3. Shell parameter expansion ?
            4. Command substitution ?
            5. Arithmetic expansion ?
            6. Process substitution ?
            7. Word splitting ?
            8. Filename expansion ?
            9. Quote removal ?

3. Parse user input
    - Separate by word and trim spaces
    - Check if input is too long
    - Check if command is known or valid
    - Interpret \

4. Commands:
    - Parse path variable
    - Save return values of executed commands
    - Fork before execution with **execve**
        - **echo** with option -n
        - **cd** with only a relative or absolute path
        - **pwd** with no options
        - **export** with no options
        - **unset** with no options
        - **env** with no options or arguments
        - **exit** with no options

5. Error validation:
    - Input too long?
