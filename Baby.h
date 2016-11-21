#ifndef _BABY
#define _BABY

#include <bitset>
#include <vector>

using namespace std;

class Baby {
private:
  //Control Instruction, Incremented before fetching the instruction stores the address of the next 
  bitset<32> CI;

  //Present Instruction. 
  bitset<32> PI;
  
  //Holds the results of our operation. All
  bitset<32> accumulator;
  
  //Store is a vector of 32 bit bitsets. This allows us to expand the store if needed
  vector<bitset<32>> store;

  bool testFlop;
  
  bitset<5> getOperandAddress(bitset<32> instruction);
  bitset<32> fetchFromStore(bitset<5> address);
  bitset<3> getOperator(bitset<32> instruction);

  bitset<32> binaryAdder(bitset<32> arg1, bitset<32> arg2);
  int convertOpcodeToIndex(bitset<3> opcode);
  int convertAddressToIndex(bitset<5> address);
  int convertBinaryToDecimal(bitset<32> convertThis);
  
  //Define the function pointer we'll be storing in our instruction set array.
  typedef void (Baby::*instruction_ptr)(bitset<5>);
  
  //Copies the contents of the operand address to the CI
  void JMP(bitset<5> operand);

  //Copies the contents of the operand address and adds them to the CI
  void JRP(bitset<5> operand); 
  
  //Copies and negates the contents of the Store to the Accumulator.
  void LDN(bitset<5>);

  //Copies the contents of the Accumulator to the Store.
  void STO(bitset<5>);

  //Subtracts contents of Store from Accumulator. Is function 4 but also 5
  void SUB(bitset<5>);

  //Skips over the next instruction to be executed if the Accumulator is a negative number
  void CMP(bitset<5>);
  
  //Halts the fetch-execute cycle and activates the stop display bit
  void STOP(bitset<5>);

  //store the pointers to the preceding functions in their relevant instruction index. We can then call the function directly by simply converting the opcode to decimal and passing in the operand 
  instruction_ptr symbolTable[8] = {&Baby::JMP, &Baby::JRP, &Baby::LDN, &Baby::STO, &Baby::SUB, &Baby::SUB, &Baby::CMP, &Baby::STOP};

 
 
 public:
  Baby();
  Baby(vector<bitset<32>> registers);

  //accessors for displaying Register, control and status info.
  bitset<32> getCI();
  bitset<32> getPI();

  bool stopped, stepExecution;
  void printRegisters();

  void increment();

  //increments the CI, stores the data CI now points to in the PI
  void fetch();

  void decode();

  void execute(bitset<3> opcode, bitset<5> operandAddress);
};
#endif
