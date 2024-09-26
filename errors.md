https://github.com/maiadegraaf/minishell/blob/main/src/utils/minishell_loop.c

1. ~$ cat <minishell.h>./outfiles/outfile
	bash: minishell.h: No such file or directory


3. $ echo hhhh >>> out
	bash: syntax error near unexpected token `>'

4. $ cat <<<<infile.txt | echo hi
	bash: syntax error near unexpected token `<'



Summary, error handling before execution:

1. if the command start with '|'								--DONE
	error: bash: syntax error near unexpected token `|'

2. cmd: meta_char (space) meta_char1 (nothing at the back of meta_char 1)
	error: bash: syntax error near unexpected token `meta_char1'

3. cmd: meta_char (space) meta_char1 (somthing at the back of meta_char 1)
	error: bash: syntax error near unexpected token `meta_char'

4.	cmd: meta_char (except '|')
	cmd: meta_char(except '|') infile.txt meta_char1
	erro: bash: syntax error near unexpected token `newline'







We DON'T consider implement these conditions:
1.	cmd: <infile.txt |
	> cat

	cmd: >outfile |
	> cat

	cmd: << EOF |
	> this
	> is the last line
	> EOF
	> cat

2. 	cmd: meta_char
	cmd: <infile.txt meta_char(except '|')
	cmd: >outfile.txt meta_char(except '|')
	cmd: >>outfile.txt meta_char(except '|')
	erro: bash: syntax error near unexpected token `newline'

3. don't consider this condition: meta_char(no space)meta_char1 .



