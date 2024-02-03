#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Tutor {
    char tutorID[20];
    char name[50];
    char title[50];
    char email[50];
    char password[20];
    int assignedSessionIndex; // Index of assigned session in the sessions array
};

struct Session {
    char sessionCode[20];
    char title[50];
    char day[20];
    char startTime[20];
    char location[50];
    char tutorID[20];
    int maxCapacity; // Maximum capacity of the session (maximum number of students it can accommodate)
    int numEnrolled; // Number of students currently enrolled in the session
};



struct Student {
    char TPNumber[20];
    char name[50];
    char email[50];
    char sessionCodes[100][20]; // Array to store assigned session codes
    int numSessions; // Number of assigned sessions
    char password[20];
};

char adminPassword[20] = "@Password123";
char currentTutorID[20];
char currentTPNumber[50];
char studentName[50];

struct Tutor tutors[100] = {
    { "T01", "Albert", "Python Programming", "albert@mail.apu.edu.my", "@Password1" },
    { "T02", "Amad", "Java Programming", "amad@mail.apu.edu.my", "@Password2" },
    { "T03", "Steve", "C Progromming", "steve@mail.apu.edu.my", "@Password3" },
    { "T04", "Drake", "Web Development", "drake@mail.apu.edu.my", "@Password4" },
    { "T05", "Ben", "C Sharp Programming", "ben@mail.apu.edu.my", "@Password5" }
};

struct Session sessions[100] = {
    {"PYP101", "Python Programming", "Saturday", "9.00am", "C-01-01", "T01", 50, 0},
    {"JAV102", "Java Programming", "Sunday", "9.00am", "C-01-02", "T02", 50, 0},
    {"CPL103", "C Programming", "Saturday", "2.00pm", "C-01-03", "T03", 50, 0},
    {"WEB104", "Web Development", "Sunday", "2.00pm", "C-01-04", "T04", 50, 0},
    {"CSP105", "C Sharp Programming", "Monday", "7.00pm", "C-01-05", "T05", 50, 0}
};
struct Student students[100];
int numTutors = 5;            // The total number of tutors in the system
int numSessions = 5;          // The total number of sessions in the system
int numStudents = 0;          // The total number of students in the system
int enrolledStudents[100][100];   // 2D array to store the enrollment status of students in sessions. Rows represent students and columns represent sessions
int preAddedSessions = 6;     // The number of sessions pre-added to the system before user input



// Function to validate tutorID input
int validateTutorID(const char* tutorID) {

    // Check if tutor ID is not empty
    if (strlen(tutorID) == 0) {
        printf("Tutor ID cannot be empty. Please try again.\n");
        return 0;
    }

    // Check if the tutor ID starts with 'T'
    if (tutorID[0] != 'T' || !isdigit(tutorID[1])) {
        printf("Invalid Tutor ID. Tutor ID should start with the letter 'T' followed by a digit. Please try again.\n");
        return 0;
    }


    // Check if the tutor ID is already registered
    for (int i = 0; i < numTutors; i++) {
        if (strcmp(tutors[i].tutorID, tutorID) == 0) {
            printf("Tutor ID is already registered. Please try again with a different ID.\n");
            return 0;
        }
    }

    return 1;
}


// Function to validate name input
int validateName(const char *name) {

    // Check if name is not empty
    if (strlen(name) == 0) {
        printf("Name cannot be empty. Please try again.\n");
        return 0;
    }
    return 1;
}

// Function to validate title input
int validateTitle(const char *title) {

    //check if title is not empty
    if (strlen(title) == 0) {
        printf("Title cannot be empty. Please try again.\n");
        return 0;
    }
    return 1;
}

int validateEmail(const char *email) {

    //check if email is not empty
    if (strlen(email) == 0) {
        printf("Email cannot be empty. Please try again.\n");
        return 0;
    }

    // Check if email contains '@' symbol
    const char atSymbol = strchr(email, '@'); // strchr searches for @ in email
    if (atSymbol == NULL) {
        printf("Invalid email format. Please enter a valid email address.\n");
        return 0;
    }



    return 1;
}

// Function to find the index of a tutor with the given tutorID.
int findTutorIndex(const char* tutorID) {
    for (int i = 0; i < numTutors; i++) {
        if (strcmp(tutors[i].tutorID, tutorID) == 0) {
            return i;
        }
    }
    return -1;  // Tutor not found
}

// Function to find the index of a student with the given TPNumber
int findStudentIndex(const char TPNumber[20]) {
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].TPNumber, TPNumber) == 0) {
            return i; // Return the index of the found student
        }
    }
    return -1; // Return -1 if student is not found
}

//Function to find the index of a session with the given sessioncode.
int findSessionIndex(char sessionCode[20]) {
    for (int i = 0; i < 100; i++) {

        if (strcmp(sessions[i].sessionCode, sessionCode) == 0) {
            return i;  // Return the index of the session if found
        }
    }
    return -1;  // Return -1 if session is not found
}


//Function to validate the password based on specific requirements.
int validatePassword(char* password) {
    int length = strlen(password);
    int hasSpecialChar = 0;
    int hasUppercase = 0;
    int hasNumber = 0;
    char* specialChars = "!@#$%^&*()-=_+[]{}|;:,.<>?/";

    if (length < 8) {
        return -1;  // Password length is less than 8 characters
    }

    for (int i = 0; i < length; i++) {
        if (password[i] == ' ') {
            return -1;  // Password contains a space
        }

        if (strchr(specialChars, password[i]) != NULL)
            hasSpecialChar = 1;  // Password contains a special character
        else if (password[i] >= 'A' && password[i] <= 'Z')
            hasUppercase = 1;  // Password contains an uppercase letter
        else if (password[i] >= '0' && password[i] <= '9')
            hasNumber = 1;  // Password contains a number
    }

    if (!hasSpecialChar || !hasUppercase || !hasNumber) {
        return -1;  // Password does not meet all requirements
    }

    return 0;  // Password meets all requirements
}

// Function to register a tutor
void registerTutor() {
    struct Tutor tutor;

    int validTutorID = 0;
    while (validTutorID == 0) {
        printf("Enter tutor ID: ");
        scanf("%19s", tutor.tutorID);
        getchar(); // Consume the newline character
        validTutorID = validateTutorID(tutor.tutorID);

        // Check if the tutor ID already exists
        if (validTutorID && findTutorIndex(tutor.tutorID) != -1) {
            printf("Tutor with the same ID already exists. Please enter a unique tutor ID.\n");
            validTutorID = 0;
        }
    }

    int validName = 0;
    while (validName == 0) {
        printf("Enter name: ");
        fgets(tutor.name, sizeof(tutor.name), stdin);
        tutor.name[strcspn(tutor.name, "\n")] = '\0'; // Remove trailing newline
        validName = validateName(tutor.name);
    }

    int validTitle = 0;
    while (validTitle == 0) {
        printf("Enter title: ");
        fgets(tutor.title, sizeof(tutor.title), stdin);
        tutor.title[strcspn(tutor.title, "\n")] = '\0';
        validTitle = validateTitle(tutor.title);
    }

    int validEmail = 0;
    do {

        printf("Enter email: ");
        scanf("%49s", tutor.email);
        getchar();
        validEmail = validateEmail(tutor.email);
    } while (validEmail == 0);

    printf("Enter password (at least 8 characters with no spaces, at least one special character, one uppercase letter, and one number): ");
    scanf("%s", tutor.password);
    getchar();

    while (validatePassword(tutor.password) == -1) {
        printf("Invalid password. Please try again: ");
        scanf("%s", tutor.password);
        getchar();
    }

    tutors[numTutors] = tutor;
    numTutors++;
    printf("Tutor registered successfully.\n");
}

//Function to remove a tutor
void removeTutor() {
    char tutorID[20];
    printf("Enter tutor ID to remove: ");
    scanf("%s", tutorID);

    // Find the index of the tutor with the given tutor ID
    int tutorIndex = findTutorIndex(tutorID);

    if (tutorIndex != -1) {
        // Shift remaining tutors to fill the gap
        for (int j = tutorIndex; j < numTutors - 1; j++) {
            tutors[j] = tutors[j + 1];
        }
        numTutors--;
        printf("Tutor removed successfully.\n");
    } else {
        printf("Tutor not found.\n");
    }
}

//  Function to add a new session
void addSession() {
    if (numSessions >= 100) {
        printf("Maximum session capacity reached.\n");
        return; // Exit the function if the maximum capacity is reached
    }

    struct Session session;
    printf("Enter sessionCode: ");
    scanf("%19s", session.sessionCode);
    getchar(); // Consume newline character

    printf("Enter title: ");
    fgets(session.title, sizeof(session.title), stdin);
    session.title[strcspn(session.title, "\n")] = '\0'; // Remove trailing newline

    printf("Enter day: ");
    fgets(session.day, sizeof(session.day), stdin);
    session.day[strcspn(session.day, "\n")] = '\0'; // Remove trailing newline

    printf("Enter startTime: ");
    fgets(session.startTime, sizeof(session.startTime), stdin);
    session.startTime[strcspn(session.startTime, "\n")] = '\0'; // Remove trailing newline

    // Check if startTime contains any spaces
    for (int i = 0; session.startTime[i] != '\0'; i++) {
        if (session.startTime[i] == ' ') {
            printf("Invalid start time. Please enter a valid time without spaces.\n");
            return; // Exit the function if spaces are detected
        }
    }

    printf("Enter location: ");
    fgets(session.location, sizeof(session.location), stdin);
    session.location[strcspn(session.location, "\n")] = '\0'; // Remove trailing newline

    printf("Enter tutorID: ");
    scanf("%19s", session.tutorID);
    getchar(); // Consume newline character

    // Check if the tutor exists
    int tutorIndex = findTutorIndex(session.tutorID);
    if (tutorIndex == -1) {
        printf("Tutor not found. Please enter a valid tutorID.\n");
        return; // Exit the function if tutor not found
    }

    // Check if the tutor is already assigned to another session
    for (int i = 0; i < numSessions; i++) {
        if (strcmp(tutors[tutorIndex].tutorID, sessions[i].tutorID) == 0) {
            printf("Tutor is already assigned to another session.\n");
            return; // Exit the function if tutor is already assigned
        }
    }

    printf("Enter session capacity: ");
    scanf("%d", &session.maxCapacity);
    getchar(); // Consume newline character

    session.numEnrolled = 0; // Initialize the number of enrolled students

    // Add the new session to the sessions array
    sessions[numSessions] = session;
    numSessions++;
    preAddedSessions++;

    printf("Session added successfully.\n");
}

//Function to remove a session
void removeSession() {
    char sessionCode[20];
    printf("Enter sessionCode to remove: ");
    scanf("%s", sessionCode);

    int sessionFound = 0;

    for (int i = 0; i < numSessions; i++) {
        if (strcmp(sessions[i].sessionCode, sessionCode) == 0) {
            sessionFound = 1;

            // Find the tutor associated with the session
            int tutorIndex = -1;
            for (int j = 0; j < numTutors; j++) {
                if (strcmp(sessions[i].tutorID, tutors[j].tutorID) == 0) {
                    tutorIndex = j;
                    break;
                }
            }

            // Shift remaining sessions to fill the gap
            for (int j = i; j < numSessions - 1; j++) {
                sessions[j] = sessions[j + 1];
            }

            // Update assignedSessionIndex for the tutor
            if (tutorIndex != -1) {
                tutors[tutorIndex].assignedSessionIndex = -1; // No longer assigned to any session
            }

            // Remove the session from the students' assigned sessions
            for (int m = 0; m < numStudents; m++) {
                for (int n = 0; n < 100; n++) {
                    if (strcmp(students[m].sessionCodes[n], sessionCode) == 0) {
                        // Shift remaining sessions to fill the gap
                        for (int p = n; p < students[m].numSessions - 1; p++) {
                            strcpy(students[m].sessionCodes[p], students[m].sessionCodes[p + 1]);
                        }
                        students[m].numSessions--;
                    }
                }
            }

            numSessions--;
            printf("Session removed successfully.\n");
        }
    }

    if (sessionFound == 0) {
        printf("Session not found.\n");
    }
}

//Function to register a student
void registerStudent() {
    struct Student student;

    printf("Enter TPNumber: ");
    scanf("%19s", student.TPNumber);
    getchar(); // Consume newline character

    printf("Enter name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0'; // Remove trailing newline

    if (strlen(student.name) < 2 || strlen(student.name) > 49) {
        printf("Invalid name. Name must be between 2 and 49 characters.\n");
        return;
    }

    printf("Enter email: ");
    scanf("%49s", student.email);
    getchar();

    if (!validateEmail(student.email)) {
        return;
    }

    int isValidPassword = 0;
    do {
        printf("Enter password (at least 8 characters with no spaces, at least one special character, one uppercase letter, and one number): ");
        scanf("%19s", student.password);
        getchar();

        if (validatePassword(student.password) == -1) {
            printf("Invalid password. Please try again.\n");
        } else {
            isValidPassword = 1;
        }
    } while (!isValidPassword);

    students[numStudents] = student;
    numStudents++;
    printf("Student registered successfully.\n");
}

//Function to remove a student
void removeStudent() {
    char TPNumber[20];
    printf("Enter TPNumber to remove: ");
    scanf("%s", TPNumber);

    int studentIndex = findStudentIndex(TPNumber);

    if (studentIndex != -1) {
        // Shift remaining students to fill the gap
        for (int i = studentIndex; i < numStudents - 1; i++) {
            students[i] = students[i + 1];
        }
        numStudents--;
        printf("Student removed successfully.\n");
    } else {
        printf("Student not found.\n");
    }
}

// Function to enroll a student in a session
void enrollStudent() {
    char sessionCode[20];
    char tpNumber[20];

    printf("Enter TPNumber: ");
    scanf("%s", tpNumber);

    printf("Enter sessionCode: ");
    scanf("%s", sessionCode);

    // Find the index of the session with the given sessionCode
    int sessionIndex = findSessionIndex(sessionCode);

    if (sessionIndex != -1) {
        // Check if the session has reached its maximum capacity
        if (sessions[sessionIndex].numEnrolled >= sessions[sessionIndex].maxCapacity) {
            printf("Session is already full. Cannot enroll more students.\n");
            return;
        }

        // Find the index of the student with the given TPNumber
        int studentIndex = findStudentIndex(tpNumber);

        if (studentIndex != -1) {
            // Check if the student is already enrolled in the session
            if (enrolledStudents[studentIndex][sessionIndex] == 1) {
                printf("Student is already enrolled in the session.\n");
                return;
            }

            // Enroll the student in the session
            enrolledStudents[studentIndex][sessionIndex] = 1;
            sessions[sessionIndex].numEnrolled++;

            printf("Student enrolled in the session successfully.\n");
        } else {
            printf("Student not found. Please register as a student first.\n");
        }
    } else {
        printf("Session not found.\n");
    }
}


void listSessionsAndStudents() {
    const char* FILE_NAME = "Programming Cafe Sessions and Participating Students.txt";

    // Open the file for writing
    FILE* file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file '%s'.\n", FILE_NAME);
        return;
    }

    // Write column headers to the file
    fprintf(file, "%-20s %-20s %-20s %-20s\n", "Student Name", "Session Code", "Tutor Code", "Location");
    fprintf(file, "------------------------------------------------------------------------------\n");

    // Print the session and student information
    for (int i = 0; i < numSessions; i++) {
        int isSessionEnrolled = 0; // Variable to check if any student is enrolled in the session

        // Print student name, session code, tutor name, and location
        for (int j = 0; j < numStudents; j++) {
            if (enrolledStudents[j][i] == 1) {
                fprintf(file, "%-20s ", students[j].name);
                fprintf(file, "%-20s ", sessions[i].sessionCode);
                fprintf(file, "%-20s ", tutors[findTutorIndex(sessions[i].tutorID)].name);
                fprintf(file, "%-20s\n", sessions[i].location);
                isSessionEnrolled = 1;
            }
        }

        // Print an empty space if no student is enrolled in the session
        if (!isSessionEnrolled) {
            fprintf(file, "%-20s ", "");
            fprintf(file, "%-20s ", sessions[i].sessionCode);
            fprintf(file, "%-20s ", tutors[findTutorIndex(sessions[i].tutorID)].name);
            fprintf(file, "%-20s\n", sessions[i].location);
        }
    }

    // Close the file
    if (fclose(file) != 0) {
        printf("Error closing file '%s'.\n", FILE_NAME);
        return;
    }

    printf("Sessions and students information written to '%s' successfully.\n", FILE_NAME);
}

//Function to list schedule of sessions.
void listSessionsSchedule() {
    const char* FILE_NAME = "Programming Cafe Sessions Schedule.txt";

    // Open the file for writing
    FILE* file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file '%s'.\n", FILE_NAME);
        return;
    }

    // Write the header line to the file
    fprintf(file, "%-20s %-20s %-20s %-20s %-20s %-20s\n", "Session Code", "Title", "Tutor Code", "Day", "Start Time", "Location");
    fprintf(file, "------------------------------------------------------------------------------------------------------------------\n");

    // Print the preadded sessions
    for (int i = 0; i < numSessions; i++) {
        // Adjust the loop limit according to the number of predefined sessions
        // Write session details to the file
        fprintf(file, "%-20s ", sessions[i].sessionCode);
        fprintf(file, "%-20s ", sessions[i].title);
        fprintf(file, "%-20s ", tutors[i].name);
        fprintf(file, "%-20s ", sessions[i].day);
        fprintf(file, "%-20s ", sessions[i].startTime);
        fprintf(file, "%-20s\n\n", sessions[i].location);
    }

    // Close the file
    if (fclose(file) != 0) {
        printf("Error closing file '%s'.\n", FILE_NAME);
        return;
    }

    printf("Sessions Schedule information written to '%s' successfully.\n", FILE_NAME);
}

//Function to check how many students are enrolled in a session
void getSessionEnrollmentStatus() {
    char sessionCode[20];
    printf("Enter sessionCode: ");
    scanf("%19s", sessionCode);

    // Find the index of the session with the given code
    int sessionIndex = findSessionIndex(sessionCode);

    // Check if the session is not found
    if (sessionIndex == -1) {
        printf("Session not found.\n");
        return;
    }

    printf("Enrollment status for session %s:\n", sessionCode);

    printf("Enrollment: %d/%d\n", sessions[sessionIndex].numEnrolled, sessions[sessionIndex].maxCapacity);
}

//Function to update session schedule
void setSessionSchedule() {
    char sessionCode[20];
    printf("Enter sessionCode: ");
    scanf("%19s", sessionCode);

    // Find the session with the given code
    struct Session* session = NULL;
    for (int i = 0; i < numSessions; i++) {
        if (strcmp(sessions[i].sessionCode, sessionCode) == 0) {
            session = &sessions[i];
            break;
        }
    }

    // Check if the session is not found
    if (session == NULL) {
        printf("Session not found.\n");
        return;
    }

    char newDay[20];
    printf("Enter new day: ");
    scanf("%19s", newDay);

    char newStartTime[20];
    printf("Enter new startTime: ");
    scanf("%19s", newStartTime);

    // Check if the input day or start time exceeds the maximum length
    if (strlen(newDay) > 19 || strlen(newStartTime) > 19) {
        printf("Invalid input: day or startTime exceeds maximum length.\n");
        return;
    }

    // Check if the session schedule remains unchanged
    if (strcmp(session->day, newDay) == 0 && strcmp(session->startTime, newStartTime) == 0) {
        printf("Session schedule remains unchanged.\n");
        return;
    }

    // Update the session's day and start time
    strncpy(session->day, newDay, sizeof(session->day));
    strncpy(session->startTime, newStartTime, sizeof(session->startTime));

    printf("Session schedule updated successfully.\n");
}


//Function to update no. of students in a session
void setSessionCapacity() {
    char sessionCode[20];
    int newCapacity;

    printf("Enter sessionCode: ");
    scanf("%19s", sessionCode);

    // Find the index of the session with the given code
    int sessionIndex = findSessionIndex(sessionCode);
    if (sessionIndex == -1) {
        printf("Session not found.\n");
        return;
    }

    printf("Enter new maxCapacity: ");
    scanf("%d", &newCapacity);

    // Check if the new capacity is a valid positive value
    if (newCapacity <= 0) {
        printf("Invalid capacity. Capacity must be a positive value.\n");
        return;
    }

    // Get a reference to the session
    struct Session* session = &sessions[sessionIndex];

    // Check if the session code length exceeds the maximum length
    if (strlen(sessionCode) > 19) {
        printf("Invalid session code length.\n");
        return;
    }

    // Check if the session capacity remains unchanged
    if (session->maxCapacity == newCapacity) {
        printf("Session capacity remains unchanged.\n");
        return;
    }

    // Check if the new capacity is lower than the number of enrolled students
    if (newCapacity < session->numEnrolled) {
        printf("Warning: The new capacity is lower than the number of enrolled students.\n");
        printf("Please handle the excess enrollment accordingly.\n");
        // Additional logic for handling excess enrollment can be added here
    }

    // Update the session's maximum capacity
    session->maxCapacity = newCapacity;
    printf("Session capacity updated successfully.\n");
}

//Function to search for  a tutor's details
void searchTutor() {
    char tutorID[20];
    printf("Enter tutorID: ");

    // Read the tutor ID from user input
    if (scanf("%19s", tutorID) != 1) {
        printf("Invalid input. Please enter a valid tutorID.\n");
        return;
    }

    // Iterate through the list of tutors to find a match
    for (int i = 0; i < numTutors; i++) {
        if (strcmp(tutors[i].tutorID, tutorID) == 0) {
            printf("Tutor Details:\n");
            printf("TutorID: %s\n", tutors[i].tutorID);
            printf("Name: %s\n", tutors[i].name);
            printf("Title: %s\n", tutors[i].title);
            printf("Email: %s\n", tutors[i].email);
            return;
        }
    }

    printf("No tutor found with ID: %s\n", tutorID);
}

//Function to print session details
void printSessionDetails(const struct Session* session) {
    printf("- %s\n", session->title);
}

//Function to search for a student's details
void searchStudent() {
    char TPNumber[20];
    printf("Enter TPNumber: ");

    // Read the TPNumber from user input
    if (scanf("%19s", TPNumber) != 1) {
        printf("Invalid input. Please enter a valid TPNumber.\n");
        return;
    }

    // Find the index of the student with the given TPNumber
    int studentIndex = findStudentIndex(TPNumber);

    if (studentIndex != -1) {
        printf("Student Details:\n");
        printf("TPNumber: %s\n", students[studentIndex].TPNumber);
        printf("Name: %s\n", students[studentIndex].name);
        printf("Email: %s\n", students[studentIndex].email);

        // Iterate through the student's session codes and print session details for each session
        for (int i = 0; i < 100; i++) {
            if (strlen(students[studentIndex].sessionCodes[i]) > 0) {
                int sessionIndex = findSessionIndex(students[studentIndex].sessionCodes[i]);
                if (sessionIndex != -1) {
                    printf("Session Details for Session Code %s:\n", students[studentIndex].sessionCodes[i]);
                    printSessionDetails(&sessions[sessionIndex]);
                }
            }
        }
    } else {
        printf("Student not found.\n");
    }
}

//Function to show logged-in tutor session
void listTutorSession(char* tutorID) {
    int tutorIndex = -1;

    // Find the index of the tutor with the given tutorID
    for (int i = 0; i < numTutors; i++) {
        if (strcmp(tutors[i].tutorID, tutorID) == 0) {
            tutorIndex = i;
            break;
        }
    }

    if (tutorIndex != -1) {
        const char* FILE_NAME = "Assigned Tutor Session.txt";
        FILE* file = fopen(FILE_NAME, "w");
        if (file == NULL) {
            printf("Error opening file '%s'.\n", FILE_NAME);
            return;
        }

        // Write the header of the report to the file
        fprintf(file, "%-20s %-20s %-20s %-20s %-20s\n", "Tutor ID", "Session Code", "Location", "Day", "Start Time");
        fprintf(file, "----------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < numSessions; i++) {
            if (strcmp(tutors[tutorIndex].tutorID, sessions[i].tutorID) == 0) {
                // Write the assigned session information to the file
                fprintf(file, "%-20s ", tutorID);
                fprintf(file, "%-20s ", sessions[i].sessionCode);
                fprintf(file, "%-20s ", sessions[i].location);
                fprintf(file, "%-20s ", sessions[i].day);
                fprintf(file, "%-20s\n", sessions[i].startTime);
            }
        }

        fprintf(file, "\n");

        if (fclose(file) != 0) {
            printf("Error closing file '%s'.\n", FILE_NAME);
            return;
        }

        printf("Tutor sessions information written to '%s' successfully.\n", FILE_NAME);
    } else {
        printf("Tutor not found.\n");
    }
}

//Function to change student password
void changeStudentPassword() {
    char currentPassword[20];
    char newPassword[20];

    printf("Enter current password: ");
    scanf("%19s", currentPassword);
    getchar(); // Consume newline character

    int found = 0; // Flag to track if the logged-in student is found

    // Search for the logged-in student and update the password
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(currentPassword, students[i].password) == 0) {
            found = 1;

            int isValid = 0; // Flag to track if the new password is valid

            do {
                printf("Enter new password (at least 8 characters with no spaces, at least one special character, one uppercase letter, and one number): ");
                scanf("%19s", newPassword);
                getchar(); // Consume newline character

                // Validate the new password (Add your validation criteria)
                if (validatePassword(newPassword) == -1) {
                    printf("Invalid new password. Please try again.\n");
                } else {
                    isValid = 1;
                }
            } while (!isValid);

            // Update the password for the logged-in student
            strcpy(students[i].password, newPassword);
            printf("Password changed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("No student is currently logged in. Password not changed.\n");
    }
}

//Function to change tutor password
void changeTutorPassword() {
    char currentPassword[20];
    char newPassword[20];

    printf("Enter current password: ");
    scanf("%19s", currentPassword);
    getchar(); // Consume newline character

    int found = 0; // Flag to track if the logged-in tutor is found

    // Search for the logged-in tutor and update the password
    for (int i = 0; i < numTutors; i++) {
        if (strcmp(currentPassword, tutors[i].password) == 0) {
            found = 1;

            int isValid = 0; // Flag to track if the new password is valid

            do {
                printf("Enter new password (at least 8 characters with no spaces, at least one special character, one uppercase letter, and one number): ");
                scanf("%19s", newPassword);
                getchar(); // Consume newline character

                // Validate the new password (Add your validation criteria)
                if (validatePassword(newPassword) == -1) {
                    printf("Invalid new password. Please try again.\n");
                } else {
                    isValid = 1;
                }
            } while (!isValid);

            // Update the password for the logged-in tutor
            strcpy(tutors[i].password, newPassword);
            printf("Password changed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("No tutor is currently logged in. Password not changed.\n");
    }
}

//Function to change admin password
void changeAdminPassword() {
    char currentPassword[20];
    char newPassword[20];

    printf("Enter current password: ");
    scanf("%19s", currentPassword);
    getchar(); // Consume newline character

    int found = 0; // Flag to track if the logged-in admin is found

    // Search for the logged-in admin and update the password
    if (strcmp(currentPassword, adminPassword) == 0) {
        found = 1;

        int isValid = 0; // Flag to track if the new password is valid

        do {
            printf("Enter new password (at least 8 characters with no spaces, at least one special character, one uppercase letter, and one number): ");
            scanf("%19s", newPassword);
            getchar(); // Consume newline character

            // Validate the new password (Add your validation criteria)
            if (validatePassword(newPassword) == -1) {
                printf("Invalid new password. Please try again.\n");
            } else {
                isValid = 1;
            }
        } while (!isValid);

        // Update the password for the logged-in admin
        strcpy(adminPassword, newPassword);
        printf("Password changed successfully.\n");
    }

    if (!found) {
        printf("No admin is currently logged in. Password not changed.\n");
    }
}

//Function to change student password by admin
void adminChangeStudentPassword() {
    char tpNumber[20];
    char newPassword[20];

    // Prompt for TPNumber and validate
    printf("Enter TPNumber of the student: ");
    scanf("%19s", tpNumber);
    getchar(); // Consume newline character

    int found = 0; // Flag to track if the student is found

    // Search for the student and update the password
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(tpNumber, students[i].TPNumber) == 0) {
            found = 1;

            int isValid = 0; // Flag to track if the new password is valid

            do {
                printf("Enter new password (at least 8 characters with no spaces, at least one special character, one uppercase letter, and one number): ");
                scanf("%19s", newPassword);
                getchar(); // Consume newline character

                // Validate the new password (Add your validation criteria)
                if (validatePassword(newPassword) == -1) {
                    printf("Invalid new password. Please try again.\n");
                } else {
                    isValid = 1;
                }
            } while (!isValid);

            // Update the password for the student
            strcpy(students[i].password, newPassword);
            printf("Password changed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Student with TPNumber '%s' not found. Password not changed.\n", tpNumber);
    }
}

//Function to change tutor password by admin
void adminChangeTutorPassword() {
    char tutorID[20];
    char newPassword[20];

    // Prompt for Tutor ID and validate
    printf("Enter Tutor ID of the tutor: ");
    scanf("%19s", tutorID);
    getchar(); // Consume newline character

    int found = 0; // Flag to track if the tutor is found

    // Search for the tutor and update the password
    for (int i = 0; i < numTutors; i++) {
        if (strcmp(tutorID, tutors[i].tutorID) == 0) {
            found = 1;

            int isValid = 0; // Flag to track if the new password is valid

            do {
                printf("Enter new password (at least 8 characters with no spaces, at least one special character, one uppercase letter, and one number): ");
                scanf("%19s", newPassword);
                getchar(); // Consume newline character

                // Validate the new password (Add your validation criteria)
                if (validatePassword(newPassword) == -1) {
                    printf("Invalid new password. Please try again.\n");
                } else {
                    isValid = 1;
                }
            } while (!isValid);

            // Update the password for the tutor
            strcpy(tutors[i].password, newPassword);
            printf("Password changed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Tutor with Tutor ID '%s' not found. Password not changed.\n", tutorID);
    }
}

//Function to list sessions of enrolled logged-in student
void printStudentEnrolledSessions(const char* tpNumber) {
    char fileName[100];
    sprintf(fileName, "%s_enrolled_sessions.txt", currentTPNumber);

    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file '%s'.\n", fileName);
        return;
    }

    fprintf(file, "%-20s %-20s %-20s %-20s %-20s\n", "Session Code", "Tutor Code", "Day", "Start Time", "Location");
    fprintf(file, "--------------------------------------------------------------------------------------------------------\n");

    int studentIndex = findStudentIndex(currentTPNumber);

    if (studentIndex == -1) {
        fprintf(file, "Student with TP number %s not found.\n", currentTPNumber);
        fclose(file);
        return;
    }

    for (int i = 0; i < numSessions; i++) {
        if (enrolledStudents[studentIndex][i] == 1) {
            fprintf(file, "%-20s ", sessions[i].sessionCode);
            fprintf(file, "%-20s ", tutors[findTutorIndex(sessions[i].tutorID)].name);
            fprintf(file, "%-20s ", sessions[i].day);
            fprintf(file, "%-20s", sessions[i].startTime);
            fprintf(file, "%-20s\n", sessions[i].location);
        }
    }

    fclose(file);
    printf("Enrolled sessions for student with TP number %s written to '%s' successfully.\n", currentTPNumber, fileName);
}

//Function for Admin menu
void adminInterface() {
    int choice;
    do {
        printf("\nAdmin Interface\n");
        printf("------------------------------\n");
        printf("1. Register Tutor\n");
        printf("2. Remove Tutor\n");
        printf("3. Add Session\n");
        printf("4. Remove Session\n");
        printf("5. Register Student\n");
        printf("6. Remove Student\n");
        printf("7. Enroll Student\n");
        printf("8. List Sessions and Students\n");
        printf("9. List Sessions Schedule\n");
        printf("10. Session Enrollment Status\n");
        printf("11. Set Session Schedule\n");
        printf("12. Set Session Capacity\n");
        printf("13. Search Tutor by TutorID\n");
        printf("14. Search Student by TPNumber\n");
        printf("15. Change Tutor Password\n");
        printf("16. Change Student Password\n");
        printf("17. Change Admin Password\n");
        printf("18. Back\n");
        printf("0. Exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");

        // Validate the input
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            fflush(stdin); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                registerTutor();
                break;
            case 2:
                removeTutor();
                break;
            case 3:
                addSession();
                break;
            case 4:
                removeSession();
                break;
            case 5:
                registerStudent();
                break;
            case 6:
                removeStudent();
                break;
            case 7:
                enrollStudent();
                break;
            case 8:
                listSessionsAndStudents();
                break;
            case 9:
                listSessionsSchedule();
                break;
            case 10:
                getSessionEnrollmentStatus();
                break;
            case 11:
                setSessionSchedule();
                break;
            case 12:
                setSessionCapacity();
                break;
            case 13:
                searchTutor();
                break;
            case 14:
                searchStudent();
                break;
            case 15:
                adminChangeTutorPassword();
                break;
            case 16:
                adminChangeStudentPassword();
                break;
            case 17:
                changeAdminPassword();
                break;
            case 18:
                main();
                break;
            case 0:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (1);
}

//Function for tutor menu
void tutorInterface() {
    int choice;
    do {
        printf("\nTutor Interface\n");
        printf("------------------------------\n");
        printf("1. List Sessions Schedule\n");
        printf("2. Check Assigned Session\n");
        printf("3. Search Student by TPNumber\n");
        printf("4. Change Password\n");
        printf("5. Back\n");
        printf("0. Exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");

        // Validate the input
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue; // Skip the rest of the loop and ask for input again
        }

        // Perform actions based on the user's choice
        switch (choice) {
            case 1:
                listSessionsSchedule();
                break;
            case 2:
                listTutorSession(currentTutorID);
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                changeTutorPassword();
                break;
            case 5:
                main();
                break;
            case 0:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}

//Function for student menu
void studentInterface() {
    int choice;
    do {
        printf("\nStudent Interface\n");
        printf("------------------------------\n");
        printf("1. List Sessions Schedule\n");
        printf("2. Check Enrolled Sessions\n");
        printf("3. Enroll Student\n");
        printf("4. Search Tutor by TutorID\n");
        printf("5. Change Password\n");
        printf("6. Back\n");
        printf("0. Exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");

        // Validate the input
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue; // Skip the rest of the loop and ask for input again
        }

        // Perform actions based on the user's choice
        switch (choice) {
            case 1:
                listSessionsSchedule();
                break;
            case 2:
                printStudentEnrolledSessions(currentTPNumber);
                break;
            case 3:
                enrollStudent();
                break;
            case 4:
                searchTutor();
                break;
            case 5:
                changeStudentPassword();
                break;
            case 6:
                main();
                break;
            case 0:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}

int main() {
    int userType;

    printf("\nUser Login\n");
    printf("------------------------------\n");
    printf("User Types:\n");
    printf("1. Admin\n");
    printf("2. Tutor\n");
    printf("3. Student\n");
    printf("0. Exit\n");
    printf("------------------------------\n");

    while (1) {
        printf("Enter user type: ");

        // Validate the user type input
        if (scanf("%d", &userType) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue; // Try again
        }

        switch (userType) {
            case 1: {
                printf("Enter admin password: ");
                char password[20];
                scanf("%19s", password);

                // Check if the entered password matches the admin password
                if (strcmp(password, adminPassword) == 0) {
                    adminInterface();
                } else {
                    printf("Incorrect admin password. Access denied.\n\n");
                    continue; // Go back to user type selection
                }
                break;
            }

            case 2: {
                printf("Enter tutor ID: ");
                scanf("%19s", currentTutorID);
                printf("Enter tutor password: ");
                char password[20];
                scanf("%19s", password);

                // Find the tutor index by ID
                int tutorIndex = findTutorIndex(currentTutorID);

                // Check if the tutor is found and the entered password matches the stored password
                if (tutorIndex != -1 && strcmp(password, tutors[tutorIndex].password) == 0) {
                    tutorInterface();
                } else {
                    printf("Incorrect tutor ID or password. Access denied.\n\n");
                    continue; // Go back to user type selection
                }
                break;
            }

            case 3: {
                printf("Enter TP number: ");
                scanf("%19s", currentTPNumber);
                printf("Enter student password: ");
                char password[20];
                scanf("%19s", password);

                // Find the student index by TP number
                int studentIndex = findStudentIndex(currentTPNumber);

                // Check if the student is found and the entered password matches the stored password
                if (studentIndex != -1 && strcmp(password, students[studentIndex].password) == 0) {
                    studentInterface();
                } else {
                    printf("Incorrect TP number or password. Access denied.\n");
                    continue; // Go back to user type selection
                }
                break;
            }

            case 0:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid user type. Please try again.\n");
                continue; // Go back to user type selection
        }

        break;
    }

    return 0;
}
