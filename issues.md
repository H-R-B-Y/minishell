

## minishell-$ (()()

provides syntax error (good)

## minishell-$ ()()(()(())

output is tokens are not valid
SUBSHELL is printed (meaning tree does no see and issue with this)

## minishell-$ (()

tokens are not valid
(seg fault) meaning either tree failed to construct OR print failed to print


## how do we handle this then?

question is, if tokens arent valid do we just not make the execution tree?

in bash when there is a quote that has not got a matching quote, or bracket without a matching bracket it goes into a new readline mode prompting the user to close the quote / match the bracket


