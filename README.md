This project was done during a Class at UCSC-Extension school
---
[Linux Systems Programming | EMBD.X420](https://www.ucsc-extension.edu/courses/linux-systems-programming-1/)

Taught by [Juergen Kienhoefer](https://github.com/aircable)

**Course description**
---
>In this course, you will explore the vital role of system calls in Linux and other systems, enabling user-space applications to connect with the kernel and perform privileged functions. System calls contribute to application and operating system compatibility and interoperability by offering a defined interface for accessing the kernel that is used for functionality.
You will explore system call APIs to learn how to build interactive and service (daemon) applications that control the system and perform operations. We categorize based on the type of operation they perform: process management and file management. Practical projects include building standard Linux applications, such as ls, cat, etc. as well as some service processes, such as ftp.
>Key topics covered include I/O control, file systems, access, and locking; signal handling; process and threads management; IPC using pipes and TCP/UDP sockets. Additionally, the course will address makefiles, man pages and packaging utilities.
>By the end of the course, you’ll have developed a complete ftp package and mastered the implementation of client-server programs using TCP, UDP, and RPC. This course adheres to the POSIX standard, ensuring a solid foundation, while also incorporating discussions on portability considerations for BSD extensions and SVR4 differences.
shell variables (enviroment variables) 
need a PATH variable 



### **Summary**

This project was done with signifigant AI support. the intention is not to make a better faster smarter shell but go through the implementation and design of a shell to better understand the userspace system utilities. I tried to following a role as the software project manager and did a lot of research on the features of the shell and try to derive a requirement document that became the basis for teh direction of the project.  This requiremnt process was driven by the weekly lectures of the class and took the form of parsing the lecture notes and slides into a functional requirement checklist and iterating from their. 

The last major thing that was accomplished was moving from a string based input parsing to a Abstract syntax tree based input parsing style. this introduced a lot of dependency in the order that object files were created and the project build system had to be redesigned. 


---

##  Build System Overview

Lshell uses a modular `Makefile`-based build system that cleanly separates components like the shell runtime, parser, and utilities. Each module has its own `Makefile` and compiles its source files into local `build/` directories, while the top-level `Makefile` orchestrates the full build and linking process.

---

### 📁 Directory Structure

```

Lshell/
├── Makefile               # Top-level makefile
├── shell/                 # Shell runtime (main loop, exec, env handling)
│   ├── Makefile
│   ├── shell.c
│   └── build/             # Object files
├── parser/                # Lexer/parser (Flex & Bison)
│   ├── Makefile
│   ├── lexer.l
│   ├── parser.y
│   └── build/
├── utils/                 # General-purpose helpers
│   ├── Makefile
│   ├── utils.c
│   └── build/
└── coreutils/             # Custom shell utilities (e.g., wc, cat)
├── Makefile
├── wc.c
└── build/

````

---

###  Top-Level Build Targets

```bash
make            # Build the full shell (default)
make clean      # Clean all object files
make -C shell   # Build only the shell module
make run        # Optional: build and run ./lshell
````

---

###  Build Process Summary

1. Flex & Bison generate `parser.c` and `lexer.c` inside `parser/`
2. Each module compiles to object files in its own `build/` dir
3. The top-level `Makefile` links all `.o` files into the final `lshell` binary

---

###  Build System Features

* Modular, per-directory `Makefile` layout
* Dedicated `build/` folders keep object files isolated
* Top-level orchestration handles clean, incremental builds
* Easy to extend: just add new modules with `Makefile` and `build/` folder

---

###  Planned Improvements

* Add dependency tracking (`.d` files) for smarter builds
* Add unit tests with `tests/` directory and a test runner target
* Auto-regenerate parser/lexer if `.y` or `.l` files change

```

---



## 🐚 Lshell Feature Checklist

Lshell is a custom Unix-like shell implemented in C, with support for core shell functionality including redirection, aliasing, and built-in commands. Below is the current implementation status of key shell features.

| Feature                              | Status        | Notes                                                                 |
|--------------------------------------|---------------|-----------------------------------------------------------------------|
| **Basic Command Execution**          | ✅ Implemented | Supports external commands using `fork()` and `exec()`               |
| **PATH Resolution**                  | ✅ Implemented | Automatically searches executable paths via `$PATH`                  |
| **Built-in Commands**                | ✅ Partial     | `cd`, `alias`, `unalias`, `export`, `set`, `unset`, `history`        |
| **Prompt and Readline Support**      | ✅ Implemented | Integrated with GNU Readline for input, editing, and history         |
| **Input Redirection (`<`)**          | ✅ Implemented | Supports redirecting stdin from a file                               |
| **Output Redirection (`>`, `>>`)**   | ✅ Implemented | Redirects stdout to overwrite (`>`) or append (`>>`) a file          |
| **Pipelines (`|`)**                  | ✅ Implemented | Enables chaining commands through pipes                              |
| **Command Sequencing (`;`)**         | ⏳ Planned     | Will support sequential execution of commands                        |
| **Background Execution (`&`)**       | ⏳ Planned     | Will enable commands to run in background                            |
| **Environment Variable Expansion**   | ✅ Implemented | Supports `$VAR` expansion in command arguments                       |
| **Alias Expansion**                  | ✅ Implemented | Includes alias management via `alias` and `unalias`                  |
| **Variable Assignment**              | ✅ Implemented | Shell variable creation with `set`, `unset`, and assignment syntax   |
| **Command History**                  | ✅ Implemented | Maintains session history and `history` command                      |
| **Built-in `exit`**                  | ✅ Implemented | Cleanly exits shell session                                          |
| **Script Execution Support**         | ⏳ Planned     | Shell script execution (e.g., `.sh` files) not yet supported         |
| **Sourcing Configuration File**      | ✅ Implemented | Loads `.lshellrc` at startup                                         |
| **Error Handling**                   | ✅ Partial     | Basic error output; refinement in progress                           |
| **Custom Prompt Support**            | ✅ Implemented | Customizable prompt with current directory support                   |
| **Directory Stack (`pushd`/`popd`)** | ❌ Not Yet     | Not implemented                                                      |
| **Job Control (`jobs`, `fg`, `bg`)** | ❌ Not Yet     | Requires signal and process group handling                           |
| **Tab Completion**                   | ❌ Not Yet     | Not yet integrated with custom parser                                |
| **Globbing (`*`, `?`)**              | ⏳ Partial     | Handled by `execvp()` fallback; not custom-expanded yet              |
| **Quoting (`'`, `"`)**               | ✅ Implemented | Basic quote parsing and escaping supported                           |
| **Comments (`#`)**                   | ✅ Implemented | Ignores lines or inline comments starting with `#`                   |
| **Command Substitution (`$(...)`)**  | ❌ Not Yet     | Advanced feature not implemented yet                                 |

---

### 🧠 Summary

- ✅ Most core POSIX shell features are working.
- 🔧 I/O redirection, pipes, variables, and aliasing are fully functional.
- 🛠️ Next major milestones include job control, scripting support, and background execution.

