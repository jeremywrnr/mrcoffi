id=53ff6f066667574816342567
src='write-demo.ino'

all: compile
	spark flash $(id)

compile: *.ino
	spark compile $(src)
	mv firmware_
