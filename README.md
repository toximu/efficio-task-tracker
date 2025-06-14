# Efficio :: Task-Tracker

[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-41CD52?style=for-the-badge&logo=qt&logoColor=white)](https://www.qt.io/)
[![PostgreSQL](https://img.shields.io/badge/PostgreSQL-4169E1?style=for-the-badge&logo=postgresql&logoColor=white)](https://www.postgresql.org/)
[![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)](https://www.linux.org/)
[![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)

> A collaborative task tracker that will allow teams to plan, manage tasks and work together. Each user will have their own set of project boards where they can create notes that will be visible to users who have access to the project.

## Features

- **Collaborative editing of tasks:** Users can see changes made by other team members.
- **Save change history:** Each action is saved so users can track changes made and roll back if necessary.
- **Local data storage:** The ability to save data locally without the need to use the cloud, providing increased privacy. As a consequence the ability to work without an internet connection.
- **Easy customization and customization:** Users can change the appearance of the application and the structure of workspaces to suit their needs.

## Installation

1. Clone the repository

```bash
git clone git@github.com:toximu/efficio-task-tracker.git
```

2. Create **efficio** user

```SQL
CREATE USER efficio WITH PASSWORD 'admin';
CREATE DATABASE efficio OWNER efficio;
GRANT ALL PRIVILEGES ON DATABASE efficio TO efficio;
\q
```

3. Build

```bash
mkdir -p build && cd build
cmake ..
make
```

4. Run the server and client in different terminal windows

```bash
build/server/Server
build/client/EfficioTaskTracker
```

## Recent problems

### 1) libpqxx not installed

```shell
CMake Error at server/service/CMakelists.txt:8 (find_package):
  By not providing "Findlibpqxx.cmake" in CMAKE_MODULE_PATH this project has
  asked CMake to find a package configuration file provided by "libpqxx", 
  but CMake did not find one.
```

1) Clone [libpqxx repository](https://github.com/jtv/libpqxx) into `server/`
2) `cd libpqxx/` then build and install it

```shell
cmake .
cmake --build .
cmake --install .
```

Now try to build **EFFICIO** one more time

## Technologies Used
- Qt 6.8.2
- PostgreSQL 17.4
- CMake 3.28.3
- gRPC 1.72.0
- pqxx 7.9.2-1

## License

This project is licensed under the **MIT License**. See the [LICENSE](https://github.com/toximu/efficio-task-tracker/blob/main/LICENSE) file for details.
