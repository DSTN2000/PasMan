#include "window.h"
#include "password_gen.h"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QClipboard>
#include <QFile>
#include <QPixmap>
#include <QAbstractButton>
#include <QStandardPaths>
#include <QDir>

PasswordGenerator passwordGenerator;

QLineEdit* passwordEntry;
QLineEdit* websiteEntry;
QLineEdit* emailEntry;

struct DataRow {
    QString website;
    QString email;
    QString password;

    bool operator==(const DataRow& other) const {
        return this->website == other.website && this->password == other.password && this->email == other.email;
    }
};

vector<DataRow> userData;
QString csvFilePath;


void generatePassword() {
    QString password = QString::fromStdString(passwordGenerator.generatePassword()); // Generates a password and saves it as a QString as setText does not accept normal C++ strings
    passwordEntry->setText(password);
    QApplication::clipboard()->setText(password);
}

void saveData() {
    QFile file(csvFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Writes the header
        out << "website,email,password\n";

        for (auto& entry : userData) {
            DataRow row;
            row.website = entry.website.trimmed();
            row.email = entry.email.trimmed();
            row.password = entry.password.trimmed();
            int cnt = count(userData.begin(), userData.end(), row);
            if (cnt==1)
                out << entry.website << "," << entry.email << "," << entry.password << "\n";

            qDebug() << entry.website << "," << entry.email << "," << entry.password << "\n";

        }

        file.close();
        qDebug() << "Data saved to " + csvFilePath << Qt::endl;
    }
}

void loadData() {
    QFile file(csvFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        // Skips the header line
        if (!in.atEnd()) in.readLine();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(',');

            if (fields.size() == 3) {
                DataRow row;
                row.website = fields[0].trimmed();
                row.email = fields[1].trimmed();
                row.password = fields[2].trimmed();

                userData.push_back(row);
            }
        }
        file.close();
    }
}


int main(int argc, char *argv[])
{
    srand(time(0));

    // Gets the default AppDataLocation for currecnt OS
    QString dataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/PasMan";

    csvFilePath = dataLocation + "/password_manager.csv";
    loadData();

    QApplication app(argc, argv);
    Window window;
    window.setWindowState(Qt::WindowMaximized);
    window.setWindowTitle("PasMan");

    auto saveRow = [&](){
        if (websiteEntry->text().isEmpty() || emailEntry->text().isEmpty() || passwordEntry->text().isEmpty()) {
            qDebug() << "test";
            QMessageBox::warning(&window, "Oops", "Don't leave any fields empty!");
            return;
        }
        DataRow new_row;
        new_row.email = emailEntry->text();
        new_row.password = passwordEntry->text();
        new_row.website = websiteEntry->text();
        int cnt = count(userData.begin(), userData.end(), new_row);
        if (cnt)
        {
            QMessageBox::warning(&window, "Oops", "This data is already present!");
            return;
        }

        QMessageBox::StandardButton reply = QMessageBox::question(&window, websiteEntry->text(),
                                                                  "The details entered are:\nWebsite: " + websiteEntry->text() +
                                                                      "\nEmail/Username: " + emailEntry->text() + "\nPassword: " + passwordEntry->text(),
                                                                  QMessageBox::Ok | QMessageBox::Cancel);

        if (reply == QMessageBox::Ok) {
            userData.push_back(new_row);
            saveData(); // Save to CSV

            passwordEntry->clear();
            websiteEntry->clear();

            QMessageBox::information(&window, "Success", "Added new password data");
        }
    };

    auto searchPassword = [&]() {
        QString website = websiteEntry->text();
        QStringList results;

        for (const auto& entry : userData) {
            if (entry.website == website) {
                results << "Email/Username: " + entry.email + "\nPassword: " + entry.password;
            }
        }

        if (results.isEmpty()) {
            QMessageBox::information(&window, website, "No associated data found");
        } else {
            QString message = results.join("\n\n");
            QMessageBox::information(&window, website, message);
        }
    };

    // Creates the data directory if it doesn't exist
    QDir dir(dataLocation);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) { // Creates the directory and any necessary parent directories
            QMessageBox::critical(&window, "Error", "Could not create application data directory.");
        }
    }

    // Creates the grid layout
    QGridLayout *layout = new QGridLayout(&window);

    // Logo
    QLabel *logoLabel = new QLabel(&window);
    QPixmap logoPixmap(":/images/logo.png"); // Load the image
    logoLabel->setPixmap(logoPixmap.scaled(300, 300, Qt::KeepAspectRatio)); // Adds the image to the logoLabel
    layout->addWidget(logoLabel, 0, 1, 1, 1, Qt::AlignCenter);

    // Website label and entry
    QLabel *websiteLabel = new QLabel("Website:", &window);
    layout->addWidget(websiteLabel, 1, 0);
    websiteEntry = new QLineEdit(&window);
    layout->addWidget(websiteEntry, 1, 1);

    // Search button
    QPushButton *searchButton = new QPushButton("Search", &window);
    QAbstractButton::connect(searchButton, &QPushButton::clicked, &window, searchPassword);
    layout->addWidget(searchButton, 1, 2);

    // Email/Username label and entry
    QLabel *emailLabel = new QLabel("Email/Username:", &window);
    layout->addWidget(emailLabel, 2, 0);
    emailEntry = new QLineEdit(&window);
    emailEntry->setText("example@gmail.com");
    layout->addWidget(emailEntry, 2, 1, 1, 2);

    // Password label and entry
    QLabel *passwordLabel = new QLabel("Password:", &window);
    layout->addWidget(passwordLabel, 3, 0);
    passwordEntry = new QLineEdit(&window);
    layout->addWidget(passwordEntry, 3, 1);

    // Generate Password button
    QPushButton *generateButton = new QPushButton("Generate Password", &window);
    QAbstractButton::connect(generateButton, &QPushButton::clicked, &window, generatePassword);
    layout->addWidget(generateButton, 3, 2);

    // Add button
    QPushButton *addButton = new QPushButton("Add", &window);
    QAbstractButton::connect(addButton, &QPushButton::clicked, &window, saveRow);
    layout->addWidget(addButton, 4, 1, 1, 2);
    window.show();
    return app.exec();
}



