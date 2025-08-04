// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/QU02/loop/Loop.asm

// Loops R0 times and stores -1 in R1 upon completion.
// (R0, R1 refer to RAM[0] and RAM[1] respectively.)
// (LOOP and END refer to labels to be jumped to.)
// (i refers to the variable used for the counter.)

// Basic Direction:
// Initialize the i counter variable outside of the loop and set it to 0.
// (This is to account for repeated runs via the CPUEmulator. It's a safety
// net for reseting the memory value at your variable.)

// Begin LOOP

//   Store value in i to D register to use for later
//   Store the difference of R0 and i (R0 - i)

//   CONDITIONAL STATEMENT
//   if (R0 - i) <= 0 goto END

//   else (this stays in loop after the CONDITIONAL JUMP)
//   Increment i

//   goto LOOP (Restarts LOOP)

// End LOOP 

// Begin END 

//  Store value of i in D register
//  Store value in D register in R1

// End END

//KTH258
// Put your code here.
// Initialize i (use R2 for i) and set it to 0
@2        
M=0        

// Begin LOOP
(LOOP)
@0         
D=M        
@1         
D=D-M      

// Conditional jump if (R0 - i) <= 0, go to END
@END
D;JLE      

// Increment i (R2 = i + 1)
@1        
M=M+1      

// Go back to LOOP
@LOOP
0;JMP      


