# ft_ssl_md5
42 school project

## About
Recreated part of the OpenSSL functionality: **md5**, **sha224**, **sha256**, **sha384**, **sha512**.

## Flags
- **-p**, echo STDIN to STDOUT and append the checksum to STDOUT
- **-q**, quiet mode
- **-r**, reverse the format of the output.
- **-s**, print the sum of the given string

## Examples
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
