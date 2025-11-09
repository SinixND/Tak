FROM alpine:latest AS build

RUN mkdir -p /app

WORKDIR /app

RUN apk update && apk upgrade && apk add --no-cache \
	git make clang doxygen cppcheck clang20-extra-tools py3-pip

COPY . /app

ENTRYPOINT /bin/sh 

# FROM alpine:latest AS run

# FROM alpine:latest AS dev

# ADD			Add local or remote files and directories.
# ARG			Use build-time variables.
# CMD			Specify default commands.
# COPY			Copy files and directories.
# ENTRYPOINT	Specify default executable.
# ENV			Set environment variables.
# EXPOSE		Describe which ports your application is listening on.
# FROM			Create a new build stage from a base image.
# HEALTHCHECK	Check a container's health on startup.
# LABEL			Add metadata to an image.
# MAINTAINER	Specify the author of an image.
# ONBUILD		Specify instructions for when the image is used in a build.
# RUN			Execute build commands.
# SHELL			Set the default shell of an image.
# STOPSIGNAL	Specify the system call signal for exiting a container.
# USER			Set user and group ID.
# VOLUME		Create volume mounts.
# WORKDIR		Change working directory.
