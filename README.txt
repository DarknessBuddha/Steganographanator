People: Lucia Wang and Ivan Lin

Problems:
At first, we were having issues creating the decoded image as the image came out looking like TV static.
Next, we had issues with understanding when to begin reading for an encoded message and when to stop reading
for an encoded image.
Traversing through the image to find the specific pixel with the encoded message without 10 count variables was also a challenge.
Finally, we had an issue getting the user choice in our extra credit menu where the program would crash.

Solutions:
The solution to the first problem was to create a character bank and append a new line. 
Next, a closer reading of the instructions in the hand-out gave a better understanding that the messgae begins at from the 
first pixel and ends when the value of the bits is over 255.
To traverse through the image, the last bit of an RGB pixel was calculated and then the for loop variables were updated
to find the next encoded/decoded bit.
Finally, we used scanf("%c%*c", &userChoice); instead of scanf("%c", &userChoice); to get the user choice and it did not
crash the program (something to do with the whitespace?).

Thoughts:
I liked the amount of freedom given to us to complete this project in terms of how to encode and decode messages in 
an image. I also like how it incorporated a lot of topics that we learned in class. However, I felt that the instructions
and explanation given in the .pdf was confusing in how to encode and decode messgaes from an image.

Bitwise Operation:
We chose to use the leftshift operator in our function to translate binary to ascii (char binaryToAscii(Binary binary)) 
by adding up positions in binary marked with a 1 by 2^k with k representing the positions starting from the right at 0. 
We did this as leftshifts esssentially 2^k, which is needed to translate binary to decimal.