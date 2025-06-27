#include <bits/stdc++.h> // Includes all standard libraries
using namespace std;

// Function to output an empty line using cout.put()
void enter() {
    cout.put('\n'); // Prints a single newline character
}

// Function to output a message using cout.put()
void out(const string& msg) {
    for (char ch : msg) {      // Loop through each character in the string
        cout.put(ch);          // Output the character using cout.put()
    }
}

// Function to write data to a file using ofstream
void writee(ofstream& file, const string& data) {
    if (file.is_open()) {      // Check if the file stream is open
        for (char ch : data) { // Loop through each character in the data string
            file.put(ch);      // Write the character to the file using file.put()
        }
    }
}
// Utility function to check if a string is a number
bool is_number(const string& s) {
    string temp = s;                 // Copy the input string
    int i = 0;

    // Handle signs at the beginning
    if (temp[i] == '-' || temp[i] == '+') { 
        i++;                         // Skip the sign (+ or -)
    }

    // Handle hexadecimal case
    if (temp.length() > i + 1 && temp[i] == '0' && temp[i + 1] == 'x') { 
        i += 2;                      // Skip "0x" prefix
        // Check if the remaining characters are valid hexadecimal digits
        for (; i < temp.length(); ++i) {
            if (!isxdigit(temp[i])) { 
                return false;        // Return false if any non-hex digit is found
            }
        }
        return true;                 // Valid hexadecimal number
    }

    // Check if all characters are digits for regular numbers
    for (; i < temp.length(); ++i) {
        if (!isdigit(temp[i])) {     // Return false if any non-digit character is found
            return false;
        }
    }

    return true;                     // The string is a valid number
}

// Custom find function
template<typename ForwardIterator, typename T>
bool locate(ForwardIterator first, ForwardIterator last, const T& value) {
    // Iterates through the range [first, last) looking for the value
    while (first != last) {          // Loop until the end of the range is reached
        if (*first == value) {       // Check if the current element matches the value
            return true;             // Value found
        }
        ++first;                     // Move to the next element
    }
    return false;                    // Value not found
}
// Function to convert an integer to an 8-character hexadecimal string
string IntToHexa(int i) {
    stringstream stream;                     // Create a stringstream for formatting
    stream << std::uppercase << std::hex;   // Convert to uppercase hexadecimal
    stream << i;                             // Write the integer to the stream
    string hex_str = stream.str();          // Retrieve the formatted string
    while (hex_str.length() < 8) {          // Ensure the length is at least 8 characters
        hex_str = "0" + hex_str;            // Pad with leading zeros if necessary
    }
    return hex_str;                         // Return the formatted hexadecimal string
}

// Structure representing the machine state with registers
struct MachineState {
    int32_t A1;  // General-purpose register A1
    int32_t B1;  // General-purpose register B1
    int32_t PC;  // Program Counter register
    int32_t SP;  // Stack Pointer register
};

// Global machine state and memory
MachineState machineState = {0, 0, 0, 0}; // Initialize machine state to zeros
int32_t memory[10000] = {0};              // Memory array initialized to zeros
vector<int> PC_of_DataVar;                // Stores program counters of data variables

// Accessors for the machine registers
int32_t& A1 = machineState.A1;  // Reference to A1 register
int32_t& B1 = machineState.B1;  // Reference to B1 register
int32_t& PC = machineState.PC;  // Reference to Program Counter (PC) register
int32_t& SP = machineState.SP;  // Reference to Stack Pointer (SP) register

// Function to extract the operand and opcode from a 32-bit instruction
tuple<int32_t, int32_t> inst_to_operand_opcode(int32_t instr) {
    int32_t opcode = 0;                     // Variable to store the opcode
    int32_t operand = 0;                    // Variable to store the operand

    int32_t mask_opcode = 0x000000FF;       // Mask for extracting the opcode (last 8 bits)
    opcode = instr & mask_opcode;           // Extract opcode using bitwise AND

    int32_t mask_operand = 0xFFFFFF00;      // Mask for extracting the operand (remaining 24 bits)
    operand = instr & mask_operand;         // Extract operand using bitwise AND
    operand = operand >> 8;                 // Shift the operand right by 8 bits to align it

    return make_tuple(operand, opcode);     // Return the operand and opcode as a tuple
}
// Function to display the usage prompt and available options
void prompt() {
    // A map to hold command-line options and their descriptions
    map<string, string> options = {
        {"-Trace_func", "Show instruction trace function"},
        {"-before", "Show memory dump before execution"},
        {"-after", "Show memory dump after execution"},
        {"-isa", "Display Instruction Set Architecture"}
    };

    // Display the usage format
    cout << "Usage: ./emu.exe [option] file.o\n";
    cout << "Options:\n";

    // Iterate over the options map and print each option with its description
    for (const auto& option : options) {
        cout << "\t" << option.first << "\t" << option.second << endl;
    }
}

// Function to dump memory content to a file and console
void Dump_Mem(int poc, ofstream& trcfile) {
    // Write and print a header for the memory dump
    trcfile << "Dump from memory\n";
    cout << "Dump from memory\n";

    // Iterate through the memory up to the specified point of count (poc)
    for (int cat = 0; cat < poc; ++cat) {
        if (cat % 4 == 0) {  // Print 4 memory values per line
            if (cat != 0) {  // Add a newline after every 4 values
                cout << "\n";
                trcfile << "\n";
            }
            // Print the memory address and its value
            cout << IntToHexa(cat) << "\t" << IntToHexa(memory[cat]) << " ";
            trcfile << IntToHexa(cat) << "\t" << IntToHexa(memory[cat]) << " ";
        } else {
            // Print only the memory value for the remaining entries
            cout << IntToHexa(memory[cat]) << " ";
            trcfile << IntToHexa(memory[cat]) << " ";
        }
    }

    // Add a final newline for formatting
    cout << "\n";
}

// Function to display the Instruction Set Architecture (ISA)
void InsSetArch() {
    // A vector of pairs where each pair contains an opcode and its mnemonic/description
    vector<pair<int, string>> instructions = {
        {0,  "ldc      value"},       // Load constant
        {1,  "adc      value"},       // Add constant
        {2,  "ldl      value"},       // Load local
        {3,  "stl      value"},       // Store local
        {4,  "ldnl     value"},       // Load non-local
        {5,  "stnl     value"},       // Store non-local
        {6,  "add"},                  // Add
        {7,  "sub"},                  // Subtract
        {8,  "shl"},                  // Shift left
        {9,  "shr"},                  // Shift right
        {10, "adj      value"},       // Adjust stack pointer
        {11, "a2sp"},                 // Copy accumulator to stack pointer
        {12, "sp2a"},                 // Copy stack pointer to accumulator
        {13, "call     offset"},      // Call subroutine
        {14, "return"},               // Return from subroutine
        {15, "brz      offset"},      // Branch if zero
        {16, "brlz     offset"},      // Branch if less than zero
        {17, "br       offset"},      // Unconditional branch
        {18, "HALT"},                 // Halt the program
        {19, "SET      value"}        // Set value
    };

    // Print headers for the opcode table
    cout << "Opcode Mnemonic Operand\n";
    cout << "       data     value\n";

    // Iterate through the instruction set and print each opcode and its mnemonic
    for (const auto& instruction : instructions) {
        cout << instruction.first << "      " << instruction.second << endl;
    }
}

// Structure to store the Mapping of Opcode and Mnemonic
struct MOTEntry {
    int opcode;          // Opcode of the instruction
    string mnemonic;     // Mnemonic name of the instruction
};

// Global map to store the opcode-to-mnemonic table
map<int, string> MOT_TableEntries;

// Function to initialize the opcode-mnemonic mapping
void MOT_TableEntries_init() {
    // Array of predefined opcode-mnemonic pairs
    MOTEntry entries[] = {
        {0, "ldc"}, {1, "adc"}, {2, "ldl"}, {3, "stl"},
        {4, "ldnl"}, {5, "stnl"}, {6, "add"}, {7, "sub"},
        {8, "shl"}, {9, "shr"}, {10, "adj"}, {11, "a2sp"},
        {12, "sp2a"}, {13, "call"}, {14, "return"}, {15, "brz"},
        {16, "brlz"}, {17, "br"}, {18, "HALT"}, {19, "data"},
        {20, "SET"}
    };

    // Populate the global map with opcode-mnemonic pairs
    for (const auto& entry : entries) {
        MOT_TableEntries[entry.opcode] = entry.mnemonic;
    }
}

// Function to trace the execution of instructions
int Trace_func(int PC, int poc, ofstream& trcfile) {
    int count = 0;       // Instruction execution counter
    bool running = true; // Running state of the program
    int old_pc = PC;     // Store the previous PC to detect infinite loops

    // Continue executing instructions until HALT or a condition stops execution
    while (running) {
        // Fetch the instruction from memory using the PC
        int32_t instr = memory[PC];
        int32_t operand, operation;

        // Decode the instruction into operand and opcode
        tie(operand, operation) = inst_to_operand_opcode(instr);

        // Create a trace message with the current machine state
        string traceMessage = "PC: " + IntToHexa(PC) + "\tSP: " + IntToHexa(SP)
                            + "\tA1: " + IntToHexa(A1) + "\tB1: " + IntToHexa(B1)
                            + "\t" + MOT_TableEntries[operation] + " " + to_string(operand);

        // Output the trace message to console and trace file
        out(traceMessage);
        enter(); // Add a newline to the console output
        writee(trcfile, traceMessage + "\n"); // Write to the trace file

        // Skip execution if the PC is part of PC_of_DataVar
        if (find(PC_of_DataVar.begin(), PC_of_DataVar.end(), PC) != PC_of_DataVar.end()) {
            PC++;
            continue;
        }

        // Switch case to execute operations based on the opcode
        switch (operation) {
            case 0:  // ldc (Load constant)
                B1 = A1;        // Backup current A1 value to B1
                A1 = operand;   // Load operand into A1
                break;
            case 1:  // adc (Add constant)
                A1 += operand;  // Add operand to A1
                break;
            case 2:  // ldl (Load local)
                B1 = A1;        // Backup current A1 value to B1
                A1 = memory[SP + operand]; // Load value from stack relative to SP
                break;
            case 3:  // stl (Store local)
                memory[SP + operand] = A1; // Store A1 value to stack
                A1 = B1;        // Restore previous value of A1 from B1
                break;
            case 4:  // ldnl (Load non-local)
                A1 = memory[A1 + operand]; // Load value at address (A1 + operand)
                break;
            case 5:  // stnl (Store non-local)
                memory[A1 + operand] = B1; // Store B1 value at address (A1 + operand)
                break;
            case 6:  // add
                A1 += B1;       // Add A1 and B1, store result in A1
                break;
            case 7:  // sub
                A1 = B1 - A1;   // Subtract A1 from B1, store result in A1
                break;
            case 8:  // shl (Shift left)
                A1 = B1 << A1;  // Shift B1 left by A1 bits
                break;
            case 9:  // shr (Shift right)
                A1 = B1 >> A1;  // Shift B1 right by A1 bits
                break;
            case 10: // adj (Adjust SP)
                SP += operand;  // Adjust the stack pointer by operand
                break;
            case 11: // a2sp (Accumulator to SP)
                SP = A1;        // Copy A1 to stack pointer (SP)
                A1 = B1;        // Restore previous value of A1 from B1
                break;
            case 12: // sp2a (SP to Accumulator)
                B1 = A1;        // Backup current A1 value to B1
                A1 = SP;        // Copy SP to A1
                break;
            case 13: // call (Subroutine call)
                B1 = A1;        // Backup current A1 value to B1
                A1 = PC;        // Save current PC in A1
                PC += operand;  // Jump to the subroutine
                break;
            case 14: // return
                PC = A1;        // Restore PC from A1
                A1 = B1;        // Restore previous value of A1 from B1
                break;
            case 15: // brz (Branch if zero)
                if (A1 == 0) {
                    PC += operand; // Branch by operand offset if A1 is zero
                }
                break;
            case 16: // brlz (Branch if less than zero)
                if (A1 < 0) {
                    PC += operand; // Branch by operand offset if A1 is negative
                }
                break;
            case 17: // br (Unconditional branch)
                PC += operand;  // Branch by operand offset unconditionally
                break;
            case 18: // HALT (Stop execution)
                out(to_string(count) + " number of instructions executed\n");
                running = false; // Stop execution loop
                break;
            case 20: // SET (Set A1)
                A1 = operand;   // Set A1 to operand
                break;
            default:  // Unknown opcode
                out("Unknown operation\n");
                running = false; // Stop execution loop
                break;
        }

        // Increment PC and update instruction count
        PC++;
        count++;

        // Detect infinite loops by checking if PC hasn't changed
        if (PC == old_pc) {
            out("Infinite loop detected\n");
            break;
        }

        // Update old PC to the current PC
        old_pc = PC;
    }

    return count; // Return the total instruction count
}
int main(int Arg_C, char* Arg_V[])
{
    // Check if sufficient command-line arguments are provided
    if (Arg_C < 3)
    {
        // Display usage instructions if arguments are insufficient
        prompt();
        return 0;
    }

    // Initialize the Machine Operand Table (MOT)
    MOT_TableEntries_init();

    // Input file containing machine code
    string in_file = Arg_V[2];

    // Create the output file name for the trace log
    string Trace_func_file = in_file.substr(0, in_file.find(".", 0)) + ".Trace_func";

    // Open input file in binary mode and trace output file
    ifstream infile(in_file, ios::binary);
    ofstream trcfile(Trace_func_file);

    // Check if the input and output files were opened successfully
    if (!infile.is_open() || !trcfile.is_open())
    {
        cout << "Error opening files." << endl;
        return 0;
    }

    // Declare a 32-bit integer to hold each instruction
    int32_t instr_code;
    int poc = 0; // Position counter for memory

    // Read instructions from the input file and load them into memory
    while (infile.read((char*)&instr_code, sizeof(instr_code)))
    {
        int32_t operand, operation;

        // Decode instruction into operand and operation
        tie(operand, operation) = inst_to_operand_opcode(instr_code);

        // Check for SET or DATA instructions (special handling)
        if (operation == 19 || operation == 20)
        {
            // Store only the operand value in memory for DATA/SET instructions
            memory[poc] = operand;

            // Keep track of memory locations for data variables
            PC_of_DataVar.push_back(poc++);
        }
        // Check if the operation is within valid instruction range
        else if (operation >= 0 && operation < 20)
        {
            // Store the full instruction in memory
            memory[poc++] = instr_code;
        }
        else
        {
            // Invalid opcode encountered
            cout << "Invalid instruction at memory location " << poc << endl;
            return 0;
        }
    }

    // Initialize the machine registers
    A1 = 0; // Accumulator 1
    B1 = 0; // Accumulator 2
    PC = 0; // Program Counter
    SP = sizeof(memory) / sizeof(memory[0]) - 1; // Stack Pointer set to the end of memory

    // Option to perform a memory dump **before** program execution
    if (string(Arg_V[1]) == "-before")
    {
        Dump_Mem(poc, trcfile); // Dump memory to console and trace file
    }

    // Option to execute the program and trace its execution
    if (string(Arg_V[1]) == "-Trace_func")
    {
        Trace_func(0, poc, trcfile); // Start execution from PC = 0
    }

    // Option to dump memory **after** program execution
    if (string(Arg_V[1]) == "-after")
    {
        Trace_func(0, poc, trcfile); // Execute the program
        Dump_Mem(poc, trcfile);      // Dump memory state after execution

        // Output the sorted array to a file
        ofstream sortedFile("sorted_output.txt");
        if (sortedFile.is_open())
        {
            sortedFile << "Sorted Array:\n";
            for (int i = 0; i < 10; ++i) // Assuming only the first 10 elements are sorted
            {
                sortedFile << memory[i] << " ";
            }
            sortedFile << endl;
            sortedFile.close();
        }
        else
        {
            cout << "Unable to open sorted output file." << endl;
        }
    }

    // Close the input and output files
    infile.close();
    trcfile.close();

    return 0; // Program completed successfully
}
