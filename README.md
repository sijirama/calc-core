
# **Calc-Core: The Ultimate C Expression Interpreter**

Welcome to **Calc-Core**! The fastest, most lightweight calculator expression interpreter ever, written in pure **C**! No dependencies required—just make and C with the GCC compiler. Whether you're a programming newbie or a seasoned coder, **Calc-Core** will make evaluating mathematical expressions a breeze!

This interpreter is designed for simplicity and power, allowing you to parse and compute arithmetic expressions directly from the command line with minimal effort. It’s your go-to tool for everything from basic math to complex operations, all executed instantly!

---

## 🚀 **Features**
- **No Dependencies:** Built with just **C** and **Make**. All you need is a **GCC compiler** and you're good to go!
- **Easy to Use:** Evaluate complex expressions directly in your terminal.
- **Supports Common Operators:** Addition (+), Subtraction (-), Multiplication (*), Division (/), and Exponentiation (^).
- **Parentheses Support:** Fully supports operator precedence with parentheses for clear and efficient evaluation.
- **Lightning Fast:** Written in C, with performance that can’t be beat.

---

## ⚡ **Installation**

### Requirements:
- **GCC Compiler**: Make sure you have GCC installed on your machine.
- **Make**: You’ll need Make to build the project.

### Steps:
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/calc-core.git
   cd calc-core
   ```

2. Build the project:
   ```bash
   make
   ```

3. You're ready to roll! The executable is `calc` and can be run from the command line.

---

## 🧮 **Usage Examples**

Start by simply running the program and passing a mathematical expression in quotes as an argument:

```bash
% ./calc "2 ^ 2"
Parsing Expression: 2 ^ 2
4
```

Another example:

```bash
% ./calc "2 + 2 ^ 2"
Parsing Expression: 2 + 2 ^ 2
6
```

And with parentheses:

```bash
% ./calc "(2 + 2) ^ 2"
Parsing Expression: (2 + 2) ^ 2
16
```

---

## 💡 **How It Works**
This interpreter is a command-line tool that reads an arithmetic expression, parses it, and evaluates it. It does so by using a recursive descent parsing algorithm, which ensures that operator precedence (like exponentiation and parentheses) is handled correctly.

When you run the program, it performs the following steps:
1. It **parses** the expression to ensure correct syntax.
2. It **evaluates** the expression based on the rules of arithmetic.
3. It **outputs** the result directly to your terminal.

---

## 🛠 **Building from Source**

If you want to tweak or contribute to this project, feel free to clone the repo and make your changes! To build the project, simply run `make`:

```bash
make
```

This will produce the `calc` binary, which you can use to evaluate any expression you'd like.
