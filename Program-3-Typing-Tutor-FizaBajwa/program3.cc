 /**------------------------------------------
    Program 3: Typing Tutor
    Course: CS 141, Spring 2023
    System: Linux_x86_64 and G++
    Author: Fiza Bajwa
 ---------------------------------------------**/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>
#include <iomanip>
using namespace std;

const int NMISP = 5; //the number of words in the full dictionary
const int RNG_RANGE = 100; // the number of word pairs in the misspelled dataset.

void
display_header(const int ndict, const int nmiss)
{
   /* Parameters:
        int ndict -> the number of words in the full dictionary
        int nmiss -> the number of word pairs in the misspelled
                     dataset.
    */
  cout <<  "*** Typing Tutor\n"
  << "There are " << ndict << " words in the dictionary.\n"
  <<"There are " << nmiss << " commonly misspelled words." << endl;
}

void
display_menu_options() // This function prints out all the menu options
{

    cout << endl << "*** Select a menu option:" << endl
         << "1. Spell commonly misspelled words" << endl
         << "2. Type random words from the full dictionary" << endl
         << "3. Display some words from one of the lists" << endl
         << "4. Use binary search to lookup a word in the dictionary" << endl
         << "5. Exit the program." << endl
         << "Your choice: ";
}

vector<int> 
randn(const int n, const int max) //randn had n random numbers from 0-max value
{
  vector<int> result;

  for (int i =0; i < n; i++) 
    result.push_back(rand() % (max+1));

  return result; // returns a vector that contains n random numbers between [0, max]
}

ifstream
open(const string& src_file)
{
    ifstream src{src_file};
    if (!src.is_open()) {
        cout << "Could not find file " << src_file << "." << endl;
        exit(1);
    }
    return src;
}

void 
extract_dict(vector<string>& dst, const string& src_file)
{ 
  ifstream src = open(src_file); // reads data from file
  for (string line;
    getline(src, line); 
      dst.push_back(line)); // stores each line in vector dst( an empty)
  
  /*  Parameters:
        dst -> an empty vector (of strings), passed by reference,
               that  you  will  store  every line  of the file in
               (each line is one element in the file).

        src_file -> a string, passed by reference, that you are not
                    allowed to change  (const),  that is simply the
                    name of the file.
    */
}

void
extract_misspelled(vector<string>& misspelled, vector<string>& correct,
                    const string& src_file)
{
  ifstream src = open(src_file);
  string wordi, word;
  
  for (string line; getline(src, line);) {
    istringstream line_stream{line}; // extracts word pairs and stores in their vectors
      line_stream >>wordi>> word;
    
      misspelled.push_back(wordi);
    
      correct.push_back(word);
    }
  }
/*
Parameters:
  misspelled -> an  empty vector (strings),  passed by reference,
                that you will store the misspelled words in.

  correct -> an empty vector (strings), passed by reference, that
             you will store the correct version of the words in.

  src_file -> a string, passed by reference, that you are not
              allowed to change  (const),  that is simply the
              name of the file.
    */

void
display_elems(const vector<string>& src, const vector<int>& positions)
{
  string line, mword;
  const int size = positions.size();
  int place;
  
  for (int i=0; i < size - 1; i++) {
    place= positions[i];
    cout << src[place] << ' '; // prints out the elementsin the vector src only at those indiceswith a space between each of the elements.
    }
  
  place= positions[size-1];
  cout << src[place] << endl;
  }

/* 
Parameters:
    src -> a vector (strings), passed by reference, that is not
           allowed to be modified (const), which holds the data
           that is to be printed

    positions -> a vector (int), passed by reference, that is not
                 allowed to be modified (const),  which holds the
                 indices for elements in src to print.
*/

void // Copies the elements at the indices, in the positions vector, from the correct vector, into the vector dst.
extract_spelling_answers(vector<string>& dst, const vector<string>& correct,
                            const vector<int> positions)
{
  for (int pos: positions)
  dst.push_back(correct[pos]);
  }

/* 
Parameters:
    dst -> an empty vector (of strings), passed by reference, that
           you will copy the specific elements from correct into.

    correct -> a vector (strings), passed by reference, that is not
               allowed to be modified (const), which holds the data
               that is to be copied over to dst

    positions -> a vector (int), passed by reference, that is not
                 allowed to be modified (const),  which holds the
                 indices of the elements in correct to copy over
*/


void
extract_spelling_mistakes(vector<string>& dst, const string& to_grade,
                const vector<string>& correct)
{
  string line;
  
  istringstream user_stream{to_grade}; // Populate the vector dst with all the spelling errors in the user's answer (to_grade).
  
  for (string answer: correct) { 
    user_stream >> line;
    
    if (line != answer) {
      string error{line + " -> " + answer}; 
      dst.push_back(error);
      }
    }
  } 
/* 
Parameters:
    dst -> an empty vector (of strings), passed by reference, that you
    will fill with strings that represent spelling errors  (mispelling
    -> correct spelling) (see Hints)

    to_grade -> a string, passed  by reference,  that is not allowed to
                be modified (const) that holds the user's typed answer.

    correct -> a vector (strings), passed by reference, that is not
               allowed to be modified (const), which holds the correct
               answers. (one vector element -> one word)
*/

void
report_misspell_mistakes(const vector<string>& mistakes,
                            const int num_words) // report_mispell_mistakes prints out the part with reporting the mistakes
{
  int numMistakes = mistakes.size();
  
  int numCorrect = num_words - numMistakes;
  
  int correctScore = numCorrect *3;
  
  int mistakesScore = numMistakes * 6;
  
  int finalScore = correctScore - mistakesScore;

  if (numMistakes >0){
     cout << "Misspelled words:" << endl;
    
    for(int i=0; i< mistakes.size(); i++){
      cout << "    " << mistakes.at(i) << endl;
      }
    }
    
  else{
         cout << "No misspelled words!" << endl;
    }

     cout << correctScore << " points: " << numCorrect << " spelled correctly x " << "3 points for each." << endl
   << mistakesScore << " point penalty: " << numMistakes << " spelled incorrectly x -6 points for each." << endl
   << "Score: " << finalScore << endl;
  }
/*
Parameters:
  mistakes -> a vector (strings), passed by reference, that is
              not allowed  to be modified  (const),  and holds
              the messages about  misspellings that we want to
              report to the user.

  num_words -> an integer, that is not allowed to be modified
               (const),  which is  the total number  of words
               being tested
*/


void 
evaluate_user_misspells(const vector<string>& src, const vector<int>& positions)
{ // Read the users input for the typing test, and report back their performance
  string user_input;
  getline(cin, user_input); 
  
  vector<string> mistakes;
  vector<string> answers;
  
  extract_spelling_answers(answers, src, positions);
  extract_spelling_mistakes(mistakes, user_input, answers);
  
  int num_words = answers.size(); 
  
  report_misspell_mistakes(mistakes, num_words);
    }
/*
Parameters:
  src -> a vector (strings), passed by reference, that is not
         allowed to be modified (const), which holds the data
         that the user is being tested on.

  positions -> a vector (int), passed by reference, that is not
               allowed to be modified (const),  which holds the
               indices of the elements in correct to copy over
*/
  

void
misspelled(const vector<string>& mspelled, const vector<string>& correct)
{
  cout << endl << "*** Using commonly misspelled words." << endl; // starting message
  
  vector<int> positions = randn(5, mspelled.size()-1); // display 5 random words from dictionary
  
  display_elems(mspelled, positions);
  
  cout << "Type the words above with the correct spelling:" << endl;
  
  evaluate_user_misspells(correct, positions); // evaluates input
  }

/* 

Parameters:
    mspelled -> a vector (string) where each element is one
                mispelled word from the data set

    correct -> a vector (string) where each element is a
               correctly spelled word from the data set

Hints:
    Do not try to write this function first.  The role of this function
    is to simply drive the whole procedure for menu option 1, it should
    be calling helper functions to handle the details of the sub tasks.
    Use randn, display_elems, and evaluate_user_misspells.
*/
  

void
full_dict(const vector<string>& dict)
{
  cout << endl << "*** Using full dictionary." << endl; // Prints out starting message for menu option 2,
  
  vector<int> positions = randn(5, dict.size()-1);  // displays five random words from the full dictionary
  
  display_elems(dict, positions);
  
  cout << "Correctly type the words above:" << endl;
  
  evaluate_user_misspells(dict, positions); // evaluates user input
  }
/* 
Parameters:
    dict -> a vector (string), passed by reference, where
            each element is one word from the full
            dictionary.
*/


void
display_words_prompt()
{
  // This displays the data set choices for menu option 3
  cout << endl << "*** Displaying word list entries." << endl
       << "Which words do you want to display?" << endl
       << "A. Dictionary of all words" << endl
       << "B. Commonly misspelled words (wrongly spelled)" << endl
       << "C. Commonly misspelled words (correctly spelled)" << endl
       << "Your choice: ";
}

void
print_range(const vector<string>& data)
{
  int lower1;
  int upper2;
  int data_size = data.size() - 1;
  
  cout << "*** Enter the start and end indices between 0 and " << data_size << ": ";
  cin >> lower1 >> upper2;
  
  if ((upper2 <= lower1) || (lower1 < 0) || (upper2 > data_size)) {
    cout << "The end index must come after the start, and the indices must be in range." << endl;
    
  } else {
    for (int i = lower1; i <= upper2; i++) {
      cout << i << ". " << data[i] << endl;
    }
  }
  
}

void
display_in_range(const vector<string>& dict, const vector<string>& mspelled,
                const vector<string>& correct)
{
  display_words_prompt(); // displays initia message for menu option 3
  char choice;
  cin >> choice; // users choice of dataset
  
  // displays data in range
  if (toupper(choice) == 'A') { 
    print_range(dict);
    
  } else if (toupper(choice) == 'B') {
    print_range(mspelled);
    
  } else {
    print_range(correct);
  }
}
/* 
Parameters:
    dict -> a vector (string),  passed by reference, that cannot be
            modified (const), which holds the all the data from the
            full dictionary

    mspelled -> a vector (string), passed by reference, that cannot
                be modified (const),  which holds the all the miss-
                pelled words

    correct -> a vector (string), passed by reference, that cannot
               be modified (const),  which holds the all the words
               with correct spelling
*/

void
bsearch(const vector<string>& data)
{
  string word;
  cout << "*** Enter word to search: ";
  cin >> word; // reads word to search for
  
  int one, two, three;
  two = 0;
  three = data.size()-1;
  
  int count=1;
  
  bool works, point;
  works = true;
  point = false;
  
  // run the Binary Search Algorithm to search for the word
  for (int i=0; i<word.length(); i++){
    if (!isalpha(word.at(i))) {
      works = false;
      }
    }
  
    if(!works){
      cout << word << " not found";
      return;
      }
  
    while(two <= three){
      one = (three + two + 1) /2;
      if (count <10){
        cout << " ";
        }
      
      if (data[one] == word){
        point = true;
        cout << "   " << count << ". Comparing to: " << data.at(one) << endl;
        cout << word << " was found."; // prints out word that is being compared
        return;
        
        } else if (data[one] < word){
          two = one+1;
        
        } else if (data[one] > word){
          three = one-1;
        }
      
      cout << "   " << count << ". Comparing to: " << data.at(one) << endl;
      count += 1;
      }
  
    if (!point){
      cout << word << " was NOT found.";
      }
    }
/* 
Parameters:
    data -> a vector (string),  passed by reference, that cannot be
            modified (const), which holds the all the data from the
            full dictionary
*/

void
extract_all_data(vector<string>& dict, vector<string>& mspelled,
                    vector<string>& correct)
{
    extract_dict(dict, "dictionary.txt");
    extract_misspelled(mspelled, correct, "misspelled.txt");
}

int
main()
{
  srand(1);
  vector<string> dict, mspelled, correct;
  extract_all_data(dict, mspelled, correct);
  display_header(dict.size(), correct.size());
  unsigned int choice;
  do {
      display_menu_options();
      cin >> choice;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      switch (choice) {
      case 1:
          misspelled(mspelled, correct);
          break;
      case 2:
          full_dict(dict);
          break;
      case 3:
          display_in_range(dict, mspelled, correct);
          break;
      case 4:
          bsearch(dict);
          break;
      case 5:
          cout << "Exiting." << endl;
          break;
      default:
          cout << "No menu option " << choice << ". "
               << "Please try again." << endl;
      }
  } while ((choice != 5) && !cin.eof());

  return 0;
}