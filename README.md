# pipek

Learning pipes and redirections

## Status

COMPLETED

## Description

The goal of the project is to simulate a mechanism of multipipes and redirections. The way of executing the programm is <b>./pipek file_1 cmd_1 cmd_2 cmd_3 ... cmd_n file_2</b> where file_1 and file_2 are file names and cmd_1 - cmd_n are other programms (shell commands) with their parameters.

The following two executions do the same:

	./pipek file_1 "cat" "wc -l" file_2

	< file_1 cat | wc -l > file_2
