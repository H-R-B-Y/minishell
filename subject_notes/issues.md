


## 

question is, if tokens arent valid do we just not make the execution tree?
> YES AST is not constructed anymore if tokens are invalid.

Note: when bash prompts to close the bracket, it has different signal handlers
try running 
```sh
$ echo "
dquote> 
```
> ctrl+d is not a signal handler it just send EOF through the terminal.


## we should do all other syntax checks during the tree construction

> NO



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

> HEREDOC prep WILL need to happen BEFORE the execution pipeline, it needs to happen at either the TOKENISER or AST construction because it needs to be redirected before execution.

> >  I can set this up to happen during the ast and append it to the end of the redirect list, then when redirects are setup during the execution step the redirects need to happen in order of FIFO meaning the last takes precedence if there are overlaps.


