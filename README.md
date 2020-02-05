# client-server

Simple client-server program. The server part generates a sequence of numbers consisting of subsequences (the subsequence is set by the client). 
Each of the subsequences is an integer non-negative 64-bit counter. 
The generated sequence is sent to the client. <pthread> library used to serve multiple clients.

Example:  
seq1 1 2 . 
seq2 2 3 . 
seq3 3 4 . 
export seq . 
//1, 2, 3, 3, 5, 7, 5, 8, 11...
