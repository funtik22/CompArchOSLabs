
# Ping-Pong Client-Server Application

## Table of Contents

- [Description](#Description)  
- [Functionality](#Functionality)  
- [Requirements](#Requirements)  
- [Installation](#Installation)  
- [Usage](#usage)  

---

## Description

The project implements interprocess communication via a TCP socket in the form of two files: a client and a server. The client sends "ping" messages to the server, and the server responds with "pong" messages. Both the client and server are written in C++.

## Functionality

- **Server**:
  - Creates a socket and binds it to the specified port.
  - Listens for incoming connections from clients.
  - Receives messages from clients and sends responses.

- **Client**:
  - Creates a socket and connects to the server.
  - Sends a "ping" message to the server every second.
  - Receives a "pong" response from the server.

## Requirements

- C++ compiler (e.g., g++)
- POSIX sockets (supported on most Unix-like systems)

## Installation

1. **Clone the repository** (if using Git):
   ```bash
   git clone <repository_URL>
   cd <repository_folder>

2. **Create files**:
   Create two files named client.cpp and server.cpp, and insert the corresponding code from the project.
   Compile the code:
   In the terminal, run the following commands:
      ```bash
      g++ -o server server.cpp
      g++ -o client client.cpp
      ```

## Usage
1. Start the server first:
   In one terminal, run:
      ```bash
      ./server
      ```
    You should see a message indicating that the server is ready to listen.

2. Start the client:
   In another terminal, run:
     ```bash
      ./client
     ```
    The client will start sending "ping" messages to the server, and the server will respond with "pong".

3. Observe the message exchange in the console logs for both the client and the server:

  ## Client Logs
  
  ```bash
    Create client socket #3
    Connect to server port: 3457
    Client send: ping
    Client get: pong
    =========================================
  ```
  ## Server Logs
  ```bash
    Create server socket #3
    Bind port: 3457 to socket
    Server is ready to listen
    Connection accepted
    Server get a message: ping
    Server send a message: pong
  ```
