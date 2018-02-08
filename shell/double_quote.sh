#########################################################################
# File Name: double_quote.sh
# Author: andrew Choe
# mail: xgod@163.com
# Created Time: Tue 25 Jul 2017 12:26:34 PM CST
#########################################################################
#!/bin/bash
#Using double quotes the literal value of all characters enclosed is preserved, except for the dollar sign, the backticks(backward single quotes, ``) and the backslash.

#The dollar sign and the backticks retain their special meaning within the double quotes.
#
#The backslash retains its meaning only when followed by dollar, backtick, double quote, backslash or newline. Within double quotes, the backslashes are removed from the input stream when followed by one of these characters. Backslashes preceding characters that don’t have a special meaning are left unmodified for processing by the shell interpreter.

HI="hello"
echo "$HI `date` \$HI \abc"
