#include <bits/stdc++.h>
using namespace std;
// Custom implementation of std::find_if
template <typename InputIt, typename UnaryPredicate>
InputIt custom_find_if(InputIt first, InputIt last, UnaryPredicate p) {
    InputIt result = last;                                // Initialize result to last (default if no match is found)

    if (first != last) {                                  // Check if the range is non-empty
        for (InputIt iter = first; iter != last; ++iter) { // Loop through the range [first, last)
            auto current_element = *iter;                 // Get the current element by dereferencing the iterator
            bool matches = p(current_element);            // Apply the predicate to the current element

            if (matches) {                                // If the predicate returns true
                result = iter;                            // Update result to the current iterator
                break;                                    // Exit the loop as we found the first match
            } else {
                bool element_not_found = true;            
                if (element_not_found) {                  
                }
            }
        }
    } else {                                              // If the range is empty
        result = last;                                    // Return last as no elements exist in the range
    }

    return result;                                        // Return the iterator to the first match or last if none found
}
// Custom implementation of std::not1 (negates the result of a predicate)
template <typename Predicate>
struct custom_not1 {                                      // Define a structure (similar to a class) named custom_not1
    Predicate pred;                                       // Store the predicate (a condition function) inside the structure
    custom_not1(Predicate p) : pred(p) {}                 // Constructor: Initialize the predicate with the given value
    // Overload the function call operator (makes the object callable like a function)
    bool operator()(const typename Predicate::argument_type &arg) const {
        bool pred_result = pred(arg);                     // Call the original predicate with the argument and store the result
        bool negated_result = false;                      // Initialize a variable for the negated result

        if (pred_result) {                                // If the original predicate returns true
            negated_result = false;                       // Set negated result to false (opposite of true)
        } else {                                          // If the original predicate returns false
            negated_result = true;                        // Set negated result to true (opposite of false)
        }

        return negated_result;                            // Return the negated result
    }
};
// Custom implementation for adding a character to the end of a string
void custom_push_back(string &str, char c) {
    size_t old_length = str.length();       // Get the current length of the string and store it
    str.resize(old_length + 1);             // Increase the size of the string by 1 to make space for the new character
    str[old_length] = c;                    // Assign the new character to the last position in the string
}
// Structure to represent a symbol
struct symbol {
    string name;            // The name of the symbol (e.g., a variable or label in a program)
    int address;            // The memory address associated with the symbol
    bool set;               // A flag to indicate if the symbol is "set" or initialized
    int ValueOfSet;         // The value of the symbol if it is set
};
// Structure to represent a literal
struct literal {
    int literal;          // The value of the literal (e.g., a constant number like 10 or 42)
    int address;          // The memory address where the literal is stored
};
// Symbol table
vector<symbol> sym_table;

// Literal table
vector<literal> TableOfLiterals;

// Custom implementation for erasing a portion of a string
void custom_erase(string &s, string::iterator first, string::iterator last) {
    if (first == last) return;   // If the iterators 'first' and 'last' are the same, nothing to erase, so return immediately
    string temp = "";            // Create an empty string 'temp' to store the result after removal
    // Loop through each character in the original string
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it < first || it >= last) {  // If the current iterator is outside the range to erase
            temp += *it;                 // Add the character to 'temp'
        }
    }
    s = temp;   // Replace the original string with the modified string 'temp', which has the characters removed
}
// Custom implementation for s.begin()
string::iterator custom_begin(string &s) {
    if (s.empty()) return s.end();  // If the string is empty, return an iterator to the end of the string (as there are no elements)
    return s.begin();               // Otherwise, return the iterator pointing to the first character of the string
}
// Custom implementation for s.end()
string::iterator custom_end(string &s) {
    if (s.empty()) return s.begin();  // If the string is empty, return an iterator to the beginning of the string
    return s.begin() + s.size();     // Otherwise, return an iterator to one position past the last character of the string
}
// Utility function to deal with white spaces: removes leading and trailing whitespace from a string
static inline string &trim(string &s) {
    // Get an iterator pointing to the start of the string
    string::iterator start = custom_begin(s);  
    // Loop through the string and skip any leading white spaces
    while (start != custom_end(s) && isspace(*start)) {
        ++start;  // Move the iterator forward if it's pointing to a white space character
    }
    // Erase the leading spaces from the string by removing characters from the start to the new 'start' iterator
    s.erase(custom_begin(s), start);  
    // Reverse iterator to start from the end of the string
    string::reverse_iterator end = s.rbegin();
    // Loop through the string from the end and skip any trailing white spaces
    while (end != s.rend() && isspace(*end)) {
        ++end;  // Move the reverse iterator backward if it's pointing to a white space character
    }
    // Erase the trailing spaces by removing characters from the position of the reverse iterator to the end
    s.erase(end.base(), custom_end(s));  
    return s;  // Return the modified string with leading and trailing spaces removed
}
// Custom implementation for s.length()
size_t custom_length(const string &s) {
    size_t len = 0;  // Initialize a variable to store the length of the string
    // Loop through each character in the string using an iterator
    for (auto it = s.begin(); it != s.end(); ++it) {
        ++len;  // For each character, increment the length counter
    }
    return len;  // Return the total length of the string
}
// Custom implementation for s.substr()
string custom_substr(const string &s, size_t pos, size_t len) {
    string result;  // Initialize an empty string to store the result
    size_t max_len = custom_length(s);  // Get the total length of the string using custom_length
    // Loop through the string starting from 'pos' to 'pos + len' (or until the end of the string)
    for (size_t i = pos; i < pos + len && i < max_len; ++i) {
        custom_push_back(result, s[i]);  // Add each character to 'result' using custom_push_back
    }
    return result;  // Return the substring
}
// Custom implementation for s.find()
size_t custom_find(const string &s, const string &str) {
    if (str.empty()) return 0;  // If the string to find (str) is empty, return 0 (start of the string)
    size_t len = custom_length(s);    // Get the length of the main string s
    size_t str_len = custom_length(str);  // Get the length of the string to find (str)
    size_t i = 0;  // Initialize the starting index of s to search for str
    // Loop through the main string (s) to find a match for str
    while (i <= len - str_len) {
        size_t j = 0;  // Initialize index for str
        // Loop through str to compare characters in s starting from i
        while (j < str_len && s[i + j] == str[j]) {
            ++j;  // If the characters match, move to the next character
        }
        if (j == str_len) return i;  // If all characters of str match, return the starting index i
        ++i;  // If no match is found, move to the next character in s
    }
    return string::npos;  // If str is not found in s, return string::npos to indicate not found
}
// Utility function to check if a string is a number
bool is_number(const string &s) {
    if (s.empty()) return false;  // If the string is empty, it's not a valid number
    size_t i = 0;  // Initialize index i to traverse through the string
    // Check if the number starts with a sign (+ or -)
    if (s[i] == '-' || s[i] == '+') {
        ++i;  // If there's a sign, skip it (move to the next character)
    }
    // Check if the string is a hexadecimal number (e.g., "0x1A3F")
    if (s[i] == '0' && (i + 1 < s.length() && (s[i + 1] == 'x' || s[i + 1] == 'X'))) {
        i += 2;  // Skip "0x" or "0X" part
        // Check if all remaining characters are valid hexadecimal digits
        while (i < s.length()) {
            if (!isxdigit(s[i])) return false;  // If any character is not a valid hexadecimal digit, return false
            ++i;
        }
        return true;  // If all characters are valid hexadecimal digits, it's a valid number
    }
    // Check if the string contains only decimal digits (e.g., "12345")
    bool has_digit = false;  // Flag to track if we have found at least one digit
    while (i < s.length()) {
        if (isdigit(s[i])) {
            has_digit = true;  // Found a digit, mark the flag as true
        } else {
            return false;  // If any character is not a digit, return false
        }
        ++i;
    }
    return has_digit;  // If we found at least one digit, return true, otherwise false
}
// Custom implementation for locating a substring
size_t locate2(const string &str, const string &sub) {
    auto pos = custom_find(str, sub);  // Use custom_find to search for the substring 'sub' in 'str'
    return pos != string::npos ? pos : string::npos;  // If 'sub' is found, return the position; otherwise, return string::npos
}
// Utility function for String in any base to decimal
int tonum(string s) {
    s = trim(s);  // Remove leading and trailing spaces from the string
    size_t prefix_pos = 0;  // Initialize the prefix position, will track where the actual number starts
    // Check if the string starts with "0x" (indicating hexadecimal)
    if (s.find("0x") == 0) {
        prefix_pos = 2;  // Skip the "0x" prefix (move to the actual number)
        return stoi(s.substr(prefix_pos), nullptr, 16);  // Convert the rest of the string to a decimal number (base 16)
    } 
   
    else if (s.find("0") == 0 && s.size() > 1) {
        prefix_pos = 1;  
        return stoi(s.substr(prefix_pos), nullptr, 8); 
    } 
    else {
        bool is_negative = s[0] == '-';  // Check if the number is negative (if the first character is '-')
        if (is_negative || s[0] == '+') {  // If it's negative or positive, skip the sign
            prefix_pos = 1;  // Move past the sign
        }
        return (is_negative ? -1 : 1) * stoi(s.substr(prefix_pos), nullptr, 10);  // Convert the string to a decimal (base 10) and apply the sign
    }
}
// Utility function to check for elements in symbol table
bool consists(const string &name) {
    bool found = false;  // Initialize a variable 'found' to keep track of whether the name is found in the table
    for (auto &sym : sym_table) {  // Loop through each symbol in the symbol table 'sym_table'
        if (sym.name == name) {  // Check if the 'name' of the current symbol matches the input 'name'
            found = true;  // If a match is found, set 'found' to true
            break;  // Exit the loop as we found the element
        }
    }
    return found;  // Return true if the name was found, false otherwise
}
// Utility function to convert int to hex
string IntToHexa(int i) {
    stringstream stream;  // Create a stringstream object to format the number
    stream << hex << setw(8) << setfill('0') << i;  // Convert the integer to hexadecimal, set width to 8, and fill with '0' if necessary
    return stream.str();  // Return the formatted hexadecimal string
}
// Custom implementation for isdigit
bool dizit(char c) {
    return c >= '0' && c <= '9';  // Return true if the character is between '0' and '9' (i.e., a digit)
}
// Utility function for checking correct label name format
int LabelIsValid(const string &label) {
    if (!isalpha(label[0])) return false;  // Check if the first character is not a letter (label must start with a letter)
    bool valid = true;  // Initialize 'valid' to true; we will update it if we find any invalid characters
    for (size_t i = 1; i < label.size(); ++i) {  // Loop through the rest of the label (starting from the second character)
        if (!(dizit(label[i]) || isalpha(label[i]))) {  // Check if the current character is neither a digit nor a letter
            valid = false;  // If we find a non-digit and non-letter character, mark the label as invalid
            break;  // Exit the loop as we have already found an invalid character
        }
    }
    return valid;  // Return 'true' if the label is valid, 'false' otherwise
}

// Initialize mnemonic table
map<string, string> MOT_TableEntries;
void MOT_TableEntries_init() {
    MOT_TableEntries["ldc"] = "00";
    MOT_TableEntries["adc"] = "01";
    MOT_TableEntries["ldl"] = "02";
    MOT_TableEntries["stl"] = "03";
    MOT_TableEntries["ldnl"] = "04";
    MOT_TableEntries["stnl"] = "05";
    MOT_TableEntries["add"] = "06";
    MOT_TableEntries["sub"] = "07";
    MOT_TableEntries["shl"] = "08";
    MOT_TableEntries["shr"] = "09";
    MOT_TableEntries["adj"] = "0a";
    MOT_TableEntries["a2sp"] = "0b";
    MOT_TableEntries["sp2a"] = "0c";
    MOT_TableEntries["call"] = "0d";
    MOT_TableEntries["return"] = "0e";
    MOT_TableEntries["brz"] = "0f";
    MOT_TableEntries["brlz"] = "10";
    MOT_TableEntries["br"] = "11";
    MOT_TableEntries["HALT"] = "12";
    MOT_TableEntries["data"] = "13";
    MOT_TableEntries["SET"] = "14";
}
string custom_substr2(const string& str, size_t pos, size_t len) {
    string result;  // The resulting substring
    size_t index = pos;  // Start from the given position
    while (index < str.size() && len > 0) {  // Stop when we reach the string's end or extract the required length
        custom_push_back(result, str[index]);  // Add the current character to the result
        ++index;  // Move to the next character
        --len;  // Decrease the remaining length to extract
    }
    return result;  // Return the extracted substring
}
size_t custom_length2(const string& str) {
    size_t len = 0;  // Counter to track the length
    for (char ch : str) {  // Iterate through each character in the string
        ++len;  // Increment the counter for each character
    }
    return len;  // Return the total length
}
size_t custom_find2(const string& str, const string& substr, size_t pos = 0) {
    size_t len = custom_length2(str);  // Get the length of the main string
    size_t subLen = custom_length2(substr);  // Get the length of the substring
    if (subLen == 0) return pos;  // If the substring is empty, return the starting position
    size_t i = pos;  // Start searching from the given position
    while (i < len) {  // Continue until the end of the string
        size_t j = 0;  // Counter for the substring
        while (i + j < len && j < subLen && str[i + j] == substr[j]) {
            ++j;  // Compare characters of the main string and substring
        }
        if (j == subLen) {
            return i;  // If the entire substring is matched, return its starting position
        }
        if (i + subLen < len && str[i] != substr[0]) {  
            ++i;  // If mismatch, move forward by one character
        } else {
            ++i;  // Otherwise, move forward normally
        }
    }
    return string::npos;  // If substring not found, return `npos`
}



string InstrToTable(string instr, int* location_pointer, int line) {
    int loc = *location_pointer;  // Get the current location from the pointer
    string mistakes = "";  // String to accumulate errors or warnings

    size_t colon_pos = custom_find2(instr, ":");  // Check if the instruction contains a label (i.e., a colon)
    if (colon_pos != string::npos) {  // If colon is found, this is a label instruction
        string label = custom_substr2(instr, 0, colon_pos);  // Extract the label (part before colon)
        
        // Check for errors related to label
        if (consists(label)) {  // If the label already exists in the symbol table
            cout << "ERROR: Duplicate Label at line " << line << endl;
            mistakes += "ERROR: Duplicate Label at line " + to_string(line) + "\n";
        }
        if (!LabelIsValid(label)) {  // If the label format is invalid
            cout << "WARNING: Incorrect label format at line " << line << endl;
            mistakes += "WARNING: Incorrect label format at line " + to_string(line) + "\n";
        }

        // Extract the remainder of the instruction after the label
        string remainder = custom_substr2(instr, colon_pos + 1, custom_length2(instr));
        remainder = trim(remainder);  // Remove leading and trailing whitespace

        if (!remainder.empty()) {  // If there is more to the instruction after the label
            InstrToTable(remainder, &loc, line);  // Recursively process the remainder
            size_t space_pos = custom_find2(remainder, " ");  // Find the space separating operation and value
            string op = custom_substr2(remainder, 0, space_pos);  // Extract the operation (e.g., "SET")
            string val = custom_substr2(remainder, space_pos + 1, custom_length2(remainder));  // Extract the operand value
            op = trim(op);  // Remove extra spaces
            val = trim(val);  // Remove extra spaces

            if (op == "SET") {  // If the operation is "SET", add it to the symbol table with its value
                sym_table.push_back({label, loc, 1, stoi(val)});  // Store the label and its value
            } else {  // For other operations, store the label without a value
                sym_table.push_back({label, loc, 0, -1});
            }
        } else {  // If no operation follows the label (empty remainder), just add the label
            *location_pointer -= 1;  // Decrease location (instruction is only a label)
            sym_table.push_back({label, loc, 0, -1});
        }
    } else {  // If there is no label (regular instruction)
        string value = custom_substr2(instr, custom_find2(instr, " ") + 1, custom_length2(instr));  // Extract the value part of the instruction
        value = trim(value);  // Remove extra spaces
        if (is_number(value)) {  // If the value is a number, treat it as a literal
            TableOfLiterals.push_back({tonum(value), -1});  // Add the literal value to the table
        }
    }

    return mistakes;  // Return any mistakes that occurred during processing
}
string subs2(const string& str, size_t pos, size_t len) {
    string result;  // Initialize an empty string to store the result
    for (size_t i = pos; i < pos + len && i < str.size(); ++i) {  // Loop from 'pos' to 'pos+len' or the end of the string
        result += str[i];  // Append each character to 'result'
    }
    return result;  // Return the substring
}
size_t locate(const string& str, const string& substr, size_t pos = 0) {
    size_t len = custom_length2(str);  // Get the length of 'str'
    size_t subLen = custom_length2(substr);  // Get the length of 'substr'
    if (subLen == 0) return pos;  // If the substring is empty, return the starting position

    size_t i = pos;  // Start from the given position
    while (i < len) {  // Loop until the end of 'str'
        size_t j = 0;
        while (j < subLen && (i + j) < len && str[i + j] == substr[j]) {  // Match characters one by one
            ++j;
        }
        if (j == subLen) return i;  // If full match found, return the starting position
        if (i + subLen < len && str[i] != substr[0]) {
            ++i;  // Skip to the next character if the match fails
        } else {
            ++i;
        }
    }
    return string::npos;  // Return 'npos' if substring is not found
}

bool custom_open_file(ifstream& file, const string& filename) {
    file.open(filename, ios::in);  // Open the file in read mode
    return file.good();  // Return true if the file opened successfully, false otherwise
}
bool ObtainLine(ifstream& file, string& line) {
    if (!file) {  // Check if the file stream is valid
        return false;
    }
    char ch;
    line.clear();  // Clear any previous content in the 'line'
    while (file.get(ch)) {  // Read the file one character at a time
        if (ch == '\n') {  // Stop if the end of the line is reached
            break;
        }
        line += ch;  // Add the character to 'line'
    }
    return !line.empty();  // Return true if the line is not empty
}

// Function to analyze the input file and process instructions and literals
void analysis(string file, ofstream& LogFile) {
    int loc = 0;           // Location pointer to track memory location of instructions
    int line_count = 1;    // Line number tracker for error reporting
    string line;           // String to hold each line read from the file

    // Open the file for reading
    ifstream PersFile(file);
    if (!PersFile.is_open()) {
        cerr << "Error: Unable to open file: " << file << endl; // If file can't be opened, display error
        return;
    }

    // Read the file line by line
    while (getline(PersFile, line)) {
        // Extract instruction part from the line, ignoring comments (denoted by semicolon)
        string instr = custom_substr2(line, 0, custom_find2(line, ";"));
        instr = trim(instr);  // Remove leading and trailing spaces

        if (instr.empty()) {   // If the instruction is empty, skip the line
            line_count++;      // Increment line count to process next line
            continue;
        }

        // Process the instruction and check for any errors
        string mistakes = InstrToTable(instr, &loc, line_count);
        LogFile << mistakes;  // Write the mistakes (if any) to the log file
        loc++;                // Increment location to track next memory location

        line_count++;         // Move to the next line
    }

    // After processing all instructions, handle literals
    for (int i = 0; i < TableOfLiterals.size(); ++i) {
        if (TableOfLiterals[i].address == -1) {  // If literal doesn't have an address yet
            TableOfLiterals[i].address = loc++; // Assign it a location
        }
    }

    // Close the file after reading all lines
    PersFile.close();
}
// Custom implementation for make_tuple to return a tuple with encoded instruction, mistakes, and machine code
tuple<string, string, string> FuncForTouple(const string& EncodedStuff, const string& mistakes, const string& MachineCode) {
    // Manually constructing the tuple and assigning values
    tuple<string, string, string> result;
    get<0>(result) = EncodedStuff; // The encoded instruction as a string
    get<1>(result) = mistakes;    // Any mistakes or errors encountered during processing
    get<2>(result) = MachineCode; // The machine code corresponding to the instruction
    return result;
}
// Function to process and encode a single instruction
tuple<string, string, string> InstrToCode(string instr, int* location_pointer, int line) {
    int loc = *location_pointer;    // Get the current location pointer
    string EncodedStuff = IntToHexa(loc) + " ";  // Initialize the encoded instruction string with the location
    string mistakes = "", MachineCode = "";      // Initialize empty strings for mistakes and machine code
    
    // Handling the case when the instruction has a label (e.g., "LABEL: instruction")
    if (instr.find(':') != string::npos) {
        int colon_pos = instr.find(':');  // Find the position of the colon
        string label = instr.substr(0, colon_pos);  // Extract the label
        string remaining_instr = instr.substr(colon_pos + 1);  // Extract the instruction after the label
        remaining_instr = trim(remaining_instr);  // Trim any leading/trailing spaces

        if (LabelIsValid(label)) {
            // If the label is valid, recursively process the instruction after the label
            EncodedStuff += label + ": ";  // Add label to the encoded instruction
            tie(EncodedStuff, mistakes, MachineCode) = InstrToCode(remaining_instr, &loc, line);  // Recursively encode the rest of the instruction
        } else {
            // If the label is not valid, add an error message
            mistakes += "ERROR: Invalid Label at line " + to_string(line) + "\n";
        }
    } else {
        // Process the instruction without a label
        size_t space_pos = instr.find(' ');  // Find the position of the space (separates operation and operand)
        string operation = instr.substr(0, space_pos);  // Extract the operation (e.g., "add", "sub")
        string operand = instr.substr(space_pos + 1);  // Extract the operand (e.g., a number or variable)
        operand = trim(operand);  // Trim any spaces from the operand

        // Check if the operation exists in the MOT (Mnemonic Operation Table)
        if (MOT_TableEntries.find(operation) == MOT_TableEntries.end()) {
            // If the operation is not found, log an error
            mistakes += "ERROR: Undefined Mnemonic at line " + to_string(line) + "\n";
        } else {
            string hex_value = "";

            // Operations that do not expect operands (e.g., "add", "sub", "shl", "shr")
            if (operation == "add" || operation == "sub" || operation == "shl" || operation == "shr") {
                if (!operand.empty()) {
                    // If an operand is provided for operations that don't expect one, log an error
                    mistakes += "ERROR: Operand not expected at line " + to_string(line) + "\n";
                }
                // Add the corresponding machine code for these operations
                EncodedStuff += "000000" + MOT_TableEntries[operation] + " ";
                MachineCode += "000000" + MOT_TableEntries[operation] + " ";
            } else if (is_number(operand)) {
                // If the operand is a number, encode it directly
                hex_value = IntToHexa(tonum(operand));
                EncodedStuff += hex_value.substr(hex_value.length() - 6) + MOT_TableEntries[operation] + " ";
                MachineCode += hex_value.substr(hex_value.length() - 6) + MOT_TableEntries[operation] + " ";
            } else {
                bool symbol_found = false;
                // Loop through the symbol table to find the operand
                for (auto& symbol : sym_table) {
                    if (symbol.name == operand) {
                        symbol_found = true;
                        // Handle symbol based on whether it's a set variable or a normal variable
                        if (symbol.set) {
                            hex_value = IntToHexa(symbol.ValueOfSet);  // For set variables, use their value
                        } else {
                            hex_value = IntToHexa(symbol.address);    // For normal variables, use their address
                        }
                        EncodedStuff += hex_value.substr(hex_value.length() - 6) + MOT_TableEntries[operation] + " ";
                        MachineCode += hex_value.substr(hex_value.length() - 6) + MOT_TableEntries[operation] + " ";
                        break;
                    }
                }

                if (!symbol_found) {
                    // If the operand is not found in the symbol table, log an error
                    mistakes += "ERROR: Unknown Symbol at line " + to_string(line) + "\n";
                }
            }
        }
    }

    // Append the final instruction to the encoded string and return the result as a tuple
    EncodedStuff += instr + "\n";  // Append the original instruction
    return FuncForTouple(EncodedStuff, mistakes, MachineCode);  // Return the result as a tuple
}
void synthesize(string file, ofstream& OutFile, ofstream& LogFile, ofstream& ObjectFile) {
    // Initialize variables for file processing and line counting
    string line;
    int loc = 0;  // Location counter, tracks memory address for each instruction
    int line_count = 1;  // Tracks line number in the source file

    // Open the input source file
    ifstream PersFile(file);
    if (!PersFile.is_open()) {
        // If the file can't be opened, print an error and exit the function
        cerr << "ERROR: Unable to open source file: " << file << endl;
        return;
    }

    // Read the source file line by line
    while (getline(PersFile, line)) {
        // Remove comments (anything after a semicolon) and trim spaces
        string instr = line.substr(0, line.find(";", 0));  // Remove comments
        instr = trim(instr);  // Trim leading/trailing spaces

        // Skip empty lines
        if (instr.empty()) {
            line_count++;  // Move to the next line
            continue;  // Skip this iteration and go to the next line
        }

        // Declare variables to hold the results of instruction encoding
        string EncodedStuff, mistakes, MachineCode;
        // Call the InstrToCode function to encode the instruction
        tie(EncodedStuff, mistakes, MachineCode) = InstrToCode(instr, &loc, line_count++);

        // If there is any encoded instruction, write it to the output file
        if (!EncodedStuff.empty()) {
            OutFile << EncodedStuff;
        }

        // If any mistakes were detected during encoding, log them in the log file
        if (!mistakes.empty()) {
            LogFile << mistakes;
        }

        // If valid machine code is generated, convert it to binary and write to the object file
        if (!MachineCode.empty()) {
            try {
                // Convert the MachineCode string (hex) to a 32-bit unsigned integer
                uint32_t temp = stoul("0x" + trim(MachineCode), nullptr, 16);
                // Write the binary machine code to the Object file
                ObjectFile.write(reinterpret_cast<char*>(&temp), sizeof(temp));
            } catch (const exception& e) {
                // If there is an error with the machine code format, log it
                LogFile << "ERROR: Invalid machine code format at line " + to_string(line_count) + "\n";
            }
        }

        // Increment the location counter to point to the next memory address
        loc++;
    }
    // Close the input source file
    PersFile.close();

    // If no lines were processed, log a warning about the empty file
    if (line_count == 1) {
        LogFile << "WARNING: The input file is empty!" << endl;
    }
}
int main(int argc, char* argv[]) {
    if (argc < 2) { // Check if an input file is provided as a command-line argument
        cerr << "ERROR: Input file not specified." << endl;
        return 1; // Exit with an error code
    }

    string inputFile = argv[1]; // Get the input file name from the command-line argument
    string baseName = inputFile.substr(0, inputFile.find_last_of('.')); // Extract the base name (filename without extension)

    string outputFileName = baseName + ".L";     // Construct the name for the encoded instruction file
    string logFileName = baseName + ".log";      // Construct the name for the log file
    string objectFileName = baseName + ".o";     // Construct the name for the binary object file

    ofstream outputFile(outputFileName);         // Open the output file for encoded instructions
    ofstream logFile(logFileName);               // Open the log file for warnings/errors
    ofstream objectFile(objectFileName, ios::binary); // Open the object file in binary mode for machine code

    if (!outputFile.is_open() || !logFile.is_open() || !objectFile.is_open()) { // Check if all output files were successfully opened
        cerr << "ERROR: Failed to open output files." << endl;
        return 1; // Exit with an error code if any file failed to open
    }

    MOT_TableEntries_init(); // Initialize the Mnemonic Operation Table (MOT)

    analysis(inputFile, logFile); // Perform analysis on the input file to populate symbol and literal tables

    synthesize(inputFile, outputFile, logFile, objectFile); // Encode instructions and generate output, log, and object files

    outputFile.close(); // Close the output file after processing
    logFile.close();    // Close the log file after processing
    objectFile.close(); // Close the object file after processing

    return 0; // Return 0 to indicate successful execution
}


