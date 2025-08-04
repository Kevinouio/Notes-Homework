// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/QU02/double/Double.asm

// Doubles R0 and stores the result in R1.
// (R0, R1 refer to RAM[0] and RAM[1] respectively.)

// Put your code here.
//KTH258

// Load the value of R0 into D
@0         
D=M        

// Double the value (D = D + D)
D=D+M      

// Store the result in R1
@1         
M=D        
