# Minishell ![norminette](https://github.com/tinitiuset/minishell/workflows/norminette/badge.svg)

This project is a simple shell.

## Mark:
![100/100](./doc/img/mark.png)

# Reference Information:
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf


# Initial Flowchart Diagram

![Minishell Basic Digram](doc/diagram/Minishell_Basic.drawio.svg)

## Job Delegator Example Flowchart

![Job Delegator ExampleFlowchart](doc/diagram/Job%20Delegator%20Example%20Flowchart.svg)

## Job Flowchart

![Job Flowchart](doc/diagram/Job%20Flowchart.svg)

## Debug a Child process
    
    set detach-on-fork off
    set follow-fork-mode child

https://unix.stackexchange.com/questions/79888/what-exactly-happens-when-a-built-in-command-is-run-in-a-shell
