id=53ff6f066667574816342567
src='write-demo.ino'
out='output.bin'

all: compile
	spark flash $(id) $(out)

compile: *.ino
	spark compile $(src)
	mv firmware_* $(out)
