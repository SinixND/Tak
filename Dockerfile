FROM alpine:latest

RUN adduser -D docker
COPY . /home/docker/Tak

RUN apk update && apk upgrade && apk add --no-cache \
	make clang20-extra-tools cppcheck 

# RUN apk add --no-cache \
# 	py3-pip && \
# 	python3 -m venv /venv && \
# 	. /venv/bin/activate && \
# 	pip install --upgrade pip && \
# 	pip install compiledb

WORKDIR /home/docker/Tak

ENTRYPOINT /bin/sh
