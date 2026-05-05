FROM alpine:latest

RUN adduser -D docker
COPY . /home/docker/Tak

RUN apk update && apk upgrade && apk add --no-cache \
	clang20 cppcheck git make ncurses-dev

# compiledb
#RUN apk add --no-cache py3-pip
#RUN python3 -m venv /venv
#RUN . /venv/bin/activate
#RUN pip install compiledb

WORKDIR /home/docker/Tak

ENTRYPOINT /bin/sh
