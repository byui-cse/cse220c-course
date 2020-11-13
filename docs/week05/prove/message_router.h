// message_router.h
//
// Stores a collection of office nodes and provides facilities
// to send, read, delete messages between office locations
//

#ifndef message_router_h
#define message_router_h

#include <string>
#include "message_store.h"

using namespace std;

class MessageRouter
{
public:
  // Adds a new office node to the collection of offices
  void add_office(const string& office_name);

  // Adds an office node by importing a file of stored messages
  void open_office(const string& office_name, const string& filename);

  // Removes an office node from the collection
  void remove_office(const string& office_name);

  // Show all office name in the collection
  void display_office_names() const;

  // Save the message store of an office to filename
  void save_office(const string& office, const string& filename) const;

  // Returns true if the given location exists in the collection
  bool location_is_valid(const string& location) const;

  // Display all messages for recipient at the location
  void display_messages(const string& location, const string& recipient);

  // Read the message identified by msg_id at office for recipient
  void read_message(const string& location, const string& recipient, int msg_id);

  // Send a message to reciever at location
  void send_message(const string& location, const string& author,
    const string& receiver, const string& subject, const string& content);

  // Delete a message to recipient at location
  void delete_message(const string& location, const string& recipient, int msg_id);

private:
  // Stores an instance of an office
  class OfficeNode  {
  public:
    shared_ptr<MessageStore> store;   // the messages for this office
    string name;                      // the office name
    shared_ptr<OfficeNode> next_ptr;  // points to the next node
    OfficeNode(const string& a_name); // constructor for a new office node
  };
  shared_ptr<OfficeNode> root_ptr;    // points to the first node

};

# endif // message_router_h

