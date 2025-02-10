# UStr

[![Ubuntu](https://github.com/Galfurian/cpp_string_utils/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/Galfurian/cpp_string_utils/actions/workflows/ubuntu.yml)
[![Windows](https://github.com/Galfurian/cpp_string_utils/actions/workflows/windows.yml/badge.svg)](https://github.com/Galfurian/cpp_string_utils/actions/workflows/windows.yml)
[![MacOS](https://github.com/Galfurian/cpp_string_utils/actions/workflows/macos.yml/badge.svg)](https://github.com/Galfurian/cpp_string_utils/actions/workflows/macos.yml)
[![Documentation](https://github.com/Galfurian/cpp_string_utils/actions/workflows/documentation.yml/badge.svg)](https://github.com/Galfurian/cpp_string_utils/actions/workflows/documentation.yml)

The `ustr` library is a collection of utilities for string manipulation and checking in C++. It provides a set of functions to work with strings, including operations like trimming, case conversion, substring replacement, and more. Whether you need to check if a string starts or ends with a specific substring, or manipulate string content, `ustr` offers a simple and efficient set of functions.

## Features

- **String checking**: Check if a string begins or ends with a substring, if it's an abbreviation, or compare strings.
- **String manipulation**: Capitalize, decapitalize, trim, align, and more.
- **Convenient utilities**: Functions for transforming strings to numbers, binary representations, or human-readable sizes.

## Installation

You can include this library in your project by copying the necessary header files into your project directory.

1. Clone the repository or copy the header files to your project.
2. Include the relevant headers in your code:

```cpp
#include "check.hpp"
#include "manipulate.hpp"
#include "utility.hpp"
```

## Functions

### Checking Functions

#### `begin_with`

Checks if a string begins with a given substring.

```cpp
bool begin_with(const std::string &s, const std::string &prefix, bool sensitive = false, unsigned n = 0);
```

- `s`: Source string.
- `prefix`: Substring to check.
- `sensitive`: Case-sensitive check (default is `false`).
- `n`: Number of characters to check (0 means all of the prefix).

#### `end_with`

Checks if a string ends with a given substring.

```cpp
bool end_with(const std::string &s, const std::string &suffix, bool sensitive = false, unsigned n = 0);
```

- `s`: Source string.
- `suffix`: Substring to check.
- `sensitive`: Case-sensitive check (default is `false`).
- `n`: Number of characters to check (0 means all of the suffix).

#### `is_abbreviation_of`

Checks if a string is an abbreviation of another string.

```cpp
bool is_abbreviation_of(const std::string &prefix, const std::string &s, bool sensitive = false, std::size_t min_length = 1);
```

- `prefix`: Prefix string to check.
- `s`: Source string.
- `sensitive`: Case-sensitive check (default is `false`).
- `min_length`: Minimum length of the abbreviation.

#### `compare`

Compares two strings.

```cpp
bool compare(const std::string &s0, const std::string &s1, bool sensitive = false, unsigned n = 0);
```

- `s0`: First string.
- `s1`: Second string.
- `sensitive`: Case-sensitive check (default is `false`).
- `n`: Number of characters to compare (0 means all).

#### `count`

Counts the occurrences of a substring inside the given string.

```cpp
std::size_t count(const std::string &s, const std::string &sub_s, bool sensitive = false);
```

- `s`: Source string.
- `sub_s`: Substring to count.
- `sensitive`: Case-sensitive check (default is `false`).
- Returns: The number of occurrences.

#### `word_is_among`

Checks if a control word is among a list of words.

```cpp
bool word_is_among(
    const std::string &control,
    const std::vector<std::string> words,
    bool sensitive,
    bool begins_with,
    bool ends_with,
    bool exact_match);
```

- `control`: Control word to find.
- `words`: List of words.
- `sensitive`: Case-sensitive check (default is `false`).
- `begins_with`: Check if words begin with the control word.
- `ends_with`: Check if words end with the control word.
- `exact_match`: Check if words exactly match the control word.

### Manipulation Functions

#### `trim`

Removes the specified characters from both the beginning and the end of the string.

```cpp
std::string trim(const std::string &s, const std::string &padchar = " ");
```

- `s`: Source string.
- `padchar`: Character to remove (default is space).

#### `ltrim`

Removes the specified characters from the beginning of the string.

```cpp
std::string ltrim(const std::string &s, const std::string &padchar = " ");
```

- `s`: Source string.
- `padchar`: Character to remove (default is space).

#### `rtrim`

Removes the specified characters from the end of the string.

```cpp
std::string rtrim(const std::string &s, const std::string &padchar = " ");
```

- `s`: Source string.
- `padchar`: Character to remove (default is space).

#### `to_upper`

Converts the string to all uppercase.

```cpp
std::string to_upper(std::string s);
```

- `s`: Source string.

#### `to_lower`

Converts the string to all lowercase.

```cpp
std::string to_lower(std::string s);
```

- `s`: Source string.

#### `ralign`

Aligns the string to the right.

```cpp
std::string ralign(std::string s, std::string::size_type width, char fill = ' ');
```

- `s`: Source string.
- `width`: Final width of the string.
- `fill`: Character used to fill (default is space).

#### `lalign`

Aligns the string to the left.

```cpp
std::string lalign(std::string s, std::string::size_type width, char fill = ' ');
```

- `s`: Source string.
- `width`: Final width of the string.
- `fill`: Character used to fill (default is space).

#### `calign`

Centers the string.

```cpp
std::string calign(std::string s, std::string::size_type width, char fill = ' ');
```

- `s`: Source string.
- `width`: Final width of the string.
- `fill`: Character used to fill (default is space).

#### `replace`

Replaces all occurrences of the given substring.

```cpp
std::string replace(std::string s, const std::string &substring, const std::string &substitute, unsigned occurences = 0);
```

- `s`: Source string.
- `substring`: Substring to replace.
- `substitute`: Substitute string.
- `occurences`: Number of occurrences to replace (0 means all).

#### `replace_inplace`

Replaces all occurrences of the given substring in place.

```cpp
std::string &replace_inplace(std::string &s, const std::string &substring, const std::string &substitute, unsigned occurences);
```

- `s`: Source string (modified in place).
- `substring`: Substring to replace.
- `substitute`: Substitute string.
- `occurences`: Number of occurrences to replace.

#### `strip`

Removes all occurrences of a character from the string.

```cpp
std::string strip(std::string s, char c);
```

- `s`: Source string.
- `c`: Character to remove.

#### `strip_inplace`

Removes all occurrences of a character from the string in place.

```cpp
std::string &strip_inplace(std::string &s, char c);
```

- `s`: Source string (modified in place).
- `c`: Character to remove.

#### `split_paragraph`

Transforms a single-line string into a paragraph-formatted string.

```cpp
std::string split_paragraph(std::string s, std::string::size_type width, std::string whitespace = "");
```

- `s`: Source string.
- `width`: Width of each paragraph.
- `whitespace`: Whitespace characters (default is `"  
"`).

#### `merge_paragraph`

Transforms a paragraph-formatted string into a single line.

```cpp
std::string merge_paragraph(std::string s);
```

- `s`: Source string.

#### `split`

Splits the string by the given delimiter.

```cpp
std::vector<std::string> split(std::string const &s, std::string const &delimiter);
```

- `s`: Source string.
- `delimiter`: Delimiter for splitting.

#### `capitalize`

Capitalizes the first letter of the string.

```cpp
std::string capitalize(std::string s, unsigned occurences = 1);
```

- `s`: Source string.
- `occurences`: Number of occurrences to capitalize (0 means all).

#### `decapitalize`

Decapitalizes the first letter of the string.

```cpp
std::string decapitalize(std::string s, unsigned occurences = 0);
```

- `s`: Source string.
- `occurences`: Number of occurrences to decapitalize (0 means all).

### Utility Functions

#### `to_number`

Converts a string to an integer value.

```cpp
template <typename T>
T to_number(const std::string &s);
```

- `s`: String to convert.
- Returns: Converted integer value.

#### `to_double`

Converts a string to a floating-point value.

```cpp
template <typename T>
T to_double(const std::string &s);
```

- `s`: String to convert.
- Returns: Converted floating-point value.

#### `to_string`

Converts a value to a string.

```cpp
template <typename T>
std::string to_string(const T &value);
```

- `value`: The value to convert.
- Returns: String representation.

#### `is_number`

Checks if a string represents a number.

```cpp
bool is_number(const std::string &s);
```

- `s`: Source string.
- Returns: `true` if the string is a valid number.

#### `to_human_size`

Converts bytes to a human-readable size.

```cpp
const char *to_human_size(unsigned long bytes);
```

- `bytes`: The number of bytes to convert.
- Returns: Human-readable size (e.g., "1.23 MB").

#### `decimal_to_binary_string`

Converts a decimal value to a binary string.

```cpp
const char *decimal_to_binary_string(unsigned long value, unsigned length);
```

- `value`: The value to convert.
- `length`: Desired length of the binary output.

#### `get_ordinal`

Gets the ordinal suffix for a number.

```cpp
template <typename T>
const char *get_ordinal(T value);
```

- `value`: The number to convert.
- Returns: Ordinal suffix (e.g., "st", "nd", "rd", "th").

## Contributing

Contributions are welcome! If you have suggestions, bug reports, or new features
to propose, feel free to open an issue or submit a pull request.

Steps to Contribute:

- Fork the repository.
- Create a new branch: `git checkout -b my-feature-branch`
- Commit your changes: `git commit -m 'Add some feature'`
- Push the branch: `git push origin my-feature-branch`
- Open a pull request.

## License

`ustr` is licensed under the MIT License.
