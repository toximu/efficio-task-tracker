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

2. Start **PostgreSQL** service

```bash
sudo service postgresql start && sudo -u postgres psql
```

3. Create **efficio** user

```SQL
CREATE USER efficio WITH PASSWORD 'admin';
CREATE DATABASE efficio OWNER efficio;
GRANT ALL PRIVILEGES ON DATABASE efficio TO efficio;
\q
```

4. Enter under **efficio** profile

```bash
psql -U efficio -d efficio -h localhost
```

> After that run the server on address **localhost** and **port** 5433 in your pgAdmin4

5. Build and start app

```bash
mkdir -p build && cd build
cmake ..
make
./EfficioTaskTracker -platform xcb
```

## Technologies Used
- Qt 6.8.2
- PostgreSQL 17.4
- CMake 3.28.3
- VcXsrv server (XLaunch)

## License

This project is licensed under the **MIT License**. See the [LICENSE](https://github.com/toximu/efficio-task-tracker/blob/main/LICENSE) file for details.
