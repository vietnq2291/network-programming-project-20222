Welcome to the messaging app! This app allows you to send messages to other users who are connected to the same server. To get started with the app, please follow the instructions below.

## Building the app
1. Clone the repository to your local machine.
2. Navigate to the `server` and `client` directories in separate terminal windows.
3. Create a build directory inside each directory and navigate to it.
4. Run `cmake ..` to generate the build files.
5. Run `cmake --build .` to compile the source files and create the final executable.

## Setting up the database
1. Log in to MySQL using the command `mysql -u <username> -p` 
(default user is `root` and password is `123456`).
2. Run the SQL file to create the necessary database and tables `source <path to messaging_db.sql>` .

## Running the server
1. In the `server` directory, run the command `./messaging-server`.
2. The server should now be running and listening for incoming connections.

## Running the client
1. In the `client` directory, run the command `./messaging-client`.
2. Follow the prompts to log in to the server and start sending messages to other connected users.
