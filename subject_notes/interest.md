
# fd table

while the actual kernal fd table attributed to any running process is not
accessible via any sys call in c, it is actually possible to inspect the fd table
via some of the quirks in the unix system, namely, we can run ls on:
`/proc/<pid>/fd`
and info can be acquired about the fds in:
`/proc/<pid>/fdinfo`