# setting terminal character display color and moving cursor position in code

This article describes how to use the ANSI escape code to set the [terminal](https://developpaper.com/tag/terminal/) [character](https://developpaper.com/tag/character/) display color, move the [cursor](https://developpaper.com/tag/cursor/) position, and achieve a progress bar percentage jump effect.

# ANSI escape code

In Linux, ANSI escape codes can be used to set character display color, move cursor position, clear character display, etc.

ANSI escape code is supported by the terminal itself, independent of  the programming language, and can be used in C language, Java, python,  or shell.

The bash shell is used as an example to illustrate how to use ANSI escape codes.

# ANSI escape code format

The ANSI escape code is composed of a string of ASCII encoded strings, which requires ASCII encoding*Escape*Characters and*[*Character, followed by a specific escape code, specifies the corresponding operation. The basic format is as follows:

```
Esc[escape code
```

The escape character is the character corresponding to the ESC key.

Because pressing the ESC key will not get a character that can be  displayed, you need to use a specific encoding value to represent the  character.



In different programming languages, the writing of character encoding values may be different. Commonly used`\e`Escape characters to represent ESC characters.

# Testing ANSI escape code with echo [command](https://developpaper.com/tag/command/)

In the bash shell, you can use the`echo`Imperative`-e`Option to test the ANSI escape code.

View the man echo pair`-e`The options are described as follows:

> **-e**
>
> enable interpretation of backslash escapes.
>
> If -e is in effect, the following sequences are recognized:
>
> **e**
>
> ```
> escape
> ```
>
> **0NNN**
>
> ```
> byte with octal value NNN (1 to 3 digits).
> ```

That is, in`echo`In the order,`-e`Option to specify the processing of escape characters.

`\e`Escape characters represent escape characters.

`\0NNN`Escape characters are obtained using octal*NNN*The character corresponding to the encoded value.

In ASCII encoding, the octal value corresponding to the escape character is 033.



Then in the`echo`In the order,`\033`Represents the escape character.



use`echo`Command to test ANSI escape code can be written as`echo -e "\033[31m"`。

there*31m*The escape code means to set the foreground color of the terminal character to red.

Linux printf command can also output ANSI escape code, and does not need to add`-e`Options, such as’ printf ‘E [31m].

**be careful**You need to use double or single quotation marks*033[31m*To avoid bash’s own`\`It will be removed`\`Character, resulting in`echo`Order not received`\`Character, escape character cannot be processed.

It can also be written as`echo -e "\e[31m"`，`\e`Also represents escape characters.

In the later test, it should be used uniformly`\e`Type less characters.

The specific tests are as follows:

> $ echo -e “e[31m”
>
> <span style=”color:red;”>$ echo -e “e[0m”</span>
>
> $

implement`echo -e "\e[31m"`After the command, the prompt character of the terminal will turn red, and the characters entered later will also turn red.

That is, the default character color of the terminal changes to red.

implement`echo -e "\e[0m"`Command to reset the terminal properties so that the terminal character color becomes the original default color.

there*0m*The escape code represents a reset character display property.

Generally speaking, in order not to affect the display of the  terminal itself, it is recommended to use the ANSI escape code to set  the display color of a string*0m*Escape code to reset to the original color.

Examples are as follows:

> $ echo -e “e[31mThis is a red string.e[0m”  
> <span style=”color:red;”>This is a red string.</span>  
> $

In the above command,`\e[31m`Is an ANSI escape code, indicating that the terminal character color is set to red.

`\e[0m`It is also an ANSI escape code, indicating that the color attribute of the terminal will be reset to the original color.



The string between the two escape codes is displayed on the terminal.



After executing the command, the prompt of the terminal will be displayed in the original color.

# Set the ANSI escape code of terminal character color

The following describes in detail the ANSI escape code for setting the terminal character color. Its basic format is as follows:

```
Esc[Value;...;Valuem
```

there*Value*You can provide multiple values separated by a semicolon ‘;’.

These values can specify the foreground color, background color, and  character properties (bold, underline, reverse) of the character,  respectively. There is no limit to the order between them.

The escape code ends with`m`End of character.

Set the value of the character foreground color as follows:

| Color value | [colour](https://developpaper.com/tag/colour/) |
| ----------- | ---------------------------------------------- |
| 30          | black                                          |
| 31          | gules                                          |
| 32          | green                                          |
| 33          | yellow                                         |
| 34          | blue                                           |
| 35          | violet                                         |
| 36          | Cyan                                           |
| 37          | white                                          |

Set the value of character background color as follows:

| Color value | colour |
| ----------- | ------ |
| 40          | black  |
| 41          | gules  |
| 42          | green  |
| 43          | yellow |
| 44          | blue   |
| 45          | violet |
| 46          | Cyan   |
| 47          | white  |

Set the value of the character property as follows:

| Property value | Attribute meaning                               |
| -------------- | ----------------------------------------------- |
| 0              | Reset all properties, including character color |
| 1              | Set to bold                                     |
| 4              | Underline                                       |
| 5              | Turn on blinking                                |
| 7              | Color reversal                                  |
| 8              | Show invisible text                             |

Specific examples are as follows:

> $ echo -e “e[31;44mFg color: Red. Bg color: Blue.e[0m”  
> <span style=”color:red;background-color:blue;”>Fg color: Red. Bg color: Blue.</span>  
> $ echo -e “e[44;31mFg color: Red. Bg color: Blue.e[0m”  
> <span style=”color:red;background-color:blue;”>Fg color: Red. Bg color: Blue.</span>

As you can see,`\e[31;44m`、`\e[44;31m`The color effect of the two escape codes is the same.

The given foreground color and background color have no order.

At present, most terminals support 256 colors and can be used`Esc[38;5;Valuem`To set the terminal character to 256 colors.

there*Value*The value is 0-255.

For example,`echo -e "\e[38;5;111mAAAAAA\e[0m"`The command is set to the color corresponding to 111.

For specific color values, you can view the color table of 256  colors. Many articles on the Internet have explanations. I won’t list  them here.

# Use ANSI escape code to move terminal cursor

ANSI escape code can be used to move the cursor position of the terminal to change the output position of characters.

Specific examples are as follows:

```
$ echo -e "123456789\e[4Dabc"
12345abc9
```

In this order,`\e[4D`Escape code means to move the cursor to the left by 4 columns.

After 4, the position of the cursor can be seen again*abc*, covering the original*678*Three characters.

The specific escape code of moving cursor is described as follows:

| Escape code      | meaning                                                      |
| ---------------- | ------------------------------------------------------------ |
| Esc[nA           | Move the cursor up n lines and the number of columns remains unchanged. Move to the top of the terminal and do not move again |
| Esc[nB           | Move the cursor down n lines, and the number of columns remains  unchanged. Move to the bottom of the terminal and do not move again |
| Esc[nC           | Move the cursor to the right of N columns, and the number of rows remains unchanged. Move to the far right of the terminal |
| Esc[nD           | Move the cursor to the left of N columns, and the number of rows remains unchanged. Move to the far left of the terminal |
| Esc[nE           | Move the cursor down n lines and the number of columns changes to the beginning of the line |
| Esc[nF           | Move the cursor up n lines and the number of columns changes to the beginning of the line |
| Esc[Line;ColumnH | Moves the cursor to the specified number of rows and columns. If no value is provided, the default value is 0 |
| Esc[ColumnG      | Move the cursor to column column column, and the current number of rows remains unchanged |
| Esc[s            | Save the current cursor position. You can use ESC [u to jump to the saved location |
| Esc[u            | Jump to the cursor position saved by ESC [S                  |
| Esc[?25l         | Hide cursor (lowercase L after 25)                           |
| Esc[?25h         | Show cursor                                                  |

The terminal location mentioned above refers to the window position visible to the terminal, excluding the buffer location.

That is, the window display will not scroll, only jump the cursor in the currently visible window area.

**be careful**: due to`echo`The command will  output line feed character by default, which will cause line break again after moving the cursor, which will cause interference to the cursor  movement effect.

When testing escape code of moving cursor, it is recommended to use`printf`Command test. This command does not output line breaks by default.

Since you need to press enter in Bash to execute the command, it will affect the left and right movement effect of the cursor. It is  recommended that the`printf`Move the cursor left and right in the output content.

The actual test shows that if the cursor moves to the right column n, the cursor will be behind the n column, and then the output string will start from column n + 1.

ESC [C, ESC [0C, and ESC [1c) have the same effect, with the cursor moving to the right by 1 column.

Similarly, the effect of ESC [D, ESC [0d, and ESC [1D) is the same, and the cursor is moved to the left by 1 column.

use`printf`The command tests are as follows:

```
$ printf "123456789\e[1Da\n"
12345678a
$ printf "123456789\e[0Da\n"
12345678a
$ printf "123456789\e[Da\n"
12345678a
```

As you can see, use`\e[D`、`\e[0D`、`\e[1D`Move the cursor to the left, and then output the character a, covering the same character 9.

The cursor movement effect of the three escape codes is the same.

```
$ printf "123456789\e[4Da\n"
12345a789
$ printf "123456789\e[4D\e[Ca\n"
123456a89
$ printf "123456789\e[4D\e[0Ca\n"
123456a89
$ printf "123456789\e[4D\e[1Ca\n"
123456a89
```

`\e[4D`Move the cursor to the left by 4 columns to the position of character 6.

`\e[C`、`\e[0C`、`\e[1C`Move the cursor to the right to the next column to the position of character 7, and output character a, covering character 7.

# The effect of progress percentage is achieved by moving the cursor

We can achieve the effect of progress percentage by moving the cursor. Suppose there is one`progress.sh`The script is as follows:

```
#!/bin/bash

for ((i = 0; i <= 100; ++i)); do
    printf "\e[5D%3d%%" $i
    sleep 0.1s
done
echo
```

Use it here`printf`Command to format the string.

`printf`Commands are also used`\e`To represent the escape character.

`\e[5D`The escape code moves the cursor to the left by 5 columns.

Since the output characters are no more than 5 characters, each time  the cursor moves 5 columns to the left, it will move to the far left and output from the first column.

Then the output content will cover the content of the previous  output, so as to achieve the effect of repeated output in the same line.

`sleep 0.1s`The command indicates a pause of 0.1 seconds.  Add this statement so that you can see the progress percentage jump  clearly. Otherwise, if the execution is too fast, the percentage will  jump to 100%.

implement`progress.sh`The results of the script are as follows:

```
$ ./progress.sh
100%
```

I can’t see the percentage change here. It can be seen from the actual implementation.

As a result, information is printed multiple times in the for loop,  all of which are printed on the same line and override the previous  output. Instead of wrapping.

# Through moving the cursor to achieve the effect of progress bar

Next, move the cursor to achieve the effect of the progress bar. Suppose there is one`progressbar.sh`The script is as follows:

```
#!/bin/bash

function print_chars()
{
    #The first parameter passed in specifies the string to print
    local char="$1"
    #The second parameter passed in specifies how many times the specified string will be printed
    local number="$2"
    local c
    for ((c = 0; c < number; ++c)); do
        printf "$char"
    done
}

declare -i end=50
for ((i = 1; i <= end; ++i)); do
    printf "\e[80D["
    print_chars "#" $i
    print_chars " " $((end - i))
    printf "] %3d%%" $((i * 2))
    sleep 0.1s
done
echo
```

This script defines a*print_chars*Function to print the same character multiple times.

`printf "\e[80D["`Statement to move the cursor to the left 80 columns. Since the total character length of this progress bar is  less than 80, it will move to the left and always output from the first  column.

The ‘[‘ character after ’80D’ is the first character at the beginning of the progress bar.

`print_chars "#" $i`Statement incremental printing multiple ා characters, forming the effect of the progress bar moving forward.

`print_chars " " $((end - i))`Statement to print multiple  spaces to the last specified column so that the end character of the  progress bar is always printed in the same column.

`printf "] %3d%%" $((i * 2))`Statement to print the end character of the progress bar], and the percentage of the progress bar.

`sleep 0.1s`The statement is suspended for 0.1 seconds to avoid the execution being too fast to see the moving effect of the progress bar.

implement`progressbar.sh`The results of the script are as follows:

```
$ ./progressbar.sh
[##################################################] 100%
```

I can’t see the percentage change here. It can be seen from the actual implementation.

# Clear screen and clear characters with ANSI escape code

The following ANSI escape code can be used to clear the screen and clear the characters behind the cursor.

| Escape code | meaning                                                      |
| ----------- | ------------------------------------------------------------ |
| Esc[2J      | Clear the screen. When tested on Ubuntu, the cursor position remains unchanged |
| Esc[K       | Clear all characters from the cursor position to the end of the line (including the characters under the cursor) |
| Esc[1K      | Clear all characters from the cursor position to the beginning of the line (including the characters under the cursor) |
| Esc[2K      | Clear the entire line where the cursor is located            |

**be careful**The letters J and K above are all capital letters.

Specific examples are as follows:

```
$ printf "123456789\e[5D\e[K\n"
1234
$ printf "123456789\e[5D\e[1K\n"
     6789
$ printf "123456789\e[5D\e[2K\n"
```

`printf "123456789\e[5D\e[K\n"`The command moves the cursor to the left 5 columns, stops at the position of character 5, and then uses the`\e[K`The escape code clears all characters from the back of the cursor position, leaving only the preceding*1234*character string.

`printf "123456789\e[5D\e[1K\n"`Command usage`\e[1K`The escape code clears all characters from the front of the cursor, leaving only the following*6789*character string.

`printf "123456789\e[5D\e[2K\n"`Command usage`\e[2K`The escape code clears the whole line of the cursor, and the output content is empty.