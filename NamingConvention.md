# Public-Facing API

### Types

1. All public types will be named using a snakecase scheme.
2. All public types will be appended with `_t`.
3. Public types will never be aliased as a pointer.
4. Examples:
    - `foo_t`
    - `foo_bar_t`
    - `foo_bar_t *`

### Functions

1. All public functions will be named using a snakecase scheme.
2. All public functions will be named using four segments:
    1. The first segment is always `Crypt_`.
    2. The second segment is always the name of the module the function belongs to.
    3. The third segment is always the name of the object the function primarily operates on. This is an optional segment and not always present.
    4. The fourth segment always the name of the operation the function performs.
3. In the case of function overloading, a fifth segment may be added to describe the change of data type operated on. This segment must be added on all functions being overloaded.
4. Examples:
    - `Crypt_memory_allocate`
    - `Crypt_list_linkedlist_create`
    - `Crypt_list_linkedlist_add_int` or `Crypt_list_linkedlist_add_double`

### Headers

1. All public headers will be named as "Crypt_\<module\>.h", where \<module\> is the name of the module the header belongs to.
2. All modules will have no more than one public header.
3. All public headers can be safely and directly included into any source file.

---

# Private-Facing API

### Types

1. Private types will never be aliased.
2. Private types will always be prefixed with two underscores.
3. Private types will always be opaque and should never be used directly.
4. Examples:
    - `struct __foo`
    - `struct __foo_bar`
    - `struct __foo_bar *`

### Functions

1. All private functions will start with `__internal` and otherwise follow the same naming convention as the public functions.
2. If a private function shares the same name as a public function (besides the `__internal`) then it can be assumed as a helper function.
3. Private functions should never be called directly. Directly using a private function can result in the instability of the system.
4. Examples:
    - `__internal_Crypt_memory_allocate`
    - `__internal_Crypt_list_linkedlist_create`

### Headers

1. All private headers will be named "internal_\<segment\>.h", where \<segment\> will be one of four things:
    - \<module\>: The module that this private header belongs to. This is used as a bulk private inclusion and called a monolithic module header.
    - function: This private header contains private function prototype information.
    - type: This private header contains private type definitions.
    - macro: This private header contains private macro definitions
2. All private module headers will be placed in include/Crypt_utils/
3. If private monolithic module header is deemed too large, it will be split into the smaller files defined above.
4. All private monolithic module headers will be placed in include/Crypt_utils/\<module\>/
5. Private headers should __never__ be included directly.

---

# Macros

### General Naming

1. All macro names will be defined with a capital snakecase scheme.
2. All macros will begin with `CRYPT_<MODULE>_`, where \<MODULE\> is the name of the module this macro is defined in.
3. If a macro is to be private, it will begin with `__CRYPT_<MODULE>_` instead.
4. All public macros will be defined in its respective header file.


### Constants

1. All constant macros are gauranteed to be constant expressions.

### Macro-Functions

1. All functional macros will be suffixed with the type it is meant to "return".
2. All functional macros must make a final cast to this "return" value.
3. Those that "return" void does not need to be suffixed with `_VOID`, but must be wrapped in `do { /* code */ } while(0)`.

---

# Source Files

1. Locations
    1. All source files will be placed into the module it belongs to.
    2. Source files live in a flat environment: they cannot live within subdirectories within its module's folder.
2. Content
    1. All source files will contain at most one public function.
    2. Source files may contain any amount of private functions.
    3. Source files will be titled after the public function it contains.
    4. If a source file contains no public function, it will be named after the job of its private function(s). The file will not be named after the name of the function.
3. Examples:
        - `memory_allocate.c` - Defines the public function `Crypt_memory_allocate`
        - `list_linkedlist_create.c` - Defines the public function `Crypt_list_linkedlist_create`
        - `sanity_check.c` - Defines private function(s) that provides a sanity checker

---

# Parameters

### Types

1. All parameter type keywords will be seperated by one space.
2. If it is a pointer, then the asterisk (*) will also be seperated by one space.

### Names

1. All parameters will be named using a snakecase scheme.
2. The parameter name will be named roughly after what function it performs
3. Parameter names will likely be heavily shortened for ease of typing.

---

# Commenting and Documentation

### Functions

1. All public functions will be documented in its respective header file.
2. All private functions will be documented in the source file it is defined in.
3. All functions within header files will be documented with the following information:
    - A description of what the function does.
    - List of parameters, and their purpose.
    - What the return value is, if it is not obviously inferable.
    - Any errors that can arise from the function, what makes the error appear, and how that error is communicated to the callee.
4. Parameters will be described as "@<param>: description".
5. The return value will be described as "Returns: description".
6. Any errors will be described as "Errors:" followed by either a description for one error, or a list of descriptions for multiple.

### Headers

1. All function prototypes defined in a header file will be seperated by a category.
2. Categories are split by functionality: initalization, destruction, etc.

