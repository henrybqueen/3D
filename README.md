
# Project Title

Brief description of your project.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

- Git
- CMake
- vcpkg

### Installing

Follow these steps to get your development env running:

#### 0. Clone the Repository

First, clone the repository to your local machine:

```bash
git clone https://github.com/yourusername/yourprojectname.git
```

Navigate to the cloned directory:

```bash
cd yourprojectname
```

#### 1. Install CMake

Ensure you have CMake installed. If not, download and install it from [CMake's official website](https://cmake.org/download/).

#### 2. Install vcpkg

Clone Microsoft's vcpkg repository:

```bash
git clone https://github.com/Microsoft/vcpkg.git
```

Then, bootstrap vcpkg:

```bash
./vcpkg/bootstrap-vcpkg.sh  # On Unix/Linux
.\vcpkg\bootstrap-vcpkg.bat # On Windows
```

#### 3. Add vcpkg Root Path to System Variable

Set the `VCPKG_ROOT` environment variable to the path of your vcpkg installation. Replace `<path_to_vcpkg>` with the actual path to your vcpkg directory.

- **Windows:**

  ```powershell
  [System.Environment]::SetEnvironmentVariable('VCPKG_ROOT', '<path_to_vcpkg>', 'User')
  ```

- **Linux/macOS:**

  Add this line to your `~/.bashrc` or `~/.zshrc`:

  ```bash
  export VCPKG_ROOT="<path_to_vcpkg>"
  ```

  Then, apply the changes:

  ```bash
  source ~/.bashrc  # or source ~/.zshrc
  ```

#### 4. Navigate to Project Repository and Proceed with CMake Build Process

Create a build directory and navigate into it:

```bash
mkdir build && cd build
```

Configure the project with CMake. Ensure you replace `<path_to_source>` with the path to your project's source directory:

```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
```

Finally, build the project:

```bash
cmake --build .
```

## Running the tests

Explain how to run the automated tests for this system (if applicable).

## Deployment

Add additional notes about how to deploy this on a live system.

## Contributing

Please read [CONTRIBUTING.md](https://github.com/yourusername/yourprojectname/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- Hat tip to anyone whose code was used
- Inspiration
- etc
