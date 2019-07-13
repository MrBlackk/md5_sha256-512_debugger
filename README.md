# md5, sha256/224, sha512/384 debugger
Initially it was **42 school** project written in C (with some strange code style). That's why code looks so ugly (really, don't look to code).

## About
Recreated part of the OpenSSL functionality: **md5**, **sha224**, **sha256**, **sha384**, **sha512**. It works just as **openssl** on Mac or Linux, but wih additional detailed debug info.

## Usage
Clone repository and run "**make**" command inside folder.

See https://www.embedthis.com/makeme/doc/source/index.html

## Flags
- **-p**, echo STDIN to STDOUT and append the checksum to STDOUT
- **-q**, quiet mode
- **-r**, reverse the format of the output.
- **-s**, print the sum of the given string

## Examples when DEBUG is turned ON (by default)
```
./ft_ssl md5 -s "1"
Table of constants:
K[ 0]=3614090360   K[ 1]=3905402710   K[ 2]=606105819  ...  K[ 7]=4249261313
...
K[56]=1873313359   K[57]=4264355552   K[58]=2734768916 ...  K[63]=3951481745

Table of per-round shift amounts:
s[ 0]=7   s[ 1]=12  s[ 2]=17  s[ 3]=22  s[ 4]=7   s[ 5]=12  s[ 6]=17  s[ 7]=22
...
s[56]=6   s[57]=10  s[58]=15  s[59]=21  s[60]=6   s[61]=10  s[62]=15  s[63]=21

Initial words values:
A: 1732584193
B: 4023233417
C: 2562383102
D: 271733878

-- Set memory end .../ 10000000 /... at 2 byte --
-- Set memory length=1 starting from 57 byte in little endian
#0 memory block binary /byte by byte/:
00110001 10000000 00000000 00000000 00000000 00000000 00000000 00000000
...
00001000 00000000 00000000 00000000 00000000 00000000 00000000 00000000

#0 memory block decimal /unsigned ints/:
[ 0] 32817
[ 1] 0
[ 2] 0
[ 3] 0
[ 4] 0
[ 5] 0
[ 6] 0
[ 7] 0
[ 8] 0
[ 9] 0
[10] 0
[11] 0
[12] 0
[13] 0
[14] 8
[15] 0

Start words values A=1732584193 B=4023233417 C=2562383102 D=271733878
Words on each permutation step:
[ 0] A=2774532084  B=4023233417  C=2562383102  D=271733878
...
[63] A=3506284483  B=2455113239  C=26603279    D=2337415417
Processed A=943901380 B=2183379360 C=2588986381 D=2609149295

Results in hex and concatenate final results:
A: 3842cac4 converting to c4ca4238
B: 8223b9a0 converting to a0b92382
C: 9a50cc0d converting to 0dcc509a
D: 9b84756f converting to 6f75849b
MD5 ("1") = c4ca4238a0b923820dcc509a6f75849b
```

## Turning off DEBUG mode
Open **includes/common.h** file and change:
```
# define DEBUG 1
to
# define DEBUG 0
```
Run "**make re**" command

## Examples when DEBUG is turned off
```
>./ft_ssl
ft_ssl> help

Usage:  ft_ssl command [command opts] [command args]
opts:  -p -q -r -s

Message Digest commands:
md5
sha256
sha224
sha512
sha384

ft_ssl commands:
exit
help

> echo "pickle rick" | ./ft_ssl md5
c5e433c1dbd7ba01e3763a9483e74b04
>
> echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p
Do not pity the dead, Harry.
2d95365bc44bf0a298e09a3ab7b34d2f
>
> echo "Pity the living." | ./ft_ssl md5 -q -r
e20c3b973f63482a778f3fd1869b7f25
>
> echo "And above all," > file
> ./ft_ssl md5 file
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a
> ./ft_ssl md5 -r file
53d53ea94217b259c11a5a2d104ec58a file
> echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file
just to be extra clear
3ba35f1ea0d170cb3b9a752e3360286c
acbd18db4cc2f85cedef654fccc4a4d8
53d53ea94217b259c11a5a2d104ec58a

> echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > big_smoke_order_remix
> ./ft_ssl sha256 -q big_smoke_order_remix
a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9
>
> openssl sha -sha256 big_smoke_order_remix
SHA256 (big_smoke_order_remix) = a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9
>
> ./ft_ssl sha256 -s "wubba lubba dub dub"
SHA256 ("wubba lubba dub dub") = 23a0944d11b5a54f1970492b5265c732044ae824b7d5656acb193e7f0e51e5fa
```
