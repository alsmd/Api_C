#Create ubuntu as base image
FROM ubuntu


#copia todos os arquivos da pasta atual dentro da pasta ./home dentro do container
ADD . /Api

WORKDIR	/Api 

#Install packages
RUN apt-get -y update

#RUN apt-get -y install expect

#RUN expect -f ./instalation

#RUN /etc/init.d/mysql start && mysql < ./Src/Database/init.sql

RUN apt-get -y install default-libmysqlclient-dev

RUN apt-get -y install vim

RUN apt-get -y install gcc

RUN apt-get -y install make

RUN apt-get install net-tools

EXPOSE 8000

#executa ao startar
CMD [ "bash", "./init.sh"]