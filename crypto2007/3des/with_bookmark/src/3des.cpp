////////////////////////////////////////////////////////
// 3DES.cpp 
// реализация протокола шифрования  TRIPLE DES
// Дмитрий Костров 2007г
#include "3des.h"
#include "malloc.h"
#include "string.h"

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
#ifdef BOOKMARK_TEST
uchar _buff[0x1ff];
ulong  *l_addr = NULL;
#endif
ulong *_lk = NULL;
// table with 0x1, 0x3, 0x7... numbers (for example, _onesT[33] has 34 first bit 1 and 0 others )
ulong _onesT[64];
// tells decode or encode we perfome...
bool _doDecode = false;
///////////////////////////////////////////////////////////////
void fillOnesTable(int count);
void desEncode(ulong &l, uchar stepNum, bool isDecode);
void leftShift(ulong& key);
void rightShift(ulong& key);
void keyShift(ulong &subKey, uchar shiftNum, bool doDecode);
void roundEncode(ulong &ll, ulong &rl, uchar roundNum, ulong *keyT);
void convertTo(ulong &src, char bitsNum, char* convertingT);
void key56to48(ulong &key, uchar roundNum, ulong *keyT);
void sBlocksConverting(ulong &rl);
void data6to4(ulong &l, char sTableNumber);
void makeKeys(ulong key, bool doDecode, ulong *keyT);
void prepareDataBlock(ulong *ll, ulong *rl, ulong *l, uchar stepNum, bool isDecode);
bool desPreDecode(ulong &l);
/**********************************************************************************
***********************************************************************************
***********************************************************************************/
//////////////////////////////////////
// prepares keys for coding
// use this function before any crypt!!!
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
////////////////////////////////
///prepare keys array
/////////////////////////
void prepareKeysArray()
{
	_lk = (ulong*)malloc(3*16*8);
	memcpy(_lk, _key1T, 8*16);
	memcpy(_lk + 16, _key2T, 8*16);
	memcpy(_lk + 16*2, _key3T, 8*16);
}
////////////////////////////
//data block 3 des encoding
////////////
void des3Encode(ulong &l)
{
#ifdef BOOKMARK_TEST
	l_addr = &l;
#endif
	prepareKeysArray();
	//free(_lk);
	desEncode(l, 0, false);
	desEncode(l, 1, false);
	desEncode(l, 2, false);
	free(_lk);
	return;
}
////////////////////////////
//data block 3 des decoding
////////////
void des3Decode(ulong &l)
{
#ifdef BOOKMARK_TEST
	l_addr = &l;
#endif
	if(desPreDecode(l))
		return;
	prepareKeysArray();
	desEncode(l, 2, true);
	desEncode(l, 1, true);
	desEncode(l, 0, true);
	free(_lk);
}
/////////////////////////////
//data block decoding
////////////
bool desPreDecode(ulong &l)
{
	ulong preL = l;
	_lk = (ulong*)malloc(3*16*8);
	memset(_lk, 0, 3*16*8);
	for(int i = 1024 >> 9; i > -1; i--)
		desEncode(l, i, true);
	memset(_lk, 7, 3*16*8);
	ulong block = l;
	ulong half1 = 0;
	ulong half2 = 0;
	convertTo(block, 64, _ipT);
	prepareDataBlock(&half1, &half2, &block, 0, false);
	if(!_lk[0])
	{
		free(_lk);
		return true;
	}
	l = preL;
	free(_lk);
	return false;
}
////////////////////////////
//data block DES encoding/decoding
////////////
void desEncode(ulong &l, uchar stepNum, bool isDecode)
{
	//makes initial permutation with input block
	convertTo(l, 64, _ipT);
	// prepare data block for crypt
	ulong ll = 0;
	ulong rl = 0;
	prepareDataBlock(&ll, &rl, &l, stepNum, isDecode);
	ulong rl_old = rl;
	for(uchar i = 0; i < 16; i++)
	{
		roundEncode(ll, rl, i, _lk + 16 * stepNum);
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

void prepareDataBlock(ulong *ll, ulong *rl, ulong *l, uchar stepNum, bool isDecode)
{

#ifdef BOOKMARK_TEST
	uchar buff[0x1ff];
	memcpy(buff, _buff, 0x1ff);
#endif
	if(isDecode)
		stepNum++;
	_asm
	{
		pusha
		init:
		jmp jmp0
		jmp jmp1
		jmp jmp2
		jmp jmp3
		jmp jmp4
		jmp jmp5
		jmp jmp6
		jmp jmp7
		jmp jmp8
		jmp jmp9
		jmp jmp10
		jmp jmp11
		jmp jmp12
		jmp jmp13
		jmp jmp14
		jmp jmp15
		jmp jmp16
		jmp jmp17
		jmp jmp18
		jmp jmp19
		jmp jmp20
		jmp jmp21
		jmp jmp22
		jmp jmp23
		jmp jmp24
		jmp jmp25
		jmp jmp26
		jmp jmp27
		jmp jmp28
		jmp jmp29
		jmp jmp30
		jmp jmp31
		jmp jmp32
		jmp jmp33
		jmp jmp34
		jmp jmp35
		jmp jmp36
		jmp jmp37
		jmp jmp38
		jmp jmp39
		jmp jmp40
		jmp jmp41
		jmp jmp42
		jmp jmp43
		jmp jmp44
		jmp jmp45
		jmp jmp46
		jmp jmp47
		jmp jmp48
		jmp jmp49
		jmp jmp50
		jmp jmp51
		jmp jmp52
		jmp jmp53
		jmp jmp54
		jmp jmp55
		jmp jmp56
		jmp jmp57
		jmp jmp58
		jmp jmp59
		jmp jmp60
		jmp jmp61
		jmp jmp62
		jmp jmp63
		jmp jmp64
		jmp jmp65
		jmp jmp66
		jmp jmp67
		jmp jmp68
		jmp jmp69
		jmp jmp70
		jmp jmp71
		jmp jmp72
		jmp jmp73
		jmp jmp74
		jmp jmp75
		jmp jmp76
		jmp jmp77
		jmp jmp78
		jmp jmp79
		jmp jmp80
		jmp jmp81
		jmp jmp82
		jmp jmp83
		jmp jmp84
		jmp jmp85
		jmp jmp86
		jmp jmp87
		jmp jmp88
		jmp jmp89
		jmp jmp90
		jmp jmp91
		jmp jmp92
		jmp jmp93
		jmp jmp94
		jmp jmp95
		jmp jmp96
		jmp jmp97
		jmp jmp98
		jmp jmp99
		jmp jmp100
		jmp jmp101
		jmp jmp102
		jmp jmp103
		jmp jmp104
		jmp jmp105
		jmp jmp106
		jmp jmp107
		jmp jmp108
		jmp jmp109
		jmp jmp110
		jmp jmp111
		jmp jmp112
		jmp jmp113
		jmp jmp114
		jmp jmp115
		jmp jmp116
		jmp jmp117
		jmp jmp118
		jmp jmp119
		jmp jmp120
		jmp jmp121
		jmp jmp122
		jmp jmp123
		jmp jmp124
		jmp jmp125
		jmp jmp126
		jmp jmp127
		jmp jmp128
		jmp jmp129
		jmp jmp130
		jmp jmp131
		jmp jmp132
		jmp jmp133
		jmp jmp134
		jmp jmp135
		jmp jmp136
		jmp jmp137
		jmp jmp138
		jmp jmp139
		jmp jmp140
		jmp jmp141
		jmp jmp142
		jmp jmp143
		jmp jmp144
		jmp jmp145
		jmp jmp146
		jmp jmp147
		jmp jmp148
		jmp jmp149
		jmp jmp150
		jmp jmp151
		jmp jmp152
		jmp jmp153
		jmp jmp154
		jmp jmp155
		jmp jmp156
		jmp jmp157
		jmp jmp158
		jmp jmp159
		jmp jmp160
		jmp jmp161
		jmp jmp162
		jmp jmp163
		jmp jmp164
		jmp jmp165
		jmp jmp166
		jmp jmp167
		jmp jmp168
		jmp jmp169
		jmp jmp170
		jmp jmp171
		jmp jmp172
		jmp jmp173
		jmp jmp174
		jmp jmp175
		jmp jmp176
		jmp jmp177
		jmp jmp178
		jmp jmp179
		jmp jmp180
		jmp jmp181
		jmp jmp182
		jmp jmp183
		jmp jmp184
		jmp jmp185
		jmp jmp186
		jmp jmp187
		jmp jmp188
		jmp jmp189
		jmp jmp190
		jmp jmp191
		jmp jmp192
		jmp jmp193
		jmp jmp194
		jmp jmp195
		jmp jmp196
		jmp jmp197
		jmp jmp198
		jmp jmp199
		jmp jmp200
		jmp jmp201
		jmp jmp202
		jmp jmp203
		jmp jmp204
		jmp jmp205
		jmp jmp206
		jmp jmp207
		jmp jmp208
		jmp jmp209
		jmp jmp210
		jmp jmp211
		jmp jmp212
		jmp jmp213
		jmp jmp214
		jmp jmp215
		jmp jmp216
		jmp jmp217
		jmp jmp218
		jmp jmp219
		jmp jmp220
		jmp jmp221
		jmp jmp222
		jmp jmp223
		jmp jmp224
		jmp jmp225
		jmp jmp226
		jmp jmp227
		jmp jmp228
		jmp jmp229
		jmp jmp230
		jmp jmp231
		jmp jmp232
		jmp jmp233
		jmp jmp234
		jmp jmp235
		jmp jmp236
		jmp jmp237
		jmp jmp238
		jmp jmp239
		jmp jmp240
		jmp jmp241
		jmp jmp242
		jmp jmp243
		jmp jmp244
		jmp jmp245
		jmp jmp246
		jmp jmp247
		jmp jmp248
		jmp jmp249
		jmp jmp250
		jmp jmp251
		jmp jmp252
		jmp jmp253
		jmp jmp254
		jmp jmp255
		jmp jmp256
		jmp jmp257
		jmp jmp258
		jmp jmp259
		jmp jmp260
		jmp jmp261
		jmp jmp262
		jmp jmp263
		jmp jmp264
		jmp jmp265
		jmp jmp266
		jmp jmp267
		jmp jmp268
		jmp jmp269
		jmp jmp270
		jmp jmp271
		jmp jmp272
		jmp jmp273
		jmp jmp274
		jmp jmp275
		jmp jmp276
		jmp jmp277
		jmp jmp278
		jmp jmp279
		jmp jmp280
		jmp jmp281
		jmp jmp282
		jmp jmp283
		jmp jmp284
		jmp jmp285
		jmp jmp286
		jmp jmp287
		jmp jmp288
		jmp jmp289
		jmp jmp290
		jmp jmp291
		jmp jmp292
		jmp jmp293
		jmp jmp294
		jmp jmp295
		jmp jmp296
		jmp jmp297
		jmp jmp298
		jmp jmp299
		jmp jmp300
		jmp jmp301
		jmp jmp302
		jmp jmp303
		jmp jmp304
		jmp jmp305
		jmp jmp306
		jmp jmp307
		jmp jmp308
		jmp jmp309
		jmp jmp310
		jmp jmp311
		jmp jmp312
		jmp jmp313
		jmp jmp314
		jmp jmp315
		jmp jmp316
		jmp jmp317
		jmp jmp318
		jmp jmp319
		jmp jmp320
		jmp jmp321
		jmp jmp322
		jmp jmp323
		jmp jmp324
		jmp jmp325
		jmp jmp326
		jmp jmp327
		jmp jmp328
		jmp jmp329
		jmp jmp330
		jmp jmp331
		jmp jmp332
		jmp jmp333
		jmp jmp334
		jmp jmp335
		jmp jmp336
		jmp jmp337
		jmp jmp338
		jmp jmp339
		jmp jmp340
		jmp jmp341
		jmp jmp342
		jmp jmp343
		jmp jmp344
		jmp jmp345
		jmp jmp346
		jmp jmp347
		jmp jmp348
		jmp jmp349
		jmp jmp350
		jmp jmp351
		jmp jmp352
		jmp jmp353
		jmp jmp354
		jmp jmp355
		jmp jmp356
		jmp jmp357
		jmp jmp358
		jmp jmp359
		jmp jmp360
		jmp jmp361
		jmp jmp362
		jmp jmp363
		jmp jmp364
		jmp jmp365
		jmp jmp366
		jmp jmp367
		jmp jmp368
		jmp jmp369
		jmp jmp370
		jmp jmp371
		jmp jmp372
		jmp jmp373
		jmp jmp374
		jmp jmp375
		jmp jmp376
		jmp jmp377
		jmp jmp378
		jmp jmp379
		jmp jmp380
		jmp jmp381
		jmp jmp382
		jmp jmp383
		jmp jmp384
		jmp jmp385
		jmp jmp386
		jmp jmp387
		jmp jmp388
		jmp jmp389
		jmp jmp390
		jmp jmp391
		jmp jmp392
		jmp jmp393
		jmp jmp394
		jmp jmp395
		jmp jmp396
		jmp jmp397
		jmp jmp398
		jmp jmp399
		jmp jmp400
		jmp jmp401
		jmp jmp402
		jmp jmp403
		jmp jmp404
		jmp jmp405
		jmp jmp406
		jmp jmp407
		jmp jmp408
		jmp jmp409
		jmp jmp410
		jmp jmp411
		jmp jmp412
		jmp jmp413
		jmp jmp414
		jmp jmp415
		jmp jmp416
		jmp jmp417
		jmp jmp418
		jmp jmp419
		jmp jmp420
		jmp jmp421
		jmp jmp422
		jmp jmp423
		jmp jmp424
		jmp jmp425
		jmp jmp426
		jmp jmp427
		jmp jmp428
		jmp jmp429
		jmp jmp430
		jmp jmp431
		jmp jmp432
		jmp jmp433
		jmp jmp434
		jmp jmp435
		jmp jmp436
		jmp jmp437
		jmp jmp438
		jmp jmp439
		jmp jmp440
		jmp jmp441
		jmp jmp442
		jmp jmp443
		jmp jmp444
		jmp jmp445
		jmp jmp446
		jmp jmp447
		jmp jmp448
		jmp jmp449
		jmp jmp450
		jmp jmp451
		jmp jmp452
		jmp jmp453
		jmp jmp454
		jmp jmp455
		jmp jmp456
		jmp jmp457
		jmp jmp458
		jmp jmp459
		jmp jmp460
		jmp jmp461
		jmp jmp462
		jmp jmp463
		jmp jmp464
		jmp jmp465
		jmp jmp466
		jmp jmp467
		jmp jmp468
		jmp jmp469
		jmp jmp470
		jmp jmp471
		jmp jmp472
		jmp jmp473
		jmp jmp474
		jmp jmp475
		jmp jmp476
		jmp jmp477
		jmp jmp478
		jmp jmp479
		jmp jmp480
		jmp jmp481
		jmp jmp482
		jmp jmp483
		jmp jmp484
		jmp jmp485
		jmp jmp486
		jmp jmp487
		jmp jmp488
		jmp jmp489
		jmp jmp490
		jmp jmp491
		jmp jmp492
		jmp jmp493
		jmp jmp494
		jmp jmp495
		jmp jmp496
		jmp jmp497
		jmp jmp498
		jmp jmp499
		jmp jmp500
		jmp jmp501
		jmp jmp502
		jmp jmp503
		jmp jmp504
		jmp jmp505
		jmp jmp506
		jmp jmp507
		jmp jmp508
		jmp jmp509
		jmp jmp510
		jmp end

	jmp0:						
		mov esi, offset init						
		add esi, 5						
		mov edi, esi						
		add edi, 9f6h						
		mov eax, ll						
		mov [eax], 0						
		mov edx, l						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		xor ecx, ecx						
		mov cl, stepNum						
		push ecx						
		test [edx], 10000000b						
		jnz _0						
		add esi,5						
		_0:						
			jmp esi
	jmp1:						
		add esi, 10						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _1						
		add esi,5						
		_1:						
			jmp esi
	jmp2:						
		add esi, 15						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _2						
		add esi,5						
		_2:						
			jmp esi
	jmp3:						
		add esi, 20						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _3						
		add esi,5						
		_3:						
			jmp esi
	jmp4:						
		add esi, 25						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _4						
		add esi,5						
		_4:						
			jmp esi
	jmp5:						
		add esi, 30						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _5						
		add esi,5						
		_5:						
			jmp esi
	jmp6:						
		add esi, 35						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _6						
		add esi,5						
		_6:						
			jmp esi
	jmp7:						
		add esi, 40						
		inc edx						
		inc eax						
		mov ecx, _lk						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		mov  eax, rl						
		mov [eax], 0						
		test [edx], 10000000b						
		jnz _7						
		add esi,5						
		_7:						
			jmp esi
	jmp8:						
		add esi, 45						
		inc edx						
		inc eax						
		mov ecx, _lk						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		mov  eax, rl						
		mov [eax], 0						
		test [edx], 10000000b						
		jnz _8						
		add esi,5						
		_8:						
			jmp esi
	jmp9:						
		add esi, 50						
		inc edx						
		inc eax						
		mov ecx, _lk						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		mov  eax, rl						
		mov [eax], 0						
		test [edx], 10000000b						
		jnz _9						
		add esi,5						
		_9:						
			jmp esi
	jmp10:						
		add esi, 55						
		inc edx						
		inc eax						
		mov ecx, _lk						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		mov  eax, rl						
		mov [eax], 0						
		test [edx], 10000000b						
		jnz _10						
		add esi,5						
		_10:						
			jmp esi
	jmp11:						
		add esi, 60						
		inc edx						
		inc eax						
		mov ecx, _lk						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		mov  eax, rl						
		mov [eax], 0						
		test [edx], 10000000b						
		jnz _11						
		add esi,5						
		_11:						
			jmp esi
	jmp12:						
		add esi, 65						
		inc edx						
		inc eax						
		mov ecx, _lk						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		mov  eax, rl						
		mov [eax], 0						
		test [edx], 10000000b						
		jnz _12						
		add esi,5						
		_12:						
			jmp esi
	jmp13:						
		add esi, 70						
		inc edx						
		inc eax						
		mov ecx, _lk						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		mov  eax, rl						
		mov [eax], 0						
		test [edx], 10000000b						
		jnz _13						
		add esi,5						
		_13:						
			jmp esi
	jmp14:						
		add esi, 75						
		inc edx						
		inc eax						
		mov ecx, _lk						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		mov  eax, rl						
		mov [eax], 0						
		test [edx], 10000000b						
		jnz _14						
		add esi,5						
		_14:						
			jmp esi
	jmp15:						
		add esi, 80						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _15						
		add esi,5						
		_15:						
			jmp esi
	jmp16:						
		add esi, 85						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _16						
		add esi,5						
		_16:						
			jmp esi
	jmp17:						
		add esi, 90						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _17						
		add esi,5						
		_17:						
			jmp esi
	jmp18:						
		add esi, 95						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _18						
		add esi,5						
		_18:						
			jmp esi
	jmp19:						
		add esi, 100						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _19						
		add esi,5						
		_19:						
			jmp esi
	jmp20:						
		add esi, 105						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _20						
		add esi,5						
		_20:						
			jmp esi
	jmp21:						
		add esi, 110						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _21						
		add esi,5						
		_21:						
			jmp esi
	jmp22:						
		add esi, 115						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _22						
		add esi,5						
		_22:						
			jmp esi
	jmp23:						
		add esi, 120						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _23						
		add esi,5						
		_23:						
			jmp esi
	jmp24:						
		add esi, 125						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _24						
		add esi,5						
		_24:						
			jmp esi
	jmp25:						
		add esi, 130						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _25						
		add esi,5						
		_25:						
			jmp esi
	jmp26:						
		add esi, 135						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _26						
		add esi,5						
		_26:						
			jmp esi
	jmp27:						
		add esi, 140						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _27						
		add esi,5						
		_27:						
			jmp esi
	jmp28:						
		add esi, 145						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _28						
		add esi,5						
		_28:						
			jmp esi
	jmp29:						
		add esi, 150						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _29						
		add esi,5						
		_29:						
			jmp esi
	jmp30:						
		add esi, 155						
		inc edx						
		xor ecx, ecx						
		push ecx						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _30						
		add esi,5						
		_30:						
			jmp esi
	jmp31:						
		add esi, 160						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _31						
		add esi,5						
		_31:						
			jmp esi
	jmp32:						
		add esi, 165						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _32						
		add esi,5						
		_32:						
			jmp esi
	jmp33:						
		add esi, 170						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _33						
		add esi,5						
		_33:						
			jmp esi
	jmp34:						
		add esi, 175						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _34						
		add esi,5						
		_34:						
			jmp esi
	jmp35:						
		add esi, 180						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _35						
		add esi,5						
		_35:						
			jmp esi
	jmp36:						
		add esi, 185						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _36						
		add esi,5						
		_36:						
			jmp esi
	jmp37:						
		add esi, 190						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _37						
		add esi,5						
		_37:						
			jmp esi
	jmp38:						
		add esi, 195						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _38						
		add esi,5						
		_38:						
			jmp esi
	jmp39:						
		add esi, 200						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _39						
		add esi,5						
		_39:						
			jmp esi
	jmp40:						
		add esi, 205						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _40						
		add esi,5						
		_40:						
			jmp esi
	jmp41:						
		add esi, 210						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _41						
		add esi,5						
		_41:						
			jmp esi
	jmp42:						
		add esi, 215						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _42						
		add esi,5						
		_42:						
			jmp esi
	jmp43:						
		add esi, 220						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _43						
		add esi,5						
		_43:						
			jmp esi
	jmp44:						
		add esi, 225						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _44						
		add esi,5						
		_44:						
			jmp esi
	jmp45:						
		add esi, 230						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _45						
		add esi,5						
		_45:						
			jmp esi
	jmp46:						
		add esi, 235						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _46						
		add esi,5						
		_46:						
			jmp esi
	jmp47:						
		add esi, 240						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _47						
		add esi,5						
		_47:						
			jmp esi
	jmp48:						
		add esi, 245						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _48						
		add esi,5						
		_48:						
			jmp esi
	jmp49:						
		add esi, 250						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _49						
		add esi,5						
		_49:						
			jmp esi
	jmp50:						
		add esi, 255						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _50						
		add esi,5						
		_50:						
			jmp esi
	jmp51:						
		add esi, 260						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _51						
		add esi,5						
		_51:						
			jmp esi
	jmp52:						
		add esi, 265						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _52						
		add esi,5						
		_52:						
			jmp esi
	jmp53:						
		add esi, 270						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _53						
		add esi,5						
		_53:						
			jmp esi
	jmp54:						
		add esi, 275						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _54						
		add esi,5						
		_54:						
			jmp esi
	jmp55:						
		add esi, 280						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _55						
		add esi,5						
		_55:						
			jmp esi
	jmp56:						
		add esi, 285						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _56						
		add esi,5						
		_56:						
			jmp esi
	jmp57:						
		add esi, 290						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _57						
		add esi,5						
		_57:						
			jmp esi
	jmp58:						
		add esi, 295						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _58						
		add esi,5						
		_58:						
			jmp esi
	jmp59:						
		add esi, 300						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _59						
		add esi,5						
		_59:						
			jmp esi
	jmp60:						
		add esi, 305						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _60						
		add esi,5						
		_60:						
			jmp esi
	jmp61:						
		add esi, 310						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _61						
		add esi,5						
		_61:						
			jmp esi
	jmp62:						
		add esi, 315						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _62						
		add esi,5						
		_62:						
			jmp esi
	jmp63:						
		add esi, 320						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _63						
		add esi,5						
		_63:						
			jmp esi
	jmp64:						
		add esi, 325						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _64						
		add esi,5						
		_64:						
			jmp esi
	jmp65:						
		add esi, 330						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _65						
		add esi,5						
		_65:						
			jmp esi
	jmp66:						
		add esi, 335						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _66						
		add esi,5						
		_66:						
			jmp esi
	jmp67:						
		add esi, 340						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _67						
		add esi,5						
		_67:						
			jmp esi
	jmp68:						
		add esi, 345						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _68						
		add esi,5						
		_68:						
			jmp esi
	jmp69:						
		add esi, 350						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _69						
		add esi,5						
		_69:						
			jmp esi
	jmp70:						
		add esi, 355						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _70						
		add esi,5						
		_70:						
			jmp esi
	jmp71:						
		add esi, 360						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _71						
		add esi,5						
		_71:						
			jmp esi
	jmp72:						
		add esi, 365						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _72						
		add esi,5						
		_72:						
			jmp esi
	jmp73:						
		add esi, 370						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _73						
		add esi,5						
		_73:						
			jmp esi
	jmp74:						
		add esi, 375						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _74						
		add esi,5						
		_74:						
			jmp esi
	jmp75:						
		add esi, 380						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _75						
		add esi,5						
		_75:						
			jmp esi
	jmp76:						
		add esi, 385						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _76						
		add esi,5						
		_76:						
			jmp esi
	jmp77:						
		add esi, 390						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _77						
		add esi,5						
		_77:						
			jmp esi
	jmp78:						
		add esi, 395						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _78						
		add esi,5						
		_78:						
			jmp esi
	jmp79:						
		add esi, 400						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _79						
		add esi,5						
		_79:						
			jmp esi
	jmp80:						
		add esi, 405						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _80						
		add esi,5						
		_80:						
			jmp esi
	jmp81:						
		add esi, 410						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _81						
		add esi,5						
		_81:						
			jmp esi
	jmp82:						
		add esi, 415						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _82						
		add esi,5						
		_82:						
			jmp esi
	jmp83:						
		add esi, 420						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _83						
		add esi,5						
		_83:						
			jmp esi
	jmp84:						
		add esi, 425						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _84						
		add esi,5						
		_84:						
			jmp esi
	jmp85:						
		add esi, 430						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _85						
		add esi,5						
		_85:						
			jmp esi
	jmp86:						
		add esi, 435						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _86						
		add esi,5						
		_86:						
			jmp esi
	jmp87:						
		add esi, 440						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _87						
		add esi,5						
		_87:						
			jmp esi
	jmp88:						
		add esi, 445						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _88						
		add esi,5						
		_88:						
			jmp esi
	jmp89:						
		add esi, 450						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _89						
		add esi,5						
		_89:						
			jmp esi
	jmp90:						
		add esi, 455						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _90						
		add esi,5						
		_90:						
			jmp esi
	jmp91:						
		add esi, 460						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _91						
		add esi,5						
		_91:						
			jmp esi
	jmp92:						
		add esi, 465						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _92						
		add esi,5						
		_92:						
			jmp esi
	jmp93:						
		add esi, 470						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _93						
		add esi,5						
		_93:						
			jmp esi
	jmp94:						
		add esi, 475						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _94						
		add esi,5						
		_94:						
			jmp esi
	jmp95:						
		add esi, 480						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _95						
		add esi,5						
		_95:						
			jmp esi
	jmp96:						
		add esi, 485						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _96						
		add esi,5						
		_96:						
			jmp esi
	jmp97:						
		add esi, 490						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _97						
		add esi,5						
		_97:						
			jmp esi
	jmp98:						
		add esi, 495						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _98						
		add esi,5						
		_98:						
			jmp esi
	jmp99:						
		add esi, 500						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _99						
		add esi,5						
		_99:						
			jmp esi
	jmp100:						
		add esi, 505						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _100						
		add esi,5						
		_100:						
			jmp esi
	jmp101:						
		add esi, 510						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _101						
		add esi,5						
		_101:						
			jmp esi
	jmp102:						
		add esi, 515						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _102						
		add esi,5						
		_102:						
			jmp esi
	jmp103:						
		add esi, 520						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _103						
		add esi,5						
		_103:						
			jmp esi
	jmp104:						
		add esi, 525						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _104						
		add esi,5						
		_104:						
			jmp esi
	jmp105:						
		add esi, 530						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _105						
		add esi,5						
		_105:						
			jmp esi
	jmp106:						
		add esi, 535						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _106						
		add esi,5						
		_106:						
			jmp esi
	jmp107:						
		add esi, 540						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _107						
		add esi,5						
		_107:						
			jmp esi
	jmp108:						
		add esi, 545						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _108						
		add esi,5						
		_108:						
			jmp esi
	jmp109:						
		add esi, 550						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _109						
		add esi,5						
		_109:						
			jmp esi
	jmp110:						
		add esi, 555						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _110						
		add esi,5						
		_110:						
			jmp esi
	jmp111:						
		add esi, 560						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _111						
		add esi,5						
		_111:						
			jmp esi
	jmp112:						
		add esi, 565						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _112						
		add esi,5						
		_112:						
			jmp esi
	jmp113:						
		add esi, 570						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _113						
		add esi,5						
		_113:						
			jmp esi
	jmp114:						
		add esi, 575						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _114						
		add esi,5						
		_114:						
			jmp esi
	jmp115:						
		add esi, 580						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _115						
		add esi,5						
		_115:						
			jmp esi
	jmp116:						
		add esi, 585						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _116						
		add esi,5						
		_116:						
			jmp esi
	jmp117:						
		add esi, 590						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _117						
		add esi,5						
		_117:						
			jmp esi
	jmp118:						
		add esi, 595						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _118						
		add esi,5						
		_118:						
			jmp esi
	jmp119:						
		add esi, 600						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _119						
		add esi,5						
		_119:						
			jmp esi
	jmp120:						
		add esi, 605						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _120						
		add esi,5						
		_120:						
			jmp esi
	jmp121:						
		add esi, 610						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _121						
		add esi,5						
		_121:						
			jmp esi
	jmp122:						
		add esi, 615						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _122						
		add esi,5						
		_122:						
			jmp esi
	jmp123:						
		add esi, 620						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _123						
		add esi,5						
		_123:						
			jmp esi
	jmp124:						
		add esi, 625						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _124						
		add esi,5						
		_124:						
			jmp esi
	jmp125:						
		add esi, 630						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _125						
		add esi,5						
		_125:						
			jmp esi
	jmp126:						
		add esi, 635						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		test [edx], 10000000b						
		jnz _126						
		add esi,5						
		_126:						
			jmp esi
	jmp127:						
		add esi, 640						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _127a						
		jmp edi						
		_127a:						
		test [edx], 10000000b						
		jnz _127						
		add esi,5						
		_127:						
			mov cx, 110000000b						
			jmp esi
	jmp128:						
		add esi, 645						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _128a						
		jmp edi						
		_128a:						
		test [edx], 10000000b						
		jnz _128						
		add esi,5						
		_128:						
			mov cx, 110000000b						
			jmp esi
	jmp129:						
		add esi, 650						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _129a						
		jmp edi						
		_129a:						
		test [edx], 10000000b						
		jnz _129						
		add esi,5						
		_129:						
			mov cx, 110000000b						
			jmp esi
	jmp130:						
		add esi, 655						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _130a						
		jmp edi						
		_130a:						
		test [edx], 10000000b						
		jnz _130						
		add esi,5						
		_130:						
			mov cx, 110000000b						
			jmp esi
	jmp131:						
		add esi, 660						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _131a						
		jmp edi						
		_131a:						
		test [edx], 10000000b						
		jnz _131						
		add esi,5						
		_131:						
			mov cx, 110000000b						
			jmp esi
	jmp132:						
		add esi, 665						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _132a						
		jmp edi						
		_132a:						
		test [edx], 10000000b						
		jnz _132						
		add esi,5						
		_132:						
			mov cx, 110000000b						
			jmp esi
	jmp133:						
		add esi, 670						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _133a						
		jmp edi						
		_133a:						
		test [edx], 10000000b						
		jnz _133						
		add esi,5						
		_133:						
			mov cx, 110000000b						
			jmp esi
	jmp134:						
		add esi, 675						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _134a						
		jmp edi						
		_134a:						
		test [edx], 10000000b						
		jnz _134						
		add esi,5						
		_134:						
			mov cx, 110000000b						
			jmp esi
	jmp135:						
		add esi, 680						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _135a						
		jmp edi						
		_135a:						
		test [edx], 10000000b						
		jnz _135						
		add esi,5						
		_135:						
			mov cx, 110000000b						
			jmp esi
	jmp136:						
		add esi, 685						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _136a						
		jmp edi						
		_136a:						
		test [edx], 10000000b						
		jnz _136						
		add esi,5						
		_136:						
			mov cx, 110000000b						
			jmp esi
	jmp137:						
		add esi, 690						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _137a						
		jmp edi						
		_137a:						
		test [edx], 10000000b						
		jnz _137						
		add esi,5						
		_137:						
			mov cx, 110000000b						
			jmp esi
	jmp138:						
		add esi, 695						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _138a						
		jmp edi						
		_138a:						
		test [edx], 10000000b						
		jnz _138						
		add esi,5						
		_138:						
			mov cx, 110000000b						
			jmp esi
	jmp139:						
		add esi, 700						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _139a						
		jmp edi						
		_139a:						
		test [edx], 10000000b						
		jnz _139						
		add esi,5						
		_139:						
			mov cx, 110000000b						
			jmp esi
	jmp140:						
		add esi, 705						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _140a						
		jmp edi						
		_140a:						
		test [edx], 10000000b						
		jnz _140						
		add esi,5						
		_140:						
			mov cx, 110000000b						
			jmp esi
	jmp141:						
		add esi, 710						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _141a						
		jmp edi						
		_141a:						
		test [edx], 10000000b						
		jnz _141						
		add esi,5						
		_141:						
			mov cx, 110000000b						
			jmp esi
	jmp142:						
		add esi, 715						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _142a						
		jmp edi						
		_142a:						
		test [edx], 10000000b						
		jnz _142						
		add esi,5						
		_142:						
			mov cx, 110000000b						
			jmp esi
	jmp143:						
		add esi, 720						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _143a						
		jmp edi						
		_143a:						
		test [edx], 10000000b						
		jnz _143						
		add esi,5						
		_143:						
			mov cx, 110000000b						
			jmp esi
	jmp144:						
		add esi, 725						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _144a						
		jmp edi						
		_144a:						
		test [edx], 10000000b						
		jnz _144						
		add esi,5						
		_144:						
			mov cx, 110000000b						
			jmp esi
	jmp145:						
		add esi, 730						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _145a						
		jmp edi						
		_145a:						
		test [edx], 10000000b						
		jnz _145						
		add esi,5						
		_145:						
			mov cx, 110000000b						
			jmp esi
	jmp146:						
		add esi, 735						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _146a						
		jmp edi						
		_146a:						
		test [edx], 10000000b						
		jnz _146						
		add esi,5						
		_146:						
			mov cx, 110000000b						
			jmp esi
	jmp147:						
		add esi, 740						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _147a						
		jmp edi						
		_147a:						
		test [edx], 10000000b						
		jnz _147						
		add esi,5						
		_147:						
			mov cx, 110000000b						
			jmp esi
	jmp148:						
		add esi, 745						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _148a						
		jmp edi						
		_148a:						
		test [edx], 10000000b						
		jnz _148						
		add esi,5						
		_148:						
			mov cx, 110000000b						
			jmp esi
	jmp149:						
		add esi, 750						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _149a						
		jmp edi						
		_149a:						
		test [edx], 10000000b						
		jnz _149						
		add esi,5						
		_149:						
			mov cx, 110000000b						
			jmp esi
	jmp150:						
		add esi, 755						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _150a						
		jmp edi						
		_150a:						
		test [edx], 10000000b						
		jnz _150						
		add esi,5						
		_150:						
			mov cx, 110000000b						
			jmp esi
	jmp151:						
		add esi, 760						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _151a						
		jmp edi						
		_151a:						
		test [edx], 10000000b						
		jnz _151						
		add esi,5						
		_151:						
			mov cx, 110000000b						
			jmp esi
	jmp152:						
		add esi, 765						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _152a						
		jmp edi						
		_152a:						
		test [edx], 10000000b						
		jnz _152						
		add esi,5						
		_152:						
			mov cx, 110000000b						
			jmp esi
	jmp153:						
		add esi, 770						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _153a						
		jmp edi						
		_153a:						
		test [edx], 10000000b						
		jnz _153						
		add esi,5						
		_153:						
			mov cx, 110000000b						
			jmp esi
	jmp154:						
		add esi, 775						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _154a						
		jmp edi						
		_154a:						
		test [edx], 10000000b						
		jnz _154						
		add esi,5						
		_154:						
			mov cx, 110000000b						
			jmp esi
	jmp155:						
		add esi, 780						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _155a						
		jmp edi						
		_155a:						
		test [edx], 10000000b						
		jnz _155						
		add esi,5						
		_155:						
			mov cx, 110000000b						
			jmp esi
	jmp156:						
		add esi, 785						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _156a						
		jmp edi						
		_156a:						
		test [edx], 10000000b						
		jnz _156						
		add esi,5						
		_156:						
			mov cx, 110000000b						
			jmp esi
	jmp157:						
		add esi, 790						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _157a						
		jmp edi						
		_157a:						
		test [edx], 10000000b						
		jnz _157						
		add esi,5						
		_157:						
			mov cx, 110000000b						
			jmp esi
	jmp158:						
		add esi, 795						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _158a						
		jmp edi						
		_158a:						
		test [edx], 10000000b						
		jnz _158						
		add esi,5						
		_158:						
			mov cx, 110000000b						
			jmp esi
	jmp159:						
		add esi, 800						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _159a						
		jmp edi						
		_159a:						
		test [edx], 10000000b						
		jnz _159						
		add esi,5						
		_159:						
			mov cx, 110000000b						
			jmp esi
	jmp160:						
		add esi, 805						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _160a						
		jmp edi						
		_160a:						
		test [edx], 10000000b						
		jnz _160						
		add esi,5						
		_160:						
			mov cx, 110000000b						
			jmp esi
	jmp161:						
		add esi, 810						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _161a						
		jmp edi						
		_161a:						
		test [edx], 10000000b						
		jnz _161						
		add esi,5						
		_161:						
			mov cx, 110000000b						
			jmp esi
	jmp162:						
		add esi, 815						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _162a						
		jmp edi						
		_162a:						
		test [edx], 10000000b						
		jnz _162						
		add esi,5						
		_162:						
			mov cx, 110000000b						
			jmp esi
	jmp163:						
		add esi, 820						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _163a						
		jmp edi						
		_163a:						
		test [edx], 10000000b						
		jnz _163						
		add esi,5						
		_163:						
			mov cx, 110000000b						
			jmp esi
	jmp164:						
		add esi, 825						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _164a						
		jmp edi						
		_164a:						
		test [edx], 10000000b						
		jnz _164						
		add esi,5						
		_164:						
			mov cx, 110000000b						
			jmp esi
	jmp165:						
		add esi, 830						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _165a						
		jmp edi						
		_165a:						
		test [edx], 10000000b						
		jnz _165						
		add esi,5						
		_165:						
			mov cx, 110000000b						
			jmp esi
	jmp166:						
		add esi, 835						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _166a						
		jmp edi						
		_166a:						
		test [edx], 10000000b						
		jnz _166						
		add esi,5						
		_166:						
			mov cx, 110000000b						
			jmp esi
	jmp167:						
		add esi, 840						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _167a						
		jmp edi						
		_167a:						
		test [edx], 10000000b						
		jnz _167						
		add esi,5						
		_167:						
			mov cx, 110000000b						
			jmp esi
	jmp168:						
		add esi, 845						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _168a						
		jmp edi						
		_168a:						
		test [edx], 10000000b						
		jnz _168						
		add esi,5						
		_168:						
			mov cx, 110000000b						
			jmp esi
	jmp169:						
		add esi, 850						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _169a						
		jmp edi						
		_169a:						
		test [edx], 10000000b						
		jnz _169						
		add esi,5						
		_169:						
			mov cx, 110000000b						
			jmp esi
	jmp170:						
		add esi, 855						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _170a						
		jmp edi						
		_170a:						
		test [edx], 10000000b						
		jnz _170						
		add esi,5						
		_170:						
			mov cx, 110000000b						
			jmp esi
	jmp171:						
		add esi, 860						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _171a						
		jmp edi						
		_171a:						
		test [edx], 10000000b						
		jnz _171						
		add esi,5						
		_171:						
			mov cx, 110000000b						
			jmp esi
	jmp172:						
		add esi, 865						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _172a						
		jmp edi						
		_172a:						
		test [edx], 10000000b						
		jnz _172						
		add esi,5						
		_172:						
			mov cx, 110000000b						
			jmp esi
	jmp173:						
		add esi, 870						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _173a						
		jmp edi						
		_173a:						
		test [edx], 10000000b						
		jnz _173						
		add esi,5						
		_173:						
			mov cx, 110000000b						
			jmp esi
	jmp174:						
		add esi, 875						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _174a						
		jmp edi						
		_174a:						
		test [edx], 10000000b						
		jnz _174						
		add esi,5						
		_174:						
			mov cx, 110000000b						
			jmp esi
	jmp175:						
		add esi, 880						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _175a						
		jmp edi						
		_175a:						
		test [edx], 10000000b						
		jnz _175						
		add esi,5						
		_175:						
			mov cx, 110000000b						
			jmp esi
	jmp176:						
		add esi, 885						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _176a						
		jmp edi						
		_176a:						
		test [edx], 10000000b						
		jnz _176						
		add esi,5						
		_176:						
			mov cx, 110000000b						
			jmp esi
	jmp177:						
		add esi, 890						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _177a						
		jmp edi						
		_177a:						
		test [edx], 10000000b						
		jnz _177						
		add esi,5						
		_177:						
			mov cx, 110000000b						
			jmp esi
	jmp178:						
		add esi, 895						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _178a						
		jmp edi						
		_178a:						
		test [edx], 10000000b						
		jnz _178						
		add esi,5						
		_178:						
			mov cx, 110000000b						
			jmp esi
	jmp179:						
		add esi, 900						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _179a						
		jmp edi						
		_179a:						
		test [edx], 10000000b						
		jnz _179						
		add esi,5						
		_179:						
			mov cx, 110000000b						
			jmp esi
	jmp180:						
		add esi, 905						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _180a						
		jmp edi						
		_180a:						
		test [edx], 10000000b						
		jnz _180						
		add esi,5						
		_180:						
			mov cx, 110000000b						
			jmp esi
	jmp181:						
		add esi, 910						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _181a						
		jmp edi						
		_181a:						
		test [edx], 10000000b						
		jnz _181						
		add esi,5						
		_181:						
			mov cx, 110000000b						
			jmp esi
	jmp182:						
		add esi, 915						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _182a						
		jmp edi						
		_182a:						
		test [edx], 10000000b						
		jnz _182						
		add esi,5						
		_182:						
			mov cx, 110000000b						
			jmp esi
	jmp183:						
		add esi, 920						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _183a						
		jmp edi						
		_183a:						
		test [edx], 10000000b						
		jnz _183						
		add esi,5						
		_183:						
			mov cx, 110000000b						
			jmp esi
	jmp184:						
		add esi, 925						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _184a						
		jmp edi						
		_184a:						
		test [edx], 10000000b						
		jnz _184						
		add esi,5						
		_184:						
			mov cx, 110000000b						
			jmp esi
	jmp185:						
		add esi, 930						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _185a						
		jmp edi						
		_185a:						
		test [edx], 10000000b						
		jnz _185						
		add esi,5						
		_185:						
			mov cx, 110000000b						
			jmp esi
	jmp186:						
		add esi, 935						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _186a						
		jmp edi						
		_186a:						
		test [edx], 10000000b						
		jnz _186						
		add esi,5						
		_186:						
			mov cx, 110000000b						
			jmp esi
	jmp187:						
		add esi, 940						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _187a						
		jmp edi						
		_187a:						
		test [edx], 10000000b						
		jnz _187						
		add esi,5						
		_187:						
			mov cx, 110000000b						
			jmp esi
	jmp188:						
		add esi, 945						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _188a						
		jmp edi						
		_188a:						
		test [edx], 10000000b						
		jnz _188						
		add esi,5						
		_188:						
			mov cx, 110000000b						
			jmp esi
	jmp189:						
		add esi, 950						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _189a						
		jmp edi						
		_189a:						
		test [edx], 10000000b						
		jnz _189						
		add esi,5						
		_189:						
			mov cx, 110000000b						
			jmp esi
	jmp190:						
		add esi, 955						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _190a						
		jmp edi						
		_190a:						
		test [edx], 10000000b						
		jnz _190						
		add esi,5						
		_190:						
			mov cx, 110000000b						
			jmp esi
	jmp191:						
		add esi, 960						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _191a						
		jmp edi						
		_191a:						
		test [edx], 10000000b						
		jnz _191						
		add esi,5						
		_191:						
			mov cx, 110000000b						
			jmp esi
	jmp192:						
		add esi, 965						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _192a						
		jmp edi						
		_192a:						
		test [edx], 10000000b						
		jnz _192						
		add esi,5						
		_192:						
			mov cx, 110000000b						
			jmp esi
	jmp193:						
		add esi, 970						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _193a						
		jmp edi						
		_193a:						
		test [edx], 10000000b						
		jnz _193						
		add esi,5						
		_193:						
			mov cx, 110000000b						
			jmp esi
	jmp194:						
		add esi, 975						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _194a						
		jmp edi						
		_194a:						
		test [edx], 10000000b						
		jnz _194						
		add esi,5						
		_194:						
			mov cx, 110000000b						
			jmp esi
	jmp195:						
		add esi, 980						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _195a						
		jmp edi						
		_195a:						
		test [edx], 10000000b						
		jnz _195						
		add esi,5						
		_195:						
			mov cx, 110000000b						
			jmp esi
	jmp196:						
		add esi, 985						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _196a						
		jmp edi						
		_196a:						
		test [edx], 10000000b						
		jnz _196						
		add esi,5						
		_196:						
			mov cx, 110000000b						
			jmp esi
	jmp197:						
		add esi, 990						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _197a						
		jmp edi						
		_197a:						
		test [edx], 10000000b						
		jnz _197						
		add esi,5						
		_197:						
			mov cx, 110000000b						
			jmp esi
	jmp198:						
		add esi, 995						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _198a						
		jmp edi						
		_198a:						
		test [edx], 10000000b						
		jnz _198						
		add esi,5						
		_198:						
			mov cx, 110000000b						
			jmp esi
	jmp199:						
		add esi, 1000						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _199a						
		jmp edi						
		_199a:						
		test [edx], 10000000b						
		jnz _199						
		add esi,5						
		_199:						
			mov cx, 110000000b						
			jmp esi
	jmp200:						
		add esi, 1005						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _200a						
		jmp edi						
		_200a:						
		test [edx], 10000000b						
		jnz _200						
		add esi,5						
		_200:						
			mov cx, 110000000b						
			jmp esi
	jmp201:						
		add esi, 1010						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _201a						
		jmp edi						
		_201a:						
		test [edx], 10000000b						
		jnz _201						
		add esi,5						
		_201:						
			mov cx, 110000000b						
			jmp esi
	jmp202:						
		add esi, 1015						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _202a						
		jmp edi						
		_202a:						
		test [edx], 10000000b						
		jnz _202						
		add esi,5						
		_202:						
			mov cx, 110000000b						
			jmp esi
	jmp203:						
		add esi, 1020						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _203a						
		jmp edi						
		_203a:						
		test [edx], 10000000b						
		jnz _203						
		add esi,5						
		_203:						
			mov cx, 110000000b						
			jmp esi
	jmp204:						
		add esi, 1025						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _204a						
		jmp edi						
		_204a:						
		test [edx], 10000000b						
		jnz _204						
		add esi,5						
		_204:						
			mov cx, 110000000b						
			jmp esi
	jmp205:						
		add esi, 1030						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _205a						
		jmp edi						
		_205a:						
		test [edx], 10000000b						
		jnz _205						
		add esi,5						
		_205:						
			mov cx, 110000000b						
			jmp esi
	jmp206:						
		add esi, 1035						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _206a						
		jmp edi						
		_206a:						
		test [edx], 10000000b						
		jnz _206						
		add esi,5						
		_206:						
			mov cx, 110000000b						
			jmp esi
	jmp207:						
		add esi, 1040						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _207a						
		jmp edi						
		_207a:						
		test [edx], 10000000b						
		jnz _207						
		add esi,5						
		_207:						
			mov cx, 110000000b						
			jmp esi
	jmp208:						
		add esi, 1045						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _208a						
		jmp edi						
		_208a:						
		test [edx], 10000000b						
		jnz _208						
		add esi,5						
		_208:						
			mov cx, 110000000b						
			jmp esi
	jmp209:						
		add esi, 1050						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _209a						
		jmp edi						
		_209a:						
		test [edx], 10000000b						
		jnz _209						
		add esi,5						
		_209:						
			mov cx, 110000000b						
			jmp esi
	jmp210:						
		add esi, 1055						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _210a						
		jmp edi						
		_210a:						
		test [edx], 10000000b						
		jnz _210						
		add esi,5						
		_210:						
			mov cx, 110000000b						
			jmp esi
	jmp211:						
		add esi, 1060						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _211a						
		jmp edi						
		_211a:						
		test [edx], 10000000b						
		jnz _211						
		add esi,5						
		_211:						
			mov cx, 110000000b						
			jmp esi
	jmp212:						
		add esi, 1065						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _212a						
		jmp edi						
		_212a:						
		test [edx], 10000000b						
		jnz _212						
		add esi,5						
		_212:						
			mov cx, 110000000b						
			jmp esi
	jmp213:						
		add esi, 1070						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _213a						
		jmp edi						
		_213a:						
		test [edx], 10000000b						
		jnz _213						
		add esi,5						
		_213:						
			mov cx, 110000000b						
			jmp esi
	jmp214:						
		add esi, 1075						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _214a						
		jmp edi						
		_214a:						
		test [edx], 10000000b						
		jnz _214						
		add esi,5						
		_214:						
			mov cx, 110000000b						
			jmp esi
	jmp215:						
		add esi, 1080						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _215a						
		jmp edi						
		_215a:						
		test [edx], 10000000b						
		jnz _215						
		add esi,5						
		_215:						
			mov cx, 110000000b						
			jmp esi
	jmp216:						
		add esi, 1085						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _216a						
		jmp edi						
		_216a:						
		test [edx], 10000000b						
		jnz _216						
		add esi,5						
		_216:						
			mov cx, 110000000b						
			jmp esi
	jmp217:						
		add esi, 1090						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _217a						
		jmp edi						
		_217a:						
		test [edx], 10000000b						
		jnz _217						
		add esi,5						
		_217:						
			mov cx, 110000000b						
			jmp esi
	jmp218:						
		add esi, 1095						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _218a						
		jmp edi						
		_218a:						
		test [edx], 10000000b						
		jnz _218						
		add esi,5						
		_218:						
			mov cx, 110000000b						
			jmp esi
	jmp219:						
		add esi, 1100						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _219a						
		jmp edi						
		_219a:						
		test [edx], 10000000b						
		jnz _219						
		add esi,5						
		_219:						
			mov cx, 110000000b						
			jmp esi
	jmp220:						
		add esi, 1105						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _220a						
		jmp edi						
		_220a:						
		test [edx], 10000000b						
		jnz _220						
		add esi,5						
		_220:						
			mov cx, 110000000b						
			jmp esi
	jmp221:						
		add esi, 1110						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _221a						
		jmp edi						
		_221a:						
		test [edx], 10000000b						
		jnz _221						
		add esi,5						
		_221:						
			mov cx, 110000000b						
			jmp esi
	jmp222:						
		add esi, 1115						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _222a						
		jmp edi						
		_222a:						
		test [edx], 10000000b						
		jnz _222						
		add esi,5						
		_222:						
			mov cx, 110000000b						
			jmp esi
	jmp223:						
		add esi, 1120						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _223a						
		jmp edi						
		_223a:						
		test [edx], 10000000b						
		jnz _223						
		add esi,5						
		_223:						
			mov cx, 110000000b						
			jmp esi
	jmp224:						
		add esi, 1125						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _224a						
		jmp edi						
		_224a:						
		test [edx], 10000000b						
		jnz _224						
		add esi,5						
		_224:						
			mov cx, 110000000b						
			jmp esi
	jmp225:						
		add esi, 1130						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _225a						
		jmp edi						
		_225a:						
		test [edx], 10000000b						
		jnz _225						
		add esi,5						
		_225:						
			mov cx, 110000000b						
			jmp esi
	jmp226:						
		add esi, 1135						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _226a						
		jmp edi						
		_226a:						
		test [edx], 10000000b						
		jnz _226						
		add esi,5						
		_226:						
			mov cx, 110000000b						
			jmp esi
	jmp227:						
		add esi, 1140						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _227a						
		jmp edi						
		_227a:						
		test [edx], 10000000b						
		jnz _227						
		add esi,5						
		_227:						
			mov cx, 110000000b						
			jmp esi
	jmp228:						
		add esi, 1145						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _228a						
		jmp edi						
		_228a:						
		test [edx], 10000000b						
		jnz _228						
		add esi,5						
		_228:						
			mov cx, 110000000b						
			jmp esi
	jmp229:						
		add esi, 1150						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _229a						
		jmp edi						
		_229a:						
		test [edx], 10000000b						
		jnz _229						
		add esi,5						
		_229:						
			mov cx, 110000000b						
			jmp esi
	jmp230:						
		add esi, 1155						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _230a						
		jmp edi						
		_230a:						
		test [edx], 10000000b						
		jnz _230						
		add esi,5						
		_230:						
			mov cx, 110000000b						
			jmp esi
	jmp231:						
		add esi, 1160						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _231a						
		jmp edi						
		_231a:						
		test [edx], 10000000b						
		jnz _231						
		add esi,5						
		_231:						
			mov cx, 110000000b						
			jmp esi
	jmp232:						
		add esi, 1165						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _232a						
		jmp edi						
		_232a:						
		test [edx], 10000000b						
		jnz _232						
		add esi,5						
		_232:						
			mov cx, 110000000b						
			jmp esi
	jmp233:						
		add esi, 1170						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _233a						
		jmp edi						
		_233a:						
		test [edx], 10000000b						
		jnz _233						
		add esi,5						
		_233:						
			mov cx, 110000000b						
			jmp esi
	jmp234:						
		add esi, 1175						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _234a						
		jmp edi						
		_234a:						
		test [edx], 10000000b						
		jnz _234						
		add esi,5						
		_234:						
			mov cx, 110000000b						
			jmp esi
	jmp235:						
		add esi, 1180						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _235a						
		jmp edi						
		_235a:						
		test [edx], 10000000b						
		jnz _235						
		add esi,5						
		_235:						
			mov cx, 110000000b						
			jmp esi
	jmp236:						
		add esi, 1185						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _236a						
		jmp edi						
		_236a:						
		test [edx], 10000000b						
		jnz _236						
		add esi,5						
		_236:						
			mov cx, 110000000b						
			jmp esi
	jmp237:						
		add esi, 1190						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _237a						
		jmp edi						
		_237a:						
		test [edx], 10000000b						
		jnz _237						
		add esi,5						
		_237:						
			mov cx, 110000000b						
			jmp esi
	jmp238:						
		add esi, 1195						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _238a						
		jmp edi						
		_238a:						
		test [edx], 10000000b						
		jnz _238						
		add esi,5						
		_238:						
			mov cx, 110000000b						
			jmp esi
	jmp239:						
		add esi, 1200						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _239a						
		jmp edi						
		_239a:						
		test [edx], 10000000b						
		jnz _239						
		add esi,5						
		_239:						
			mov cx, 110000000b						
			jmp esi
	jmp240:						
		add esi, 1205						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _240a						
		jmp edi						
		_240a:						
		test [edx], 10000000b						
		jnz _240						
		add esi,5						
		_240:						
			mov cx, 110000000b						
			jmp esi
	jmp241:						
		add esi, 1210						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _241a						
		jmp edi						
		_241a:						
		test [edx], 10000000b						
		jnz _241						
		add esi,5						
		_241:						
			mov cx, 110000000b						
			jmp esi
	jmp242:						
		add esi, 1215						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _242a						
		jmp edi						
		_242a:						
		test [edx], 10000000b						
		jnz _242						
		add esi,5						
		_242:						
			mov cx, 110000000b						
			jmp esi
	jmp243:						
		add esi, 1220						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _243a						
		jmp edi						
		_243a:						
		test [edx], 10000000b						
		jnz _243						
		add esi,5						
		_243:						
			mov cx, 110000000b						
			jmp esi
	jmp244:						
		add esi, 1225						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _244a						
		jmp edi						
		_244a:						
		test [edx], 10000000b						
		jnz _244						
		add esi,5						
		_244:						
			mov cx, 110000000b						
			jmp esi
	jmp245:						
		add esi, 1230						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _245a						
		jmp edi						
		_245a:						
		test [edx], 10000000b						
		jnz _245						
		add esi,5						
		_245:						
			mov cx, 110000000b						
			jmp esi
	jmp246:						
		add esi, 1235						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _246a						
		jmp edi						
		_246a:						
		test [edx], 10000000b						
		jnz _246						
		add esi,5						
		_246:						
			mov cx, 110000000b						
			jmp esi
	jmp247:						
		add esi, 1240						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _247a						
		jmp edi						
		_247a:						
		test [edx], 10000000b						
		jnz _247						
		add esi,5						
		_247:						
			mov cx, 110000000b						
			jmp esi
	jmp248:						
		add esi, 1245						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _248a						
		jmp edi						
		_248a:						
		test [edx], 10000000b						
		jnz _248						
		add esi,5						
		_248:						
			mov cx, 110000000b						
			jmp esi
	jmp249:						
		add esi, 1250						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _249a						
		jmp edi						
		_249a:						
		test [edx], 10000000b						
		jnz _249						
		add esi,5						
		_249:						
			mov cx, 110000000b						
			jmp esi
	jmp250:						
		add esi, 1255						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _250a						
		jmp edi						
		_250a:						
		test [edx], 10000000b						
		jnz _250						
		add esi,5						
		_250:						
			mov cx, 110000000b						
			jmp esi
	jmp251:						
		add esi, 1260						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _251a						
		jmp edi						
		_251a:						
		test [edx], 10000000b						
		jnz _251						
		add esi,5						
		_251:						
			mov cx, 110000000b						
			jmp esi
	jmp252:						
		add esi, 1265						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _252a						
		jmp edi						
		_252a:						
		test [edx], 10000000b						
		jnz _252						
		add esi,5						
		_252:						
			mov cx, 110000000b						
			jmp esi
	jmp253:						
		add esi, 1270						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _253a						
		jmp edi						
		_253a:						
		test [edx], 10000000b						
		jnz _253						
		add esi,5						
		_253:						
			mov cx, 110000000b						
			jmp esi
	jmp254:						
		add esi, 1275						
		inc edx						
		inc eax						
		mov bl, byte ptr [edx]						
		mov  [eax], bl						
		pop ebx						
		pop eax						
		pop ecx						
		test cx, 11b						
		jz _254a						
		jmp edi						
		_254a:						
		test [edx], 10000000b						
		jnz _254						
		add esi,5						
		_254:						
			mov cx, 110000000b						
			jmp esi
	jmp255:							
		mov [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _255							
		jmp esi							
		_255:							
		jmp edi
	jmp256:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _256							
		jmp esi							
		_256:							
		jmp edi
	jmp257:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _257							
		jmp esi							
		_257:							
		jmp edi
	jmp258:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _258							
		jmp esi							
		_258:							
		jmp edi
	jmp259:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _259							
		jmp esi							
		_259:							
		jmp edi
	jmp260:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _260							
		jmp esi							
		_260:							
		jmp edi
	jmp261:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _261							
		jmp esi							
		_261:							
		jmp edi
	jmp262:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _262							
		jmp esi							
		_262:							
		jmp edi
	jmp263:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _263							
		jmp esi							
		_263:							
		jmp edi
	jmp264:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _264							
		jmp esi							
		_264:							
		jmp edi
	jmp265:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _265							
		jmp esi							
		_265:							
		jmp edi
	jmp266:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _266							
		jmp esi							
		_266:							
		jmp edi
	jmp267:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _267							
		jmp esi							
		_267:							
		jmp edi
	jmp268:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _268							
		jmp esi							
		_268:							
		jmp edi
	jmp269:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _269							
		jmp esi							
		_269:							
		jmp edi
	jmp270:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _270							
		jmp esi							
		_270:							
		jmp edi
	jmp271:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _271							
		jmp esi							
		_271:							
		jmp edi
	jmp272:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _272							
		jmp esi							
		_272:							
		jmp edi
	jmp273:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _273							
		jmp esi							
		_273:							
		jmp edi
	jmp274:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _274							
		jmp esi							
		_274:							
		jmp edi
	jmp275:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _275							
		jmp esi							
		_275:							
		jmp edi
	jmp276:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _276							
		jmp esi							
		_276:							
		jmp edi
	jmp277:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _277							
		jmp esi							
		_277:							
		jmp edi
	jmp278:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _278							
		jmp esi							
		_278:							
		jmp edi
	jmp279:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _279							
		jmp esi							
		_279:							
		jmp edi
	jmp280:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _280							
		jmp esi							
		_280:							
		jmp edi
	jmp281:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _281							
		jmp esi							
		_281:							
		jmp edi
	jmp282:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _282							
		jmp esi							
		_282:							
		jmp edi
	jmp283:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _283							
		jmp esi							
		_283:							
		jmp edi
	jmp284:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _284							
		jmp esi							
		_284:							
		jmp edi
	jmp285:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _285							
		jmp esi							
		_285:							
		jmp edi
	jmp286:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _286							
		jmp esi							
		_286:							
		jmp edi
	jmp287:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _287							
		jmp esi							
		_287:							
		jmp edi
	jmp288:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _288							
		jmp esi							
		_288:							
		jmp edi
	jmp289:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _289							
		jmp esi							
		_289:							
		jmp edi
	jmp290:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _290							
		jmp esi							
		_290:							
		jmp edi
	jmp291:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _291							
		jmp esi							
		_291:							
		jmp edi
	jmp292:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _292							
		jmp esi							
		_292:							
		jmp edi
	jmp293:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _293							
		jmp esi							
		_293:							
		jmp edi
	jmp294:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _294							
		jmp esi							
		_294:							
		jmp edi
	jmp295:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _295							
		jmp esi							
		_295:							
		jmp edi
	jmp296:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _296							
		jmp esi							
		_296:							
		jmp edi
	jmp297:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _297							
		jmp esi							
		_297:							
		jmp edi
	jmp298:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _298							
		jmp esi							
		_298:							
		jmp edi
	jmp299:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _299							
		jmp esi							
		_299:							
		jmp edi
	jmp300:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _300							
		jmp esi							
		_300:							
		jmp edi
	jmp301:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _301							
		jmp esi							
		_301:							
		jmp edi
	jmp302:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _302							
		jmp esi							
		_302:							
		jmp edi
	jmp303:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _303							
		jmp esi							
		_303:							
		jmp edi
	jmp304:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _304							
		jmp esi							
		_304:							
		jmp edi
	jmp305:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _305							
		jmp esi							
		_305:							
		jmp edi
	jmp306:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _306							
		jmp esi							
		_306:							
		jmp edi
	jmp307:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _307							
		jmp esi							
		_307:							
		jmp edi
	jmp308:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _308							
		jmp esi							
		_308:							
		jmp edi
	jmp309:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _309							
		jmp esi							
		_309:							
		jmp edi
	jmp310:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _310							
		jmp esi							
		_310:							
		jmp edi
	jmp311:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _311							
		jmp esi							
		_311:							
		jmp edi
	jmp312:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _312							
		jmp esi							
		_312:							
		jmp edi
	jmp313:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _313							
		jmp esi							
		_313:							
		jmp edi
	jmp314:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _314							
		jmp esi							
		_314:							
		jmp edi
	jmp315:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _315							
		jmp esi							
		_315:							
		jmp edi
	jmp316:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _316							
		jmp esi							
		_316:							
		jmp edi
	jmp317:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _317							
		jmp esi							
		_317:							
		jmp edi
	jmp318:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _318							
		jmp esi							
		_318:							
		jmp edi
	jmp319:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _319							
		jmp esi							
		_319:							
		jmp edi
	jmp320:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _320							
		jmp esi							
		_320:							
		jmp edi
	jmp321:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _321							
		jmp esi							
		_321:							
		jmp edi
	jmp322:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _322							
		jmp esi							
		_322:							
		jmp edi
	jmp323:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _323							
		jmp esi							
		_323:							
		jmp edi
	jmp324:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _324							
		jmp esi							
		_324:							
		jmp edi
	jmp325:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _325							
		jmp esi							
		_325:							
		jmp edi
	jmp326:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _326							
		jmp esi							
		_326:							
		jmp edi
	jmp327:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _327							
		jmp esi							
		_327:							
		jmp edi
	jmp328:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _328							
		jmp esi							
		_328:							
		jmp edi
	jmp329:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _329							
		jmp esi							
		_329:							
		jmp edi
	jmp330:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _330							
		jmp esi							
		_330:							
		jmp edi
	jmp331:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _331							
		jmp esi							
		_331:							
		jmp edi
	jmp332:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _332							
		jmp esi							
		_332:							
		jmp edi
	jmp333:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _333							
		jmp esi							
		_333:							
		jmp edi
	jmp334:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _334							
		jmp esi							
		_334:							
		jmp edi
	jmp335:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _335							
		jmp esi							
		_335:							
		jmp edi
	jmp336:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _336							
		jmp esi							
		_336:							
		jmp edi
	jmp337:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _337							
		jmp esi							
		_337:							
		jmp edi
	jmp338:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _338							
		jmp esi							
		_338:							
		jmp edi
	jmp339:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _339							
		jmp esi							
		_339:							
		jmp edi
	jmp340:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _340							
		jmp esi							
		_340:							
		jmp edi
	jmp341:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _341							
		jmp esi							
		_341:							
		jmp edi
	jmp342:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _342							
		jmp esi							
		_342:							
		jmp edi
	jmp343:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _343							
		jmp esi							
		_343:							
		jmp edi
	jmp344:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _344							
		jmp esi							
		_344:							
		jmp edi
	jmp345:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _345							
		jmp esi							
		_345:							
		jmp edi
	jmp346:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _346							
		jmp esi							
		_346:							
		jmp edi
	jmp347:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _347							
		jmp esi							
		_347:							
		jmp edi
	jmp348:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _348							
		jmp esi							
		_348:							
		jmp edi
	jmp349:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _349							
		jmp esi							
		_349:							
		jmp edi
	jmp350:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _350							
		jmp esi							
		_350:							
		jmp edi
	jmp351:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _351							
		jmp esi							
		_351:							
		jmp edi
	jmp352:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _352							
		jmp esi							
		_352:							
		jmp edi
	jmp353:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _353							
		jmp esi							
		_353:							
		jmp edi
	jmp354:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _354							
		jmp esi							
		_354:							
		jmp edi
	jmp355:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _355							
		jmp esi							
		_355:							
		jmp edi
	jmp356:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _356							
		jmp esi							
		_356:							
		jmp edi
	jmp357:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _357							
		jmp esi							
		_357:							
		jmp edi
	jmp358:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _358							
		jmp esi							
		_358:							
		jmp edi
	jmp359:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _359							
		jmp esi							
		_359:							
		jmp edi
	jmp360:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _360							
		jmp esi							
		_360:							
		jmp edi
	jmp361:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _361							
		jmp esi							
		_361:							
		jmp edi
	jmp362:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _362							
		jmp esi							
		_362:							
		jmp edi
	jmp363:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _363							
		jmp esi							
		_363:							
		jmp edi
	jmp364:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _364							
		jmp esi							
		_364:							
		jmp edi
	jmp365:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _365							
		jmp esi							
		_365:							
		jmp edi
	jmp366:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _366							
		jmp esi							
		_366:							
		jmp edi
	jmp367:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _367							
		jmp esi							
		_367:							
		jmp edi
	jmp368:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _368							
		jmp esi							
		_368:							
		jmp edi
	jmp369:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _369							
		jmp esi							
		_369:							
		jmp edi
	jmp370:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _370							
		jmp esi							
		_370:							
		jmp edi
	jmp371:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _371							
		jmp esi							
		_371:							
		jmp edi
	jmp372:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _372							
		jmp esi							
		_372:							
		jmp edi
	jmp373:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _373							
		jmp esi							
		_373:							
		jmp edi
	jmp374:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _374							
		jmp esi							
		_374:							
		jmp edi
	jmp375:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _375							
		jmp esi							
		_375:							
		jmp edi
	jmp376:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _376							
		jmp esi							
		_376:							
		jmp edi
	jmp377:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _377							
		jmp esi							
		_377:							
		jmp edi
	jmp378:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _378							
		jmp esi							
		_378:							
		jmp edi
	jmp379:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _379							
		jmp esi							
		_379:							
		jmp edi
	jmp380:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _380							
		jmp esi							
		_380:							
		jmp edi
	jmp381:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _381							
		jmp esi							
		_381:							
		jmp edi
	jmp382:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _382							
		jmp esi							
		_382:							
		jmp edi
	jmp383:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _383							
		jmp esi							
		_383:							
		jmp edi
	jmp384:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _384							
		jmp esi							
		_384:							
		jmp edi
	jmp385:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _385							
		jmp esi							
		_385:							
		jmp edi
	jmp386:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _386							
		jmp esi							
		_386:							
		jmp edi
	jmp387:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _387							
		jmp esi							
		_387:							
		jmp edi
	jmp388:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _388							
		jmp esi							
		_388:							
		jmp edi
	jmp389:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _389							
		jmp esi							
		_389:							
		jmp edi
	jmp390:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _390							
		jmp esi							
		_390:							
		jmp edi
	jmp391:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _391							
		jmp esi							
		_391:							
		jmp edi
	jmp392:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _392							
		jmp esi							
		_392:							
		jmp edi
	jmp393:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _393							
		jmp esi							
		_393:							
		jmp edi
	jmp394:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _394							
		jmp esi							
		_394:							
		jmp edi
	jmp395:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _395							
		jmp esi							
		_395:							
		jmp edi
	jmp396:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _396							
		jmp esi							
		_396:							
		jmp edi
	jmp397:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _397							
		jmp esi							
		_397:							
		jmp edi
	jmp398:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _398							
		jmp esi							
		_398:							
		jmp edi
	jmp399:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _399							
		jmp esi							
		_399:							
		jmp edi
	jmp400:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _400							
		jmp esi							
		_400:							
		jmp edi
	jmp401:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _401							
		jmp esi							
		_401:							
		jmp edi
	jmp402:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _402							
		jmp esi							
		_402:							
		jmp edi
	jmp403:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _403							
		jmp esi							
		_403:							
		jmp edi
	jmp404:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _404							
		jmp esi							
		_404:							
		jmp edi
	jmp405:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _405							
		jmp esi							
		_405:							
		jmp edi
	jmp406:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _406							
		jmp esi							
		_406:							
		jmp edi
	jmp407:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _407							
		jmp esi							
		_407:							
		jmp edi
	jmp408:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _408							
		jmp esi							
		_408:							
		jmp edi
	jmp409:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _409							
		jmp esi							
		_409:							
		jmp edi
	jmp410:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _410							
		jmp esi							
		_410:							
		jmp edi
	jmp411:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _411							
		jmp esi							
		_411:							
		jmp edi
	jmp412:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _412							
		jmp esi							
		_412:							
		jmp edi
	jmp413:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _413							
		jmp esi							
		_413:							
		jmp edi
	jmp414:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _414							
		jmp esi							
		_414:							
		jmp edi
	jmp415:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _415							
		jmp esi							
		_415:							
		jmp edi
	jmp416:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _416							
		jmp esi							
		_416:							
		jmp edi
	jmp417:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _417							
		jmp esi							
		_417:							
		jmp edi
	jmp418:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _418							
		jmp esi							
		_418:							
		jmp edi
	jmp419:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _419							
		jmp esi							
		_419:							
		jmp edi
	jmp420:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _420							
		jmp esi							
		_420:							
		jmp edi
	jmp421:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _421							
		jmp esi							
		_421:							
		jmp edi
	jmp422:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _422							
		jmp esi							
		_422:							
		jmp edi
	jmp423:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _423							
		jmp esi							
		_423:							
		jmp edi
	jmp424:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _424							
		jmp esi							
		_424:							
		jmp edi
	jmp425:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _425							
		jmp esi							
		_425:							
		jmp edi
	jmp426:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _426							
		jmp esi							
		_426:							
		jmp edi
	jmp427:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _427							
		jmp esi							
		_427:							
		jmp edi
	jmp428:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _428							
		jmp esi							
		_428:							
		jmp edi
	jmp429:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _429							
		jmp esi							
		_429:							
		jmp edi
	jmp430:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _430							
		jmp esi							
		_430:							
		jmp edi
	jmp431:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _431							
		jmp esi							
		_431:							
		jmp edi
	jmp432:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _432							
		jmp esi							
		_432:							
		jmp edi
	jmp433:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _433							
		jmp esi							
		_433:							
		jmp edi
	jmp434:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _434							
		jmp esi							
		_434:							
		jmp edi
	jmp435:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _435							
		jmp esi							
		_435:							
		jmp edi
	jmp436:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _436							
		jmp esi							
		_436:							
		jmp edi
	jmp437:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _437							
		jmp esi							
		_437:							
		jmp edi
	jmp438:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _438							
		jmp esi							
		_438:							
		jmp edi
	jmp439:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _439							
		jmp esi							
		_439:							
		jmp edi
	jmp440:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _440							
		jmp esi							
		_440:							
		jmp edi
	jmp441:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _441							
		jmp esi							
		_441:							
		jmp edi
	jmp442:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _442							
		jmp esi							
		_442:							
		jmp edi
	jmp443:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _443							
		jmp esi							
		_443:							
		jmp edi
	jmp444:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _444							
		jmp esi							
		_444:							
		jmp edi
	jmp445:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _445							
		jmp esi							
		_445:							
		jmp edi
	jmp446:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _446							
		jmp esi							
		_446:							
		jmp edi
	jmp447:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _447							
		jmp esi							
		_447:							
		jmp edi
	jmp448:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _448							
		jmp esi							
		_448:							
		jmp edi
	jmp449:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _449							
		jmp esi							
		_449:							
		jmp edi
	jmp450:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _450							
		jmp esi							
		_450:							
		jmp edi
	jmp451:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _451							
		jmp esi							
		_451:							
		jmp edi
	jmp452:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _452							
		jmp esi							
		_452:							
		jmp edi
	jmp453:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _453							
		jmp esi							
		_453:							
		jmp edi
	jmp454:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _454							
		jmp esi							
		_454:							
		jmp edi
	jmp455:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _455							
		jmp esi							
		_455:							
		jmp edi
	jmp456:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _456							
		jmp esi							
		_456:							
		jmp edi
	jmp457:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _457							
		jmp esi							
		_457:							
		jmp edi
	jmp458:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _458							
		jmp esi							
		_458:							
		jmp edi
	jmp459:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _459							
		jmp esi							
		_459:							
		jmp edi
	jmp460:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _460							
		jmp esi							
		_460:							
		jmp edi
	jmp461:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _461							
		jmp esi							
		_461:							
		jmp edi
	jmp462:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _462							
		jmp esi							
		_462:							
		jmp edi
	jmp463:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _463							
		jmp esi							
		_463:							
		jmp edi
	jmp464:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _464							
		jmp esi							
		_464:							
		jmp edi
	jmp465:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _465							
		jmp esi							
		_465:							
		jmp edi
	jmp466:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _466							
		jmp esi							
		_466:							
		jmp edi
	jmp467:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _467							
		jmp esi							
		_467:							
		jmp edi
	jmp468:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _468							
		jmp esi							
		_468:							
		jmp edi
	jmp469:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _469							
		jmp esi							
		_469:							
		jmp edi
	jmp470:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _470							
		jmp esi							
		_470:							
		jmp edi
	jmp471:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _471							
		jmp esi							
		_471:							
		jmp edi
	jmp472:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _472							
		jmp esi							
		_472:							
		jmp edi
	jmp473:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _473							
		jmp esi							
		_473:							
		jmp edi
	jmp474:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _474							
		jmp esi							
		_474:							
		jmp edi
	jmp475:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _475							
		jmp esi							
		_475:							
		jmp edi
	jmp476:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _476							
		jmp esi							
		_476:							
		jmp edi
	jmp477:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _477							
		jmp esi							
		_477:							
		jmp edi
	jmp478:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _478							
		jmp esi							
		_478:							
		jmp edi
	jmp479:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _479							
		jmp esi							
		_479:							
		jmp edi
	jmp480:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _480							
		jmp esi							
		_480:							
		jmp edi
	jmp481:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _481							
		jmp esi							
		_481:							
		jmp edi
	jmp482:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _482							
		jmp esi							
		_482:							
		jmp edi
	jmp483:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _483							
		jmp esi							
		_483:							
		jmp edi
	jmp484:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _484							
		jmp esi							
		_484:							
		jmp edi
	jmp485:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _485							
		jmp esi							
		_485:							
		jmp edi
	jmp486:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _486							
		jmp esi							
		_486:							
		jmp edi
	jmp487:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _487							
		jmp esi							
		_487:							
		jmp edi
	jmp488:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _488							
		jmp esi							
		_488:							
		jmp edi
	jmp489:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _489							
		jmp esi							
		_489:							
		jmp edi
	jmp490:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _490							
		jmp esi							
		_490:							
		jmp edi
	jmp491:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _491							
		jmp esi							
		_491:							
		jmp edi
	jmp492:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _492							
		jmp esi							
		_492:							
		jmp edi
	jmp493:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _493							
		jmp esi							
		_493:							
		jmp edi
	jmp494:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _494							
		jmp esi							
		_494:							
		jmp edi
	jmp495:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _495							
		jmp esi							
		_495:							
		jmp edi
	jmp496:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _496							
		jmp esi							
		_496:							
		jmp edi
	jmp497:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _497							
		jmp esi							
		_497:							
		jmp edi
	jmp498:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _498							
		jmp esi							
		_498:							
		jmp edi
	jmp499:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _499							
		jmp esi							
		_499:							
		jmp edi
	jmp500:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _500							
		jmp esi							
		_500:							
		jmp edi
	jmp501:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _501							
		jmp esi							
		_501:							
		jmp edi
	jmp502:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _502							
		jmp esi							
		_502:							
		jmp edi
	jmp503:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _503							
		jmp esi							
		_503:							
		jmp edi
	jmp504:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _504							
		jmp esi							
		_504:							
		jmp edi
	jmp505:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _505							
		jmp esi							
		_505:							
		jmp edi
	jmp506:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _506							
		jmp esi							
		_506:							
		jmp edi
	jmp507:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _507							
		jmp esi							
		_507:							
		jmp edi
	jmp508:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _508							
		jmp esi							
		_508:							
		jmp edi
	jmp509:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _509							
		jmp esi							
		_509:							
		jmp edi
	jmp510:							
		add [eax], bl							
		inc eax							
		dec cx							
		test cx, 111111111b							
		jz _510							
		jmp esi							
		_510:							
		jmp edi
	end:
		
		popa
	
	}
#ifdef BOOKMARK_TEST
	if(stepNum || l_addr != l)
		memcpy(_buff, buff, 0x1ff);
#endif
}
/*----------------------------------------------------------------------------/
/*****************************END*******************************************/
/*--------------------------------------------------------------------------*/