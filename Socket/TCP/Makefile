#!/bin/sh
TARGET = stServer.c stClient.c
CC = gcc

all:$(TARGET)
	@echo "==== Compile"
	$(CC) -o server stServer.c
	$(CC) -o client stClient.c
clean:
	@if [ -e server ] || [ -e client ]; then echo "==== Clean"; fi
	@if [ -e server ]; then echo "rm server"; rm server; fi
	@if [ -e client ]; then echo "rm client"; rm client; fi
