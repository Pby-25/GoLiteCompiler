FROM ubuntu:16.04

RUN apt-get update && apt-get upgrade -y && apt-get install --reinstall make bison flex gcc -y

ADD / 520a1
WORKDIR /520a1
COPY . ./

RUN ./build.sh
# CMD bash
# CMD ./test.sh 
# CMD ./run.sh typecheck programs/2-typecheck/invalid/2-1-var_decls/var_decl19.go
#  CMD ./run.sh typecheck programs/2-typecheck/valid/4-6_indexing_expr.go
# CMD ./run.sh typecheck programs/2-typecheck/valid/3-7_assign_stmts.go
CMD ./run.sh typecheck programs/2-typecheck/valid/4-9_cast_expr.go