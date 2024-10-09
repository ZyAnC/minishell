# Heading Requirement from Parse
## Passing parameters as

```c
t_cmd *cmds = malloc(sizeof(t_cmd));
```
### Heading CMD

Every single cmd should save in `cmd`.

```c
typedef struct s_cmd {
    char **cmd;
    char    *infile;
    char    *outfile;
    t_token_type intype;
    t_token_type outype;
    int ispipe;
    struct s_cmd *next;

Default setting
    infile = NULL;
    outfile = NULL;
    intype = tk_none;
    outtype = tk_none;
    ispipe = 0;



Example
    cmd = split(input,' ');
    input = "ls -l"
    cmd[0]="ls";
    cmd[1]="-l"



for <infile ls | grep "txt" > outfile
    1st half: <infile ls |

        intype = TK_IN_RE;
        outtype=TK_PIPE;
        outfile = null;
        infile = "infile";

    2nd half: grep "txt" > outfile
        intype=TK_PIPE;
        outtype = TK_OUT_RE;
        infile = NULL
        outfile = "outfile"

for echo a | echo b
     1st half: echo a |

        intype = TK_NONE;
        outtype=TK_PIPE;
        outfile = NULL;
        infile = NULL;

    2nd half: echo b

        intype=TK_PIPE;
        outtype = TK_NONE;
        infile = NULL
        outfile = NULL

for  <infile >out1 | <infile2 >>out2
    1st half: <infile >out1 |

        intype = TK_IN_RE;
        outtype= TK_OUT_RE;
        outfile = out1;
        infile = infile;

    2nd half: <infile2 >>out2

        intype=TK_IN_RE;
        outtype = TK_APPEND;
        infile = infile2
        outfile = out2


for cat <1 <4 >3 <2
should same with <2 cat >3
so save the last < and >
also save first symbol <1 in (cat <1 <4 >3 <2) for report error
so errorfilename = command[0];
other in and out symbol same with previous
} t_cmd;

token type for lexer
TK_NONE:no redirect
TK_PIPE: pipes |
TK_IN_RE/TK_OUT_RE: redirection </>
TK_HDOC: <<
TK_APPEND: >>
typedef enum e_type
{
	TK_NONE;
    TK_PIPE,
	TK_IN_RE,
	TK_OUT_RE,
	TK_HDOC,
	TK_APPEND,
	TK_SINGLE_QT,
	TK_DOUBLE_QT,
	TK_KEYWORD,
	TK_LOC_V,
}	t_token_type;```
