#ifndef COMMANDS_H
#define COMMANDS_H

class String;

void executeSerialCommand(String command); // execute command from serial
void executeServerCommand(String operation, int value); // execute command from server

#endif