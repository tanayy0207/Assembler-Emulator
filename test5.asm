;sum of numbers from 1 to n
call Accumulate
HALT

Accumulate:
    stl 078       ; store return address (from A) into stack
    adj -1      ; adjust stack pointer
loop:
    ldc a
    ldnl 0      ; load a into A
    ldc sum
    ldnl 0      ; load sum into A, B = a
    add         ; A = B + A
    ldc sum
    stnl 0      ; store new value of sum
    ldc a
    ldnl 0      ; load a into A again
    adc -1      ; decrement A
    brz done    ; if A == 0, stop sum calculation
    ldc a
    stnl 0      ; otherwise update a value
    br loop     ; repeat calculation
done:
    adj 1       ; if done, adjust stack pointer
    ldl 0       ; load calling address address to A
    return      ; return to calling address

a: data 10   ; aber upto which sum is calculated
sum: data 0     ; sum is stored here
