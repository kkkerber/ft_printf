*This project has been created as part of the 42 curriculum by vakhapil.*

# Description

`ft_printf` recreates the mandatory conversions of C's `printf` in a static
library, `libftprintf.a`. The project introduces variadic functions: functions
that accept a variable number of arguments.

Supported conversions are `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, and
`%%`. Flags, field widths, precision, and bonus conversions are not implemented.
Output goes directly to standard output, without printf-style buffering or
heap allocation.

# Instructions

- `make`: build `libftprintf.a`; unchanged files are not rebuilt.
- `make clean`: remove object files.
- `make fclean`: remove object files and the library.
- `make re`: remove build artifacts and rebuild the library.

The build uses `cc -Wall -Wextra -Werror` and `ar rcs`.
Create a separate `test.c`:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("hello %s: %d %%\n", "world", 42);
    return (0);
}
```

Compile and run it from the repository root:

```sh
cc -Wall -Wextra -Werror test.c libftprintf.a -o test
./test
```

The Makefile names its sources explicitly, so a separate test program is not
included in the library.

# Algorithm and Data Structure

`ft_printf` scans the format string sequentially. Ordinary characters go to the
character helper. A `%` followed by another character selects a conversion in
the dispatcher. The dispatcher uses `va_arg` to extract the matching argument
from the `va_list` initialized by `va_start`; `va_end` always closes that list.
`%%` writes a percent sign without reading an argument.

The text helper writes one byte at a time and counts successful writes. Decimal
conversion recursively prints the quotient before the remainder, placing digits
in their natural order. Signed conversion prints a minus sign when needed and
computes the magnitude with unsigned arithmetic. Unsigned subtraction is defined
modulo the unsigned range, so this also handles `INT_MIN` without negating it as
a signed integer.

Hexadecimal conversion uses the same quotient/remainder approach with base 16
and the appropriate lowercase or uppercase digit alphabet. Pointer conversion
extracts `void *`, converts it to `uintptr_t` to preserve its full value, writes
`0x`, and reuses the lowercase hexadecimal helper.

Each helper returns its character count, or `-1` if a write fails. The parser
adds successful counts and propagates failures after calling `va_end`. A write
failure can leave some output already written. No heap memory is allocated;
recursion depth is bounded by the number of digits in an integer.

Separating parsing, text output, number conversion, and pointer formatting keeps
each function short and makes the logic easy to explain. A scan position, an
argument list, and counters are sufficient; no complex data structure is needed.

| Conversion | Extracted type |
| --- | --- |
| `%c` | `int` (default argument promotion) |
| `%s` | `char *` |
| `%p` | `void *` |
| `%d`, `%i` | `int` |
| `%u`, `%x`, `%X` | `unsigned int` |
| `%%` | None |

## Platform behavior and scope

This implementation targets the tested macOS libc behavior: NULL strings print
`(null)` and NULL pointers print `0x0`. NULL string formatting is not guaranteed
by the C standard, and pointer formatting is implementation-defined. Linux
glibc commonly prints `(nil)` for NULL pointers, so that case needs adapting if
the evaluation target changes to glibc.

Use valid mandatory format strings and correctly typed arguments. As defensive
behavior, a NULL format returns `-1`, an unsupported conversion returns `-1`,
and a trailing `%` prints a literal percent sign. These are not promises of
libc compatibility for invalid formats. Output counts beyond `INT_MAX` are
outside the supported scope.

# Resources

- `man 3 printf`: conversions, return values, and platform behavior.
- `man 3 stdarg`: variadic functions and `va_start`, `va_arg`, and `va_end`.
- *The C Programming Language*, second edition, section 7.3: variable-length
  argument lists.
- `man 2 write`: direct output and write errors.
- `man 1 ar` and `man 1 ranlib`: static archives and their symbol indexes.
- `man 1 make`: build rules, prerequisites, and incremental compilation.

### AI usage

AI was used as a supporting learning tool for:
- explaining variadic arguments and integer conversion;
- developing and reviewing the implementation approach against the requirements;
- suggesting and running output, return-value, build, and Norm checks.
