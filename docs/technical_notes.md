
## 📌 **Important Notes & Useful Commands**

### 🔹 **Running Bash without Environment Variables or Configurations**

```plaintext
env -i bash --noprofile --norc
```

**What does this command do?**  
It runs **Bash in a clean environment**, without loading configurations or inheriting variables from the current environment.

#### **📌 Breakdown of the Command:**

- **`env -i`** (`--ignore-environment`)
    - Starts a new **empty environment**, without inheriting variables like `PATH`, `HOME`, `USER`.
    - Useful for testing or debugging without inherited configurations.

- **`bash --noprofile --norc`**
    - **`--noprofile`** → Does not load `~/.bash_profile`, `~/.bash_login`, or `/etc/profile`.
    - **`--norc`** → Does not execute `~/.bashrc`, avoiding custom configurations.

### **📌 Example Usage**

To verify that the environment is indeed empty, run:

```sh
  env -i bash --noprofile --norc
  env
```

**Expected Output:** (No environment variables loaded)
```sh
  # Depends the distributions of LINUX, is possible per default linux create 3 or 4 variables.
```

## ENVIRONMENT VARIABLES TO INITIALIZE

### **📌 Environment Configuration in Minishell**

This section describes the **environment variables** that are initialized if they don't exist when running **Minishell**, based on our `configure_shell_env()` function.

---

## **🔹 Initialized Environment Variables**

Minishell checks and creates the following variables if they don't exist in the environment:

| **Variable** | **Purpose** | **Default Value if Not Present** |
|--------------|-------------|----------------------------------|
| `OLDPWD`     | Stores the previous directory for `cd -` | `""` (empty until `cd` modifies it) |
| `PATH`       | Defines directories to search for executable commands | `"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin"` |
| `HOME`       | User's home directory | Value of `getenv("HOME")` or `"/home/"` if not found |
| `USER`       | Current user's name | `getenv("USER")` or `"unknown"` if not found |
| `SHLVL`      | Shell level, increases with each new instance | If `SHLVL >= 100`, resets to `"1"` |

---

## **🔹 Special Handling of `OLDPWD` and `PWD`**

### **Should `OLDPWD` be reset to `""` or remain?**
- If `OLDPWD` already exists with a valid path, **it remains unchanged**.
- If `OLDPWD` does not exist, **it is initialized to `""` (empty)** until `cd` updates it.

### **How does `PWD` behave?**
- `PWD` **remains as is**, as it represents the current directory.
- Bash also keeps it if it exists in `env`.

---

## **🔹 Handling of `SHLVL`**
1. If `SHLVL` **does not exist or is negative**, it is initialized to `0`.
2. If `SHLVL >= 100`, **a warning is displayed, and it is reset to `1`**.
3. In other cases, **it is incremented by `+1`**.

Example warning message if `SHLVL >= 100`:
```sh
mish: warning: shell level (100) too high, resetting to 1
```

---

## **📌 How does this behave in Bash?**

Running **Bash in an empty environment** (`env -i bash --noprofile --norc`), we get:
```sh
  PWD=/home/user
  SHLVL=1
  _=/usr/bin/env
```

**We hope this shell becomes an effective and user-friendly tool for interacting with the system.**

Thank you for reviewing our project, and feel free to contact us with any questions or suggestions!

---