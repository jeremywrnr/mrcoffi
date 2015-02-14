id=53ff6f066667574816342567
src='write-demo.ino'
out='output.bin'

all: clean compile
	spark flash $(id) $(out)

clean:
	find . -type f -iname "firmware*" -exec rm {} \;

compile: *.ino
	spark compile $(src)
	mv firmware_* $(out)

