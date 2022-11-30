![](./images/🤖_Steganographanator.png)

## Description
<b> This program encodes a message to a ppm file. </b>

Steganography is the art of hiding a message within another form of media: images, articles,
books, etc.  It is an ancient practice, dating back to approximately 1499. The cool thing about
messages encrypted with steganography is that if you don’t know that there’s a message in the
image or file, it’s really hard to tell that there is a hidden message! A common example of this is
“invisible ink”—unless you know that someone wrote on a paper with invisible ink, then you
wouldn’t know to hold it to heat to see the hidden message.

## Requirements
* gcc
* make

## Usage
```shell
    make run ARGS="<input> <output>"
```
<p>input - name of ppm file to be encoded</p> 
<p>output - name of ppm file to be generated</p>

## Commands
```shell
   make <target>
```
target
- all - compiles all file
- run - executes program
- clean - removes .o .out .exe files