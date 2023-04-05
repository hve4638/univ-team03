#define CMD char*
#define CMDArray char**

void runProgram(CMDArray, size_t);

int splitCommand(CMD input, CMDArray output, size_t *capcity);

int parseCommand(CMDArray input, CMDArray output, size_t *capcity);

void runBuiltIn(CMDArray);