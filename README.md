# OS-SHELL

## INTRODUCTION

Created an interactive shell that program that can create and manage new processes.

## Execution Steps:
  - Type command 'make' to run the makefile.
  - './os' to execute the user-defined shell.

## FEATURES

* Builtins:
	1. cd
	2. pinfo
	3. exit
	4. pwd
	5. ls
	6. nightswatch
	7. jobs
	8. kjob
	9. fg
	10. bg
	11. overkill
	12. setenv
	13. unsetenv

## Functionalities
### Specification 1:
- Displays appropriate shell prompt considering the directory in which the program is executed as Home directory.


### Specification 2:
- 'cd', 'pwd', and 'echo' implemented as per the requirements.
- Extra functionality of displaying environment variables like $HOME, $PWD added in 'echo' command.

### Specification 3:
- Typing only 'ls' gives the output as expected.
- It works for the flag '-l' and '-a'.The ordering or the number of '-l' and '-a' does not affect the execution of the command. Arguments with file names can be given with the command.

### Specification 4:
- System commands running using 'execvp'.
* Foreground processes running as per requirements. That is the shell is stopped until the process is terminated if it starts in foreground.
* Background processes running as per requirements. Any command invoked with "&" is treated as background command. This implies that your shell will spawn that process and doesn't wait for the process to exit. It will keep taking user commands.

### Specification 5:
- 'pinfo' command implemented. It  fetches its data from the file /proc/<pid>/state and executable path from /proc/<pid>/exe.

## Bonus:
If the background process exits then the shell displays the appropriate message to the user.

