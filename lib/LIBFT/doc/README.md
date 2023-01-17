# 00_extended_libft
A modified version of lift project, to be used in other projects.
```console
             w                  8          8    8 w 8     d8b  w   
.d88b Yb dP w8ww .d88b 8d8b. .d88 .d88b .d88    8 w 88b.  8'  w8ww 
8.dP'  `8.   8   8.dP' 8P Y8 8  8 8.dP' 8  8    8 8 8  8 w8ww  8   
`Y88P dP Yb  Y8P `Y88P 8   8 `Y88 `Y88P `Y88    8 8 88P'  8    Y8P 
                                                                   
```

## Changes over regular libft
- Modified source file structure.
- ft_put functions return the number of characters printed as int.
- ft_substr is modified to return NULL when len is = 0 instead of an empty string
- ft_substr is modified to return NULL when the starting point is higher than the length of the string
- Bonus removed as an alternative compilation option (all included in the main libft)
- Included useful functions (both main and auxiliary) and variable types from other projects.

## Additional variable types:

## Additional main functions

## Additional auxiliary functions
- ft_isspace: checks if a character is a space (extracted from atoi).
- ft_abs: returns the absolute value of an signed int (extracted from putnbr).
- ft_ischarset: tests if the character c is contained within the string set (extracted from strtrim).
- ft_digitcount: returns the number of digits in an unsigned long in a given base length (extracted from itoa and modified with base length as argument).
- ft_putunbr_fd: outputs the unsigned integer n to the file descriptor fd.
- ft_putuhexnbr_fd: outputs the unisgned integer n to the file descriptor fd in hexadecimal.
- ft_isline: test for a new line character in a string (extracted from gnl).
- ft_is_samesign: (extracted from push_swap).
- ft_is_int: checks if a string is a vallid int (syntax and max/min values) (extracted from push_swap).
- ft_strcat: replicates strcat (extracted from push_swap).
- ft_max: compares two signed integers and provides tha one with the highest value (extracted from push_swap).
- ft_exit_w_error: exits with perror and errno or custom error message (extracted from pipex)
- ft_chars_valid: checks if the chars in a string are all contained in a provided set.
- ft_count_chars: counts the instances of a char in a string.
