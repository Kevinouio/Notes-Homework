// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/QU02/add/Add.asm

// Adds R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//KTH258
// Put your code here.

// Load the value of R0 into D
@0         
D=M        

// Add the value of R1 to D
@1         
D=D+M      

// Store the result in R2
@2         
M=D        
