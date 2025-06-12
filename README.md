

chdir 
echo 
kill
jobs
help

shell variables (enviroment variables) 
need a PATH variable 

beginning is highest precedents on path
For us built ins get first dibs (functions)

basic workings of a shell
initilialize get basic configuration of enviroment 
interpret command input from stdin or file
execute commands with interaction and/or parallelism
terminate lets comand terminate, free resources
active - a shell does not terminate unless its a sub-shell



Basic loop
 Read 
  read the command from stdin or file
 Parse
  separate commands into tokens
 Execute


parse
  Name and Args
  simplify with delimiters
  tokenization
