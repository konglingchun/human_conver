## usage

human <number>
number must be Hexadecimal, Decimal, Octal, Binary
Different bases can be automatically detected and converted
	Hexadecimal: start with 0x or 0X
	Decimal: default
	Octal: start with 0
	Binary: start with 0b or 0B

## demo

human 18446744073709551615
	ibase: DEC_BASE
	input = [18446744073709551615]
	Human: 15E 1023P 1023T 1023G 1023M 1023K 1023B 
	BASE:	number
	hex: 	0XFFFFFFFFFFFFFFFF
	dec: 	18446744073709551615
	oct: 	1777777777777777777777
	bin: 	1111111111111111111111111111111111111111111111111111111111111111