#!/bin/bash

docker compose up -d
docker compose exec apachebench ab -n 30000 -c 1000 nginx/
# docker compose exec cat "cat /var/log/nginx/access.log"
# docker compose down
