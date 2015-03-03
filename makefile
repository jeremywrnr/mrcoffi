# BREWING THE INTERNET
src='brew.ino'
out='output.bin'

# use `make getid` to set sparkid externally
# sparkid=$(make getid)
export sid=$(shell echo $(sparkid))

all: clean compile
	spark flash $(sid) $(out)

getid:
	@spark list 2>/dev/null | sed -ne 's/.*(\(.*\)) is online/\1/p'

clean:
	find . -type f -iname "firmware_*" -exec rm {} \;

compile: *.ino
	spark compile $(src)
	mv firmware_* $(out)

