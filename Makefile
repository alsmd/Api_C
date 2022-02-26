watch_dir = ./watch/

$(watch_dir).pull_depen:
	docker pull mysql
	docker pull ubuntu
	docker pull debian
	touch $(watch_dir).pull_depen

$(watch_dir).create_volum:
	docker volume create --name Logs
	docker volume create --name Database-volume
	touch $(watch_dir).create_volum

$(watch_dir).build:
	docker build -t api ./Api
	docker build -t cli ./Cli
	docker build -t my_sql ./Database
	touch $(watch_dir).build

$(watch_dir).network:
	docker network create database_network
	touch $(watch_dir).network

$(watch_dir).run:
	docker run -d --network database_network -v Database-volume:/var/lib/mysql --name=mysql_container my_sql
	docker run -ti -d --name=api_container -p 8000:8000 -v Logs:/Logs api
	docker network connect database_network api_container
	docker run -ti -d --name=cli_container --volumes-from api_container cli
	touch $(watch_dir).run

init_server: $(watch_dir).pull_depen $(watch_dir).create_volum $(watch_dir).build $(watch_dir).network $(watch_dir).run
	
reset_server:
	docker rm -f api_container
	docker rm -f mysql_container
	docker rm -f cli_container
	rm -f $(watch_dir).pull_depen $(watch_dir).create_volum $(watch_dir).build $(watch_dir).network $(watch_dir).run
	docker network remove database_network
