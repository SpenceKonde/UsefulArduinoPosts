# Print byte as hex, padded with 0's
Stolen from somewhere else, IIRC by amn arduimno community luminary, ages ago. Will update if I find out who wrote it with proper credit... 

```
void showHex (const byte b) {
  char buf [3] = { ((b >> 4) & 0x0F) | '0', (b & 0x0F) | '0', 0};
  if (buf [0] > '9')
    buf [0] += 7;
  if (buf [1] > '9')
    buf [1] += 7;
  Serial.print(buf);
}
```

### Motivation
Serial.print(data,HEX) doesn't pad bytes with value less than 0x0F with the leading 0. 

sprintf() can do all sorts of fancy stuff, but is overkill for this, and has overhead of a whopping 1.5k. 

This provides a fast, efficient way to print bytes as hex without having to do your own zero-padding.

### Explanation 

buf is a three member char array, initialized per above; last byte is 0 (null terminator). For the data, we take the high and low nybble and bitwise OR with '0' (the character). '0' has ascii value 0x30, and is followed by digits 1~9, so will give value between 0x30 and 0x3F, so this gets 0~9. If the value is greater than '9' (0x39), we add 7, resulting in 0x41 ('A') ~ 0x46 ('F'). 

### Compiler warning
The compiler creates warnings on the first line, but I haven't been able to figure out why - no matter how I parenthecize or add in casts, it always acts like there is cast to int outside all that, and then complains of the narrowing conversion from int to char in an array assignment.
