# pipek

Learning pipes and redirections

## Status

IN PROGRESS

## Description

The goal of the project is to simulate a mechanism of multipipes and redirections.
The way of executing the programm is: <br>./pipek file_1 cmd_1 cmd_2 cmd_3 ... cmd_n file_2</br>
where file_1 and file_2 are files and cmd_1 - cmd_n are other programms (shell commands) with their parameters.

	./pipek file_1 "cat" "wc -l" file_2
This execution does the same as the next shell command:
	< file_1 cat | wc -l > file_2
