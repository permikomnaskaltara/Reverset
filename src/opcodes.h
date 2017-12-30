#ifndef OPCODES_H
#define OPCODES_H

enum x86_OPERAND_TYPE
{
	REG,
	MRM,
	IMM8,
	IMM32,
	RPC,
	REL8,
	REL1632,
	//Some instructions have set operands, like 0x05 is add something to eax
	ONE,
	EAX,
	//4 Mov instructions don't use MOD/RM but just put the offset in there
	MOFF,
	NON
};

typedef struct x86_opcode
{
	//Two byte opcode
	unsigned char two_bytes;
	unsigned char opcode;//Byte value of opcode
	unsigned char multi_byte;//If it is a multi byte opcode this will hold "base"
	//
	int modrm_dir;
	int size;	//0 is 8 bit operands, 1 for 16 or 32 bit operands
	int extended; //Is the second byte used to extend the opcode
	//The opcode operand types
	enum x86_OPERAND_TYPE arg1, arg2, arg3;
	char * mnemonic;
} x86_opcode;

static const x86_opcode x86_opcodes[] = {
	{0x00, 0x00, 0x00, 0, 0, 0, MRM, REG, NON, "add"},
	{0x00, 0x01, 0x00, 0, 1, 0, MRM, REG, NON, "add"},
	{0x00, 0x02, 0x00, 1, 0, 0, REG, MRM, NON, "add"},
	{0x00, 0x03, 0x00, 1, 0, 0, REG, REG, NON, "add"},
	{0x00, 0x04, 0x00, 0, 0, 0, EAX, IMM8, NON, "add"},
	{0x00, 0x05, 0x00, 0, 1, 0, EAX, IMM32, NON, "add"},
	//06 is push es
	//07 is pop es
	{0x00, 0x08, 0x00, 0, 0, 0, MRM, REG, NON, "or"},
	{0x00, 0x09, 0x00, 0, 1, 0, MRM, REG, NON, "or"},
	{0x00, 0x0A, 0x00, 1, 0, 0, REG, MRM, NON, "or"},
	{0x00, 0x0B, 0x00, 1, 1, 0, REG, MRM, NON, "or"},
	{0x00, 0x0D, 0x00, 0, 0, 0, EAX, IMM8, NON, "or"},
	{0x00, 0x0C, 0x00, 0, 0, 0, EAX, IMM8, NON, "or"},
	{0x00, 0x0D, 0x00, 0, 1, 0, EAX, IMM32, NON, "or"},
	//0E is push cs
	//0F is two byte instruction 

	{0x00, 0x10, 0x00, 0, 0, 0, MRM, REG, NON, "adc"},
	{0x00, 0x11, 0x00, 0, 1, 0, MRM, REG, NON, "adc"},
	{0x00, 0x12, 0x00, 1, 0, 0, REG, MRM, NON, "adc"},
	{0x00, 0x13, 0x00, 1, 1, 0, REG, MRM, NON, "adc"},
	{0x00, 0x14, 0x00, 0, 0, 0, EAX, IMM8, NON, "adc"},
	{0x00, 0x15, 0x00, 0, 1, 0, EAX, IMM32, NON, "adc"},
	//16 is push ss
	//17 is poop ss
	{0x00, 0x18, 0x00, 0, 0, 0, MRM, REG, NON, "sbb"},
	{0x00, 0x19, 0x00, 0, 1, 0, MRM, REG, NON, "sbb"},
	{0x00, 0x1A, 0x00, 1, 0, 0, REG, MRM, NON, "sbb"},
	{0x00, 0x1B, 0x00, 1, 1, 0, REG, MRM, NON, "sbb"},
	{0x00, 0x1C, 0x00, 0, 0, 0, EAX, IMM8, NON, "sbb"},
	{0x00, 0x1D, 0x00, 0, 1, 0, EAX, IMM32, NON, "sbb"},
	//1E is pop ds
	//1F is pop ds

	{0x00, 0x20, 0x00, 0, 0, 0, MRM, REG, NON, "and"},
	{0x00, 0x21, 0x00, 0, 1, 0, MRM, REG, NON, "and"},
	{0x00, 0x22, 0x00, 1, 0, 0, REG, MRM, NON, "and"},
	{0x00, 0x23, 0x00, 1, 1, 0, REG, MRM, NON, "and"},
	{0x00, 0x24, 0x00, 0, 0, 0, EAX, IMM8, NON, "and"},
	{0x00, 0x25, 0x00, 0, 1, 0, EAX, IMM32, NON, "and"},
	//26 is ES segment override
	{0x00, 0x27, 0x00, 0, 0, 0, EAX, NON, NON, "das"},
	{0x00, 0x28, 0x00, 0, 0, 0, MRM, REG, NON, "sub"},
	{0x00, 0x29, 0x00, 0, 1, 0, MRM, REG, NON, "sub"},
	{0x00, 0x2A, 0x00, 1, 0, 0, REG, MRM, NON, "sub"},
	{0x00, 0x2B, 0x00, 1, 1, 0, REG, MRM, NON, "sub"}, 
	{0x00, 0x2D, 0x00, 0, 1, 0, EAX, IMM32, NON, "sub"}, 
	{0x00, 0x2F, 0x00, 0, 0, 0, EAX, NON, NON, "das"}, 

	{0x00, 0x30, 0x00, 0, 0, 0, MRM, REG, NON, "xor"},
	{0x00, 0x31, 0x00, 0, 1, 0, MRM, REG, NON, "xor"},
	{0x00, 0x32, 0x00, 1, 0, 0, REG, MRM, NON, "xor"},
	{0x00, 0x33, 0x00, 1, 1, 0, REG, MRM, NON, "xor"},
	{0x00, 0x34, 0x00, 0, 0, 0, EAX, IMM8, NON, "xor"},
	{0x00, 0x35, 0x00, 0, 1, 0, EAX, IMM32, NON, "xor"},
	//36 is SS segment override
	//37 is aaa al, ah
	{0x00, 0x38, 0x00, 0, 0, 0, MRM, REG, NON, "cmp"},
	{0x00, 0x39, 0x00, 0, 1, 0, MRM, REG, NON, "cmp"},
	{0x00, 0x3A, 0x00, 1, 0, 0, REG, MRM, NON, "cmp"},
	{0x00, 0x3B, 0x00, 1, 1, 0, REG, MRM, NON, "cmp"},
	{0x00, 0x3C, 0x00, 0, 0, 0, EAX, IMM8, NON, "cmp"},
	{0x00, 0x3D, 0x00, 0, 1, 0, EAX, IMM32, NON, "cmp"},
	//3E is DS segment override
	//3F is AAS AL, AH
	{0x00, 0x40, 0x040, 0, 1, 0, RPC, NON, NON, "inc"},
	{0x00, 0x41, 0x040, 0, 1, 0, RPC, NON, NON, "inc"},
	{0x00, 0x42, 0x040, 0, 1, 0, RPC, NON, NON, "inc"},
	{0x00, 0x43, 0x040, 0, 1, 0, RPC, NON, NON, "inc"},
	{0x00, 0x44, 0x040, 0, 1, 0, RPC, NON, NON, "inc"},
	{0x00, 0x45, 0x040, 0, 1, 0, RPC, NON, NON, "inc"},
	{0x00, 0x46, 0x040, 0, 1, 0, RPC, NON, NON, "inc"},
	{0x00, 0x47, 0x040, 0, 1, 0, RPC, NON, NON, "inc"},
	{0x00, 0x48, 0x048, 0, 1, 0, RPC, NON, NON, "dec"},
	{0x00, 0x49, 0x048, 0, 1, 0, RPC, NON, NON, "dec"},
	{0x00, 0x4a, 0x048, 0, 1, 0, RPC, NON, NON, "dec"},
	{0x00, 0x4b, 0x048, 0, 1, 0, RPC, NON, NON, "dec"},
	{0x00, 0x4c, 0x048, 0, 1, 0, RPC, NON, NON, "dec"},
	{0x00, 0x4d, 0x048, 0, 1, 0, RPC, NON, NON, "dec"},
	{0x00, 0x4e, 0x048, 0, 1, 0, RPC, NON, NON, "dec"},
	{0x00, 0x4f, 0x048, 0, 1, 0, RPC, NON, NON, "dec"},

	{0x00, 0x50, 0x50, 0, 1, 0, RPC, NON, NON, "push"},
	{0x00, 0x51, 0x50, 0, 1, 0, RPC, NON, NON, "push"},
	{0x00, 0x52, 0x50, 0, 1, 0, RPC, NON, NON, "push"},
	{0x00, 0x53, 0x50, 0, 1, 0, RPC, NON, NON, "push"},
	{0x00, 0x54, 0x50, 0, 1, 0, RPC, NON, NON, "push"},
	{0x00, 0x55, 0x50, 0, 1, 0, RPC, NON, NON, "push"},
	{0x00, 0x56, 0x50, 0, 1, 0, RPC, NON, NON, "push"},
	{0x00, 0x57, 0x50, 0, 1, 0, RPC, NON, NON, "push"},
	{0x00, 0x58, 0x58, 0, 1, 0, RPC, NON, NON, "pop"},
	{0x00, 0x59, 0x58, 0, 1, 0, RPC, NON, NON, "pop"},
	{0x00, 0x5a, 0x58, 0, 1, 0, RPC, NON, NON, "pop"},
	{0x00, 0x5b, 0x58, 0, 1, 0, RPC, NON, NON, "pop"},
	{0x00, 0x5c, 0x58, 0, 1, 0, RPC, NON, NON, "pop"},
	{0x00, 0x5d, 0x58, 0, 1, 0, RPC, NON, NON, "pop"},
	{0x00, 0x5e, 0x58, 0, 1, 0, RPC, NON, NON, "pop"},
	{0x00, 0x5f, 0x58, 0, 1, 0, RPC, NON, NON, "pop"},

	//
	{0x00, 0x68, 0x00, 0, 1, 0, IMM32, NON, NON, "push"}, //wat

	{0x00, 0x6A, 0x00, 0, 0, 0, IMM8, NON, NON, "push"}, //wat


	{0x00, 0x81, 0x00, 1, 0, 1, MRM, IMM32, NON, "add"},
	{0x00, 0x81, 0x01, 1, 0, 1, MRM, IMM32, NON, "or"},
	{0x00, 0x81, 0x02, 1, 0, 1, MRM, IMM32, NON, "adc"},
	{0x00, 0x81, 0x03, 1, 0, 1, MRM, IMM32, NON, "sbb"},
	{0x00, 0x81, 0x04, 1, 0, 1, MRM, IMM32, NON, "and"},
	{0x00, 0x81, 0x05, 1, 0, 1, MRM, IMM32, NON, "sub"},
	{0x00, 0x81, 0x06, 1, 0, 1, MRM, IMM32, NON, "xor"},
	{0x00, 0x81, 0x07, 1, 0, 1, MRM, IMM32, NON, "cmp"},

	{0x00, 0x86, 0x00, 1, 0, 0, REG, MRM, NON, "xchg"},

	{0x00, 0x88, 0x00, 0, 0, 0, MRM, REG, NON, "mov"},
	{0x00, 0x89, 0x00, 0, 1, 0, MRM, REG, NON, "mov"},
	{0x00, 0x8a, 0x00, 0, 0, 0, REG, REG, NON, "mov"},
	{0x00, 0x8b, 0x00, 1, 1, 0, REG, MRM, NON, "mov"},
	//{0x00, 0xb8, 0x00, 0, 0, 0, MRM, IMM, NON, "mov"},
	{0x00, 0x74, 0x00, 0, 0, 0, REL8, NON, NON, "je"},
	{0x00, 0x75, 0x00, 0, 0, 0, REL8, NON, NON, "jne"},
	{0x00, 0x76, 0x00, 0, 0, 0, REL8, NON, NON, "jbe"},
	{0x00, 0x77, 0x00, 0, 0, 0, REL8, NON, NON, "jnbe"},
	{0x00, 0x78, 0x00, 0, 0, 0, REL8, NON, NON, "js"},
	{0x00, 0x79, 0x00, 0, 0, 0, REL8, NON, NON, "jns"},
	{0x00, 0x7a, 0x00, 0, 0, 0, REL8, NON, NON, "jp"},
	{0x00, 0x7b, 0x00, 0, 0, 0, REL8, NON, NON, "jnp"},
	{0x00, 0x7c, 0x00, 0, 0, 0, REL8, NON, NON, "jl"},
	{0x00, 0x7d, 0x00, 0, 0, 0, REL8, NON, NON, "jge"},
	{0x00, 0x7e, 0x00, 0, 0, 0, REL8, NON, NON, "jle"},
	{0x00, 0x7f, 0x00, 0, 0, 0, REL8, NON, NON, "jg"},
	{0x00, 0x90, 0x00, 0, 0, 0, NON, NON, NON, "nop"},
	
	//may revert dir to 0
	{0x00, 0x83, 0x00, 1, 0, 1, MRM, IMM8, NON, "add"},
	{0x00, 0x83, 0x01, 1, 0, 1, MRM, IMM8, NON, "add"},
	{0x00, 0x83, 0x02, 1, 0, 1, MRM, IMM8, NON, "adc"},
	{0x00, 0x83, 0x03, 1, 0, 1, MRM, IMM8, NON, "sbb"},
	{0x00, 0x83, 0x04, 1, 0, 1, MRM, IMM8, NON, "and"},
	{0x00, 0x83, 0x05, 1, 0, 1, MRM, IMM8, NON, "sub"},
	{0x00, 0x83, 0x06, 1, 0, 1, MRM, IMM8, NON, "xor"},
	{0x00, 0x83, 0x07, 1, 0, 1, MRM, IMM8, NON, "cmp"},

	{0x00, 0xD1, 0x00, 1, 0, 1, MRM, ONE, NON, "rol"},
	{0x00, 0xD1, 0x01, 1, 0, 1, MRM, ONE, NON, "ror"},
	{0x00, 0xD1, 0x02, 1, 0, 1, MRM, ONE, NON, "rcl"},
	{0x00, 0xD1, 0x03, 1, 0, 1, MRM, ONE, NON, "rcr"},
	{0x00, 0xD1, 0x04, 1, 0, 1, MRM, ONE, NON, "shl"},
	{0x00, 0xD1, 0x05, 1, 0, 1, MRM, ONE, NON, "shr"},
	{0x00, 0xD1, 0x06, 1, 0, 1, MRM, ONE, NON, "shl"},
	{0x00, 0xD1, 0x07, 1, 0, 1, MRM, ONE, NON, "sar"},

	{0x00, 0x80, 0x00, 0, 0, 1, MRM, IMM8, NON, "add"},
	{0x00, 0x80, 0x01, 0, 0, 1, MRM, IMM8, NON, "or"},
	{0x00, 0x80, 0x02, 0, 0, 1, MRM, IMM8, NON, "adc"},
	{0x00, 0x80, 0x03, 0, 0, 1, MRM, IMM8, NON, "sbb"},
	{0x00, 0x80, 0x04, 0, 0, 1, MRM, IMM8, NON, "and"},
	{0x00, 0x80, 0x05, 0, 0, 1, MRM, IMM8, NON, "sub"},
	{0x00, 0x80, 0x06, 0, 0, 1, MRM, IMM8, NON, "or"},
	{0x00, 0x80, 0x07, 0, 0, 1, MRM, IMM8, NON, "cmp"},
	{0x00, 0x85, 0x00, 1, 1, 0, MRM, REG, NON, "test"},
//	{0x00, 0x8d, 0x00, 0, 1, 0, REG, MRM, NON, "lea"},
	{0x00, 0xFE, 0x00, 0, 0, 1, MRM, NON, NON, "inc"},
	{0x00, 0xFE, 0x01, 0, 0, 1, MRM, NON, NON, "dec"},
	{0x00, 0xFF, 0x00, 0, 1, 1, MRM, NON, NON, "inc"},
	{0x00, 0xFF, 0x01, 0, 1, 1, MRM, NON, NON, "dec"},
	{0x00, 0xFF, 0x02, 0, 1, 1, MRM, NON, NON, "call"},
	{0x00, 0xFF, 0x03, 0, 1, 1, MRM, NON, NON, "callf"},
	{0x00, 0xFF, 0x04, 0, 1, 1, MRM, NON, NON, "jmp"},
	{0x00, 0xFF, 0x05, 0, 1, 1, MRM, NON, NON, "jmpf"},
	{0x00, 0xFF, 0x06, 0, 1, 1, MRM, NON, NON, "push"},
	{0x00, 0xC0, 0x00, 0, 0, 1, MRM, IMM8, NON, "rol"},
	{0x00, 0xC0, 0x01, 0, 0, 1, MRM, IMM8, NON, "ror"},
	{0x00, 0xC0, 0x02, 0, 0, 1, MRM, IMM8, NON, "rcl"},
	{0x00, 0xC0, 0x03, 0, 0, 1, MRM, IMM8, NON, "rcr"},
	{0x00, 0xC0, 0x04, 0, 0, 1, MRM, IMM8, NON, "shl"},
	{0x00, 0xC0, 0x05, 0, 0, 1, MRM, IMM8, NON, "shr"},
	{0x00, 0xC0, 0x06, 0, 0, 1, MRM, IMM8, NON, "sal"},	
	{0x00, 0xC0, 0x07, 0, 0, 1, MRM, IMM8, NON, "sar"},
	{0x00, 0xC1, 0x00, 0, 1, 1, MRM, IMM8, NON, "rol"},
	{0x00, 0xC1, 0x01, 0, 1, 1, MRM, IMM8, NON, "ror"},
	{0x00, 0xC1, 0x02, 0, 1, 1, MRM, IMM8, NON, "rcl"},
	{0x00, 0xC1, 0x03, 0, 1, 1, MRM, IMM8, NON, "rcr"},
	{0x00, 0xC1, 0x04, 0, 1, 1, MRM, IMM8, NON, "shl"},
	{0x00, 0xC1, 0x05, 0, 1, 1, MRM, IMM8, NON, "shr"},
	{0x00, 0xC1, 0x06, 0, 1, 1, MRM, IMM8, NON, "sal"},	
	{0x00, 0xC1, 0x07, 0, 1, 1, MRM, IMM8, NON, "sar"},
	{0x00, 0xC6, 0x00, 0, 0, 0, MRM, IMM8, NON, "mov"},
	{0x00, 0xC7, 0x00, 0, 1, 0, MRM, IMM32, NON, "mov"},
	{0x00, 0xC3, 0x00, 0, 0, 0, NON, NON, NON, "ret"},
	{0x00, 0xB0, 0xB0, 0, 0, 0, RPC, IMM8, NON, "mov"},
	{0x00, 0xB1, 0xB0, 0, 0, 0, RPC, IMM8, NON, "mov"},
	{0x00, 0xB2, 0xB0, 0, 0, 0, RPC, IMM8, NON, "mov"},
	{0x00, 0xB3, 0xB0, 0, 0, 0, RPC, IMM8, NON, "mov"},
	{0x00, 0xB4, 0xB0, 0, 0, 0, RPC, IMM8, NON, "mov"},
	{0x00, 0xB5, 0xB0, 0, 0, 0, RPC, IMM8, NON, "mov"},
	{0x00, 0xB6, 0xB0, 0, 0, 0, RPC, IMM8, NON, "mov"},
	{0x00, 0xB7, 0xB0, 0, 0, 0, RPC, IMM8, NON, "mov"},
	{0x00, 0xB8, 0xB8, 0, 1, 0, RPC, IMM32, NON, "mov"},
	{0x00, 0xB9, 0xB8, 0, 1, 0, RPC, IMM32, NON, "mov"},
	{0x00, 0xBA, 0xB8, 0, 1, 0, RPC, IMM32, NON, "mov"},
	{0x00, 0xBB, 0xB8, 0, 1, 0, RPC, IMM32, NON, "mov"},
	{0x00, 0xBC, 0xB8, 0, 1, 0, RPC, IMM32, NON, "mov"},
	{0x00, 0xBD, 0xB8, 0, 1, 0, RPC, IMM32, NON, "mov"},
	{0x00, 0xBF, 0xB8, 0, 1, 0, RPC, IMM32, NON, "mov"},
	{0x00, 0x8D, 0x00, 1, 1, 0, REG, MRM, NON, "lea"},//
	{0x00, 0xE8, 0x00, 0, 1, 0, REL1632, NON, NON, "call"},
	{0x00, 0xE9, 0x00, 0, 1, 0, REL1632, NON, NON, "jmp"},
	{0x00, 0xEB, 0x00, 0, 0, 0, REL8, NON, NON, "jmp"},
	{0x00, 0x4f, 0x048, 0, 1, 0, RPC, NON, NON, "dec"},
	{0x00, 0xf4, 0x00, 0, 0, 0, NON, NON, NON, "hlt"},
	{0x00, 0xA1, 0x00, 0, 1, 0, EAX, MOFF, NON, "mov"},

	//
	{0x00, 0xC9, 0x00, 0, 0, 0, NON, NON, NON, "leave"},
	{0x00, 0xF7, 0x00, 0, 1, 1, MRM, IMM32, NON, "test"},
	{0x00, 0xF7, 0x01, 0, 1, 1, MRM, IMM32, NON, "test"},
	{0x00, 0xF7, 0x02, 0, 1, 1, MRM, NON, NON, "not"},
	{0x00, 0xF7, 0x03, 0, 1, 1, MRM, NON, NON, "neg"},
	//{0x00, 0xF7, 0x04, 0, 1, 0, MRM, IMM32, NON, "test"}
	//{0x00, 0xF7, 0x05, 0, 1, 0, MRM, IMM32, NON, "test"}
	//{0x00, 0xF7, 0x06, 0, 1, 0, MRM, IMM32, NON, "test"}
	//{0x00, 0xF7, 0x07, 0, 1, 0, MRM, IMM32, NON, "test"}
	{0x0F, 0xBE, 0x00, 1, 0, 0, REG, MRM, NON, "movsx"},
	{0x0F, 0xB6, 0x00, 1, 1, 0, REG, MRM, NON, "movzx"},
	{0x0F, 0x85, 0x00, 0, 1, 0, REL1632, NON, NON, "jne"},
	{0x0F, 0x94, 0x00, 0, 0, 0, MRM, NON, NON, "sete"}


};

#endif