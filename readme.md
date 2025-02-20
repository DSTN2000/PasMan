PasMan is a lightweight crossplatform password manager built with Qt which utilizes a locally stored csv file to save and keep your data.
Here are the core features:

### 🔑 Password Generation
- Automatically generates secure and random passwords using a built-in password generator.
- Displays the generated password directly in the input field.
- Automatically copies the generated password to the system clipboard for easy use.

### 📂 Data Storage
- Stores credentials (website, email/username, and password) in a structured CSV file.
- Ensures clean data storage by trimming unnecessary spaces from entries.
- Reads data from the CSV file on startup to restore saved credentials.

### 🚀 Duplicate Detection
- Prevents duplicate entries by checking for identical website, email, and password combinations.
- Alerts the user via a warning message when duplicate data is detected.
- Ensures data integrity and prevents redundant storage of credentials.

### 🔍 Search Functionality
- Allows quick retrieval of stored credentials by searching for a website name.
- Displays matching email and password information in a message box.
- Notifies users when no matching records are found.

### 🎨 User Interface & Interaction
- Built with Qt for a modern and user-friendly graphical interface.
- Displays a logo and organizes input fields for structured data entry.
- Provides buttons for key actions: password generation, adding new credentials, and searching stored data.
- Confirms new data entries with a dialog box before saving.

### 📋 Clipboard Integration
- Automatically copies generated passwords to the system clipboard.
- Reduces the risk of manual copying errors and enhances usability.

### 📁 File System Handling
- Saves credentials in a system-defined secure location using `QStandardPaths`.
- Creates necessary directories if they do not exist using `QDir`.
- Ensures reliable storage and simplifies backup management.

### ⚠️ Error Handling & Feedback
- Alerts users when required fields are left empty.
- Provides warnings for duplicate entries.
- Displays informative dialog messages for successful or failed operations.
- Uses `qDebug()` for real-time debugging and logging.

### ⚡ Performance & Reliability
- Built on the Qt framework and standard C++ libraries for stability.
- Ensures fast and consistent processing of user requests.
- Implements validation, duplicate checking, and confirmation dialogs to enhance user confidence.
