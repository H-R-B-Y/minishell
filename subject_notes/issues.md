

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

in bash when there is a quote that has not got a matching quote, or bracket without a matching bracket it goes into a new readline mode prompting the user to close the quote / match the bracket.

Note: when bash prompts to close the bracket, it has different signal handlers
try running 
```sh
$ echo "
dquote> 
```
and press ctrl+d, this is a different signal handler?


## we should do all other syntax checks during the tree construction

so other syntax errors are: 
// TODO: note down bash syntax errors



## Just found something interesting not sure where to write this:

using zsh it is hard to see what goes on here but in bash it is simple:

```sh
sleep 10 && << EOF | cat && echo "
```

execution order would suggest (in my mind)
1. quotes need to be closed
2. sleep for 10 seconds
3. read into the heredoc
4. contents of heredoc is cat'd
5. echo is printed

what actually happens:
1. bash does not start the execution process because there is an unclosed quote.
2. upon closing the quote we still do not enter execution because there is an open heredoc
3. upon closing the heredoc the contents of the heredoc is written out then the contents of the quote

this means that the heredoc is opened before the execution of anything,
perhaps this needs to be done somewhere before the AST execution pipeline?

truthfully i am not really interested in replicating bash 100%, I know that I personaly wont mind if
we wait until the stage in the AST where we need the heredoc to finish it, but some evaluators might not be kind 
to this way of doing things?
