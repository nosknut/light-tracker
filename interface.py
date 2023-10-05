import serial

with serial.Serial('COM3', 115200, timeout=1) as ser:
    ser.write = print
    ser.read=input
    ser.read_until = input
    while True:
        ser.write("s")
        ser.read_until("Max:")
        ser.write("d")
        ser.read_until("%")
        lightmap = ser.read_until("#")
        values = lightmap.split(",")
        matrix = []
        for x in range(0, 180):
            matrix.append([])
            for y in range(0, 180):
                matrix[x].append(int(values[(x * 180) + y]))
        print(matrix)
