Symbol: add symbol kind to distinsh var dcl, type dcl, func dcl, prefix with sk_ to dist previously defined kinds
var a struct {}
return statement： 1. check if needed 2. check if return type is right 3. when needed, how to check it actually exists, especially with if/else/for/switch cases 



type a struct{t int} and type b struct{t int} are not the same type
however, when declared c as var c strcut{t int}, c shares same type as a and b
the field has to be declared in same order, however multiple assignment and assignment one by one are equivalent