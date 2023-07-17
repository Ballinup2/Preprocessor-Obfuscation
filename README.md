# Preprocessor-Obfuscation
Finds and randomizes data stored in the #define preprocessor

#- How to Use -
Obfuscator.cpp is a program designed to find #define preprocessors used to function name obfuscation and change the value stored in them. It will find and change all #define preprocessors within the specified file, it is recommended to create a file specifically to hold function and variable obfuscations

#- Commands -
-help : Shows the help menu 
-verbose : shows a more diverse log of what the program is doing

./Obfuscator <filepath> <verbosity>
<filepath> is the command to be replaced by the -help command\n";

#- Example -

// in our code....
#define SomeFunctionName abc

void SomeFunctionName() { <- abc will be inserted into this functions name at compile time
  std::cout << "Hello World!\n";
}

int main(int argc, char* argv[]) {
  SomeFunctionName(); <- the function can still be called with this alias
  return 0;
}

// After using this file with Obfuscator...

// in our code....
#define SomeFunctionName t5p

void SomeFunctionName() { <- t5p will be inserted into this functions name at compile time
  std::cout << "Hello World!\n";
}

int main(int argc, char* argv[]) {
  SomeFunctionName(); <- the function can still be called with this alias
  return 0;
}
