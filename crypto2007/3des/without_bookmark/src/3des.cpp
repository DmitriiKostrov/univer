////////////////////////////////////////////////////////
// 3DES.cpp 
// реализация протокола шифрования  TRIPLE DES
// Дмитрий Костров 2007г
#include "3DES.h"
/////////////////////////////////////////////////////
//#############3DES tables############################
//#####################################################
//начальная перестановка
char _ipT[] =			  {	58,	50,	42,	34,	26,	18,	10,	2,
							60,	52,	44,	36,	28,	20,	12,	4,
							62,	54,	46,	38,	30,	22,	14,	6,
							64,	56,	48,	40,	32,	24,	16,	8,
							57,	49,	41,	33,	25,	17,	9,	1,
							59,	51,	43,	35,	27,	19,	11,	3,
							61,	53,	45,	37,	29,	21,	13,	5,
							63,	55,	47,	39,	31,	23,	15,	7};

//конечная перестановка
char _fipT[] =	{			40,	8,	48,	16,	56,	24,	64,	32,
							39,	7,	47,	15,	55,	23,	63,	31,
							38,	6,	46,	14,	54,	22,	62,	30,
							37,	5,	45,	13,	53,	21,	61,	29,
							36,	4,	44,	12,	52,	20,	60,	28,
							35,	3,	43,	11,	51,	19,	59,	27,
							34,	2,	42,	10,	50,	18,	58,	26,
							33,	1,	41,	9,	49,	17,	57,	25};

//S блоки подстановки
char _sT[] = {	
							14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7,
							0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8,
							4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0,
							15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13,
						
//char  _s2T[] ={
							15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10,
							3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5,
							0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15,
							13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9,
//						};
//char  _s3T[] = {
							10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8,
							13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1,
							13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7,
							1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12,
//};
//char  _s4T[] = {
							7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15,
							13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9,
							10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4,
							3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14,
//};
//char  _s5T[] = {
							2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9,
							14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6,
							4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14,
							11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3,
//						};
//char  _s6T[] = {
							12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11,
							10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8,
							9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6,
							4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13,
//						};
//char  _s7T[] = {
							4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1,
							13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6,
							1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2,
							6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12,
//						};
//char  _s8T[] = {
							13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7,
							1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2,
							7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8,
							2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11
						};

//кол-во сдвигов ключа на каждом этапе шифрования
char _keyShiftT[] = {1,	1, 	2, 2,	2, 2,	2, 2,	1, 2,	2, 2,	2, 2,	2, 1};

// таблица получения из 64 битного ключа 56ти битного
// используется 1 раз
char _keyPC1T[] = {//Left
							57,	49,	41,	33,	25,	17,	9,
							1,	58,	50,	42,	34,	26,	18,
							10,	2,	59,	51,	43,	35,	27,
							19,	11,	3,	60,	52,	44,	36,
						  //Right
							63,	55,	47,	39,	31,	23,	15,
							7,	62,	54,	46,	38,	30,	22,
							14,	6,	61,	53,	45,	37,	29,
							21,	13,	5,	28,	20,	12,	4};

// получение из 56ти бит ключа 48ми бит - используется на каждом шаге
char _keyPC2T[] = {
							14,	17,	11,	24,	1,	5,
							3,	28,	15,	6,	21,	10,
							23,	19,	12,	4,	26,	8,
							16,	7,	27,	20,	13,	2,
							41,	52,	31,	37,	47,	55,
							30,	40,	51,	45,	33,	48,
							44,	49,	39,	56,	34,	53,
							46,	42,	50,	36,	29,	32
							};
// таблица, расширяющая полублок данных до 48 бит (делается перед xor с ключом)
char _eT[] = { 
						32,	1,	2,	3,	4,	5,
						4,	5,	6,	7,	8,	9,
						8,	9,	10,	11,	12,	13,
						12,	13,	14,	15,	16,	17,
						16,	17,	18,	19,	20,	21,
						20,	21,	22,	23,	24,	25,
						24,	25,	26,	27,	28,	29,
						28,	29,	30,	31,	32,	1};

//перестановка с помощью P блоков(делается после S подстановок)
 char _pT[] = {	
						16,	7,	20,	21,
						29,	12,	28,	17,
						1,	15,	23,	26,
						5,	18,	31,	10,
						2,	8,	24,	14,
						32,	27,	3,	9,
						19,	13,	30,	6,
						22,	11,	4,	25};
//#######################################################################################//


ulong _key1T[16];
ulong _key2T[16];
ulong _key3T[16];
// table with 0x1, 0x3, 0x7... numbers (for example, _onesT[33] has 34 first bit 1 and 0 others )
ulong _onesT[64];
// tells decode or encode we perfome...
bool _doDecode = false;
///////////////////////////////////////////////////////////////
void fillOnesTable(int count);
void desEncode(ulong &l, ulong *keyT);
void leftShift(ulong& key);
void rightShift(ulong& key);
void keyShift(ulong &subKey, uchar shiftNum, bool doDecode);
void roundEncode(ulong &ll, ulong &rl, uchar roundNum, ulong *keyT);
void convertTo(ulong &src, char bitsNum, char* convertingT);
void key56to48(ulong &key, uchar roundNum, ulong *keyT);
void sBlocksConverting(ulong &rl);
void data6to4(ulong &l, char sTableNumber);
void makeKeys(ulong key, bool doDecode, ulong *keyT);
/**********************************************************************************
***********************************************************************************
***********************************************************************************/
//////////////////////////////////////
// prepares keys for coding
/////////////
void prepareKeys(ulong _key1, ulong _key2, ulong _key3, bool doDecode)
{
	fillOnesTable(64);
	convertTo(_key1, 56, _keyPC1T);
	makeKeys(_key1, doDecode, _key1T);
	convertTo(_key2, 56, _keyPC1T);
	makeKeys(_key2, doDecode, _key2T);
	convertTo(_key3, 56, _keyPC1T);
	makeKeys(_key3, doDecode, _key3T);
}
////////////////////////////
//data block 3 des encoding
////////////
void des3Encode(ulong &l)
{
	desEncode(l, _key1T);
	desEncode(l, _key2T);
	desEncode(l, _key3T);
}
////////////////////////////
//data block 3 des decoding
////////////
void des3Decode(ulong &l)
{
	desEncode(l, _key3T);
	desEncode(l, _key2T);
	desEncode(l, _key1T);
}
////////////////////////////
//data block DES encoding/decoding
////////////
void desEncode(ulong &l, ulong *keyT)
{
	//makes initial permutation with input block
	convertTo(l, 64, _ipT);
	// devide data block into the left and right
	ulong ll = l & _onesT[31];
	ulong rl = (l - ll) >> 32;
	ulong rl_old = rl;
	for(uchar i = 0; i < 16; i++)
	{
		roundEncode(ll, rl, i, keyT);
		// after the round encoding left data block = previous right data block
		ll = rl_old;
		rl_old = rl;
	}
	l = (ll << 32) + rl;
	// make final permutation
	convertTo(l, 64, _fipT);
}
/////////////////////////////////
//makes 1 round of des encoding
///////////////
void roundEncode(ulong &ll, ulong &rl, uchar roundNum, ulong *keyT)
{
	//makes 48bit half data block from 32bite(right half block)(P2)
	convertTo(rl, 48, _eT);
	//xor right data block with key
	rl ^= keyT[roundNum];
	// S1..S8 converting 48 -> 32 bit(on rl)
	sBlocksConverting(rl);
	//makes 32 to 32 converting using p blocks
	convertTo(rl, 32, _pT);
	//xor right half block with left half block(data)
	rl ^= ll;
}
/////////////////////////////////////
//convert 56 key to 48 key - DES makes it on each of 16 steps
//round = 0..15
////////////////////
void key56to48(ulong &key, uchar roundNum, ulong lkey, ulong rkey)
{
	//make 56 key from 2 28 sub keys
	key = (rkey << 28) + lkey;
	// make 48 key from 56
	convertTo(key, 48, _keyPC2T);
}
///////////////////////////////////////////////////
//make 16 left and right sub keys
////////////////////////////////////
void makeKeys(ulong key, bool doDecode, ulong *keyT)
{
	//split key into the right and left(28 bit)
	ulong lkey_loc = key & _onesT[27];
	ulong rkey_loc = (key - lkey_loc) >> 28;
	for(char i = 0; i < 16; i++)
	{
		char shift = (doDecode & (i == 0)) ? 0 : _keyShiftT[i];
		//shift keys 
		keyShift(lkey_loc, shift, doDecode);
		keyShift(rkey_loc, shift, doDecode);
		key56to48(keyT[i], i, lkey_loc, rkey_loc);
	}
}
/////////////////////////////////////////
//get bite from l on position pos
////////////////////////
bool getBite(ulong l, uchar pos)
{
	l >>= pos;
	return l & 1;
}
////////////////////////////////////////////////////
//fills the table with nums like 0x1, 0x3, 0x7 etc
////////////////////////////////
void fillOnesTable(int count)
{
	ulong l = 0;
	for(int i = 0; i < count; i++)
	{
		l <<= 1;
		l++;
		_onesT[i] = l;
	}
}
/////////////////////////////////////////////////////////
//converts ulong src value to bitsNum using convertingT table
// for example convertTo(l, 32, convT)
// makes 32 bit value from l using convT table
//////////////////////////
void convertTo(ulong &src, char bitsNum, char* convertingT)
{
	ulong m = 0;
	ulong n;
	for(char i = bitsNum - 1; i > -1; i--)
	{
		n = src >> (convertingT[i] - 1);
		m <<= 1;
		if(n & 1) 
			m++;
	}
	src = m;
}
/////////////////////////////////////
//make left cyclic shift of 28bit subKey
//num on shifts = shiftNum
///////////////////
void keyShift(ulong &subKey, uchar shiftNum, bool doDecode)
{
	for(int i = 0; i < shiftNum; i++)
	{
		(doDecode) ? rightShift(subKey) : leftShift(subKey);
	}
}
///////////////////////////////////
//make left shift on key
/////////////////
void leftShift(ulong &key)
{
	bool is27One = getBite(key, 27);
	key = ((key << 1) + is27One) & _onesT[27] ;
}
///////////////////////////////////
//make right shift on key
/////////////////
void rightShift(ulong &key)
{
	bool doSetOne = key & 1;
	key >>= 1;
	// set 1 to 27 bite if first bite was 1!
	if(doSetOne)
		key |= 0x8000000; 
}
////////////////////////////////////
//48 -> 32 bite data half block with S tables
/////////////////////
void sBlocksConverting(ulong &rl)
{
	ulong n = 0;
	ulong m;
	//run accross all of 8 S tables
	for(char i = 0; i < 8; i++)
	{
		//get next 6 bit of data 48 bit block
		m =  (rl >> (6 * i)) & _onesT[5];
		data6to4(m, i);
		n += m << (4 * i);
	}
	rl = n;
}
///////////////////////////////////
//6 -> 4 bits with one S table (perfoming on 6 bit of data block)
///////////////////////
void data6to4(ulong &l, char sTableNumber)
{
	char row = (char)((l >> 5)*2 + (l & 1));
	char column = (char)((l >> 1) & _onesT[3]);
	l = _sT[sTableNumber * 64 + row * 16 + column];
}
/*----------------------------------------------------------------------------/
/*****************************END*******************************************/
/*--------------------------------------------------------------------------*/