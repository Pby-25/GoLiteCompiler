FROM ubuntu:16.04

RUN apt-get update && apt-get upgrade -y && apt-get install --reinstall make bison flex gcc -y

ADD / 520a1
WORKDIR /520a1
COPY . ./

CMD ./test.sh