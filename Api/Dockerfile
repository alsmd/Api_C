#Create ubuntu as base image
FROM ubuntu


#copia todos os arquivos da pasta atual dentro da pasta ./home dentro do container
ADD . /Api

WORKDIR	/Api 

#Install packages
RUN apt-get -y update

RUN apt-get -y install default-libmysqlclient-dev && \
	apt-get -y install vim && apt-get -y install libcurl4-openssl-dev \
	&& apt-get -y install gcc && apt-get -y install make && apt-get install net-tools

EXPOSE 8000

#executa ao startar
CMD [ "bash", "./init.sh"]