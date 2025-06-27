var1: data 10
var2: data 15
sum: data 0 ; Variable to store the sum

main:
    ldc var1   ; Load the address of var1
    lnl 0     ; Load the value stored at var1
    ldc var2   ; Load the address of var2
    ldnl 0     ; Load the value stored at var2
    add        ; Add the two numbers
    stl sum    ; Store the sum in the variable 'sum'
    
    ; Output the result
    ldc sum    ; Load the address of sum
    ldnl 0     ; Load the value stored at sum
    OUT        ; Output the value
    HALT       ; Halt the program
