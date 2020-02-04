# from pymodbus.client.sync import ModbusSerialClient
from pymodbus.client.sync import ModbusTcpClient

def raz(ip, reg, val):
    # client = ModbusSerialClient(method='rtu', port='/dev/ttyS7', timeout=1, baudrate=19200)
    # client.connect()
    client = ModbusTcpClient(ip)
    # result = client.read_holding_registers(1500, 1)
    client.write_register(int(reg), int(val))
    # print(result)
    client.close()
