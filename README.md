# APU Programming Café Management System

## Overview

The APU Programming Café Management System is designed to enhance students' problem-solving and coding confidence. It facilitates two-hour, tutor-led programming sessions conducted outside the regular academic timetable. These sessions are led by graduate tutors who are compensated at a flat rate per session and are available for selected programming languages.

## Features

### User Management
*   **Admin:**
    *   Add, remove, and manage student accounts.
    *   Add, remove, and manage tutor accounts.
*   **Tutor:**
    *   View their assigned programming sessions.
    *   Manage interactions with enrolled students.
*   **Student:**
    *   Enroll in available programming sessions.
    *   View their personal session schedules.
    *   Manage their user profile.

### Session Management
*   Create, delete, and view programming sessions.
*   Configure session schedules and capacities.

### Enrollment & Reporting
*   Enroll students into sessions, with automatic capacity checks.
*   Generate and manage reports detailing enrollment status and session status.

## Technologies

*   **Programming Language:** C
*   **File I/O:** Used for generating and managing reports.
*   **Data Structures:** Implemented for managing users, sessions, and enrollments.

## Getting Started

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/yourusername/APU-Programming-Cafe-Management-System.git
    ```
2.  **Navigate to the project directory:**
    ```bash
    cd APU-Programming-Cafe-Management-System
    ```
3.  **Build the project:**
    ```bash
    gcc -o cafe_management_system cafe_management_system.c
    ```
4.  **Run the application:**
    ```bash
    ./cafe_management_system
    ```

## Usage

Upon launching the program, users will be prompted to select their role: **Admin**, **Tutor**, or **Student**.

*   **Admin:** Can manage all aspects of user accounts and programming sessions.
*   **Tutor:** Can review their assigned sessions and interact with students who have enrolled.
*   **Student:** Can browse available programming sessions and enroll in desired sessions.

## Sample Outputs

*   A list of active sessions, including the students enrolled in each.
*   Comprehensive reports on enrollment status and session status.

## Contributing

We welcome contributions! Please follow these steps:

1.  **Fork the repository.**
2.  **Create a new feature branch** for your contributions.
3.  **Commit your changes** and open a pull request.
4.  **Open issues** to report bugs or suggest enhancements.
