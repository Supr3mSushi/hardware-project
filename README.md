# Welcome to Hardware Project👋

This hardware project uses an RFID reader with Arduino, a Node.js API (or a Raspberry Pi with a MariaDB database), to create a secure access system. Simply scan your RFID badge and explore the possibilities!


## Table of Contents 🏠
1. [Overview](#overview)
2. [Technologies Used](#technologies-used)
3. [Project Setup](#project-setup)
4. [Usage](#usage)
5. [Contributions](#contributions)
6. [Author](#author)
7. [License](#license)


## Overview
This project combines the physical and digital worlds to create a unique experience. The RFID reader detects badges, sends the data to a Node.js API or a Raspberry Pi with a MariaDB database (your choice), which stores and manages it. An intuitive web interface lets you view and manage badge information in real time.

*Optional: The project can also be configured with a Raspberry Pi and a MariaDB database.


## Technologies Used

- [Node.js](https://nodejs.org/) (Optional)
- [Express](https://expressjs.com/) (Optional)
- [MongoDB](https://www.mongodb.com/) (Optional)
- [Arduino](https://www.arduino.cc/)
- [Raspberry Pi](https://www.raspberrypi.org/)
- [MariaDB](https://mariadb.org/) (Optional)

## Project Setup
### Arduino Setup
1. Connect your RFID reader to your Arduino and make your connections
2. Open the Arduino IDE and load the Arduino sketch provided in the project.
3. Upload the sketch to your Arduino.

### Node.js API Setup (Optional)
1. Install Node.js if not already installed.
2. Navigate to the `api` directory.
3. Run `npm install` to install dependencies.
4. Configure API settings if necessary.

### MongoDB Setup (Optional)
1. **Install MongoDB:**
   - [Follow the MongoDB installation instructions](https://docs.mongodb.com/manual/installation/).

2. **Start the MongoDB Server:**
   - Depending on your operating system, you might start MongoDB using a command like:
     ```bash
     sudo service mongod start
     ```

3. **Create a Database:**
   - Access the MongoDB shell and create a database for your project:
     ```bash
     # Start MongoDB shell
     mongo

     # Create a new database (replace 'yourdbname' with your desired database name)
     use yourdbname
     ```

4. **Update API Configuration:**
   - If necessary, update the API configuration file to connect to MongoDB. You might need to modify the `mongoose.connect` line in your Node.js API code.

     Example (in Node.js):
     ```javascript
     const mongoose = require('mongoose');
     mongoose.connect('mongodb://localhost/yourdbname', { useNewUrlParser: true, useUnifiedTopology: true });
     ```

Make sure to replace 'yourdbname' with the actual name you chose for your MongoDB database.

### Node.js API Setup (Optional)
1. **Install Node.js and npm:**
   - [Follow the Node.js installation instructions](https://nodejs.org/).

2. **Navigate to the `api` Directory:**
   - Open a terminal and navigate to the directory where your Node.js API code is located.

     ```bash
     cd path/to/your/api
     ```

3. **Install Dependencies:**
   - Run the following command to install the necessary dependencies for your Node.js API:

     ```bash
     npm install
     ```

4. **Configure API Settings:**
   - If needed, update the API settings in your code. This might include specifying the port to listen on, database connection details, etc.

     Example (in Node.js):
     ```javascript
     const express = require('express');
     const app = express();
     const port = 3000; // Replace with your desired port

     // Other API configuration...

     app.listen(port, () => {
       console.log(`API listening at http://localhost:${port}`);
     });
     ```
     
### Raspberry Pi Setup (Optional)
1. **Install Debian on Raspberry Pi (Recommended):**
   - [Download and install Debian for Raspberry Pi](https://www.raspberrypi.org/software/operating-systems/).
   - Installing Debian directly is recommended for optimal compatibility.

   *OR*

   **Install Raspberry Pi OS:**
   - If you prefer or already have Raspberry Pi OS, you can use it as well.

2. **Connect RFID Reader to Raspberry Pi:**
   - Ensure your RFID reader is connected to the GPIO pins on the Raspberry Pi.

3. **Install Node.js and npm:**
   - [Follow the Node.js installation instructions for Debian](https://nodejs.org/).

     ```bash
     sudo apt update
     sudo apt install nodejs
     sudo apt install npm
     ```

4. **Navigate to the `api` Directory:**
   - Open a terminal and navigate to the directory where your Node.js API code is located.

     ```bash
     cd path/to/your/api
     ```

5. **Install Dependencies:**
   - Run the following command to install the necessary dependencies for your Node.js API:

     ```bash
     npm install
     ```

6. **Configure API Settings:**
   - If needed, update the API settings in your code. This might include specifying the port to listen on, database connection details, etc.

     Example (in Node.js):
     ```javascript
     const express = require('express');
     const app = express();
     const port = 3000; // Replace with your desired port

     // Other API configuration...

     app.listen(port, () => {
       console.log(`API listening at http://localhost:${port}`);
     });
     ```

Make sure to customize the configuration according to your project requirements.


## Utilisation
To use this project, follow these steps:

### Scan RFID:
Ensure that the RFID reader is connected, and the hardware is configured correctly.

### Launch Arduino:
Upload the code to your Arduino.

### Connect to the API:
Make sure the API is running on the specified server. Refer to the "Deployment" section for more information.

### Scan Badges:
Swipe an RFID badge on the reader. The information will be sent to the API.

### View the Interface:
Check the web interface or dashboard to see badge information and access permissions.

---

**Note:** Customize the steps according to your specific project details. Update the server address, API endpoints, or any other relevant information.


## Contributions 🤝

The development of this project has benefited from the contributions of several talented individuals. We extend our heartfelt thanks to the following contributors:

- [Ozan](https://github.com/osahinGuardia)
- [Amandine](https://github.com/Avg38)
- [Theresty](https://github.com/TherestyGit)

A special thanks to [GhostFighter50](https://github.com/ghostfighter50) for their outstanding work in creating the API.
The associated API for this project can be found on [GitHub](https://github.com/ghostfighter50/BadgeReaderWebApp).

If you would like to contribute to this project, feel free to submit pull requests, report issues, or get in touch with the existing contributors.


## Author 👤
This project was initiated and developed by [Sushi](https://github.com/Supr3mSushi).

If you have any questions, feedback, or would like to contribute, feel free to get in touch.


## License
This project is licensed under the [License](LICENSE).
