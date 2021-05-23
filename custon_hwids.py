Import("env")

board_config = env.BoardConfig()

#micro.build.vid=0x2341
#micro.build.pid=0x8037
#micro.build.usb_product="Arduino Micro"
# "0x2341", "0x8037"

# should be array of VID:PID pairs
board_config.update("build.hwids", [
  #["0x2341", "0x8037"],  # 1st pair
  ["0x8798", "0x8798"]  # 2nd pair, etc.
])

board_config.update("build.usb_product", "Schnoog Throttle")
