/* Authors: Ewan Mallinson - 150007735 Martin Learmont - */
/* Module: AC21009 Team 20*/

#include "Baby.h"
#include <iostream>
#include <cmath>

using namespace std;

template <size_t T>
bitset<T> reverse(bitset<T> initialSet){
  bitset<T> reversed = bitset<T>();
  for(int i = 0; i < T; i++){
    reversed[i] = initialSet[(T-1)-i];
  }
  return reversed;
}

template <size_t T>
int binaryToDecimal(bitset<T> binary){
  bool isNegative = binary[T-1];
  int decimal = 0;
  for(int i = 0; i < T-1; i++){
    if (binary[i])
      decimal += pow(2, i);
  }
  if(isNegative){
    decimal *= -1; 
  }
  return decimal;
}

Baby::Baby(){
  //Create our store of empty registers.
  bitset<32> initialRegister;
  store.resize(32, initialRegister);
  
  //This is only here for testing
  bitset<5> op;

  stopped = false;
  testFlop = false;
  
  int x = 0;
  while(x<=7){
    ((*this).*symbolTable[x])(op);
    x++;
    }
}

Baby::Baby(vector<bitset<32>> registers){
  store = registers;
  
  CI = bitset<32>();
  stopped = false;
  testFlop = false;
  accumulator = bitset<32>();
  
}


int Baby::convertOpcodeToIndex(bitset<3> opcode){
  bitset<3> reversed = bitset<3>();
  for(int i = 2; i >= 0; i--){
    reversed[i] = opcode[2-i];
  }
  //return the converted decimal
  return reversed.to_ulong();
}

int Baby::convertBinaryToDecimal(bitset<32> convertThis){
  int x = 0;
  for(int i = 0; i <= 30; i++ ){
    convertThis[i] ? x += 2^i : false;     
    }
  return x;
  
}

bitset<32> Baby::binaryAdder(bitset<32>arg1, bitset<32> arg2){
  bitset<32> sum = bitset<32>();
  bool carry = false;
  for(int i = 0; i < 32; i++){
    sum[i] = (arg1[i] ^ arg2[i]) ^ carry;
    carry = ((arg1[i] & arg2[i]) | (arg1[i] & carry)) | (arg2[i] & carry);
  }
  return sum;
}

void Baby::JMP(bitset<5> operand){
  cout << "JMP" << endl;  
  CI = fetchFromStore(operand);
  
  cout << CI << endl;
}

void Baby::JRP(bitset<5> operand){
  cout << "JRP" << endl;
  
  //get the increment number from the store
  bitset<32> increment = fetchFromStore(operand);

  //CI is equal to itself, plus the register it is being incremented by
  CI = binaryAdder(CI, increment);
}

//Instruction Stubs, need to implement the functionality
void Baby::LDN(bitset<5> operand){
  bitset<32> storeLine = fetchFromStore(operand);

  //flip the positive/negative bit
  storeLine[31] = !storeLine[31];
  accumulator = storeLine;
  cout << "LDN" << endl;
  cout << "StoreLine: " << reverse(storeLine) << endl;
  cout << binaryToDecimal(storeLine) << endl;
}

void Baby::STO(bitset<5> operand){
  cout << "STO" << endl;
  int storeIndex = operand.to_ulong();
  store[storeIndex] = accumulator;
}

void Baby::SUB(bitset<5> operand){
  cout << "SUB" << endl;
  bitset<32> storeLine = fetchFromStore(operand);
  bitset<32> product  = bitset<32>();
  bool borrow = false;
  for(int i = 0; i <32; i++){
    product[i] = accumulator[i] ^ storeLine[i] ^ borrow;
    //we borrow from the next bit if the accumulator bit is 0 and the borrow or storeLine bits are 1 or if the borrow and storeline bits are one
    borrow = (~accumulator[i] & (borrow | storeLine[i])) | storeLine[i] & borrow;
  }
  cout << "Accumulator: " << reverse(accumulator) << endl;
  
  accumulator = product;
  cout << "StoreLine: " << reverse(storeLine) << endl; 
  cout << "Product: " << reverse(product) << endl;
}

void Baby::CMP(bitset<5> operand){
  cout << "CMP" << endl;
  //if the accumulator is negative.
  if(accumulator[31]){
    //set testFlop to true in order to increment CI by 2 in the next fetch
    testFlop = true;
  }
}

void Baby::STOP(bitset<5> operand){
  cout << "STOP" << endl;
  stopped = true;
}


bitset<32> Baby::fetchFromStore(bitset<5> address){
  bitset<32> registerContents = bitset<32>();

  //get the decimal value of the address that corresponds to the index of the register in the store
  unsigned int addressIndex = address.to_ulong();

  //get the register contents using the address index.
  registerContents = store[addressIndex];

  //return the register contents
  return registerContents;
}



void Baby::fetch(){
  //get the address of PI from CI's operand
  bitset<5> PIAddress = getOperandAddress(CI);
  
  //get the instruction to be executed from the address of CI and assign it to PI
  PI = fetchFromStore(PIAddress);
  decode();
}

void Baby::increment(){
  cout << ">> increment" << endl;

  //create a new bitset with the value 1
  bitset<32> increment = bitset<32>();

  //if the test flip flop has been set from CMP increment by two, otherwise increment by one.
  if(testFlop){
    //set increment to 2
    increment[1] = true;
    testFlop = false;
  }
  else{
    //set increment to 1
    increment[0] = 1;
  }

  //increment the address of the CI by summing it with the increment bitset.
  CI = binaryAdder(CI, increment);

  cout << "<< increment increment is: "<< increment <<  "\n CI is: " << CI << endl;
  fetch();
}



void Baby::decode(){
  //get the current opcode from PI
  bitset<3> opcode = getOperator(PI);
  
  //get the operand address as well
  bitset<5> operandAddress = getOperandAddress(PI);
  
  execute(opcode, operandAddress);  
}

void Baby::execute(bitset<3> opcode, bitset<5> operandAddress){
  unsigned int opcodeIndex = opcode.to_ulong();
  
  ((*this).*symbolTable[opcodeIndex])(operandAddress);

}

bitset<5> Baby::getOperandAddress(bitset<32> instruction){
  bitset<5> operand = bitset<5>();
  
  for(int i = 0; i <= 4; i++){
    //extract bits one through five from the instruction and insert them into the operand
    operand[i] = instruction[i];
  }
  
  //return the extracted operand to the caller
   return operand;
}

bitset<3> Baby::getOperator(bitset<32> instruction){
  bitset<3> opcode = bitset<3>();
  
  for(int i = 13; i <= 15; i++){
    //Extract the first, second and third bits of the opcode from the instruction
    opcode[i-13] = instruction[i];
  }
  
  //return the extracted opcode to the caller
  return opcode;
}
