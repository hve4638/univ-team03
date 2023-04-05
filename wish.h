#define CMD char*
#define CMDArray char**

void runProgram(CMD);

int splitCommand(CMD input, CMDArray output);

int parseCommand(CMDArray input, CMDArray output);

void runBuiltIn(CMDArray);