#include "node.h"
#include <cassert>

/*
Input/Output format for this program.

A tree of questions and answers is represented by multiple lines of
text. There will always be at least one line of text.

Each line represents one node in the tree. Each begins with either a
'Q' or an 'A', indicating whether the node is a Question node or an
Answer node, followed by one or more blank spaces, followed by the
text of the question or answer. The text of a question or answer
begins with the first non-blank character after the Q or A and
continues until the end of the line.

Each 'Q' line is followed immediately by two blocks of 'Q' and 'A'
lines. The first block describes the collection of questions and
answers relevant following a "yes" answer to the first question. The
second block describes the collection of questions and answers
relevant to a "no" answer to the opening question.

For example,

Q Does it live in the water?
Q   Does it have webbed feet?
A     Duck
A     Fish
A   Cat


Describes a tree in which the first question to be asked is "Does it
live in the water?". If the person playing the game answers "yes",
then the block of lines

Q   Does it have webbed feet?
A     Duck
A     Fish

is relevant (i.e., the program will next ask about webbed feet). If
the person answers "no". then the block of lines

A   Cat

is relevant (i.e., the program will next ask "Is it a cat?".

The "indentation" shown in the sample above is purely for human
readability.  It is not required in your output, though your input
routine should tolerate it if it is present.

 */



using namespace std;

// write the tree whose root is given.
// Note: the form written out by this function should be something
//   that read(...) will accept, recreating the original tree.
void node::write (std::ostream& out, const node* root)
{
  // ensure root isn't null
  if(root == nullptr)
    return;

  // determine if node is question or answer
  if(root->ifNo == nullptr && root->ifYes == nullptr)
    out << "A ";
  else
    out << "Q ";

  // write details to stream
  out << root->detailText << endl;

  // call left and right nodes
  write(out, root->ifNo);
  write(out, root->ifYes);
}


// read a tree from in storing the tree root in t
void node::read (istream& in, node*& t)
{
  // exit if end of file reached
  if (in.eof()) {
    t = NULL;
    return;
  }

  // import a line of text
  string text = "";
  getline(in, text);

  // get the first letter of the incoming string
  char type = text[0];

  // trim the leading whitespace after the first letter and save as
  // the nodes detailText
  text = text.substr(1);
  text = text.substr(text.find_first_not_of(' '));

  t = NULL;
}
