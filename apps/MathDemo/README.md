# Demo client and server

This is a demo application using the TCP Client and Server, protobuf protocol and application/event model provided by the libs.

## Usage

In one console, run the server.
In any number of other consoles, run clients.
No command line args required.


## Client

The client (**MathClient.exe**):
- Connects to the server (currently just defaults to 127.0.0.1:54000).
- If it can't connect, or if the server sends it data that it can't parse according to the protocol, it will shut down.
- Randomly generates a basic arithmetic question every 1 second and asks the server.
- Logs both the question and answer when it gets a response.
- Exits if it receives a signal CTRL+C, CTRL+Break *etc.*

## Server

The server (**MathServer.exe**):
- Starts listening for clients - it can handle multiple, dropping them on disconnect.
- If it receives data that it can't parse according to the protocol, it will just drop the client.
- Otherwise, it will see the maths arithmetic question and send back a response.
- Exits if it receives a signal CTRL+C, CTRL+Break *etc.*