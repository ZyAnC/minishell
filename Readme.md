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
    1st half <infile ls |

        intype = TK_IN_RE;
        outtype=tk_none;
        outfile = null;
        infile = "infile";
        ispipe = 1;

    2nd half grep "txt" > outfile
        intype=tk_none;
        outtype = TK_OUT_RE;
        infile = NULL
        outfile = "outfile"
        ispipe = 0;
   
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
