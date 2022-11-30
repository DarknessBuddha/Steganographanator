Ivan Lin
Partner: Lucia Wang

Description:
The first problem that occurred was the image did not print correctly. It turns
out that on Windows the file must be opened in binary. The second problem
that occurred was that the decoded message was partially correct. Half of the
message was gibberish. The solution was to stop reading the file when the bits
add up to 0 which translates to NUL or the null byte in ascii. Lastly,
the message we were trying to get from the user failed to read correctly. It
skipped the next prompt for user input. The solution was to flush the new line
out by reading and discarding it.

Thoughts:
The concept of the assignment was fine; however, the instructions were
so unclear that I had to sanitize my 4k monitor with bleach. The tip on when to
stop decoding fails to make sense since it is impossible to have a bit over 255
when the first bit is always 0 leaving only 8 usable bits.
There are no example inputs or outputs of the program. I did not how to encode
the remaining image after encoding the message,
which forced me to print the sample ppm file in plaintext; I determined that
the remaining bits should be 0s.

Bitwise or shift operation:
We used right shift operation in the function binaryToAscii to simulate how we
would normally convert binary to decimal which is adding up all the bits by
b*2^k where k is the position of the bit starting at 0 and b represents the bit
0 or 1.