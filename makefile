id=53ff6f066667574816342567
src='brew.ino'
out='output.bin'

all: clean compile
	spark flash $(id) $(out)

getid:
	export id=$(spark list 2&>1 | sed -ne 's/.*(\(.*\)) is online/\1/p')

clean:
	find . -type f -iname "firmware*" -exec rm {} \;

compile: *.ino
	spark compile $(src)
	mv firmware_* $(out)

