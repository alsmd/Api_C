#Create ubuntu as base image
FROM ubuntu


#copia todos os arquivos da pasta atual dentro da pasta ./home dentro do container
ADD . ./Api

#Install packages
RUN apt-get -y update

RUN apt-get -y install expect

RUN expect -f ./Api/instalation

RUN /etc/init.d/mysql start && mysql < /Api/Src/Database/init.sql

RUN apt-get -y install default-libmysqlclient-dev

RUN apt-get -y install vim

RUN apt-get -y install gcc

RUN apt-get -y install make

RUN apt-get install net-tools

RUN make -C /Api

RUN /etc/init.d/mysql start && make db -C /Api
#EXPOSE 8000

#executa ao startar
#CMD [ "/Api/server"]