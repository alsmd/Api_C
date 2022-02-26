#Create debian as base image
FROM debian


#copia todos os arquivos da pasta atual dentro da pasta ./home dentro do container
ADD . ./Cli

#Install packages
RUN apt-get -y update

RUN apt-get -y install vim

RUN apt-get -y install gcc

RUN apt-get -y install make

RUN make -C ./Cli

#executa ao startar
CMD [ "/Cli/cli" ]