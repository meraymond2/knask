# knask

A simple tool for parsing bytes on the command line.

## Usage

Provide a list of types to parse and bytes. For now, bytes must be specified as decimal.

```bash
knask u8 255 i8 255

# prints
# u8: 255
# i8: -1
```

All non-relevant characters are ignored.

```bash
knask i32 str \
  0, 0, 1, 248 \
  '[72,101,108,108,111,32,119,111,114,108,100,33]'

# prints
# i32: 504
# str: Hello world!
```

Non-final strings must be null-terminated.

```bash
knask str str str 67 97 115 0, 76 117 110 97 0, 83 104 101 114 108 111 99 107

# prints
str: Cas
str: Luna
str: Sherlock
```

## Code

In addition to being a useful tool, this was intended as C++ practice, so the code is probably horrifically unidiomatic.
