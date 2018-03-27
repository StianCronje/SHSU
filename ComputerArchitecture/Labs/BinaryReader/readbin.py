# By Christiaan Cronje
# Works with Python 2.7

import struct

fileName = raw_input("Enter a file name: ")
print (fileName)

with open(fileName, "rb") as f:
    byte = f.read(4)    # read 32 bits from binary file

    while byte:
        inputs = struct.unpack(">i",byte)[0]    # convert byte array to int
        printf(input)
        inNum = bin(inputs)                     # convert binary input
        hexNum = hex(inputs)                    # convert hex input
        bit6 = (inputs >> 16) & 0b111111        # get value from bits 21-16
        bit16 = inputs & 0b111111111111111      # get value from bits 15-0

        print(inNum[2:].zfill(32), hexNum[2:].zfill(8), bit6, bit16)

        byte = f.read(4)    # read next 32 bits
    # f will close automatically