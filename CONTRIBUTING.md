# Contributing to http-server 

Thank you for considering contributing to this project! We welcome all contributions, whether they are bug reports, feature requests, or code improvements.

## Getting Started

### Fork the Repository

1. [Fork the repository](https://github.com/devRajeshThapa/http-server) to your GitHub account.
2. Clone your forked repository to your local machine:
    ```sh
    git clone https://github.com/devRajeshThapa/http-server.git
    cd http-server
    ```

### Setting Up Your Development Environment

1. **Ensure you have the following software installed:**
    - **CMake**: Version 3.28.3 or above
    - **g++**: A C++ compiler
    - **Platform**: Linux, macOS, or Windows Subsystem for Linux (WSL)
2. **Create and build the project:**
    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
    cmake --install . --prefix ../dist
    ```
    > Note: The `dist` directory will be created at the root of the project.

### Making Changes

1. **Check out a new branch:**
    ```sh
    git checkout -b <branch_name>
    ```

2. **Make your changes in the codebase:**
    - Add new features, fix bugs, or improve documentation.
    - Ensure your code follows the coding standards.

3. **Run tests and ensure everything works:**
    - Test created functionality and ensure you don't introduce new bugs.

### Submitting Your Changes

1. **Stage and commit your changes:**
    ```sh
    git add .
    git commit -m "Description of your changes"
    ```

2. **Push your branch to your forked repository:**
    ```sh
    git push origin <branch_name>
    ```

3. **Create a Pull Request (PR):**
    - Open a pull request from your branch on GitHub.
    - Provide a detailed description of your changes.
    - Link any related issues.

### Code Review

- **All contributions will undergo code review**: Feedback may be provided. Make necessary changes according to the feedback.
- **Merge request**: Once approved, your PR will be merged.

### Additional Notes

- **Bug Reports**: Open an issue and provide detailed steps to reproduce the bug.
- **Feature Requests**: Open an issue and describe your proposed feature.
- **Questions and Discussions**: Use the issue tracker or discussions tab on GitHub.

---

Thank you for contributing! Your efforts are greatly appreciated. 😊

