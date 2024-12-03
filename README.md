
# Interpolate

A mathematical interpolation tool for creating polynomial functions from a given set of points and performing evaluations. The tool offers both an interactive UI mode and an API mode for direct computations.

## Features
- Supports **Lagrange**, **Newton's Forward**, **Newton's Backward**, and **Newton's General Divided** interpolation methods.
- Provides a UI mode for managing points and performing interpolations interactively.
- Allows API mode for quick command-line computations with specified points and methods.
- Optionally uses ANSI escape sequences to clear the terminal for better readability in UI mode.

---

## Modes of Operation

### 1. **UI Mode** (Default)
The interactive mode offers the following commands:
- `set <x> <y>`: Add or update a point.
- `remove <x>`: Remove a point by its x-coordinate.
- `clear`: Remove all registered points.
- `points`: Display all registered points.
- `<method> [<x>]`: Interpolate using the specified method. If an x-value is provided, directly evaluates the resulting polynomial at x.
- `quit`: Exit the program.

**How to Run UI Mode:**  
Simply double-click or run the program without any arguments.  

---

### 2. **API Mode**
The API mode enables direct interpolation from the command line.

#### Usage
```bash
interpolate <method> [options] <x0> <y0> ... <xn> <yn>
```

#### Options
- `-h`: Changes the output format to a mathematical function rather than a set of coefficients.

#### Examples
```bash
interpolate lagranges -h 0 0 1 1 -1 1
x^2

interpolate lagranges 0 0 1 1 -1 1
0 0 1
```

**How to Use API Mode:**  
Run the program with arguments specifying the interpolation method and points.

---

## Supported Interpolation Methods
1. **Lagrange's Interpolation**
2. **Newton's Forward Interpolation**
3. **Newton's Backward Interpolation**
4. **Newton's General Divided Interpolation**

---

## Writing New Interpolation Methods
To add a new interpolation method, follow these steps:

### Step 1: Declare and Implement the Method
- Declare the function in `methods.h` with the following signature:
   ```cpp
   ZK::polynomial new_method(const std::vector<std::pair<long double, long double>>& points);
   ```
   - The function must take a `std::vector` of point pairs as input.
   - It must return a `ZK::polynomial`.

- Implement the function in `methods.cpp`.

---

### Step 2: Add the Method to the Methods Map
To add your method, modify the initialization code in `methods.cpp` like so:

```cpp
const std::map<std::string, std::function<ZK::polynomial(const std::vector<std::pair<long double, long double>>&)>>
methods = {
    {"lagranges", lagranges},
    {"newtons_forward", newtons_forward},
    {"newtons_backward", newtons_backward},
    {"newtons_general_divided", newtons_general_divided},
    {"unique_method_name", new_method} // Add your method here
};
```

Ensure that:
- The key (e.g., `"unique_method_name"`) is a unique string with no spaces.
- The value is a reference to your declared and implemented function.

---

## Enabling ANSI Escape Sequences (optional)
The program uses ANSI escape sequences in UI mode to clear the terminal and enhance readability.  

### Windows Users
To enable ANSI escape sequences on Windows, execute the following command in an **Administrator Command Prompt**:
```bash
REG ADD HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1
```

This change allows your terminal to support ANSI escape sequences for better UI display. Note that this is optional and not required for functionality.

---

## Contributing
Contributions for adding new interpolation methods are welcome!  
Follow the instructions provided in the "Writing New Interpolation Methods" section to get started.

---
