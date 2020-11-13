// week05.cpp
// The main driver for the messaging application using 
// the MessageRouter class
//

#include "message_router.h"
#include <iostream>  // cout, endl
#include <string>

void display_menu();
void user_loop(const string& username, const string& location, MessageRouter& r);
void user_login(MessageRouter& r);
int prompt_for_id();

// file used for persistent storage of messages
const string FILENAME = "sample_messages.txt";

int main()
{
  // Create a new message router
  MessageRouter r;

  // Open three offices
  r.open_office("a", "a_messages.txt");
  r.open_office("b", "b_messages.txt");
  r.open_office("c", "c_messages.txt");

  // Add a new office that doesn't have previously stored messages
  r.add_office("d");

  // Display all offices
  cout << "Welcome. You may login to one of the following offices: " << endl;
  r.display_office_names();

  // Main loop
  user_login(r);

  // Save the messages from each office before exiting
  r.save_office("a", "a_messages.txt");
  r.save_office("b", "b_messages.txt");
  r.save_office("c", "c_messages.txt");
  r.save_office("d", "d_messages.txt");
}

void display_menu()
{
  cout << "Choose an option: " << endl;
  cout << "\td - Display all messages" << endl;
  cout << "\tr - Read a message" << endl;
  cout << "\tx - Delete a message" << endl;
  cout << "\ts - Send a message" << endl;
  cout << "\tq - Exit user" << endl;
}

// Interaction with a given user
void user_loop(const string& username, const string& location, MessageRouter& r)
{
  char response;           // collect user reponse to menu
  int id;                  // store a message id
  string receiver;         // message recipient
  string subject;          // message subject
  string message_content;  // message contents
  string destination;      // location of recipient

  cout << "\nWelcome, " << username << endl;

  while (true) {

    display_menu();
    cout << "\n" << username << " (" << location << ")> ";
    cin >> response; // get a single character from the input stream
    cin.ignore();  // ignore the next character in the input stream, '\n'

    cout << endl;
    switch (response) {
    case 'd': // display all messages for the user
      r.display_messages(location, username);
      break;
    case 'r': // read a single message
      id = prompt_for_id();
      if (id < 0) { break; } // id was not valid
      cout << endl;
      r.read_message(location, username, id);
      break;
    case 'x': // delete a single message
      id = prompt_for_id();
      if (id < 0) { break; } // id was not valid
      r.delete_message(location, username, id);
      break;
    case 's': // send a message
      cout << "Who are you sending to? ";
      getline(cin, receiver);
      cout << "What is their location? ";
      getline(cin, destination);
      cout << "What is the subject? ";
      getline(cin, subject);
      cout << "What is the message? ";
      getline(cin, message_content);
      r.send_message(destination, username, receiver, subject, message_content);
      break;
    case 'q': // exit menu for user
      cout << "Goodbye " << username << "." << endl;
      return;
    default:
      cout << "Invalid option: " << response << endl;
      break;
    }
    cout << endl;
  }
}

// Allows user to login to system
void user_login(MessageRouter& r)
{

  while (true) {
    string username;
    string location; // office name

    cout << "\nEnter user name ('quit' to exit): ";
    getline(cin, username);

    if (username == "quit") {
      cout << "Goodbye." << endl << endl;
      return;
    }

    cout << "\nEnter location: ";
    getline(cin, location);

    if (!r.location_is_valid(location)) {
      cout << "That location does not exist" << endl;
    }
    else {
      user_loop(username, location, r);
    }

  }
}

// Helper function to get a message id
int prompt_for_id()
{
  int id;
  cout << "Enter message id: ";
  cin >> id;
  if (!cin) {
    cout << "Invalid ID" << endl;
    cin.clear();  // unset fail bit
    // skip any bad characters until the end of the line
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return -1; // signals error
  }
  return id;
}
