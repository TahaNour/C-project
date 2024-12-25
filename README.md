URL Shortener                                                                                                                                                    

I.  Introduction                                                                                                                                                   This application provides a URL shortening service that includes a web interface for users, a C application for encoding and decoding URLs, and a database to map short and long URLs.


Objective: To provide a fast and efficient URL shortening service.


II. Features 
1)  Shortening Long URLs into Short Links The application allows users to convert long, complex URLs into short, user-friendly links. This feature improves readability and facilitates easier sharing across various platforms.
2)  Automatic Redirection to Original URLs When a short link is accessed, the system automatically redirects the user to the corresponding original URL, providing a seamless browsing experience.
3)  User-Friendly Web Interface The web interface is designed to be simple and intuitive, allowing users to easily create and access short links.)  
4)  Flask-Based Backend The backend is built using Flask, a lightweight Python web framework that ensures efficient handling of user requests, processing, and communication between the web interface and the URL encoding/decoding logic.
5)  Encoding and Decoding Algorithm in C A robust algorithm implemented in C is used for encoding long URLs into unique short codes and decoding them back into their original form. This approach leverages the speed and reliability of C for optimal performance.

III. Project Architecture 
The project uses a modular architecture to ensure smooth interaction between its components.
1)  Web Interface: Developed using HTML, CSS, and JavaScript, the web interface is the primary point of interaction, allowing users to input long URLs to generate short links.
2=)  Flask Server: Acts as the backbone of the application, providing a REST API for communication between the web interface and the C application. It handles HTTP requests (e.g., POST for creating short URLs, GET for redirection) and ensures efficient data flow.
3)  C Application: Implements the core algorithm to convert long URLs into unique short codes and decodes them back to the original URLs, ensuring fast and efficient processing.

IV. Prerequisites 
To run this project, the following tools and software are required:
1)  Python (recommended version: 3.10+): Required to run the Flask server and handle web-based functionalities.
2)  Flask: A lightweight Python framework used for building the server and handling HTTP requests.
3)  C Compiler (e.g., GCC or Clang): Needed to compile the C application for URL encoding and decoding.
4)  Web Browser (e.g., Chrome, Firefox): Necessary for interacting with the web interface and testing the shortened URLs.

V. Installation To set up and run the project locally, follow these steps:
1)  Clone the repository Clone the project repository to your local machine using the following command: git clone https://github.com/TahaNour/C-project.git.  This will create a local copy of the project on your machine.
2)  Navigate to the project directory Change into the project directory: cd URL_Shortener This ensures you're working in the correct folder.
3)  Install Flask dependencies Install Flask and its dependencies by running: pip install flask
4)  Run the Flask server Once Flask is installed, start the server by running: python app.py
This will launch the Flask application, making the web interface accessible at http://127.0.0.1:5000.

VI. Usage To use the application:
1)  Adding a URL (Shortening a URL) Open the web interface in your browser. Paste the long URL you wish to shorten into the provided input field, and click the "Shorten" button. The application will generate a short code and display it as a clickable link.
2)  Decoding a Shortened URL To decode a short URL and retrieve the original long URL, enter the short code in the designated input field. The application will look up the original URL and display it for redirection.

VII. File Structure The project is organized as follows: /:
1)  app.py: Python script containing the Flask application, routes, and server logic.
2)  URL_Shortener.exe: Executable file for URL shortening functionality, generated from the C source code.
3)  main.c: C source code for encoding and decoding URLs.
4)  sqlite3.h: Header file for the SQLite database used to map short and long URLs.
5)  /templates/:
        -  index.html: HTML template for the main user interface, where users can shorten or decode URLs.
6)  /static/css/:
        -  style.css: CSS file for styling the web interface.

VIII. Author(s) 
This project was developed by a group of first-year telecommunications students at SUP'COM. It was created as part of a C programming course during the second period of the first semester. The group consisted of Montassar Ezzine, Taha Nour Chabchoub, Tarek Azzabou, Hayder Jamli, Hassen Mahmoud, and Oussema Harrabi.

IX. License 
This project is open-source and available for personal use, modification, and distribution. Feel free to explore, contribute, or adapt the project as needed. Proper attribution is appreciated, and users should follow any guidelines provided.
