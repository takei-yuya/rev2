rev2
====

advanced rev(1)

```
Usage: ./src/rev2 [OPTION...] [FILE]...
reverse lines of input

  -n, --length=NUM           reverse line by each NUM-chars.
  -d, --delim=DELIMS         reverse line in words split by DELIMS
  -j, --join=JOIN            join each sub-string by JOIN
  -h, --help                 display this help and exit
  -v, --version              display version information and exit

If no FILEs are specified, the standard input is read
If JOIN is not given, use empty string for length, or use first char of DELIMS for words

e.g.
echo "foo bar baz" | ./src/rev2             # "zab rab oof"
echo "foobarbaz"   | ./src/rev2 -n3         # "bazbarfoo"
echo "foo,bar,baz" | ./src/rev2 -d,         # "baz,bar,foo"
echo "foo,bar,baz" | ./src/rev2 -d, -j' '   # "baz bar foo"
echo "foo,bar+baz" | ./src/rev2 -d,+        # "baz,bar,foo"
```
