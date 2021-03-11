#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/*
可以选择的编码如下所示:
	编码    颜色/动作 
	0       重新设置属性到缺省设置 
	1       设置粗体 
	2       设置一半亮度（模拟彩色显示器的颜色） 
	4       设置下划线（模拟彩色显示器的颜色） 
	5       设置闪烁 
	7       设置反向图象
	8       隐形
	22      设置一般密度 
	24      关闭下划线 
	25      关闭闪烁 
	27      关闭反向图象
	颜色分为背景色和字体色，30~39用来设置字体色，40~49设置背景
	30      设置黑色前景 
	31      设置红色前景 
	32      设置绿色前景 
	33      设置黄色前景 
	34      设置蓝色前景 
	35      设置紫色前景 
	36      设置青色前景 
	37      设置白色前景 
	38      在缺省的前景颜色上设置下划线 
	39      在缺省的前景颜色上关闭下划线 
	40      设置黑色背景 
	41      设置红色背景 
	42      设置绿色背景 
	43      设置黄色背景 
	44      设置蓝色背景 
	45      设置紫色背景 
	46      设置青色背景 
	47      设置白色背景 
	49      设置缺省黑色背景

其他一些有趣的编码(“\e”也可写成“\033”):
	\e[2J     清屏 
	\e[K      清除从光标到行尾的内容 
	\e[?25l   隐藏光标 
	\e[?25h   显示光标
	\e[y;xH   设置光标位置（x代表行，y代表列）
	\e[s      保存光标位置 
	\e[u      恢复光标位置
	\e[nA     光标上移n行 
	\e[nB     光标下移n行 
	\e[nC     光标右移n行 
	\e[nD     光标左移n行
	\e[0q     关闭所有的键盘指示灯 
	\e[1q     设置“滚动锁定”指示灯 (Scroll Lock) 
	\e[2q     设置“数值锁定”指示灯 (Num Lock) 
	\e[3q     设置“大写锁定”指示灯 (Caps Lock) 
*/

enum {
	HEX_BASE = 16,
	DEC_BASE = 10,
	OCT_BASE = 8,
	BIN_BASE = 2,
};

unsigned long long ibase = DEC_BASE;


const char* asciicodes[34] = {
  "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
  "BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI",
  "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
  "CAN", "EM", "SUB",  "ESC", "FS", "GS", "RS", "US",
  "SPC",
  "DEL"
};

const char* asciiescapes[34] = {
  "\\0", "", "", "", "", "", "", "",
  "\\b", "\\t", "\\n", "\\v", "\\f", "\\r", "", "",
  "", "", "", "", "", "", "", "",
  "", "", "", "(\\e)", "", "", "", "",
  "space",
  ""
};

const char* unicodenames[128] = {
  "NULL",
  "START OF HEADING",
  "START OF TEXT",
  "END OF TEXT",
  "END OF TRANSMISSION",
  "ENQUIRY",
  "ACKNOWLEDGE",
  "BELL",
  "BACKSPACE",
  "HORIZONTAL TABULATION",
  "LINE FEED",
  "VERTICAL TABULATION",
  "FORM FEED",
  "CARRIAGE RETURN",
  "SHIFT OUT",
  "SHIFT IN",

  "DATA LINK ESCAPE",
  "DEVICE CONTROL ONE",
  "DEVICE CONTROL TWO",
  "DEVICE CONTROL THREE",
  "DEVICE CONTROL FOUR",
  "NEGATIVE ACKNOWLEDGE",
  "SYNCHRONOUS IDLE",
  "END OF TRANSMISSION BLOCK",
  "CANCEL",
  "END OF MEDIUM",
  "SUBSTITUTE",
  "ESCAPE",
  "FILE SEPARATOR",
  "GROUP SEPARATOR",
  "RECORD SEPARATOR",
  "UNIT SEPARATOR",

  "SPACE",
  "EXCLAMATION MARK",
  "QUOTATION MARK",
  "NUMBER SIGN",
  "DOLLAR SIGN",
  "PERCENT SIGN",
  "AMPERSAND",
  "APOSTROPHE",
  "LEFT PARENTHESIS",
  "RIGHT PARENTHESIS",
  "ASTERISK",
  "PLUS SIGN",
  "COMMA",
  "HYPHEN-MINUS",
  "FULL STOP",
  "SOLIDUS",

  "DIGIT ZERO",
  "DIGIT ONE",
  "DIGIT TWO",
  "DIGIT THREE",
  "DIGIT FOUR",
  "DIGIT FIVE",
  "DIGIT SIX",
  "DIGIT SEVEN",
  "DIGIT EIGHT",
  "DIGIT NINE",
  "COLON",
  "SEMICOLON",
  "LESS-THAN SIGN",
  "EQUALS SIGN",
  "GREATER-THAN SIGN",
  "QUESTION MARK",

  "COMMERCIAL AT",
  "LATIN CAPITAL LETTER A",
  "LATIN CAPITAL LETTER B",
  "LATIN CAPITAL LETTER C",
  "LATIN CAPITAL LETTER D",
  "LATIN CAPITAL LETTER E",
  "LATIN CAPITAL LETTER F",
  "LATIN CAPITAL LETTER G",
  "LATIN CAPITAL LETTER H",
  "LATIN CAPITAL LETTER I",
  "LATIN CAPITAL LETTER J",
  "LATIN CAPITAL LETTER K",
  "LATIN CAPITAL LETTER L",
  "LATIN CAPITAL LETTER M",
  "LATIN CAPITAL LETTER N",
  "LATIN CAPITAL LETTER O",

  "LATIN CAPITAL LETTER P",
  "LATIN CAPITAL LETTER Q",
  "LATIN CAPITAL LETTER R",
  "LATIN CAPITAL LETTER S",
  "LATIN CAPITAL LETTER T",
  "LATIN CAPITAL LETTER U",
  "LATIN CAPITAL LETTER V",
  "LATIN CAPITAL LETTER W",
  "LATIN CAPITAL LETTER X",
  "LATIN CAPITAL LETTER Y",
  "LATIN CAPITAL LETTER Z",
  "LEFT SQUARE BRACKET",
  "REVERSE SOLIDUS",
  "RIGHT SQUARE BRACKET",
  "CIRCUMFLEX ACCENT",
  "LOW LINE",

  "GRAVE ACCENT",
  "LATIN SMALL LETTER A",
  "LATIN SMALL LETTER B",
  "LATIN SMALL LETTER C",
  "LATIN SMALL LETTER D",
  "LATIN SMALL LETTER E",
  "LATIN SMALL LETTER F",
  "LATIN SMALL LETTER G",
  "LATIN SMALL LETTER H",
  "LATIN SMALL LETTER I",
  "LATIN SMALL LETTER J",
  "LATIN SMALL LETTER K",
  "LATIN SMALL LETTER L",
  "LATIN SMALL LETTER M",
  "LATIN SMALL LETTER N",
  "LATIN SMALL LETTER O",

  "LATIN SMALL LETTER P",
  "LATIN SMALL LETTER Q",
  "LATIN SMALL LETTER R",
  "LATIN SMALL LETTER S",
  "LATIN SMALL LETTER T",
  "LATIN SMALL LETTER U",
  "LATIN SMALL LETTER V",
  "LATIN SMALL LETTER W",
  "LATIN SMALL LETTER X",
  "LATIN SMALL LETTER Y",
  "LATIN SMALL LETTER Z",
  "LEFT CURLY BRACKET",
  "VERTICAL LINE",
  "RIGHT CURLY BRACKET",
  "TILDE",
  "DELETE",
};

void ascii_print_info(unsigned char itemIndex)
{
	if(itemIndex < 32){
		printf("%i\t0x%02x\t%s\t%s\t%s\n", itemIndex, itemIndex, asciicodes[itemIndex], asciiescapes[itemIndex], unicodenames[itemIndex]);
	}else if(itemIndex < 127){
		printf("%i\t0x%02x\t\'%c\'\t\t%s\n", itemIndex, itemIndex, itemIndex, unicodenames[itemIndex]);
	}else{
		printf("%i\t0x%02x\t%s\t\t%s\n", itemIndex, itemIndex, asciicodes[33], unicodenames[127]);
	}
}

void ascii_print(void)
{
	unsigned char itemIndex;

	printf("%s\t%s\t%s\t%s\t%s\n", "dec", "hex", "codes", "escapes", "unicodenames");
	for(itemIndex=0; itemIndex<128; itemIndex++){
		ascii_print_info(itemIndex);
	}	
}

int legitimacy(char *buffer)
{
    int num_start_index = 0;
	int ret = -1;
	int i;
	int length = 0;

    if(buffer[num_start_index] >= '0' && buffer[num_start_index] <= '9') {
        if(buffer[num_start_index] == '0') {
            num_start_index++;
            if((buffer[num_start_index] == 'x') || (buffer[num_start_index] == 'X')) {
				printf("ibase: HEX_BASE\n");
				buffer[num_start_index]  = toupper(buffer[num_start_index]);
                ibase = HEX_BASE;
				num_start_index++;
            } else if((buffer[num_start_index] == 'b') || (buffer[num_start_index] == 'B')) {
				printf("ibase: BIN_BASE\n");
				buffer[num_start_index]  = toupper(buffer[num_start_index]);
				ibase = BIN_BASE;
				num_start_index++;
			} else {
				printf("ibase: OCT_BASE\n");
                ibase = OCT_BASE;
            }
        } else {
			printf("ibase: DEC_BASE\n");
			ibase = DEC_BASE;
		}
    } else {
		goto err;
    }
	length = strlen(buffer);
	for(i=num_start_index; i<length; i++) {
		if((ibase == HEX_BASE) 
			&& (!(((buffer[i]>='0') && (buffer[i]<='9'))
				||((buffer[i]>='a') && (buffer[i]<='f'))
				||((buffer[i]>='A') && (buffer[i]<='F'))))){
			goto err;
		}
        if((ibase == DEC_BASE) 
			&& (!((buffer[i]>='0') && (buffer[i]<='9')))){
			goto err;
		}
		if((ibase == OCT_BASE) 
			&& (!((buffer[i]>='0') && (buffer[i]<='7')))){
			goto err;
		}
		if((ibase == BIN_BASE) 
			&& (!((buffer[i]>='0') && (buffer[i]<='1')))){
			goto err;
		}
		buffer[i]  = toupper(buffer[i]);
	}
	printf("input = [%s]\n", buffer);
	ret = 0;
	return ret;
err:
	printf("invalid number\n");
	return ret;
}

unsigned long long decimal_get(char *buffer, unsigned long long ibase)
{
	int num_start_index = 0;
	int i,k;
	int length = 0;
	unsigned long long decimal = 0;
	char *valid_data = NULL;

	switch (ibase) {
		case HEX_BASE:
			num_start_index = 2;
			break;
		case DEC_BASE:
			num_start_index = 0;
			break;
		case OCT_BASE:
			num_start_index = 1;
			break;
		case BIN_BASE:
			num_start_index = 2;
			break;
		default:
			num_start_index = 0;
			ibase = DEC_BASE;
	}
	length = strlen(buffer);
	valid_data = buffer+num_start_index;
	//printf("valid data = [%s]\n", valid_data);
	k = length - num_start_index;
	for(i=(k-1); i>=0; i--) {
		unsigned long long temp = 0;

		if((valid_data[i]>='0') && (valid_data[i]<='9')) {
			temp = valid_data[i] - '0';
		} else if((valid_data[i]>='A') && (valid_data[i]<='F')) {
			temp = valid_data[i] - 'A' + 10;
		}
		//printf("temp = %llu, %llu^%d\n", temp, ibase, k-i-1);
		decimal += temp * powl(ibase, k-i-1);
		//printf("decimal:%llu\n", decimal);
	}
	return decimal;
}

const char *dec_to_humanstr(unsigned long long size)
{
	char unit_chars[]= { 'B', 'K', 'M', 'G', 'T', 'P', 'E' };
	unsigned long long unit_result[7]= {};
	static char result_str[42] = ""; 
	char tmp[7] = "";
	int cycle_times;
	int i,j;

	if(size == 0)
		return "0";
	cycle_times = sizeof(unit_chars);
	memset(result_str, 0, sizeof(result_str));
	for(i=(cycle_times-1);i>=0;i--){
		unit_result[i] = size>>(i*10);
		size -= unit_result[i]<<(i*10);
	}
	for(i=(cycle_times-1);i>=0;i--){
		if(unit_result[i] != 0){
			for(j=i;j>=0;j--){
				if(unit_result[j] != 0){
					snprintf(tmp, sizeof(tmp), "%llu%c ", unit_result[j], unit_chars[j]);
				}else{
					snprintf(tmp, sizeof(tmp), "%llu%c ", unit_result[j], unit_chars[j]);
				}
				strcat(result_str, tmp);
			}
			break;
		}
	}
	return result_str;
}

const char *dec_to_binary(unsigned long long decimal)
{
	unsigned long long  outbase = BIN_BASE;
	char data[65] = "";
	static char result_str[65] = "";
	int i = 0;
	int length = 0;
	
	while (decimal / outbase) {
		data[i] = ((decimal % outbase) == 1) ? '1':'0';
		decimal /= outbase;
		i++;
	}
	data[i] = ((decimal % outbase) == 1) ? '1':'0';
	length = strlen(data);
	for(i=0;i<length;i++) {
		result_str[i] = data[length-1-i];
		//printf("result_str[%d]=%c\n", i, result_str[i]);
	}
	//printf("bin result_str = %s\n", result_str);
	return result_str;
}

void usage(int argc, char **argv)
{
	printf("usage: %s <number>\n"\
		"number must be Hexadecimal, Decimal, Octal, Binary\n"\
		"Different bases can be automatically detected and converted\n"\
		"\tHexadecimal: start with 0x or 0X\n"\
		"\tDecimal: default\n"\
		"\tOctal: start with 0\n"\
		"\tBinary: start with 0b or 0B\n"
		"demo:./human 18446744073709551615\n"\
		"\tibase: DEC_BASE\n"\
		"\tinput = [18446744073709551615]\n"\
		"\tHuman: 15E 1023P 1023T 1023G 1023M 1023K 1023B \n"\
		"\tBASE:	number\n"\
		"\thex: 	0XFFFFFFFFFFFFFFFF\n"\
		"\tdec: 	18446744073709551615\n"\
		"\toct: 	1777777777777777777777\n"\
		"\tbin: 	1111111111111111111111111111111111111111111111111111111111111111\n",
		argv[0]);
}

/*
1.检测非法字符
2.未检测溢出（最大64位）
3.不同颜色打印
4.进制自动检测
5.不区分正负
*/

int main(int argc, char **argv)
{
	if(argc == 1){
		usage(argc, argv);
		ascii_print();
	} else if(argc == 2) {
		if(0 == legitimacy(argv[1])) {
			unsigned long long decimal = 0;

			decimal = decimal_get(argv[1], ibase);
			printf("Human: %s\n", dec_to_humanstr(decimal));
			if(decimal<128) {
				printf("%s\t%s\t%s\t%s\t%s\n", "dec", "hex", "codes", "escapes", "unicodenames");
				ascii_print_info(decimal);
			}
			printf("\e[30;45m%s\e[0m\t\e[35m%s\n", "BASE:", "number");
			printf("\e[30;42m%s\e[0m\t\e[32m%#llX\n", "hex: ", decimal);
			printf("\e[30;41m%s\e[0m\t\e[31m%llu\n", "dec: ", decimal);
			printf("\e[30;43m%s\e[0m\t\e[33m%llo\n\e[0m", "oct: ", decimal);
			printf("\e[30;44m%s\e[0m\t\e[34m%s\n\e[0m", "bin: ", dec_to_binary(decimal));		
		}
	} else {
		usage(argc, argv);
		return -1;
	}
	
	
	return 0;
}
