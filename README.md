# My Teams

My Teams is a chat application that allows users to communicate with each other in real-time. This project consists of two parts: a server and a command-line interface (CLI) client.

## Installation

To install My Teams, follow these steps:

1. Clone the repository: `git clone git@github.com:NielsOuvrard/my_teams.git`
2. Navigate to the project directory: `cd my_teams`
3. Be sure to have uuid-dev installed: `sudo apt-get install uuid-dev`
4. Be sure to have sqlite3 installed: `sudo apt-get install libsqlite3-dev`
5. Install the server and CLI client: `make`

## Usage

To start the server, run the following command:

```bash
./my_teams_server 3000
```

This will start the server on port 3000.

To start the CLI client, run the following command:

```bash
./myteams_cli 0.0.0.0 3000
```

This will connect the CLI client to the server running on `localhost:3000`.


Once connected, you can use the following commands:

- `/help`: show help
- `/login [“user_name”]`: set the user_name used by client
- `/logout`: disconnect the client from the server
- `/users`: get the list of all users that exist on the domain
- `/user [“user_uuid”]`: get details about the requested user
- `/send [“user_uuid”] [“message_body”]`: send a message to specific user
- `/messages [“user_uuid”]`: list all messages exchanged with the specified user
- `/subscribe [“team_uuid”]`: subscribe to the events of a team and its sub directories (enable reception of all events from a team)
- `/subscribed ?[“team_uuid”]`: list all subscribed teams or list all users subscribed to a team
- `/unsubscribe [“team_uuid”]`: unsubscribe from a team
- `/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”]`: Sets the command context to a team/channel/thread
- `/create`: based on the context, create the sub resource (see below)
- `/list`: based on the context, list all the sub resources (see below)
- `/info`: based on the context, display details of the current resource (see below)

Note: Replace the text inside the square brackets with the appropriate values.

## Credits

- [Niels Ouvrard](https://github.com/NielsOuvrard)
- [Gabriel Morais](https://github.com/gabrielmorais4)