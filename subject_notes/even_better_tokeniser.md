

## To create the best tokeniser

to create the best tokeniser i think we need to create a FSM to ensure that all tokens are valid
both in relation to their neighbors but also to the current pipeline.

we might need to reduce the number of token types to allow it to make more sense.

I think to create a good FSM we need to make sure that all tokens are preceded and proceded by valid tokens

one good way to check this would be with a function that takes two states, the prev and the next, 
we can then do a lookup in a small static constant array of potential transitions of state, if the lookup does
not succeed then we have reached an error state, if the state is found then we continue to parse the next token.

```mermaid
---
config:
  theme: redux
  layout: dagre
---
flowchart TD
    A(["START <br>"]) --> n2(["WORD <br>"]) & n5(["HEREDOC <br>"])
    n5 --> n6(["HEREDOC WORD <br>"])
    n6 --> n2
    n2 --> n7(["OPERATOR<br>"]) & n3(["REDIRECT OUT <br>"]) & n4(["REDIRECT APPEND<br>"]) & n8(["PIPE <br>"]) & n9(["REDIRECT IN <br>"])
    n7 --> n2 & n5 & n9
    n8 --> n5 & n2 & n9
    n3 --> n2
    n4 --> n2
    n9 --> n2

```