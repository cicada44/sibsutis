#!/bin/bash

docker run -it -d --name web-server -p 3000:80 nginx

docker network create my-network
docker network connect my-network web-server

sleep 5
ab -n 1000 -c 10 http://localhost:3000/ > ab_output.txt

docker stop web-server
docker rm web-server
docker network rm my-network
