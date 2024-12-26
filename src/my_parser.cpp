#include "my_parser.h"

void parseBands(char buf[33])
{
#ifdef SERIAL_DEBUG
    // fps(2);
    //Serial.println("parsing bands");
#endif
    static char bands_chars[7][4];
    char delimiter[] = ",";
    char *ptr;
    //Serial.println("before data");
    //Serial.println("before strtok");
    ptr = strtok(buf, delimiter);
    memcpy(bands_chars[0], ptr, 4);
    ptr = strtok(NULL, delimiter);
    memcpy(bands_chars[1], ptr, 4);
    ptr = strtok(NULL, delimiter);
    memcpy(bands_chars[2], ptr, 4);
    ptr = strtok(NULL, delimiter);
    memcpy(bands_chars[3], ptr, 4);
    ptr = strtok(NULL, delimiter);
    memcpy(bands_chars[4], ptr, 4);
    ptr = strtok(NULL, delimiter);
    memcpy(bands_chars[5], ptr, 4);
    ptr = strtok(NULL, delimiter);
    memcpy(bands_chars[6], ptr, 4);
    //Serial.println("after strtok");
    // reconvert char arrays to integers
    for (int i = 0; i < 7; i++)
    {
        dsp.bandLevelsReceived[i] = atoi(bands_chars[i]);
    }
}

void parsePayload(char buf[33])
// parse the raw data
{
    // Serial.println(buf);
    char identifier[2];     // a char to hold the identifier of the payload. this is used to identify what to do with the payload
    char payload[33];       // a char array to hold the payload after splitting away the identifier
    char delimiter[] = ";"; // define a char to split at
    char *ptr;              // pointer which temporarily points to the found section

    ptr = strtok(buf, delimiter); // initialise strtok & create first section(seperate the identifier from the payload
    memcpy(identifier, ptr, 2);   // copy the found identifier to variable "identifier"

    // Serial.print("found identifier: ");
    // Serial.println(identifier);
    ptr = strtok(NULL, delimiter); // take the rest of the strtokbuffer
    memcpy(payload, ptr, 33);      // and copy it to the variable "payload"

    switch (identifier[0])
    {         // now interpret the identifier
    case 'b': // band-levels
        // Serial.println("got band-values");
        parseBands(payload); // parse it

        break;

    default: // default action, in case no qualified identifier was found
        Serial.print("payload is: <");
        Serial.print(payload);
        Serial.print(">, but identifier: <");
        Serial.print(identifier);
        Serial.println("> has no valid action");
    }
}

void interpretParsedVariable(char nam[32], char val[32])
{
    if (strcmp(nam, "brightness") == 0)
    {
        //brightness = atoi(val);
        Serial.println("brightness changed");
    }
    else if (strcmp(nam, "hue") == 0)
    {
        Serial.println("hue changed");
    }
}

void parseMisc(char buf[32])
{
    char varname[32];             //create array to hold the name
    char varvalue[32];            //create array to hold the value
    bool isValue = false;         //a bool to switch from filling name to fill value
    char delimiter[] = ":";       //define a char to split at
    char *ptr;                    //pointer which temporarily points to the found section
    ptr = strtok(buf, delimiter); //initialise strtok & create first section (name of variable)
    while (ptr != NULL)
    { //until null-termination of input buffer is found
        if (!isValue)
        {                             //if "isvalue" is false ->
            memcpy(varname, ptr, 32); //copy contents of memory location from "ptr" to "varname"
            isValue = true;           //set "isvalue" true
        }
        else if (isValue)
        {                              //if "isvalue" is true
            memcpy(varvalue, ptr, 32); //copy contents of memory location from "ptr" to "varvalue"
            isValue = false;           //set the bool
        }
        ptr = strtok(NULL, delimiter); //find next section (value of variable)
    }
    Serial.println("Variable found: ");
    Serial.println(varname);
    Serial.println("Its value is: ");
    Serial.println(varvalue);
    interpretParsedVariable(varname, varvalue);
}

void parseVariable(char buf[32])
{
    char varname[32];             //create array to hold the name
    char varvalue[32];            //create array to hold the value
    bool isValue = false;         //a bool to switch from filling name to fill value
    char delimiter[] = ":";       //define a char to split at
    char *ptr;                    //pointer which temporarily points to the found section
    ptr = strtok(buf, delimiter); //initialise strtok & create first section (name of variable)
    while (ptr != NULL)
    { //until null-termination of input buffer is found
        if (!isValue)
        {                             //if "isvalue" is false ->
            memcpy(varname, ptr, 32); //copy contents of memory location from "ptr" to "varname"
            isValue = true;           //set "isvalue" true
        }
        else if (isValue)
        {                              //if "isvalue" is true
            memcpy(varvalue, ptr, 32); //copy contents of memory location from "ptr" to "varvalue"
            isValue = false;           //set the bool
        }
        ptr = strtok(NULL, delimiter); //find next section (value of variable)
    }
    Serial.println("Variable found: ");
    Serial.println(varname);
    Serial.println("Its value is: ");
    Serial.println(varvalue);
    interpretParsedVariable(varname, varvalue);
}
